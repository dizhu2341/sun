#include "rj_msg.h"

#include "IncludeFm/s_jc_public.h"

CRjMsg::CRjMsg(IAS2Context *lpContext, 
							 string TopicName, 
							 string TableName)
{
	m_lpContext = lpContext;
	m_szTopicName = TopicName;
	m_szTableName = TableName;
}

CRjMsg::~CRjMsg()
{
	m_lpContext = NULL;
	m_szTopicName = "";
	m_szTableName = "";
}

string CRjMsg::GetProcName()
{
	char sSql[500] = {0};
	sprintf(sSql, "select t.prc_name prc_name from jc_trcinterfacecfg t where t.table_name = '%s'", m_szTableName.c_str());
		
	IConnection* lpConn = GetO3DBConn();
	if(NULL == lpConn)
	{
		DLOGERROR(m_lpContext, -100, "获取数据库连接为空,获取存储过程名失败");
		return "";
	}
	
	IF2ResultSet* lpResultSet = lpConn->executeQuery(sSql);
	if (NULL == lpResultSet)
	{
		DLOGERROR(m_lpContext, -1, "查询存储表["<< m_szTableName.c_str() <<"]的日间存储过程失败,错误信息[" << lpConn->getErrInfo() << "]");
		lpConn->toFree();
		return "";
	}
	if(lpResultSet->IsEmpty())
	{
		DLOGWARNING(m_lpContext, "查询存储表["<< m_szTableName.c_str() <<"]的日间存储过程为空,可能没有支持该日间更新");
		lpConn->toFree();
		return "";
	}
	
	string szPrcName = lpResultSet->GetStr("prc_name");
	lpResultSet->Destroy();
	lpConn->toFree();
	return szPrcName;
}

bool CRjMsg::CallProcedure(string szProcName, IF2Packer* lpDelRecPack)
{
	// 上锁
	//CMutexMgr::GetInstance()->GetLock(m_szTableName.c_str());
	lpDelRecPack->BeginPack();
	
	//数据新增、修改和删除都在存储过程中完成，删除数据通过结果集返回
	char sSql[100] = {0};
	sprintf(sSql, "call %s(?)", szProcName.c_str());
	
	IConnection* lpConn = GetO3DBConn();
	if(NULL == lpConn)
	{
		DLOGERROR(m_lpContext, -100, "获取数据库连接为空,调用存储过程名["<< szProcName.c_str() <<"]失败");
		return "";
	}
	
	ICallableStatement *lpCall = lpConn->createCallableStatement();
	lpCall->prepare(sSql);
	lpCall->setInt(1, 2);// 第一个入参输入值2，表示调用日间更新，例call sp_o4sync_asset(2)
	IF2ResultSet *lpResultSet = lpCall->open();
	// 将待删除的数据打包出去
	if(NULL == lpResultSet)  // 如果执行出错
	{
		DLOGERROR(m_lpContext, -1, "执行存储过程["<< szProcName.c_str()  <<"]异常,错误信息[" << lpConn->getErrInfo() << "]");
		lpCall->destroy();		
		lpConn->toFree();
		lpDelRecPack->EndPack();
		return false;
	}
	PackResultSet(lpResultSet, lpDelRecPack);
	lpResultSet->Destroy();
	lpCall->destroy();		
	lpDelRecPack->EndPack();
	lpConn->toFree();
	// 释放锁
	//CMutexMgr::GetInstance()->FreeLock(m_szTableName.c_str());
		
	return true;
}

string CRjMsg::GetCurrUpdateTimeStamp()
{
	char sSql[500] = {0};
	sprintf(sSql, "select nvl(to_char(update_time_stamp, 'yyyymmddhh24missff'), '0') update_time_stamp from jc_ttimetable where table_name = '%s'", m_szTableName.c_str());
	
	IConnection* lpConn = GetO3DBConn();
	if(NULL == lpConn)
	{
		DLOGERROR(m_lpContext, -100, "获取数据库连接为空,获取最后更新时间戳失败");
		return "";
	}
	
	IF2ResultSet *lpResultSet = lpConn->executeQuery(sSql);
	if (NULL == lpResultSet)
	{
		DLOGERROR(m_lpContext, -1, "查询表["<< m_szTableName.c_str() <<"]的最后更新时间失败,错误信息[" << lpConn->getErrInfo() << "]");
		lpConn->toFree();
		return "";
	}
	if(lpResultSet->IsEmpty())
	{
		DLOGWARNING(m_lpContext, "查询表["<< m_szTableName.c_str() <<"]的最后更新时间为空,当做0处理");
		lpConn->toFree();
		return "0";
	}
	
	string szUpdateTime = lpResultSet->GetStr("update_time_stamp");
	DLOGWARNING(m_lpContext, "szUpdateTime:"<< szUpdateTime.c_str());
	lpResultSet->Destroy();
	lpConn->toFree();
	return szUpdateTime;
}

bool CRjMsg::PublishTopic(string szTimePrev, string szTimeAft, IF2Packer* lpDelRecPack)
{

	// 如果表名是jc_tfeeqh、jc_tfeehs、uft_tautoriskpermission，需要删除各自的明细表的数据，并发布主题
	if ("jc_tfeeqh" == m_szTableName || "jc_tfeehs" == m_szTableName || "uft_tautoriskpermission" == m_szTableName)
	{
		// 先把原来的表名保存到临时变量中
		string tempTable = m_szTableName;

		// 把明细表赋给m_szTableName
		if ("jc_tfeeqh" == m_szTableName)
		{
			m_szTableName = "jc_tfeedetailqh";
		}
		else if ("jc_tfeehs" == m_szTableName)
		{
			m_szTableName = "jc_tfeedetailhs";
		}
		else if ("uft_tautoriskpermission" == m_szTableName)
		{

			m_szTableName = "uft_tautoriskparam";
		}
		// 获取存储过程名
		string szProcName = GetProcName();
		if("" == szProcName)
		{
			DLOGERROR(m_lpContext,-100, "获取表["<< m_szTableName.c_str() <<"]存储过程为空,跳过更新");
			return false;
		}
		DLOGEVENT(m_lpContext,"获取到表["<< m_szTableName.c_str() <<"]存储过程名[" << szProcName.c_str() << "]");
		// 执行存储过程
		IF2Packer *lpDelRecPack1 = m_lpContext->GetF2PackSvr()->GetPacker(2);
		if (NULL == lpDelRecPack1)
		{
			DLOGERROR(m_lpContext, -100, "申请待存放待删除数据的PACK包失败,表["<< m_szTableName.c_str() <<"]日间处理失败");
			return false;
		}
		bool bRet = CallProcedure(szProcName, lpDelRecPack1);
		if(false == bRet)
		{
			DLOGERROR(m_lpContext, -100, "执行存储过程["<< szProcName.c_str() << "]失败,表["<< m_szTableName.c_str() <<"]日间处理失败");
			if (lpDelRecPack1)
			{
				free(lpDelRecPack1->GetPackBuf());
				lpDelRecPack1->Release();
			}
			return false;
		}


		//主表或者明细表存在需要删除的数据，那么就得发送多结果集日间删除消息
		bRet = PublishRjMultiDataSetTopic(lpDelRecPack, lpDelRecPack1, tempTable);
		if(false == bRet)
		{
			DLOGERROR(m_lpContext, -100, "推送表["<< tempTable.c_str() << "|" << m_szTableName.c_str() << "]消息主题失败");
			if (lpDelRecPack1)
			{
				free(lpDelRecPack1->GetPackBuf());
				lpDelRecPack1->Release();
			}
			return false;
		}
		m_szTableName = tempTable;

		if (lpDelRecPack1)
		{
			free(lpDelRecPack1->GetPackBuf());
			lpDelRecPack1->Release();
		}
	}
	else
	{
		// 发布删除的主题
		if (false == PublishDelMsg(lpDelRecPack))
			return false;
	}

	//-------------------------
	// 发布更新的主题

	if( false == PublishUpdateMsg(szTimePrev, szTimeAft))
		return false;
	
	if("jc_tcapitalaccount" == m_szTableName)
	{
		string tempTable = m_szTableName;
		m_szTableName = "jc_tassetcaptacct";
		if( false == PublishUpdateMsg(szTimePrev, szTimeAft))
			return false;
		m_szTableName = tempTable;

	}
	return true;
}

bool CRjMsg::PublishDelMsg(IF2Packer* lpDelRecPack)
{
	IF2UnPacker* unPack = lpDelRecPack->UnPack();
	if( 0 == unPack->GetRowCount())
	{
		DLOGEVENT(m_lpContext, "没有需要删除的记录,退出发布删除主题");
		return true;
	}
		
	// 发布主题
	
	// 打消息包
	IF2Packer *lpMsgPack = m_lpContext->GetF2PackSvr()->GetPacker(2);
	lpMsgPack->BeginPack();
	lpMsgPack->AddField("table_name", 'S', 128);
	lpMsgPack->AddField("update_type", 'I');
	lpMsgPack->AddField("comm_dataset", 'R', lpDelRecPack->GetPackLen());
	
	lpMsgPack->AddStr(m_szTableName.c_str());
	lpMsgPack->AddInt((int)REFRESH_TYPE_DELETE);
	lpMsgPack->AddRaw(lpDelRecPack->GetPackBuf(), lpDelRecPack->GetPackLen());
	lpMsgPack->EndPack();
	
	bool bRet = Publish(m_lpContext, lpMsgPack);
	if(false == bRet)
	{
		DLOGERROR(m_lpContext, -100,"日间删除的更新主题发布失败");
		return false;
	}
	DLOGEVENT(m_lpContext, "日间删除的更新主题发布成功");
	return true;
}
	
bool CRjMsg::Publish(IAS2Context* lpContext, IF2Packer* lpPack)
{
	// 发布主题
	
	
	IF2Packer *lpOutPacker = lpContext->GetF2PackSvr()->GetPacker(2);
	lpOutPacker->BeginPack();
	int iReturnCode = F3615222(lpContext, lpPack->UnPack(), lpOutPacker, NULL);
	lpOutPacker->EndPack();
  
  // 
  IF2UnPacker *lpOutUnPacker = lpOutPacker->UnPack();
  if (iReturnCode != 0)
  {
  	DLOGERROR(m_lpContext, -1, "发布主题错误,错误号["<< lpOutUnPacker->GetInt("error_no") << "]错误信息["<< lpOutUnPacker->GetInt("error_info") << "]");
  	return false;
  }  
  return true;
}

bool CRjMsg::PublishUpdateMsg(string szTimePrev, string szTimeAft)
{
        //由于封板，费用这几个表暂时不判断时间戳，代码结构后面重新考虑
	if(("jc_tassetcaptacct" != m_szTableName && "jc_tfeeqh" != m_szTableName && "jc_tfeehs" != m_szTableName && "uft_tautoriskpermission" != m_szTableName) && (szTimePrev == szTimeAft))
	{
            DLOGEVENT(m_lpContext,"检测到表[" << m_szTableName <<"]同步前后的最后更新时间相同，所以不发布O4同步主题");
            return true;
	}
	
	// 发布主题
	
	// 打消息包
	IF2Packer *lpMsgPack = m_lpContext->GetF2PackSvr()->GetPacker(2);
	lpMsgPack->BeginPack();
	lpMsgPack->AddField("table_name", 'S', 128);
	lpMsgPack->AddField("update_type", 'I');
	
	lpMsgPack->AddStr(m_szTableName.c_str());
	lpMsgPack->AddInt((int)REFRESH_TYPE_UPDATE);
	lpMsgPack->EndPack();
    
	bool bRet =  Publish(m_lpContext, lpMsgPack);
	if(false == bRet)
	{
	DLOGERROR(m_lpContext,-100,"日间更新的更新主题发布失败");
		return false;
	}
	DLOGEVENT(m_lpContext,"日间更新的更新主题发布成功");
	return true;
}

bool CRjMsg::SyncRj()
{
	//---------------------
	// 获取存储过程名
	string szProcName = GetProcName();
	if("" == szProcName)
	{
		DLOGERROR(m_lpContext,-100, "获取表["<< m_szTableName.c_str() <<"]存储过程为空,跳过更新");
		return false;
	}
	DLOGEVENT(m_lpContext,"获取到表["<< m_szTableName.c_str() <<"]存储过程名[" << szProcName.c_str() << "]");
	
	//------------------------
	// 获取当前的最后更新时间，用于跟存储过程执行后的最后更新时间作比较,
	//	如果不变，则不推送日间变更更新消息(非删除消息)
	string szTimePrev = GetCurrUpdateTimeStamp();
	if("" == szTimePrev)
	{
		DLOGERROR(m_lpContext,-100, "获取表["<< m_szTableName.c_str() <<"]日间同步前的最后更新时间失败,跳过更新");
		return false;
	}
	DLOGEVENT(m_lpContext, "获取到表["<< m_szTableName.c_str() <<"]日间同步前的最后更新时间[" << szTimePrev.c_str() << "]");
	
	//-----------------
	// 执行存储过程
	IF2Packer *lpDelRecPack = m_lpContext->GetF2PackSvr()->GetPacker(2);
	if (NULL == lpDelRecPack)
	{
		DLOGERROR(m_lpContext, -100, "申请待存放待删除数据的PACK包失败,表["<< m_szTableName.c_str() <<"]日间处理失败");
		return false;
	}
	
	bool bRet = CallProcedure(szProcName, lpDelRecPack);
	if(false == bRet)
	{
		DLOGERROR(m_lpContext, -100, "执行存储过程["<< szProcName.c_str() << "]失败,表["<< m_szTableName.c_str() <<"]日间处理失败");
		if (lpDelRecPack)
		{
			free(lpDelRecPack->GetPackBuf());
			lpDelRecPack->Release();
		}
		return false;
	}

	//----------------------
	// 获取存储过程执行后最后更新时间
	string szAfterPrev = GetCurrUpdateTimeStamp();
	if("" == szAfterPrev)
	{
		DLOGERROR(m_lpContext, -100, "获取表["<< m_szTableName.c_str() <<"]日间同步后的最后更新时间失败,跳过更新");
		if (lpDelRecPack)
		{
			free(lpDelRecPack->GetPackBuf());
			lpDelRecPack->Release();
		}
		return false;
	}
	DLOGEVENT(m_lpContext, "获取到表["<< m_szTableName.c_str() <<"]日间同步后的最后更新时间[" << szAfterPrev.c_str() << "]");
	
	//-------------------------
	// 发布主题
	bRet = PublishTopic(szTimePrev, szAfterPrev, lpDelRecPack);
	if(false == bRet)
	{
		DLOGERROR(m_lpContext, -100, "推送表["<< m_szTableName.c_str() << "]消息主题失败");
		if (lpDelRecPack)
		{
			free(lpDelRecPack->GetPackBuf());
			lpDelRecPack->Release();
		}
		return false;
	}

	if (lpDelRecPack)
	{
		free(lpDelRecPack->GetPackBuf());
		lpDelRecPack->Release();
	}
	return true;
}
IAS2Context *CRjMsg::GetContext()
{
	return m_lpContext;
}
string CRjMsg::GetTableName()
{
	return m_szTableName;
}


IConnection* CRjMsg::GetO3DBConn()
{
	IConnection* lpConn = m_lpContext->GetDBConnection(O3DB);
	if(NULL == lpConn)
	{
		DLOGERROR(m_lpContext, -100, "获取O32数据库连接失败");
		return NULL;	
	}
	
	return lpConn;
}

//多结果集日间删除消息
bool CRjMsg::PublishRjMultiDataSetTopic(IF2Packer* lpDelRecPack, IF2Packer* lpDelRecPack1, string tableName)
{
	IF2UnPacker* unPack = lpDelRecPack->UnPack();
	IF2UnPacker* unPack1 = lpDelRecPack1->UnPack();

	if( (0 == unPack->GetRowCount()) && (0 == unPack1->GetRowCount()) )
	{
		DLOGEVENT(m_lpContext, "没有需要删除的记录,退出发布删除主题");
		return true;
	}
	DLOGEVENT(m_lpContext, "开始发布日间删除消息，主表["<<tableName.c_str()<<"];明细表["<<m_szTableName.c_str()<<"]");

	//打多结果集包
	IF2Packer *lpFuncInPacker = m_lpContext->GetF2PackSvr()->GetPacker(2);
    lpFuncInPacker->BeginPack();
	lpFuncInPacker->AddField("update_type", 'I');
	lpFuncInPacker->AddField("comm_dataset1", 'R', lpDelRecPack->GetPackLen());
	lpFuncInPacker->AddField("comm_dataset2", 'R', lpDelRecPack1->GetPackLen());
	lpFuncInPacker->AddField("table_name", 'S', 128);
	lpFuncInPacker->AddField("vc_table_name_o4", 'S', 128);
	lpFuncInPacker->AddInt(3);
	lpFuncInPacker->AddRaw(lpDelRecPack->GetPackBuf(), lpDelRecPack->GetPackLen());
	lpFuncInPacker->AddRaw(lpDelRecPack1->GetPackBuf(), lpDelRecPack1->GetPackLen());
	lpFuncInPacker->AddStr(tableName.c_str());
	lpFuncInPacker->AddStr(m_szTableName.c_str());
    lpFuncInPacker->EndPack();
	//发送多结果集日间消息
	IF2Packer *lpFuncOutPacker = m_lpContext->GetF2PackSvr()->GetPacker(2);
    IF2UnPacker *lpOutUnPacker = NULL;
    lpFuncOutPacker->BeginPack();
	int iReturnCode = F3615219(m_lpContext, lpFuncInPacker->UnPack(), lpFuncOutPacker, NULL);
    lpFuncOutPacker->EndPack();
    lpOutUnPacker = lpFuncOutPacker->UnPack();
    if (iReturnCode != 0 && iReturnCode != ERR_SYSWARNING)
    {
    	DLOGERROR(m_lpContext, 100, "发布日间删除消息失败，主表["<<tableName.c_str()<<"];明细表["<<m_szTableName.c_str()<<"]，调用F3615219返回出错["<<lpOutUnPacker->GetStr("error_info")<<"]");
        if (lpFuncInPacker)
        {
            free(lpFuncInPacker->GetPackBuf());
            lpFuncInPacker->Release();
        }
        if (lpFuncOutPacker)
        {
            free(lpFuncOutPacker->GetPackBuf());
            lpFuncOutPacker->Release();
        }
        return false;
    }

    if (lpFuncInPacker)
    {
        free(lpFuncInPacker->GetPackBuf());
        lpFuncInPacker->Release();
    }
    if (lpFuncOutPacker)
    {
        free(lpFuncOutPacker->GetPackBuf());
        lpFuncOutPacker->Release();
    }

    DLOGEVENT(m_lpContext, "发布日间删除消息成功，主表["<<tableName.c_str()<<"]删除记录["<<unPack->GetRowCount()<<"]条;明细表["<<m_szTableName.c_str()<<"]删除记录["<<unPack1->GetRowCount()<<"]条");
	return true;
}
