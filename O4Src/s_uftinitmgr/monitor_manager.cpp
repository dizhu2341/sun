#include "monitor_manager.h"
#include "monitor_thread.h"

CMonitorManager::CMonitorManager(IAS2Context * lpContext, ICommAgent* lpCommAgent, IF2UnPacker * lpInUnPacker, IF2Packer * lpOutPacker)
{
		m_lpContext = lpContext;
		m_lpCommAgent = lpCommAgent;
		m_lpInUnPacker = lpInUnPacker;
		m_lpOutPacker = lpOutPacker;
		strcpy(error_pathinfo, "F615010()");
		m_nErrNo = 0;
		strcpy(m_sErrInfo, "");
}

CMonitorManager::~CMonitorManager()
{
	m_lpContext = NULL;
	m_lpCommAgent = NULL;
	m_lpInUnPacker = NULL;
	m_lpOutPacker = NULL;
}

int CMonitorManager::GetErrNo()
{
	return m_nErrNo;
}

char* CMonitorManager::GetErrInfo()
{
	return m_sErrInfo;						/*lint !e1536*/
}

void CMonitorManager::SetErrInfo(int errNo, const char* pErrInfo)
{
	m_nErrNo = errNo;
	strcpy(m_sErrInfo, pErrInfo);
}

bool CMonitorManager::CallMonitorService()
{
	if (!CheckTradeCenterInit())
	{
		return false;
	}
	
	if (!ResetTradeCenterFlag())
	{
		SetErrInfo(-101, "重置交易中心初始化状态失败");
		return false;
	}
	
	if (!GetTradeCenterList())
	{
		SetErrInfo(-102, "获取交易中心信息失败");
		return false;
	}
	
	//----------------------------------------------------------------
	//多线程执行调用服务
	TRADELIST::iterator tradeIter = m_lstTrd.begin();
	for (; tradeIter != m_lstTrd.end(); tradeIter++)
	{
		CMonitorAgent* lpMntrAgt = new CMonitorAgent();
		lpMntrAgt->Execute((void *)(*tradeIter));
		m_lstMntr.push_back(lpMntrAgt);
	}													/*lint !e429*/
	
	//---------------------------------------------------------------
	//获取各个线程结束状态
	unsigned int successCount 				= 0;
	unsigned int failCount 					= 0;
	bool isUfmOk = true;
	int ufmErrNo = -10000000;
	char ufmErrInfo[5000] = {0};
	char tmpErrInfo[5000] = {0};
	char errInfo[5000] = {0};
	for (MNTRLIST::iterator mntrIter = m_lstMntr.begin(); mntrIter != m_lstMntr.end(); mntrIter++)
	{
		CMonitorAgent* lpMntrAgt = (*mntrIter);
		CTradeCenter*  lpTrdCnt = (CTradeCenter*)lpMntrAgt->GetThreadData();
		bool isExecOk = lpMntrAgt->WaitForTid();
		
		// 如果是ufm(子系统号为35),则特殊处理
		if (35 == lpTrdCnt->GetTradeID())
		{
			ufmErrNo = lpMntrAgt->GetErrNo();
			strcpy (ufmErrInfo, lpMntrAgt->GetErrInfo());
			isUfmOk = isExecOk;
		}
		else if (!isExecOk)
		{
			sprintf(tmpErrInfo, "核心[%d]日初失败,ErrNo[%d]ErrInfo[%s];", lpTrdCnt->GetTradeID(), lpMntrAgt->GetErrNo(), lpMntrAgt->GetErrInfo());
			DLOGWARNING(m_lpContext, tmpErrInfo);
			strcat(errInfo, tmpErrInfo);
			failCount++;
		}
		else								//若返回成功，则设置初始化标记为已初始化
		{
			sprintf(tmpErrInfo, "核心[%d]日初成功;", lpTrdCnt->GetTradeID());
			DLOGWARNING(m_lpContext, tmpErrInfo);
			strcat(errInfo, tmpErrInfo);
			successCount++;
			UpdateInitFlag(lpTrdCnt);
		}
		
		delete lpMntrAgt;
	}

	if (successCount > 0 &&  failCount > 0)    // 部分成功
	{
		if (false == isUfmOk)
		{
			sprintf(tmpErrInfo, "UFT部分初始化成功,UFM初始化失败:%s;UFM日初失败ErrNo[%d]ErrInfo[%s]", errInfo, ufmErrNo, ufmErrInfo);
			SetErrInfo(615011,  tmpErrInfo);
		}
		else if (ufmErrNo == 0)
		{
			sprintf(tmpErrInfo, "UFT部分初始化成功,UFM初始化成功:%s", errInfo);
			//SetErrInfo(0,  tmpErrInfo);
            SetErrInfo(-100,  tmpErrInfo);
		}
		else
		{
			sprintf(tmpErrInfo, "UFT部分初始化成功: %s", errInfo);
			//SetErrInfo(0,  tmpErrInfo);
			SetErrInfo(-100,  tmpErrInfo);
		}	
	}
	else if (successCount > 0 &&  failCount == 0) // 全部成功
	{
		if (false == isUfmOk)
		{
			sprintf(tmpErrInfo, "UFT初始化成功,UFM初始化失败:UFM日初失败ErrNo[%d]ErrInfo[%s]", ufmErrNo, ufmErrInfo);
			SetErrInfo(615011,  tmpErrInfo);
		}
		else if (ufmErrNo == 0)
		{
			strcat(tmpErrInfo, "UFT和UFM初始化成功.");
			SetErrInfo(0,  tmpErrInfo);
		}
		else
		{
			strcat(tmpErrInfo, "UFT初始化成功.");
			SetErrInfo(0,  tmpErrInfo);
		}	

		if (false == isUfmOk) 
		{
			sprintf(tmpErrInfo, "UFT初始化成功,但是UFM初始化失败,ErrNo[%d]ErrInfo[%s]！请单独重新初始化UFM！", ufmErrNo, ufmErrInfo);
			SetErrInfo(615011, tmpErrInfo);
		}
		else
			SetErrInfo(0, "UFT初始化成功!");
	}
	else                                          // 全部失败
	{
		if (false == isUfmOk)
		{
			sprintf(tmpErrInfo, "UFT和UFM全部初始化失败:%s;UFM日初失败ErrNo[%d]ErrInfo[%s]", errInfo, ufmErrNo, ufmErrInfo);
			SetErrInfo(-100,  tmpErrInfo);
		}
		else if (ufmErrNo == 0)
		{
			sprintf(tmpErrInfo, "UFT初始化失败,UFM初始化成功:%s",  errInfo);
			SetErrInfo(-100,  tmpErrInfo);
		}
		else
		{
			sprintf(tmpErrInfo, "UFT初始化失败:%s",  errInfo);
			SetErrInfo(-100,  tmpErrInfo);
		}	
	}
	
	return true;
}

bool CMonitorManager::GetUFMStatus()
{	
    int funcId = 2617006;
    int iRet = 0;
    IF2PackSvr * lpPackService = m_lpContext->GetF2PackSvr();
    IF2Packer * lpFuncInPacker = lpPackService->GetPacker(2);
    IF2Packer * lpFuncOutPacker = lpPackService->GetPacker(2);
    IF2UnPacker * lpResultSet = NULL;
    int branch_no = m_lpInUnPacker->GetInt("branch_no");

    //--------------------------------------------------
    //判断基础子系统是否启用
    // 准备异步信息
    int subsys_id = 36;
    int sysnode_id = 0;

    //调用2617006查询系统参数值61263是否开启，若开启增加线程增加功能号
    lpFuncInPacker->BeginPack();
    lpFuncInPacker->AddField("sysparam_no",'I');
    lpFuncInPacker->AddField("error_pathinfo",'S',4000);
    lpFuncInPacker->AddInt(61263); 
    lpFuncInPacker->AddStr(error_pathinfo);
    lpFuncInPacker->EndPack();

    //将打包结果转为参数解包器供函数使用
    lpFuncOutPacker->BeginPack();
    iRet = SubServiceCall(m_lpContext,lpFuncInPacker->UnPack(),lpFuncOutPacker,5000,funcId,branch_no,sysnode_id,subsys_id);
    lpFuncOutPacker->EndPack();
    lpResultSet = lpFuncOutPacker->UnPack(); //结果解包

    if (0 != iRet)
    {
        DLOGERROR(m_lpContext,iRet, "调用功能号"<<funcId<<"失败，错误信息："<<lpResultSet->GetStr("error_info"));
        SetErrInfo(iRet, lpResultSet->GetStr("error_info"));	
        if (lpResultSet->GetStr("error_pathinfo") == NULL)
            hs_strncat(error_pathinfo,"->2617006",4000);
        else
            hs_strncpy(error_pathinfo, lpResultSet->GetStr("error_pathinfo"), 4000);

        return false;
    }
    int nUFMStatus = atoi(lpResultSet->GetStr("param_value"));

    if (lpResultSet)
    {
        lpResultSet->Release();
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

    return nUFMStatus;
}

bool CMonitorManager::GetTradeCenterList()
{
	DLOGEVENT(m_lpContext,"开始查询交易中心列表");
	int iRet = 0;
	int funcId = 2617002;
	int nTradeId = 0;
	int nInitDate = 0;
    IF2PackSvr * lpPackService = m_lpContext->GetF2PackSvr();
    IF2Packer * lpFuncInPacker = lpPackService->GetPacker(2);
	IF2Packer * lpFuncOutPacker = lpPackService->GetPacker(2);
    IF2UnPacker * lpResultSet = NULL;
	int branch_no = m_lpInUnPacker->GetInt("branch_no");
	nInitDate = m_lpInUnPacker->GetInt("init_date");
	
	//--------------------------------------------------
	//判断基础子系统是否启用
	int subsys_no = 999;
	// 准备异步信息
	int subsys_id = 36;
	int sysnode_id = 0;

	//调用AS_公共_子系统是否启用
	lpFuncInPacker->BeginPack();
	lpFuncInPacker->AddField("subsys_no",'I');
	lpFuncInPacker->AddField("error_pathinfo",'S',4000);
	lpFuncInPacker->AddInt(subsys_no); //subsys_no
	lpFuncInPacker->AddStr(error_pathinfo);
	lpFuncInPacker->EndPack();

	//将打包结果转为参数解包器供函数使用
	lpFuncOutPacker->BeginPack();
	iRet = SubServiceCall(m_lpContext,lpFuncInPacker->UnPack(),lpFuncOutPacker,5000,funcId,branch_no,sysnode_id,subsys_id);
	lpFuncOutPacker->EndPack();
	lpResultSet = lpFuncOutPacker->UnPack(); //结果解包
	
	if (0 != iRet)
	{
		DLOGERROR(m_lpContext,iRet, "调用功能号"<<funcId<<"失败，错误信息："<<lpResultSet->GetStr("error_info"));
		SetErrInfo(iRet, lpResultSet->GetStr("error_info"));

		if (lpResultSet->GetStr("error_pathinfo") == NULL)
			hs_strncat(error_pathinfo,"->2617002", 4000);
		else
			hs_strncpy(error_pathinfo, lpResultSet->GetStr("error_pathinfo"), 4000);
		
		return false;
	}
	
	while ( !lpResultSet->IsEOF() )
	{
		nTradeId = lpResultSet->GetInt("center_id");
        if (lpResultSet->GetChar("use_flag") == '1')
        {
            m_lstTrd.push_back(new CTradeCenter(m_lpContext, m_lpCommAgent, nTradeId, nInitDate));
        }
		lpResultSet->Next();
	}

	DLOGEVENT(m_lpContext,"查询到"<<m_lstTrd.size()<<"个交易中心");
	
	if (lpResultSet)
	{
		lpResultSet->Release();
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
	
	//判断是否需要将数据同步至UFM节点
	bool UFMStatus =GetUFMStatus();
	if(UFMStatus)
	{
		//UFM子系统号为35,对应初始化的功能号为460011
		m_lstTrd.push_back(new CTradeCenter(m_lpContext, m_lpCommAgent, 35, nInitDate,460011));
		DLOGDEBUG(m_lpContext, "UFM节点加入交易中心列表");
        return true;
	}
	
	return true;
}

bool CMonitorManager::ResetTradeCenterFlag()
{
	DLOGEVENT(m_lpContext,"开始重置交易中心初始化状态");
	
	int iRet = 0;
	int funcId = 2617003;
    IF2PackSvr * lpPackService = m_lpContext->GetF2PackSvr();
    IF2Packer * lpFuncInPacker = lpPackService->GetPacker(2);
	IF2Packer * lpFuncOutPacker = lpPackService->GetPacker(2);
    IF2UnPacker * lpResultSet = NULL;
	int branch_no = m_lpInUnPacker->GetInt("branch_no");
	
	//--------------------------------------------------
	//判断基础子系统是否启用
	int subsys_no = 999;
	// 准备异步信息
	int subsys_id = 36;
	int sysnode_id = 0;

	//调用AS_公共_子系统是否启用
	lpFuncInPacker->BeginPack();
	lpFuncInPacker->AddField("subsys_no",'I');
	lpFuncInPacker->AddField("error_pathinfo",'S',4000);
	lpFuncInPacker->AddInt(subsys_no); //subsys_no
	lpFuncInPacker->AddStr(error_pathinfo);
	lpFuncInPacker->EndPack();

	//将打包结果转为参数解包器供函数使用
	lpFuncOutPacker->BeginPack();
	iRet = SubServiceCall(m_lpContext,lpFuncInPacker->UnPack(),lpFuncOutPacker,5000,funcId,branch_no,sysnode_id,subsys_id);
	lpFuncOutPacker->EndPack();
	lpResultSet = lpFuncOutPacker->UnPack(); //结果解包
	
	if (0 != iRet)
	{
		DLOGERROR(m_lpContext,iRet, "调用功能号"<<funcId<<"失败，错误信息："<<lpResultSet->GetStr("error_info"));
		SetErrInfo(iRet, lpResultSet->GetStr("error_info"));

		if (lpResultSet->GetStr("error_pathinfo") == NULL)
			hs_strncat(error_pathinfo,"->2617003", 4000);
		else
			hs_strncpy(error_pathinfo, lpResultSet->GetStr("error_pathinfo"), 4000);
		
		return false;
	}
	
	if (lpResultSet)
	{
		lpResultSet->Release();
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
	
	DLOGEVENT(m_lpContext,"重置交易中心初始化状态完成");
    return true;
}

bool CMonitorManager::UpdateInitFlag(CTradeCenter* lpTrdCnt)
{
	int iRet = 0;
	int funcId = 2617004;
    IF2PackSvr * lpPackService = m_lpContext->GetF2PackSvr();
    IF2Packer * lpFuncInPacker = lpPackService->GetPacker(2);
	IF2Packer * lpFuncOutPacker = lpPackService->GetPacker(2);
    IF2UnPacker * lpResultSet = NULL;
	int branch_no = m_lpInUnPacker->GetInt("branch_no");
	
	int nTradeID = lpTrdCnt->GetTradeID();
	char sInitFlag = lpTrdCnt->GetInitFlag();
	
	DLOGEVENT(m_lpContext,"开始设置交易中心["<<nTradeID<<"]的初始化状态["<<sInitFlag<<"]");
	
	//--------------------------------------------------
	// 准备异步信息
	int subsys_id = 36;
	int sysnode_id = 0;

	//调用AS_公共_子系统是否启用
	lpFuncInPacker->BeginPack();
	lpFuncInPacker->AddField("error_pathinfo",'S',4000);
	lpFuncInPacker->AddField("center_id",'I');
	lpFuncInPacker->AddField("init_flag",'C');
	lpFuncInPacker->AddStr(error_pathinfo);
	lpFuncInPacker->AddInt(nTradeID);
	lpFuncInPacker->AddChar(sInitFlag);
	lpFuncInPacker->EndPack();

	//将打包结果转为参数解包器供函数使用
	lpFuncOutPacker->BeginPack();
	iRet = SubServiceCall(m_lpContext,lpFuncInPacker->UnPack(),lpFuncOutPacker,5000,funcId,branch_no,sysnode_id,subsys_id);
	lpFuncOutPacker->EndPack();
	lpResultSet = lpFuncOutPacker->UnPack(); //结果解包
	
	if (0 != iRet)
	{
		DLOGERROR(m_lpContext,iRet, "调用功能号"<<funcId<<"失败，错误信息："<<lpResultSet->GetStr("error_info"));
		SetErrInfo(iRet, lpResultSet->GetStr("error_info"));

		if (lpResultSet->GetStr("error_pathinfo") == NULL)
			hs_strncat(error_pathinfo,"->2617004", 4000);
		else
			hs_strncpy(error_pathinfo, lpResultSet->GetStr("error_pathinfo"), 4000);
		
		return false;
	}
	
	if (lpResultSet)
	{
		lpResultSet->Release();
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
	
	DLOGEVENT(m_lpContext,"交易中心["<<nTradeID<<"]的初始化状态设置完成");
	
    return true;
}

bool CMonitorManager::CheckTradeCenterInit()
{
	DLOGEVENT(m_lpContext,"开始交易中心初始化业务校验");
	
	int iRet = 0;
	int funcId = 2616211;
    IF2PackSvr * lpPackService = m_lpContext->GetF2PackSvr();
    IF2Packer * lpFuncInPacker = lpPackService->GetPacker(2);
	IF2Packer * lpFuncOutPacker = lpPackService->GetPacker(2);
    IF2UnPacker * lpResultSet = NULL;
	int branch_no = m_lpInUnPacker->GetInt("branch_no");
	
	//--------------------------------------------------
	// 准备异步信息
	int subsys_id = 36;
	int sysnode_id = 0;

	//调用AS_公共_子系统是否启用
	lpFuncInPacker->BeginPack();
	lpFuncInPacker->AddField("error_pathinfo",'S',4000);
	lpFuncInPacker->AddStr(error_pathinfo);
	lpFuncInPacker->EndPack();

	//将打包结果转为参数解包器供函数使用
	lpFuncOutPacker->BeginPack();
	iRet = SubServiceCall(m_lpContext,lpFuncInPacker->UnPack(),lpFuncOutPacker,5000,funcId,branch_no,sysnode_id,subsys_id);
	lpFuncOutPacker->EndPack();
	lpResultSet = lpFuncOutPacker->UnPack(); //结果解包
	
	if (0 != iRet)
	{
		DLOGERROR(m_lpContext,iRet, "调用功能号"<<funcId<<"报错，错误信息："<<lpResultSet->GetStr("error_info"));
		SetErrInfo(iRet, lpResultSet->GetStr("error_info"));

		if (lpResultSet->GetStr("error_pathinfo") == NULL)
			hs_strncat(error_pathinfo,"->2615404", 4000);
		else
			hs_strncpy(error_pathinfo, lpResultSet->GetStr("error_pathinfo"), 4000);
		
		return false;
	}
	
	if (lpResultSet)
	{
		lpResultSet->Release();
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
	
	DLOGEVENT(m_lpContext,"交易中心初始化业务校验完成");
	
    return true;
}
