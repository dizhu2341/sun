#include "syncThread.h"
#include "hshead.h"
#include "Mutex.h"
#include <iostream>
using namespace std;

CMutexMgr *gCMutexMgr = CMutexMgr::GetInstance();

CSyncThread::CSyncThread()
{
    nErrorNo = 0;
    m_lpContext = NULL;
    m_lpCommAgent = NULL;

}

CSyncThread::~CSyncThread()
{
	 m_lpContext = NULL;
	 m_lpCommAgent = NULL;
}

void CSyncThread::Start()
{
    pthread_attr_t attr;
    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED); //确保该线程处于detached状态, 线程结束自动释放系统资源
    int nRet = pthread_create(&m_nTid, &attr, ThreadProc, this);
    if (0 != nRet)
        return;
}

CSyncTask* CSyncThread::GetThreadTask()
{
    return (CSyncTask *) m_lpThreadTask;
}

void CSyncThread::SetThreadTask(void* lpTask)
{
    if (m_lpThreadTask == lpTask)
    {
        return;
    }
    m_lpThreadTask = lpTask; /*lint !e539*/
    //设置任务为已分配状态
    ((CSyncTask *) m_lpThreadTask)->SetStatus(TASK_STATUS_ASSIGNED);
}

bool CSyncThread::BeforeRun()
{
    return true;
}

bool CSyncThread::ExecProcNoParam(char *sProcName)
{
	if (NULL == m_lpContext)
	{
		SetErrInfo(-110, "获取上下文失败");
		return false;
	}
    // 获取数据库连接串
    IConnection *lpDBConn = m_lpContext->GetDBConnection(O3DB);
    if (NULL == lpDBConn)
    {
        SetErrInfo(-110, "获取O3数据库连接串失败");
        return false;
    }

    char sExecSql[256] = {0};
    sprintf(sExecSql, "call %s()", sProcName);
    //DLOGEVENT(m_lpContext, "sExecSql: "<<sExecSql);
    //DLOGEVENT(m_lpContext, "begin "<<sProcName);
    bool bRet = lpDBConn->executeUpdate(sExecSql);
    //DLOGEVENT(m_lpContext, "end "<<sProcName);
    if (bRet !=  0)
    {
        //DLOGEVENT(m_lpContext, "1prc"<<sProcName<<";error="<<lpDBConn->getErrInfo());
        SetErrInfo(lpDBConn->getErrNo(), "调用存储过程【%s】失败：%d,%s", sProcName, lpDBConn->getErrNo(), lpDBConn->getErrInfo());
        lpDBConn->toFree();
        return false;
    }
    lpDBConn->toFree();
    return true;
}

bool CSyncThread::ExecProcWithParam(char *sProcName)
{
	if (NULL == m_lpContext)
	{
		SetErrInfo(-110, "获取上下文失败");
		return false;
	}
    // 获取数据库连接串
    IConnection *lpDBConn = m_lpContext->GetDBConnection(O3DB);
    if (NULL == lpDBConn)
    {
        SetErrInfo(-110, "获取O3数据库连接串失败");
        return false;
    }

    char sExecSql[256] = {0};
    sprintf(sExecSql, "call %s(?)", sProcName);
    ICallableStatement *lpCall = lpDBConn->createCallableStatement();
    lpCall->prepare(sExecSql);
    lpCall->setInt(1, -1); //入参1的值设置成-1，表示调用日初，例call sp_o4sync_asset(-1)
    IF2ResultSet *lpResult = lpCall->open();
    if (NULL == lpResult)
    {
        //DLOGEVENT(m_lpContext, "2prc"<<sProcName<<";error="<<lpDBConn->getErrInfo());
        SetErrInfo(lpDBConn->getErrNo(), "调用存储过程【%s】失败：%s", sProcName, lpDBConn->getErrInfo());
        lpCall->destroy();
        lpDBConn->toFree();
        return false;
    }

    //释放资源
    lpCall->destroy();
    lpResult->Destroy();
    lpDBConn->toFree();

    return true;
}

bool CSyncThread::CallProcedure(CSyncTableInfo* lpSyncTable)
{
    if (
            0 == strcmp(lpSyncTable->GetTopicName(), " ") && 
                !(
                0 == strcmp(lpSyncTable->GetTableName(), "jc_tfeedetailqh") ||
                0 == strcmp(lpSyncTable->GetTableName(), "jc_tfeedetailhs") ||
                0 == strcmp(lpSyncTable->GetTableName(), "jc_tfeedetailseths") ||
                0 == strcmp(lpSyncTable->GetTableName(), "uft_tautoriskparam")
                )
            )   //如果是主题名为空（表示不支持日间，但除去这些特殊的子表），则调无参数的存储过程
    {
        return ExecProcNoParam(lpSyncTable->GetPrcName());
    }
    else
    {
        return ExecProcWithParam(lpSyncTable->GetPrcName());
    }
}

bool CSyncThread::Run()
{
    DLOGEVENT(m_lpContext, "同步表[" << GetThreadTask()->GetSyncTableInfo()->GetTableName() << "]开始");

    char sTableName[256] = {0};
    strcpy(sTableName, GetThreadTask()->GetSyncTableInfo()->GetTableName());

    // 如果是多交易中心同步则走另外的逻辑
    if ((0 == strcmp("jc_tcenterfund", sTableName)))
    {
        return CallSubService(2615076);
    }
    
    LockTable(sTableName);
    if (!CallProcedure(GetThreadTask()->GetSyncTableInfo()))
    {
        UnLockTable(sTableName);
        return false;
    }
    
    UnLockTable(sTableName);
    
    DLOGEVENT(m_lpContext, "同步表[" << GetThreadTask()->GetSyncTableInfo()->GetTableName() << "]完成");
    return true;
}

bool CSyncThread::AfterRun()
{
    if (GetThreadTask() == NULL)
    {
        SetErrInfo(-114, "线程任务对象为NULL");
        return false;
    }
    //把同步任务置成已完成
    GetThreadTask()->SetStatus(TASK_STATUS_FINISHED);
    //把线程状态置成空闲
    m_nStatus = STATUS_IDLE;
    return true;
}

bool CSyncThread::LockTable(char *pTableName)
{
    pthread_mutex_t *pSyncLock = gCMutexMgr->GetLock(pTableName);
    if (NULL == pSyncLock)
    {
        //SetErrInfo(SYNC_ERR_LOCK_MUTEX, "【%s】表同步，获取同步互斥锁失败", pTableName);
        return false;
    }
    return (0 == pthread_mutex_lock(pSyncLock)) ? true : false; /*lint !e454*/
} /*lint !e456*/

bool CSyncThread::UnLockTable(char *pTableName)
{
    return gCMutexMgr->FreeLock(pTableName);
}

void CSyncThread::SetErrInfo(int nErrNo, const char* sErrInfoFmt, ...)
{
    nErrorNo = nErrNo;

    char sErrInfo[1024] = {0};
    va_list oArglst;
    memset(&oArglst, 0, sizeof (va_list));

    va_start(oArglst, sErrInfoFmt);
    vsprintf(sErrInfo, sErrInfoFmt, oArglst);
    va_end(oArglst);

    if (GetThreadTask() == NULL)
    {
        return;
    }
    GetThreadTask()->SetErrInfo(nErrNo, sErrInfo);
    return;
}

void CSyncThread::SetErrPathInfo(const char* pErrPathInfo)
{
    if (GetThreadTask() == NULL)
    {
        return;
    }
    GetThreadTask()->SetErrPathInfo(pErrPathInfo);
}

int CSyncThread::GetErrNo()
{
    return nErrorNo;
}

void CSyncThread::SetContext(IAS2Context* lpContext)
{
    m_lpContext = lpContext;
}

void CSyncThread::SetCommAgent(ICommAgent * lpCommAgent)
{
    m_lpCommAgent = lpCommAgent;
}

int CSyncThread::CallSubService(int nAsFuncNo)
{
    int nTimeOut = 3600000;
    char sErrPathInfo[4001] = {0};
    if (NULL == m_lpContext)
	{
		SetErrInfo(-110, "获取上下文失败");
		return false;
	}
    // 打F2包
    IF2Packer* lpInPack = m_lpContext->GetF2PackSvr()->GetPacker(2);
    IF2Packer* lpOutPack = m_lpContext->GetF2PackSvr()->GetPacker(2);
    lpInPack->BeginPack();
    lpInPack->AddField("error_pathinfo");
    lpInPack->AddStr(((CSyncTask *) GetThreadTask())->GetErrPathInfo());
    lpInPack->EndPack();

    // 发送请求包
    int nHandle = AsynSend(m_lpContext, m_lpCommAgent, lpInPack, nAsFuncNo);

    // 释放入参打包器打包器内存
    free(lpInPack->GetPackBuf());
    lpInPack->Release();

    // 判断是否发送正常
    if (nHandle <= 0)
    {
        sprintf(sErrPathInfo, "%s->F%d()", ((CSyncTask *) GetThreadTask())->GetErrPathInfo(), nAsFuncNo);
        SetErrPathInfo(sErrPathInfo);
        SetErrInfo(-110, "初始化异步请求发送失败");
        return GetErrNo();
    }

    // 接收应答包
    IF2UnPacker* lpOutUnPacker = NULL;
    lpOutPack->BeginPack();
    int iRet = AsynRecv(m_lpContext, m_lpCommAgent, lpOutPack, nHandle, nTimeOut);
    lpOutPack->EndPack();

    if (iRet != 0)
    {
        sprintf(sErrPathInfo, "F%d->%s", nAsFuncNo, ((CSyncTask *) GetThreadTask())->GetErrPathInfo());
        SetErrPathInfo(sErrPathInfo);
        return GetErrNo();
    }

    //解析应答包
    lpOutUnPacker = lpOutPack->UnPack();
    int error_no = lpOutUnPacker->GetInt("error_no");
    if (error_no != 0)
    {
        SetErrInfo(lpOutUnPacker->GetInt("error_no"), lpOutUnPacker->GetStr("error_info"));
        SetErrPathInfo(lpOutUnPacker->GetStr("error_pathinfo"));
        return error_no;
    }

    return 0;
}

int CSyncThread::AsynSend(IAS2Context* lpContext, ICommAgent* lpCommAgent, IF2Packer* lpInPack, int nFuncNo)
{
    // 打esb包
    IESBMessage* lpReqMsg = lpContext->GetESBMsgFactory()->GetESBMsg();
    lpReqMsg->Prepare(REQUEST_PACKET, nFuncNo);
    lpReqMsg->GetItem(TAG_MESSAGE_BODY)->SetRawData(lpInPack->GetPackBuf(), lpInPack->GetPackLen());

    int nFlags = 0;
    int nHandle = lpCommAgent->AsynSendMsg(lpReqMsg, nFlags);
    return nHandle;
}

int CSyncThread::AsynRecv(IAS2Context* lpContext, ICommAgent* lpCommAgent, IF2Packer* lpOutPack, int nHandle, int nTimeOut)
{
    char sErrMsg[2048] = {0};
    int nErrNo = 0;
    IESBMessage* lpBackMsg = NULL;

    // 接收应答包
    int nRet = lpCommAgent->AsynGetMsg(nHandle, &lpBackMsg, nTimeOut);
    if ((nRet != 0) || (lpBackMsg == NULL))
    {
        nErrNo = -112;
        sprintf(sErrMsg, "接收功能号应答包异常, 请检查是否存在超时情况(%d s)", (nTimeOut / 1000));
        SetErrInfo(nErrNo, sErrMsg);

        if (lpBackMsg != NULL)
        {
            lpBackMsg->Release();
        }
        return nErrNo; /*lint !e539*/
    }

    // 判断ESB路由层是否异常
    nRet = lpBackMsg->GetItem(TAG_ERROR_NO)->GetInt();
    if (0 != nRet)
    {
        nErrNo = nRet;
        sprintf(sErrMsg, "异步请求路由异常，%s", lpBackMsg->GetItem(TAG_ERROR_INFO)->GetString());
        SetErrInfo(nErrNo, sErrMsg);

        lpBackMsg->Release();
        return nErrNo;
    }

    //-----------------------------
    // 解析应答包
    nRet = lpBackMsg->GetItem(TAG_RETURN_CODE)->GetInt();
    void *lpData = NULL;
    int nLen = 0;
    lpData = (void*) lpBackMsg->GetItem(TAG_MESSAGE_BODY)->GetRawData(&nLen);
    //解析业务包体
    IF2UnPacker* unPacker = lpContext->GetF2PackSvr()->GetUnPacker(lpData, nLen);
    if (NULL == unPacker)
    {
        nErrNo = -112;
        sprintf(sErrMsg, "异步请求应答解析异常，业务包体为空");
        SetErrInfo(nErrNo, sErrMsg);

        lpBackMsg->Release();
        return nErrNo;
    }

    if (nRet != 0)
    {
        nErrNo = atoi(unPacker->GetStr("error_no"));
        sprintf(sErrMsg, "异步请求业务层出错：%s", unPacker->GetStr("error_info"));
        SetErrInfo(nErrNo, sErrMsg);
        SetErrPathInfo(unPacker->GetStr("error_pathinfo"));

        lpBackMsg->Release();
        return nErrNo;
    }

    //拷贝结果集内存到出参打包器
    PackResultSet(unPacker, lpOutPack);
    unPacker->Release();

    //释放ESB内存资源
    lpBackMsg->Release();
    return 0;
}
