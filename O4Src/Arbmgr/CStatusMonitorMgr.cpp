#include "CArbManager.h"
#include "CArbMgrIOC.h"
#include "CStatusMonitorMgr.h"

CStatusMonitorMgr::CStatusMonitorMgr(CArbManager* lpOwner)
{
    m_lpOwner = lpOwner;
    ///将所有定义的管理功能处理函数添加到列中:管理功能号为索引
    mf_AddToActionList( 0, &CStatusMonitorMgr::mf_GetFuncList, "GetFuncList" );
    ///@todo 如上调用mf_AddToActionList(), 添加各种管理功能号、处理函数指针、处理函数说明
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
    ///根据功能号在map中找处理函数指针
    REQ_ACTION lpAction = mf_GetAction(dwFuncNo);
    ///找到处理函数
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
        case MSG_START:  //启动
            m_lpOwner ->OnStart(pfOnSetTimeOut);
            break;
        case MSG_STOP:  //停止
            m_lpOwner ->OnStop(pfOnSetTimeOut);
            break;
        case MSG_EXIT:  //停止
            m_lpOwner ->OnExit(pfOnSetTimeOut);
            break;
    }

    return iRet;
}

///将处理函数加入到列表中

int CStatusMonitorMgr::mf_AddToActionList(unsigned long dwFuncNo, REQ_ACTION fpAction, const char * sCaption)
{
    LPACTION_INFO lpActionInfo = new ACTION_INFO;
    lpActionInfo ->lpAction = fpAction;
    lpActionInfo ->sCaption = sCaption;
    m_ProcReqActionList[dwFuncNo] = lpActionInfo;
    return 0;
}

///根据功能号取处理函数

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

///取管理功能列表

int CStatusMonitorMgr::mf_GetFuncList(IF2UnPacker * lpRequest, IF2Packer * lpAnswer)
{
    int iRet = RET_PM_OK;
    //添加应答包字段信息
    lpAnswer ->AddField("function_id");
    lpAnswer ->AddField("function_name");
    //遍历m_ProcReqActionList
    ACTION_MAP::const_iterator i = m_ProcReqActionList.begin();
    while (i != m_ProcReqActionList.end() )
    {
        LPACTION_INFO lpInfo = i ->second;
        lpAnswer ->AddInt(i ->first);
        lpAnswer ->AddStr(lpInfo ->sCaption);
        ++i; //下一个
    }
    return iRet;
}

///@todo 添加各种管理功能处理函数的实现
//@{


//@}

