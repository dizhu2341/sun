#include "CArbManager.h"
#include "CArbMgrIOC.h"
#include "CStatusMonitorMgr.h"

unsigned long  CArbManager::QueryInterface(HS_SID iid, IKnown **ppv )
{
    if (strcmp(iid, SID_ARBMGR) == 0 )
    {
        *ppv =  this;
    }
    else if ( strcmp(iid, SID_IOC) == 0 )
    {
        *ppv =  m_lpIoC;
    }
    else if ( strcmp(iid, SID_MANAGER) == 0 )
    {
        *ppv =  m_lpMgr;
    }
    else
    {
        return I_NONE;
    }
    return I_OK;
}

unsigned long  CArbManager::AddRef()
{
    return I_OK;
}

unsigned long  CArbManager::Release()
{
    delete this;
    return I_OK;
}

///插件初始化，被插件库引出函数 ArbmgrInit()调用
int CArbManager::OnInit(PFOnSetTimeOut pfOnSetTimeOut)
{
    int iRet = I_NONE;
    if (pfOnSetTimeOut) pfOnSetTimeOut(5000); //通知调用者本函数可能的超时时间ms

    bool nRet = GetManagerPlugin();
    if (false == nRet)
    {
        LOGERROR(-99, "获取需要监控管理的插件信息失败!请正确配置arbmgr插件的monitor_plugins属性并重新启动节点！");
        printf("获取需要监控管理的插件信息失败!请正确配置arbmgr插件的monitor_plugins属性并重新启动节点！\n");
        return -99;
    }
    
    //---------------------------------------------------------
    // 初始化动作
    int heartrecvport = GetHeartRecvPort();  // 心跳接收端口
    if (heartrecvport < 0)
    {
        LOGERROR(-98, "获取心跳接收端口失败!请正确配置arbmgr插件的heart_recv_port属性并重新启动节点！\n");
        printf("获取心跳接收端口失败!请正确配置arbmgr插件的heart_recv_port属性并重新启动节点！\n");
        return -98;
    }
    
    int heartAnswerRecvPort = GetHeartAnswerRecvPort();
    if (heartAnswerRecvPort < 0)
    {
        LOGERROR(-98, "获取心跳接收端口失败!请正确配置arbmgr插件的heart_answer_recv_port属性并重新启动节点！\n");
        printf("获取心跳接收端口失败!请正确配置arbmgr插件的heart_answer_recv_port属性并重新启动节点！\n");
        return -98;
    }
    
 /*   int sendport = GetHeartSendPort();
    if (sendport < 0)
    {
        LOGERROR(-98, "获取心跳接收端口失败!请正确配置arbmgr插件的sendport属性并重新启动节点！\n");
        printf("获取心跳接收端口失败!请正确配置arbmgr插件的sendport属性并重新启动节点！\n");
        return -98;
    }*/
    
    string bakNodeip = GetBakNodeIpAddress();
    if ("" == bakNodeip)
    {
        printf("未检测到备机的配置,确认为单机模式！不启动心跳收发线程！\n");
        LOGSYSTEM("未检测到备机的配置,确认为单机模式！不启动心跳收发线程！");
    }    
    else
    {
        // 创建心跳发送线程
        m_lpSendThread = new CSendHeartThread(this, heartrecvport, heartAnswerRecvPort, bakNodeip);
        if (NULL == m_lpSendThread)
        {
            LOGERROR(-99, "心跳发送线程创建失败,请检查系统资源是否充足,并重新启动节点！");
            printf("心跳发送线程创建失败,请检查系统资源是否充足,并重新启动节点！\n");
            return -100;
        }
       
        // 创建心跳接收线程
        m_lpRecvThread = new CRecvHeartThread(this, heartrecvport, heartAnswerRecvPort, bakNodeip);
        if (NULL == m_lpSendThread)
        {
            LOGERROR(-99, "心跳接收线程创建失败,请检查系统资源是否充足,并重新启动节点！");
            printf("心跳接收线程创建失败,请检查系统资源是否充足,并重新启动节点！\n");
            return -101;
        }
    }
    
    //--------------------
    string appname = GetAppFullName();
    string shmName = appname + "_" + STATUS_SHARE_NAME;
    CSharedMem * lpShareMem = FBASE_NEW CSharedMem();
    m_lpShmStatusStruct = (ShmAcdStatus*)lpShareMem->Open(shmName.c_str());
    
    // 创建仲裁消息收发线程
    string arbResultQueueName = appname + "_" + ARB_RESULT_QUEUE;
    string eventQueueName = appname + "_" + EVENT_QUEUE; 
    m_lpArbMsgRWThread = new CArbMsgRWThread(this, eventQueueName , arbResultQueueName);
    if (NULL == m_lpArbMsgRWThread)
    {
        LOGERROR(-99, "仲裁消息收发线程创建失败,请检查系统资源是否充足,并重新启动节点！");
        printf("仲裁消息收发线程创建失败,请检查系统资源是否充足,并重新启动节点！\n");
        return -102;
    }
    
    // 设置为初始化状态
    m_CurrStatus = ACD_INIT;
    m_lpShmStatusStruct->m_byMachineStatus = ACD_INIT;
    LOGSYSTEM("设置节点状态[INIT]完成");
    return iRet;
}

//启动事件处理
void CArbManager::OnStart(PFOnSetTimeOut pfOnSetTimeOut)
{
    if (pfOnSetTimeOut) pfOnSetTimeOut(5000); //通知调用者本函数可能的超时时间ms
    
    if (m_vecMgrPlugin.size() == 0)
    {
        LOGSYSTEM("没有配置需要监控的插件,插件不工作");
        return;
    }
    
    // 获取需要监控的插件的仲裁事件处理接口的指针
    for(int i=0; i<m_vecMgrPlugin.size(); ++i)
    {
        string pluginName = m_vecMgrPlugin[i];
        IArbmgrInterface* lpInterface = m_lpIoC->GetPluginArbMgrInterface(pluginName.c_str());
        if (NULL == lpInterface)
        {
            LOGERROR(-99, "获取插进["<< pluginName <<"]仲裁事件处理句柄失败,节点启动失败,请检查配置是否正确,或者联系开发解决！");
            printf("获取插进[%s]仲裁事件处理句柄失败,节点启动失败,请检查配置是否正确,或者联系开发解决！\n", pluginName.c_str());
            continue;
        }
        m_lstArbMgrInterface.push_back(lpInterface);
    }
    
    // 启动仲裁消息收发线程
     if (NULL == m_lpArbMsgRWThread)
     {
         LOGERROR(-99, "仲裁消息收发线程没有创建,节点停止工作!");
         printf("仲裁消息收发线程没有创建,节点停止工作!\n");
         return;
     }
     m_lpArbMsgRWThread->Start();  
}

//停止事件处理
void CArbManager::OnStop(PFOnSetTimeOut pfOnSetTimeOut)
{
    if (pfOnSetTimeOut) pfOnSetTimeOut(5000); //通知调用者本函数可能的超时时间ms
    ///#todo 添加相关停止事件处理代码，比如停止相关线程
    //#{


    //#}
}

//退出事件处理
void CArbManager::OnExit(PFOnSetTimeOut pfOnSetTimeOut)
{
    if (pfOnSetTimeOut) pfOnSetTimeOut(5000); //通知调用者本函数可能的超时时间ms
    ///#todo 添加相关退出事件处理代码，比如释放资源
    //#{
   /* if (m_lpArbMsgRWThread)
        m_lpRecvThread->Stop();
    if (m_lpSendThread)
        m_lpSendThread->Stop();
    if (m_lpRecvThread)
        m_lpRecvThread->Stop();*/
    //#}
}


//------------------------------------------------------------------------
// 
CArbManager::CArbManager()
{
    m_lpIoC = new CArbMgrIOC(this);
    m_lpMgr = new CStatusMonitorMgr(this);
    m_lpConfig = NULL;        //依赖的配置项通过反转控制器初始化
    m_lpCoPub = NULL;         //依赖的配置项通过反转控制器初始化

    //----------------------------------
    m_lpSendThread = NULL;
    m_lpRecvThread = NULL;
    m_lpArbMsgRWThread = NULL;
    m_lpShmStatusStruct = NULL;
    m_CurrStatus = ACD_NONE;
}

CArbManager::~CArbManager()
{
    delete m_lpIoC;
    delete m_lpMgr;
}

//-----------------------------------------------------
// 处理仲裁机消息
void CArbManager::DealArbMsg(int arbResultId, int arbResultMsg)
{
    switch(arbResultMsg)
    {
        case SWITCH_TO_PREPARE:
        {
            SwitchToPrepare(arbResultId);
            break;
        }
        case SWITCH_TO_INACTIVE:
        {
            SwitchToInactive(arbResultId);
            break;
        }
        case SWITCH_TO_SINGLE:
        {
            SwitchToSingle(arbResultId);
            break;
        }
        case SWITCH_TO_ACTIVE:
        {
            SwitchToActive(arbResultId);
            break;
        }
        case SWITCH_TO_SEPARATE:
        {
            SwitchToSeparate(arbResultId);
            break;
        }
        default:
        {
            break;
        }
    };
}

void CArbManager::SwitchToPrepare(int arbResultId)
{
    for(int i=0; i<m_lstArbMgrInterface.size(); ++i)
    {
        IArbmgrInterface* lpInterface = m_lstArbMgrInterface[i];
        bool bRet = lpInterface->SwitchToPrepare();
        if (false == bRet)
        {
            LOGERROR(-250, "插件[" <<m_vecMgrPlugin[i].c_str() << "]切换到Prepare失败！");
            AnswerToArb(arbResultId, ALARM_TYPE_ARB_NACK);
            return;
        }
        LOGSYSTEM("插件[" <<m_vecMgrPlugin[i].c_str() << "]切换到Prepare成功！");
    }
    LOGSYSTEM("切换到PREPARE状态,开始启动心跳发送线程！");
    m_lpSendThread->Start();
    m_CurrStatus = ACD_PREPARE;
    AnswerToArb(arbResultId, ALARM_TYPE_ARB_ACK);
}

void CArbManager::SwitchToInactive(int arbResultId)
{
    for(int i=0; i<m_lstArbMgrInterface.size(); ++i)
    {
        IArbmgrInterface* lpInterface = m_lstArbMgrInterface[i];
        bool bRet = lpInterface->SwitchToInactive();
        if (false == bRet)
        {
            LOGERROR(-250, "插件[" <<m_vecMgrPlugin[i].c_str() << "]切换到Inactive失败！");
            AnswerToArb(arbResultId, ALARM_TYPE_ARB_NACK);
            return;
        }
        LOGSYSTEM("插件[" <<m_vecMgrPlugin[i].c_str() << "]切换到Inactive成功！");
    }
    
    m_CurrStatus = ACD_INACTIVE;
    LOGSYSTEM("切换到INACTIVE状态！");
    AnswerToArb(arbResultId, ALARM_TYPE_ARB_ACK);
}

void CArbManager::SwitchToSingle(int arbResultId)
{
    for(int i=0; i<m_lstArbMgrInterface.size(); ++i)
    {
        IArbmgrInterface* lpInterface = m_lstArbMgrInterface[i];
        bool bRet = lpInterface->SwitchToSingle();
        if (false == bRet)
        {
            LOGERROR(-250, "插件[" <<m_vecMgrPlugin[i].c_str() << "]切换到Single失败！");
            AnswerToArb(arbResultId, ALARM_TYPE_ARB_NACK);
            return;
        }
        LOGSYSTEM("插件[" <<m_vecMgrPlugin[i].c_str() << "]切换到Single成功！");
    }
    
    if (ACD_INIT == m_CurrStatus)
    {
        LOGSYSTEM("从状态[ACD_INIT]切换到[ACD_SINGLE]状态,开启心跳接收线程！");
        m_lpRecvThread->Start();
        m_CurrStatus = ACD_SINGLE;
        AnswerToArb(arbResultId, ALARM_TYPE_ARB_ACK);
    }
    else if (ACD_INACTIVE == m_CurrStatus)
    {
        LOGSYSTEM("从状态[ACD_INACTIVE]切换到[ACD_SINGLE]状态,暂停心跳发送线程！开始启动心跳接收线程！");
        m_lpSendThread->Pause();
        m_lpRecvThread->Start();
        m_CurrStatus = ACD_SINGLE;
        AnswerToArb(arbResultId, ALARM_TYPE_ARB_ACK);
    }
    else if (ACD_ACTIVE == m_CurrStatus)
    {
        LOGSYSTEM("从状态[ACD_ACTIVE]切换到[ACD_SINGLE]状态！");
        m_CurrStatus = ACD_SINGLE;
        AnswerToArb(arbResultId, ALARM_TYPE_ARB_ACK);
    }
    else
    {   
        LOGSYSTEM("从状态["<< m_CurrStatus << "]切换到[ACD_SINGLE]状态！");
        // 不识别的动作 
    }
}
    
void CArbManager::SwitchToActive(int arbResultId)
{
    for(int i=0; i<m_lstArbMgrInterface.size(); ++i)
    {
        IArbmgrInterface* lpInterface = m_lstArbMgrInterface[i];
        bool bRet = lpInterface->SwitchToActive();
        if (false == bRet)
        {
            LOGERROR(-250, "插件[" <<m_vecMgrPlugin[i].c_str() << "]切换到Active失败！");
            AnswerToArb(arbResultId, ALARM_TYPE_ARB_NACK);
            return;
        }
        LOGSYSTEM("插件[" <<m_vecMgrPlugin[i].c_str() << "]切换到Active成功！");
    }
    
    if (ACD_SINGLE == m_CurrStatus)
    {
        LOGSYSTEM("从状态[ACD_SINGLE]切换到[ACD_ACTIVE]状态！");
        m_CurrStatus = ACD_ACTIVE;
        AnswerToArb(arbResultId, ALARM_TYPE_ARB_ACK);
    }
    else if (ACD_INACTIVE == m_CurrStatus)
    {
        LOGSYSTEM("从状态[ACD_INACTIVE]切换到[ACD_ACTIVE]状态！暂停心跳发送线程！启动心跳接收线程！");
        m_lpSendThread->Pause();
        m_lpRecvThread->Start();
        m_CurrStatus = ACD_ACTIVE;
        AnswerToArb(arbResultId, ALARM_TYPE_ARB_ACK);
    }
    else
    {
        LOGSYSTEM("从状态[]切换到[ACD_ACTIVE]状态！");
          // 不识别的动作 
    }
}

void CArbManager::SwitchToSeparate(int arbResultId)
{
    for(int i=0; i<m_lstArbMgrInterface.size(); ++i)
    {
        IArbmgrInterface* lpInterface = m_lstArbMgrInterface[i];
        bool bRet = lpInterface->SwitchToSeparate();
        if (false == bRet)
        {
            LOGERROR(-250, "插件[" <<m_vecMgrPlugin[i].c_str() << "]切换到Separate失败！");
            AnswerToArb(arbResultId, ALARM_TYPE_ARB_NACK);
            return;
        }
        LOGSYSTEM("插件[" <<m_vecMgrPlugin[i].c_str() << "]切换到Separate成功！");
    }
    
    m_lpSendThread->Stop();
    m_lpRecvThread->Stop();
    m_CurrStatus = ACD_SEPARATE;
    AnswerToArb(arbResultId, ALARM_TYPE_ARB_ACK);
}

void CArbManager::AnswerToArb(int arbResultId, int ackResult)
{
    m_lpShmStatusStruct->m_byMachineStatus = m_CurrStatus;
    m_lpArbMsgRWThread->AnswerToArb(arbResultId,ackResult);
}


int CArbManager::GetAppSID()
{
   IRCfgObj *lpAppInfoObj = m_lpCoPub->GetChild(CO_APP_INFO);
   const char * lpID = lpAppInfoObj->GetAttrValue(CO_ATTR_APP_ID);
   return atoi(lpID);
}

string CArbManager::GetAppName()
{
   IRCfgObj *lpAppInfoObj = m_lpCoPub->GetChild(CO_APP_INFO);
   const char * lpValue = lpAppInfoObj->GetAttrValue(CO_ATTR_APP_NAME);
   return lpValue;
}

string CArbManager::GetAppFullName()
{
    IRCfgObj *lpAppInfoObj = m_lpCoPub->GetChild(CO_APP_INFO);
    const char * lpName = lpAppInfoObj->GetAttrValue(CO_ATTR_APP_NAME);
    const char * lpID = lpAppInfoObj->GetAttrValue(CO_ATTR_APP_ID);
    char appFullName[256] ;
    memset(appFullName, 0, sizeof(appFullName));
    sprintf(appFullName, "%s#%s", lpName, lpID);
    return appFullName;
}

void CArbManager::DealLoseHeart()
{
    if (ACD_SINGLE == m_CurrStatus)
    {   
        printf("Ignore Hear Lose\n");
        return;
    }
    
  //  AnswerToArb();
}

void CArbManager::DealRecvHeart()
{
    // 如果当前状态是single, 则需要告知arb，同步完成
    if (ACD_SINGLE == m_CurrStatus)
    {   
        LOGSYSTEM("接收到来自备机的心跳,发送事件[ALARM_TYPE_SYNC_COMPLETED]给仲裁");
        printf("接收到来自备机的心跳,发送事件[ALARM_TYPE_SYNC_COMPLETED]给仲裁\n"); 
        m_lpArbMsgRWThread->AnswerToArb(0, ALARM_TYPE_SYNC_COMPLETED); 
    }
}

bool CArbManager::GetManagerPlugin()
{
     ///读取配置信息
    if ( !m_lpConfig)
    {
        LOGERROR(-99, "[m_lpConfig]指针为空,获取管理的插件信息失败，请检查arbmgr的配置是否正确！");
        printf("[m_lpConfig]指针为空,获取管理的插件信息失败，请检查arbmgr的配置是否正确！\n");
        return false;
    }

    // 获取参数
    IRCfgObj *lpChild = m_lpConfig ->GetChild("args");
    if (NULL == lpChild)
    {
        LOGERROR(-99, "获取插件[arbmgr]的xml配置节点[args]失败,请检查配置文件是否正确！");
        printf("获取插件[arbmgr]的xml配置节点[args]失败,请检查配置文件是否正确！\n");
        return false;
    }

    //获取info字段信息
    const char *lpValue = lpChild ->GetAttrValue("monitor_plugins");
    if (NULL == lpValue)
    {
        LOGERROR(-99, "获取插件[arbmgr]的xml配置节点[args]中属性[monitor_plugins]失败,请检查配置文件是否正确！");
        printf("获取插件[arbmgr]的xml配置节点[args]中属性[monitor_plugins]失败,请检查配置文件是否正确！\n");
        return false;
    }    
    
    int j = 0;
    char pluginName[256];
    for(int i=0; i<strlen(lpValue); ++i)
    {
        if (';' != lpValue[i])
        {
            pluginName[j++] = lpValue[i];
            continue;
        }
        pluginName[j++] = '\0';
        m_vecMgrPlugin.push_back(pluginName);
        j = 0;
    }
    if (j>0)
    {
        pluginName[j++] = '\0';
        m_vecMgrPlugin.push_back(pluginName);
    } 
    return true;
}

int CArbManager::GetHeartRecvPort()
{
         ///读取配置信息
    if ( !m_lpConfig)
    {
        LOGERROR(-99, "[m_lpConfig]指针为空,获取管理的插件信息失败，请检查arbmgr的配置是否正确！");
        printf("[m_lpConfig]指针为空,获取管理的插件信息失败，请检查arbmgr的配置是否正确！\n");
        return -99;
    }

    // 获取参数
    IRCfgObj *lpChild = m_lpConfig ->GetChild("args");
    if (NULL == lpChild)
    {
        LOGERROR(-100, "获取插件[arbmgr]的xml配置节点[args]失败,请检查配置文件是否正确！");
        printf("获取插件[arbmgr]的xml配置节点[args]失败,请检查配置文件是否正确！\n");
        return -100;
    }

    //获取info字段信息
    const char *lpValue = lpChild ->GetAttrValue("heart_recv_port");
    if (NULL == lpValue)
    {
        LOGERROR(-101, "获取插件[arbmgr]的xml配置节点[args]中属性[heart_recv_port]失败,请检查配置文件是否正确！");
        printf("获取插件[arbmgr]的xml配置节点[args]中属性[heart_recv_port]失败,请检查配置文件是否正确！\n");
        return -101;
    }    
    
    return atoi(lpValue);
}

int CArbManager::GetHeartAnswerRecvPort()
{
    ///读取配置信息
    if ( !m_lpConfig)
    {
        LOGERROR(-99, "[m_lpConfig]指针为空,获取管理的插件信息失败，请检查arbmgr的配置是否正确！");
        printf("[m_lpConfig]指针为空,获取管理的插件信息失败，请检查arbmgr的配置是否正确！\n");
        return -99;
    }

    // 获取参数
    IRCfgObj *lpChild = m_lpConfig ->GetChild("args");
    if (NULL == lpChild)
    {
        LOGERROR(-100, "获取插件[arbmgr]的xml配置节点[args]失败,请检查配置文件是否正确！");
        printf("获取插件[arbmgr]的xml配置节点[args]失败,请检查配置文件是否正确！\n");
        return -100;
    }

    //获取info字段信息
    const char *lpValue = lpChild ->GetAttrValue("heart_answer_recv_port");
    if (NULL == lpValue)
    {
        LOGERROR(-101, "获取插件[arbmgr]的xml配置节点[args]中属性[heart_answer_recv_port]失败,请检查配置文件是否正确！");
        printf("获取插件[arbmgr]的xml配置节点[args]中属性[heart_answer_recv_port]失败,请检查配置文件是否正确！\n");
        return -101;
    }    
    
    return atoi(lpValue);
}

int CArbManager::GetHeartSendPort()
{
         ///读取配置信息
    if ( !m_lpConfig)
    {
        LOGERROR(-99, "[m_lpConfig]指针为空,获取管理的插件信息失败，请检查arbmgr的配置是否正确！");
        printf("[m_lpConfig]指针为空,获取管理的插件信息失败，请检查arbmgr的配置是否正确！\n");
        return -99;
    }

    // 获取参数
    IRCfgObj *lpChild = m_lpConfig ->GetChild("args");
    if (NULL == lpChild)
    {
        LOGERROR(-100, "获取插件[arbmgr]的xml配置节点[args]失败,请检查配置文件是否正确！");
        printf("获取插件[arbmgr]的xml配置节点[args]失败,请检查配置文件是否正确！\n");
        return -100;
    }

    //获取info字段信息
    const char *lpValue = lpChild ->GetAttrValue("send_port");
    if (NULL == lpValue)
    {
        LOGERROR(-101, "获取插件[arbmgr]的xml配置节点[args]中属性[send_port]失败,请检查配置文件是否正确！");
        printf("获取插件[arbmgr]的xml配置节点[args]中属性[send_port]失败,请检查配置文件是否正确！\n");
        return -101;
    }    
    
    return atoi(lpValue);
}

string CArbManager::GetBakNodeIpAddress()
{
    string baknodeIp = "";
    
    // 获取当前节点的IP
   IRCfgObj *lpAppInfoObj = m_lpCoPub->GetChild(CO_APP_INFO);
   const char * lpID = lpAppInfoObj->GetAttrValue(CO_ATTR_APP_ID);
   int id = atoi(lpID);   
   
   // 获取对面节点的IP
    IRCfgObj *lpChild = m_lpConfig ->GetChild("nodes");
    if (NULL == lpChild)
    {
        LOGERROR(-100, "获取插件[arbmgr]的xml配置节点[nodes]失败,请检查配置文件是否正确！");
        printf("获取插件[arbmgr]的xml配置节点[nodes]失败,请检查配置文件是否正确！\n");
        return baknodeIp;
    }

    //获取info字段信息
    IRCfgObj* lpNode = lpChild ->GetChild("node");
    if (NULL == lpNode)
    {
        LOGERROR(-101, "获取插件[arbmgr]的xml配置节点[nodes]的子节点[node]失败,请检查配置文件是否正确！");
        printf("获取插件[arbmgr]的xml配置节点[nodes]的子节点[node]失败,请检查配置文件是否正确！\n");
        return baknodeIp;
    }    
    
    while(lpNode)
    {
        const char * lpsid = lpNode->GetAttrValue("sid");
        if (NULL == lpsid)
        {
            LOGERROR(-101, "获取插件[arbmgr]的xml配置节点[nodes]的子节点[node]的属性中不存在sid,请检查配置文件是否正确！");
            printf("获取插件[arbmgr]的xml配置节点[nodes]的子节点[node]的属性中不存在sid,请检查配置文件是否正确！\n");
            return baknodeIp;
        }
        
        if (id != atoi(lpsid))
            return lpNode->GetAttrValue("ip");
        
        lpNode = lpNode->GetSibling();
    }
      
    return "";
}
        

