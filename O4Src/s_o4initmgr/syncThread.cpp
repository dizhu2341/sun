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
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED); //ȷ�����̴߳���detached״̬, �߳̽����Զ��ͷ�ϵͳ��Դ
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
    //��������Ϊ�ѷ���״̬
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
		SetErrInfo(-110, "��ȡ������ʧ��");
		return false;
	}
    // ��ȡ���ݿ����Ӵ�
    IConnection *lpDBConn = m_lpContext->GetDBConnection(O3DB);
    if (NULL == lpDBConn)
    {
        SetErrInfo(-110, "��ȡO3���ݿ����Ӵ�ʧ��");
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
        SetErrInfo(lpDBConn->getErrNo(), "���ô洢���̡�%s��ʧ�ܣ�%d,%s", sProcName, lpDBConn->getErrNo(), lpDBConn->getErrInfo());
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
		SetErrInfo(-110, "��ȡ������ʧ��");
		return false;
	}
    // ��ȡ���ݿ����Ӵ�
    IConnection *lpDBConn = m_lpContext->GetDBConnection(O3DB);
    if (NULL == lpDBConn)
    {
        SetErrInfo(-110, "��ȡO3���ݿ����Ӵ�ʧ��");
        return false;
    }

    char sExecSql[256] = {0};
    sprintf(sExecSql, "call %s(?)", sProcName);
    ICallableStatement *lpCall = lpDBConn->createCallableStatement();
    lpCall->prepare(sExecSql);
    lpCall->setInt(1, -1); //���1��ֵ���ó�-1����ʾ�����ճ�����call sp_o4sync_asset(-1)
    IF2ResultSet *lpResult = lpCall->open();
    if (NULL == lpResult)
    {
        //DLOGEVENT(m_lpContext, "2prc"<<sProcName<<";error="<<lpDBConn->getErrInfo());
        SetErrInfo(lpDBConn->getErrNo(), "���ô洢���̡�%s��ʧ�ܣ�%s", sProcName, lpDBConn->getErrInfo());
        lpCall->destroy();
        lpDBConn->toFree();
        return false;
    }

    //�ͷ���Դ
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
            )   //�����������Ϊ�գ���ʾ��֧���ռ䣬����ȥ��Щ������ӱ�������޲����Ĵ洢����
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
    DLOGEVENT(m_lpContext, "ͬ����[" << GetThreadTask()->GetSyncTableInfo()->GetTableName() << "]��ʼ");

    char sTableName[256] = {0};
    strcpy(sTableName, GetThreadTask()->GetSyncTableInfo()->GetTableName());

    // ����Ƕཻ������ͬ������������߼�
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
    
    DLOGEVENT(m_lpContext, "ͬ����[" << GetThreadTask()->GetSyncTableInfo()->GetTableName() << "]���");
    return true;
}

bool CSyncThread::AfterRun()
{
    if (GetThreadTask() == NULL)
    {
        SetErrInfo(-114, "�߳��������ΪNULL");
        return false;
    }
    //��ͬ�������ó������
    GetThreadTask()->SetStatus(TASK_STATUS_FINISHED);
    //���߳�״̬�óɿ���
    m_nStatus = STATUS_IDLE;
    return true;
}

bool CSyncThread::LockTable(char *pTableName)
{
    pthread_mutex_t *pSyncLock = gCMutexMgr->GetLock(pTableName);
    if (NULL == pSyncLock)
    {
        //SetErrInfo(SYNC_ERR_LOCK_MUTEX, "��%s����ͬ������ȡͬ��������ʧ��", pTableName);
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
		SetErrInfo(-110, "��ȡ������ʧ��");
		return false;
	}
    // ��F2��
    IF2Packer* lpInPack = m_lpContext->GetF2PackSvr()->GetPacker(2);
    IF2Packer* lpOutPack = m_lpContext->GetF2PackSvr()->GetPacker(2);
    lpInPack->BeginPack();
    lpInPack->AddField("error_pathinfo");
    lpInPack->AddStr(((CSyncTask *) GetThreadTask())->GetErrPathInfo());
    lpInPack->EndPack();

    // ���������
    int nHandle = AsynSend(m_lpContext, m_lpCommAgent, lpInPack, nAsFuncNo);

    // �ͷ���δ����������ڴ�
    free(lpInPack->GetPackBuf());
    lpInPack->Release();

    // �ж��Ƿ�������
    if (nHandle <= 0)
    {
        sprintf(sErrPathInfo, "%s->F%d()", ((CSyncTask *) GetThreadTask())->GetErrPathInfo(), nAsFuncNo);
        SetErrPathInfo(sErrPathInfo);
        SetErrInfo(-110, "��ʼ���첽������ʧ��");
        return GetErrNo();
    }

    // ����Ӧ���
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

    //����Ӧ���
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
    // ��esb��
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

    // ����Ӧ���
    int nRet = lpCommAgent->AsynGetMsg(nHandle, &lpBackMsg, nTimeOut);
    if ((nRet != 0) || (lpBackMsg == NULL))
    {
        nErrNo = -112;
        sprintf(sErrMsg, "���չ��ܺ�Ӧ����쳣, �����Ƿ���ڳ�ʱ���(%d s)", (nTimeOut / 1000));
        SetErrInfo(nErrNo, sErrMsg);

        if (lpBackMsg != NULL)
        {
            lpBackMsg->Release();
        }
        return nErrNo; /*lint !e539*/
    }

    // �ж�ESB·�ɲ��Ƿ��쳣
    nRet = lpBackMsg->GetItem(TAG_ERROR_NO)->GetInt();
    if (0 != nRet)
    {
        nErrNo = nRet;
        sprintf(sErrMsg, "�첽����·���쳣��%s", lpBackMsg->GetItem(TAG_ERROR_INFO)->GetString());
        SetErrInfo(nErrNo, sErrMsg);

        lpBackMsg->Release();
        return nErrNo;
    }

    //-----------------------------
    // ����Ӧ���
    nRet = lpBackMsg->GetItem(TAG_RETURN_CODE)->GetInt();
    void *lpData = NULL;
    int nLen = 0;
    lpData = (void*) lpBackMsg->GetItem(TAG_MESSAGE_BODY)->GetRawData(&nLen);
    //����ҵ�����
    IF2UnPacker* unPacker = lpContext->GetF2PackSvr()->GetUnPacker(lpData, nLen);
    if (NULL == unPacker)
    {
        nErrNo = -112;
        sprintf(sErrMsg, "�첽����Ӧ������쳣��ҵ�����Ϊ��");
        SetErrInfo(nErrNo, sErrMsg);

        lpBackMsg->Release();
        return nErrNo;
    }

    if (nRet != 0)
    {
        nErrNo = atoi(unPacker->GetStr("error_no"));
        sprintf(sErrMsg, "�첽����ҵ������%s", unPacker->GetStr("error_info"));
        SetErrInfo(nErrNo, sErrMsg);
        SetErrPathInfo(unPacker->GetStr("error_pathinfo"));

        lpBackMsg->Release();
        return nErrNo;
    }

    //����������ڴ浽���δ����
    PackResultSet(unPacker, lpOutPack);
    unPacker->Release();

    //�ͷ�ESB�ڴ���Դ
    lpBackMsg->Release();
    return 0;
}
