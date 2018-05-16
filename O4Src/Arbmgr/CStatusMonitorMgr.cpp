#include "CArbManager.h"
#include "CArbMgrIOC.h"
#include "CStatusMonitorMgr.h"

CStatusMonitorMgr::CStatusMonitorMgr(CArbManager* lpOwner)
{
    m_lpOwner = lpOwner;
    ///�����ж���Ĺ����ܴ�������ӵ�����:�����ܺ�Ϊ����
    mf_AddToActionList( 0, &CStatusMonitorMgr::mf_GetFuncList, "GetFuncList" );
    ///@todo ���ϵ���mf_AddToActionList(), ��Ӹ��ֹ����ܺš�������ָ�롢������˵��
    //@{


    //@}
}

unsigned long  CStatusMonitorMgr::QueryInterface( HS_SID iid, IKnown **ppv )
{
    if ( strcmp(iid, SID_ARBMGR ) == 0 )
    {
        *ppv =  m_lpOwner;
    }
    else if ( strcmp(iid, SID_MANAGER) == 0 )
    {
        *ppv =  this;
    }
    else
    {
        *ppv = (IKnown *)NULL;
        return I_NONE;
    }
    return I_OK;
}

unsigned long  CStatusMonitorMgr::AddRef()
{
    return I_OK;
}

unsigned long  CStatusMonitorMgr::Release()
{
    return I_OK;
}

int FUNCTION_CALL_MODE CStatusMonitorMgr::ProcMngRequest(IF2UnPacker * lpInput, IF2Packer * lpOutput)
{
    int iRet = RET_PM_OK;
    unsigned long dwFuncNo = lpInput ->GetInt("function_id");
    ///���ݹ��ܺ���map���Ҵ�����ָ��
    REQ_ACTION lpAction = mf_GetAction(dwFuncNo);
    ///�ҵ�������
    if (lpAction)
    {
        iRet = (this ->*lpAction)(lpInput, lpOutput);
    }
    else
    {
        iRet = RET_PM_ERR;
    }
    return iRet;
}

int FUNCTION_CALL_MODE CStatusMonitorMgr::ProcMngAnswer(IF2UnPacker * lpInput)
{
    int iRet = RET_PM_OK;
    return iRet;
}

int FUNCTION_CALL_MODE
CStatusMonitorMgr::ProcSysEvent(unsigned long dwMessageID,
                                unsigned long dwWParam,
                                unsigned long dwLParam,
                                PFOnSetTimeOut pfOnSetTimeOut)
{
    int iRet = I_OK;
    switch (dwMessageID)
    {
        case MSG_START:  //����
            m_lpOwner ->OnStart(pfOnSetTimeOut);
            break;
        case MSG_STOP:  //ֹͣ
            m_lpOwner ->OnStop(pfOnSetTimeOut);
            break;
        case MSG_EXIT:  //ֹͣ
            m_lpOwner ->OnExit(pfOnSetTimeOut);
            break;
    }

    return iRet;
}

///�����������뵽�б���

int CStatusMonitorMgr::mf_AddToActionList(unsigned long dwFuncNo, REQ_ACTION fpAction, const char * sCaption)
{
    LPACTION_INFO lpActionInfo = new ACTION_INFO;
    lpActionInfo ->lpAction = fpAction;
    lpActionInfo ->sCaption = sCaption;
    m_ProcReqActionList[dwFuncNo] = lpActionInfo;
    return 0;
}

///���ݹ��ܺ�ȡ������

CStatusMonitorMgr::REQ_ACTION CStatusMonitorMgr::mf_GetAction(unsigned long dwFuncNo)
{
    REQ_ACTION lpAction = NULL;
    ACTION_MAP::const_iterator i = m_ProcReqActionList.find(dwFuncNo);
    if ( i != m_ProcReqActionList.end() )
    {
        lpAction =  (( LPACTION_INFO)(i ->second)) ->lpAction;
    }
    return lpAction;
}

///ȡ�������б�

int CStatusMonitorMgr::mf_GetFuncList(IF2UnPacker * lpRequest, IF2Packer * lpAnswer)
{
    int iRet = RET_PM_OK;
    //���Ӧ����ֶ���Ϣ
    lpAnswer ->AddField("function_id");
    lpAnswer ->AddField("function_name");
    //����m_ProcReqActionList
    ACTION_MAP::const_iterator i = m_ProcReqActionList.begin();
    while (i != m_ProcReqActionList.end() )
    {
        LPACTION_INFO lpInfo = i ->second;
        lpAnswer ->AddInt(i ->first);
        lpAnswer ->AddStr(lpInfo ->sCaption);
        ++i; //��һ��
    }
    return iRet;
}

///@todo ��Ӹ��ֹ����ܴ�������ʵ��
//@{


//@}

