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
		DLOGERROR(m_lpContext, -100, "��ȡ���ݿ�����Ϊ��,��ȡ�洢������ʧ��");
		return "";
	}
	
	IF2ResultSet* lpResultSet = lpConn->executeQuery(sSql);
	if (NULL == lpResultSet)
	{
		DLOGERROR(m_lpContext, -1, "��ѯ�洢��["<< m_szTableName.c_str() <<"]���ռ�洢����ʧ��,������Ϣ[" << lpConn->getErrInfo() << "]");
		lpConn->toFree();
		return "";
	}
	if(lpResultSet->IsEmpty())
	{
		DLOGWARNING(m_lpContext, "��ѯ�洢��["<< m_szTableName.c_str() <<"]���ռ�洢����Ϊ��,����û��֧�ָ��ռ����");
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
	// ����
	//CMutexMgr::GetInstance()->GetLock(m_szTableName.c_str());
	lpDelRecPack->BeginPack();
	
	//�����������޸ĺ�ɾ�����ڴ洢��������ɣ�ɾ������ͨ�����������
	char sSql[100] = {0};
	sprintf(sSql, "call %s(?)", szProcName.c_str());
	
	IConnection* lpConn = GetO3DBConn();
	if(NULL == lpConn)
	{
		DLOGERROR(m_lpContext, -100, "��ȡ���ݿ�����Ϊ��,���ô洢������["<< szProcName.c_str() <<"]ʧ��");
		return "";
	}
	
	ICallableStatement *lpCall = lpConn->createCallableStatement();
	lpCall->prepare(sSql);
	lpCall->setInt(1, 2);// ��һ���������ֵ2����ʾ�����ռ���£���call sp_o4sync_asset(2)
	IF2ResultSet *lpResultSet = lpCall->open();
	// ����ɾ�������ݴ����ȥ
	if(NULL == lpResultSet)  // ���ִ�г���
	{
		DLOGERROR(m_lpContext, -1, "ִ�д洢����["<< szProcName.c_str()  <<"]�쳣,������Ϣ[" << lpConn->getErrInfo() << "]");
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
	// �ͷ���
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
		DLOGERROR(m_lpContext, -100, "��ȡ���ݿ�����Ϊ��,��ȡ������ʱ���ʧ��");
		return "";
	}
	
	IF2ResultSet *lpResultSet = lpConn->executeQuery(sSql);
	if (NULL == lpResultSet)
	{
		DLOGERROR(m_lpContext, -1, "��ѯ��["<< m_szTableName.c_str() <<"]��������ʱ��ʧ��,������Ϣ[" << lpConn->getErrInfo() << "]");
		lpConn->toFree();
		return "";
	}
	if(lpResultSet->IsEmpty())
	{
		DLOGWARNING(m_lpContext, "��ѯ��["<< m_szTableName.c_str() <<"]��������ʱ��Ϊ��,����0����");
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

	// ���������jc_tfeeqh��jc_tfeehs��uft_tautoriskpermission����Ҫɾ�����Ե���ϸ������ݣ�����������
	if ("jc_tfeeqh" == m_szTableName || "jc_tfeehs" == m_szTableName || "uft_tautoriskpermission" == m_szTableName)
	{
		// �Ȱ�ԭ���ı������浽��ʱ������
		string tempTable = m_szTableName;

		// ����ϸ����m_szTableName
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
		// ��ȡ�洢������
		string szProcName = GetProcName();
		if("" == szProcName)
		{
			DLOGERROR(m_lpContext,-100, "��ȡ��["<< m_szTableName.c_str() <<"]�洢����Ϊ��,��������");
			return false;
		}
		DLOGEVENT(m_lpContext,"��ȡ����["<< m_szTableName.c_str() <<"]�洢������[" << szProcName.c_str() << "]");
		// ִ�д洢����
		IF2Packer *lpDelRecPack1 = m_lpContext->GetF2PackSvr()->GetPacker(2);
		if (NULL == lpDelRecPack1)
		{
			DLOGERROR(m_lpContext, -100, "�������Ŵ�ɾ�����ݵ�PACK��ʧ��,��["<< m_szTableName.c_str() <<"]�ռ䴦��ʧ��");
			return false;
		}
		bool bRet = CallProcedure(szProcName, lpDelRecPack1);
		if(false == bRet)
		{
			DLOGERROR(m_lpContext, -100, "ִ�д洢����["<< szProcName.c_str() << "]ʧ��,��["<< m_szTableName.c_str() <<"]�ռ䴦��ʧ��");
			if (lpDelRecPack1)
			{
				free(lpDelRecPack1->GetPackBuf());
				lpDelRecPack1->Release();
			}
			return false;
		}


		//���������ϸ�������Ҫɾ�������ݣ���ô�͵÷��Ͷ������ռ�ɾ����Ϣ
		bRet = PublishRjMultiDataSetTopic(lpDelRecPack, lpDelRecPack1, tempTable);
		if(false == bRet)
		{
			DLOGERROR(m_lpContext, -100, "���ͱ�["<< tempTable.c_str() << "|" << m_szTableName.c_str() << "]��Ϣ����ʧ��");
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
		// ����ɾ��������
		if (false == PublishDelMsg(lpDelRecPack))
			return false;
	}

	//-------------------------
	// �������µ�����

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
		DLOGEVENT(m_lpContext, "û����Ҫɾ���ļ�¼,�˳�����ɾ������");
		return true;
	}
		
	// ��������
	
	// ����Ϣ��
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
		DLOGERROR(m_lpContext, -100,"�ռ�ɾ���ĸ������ⷢ��ʧ��");
		return false;
	}
	DLOGEVENT(m_lpContext, "�ռ�ɾ���ĸ������ⷢ���ɹ�");
	return true;
}
	
bool CRjMsg::Publish(IAS2Context* lpContext, IF2Packer* lpPack)
{
	// ��������
	
	
	IF2Packer *lpOutPacker = lpContext->GetF2PackSvr()->GetPacker(2);
	lpOutPacker->BeginPack();
	int iReturnCode = F3615222(lpContext, lpPack->UnPack(), lpOutPacker, NULL);
	lpOutPacker->EndPack();
  
  // 
  IF2UnPacker *lpOutUnPacker = lpOutPacker->UnPack();
  if (iReturnCode != 0)
  {
  	DLOGERROR(m_lpContext, -1, "�����������,�����["<< lpOutUnPacker->GetInt("error_no") << "]������Ϣ["<< lpOutUnPacker->GetInt("error_info") << "]");
  	return false;
  }  
  return true;
}

bool CRjMsg::PublishUpdateMsg(string szTimePrev, string szTimeAft)
{
        //���ڷ�壬�����⼸������ʱ���ж�ʱ���������ṹ�������¿���
	if(("jc_tassetcaptacct" != m_szTableName && "jc_tfeeqh" != m_szTableName && "jc_tfeehs" != m_szTableName && "uft_tautoriskpermission" != m_szTableName) && (szTimePrev == szTimeAft))
	{
            DLOGEVENT(m_lpContext,"��⵽��[" << m_szTableName <<"]ͬ��ǰ���������ʱ����ͬ�����Բ�����O4ͬ������");
            return true;
	}
	
	// ��������
	
	// ����Ϣ��
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
	DLOGERROR(m_lpContext,-100,"�ռ���µĸ������ⷢ��ʧ��");
		return false;
	}
	DLOGEVENT(m_lpContext,"�ռ���µĸ������ⷢ���ɹ�");
	return true;
}

bool CRjMsg::SyncRj()
{
	//---------------------
	// ��ȡ�洢������
	string szProcName = GetProcName();
	if("" == szProcName)
	{
		DLOGERROR(m_lpContext,-100, "��ȡ��["<< m_szTableName.c_str() <<"]�洢����Ϊ��,��������");
		return false;
	}
	DLOGEVENT(m_lpContext,"��ȡ����["<< m_szTableName.c_str() <<"]�洢������[" << szProcName.c_str() << "]");
	
	//------------------------
	// ��ȡ��ǰ��������ʱ�䣬���ڸ��洢����ִ�к��������ʱ�����Ƚ�,
	//	������䣬�������ռ���������Ϣ(��ɾ����Ϣ)
	string szTimePrev = GetCurrUpdateTimeStamp();
	if("" == szTimePrev)
	{
		DLOGERROR(m_lpContext,-100, "��ȡ��["<< m_szTableName.c_str() <<"]�ռ�ͬ��ǰ��������ʱ��ʧ��,��������");
		return false;
	}
	DLOGEVENT(m_lpContext, "��ȡ����["<< m_szTableName.c_str() <<"]�ռ�ͬ��ǰ��������ʱ��[" << szTimePrev.c_str() << "]");
	
	//-----------------
	// ִ�д洢����
	IF2Packer *lpDelRecPack = m_lpContext->GetF2PackSvr()->GetPacker(2);
	if (NULL == lpDelRecPack)
	{
		DLOGERROR(m_lpContext, -100, "�������Ŵ�ɾ�����ݵ�PACK��ʧ��,��["<< m_szTableName.c_str() <<"]�ռ䴦��ʧ��");
		return false;
	}
	
	bool bRet = CallProcedure(szProcName, lpDelRecPack);
	if(false == bRet)
	{
		DLOGERROR(m_lpContext, -100, "ִ�д洢����["<< szProcName.c_str() << "]ʧ��,��["<< m_szTableName.c_str() <<"]�ռ䴦��ʧ��");
		if (lpDelRecPack)
		{
			free(lpDelRecPack->GetPackBuf());
			lpDelRecPack->Release();
		}
		return false;
	}

	//----------------------
	// ��ȡ�洢����ִ�к�������ʱ��
	string szAfterPrev = GetCurrUpdateTimeStamp();
	if("" == szAfterPrev)
	{
		DLOGERROR(m_lpContext, -100, "��ȡ��["<< m_szTableName.c_str() <<"]�ռ�ͬ�����������ʱ��ʧ��,��������");
		if (lpDelRecPack)
		{
			free(lpDelRecPack->GetPackBuf());
			lpDelRecPack->Release();
		}
		return false;
	}
	DLOGEVENT(m_lpContext, "��ȡ����["<< m_szTableName.c_str() <<"]�ռ�ͬ�����������ʱ��[" << szAfterPrev.c_str() << "]");
	
	//-------------------------
	// ��������
	bRet = PublishTopic(szTimePrev, szAfterPrev, lpDelRecPack);
	if(false == bRet)
	{
		DLOGERROR(m_lpContext, -100, "���ͱ�["<< m_szTableName.c_str() << "]��Ϣ����ʧ��");
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
		DLOGERROR(m_lpContext, -100, "��ȡO32���ݿ�����ʧ��");
		return NULL;	
	}
	
	return lpConn;
}

//�������ռ�ɾ����Ϣ
bool CRjMsg::PublishRjMultiDataSetTopic(IF2Packer* lpDelRecPack, IF2Packer* lpDelRecPack1, string tableName)
{
	IF2UnPacker* unPack = lpDelRecPack->UnPack();
	IF2UnPacker* unPack1 = lpDelRecPack1->UnPack();

	if( (0 == unPack->GetRowCount()) && (0 == unPack1->GetRowCount()) )
	{
		DLOGEVENT(m_lpContext, "û����Ҫɾ���ļ�¼,�˳�����ɾ������");
		return true;
	}
	DLOGEVENT(m_lpContext, "��ʼ�����ռ�ɾ����Ϣ������["<<tableName.c_str()<<"];��ϸ��["<<m_szTableName.c_str()<<"]");

	//���������
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
	//���Ͷ������ռ���Ϣ
	IF2Packer *lpFuncOutPacker = m_lpContext->GetF2PackSvr()->GetPacker(2);
    IF2UnPacker *lpOutUnPacker = NULL;
    lpFuncOutPacker->BeginPack();
	int iReturnCode = F3615219(m_lpContext, lpFuncInPacker->UnPack(), lpFuncOutPacker, NULL);
    lpFuncOutPacker->EndPack();
    lpOutUnPacker = lpFuncOutPacker->UnPack();
    if (iReturnCode != 0 && iReturnCode != ERR_SYSWARNING)
    {
    	DLOGERROR(m_lpContext, 100, "�����ռ�ɾ����Ϣʧ�ܣ�����["<<tableName.c_str()<<"];��ϸ��["<<m_szTableName.c_str()<<"]������F3615219���س���["<<lpOutUnPacker->GetStr("error_info")<<"]");
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

    DLOGEVENT(m_lpContext, "�����ռ�ɾ����Ϣ�ɹ�������["<<tableName.c_str()<<"]ɾ����¼["<<unPack->GetRowCount()<<"]��;��ϸ��["<<m_szTableName.c_str()<<"]ɾ����¼["<<unPack1->GetRowCount()<<"]��");
	return true;
}
