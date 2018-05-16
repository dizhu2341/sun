#include "service_init/fsc_service_init_impl.h"
#include <IncludeFm/s_liblogpublic.h>
#include <IncludeFm/s_jc_public.h>
#include <map>
#include <string>

using namespace std;

//-------------------------- CService_initImpl类实现 --------------------------//

///构造函数和析构函数
//@{
    
CService_initImpl::CService_initImpl() {
    m_lpIoC = new CService_initIoC(this);
    m_lpMgr = new CService_initMgr(this);
    m_lpConfig = NULL; //依赖的配置项通过反转控制器初始化
    m_lpCoPub = NULL; //依赖的配置项通过反转控制器初始化

    ///#todo 成员变量初始化
    //#{

    //#}
}

CService_initImpl::~CService_initImpl() {
    try {
        delete m_lpIoC;
        delete m_lpMgr;
    }    catch (...) {
    };
}
//@}


///IKnown接口函数
//@{

unsigned long CService_initImpl::QueryInterface(HS_SID iid, IKnown **ppv) {
    if (strcmp(iid, SID_SERVICE_INIT) == 0) {
        *ppv = this;
    } else if (strcmp(iid, SID_IOC) == 0) {
        *ppv = m_lpIoC;
    } else if (strcmp(iid, SID_MANAGER) == 0) {
        *ppv = m_lpMgr;
    }else if (strcmp(iid, SID_CFGSVR) == 0) {
        *ppv = m_lpCfgSvr;
    } else if (strcmp(iid, SID_SECURITY) == 0) {
        *ppv = m_lpSecurity;
    } else {
        return I_NONE;
    }
    return I_OK;
}

unsigned long CService_initImpl::AddRef() {
    return I_OK;
}

unsigned long CService_initImpl::Release() {
    delete this;
    return I_OK;
}
//@}


///插件初始化，被插件库引出函数 Service_initInit()调用
//@{

int CService_initImpl::OnInit(PFOnSetTimeOut pfOnSetTimeOut) {
    int iRet = I_NONE;
    if (pfOnSetTimeOut) pfOnSetTimeOut(5000); //通知调用者本函数可能的超时时间ms


    return iRet;
}
//@}


///管理器事件处理函数
//@{
//启动事件处理

void CService_initImpl::OnStart(PFOnSetTimeOut pfOnSetTimeOut) {
    if (pfOnSetTimeOut) pfOnSetTimeOut(5000); //通知调用者本函数可能的超时时间ms
    InitLogLevel();
    InitLogLineCount();
    InitLogName();
    InitLogPath();
    InitHsdbOraInfo();
}

//停止事件处理

void CService_initImpl::OnStop(PFOnSetTimeOut pfOnSetTimeOut) {
    if (pfOnSetTimeOut) pfOnSetTimeOut(5000); //通知调用者本函数可能的超时时间ms
    ///#todo 添加相关停止事件处理代码，比如停止相关线程
    //#{


    //#}
}

//退出事件处理

void CService_initImpl::OnExit(PFOnSetTimeOut pfOnSetTimeOut) {
    if (pfOnSetTimeOut) pfOnSetTimeOut(5000); //通知调用者本函数可能的超时时间ms
    ///#todo 添加相关退出事件处理代码，比如释放资源
    //#{

    //#}
}
//@}


///@todo 定义其他函数
//@{

int CService_initImpl::InitLogLevel() {
    int iRet = I_NONE;
    if (!m_lpConfig) {
        printf("ERROR:Get log level failed! Please ensure the configuration of service_init is correct\n");
        return iRet;
    }

    iRet = I_OK;
    //获取配置信息
    IRCfgObj *lpChild = m_lpConfig ->GetChild("args");
    if (!lpChild) {
        GLogLevel = DEFAULT_LOG_LEVEL;
    } else {
        //获取日志等级信息
        const char *lpValue = lpChild ->GetAttrValue("log_level");
        // 如果配置文件没有设置日志等级，则程序默认把日志等级设置成5
        GLogLevel = (lpValue == NULL) ? DEFAULT_LOG_LEVEL : atoi(lpValue);
    }
    printf("GLogLevel=%d\n", GLogLevel);
    return iRet;
}

int CService_initImpl::InitLogLineCount() {
    //根据日志规范，不允许O4管理端统一按日期拆分
    int iRet = I_OK;
    GMaxLineCount = DEFAULT_LOG_LINE;
    return iRet;
}

int CService_initImpl::InitLogName() {
    int iRet = I_NONE;
    if (!m_lpConfig) {
        printf("ERROR:Get log name failed! Please ensure the configuration of service_init is correct\n");
        return iRet;
    }

    iRet = I_OK;
    IRCfgObj *lpChild = m_lpConfig->GetChild("args");
    if (!lpChild) {
        pGLogName = DEFAULT_LOG_NAME;
    } else {
        // 获取日志路径，默认配置在workspace/log路径
        pGLogName = lpChild->GetAttrValue("log_name");
        pGLogName = pGLogName ? pGLogName : DEFAULT_LOG_NAME;
    }
    printf("pGLogName=%s\n", pGLogName);
    return iRet;
}

int CService_initImpl::InitLogPath() {
    int iRet = I_NONE;
    if (!m_lpConfig) {
        printf("ERROR:Get log path failed! Please ensure the configuration of service_init is correct\n");
        return iRet;
    }

    iRet = I_OK;
    IRCfgObj *lpChild = m_lpConfig->GetChild("args");
    if (!lpChild) {
        GLogPath = DEFAULT_LOG_PATH;
    } else {
        // 获取日志路径，默认配置在workspace/log路径
        GLogPath = lpChild->GetAttrValue("log_path");
        GLogPath = GLogPath ? GLogPath : DEFAULT_LOG_PATH;
    }
    printf("GLogPath=%s\n", GLogPath);
    return iRet;
}

int CService_initImpl::InitHsdbOraInfo() {
    IRCfgObj * lpCoPub = m_lpCoPub;
    ICfgSvr * lpCfgSvr = m_lpCfgSvr;
    ISecurity *lpSecurity = m_lpSecurity;
    IRCfgObj * lpPubCfgSvr = lpCoPub->GetChild(CO_APP_INFO);
    if (lpPubCfgSvr == NULL)
    {
        return -1;
    }
    const char * lpSvrName = lpPubCfgSvr->GetAttrValue(CO_ATTR_SVR_NAME);
    if (lpSvrName == NULL || *lpSvrName == '\0')
    {
        return -1;
    }
    IRCfgObj * lpPubCfgArg = lpCoPub->GetChild(CO_APP_ARGS);
    if (lpPubCfgArg == NULL)
    {
        return -1;
    }
    const char * lpCfgFile = lpPubCfgArg->GetAttrValue("f");
    if (lpCfgFile == NULL || *lpCfgFile == '\0')
    {
        return -1;
    }
    //读配置文件
    ICfgObjMaker* lpReadMaker = lpCfgSvr->GetCfgObjMaker();
    if (lpReadMaker == NULL) 
    {
        return -1;
    }
    IRCfgObj * lpConfigXMl = lpReadMaker->LoadFromFile(lpCfgFile);
    if (lpConfigXMl == NULL) 
    {
        lpReadMaker->Release();
        return -1;
    }
    IRCfgObj * lpSvr = lpConfigXMl->GetChild(lpSvrName);
    if (lpSvr == NULL) 
    {
        lpConfigXMl->Release();
        lpReadMaker->Release();
        return -1;
    }
    IRCfgObj * lpPluginsObj = lpSvr->GetChild(CO_PLUGINS);
    if (NULL == lpPluginsObj) 
    {
        lpConfigXMl->Release();
        lpReadMaker->Release();
        return -1;
    }
    
    IRCfgObj * lpPlugin = lpPluginsObj->GetFirstChild();
    
    while (lpPlugin) 
    {
        const char* lpCfgLibName = lpPlugin->GetAttrValue("lib");
        if(NULL == lpCfgLibName || 0!= strcmp("fsc_f2hsdb", lpCfgLibName) )
        {   
            lpPlugin = lpPlugin->GetSibling();
            continue;
        }

        IRCfgObj * lpDsCfg = lpPlugin->GetChild("dss/ds");
        while(lpDsCfg)
        {
            const char* atrrLogicName = lpDsCfg->GetAttrValue("logic_name");
            if(NULL == atrrLogicName)
            {
                lpDsCfg = lpDsCfg->GetSibling();
                continue;
            }
            
            if (NULL != lpSecurity)
                lpSecurity->DecCfgObj(lpDsCfg);
            
            const char* atrrPasswd = lpDsCfg->GetAttrValue("password");
            AddHsdbOraInfo(atrrLogicName, atrrPasswd);
            lpDsCfg = lpDsCfg->GetSibling();
        }
        break;  
    }

    lpConfigXMl->Release();
    lpReadMaker->Release();

    return 0;
}

//@}


//-------------------------- CService_initIoC类实现 --------------------------//

unsigned long CService_initIoC::QueryInterface(HS_SID iid, IKnown **ppv) {
    if (strcmp(iid, SID_SERVICE_INIT) == 0) {
        *ppv = m_lpOwner;
    } else if (strcmp(iid, SID_IOC) == 0) {
        *ppv = this;
    } else {
        *ppv = (IKnown *) NULL;
        return I_NONE;
    }
    return I_OK;
}

unsigned long CService_initIoC::AddRef() {
    return I_OK;
}

unsigned long CService_initIoC::Release() {
    return I_OK;
}

int FUNCTION_CALL_MODE CService_initIoC::SetConfig(const char * sPath, IRCfgObj * lpConfig) {
    int iRet = I_OK;
    //增加引用计数，传递给容器，由容器在用完之后释放(处理MSG_START事件时释放)
    if (lpConfig) {
        if (strcmp(sPath, CO_PLUGIN) == 0) {
            lpConfig->AddRef();
            m_lpOwner->m_lpConfig = lpConfig;
        } else if (strcmp(sPath, CO_PUB) == 0) {
            lpConfig->AddRef();
            m_lpOwner->m_lpCoPub = lpConfig;
        }
    }

    return iRet;
}

int FUNCTION_CALL_MODE CService_initIoC::SetDependService(HS_SID iid, IKnown * lpService) {
    int iRet = I_OK;
    //@todo 保存所依赖的插件接口，这些接口由容器根据插件的声明设置进来
    if(strcmp(iid, SID_CFGSVR) == 0)
        m_lpOwner->m_lpCfgSvr = (ICfgSvr*)lpService;
    else if(strcmp(iid, SID_SECURITY) == 0)
        m_lpOwner->m_lpSecurity = (ISecurity*)lpService;
    return iRet;
}


//-------------------------- CService_initMgr类实现 --------------------------//

CService_initMgr::CService_initMgr(CService_initImpl* lpOwner) {
    m_lpOwner = lpOwner;
    ///将所有定义的管理功能处理函数添加到列中:管理功能号为索引
    mf_AddToActionList(0, &CService_initMgr::mf_GetFuncList, "GetFuncList");
    ///@todo 如上调用mf_AddToActionList(), 添加各种管理功能号、处理函数指针、处理函数说明
    //@{


    //@}
}

unsigned long CService_initMgr::QueryInterface(HS_SID iid, IKnown **ppv) {
    if (strcmp(iid, SID_SERVICE_INIT) == 0) {
        *ppv = m_lpOwner;
    } else if (strcmp(iid, SID_MANAGER) == 0) {
        *ppv = this;
    } else {
        *ppv = (IKnown *) NULL;
        return I_NONE;
    }
    return I_OK;
}

unsigned long CService_initMgr::AddRef() {
    return I_OK;
}

unsigned long CService_initMgr::Release() {
    return I_OK;
}

int FUNCTION_CALL_MODE CService_initMgr::ProcMngRequest(IF2UnPacker * lpInput, IF2Packer * lpOutput) {
    int iRet = RET_PM_OK;
    unsigned long dwFuncNo = lpInput ->GetInt("function_id");
    ///根据功能号在map中找处理函数指针
    REQ_ACTION lpAction = mf_GetAction(dwFuncNo);
    ///找到处理函数
    if (lpAction) {
        iRet = (this ->*lpAction)(lpInput, lpOutput);
    } else {
        iRet = RET_PM_ERR;
    }
    return iRet;
}

int FUNCTION_CALL_MODE CService_initMgr::ProcMngAnswer(IF2UnPacker * lpInput) {
    int iRet = RET_PM_OK;
    return iRet;
}

int FUNCTION_CALL_MODE
CService_initMgr::ProcSysEvent(unsigned long dwMessageID,
        unsigned long dwWParam,
        unsigned long dwLParam,
        PFOnSetTimeOut pfOnSetTimeOut) {
    int iRet = I_OK;
    switch (dwMessageID) {
        case MSG_START: //启动
            m_lpOwner ->OnStart(pfOnSetTimeOut);
            break;
        case MSG_STOP: //停止
            m_lpOwner ->OnStop(pfOnSetTimeOut);
            break;
        case MSG_EXIT: //停止
            m_lpOwner ->OnExit(pfOnSetTimeOut);
            break;
    }

    return iRet;
}

///将处理函数加入到列表中

int CService_initMgr::mf_AddToActionList(unsigned long dwFuncNo, REQ_ACTION fpAction, const char * sCaption) {
    LPACTION_INFO lpActionInfo = new ACTION_INFO;
    lpActionInfo ->lpAction = fpAction;
    lpActionInfo ->sCaption = sCaption;
    m_ProcReqActionList[dwFuncNo] = lpActionInfo;
    return 0;
}

///根据功能号取处理函数

CService_initMgr::REQ_ACTION CService_initMgr::mf_GetAction(unsigned long dwFuncNo) {
    REQ_ACTION lpAction = NULL;
    ACTION_MAP::const_iterator i = m_ProcReqActionList.find(dwFuncNo);
    if (i != m_ProcReqActionList.end()) {
        lpAction = ((LPACTION_INFO) (i ->second)) ->lpAction;
    }
    return lpAction;
}

///取管理功能列表

int CService_initMgr::mf_GetFuncList(IF2UnPacker * lpRequest, IF2Packer * lpAnswer) {
    int iRet = RET_PM_OK;
    //添加应答包字段信息
    lpAnswer ->AddField("function_id");
    lpAnswer ->AddField("function_name");
    //遍历m_ProcReqActionList
    ACTION_MAP::const_iterator i = m_ProcReqActionList.begin();
    while (i != m_ProcReqActionList.end()) {
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


///-------------------------- 插件库引出函数实现 --------------------------///
//@{

int FUNCTION_CALL_MODE Service_initInit(void * lpInstance, PFOnSetTimeOut pfOnSetTimeOut) {
    int iRet = I_NONE;
    if (lpInstance) iRet = ((CService_initImpl *) lpInstance) ->OnInit(pfOnSetTimeOut);
    return iRet;
}

char * FUNCTION_CALL_MODE GetService_initDependSvr(void * lpInstance) {
    ///@todo 返回本插件依赖的其他插件ID串列表
    //有多个时，形如："xxxxx\0yyyyy\0\0"，表示依赖xxxxx,yyyyy二个插件接口，以空串表示结束。

    return SID_CFGSVR"\0"SID_SECURITY"\0\0";
}

IKnown * FUNCTION_CALL_MODE GetService_initInstance() {
    return new CService_initImpl();
}

int FUNCTION_CALL_MODE GetService_initInfo(int iIndex, tagBaseServiceInfo * ppv) {
    int iRet = I_OK;
    switch (iIndex) {
        case 0:
            if (ppv != NULL) {
                ppv ->ServiceID = SID_SERVICE_INIT;
                ppv ->iVersion = 20141117;
                ppv ->Init = Service_initInit;
                ppv ->getInstance = GetService_initInstance;
                ppv ->getDependServices = GetService_initDependSvr;
                ppv ->Caption = __DATE__;
            }
            break;
        default:
            iRet = I_NONE;
    }
    return iRet;
}
//@}

