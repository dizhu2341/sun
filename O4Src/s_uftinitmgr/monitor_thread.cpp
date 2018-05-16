#include "monitor_thread.h"


CMonitorThread::CMonitorThread(CMonitorAgent* lpMntrAgt)
{
	m_lpMntrAgt = lpMntrAgt;
}

CMonitorThread::~CMonitorThread()
{
	m_lpMntrAgt = NULL;
}

bool CMonitorThread::BeforeRun()
{
	//DLOGDEBUG(NULL, "Thread["<<(unsigned int)m_nTid<<"] Before Running...");
	return true;
}

bool CMonitorThread::Run()
{
	//DLOGDEBUG(NULL, "Thread["<<(unsigned int)m_nTid<<"] IsRunning...");
	return (0 == CallSvr()) ? true : false;
}

bool CMonitorThread::AfterRun()
{
//	DLOGDEBUG(NULL,"Thread["<<(unsigned int)m_nTid<<"]After_Running...");
	CTradeCenter* lpTrdCenter = (CTradeCenter *)GetThreadData();
	if (NULL == lpTrdCenter)
	{
	//	DLOGERROR(NULL,-110, "无法获取交易中心对象数据");
		SetErrInfo(-110, "无法获取交易中心对象数据");
		return false;
	}
	lpTrdCenter->SetInitFlag('1');
	return true;
}

void CMonitorThread::SetErrInfo(int error_no, const char* error_info)
{
	m_lpMntrAgt->SetErrInfo(error_no, error_info);
}

int CMonitorThread::CallSvr()
{
	// 获取线程运行所需参数
	CTradeCenter* lpTrdCenter = (CTradeCenter *)GetThreadData();
	if (NULL == lpTrdCenter)
	{
		//	DLOGERROR(NULL,-110, "无法获取交易中心对象数据");
		SetErrInfo(-110, "无法获取交易中心对象数据");
		return -110;
	}
	ICommAgent* lpCommAgent = lpTrdCenter->GetLpCommAgent();
	IAS2Context* lpContext = lpTrdCenter->GetLpContext();
	//int nFuncNo = 2615102;
	int nFuncNo = lpTrdCenter->GetFuncID();
	int nTimeOut = 600000;
	int nInitDate = lpTrdCenter->GetInitDate();
	int nTradeID = lpTrdCenter->GetTradeID();
	
	DLOGEVENT(lpContext,"发送异步请求功能号["<<nFuncNo<<"]，branch_no["<<nTradeID<<"]");
	
	// 打F2包
	IF2Packer* lpInPack = lpContext->GetF2PackSvr()->GetPacker(2);
	lpInPack->BeginPack();
	lpInPack->AddField("branch_no", 'I');
	lpInPack->AddField("init_date", 'I');
	lpInPack->AddInt(nTradeID);
	lpInPack->AddInt(nInitDate);
	lpInPack->EndPack();
	
	// 发送请求包
	int nHandle = AsynSend(lpContext, lpCommAgent, lpInPack, nFuncNo, nTradeID);
	
	// 释放入参打包器打包器内存
	if (lpInPack)
	{
		free(lpInPack->GetPackBuf());
		lpInPack->Release();
	}

	// 判断是否发送正常
	if (nHandle <= 0)
	{
		DLOGERROR(lpContext,-110, "初始化异步请求发送失败");
		SetErrInfo(-110, "初始化异步请求发送失败");
		return -110;
	}
	
	// 接收应答包
	IF2UnPacker* unPack = AsynRecv(lpContext, lpCommAgent, nHandle, nTimeOut, nTradeID);
	
	if (NULL == unPack)
	{
		return -112;
	}
	
	//解析应答包
	int error_no = unPack->GetInt("error_no");
	if (error_no != 0)
	{
    	const char* error_info = unPack->GetStr("error_info");
		SetErrInfo(error_no, error_info);
		return error_no;
	}
	
	return 0;
}


int CMonitorThread::AsynSend(IAS2Context* lpContext, ICommAgent* lpCommAgent, IF2Packer* lpInPack, int nFuncNo, int nBranchNo)
{
	// 打esb包
	IESBMessage*  lpReqMsg = lpContext->GetESBMsgFactory()->GetESBMsg();
	lpReqMsg->Prepare(REQUEST_PACKET, nFuncNo);
	lpReqMsg->GetItem(TAG_BRANCH_NO)->SetInt(nBranchNo);
	lpReqMsg->GetItem(TAG_MESSAGE_BODY)->SetRawData(lpInPack->GetPackBuf(), lpInPack->GetPackLen());

	int nFlags = 0;
	int nHandle = lpCommAgent->AsynSendMsg(lpReqMsg, nFlags);
	return nHandle;
}


IF2UnPacker* CMonitorThread::AsynRecv(IAS2Context* lpContext, ICommAgent* lpCommAgent, int nHandle, int nTimeOut, int nBranchNo)
{
	char sErrMsg[2048] = {0};
	int nErrNo = 0;
	IESBMessage* lpBackMsg = NULL;
	
	// 接收应答包
	int nRet = lpCommAgent->AsynGetMsg(nHandle, &lpBackMsg, nTimeOut);
	if ((nRet != 0) || (lpBackMsg == NULL))
	{
		nErrNo = -112;
		sprintf(sErrMsg, "branch_no[%d]接收功能号应答包异常, 请检查是否存在超时情况(300s)", nBranchNo);
		DLOGERROR(lpContext,nErrNo, sErrMsg);
		SetErrInfo(nErrNo, sErrMsg);
		
		if (lpBackMsg != NULL)
		{
			lpBackMsg->Release();
		}
		return NULL;
	}
	
	// 判断ESB路由层是否异常
	nRet = lpBackMsg->GetItem(TAG_ERROR_NO)->GetInt();
	if (0 != nRet)
	{
		nErrNo = nRet;
		sprintf(sErrMsg, "branch_no[%d]异步请求路由异常，%s", 
			nBranchNo, 
			lpBackMsg->GetItem(TAG_ERROR_INFO)->GetString()
		);
		DLOGERROR(lpContext,nErrNo, sErrMsg);
		SetErrInfo(nErrNo, sErrMsg);
		
		lpBackMsg->Release();
		return NULL;
	}
	
	//-----------------------------
	// 解析应答包
	nRet = lpBackMsg->GetItem(TAG_RETURN_CODE)->GetInt();
	void *lpData = NULL;
	int nLen = 0;
	lpData= (void*)lpBackMsg->GetItem(TAG_MESSAGE_BODY)->GetRawData(&nLen);
	//解析业务包体
	IF2UnPacker* unPacker = lpContext->GetF2PackSvr()->GetUnPacker(lpData, nLen);
	if (NULL == unPacker)
	{
		nErrNo = -112;
		sprintf(sErrMsg, "branch_no[%d]异步请求应答解析异常，业务包体为空", nBranchNo);
		DLOGERROR(lpContext,nErrNo, sErrMsg);
		SetErrInfo(nErrNo, sErrMsg);
		
		lpBackMsg->Release();
		return NULL;
	}
	
	unPacker->AddRef();
	unPacker->Open(lpData, nLen);
	
	if (nRet != 0)
	{
		nErrNo = atoi(unPacker->GetStr("error_no"));
		sprintf(sErrMsg, "branch_no[%d]异步请求业务层出错：%s", nBranchNo, unPacker->GetStr("error_info"));
		DLOGERROR(lpContext,nErrNo, sErrMsg);
		SetErrInfo(nErrNo, sErrMsg);
		
		lpBackMsg->Release();
		return NULL;
	}


	lpBackMsg->Release();
	return unPacker;
}


CMonitorAgent::CMonitorAgent()
{
	m_lpMntrThread = new CMonitorThread(this);
}

CMonitorAgent::~CMonitorAgent()
{
	delete m_lpMntrThread;					/*lint !e1551*/
}

void CMonitorAgent::Execute(void* lpThreadData)
{
	SetThreadData(lpThreadData);
	m_lpMntrThread->Start();
}

void CMonitorAgent::SetThreadData(void* lpThreadData)
{
	m_lpMntrThread->SetThreadData(lpThreadData);
}

void* CMonitorAgent::GetThreadData()
{
	return m_lpMntrThread->GetThreadData();
}

void CMonitorAgent::SetErrInfo(int error_no, const char* error_info)
{
	m_nErrNo = error_no;
	strcpy(m_sErrInfo, error_info);
}

int CMonitorAgent::GetErrNo()
{
	return m_nErrNo;
}

char* CMonitorAgent::GetErrInfo()
{
	return m_sErrInfo;						/*lint !e1536*/
}

bool CMonitorAgent::WaitForTid()
{
	if (!m_lpMntrThread->WaitForTid())
	{
		return false;
	}
	return true;
}