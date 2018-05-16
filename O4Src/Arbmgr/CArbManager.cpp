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

///�����ʼ������������������� ArbmgrInit()����
int CArbManager::OnInit(PFOnSetTimeOut pfOnSetTimeOut)
{
    int iRet = I_NONE;
    if (pfOnSetTimeOut) pfOnSetTimeOut(5000); //֪ͨ�����߱��������ܵĳ�ʱʱ��ms

    bool nRet = GetManagerPlugin();
    if (false == nRet)
    {
        LOGERROR(-99, "��ȡ��Ҫ��ع���Ĳ����Ϣʧ��!����ȷ����arbmgr�����monitor_plugins���Բ����������ڵ㣡");
        printf("��ȡ��Ҫ��ع���Ĳ����Ϣʧ��!����ȷ����arbmgr�����monitor_plugins���Բ����������ڵ㣡\n");
        return -99;
    }
    
    //---------------------------------------------------------
    // ��ʼ������
    int heartrecvport = GetHeartRecvPort();  // �������ն˿�
    if (heartrecvport < 0)
    {
        LOGERROR(-98, "��ȡ�������ն˿�ʧ��!����ȷ����arbmgr�����heart_recv_port���Բ����������ڵ㣡\n");
        printf("��ȡ�������ն˿�ʧ��!����ȷ����arbmgr�����heart_recv_port���Բ����������ڵ㣡\n");
        return -98;
    }
    
    int heartAnswerRecvPort = GetHeartAnswerRecvPort();
    if (heartAnswerRecvPort < 0)
    {
        LOGERROR(-98, "��ȡ�������ն˿�ʧ��!����ȷ����arbmgr�����heart_answer_recv_port���Բ����������ڵ㣡\n");
        printf("��ȡ�������ն˿�ʧ��!����ȷ����arbmgr�����heart_answer_recv_port���Բ����������ڵ㣡\n");
        return -98;
    }
    
 /*   int sendport = GetHeartSendPort();
    if (sendport < 0)
    {
        LOGERROR(-98, "��ȡ�������ն˿�ʧ��!����ȷ����arbmgr�����sendport���Բ����������ڵ㣡\n");
        printf("��ȡ�������ն˿�ʧ��!����ȷ����arbmgr�����sendport���Բ����������ڵ㣡\n");
        return -98;
    }*/
    
    string bakNodeip = GetBakNodeIpAddress();
    if ("" == bakNodeip)
    {
        printf("δ��⵽����������,ȷ��Ϊ����ģʽ�������������շ��̣߳�\n");
        LOGSYSTEM("δ��⵽����������,ȷ��Ϊ����ģʽ�������������շ��̣߳�");
    }    
    else
    {
        // �������������߳�
        m_lpSendThread = new CSendHeartThread(this, heartrecvport, heartAnswerRecvPort, bakNodeip);
        if (NULL == m_lpSendThread)
        {
            LOGERROR(-99, "���������̴߳���ʧ��,����ϵͳ��Դ�Ƿ����,�����������ڵ㣡");
            printf("���������̴߳���ʧ��,����ϵͳ��Դ�Ƿ����,�����������ڵ㣡\n");
            return -100;
        }
       
        // �������������߳�
        m_lpRecvThread = new CRecvHeartThread(this, heartrecvport, heartAnswerRecvPort, bakNodeip);
        if (NULL == m_lpSendThread)
        {
            LOGERROR(-99, "���������̴߳���ʧ��,����ϵͳ��Դ�Ƿ����,�����������ڵ㣡");
            printf("���������̴߳���ʧ��,����ϵͳ��Դ�Ƿ����,�����������ڵ㣡\n");
            return -101;
        }
    }
    
    //--------------------
    string appname = GetAppFullName();
    string shmName = appname + "_" + STATUS_SHARE_NAME;
    CSharedMem * lpShareMem = FBASE_NEW CSharedMem();
    m_lpShmStatusStruct = (ShmAcdStatus*)lpShareMem->Open(shmName.c_str());
    
    // �����ٲ���Ϣ�շ��߳�
    string arbResultQueueName = appname + "_" + ARB_RESULT_QUEUE;
    string eventQueueName = appname + "_" + EVENT_QUEUE; 
    m_lpArbMsgRWThread = new CArbMsgRWThread(this, eventQueueName , arbResultQueueName);
    if (NULL == m_lpArbMsgRWThread)
    {
        LOGERROR(-99, "�ٲ���Ϣ�շ��̴߳���ʧ��,����ϵͳ��Դ�Ƿ����,�����������ڵ㣡");
        printf("�ٲ���Ϣ�շ��̴߳���ʧ��,����ϵͳ��Դ�Ƿ����,�����������ڵ㣡\n");
        return -102;
    }
    
    // ����Ϊ��ʼ��״̬
    m_CurrStatus = ACD_INIT;
    m_lpShmStatusStruct->m_byMachineStatus = ACD_INIT;
    LOGSYSTEM("���ýڵ�״̬[INIT]���");
    return iRet;
}

//�����¼�����
void CArbManager::OnStart(PFOnSetTimeOut pfOnSetTimeOut)
{
    if (pfOnSetTimeOut) pfOnSetTimeOut(5000); //֪ͨ�����߱��������ܵĳ�ʱʱ��ms
    
    if (m_vecMgrPlugin.size() == 0)
    {
        LOGSYSTEM("û��������Ҫ��صĲ��,���������");
        return;
    }
    
    // ��ȡ��Ҫ��صĲ�����ٲ��¼�����ӿڵ�ָ��
    for(int i=0; i<m_vecMgrPlugin.size(); ++i)
    {
        string pluginName = m_vecMgrPlugin[i];
        IArbmgrInterface* lpInterface = m_lpIoC->GetPluginArbMgrInterface(pluginName.c_str());
        if (NULL == lpInterface)
        {
            LOGERROR(-99, "��ȡ���["<< pluginName <<"]�ٲ��¼�������ʧ��,�ڵ�����ʧ��,���������Ƿ���ȷ,������ϵ���������");
            printf("��ȡ���[%s]�ٲ��¼�������ʧ��,�ڵ�����ʧ��,���������Ƿ���ȷ,������ϵ���������\n", pluginName.c_str());
            continue;
        }
        m_lstArbMgrInterface.push_back(lpInterface);
    }
    
    // �����ٲ���Ϣ�շ��߳�
     if (NULL == m_lpArbMsgRWThread)
     {
         LOGERROR(-99, "�ٲ���Ϣ�շ��߳�û�д���,�ڵ�ֹͣ����!");
         printf("�ٲ���Ϣ�շ��߳�û�д���,�ڵ�ֹͣ����!\n");
         return;
     }
     m_lpArbMsgRWThread->Start();  
}

//ֹͣ�¼�����
void CArbManager::OnStop(PFOnSetTimeOut pfOnSetTimeOut)
{
    if (pfOnSetTimeOut) pfOnSetTimeOut(5000); //֪ͨ�����߱��������ܵĳ�ʱʱ��ms
    ///#todo ������ֹͣ�¼�������룬����ֹͣ����߳�
    //#{


    //#}
}

//�˳��¼�����
void CArbManager::OnExit(PFOnSetTimeOut pfOnSetTimeOut)
{
    if (pfOnSetTimeOut) pfOnSetTimeOut(5000); //֪ͨ�����߱��������ܵĳ�ʱʱ��ms
    ///#todo �������˳��¼�������룬�����ͷ���Դ
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
    m_lpConfig = NULL;        //������������ͨ����ת��������ʼ��
    m_lpCoPub = NULL;         //������������ͨ����ת��������ʼ��

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
// �����ٲû���Ϣ
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
            LOGERROR(-250, "���[" <<m_vecMgrPlugin[i].c_str() << "]�л���Prepareʧ�ܣ�");
            AnswerToArb(arbResultId, ALARM_TYPE_ARB_NACK);
            return;
        }
        LOGSYSTEM("���[" <<m_vecMgrPlugin[i].c_str() << "]�л���Prepare�ɹ���");
    }
    LOGSYSTEM("�л���PREPARE״̬,��ʼ�������������̣߳�");
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
            LOGERROR(-250, "���[" <<m_vecMgrPlugin[i].c_str() << "]�л���Inactiveʧ�ܣ�");
            AnswerToArb(arbResultId, ALARM_TYPE_ARB_NACK);
            return;
        }
        LOGSYSTEM("���[" <<m_vecMgrPlugin[i].c_str() << "]�л���Inactive�ɹ���");
    }
    
    m_CurrStatus = ACD_INACTIVE;
    LOGSYSTEM("�л���INACTIVE״̬��");
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
            LOGERROR(-250, "���[" <<m_vecMgrPlugin[i].c_str() << "]�л���Singleʧ�ܣ�");
            AnswerToArb(arbResultId, ALARM_TYPE_ARB_NACK);
            return;
        }
        LOGSYSTEM("���[" <<m_vecMgrPlugin[i].c_str() << "]�л���Single�ɹ���");
    }
    
    if (ACD_INIT == m_CurrStatus)
    {
        LOGSYSTEM("��״̬[ACD_INIT]�л���[ACD_SINGLE]״̬,�������������̣߳�");
        m_lpRecvThread->Start();
        m_CurrStatus = ACD_SINGLE;
        AnswerToArb(arbResultId, ALARM_TYPE_ARB_ACK);
    }
    else if (ACD_INACTIVE == m_CurrStatus)
    {
        LOGSYSTEM("��״̬[ACD_INACTIVE]�л���[ACD_SINGLE]״̬,��ͣ���������̣߳���ʼ�������������̣߳�");
        m_lpSendThread->Pause();
        m_lpRecvThread->Start();
        m_CurrStatus = ACD_SINGLE;
        AnswerToArb(arbResultId, ALARM_TYPE_ARB_ACK);
    }
    else if (ACD_ACTIVE == m_CurrStatus)
    {
        LOGSYSTEM("��״̬[ACD_ACTIVE]�л���[ACD_SINGLE]״̬��");
        m_CurrStatus = ACD_SINGLE;
        AnswerToArb(arbResultId, ALARM_TYPE_ARB_ACK);
    }
    else
    {   
        LOGSYSTEM("��״̬["<< m_CurrStatus << "]�л���[ACD_SINGLE]״̬��");
        // ��ʶ��Ķ��� 
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
            LOGERROR(-250, "���[" <<m_vecMgrPlugin[i].c_str() << "]�л���Activeʧ�ܣ�");
            AnswerToArb(arbResultId, ALARM_TYPE_ARB_NACK);
            return;
        }
        LOGSYSTEM("���[" <<m_vecMgrPlugin[i].c_str() << "]�л���Active�ɹ���");
    }
    
    if (ACD_SINGLE == m_CurrStatus)
    {
        LOGSYSTEM("��״̬[ACD_SINGLE]�л���[ACD_ACTIVE]״̬��");
        m_CurrStatus = ACD_ACTIVE;
        AnswerToArb(arbResultId, ALARM_TYPE_ARB_ACK);
    }
    else if (ACD_INACTIVE == m_CurrStatus)
    {
        LOGSYSTEM("��״̬[ACD_INACTIVE]�л���[ACD_ACTIVE]״̬����ͣ���������̣߳��������������̣߳�");
        m_lpSendThread->Pause();
        m_lpRecvThread->Start();
        m_CurrStatus = ACD_ACTIVE;
        AnswerToArb(arbResultId, ALARM_TYPE_ARB_ACK);
    }
    else
    {
        LOGSYSTEM("��״̬[]�л���[ACD_ACTIVE]״̬��");
          // ��ʶ��Ķ��� 
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
            LOGERROR(-250, "���[" <<m_vecMgrPlugin[i].c_str() << "]�л���Separateʧ�ܣ�");
            AnswerToArb(arbResultId, ALARM_TYPE_ARB_NACK);
            return;
        }
        LOGSYSTEM("���[" <<m_vecMgrPlugin[i].c_str() << "]�л���Separate�ɹ���");
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
    // �����ǰ״̬��single, ����Ҫ��֪arb��ͬ�����
    if (ACD_SINGLE == m_CurrStatus)
    {   
        LOGSYSTEM("���յ����Ա���������,�����¼�[ALARM_TYPE_SYNC_COMPLETED]���ٲ�");
        printf("���յ����Ա���������,�����¼�[ALARM_TYPE_SYNC_COMPLETED]���ٲ�\n"); 
        m_lpArbMsgRWThread->AnswerToArb(0, ALARM_TYPE_SYNC_COMPLETED); 
    }
}

bool CArbManager::GetManagerPlugin()
{
     ///��ȡ������Ϣ
    if ( !m_lpConfig)
    {
        LOGERROR(-99, "[m_lpConfig]ָ��Ϊ��,��ȡ����Ĳ����Ϣʧ�ܣ�����arbmgr�������Ƿ���ȷ��");
        printf("[m_lpConfig]ָ��Ϊ��,��ȡ����Ĳ����Ϣʧ�ܣ�����arbmgr�������Ƿ���ȷ��\n");
        return false;
    }

    // ��ȡ����
    IRCfgObj *lpChild = m_lpConfig ->GetChild("args");
    if (NULL == lpChild)
    {
        LOGERROR(-99, "��ȡ���[arbmgr]��xml���ýڵ�[args]ʧ��,���������ļ��Ƿ���ȷ��");
        printf("��ȡ���[arbmgr]��xml���ýڵ�[args]ʧ��,���������ļ��Ƿ���ȷ��\n");
        return false;
    }

    //��ȡinfo�ֶ���Ϣ
    const char *lpValue = lpChild ->GetAttrValue("monitor_plugins");
    if (NULL == lpValue)
    {
        LOGERROR(-99, "��ȡ���[arbmgr]��xml���ýڵ�[args]������[monitor_plugins]ʧ��,���������ļ��Ƿ���ȷ��");
        printf("��ȡ���[arbmgr]��xml���ýڵ�[args]������[monitor_plugins]ʧ��,���������ļ��Ƿ���ȷ��\n");
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
         ///��ȡ������Ϣ
    if ( !m_lpConfig)
    {
        LOGERROR(-99, "[m_lpConfig]ָ��Ϊ��,��ȡ����Ĳ����Ϣʧ�ܣ�����arbmgr�������Ƿ���ȷ��");
        printf("[m_lpConfig]ָ��Ϊ��,��ȡ����Ĳ����Ϣʧ�ܣ�����arbmgr�������Ƿ���ȷ��\n");
        return -99;
    }

    // ��ȡ����
    IRCfgObj *lpChild = m_lpConfig ->GetChild("args");
    if (NULL == lpChild)
    {
        LOGERROR(-100, "��ȡ���[arbmgr]��xml���ýڵ�[args]ʧ��,���������ļ��Ƿ���ȷ��");
        printf("��ȡ���[arbmgr]��xml���ýڵ�[args]ʧ��,���������ļ��Ƿ���ȷ��\n");
        return -100;
    }

    //��ȡinfo�ֶ���Ϣ
    const char *lpValue = lpChild ->GetAttrValue("heart_recv_port");
    if (NULL == lpValue)
    {
        LOGERROR(-101, "��ȡ���[arbmgr]��xml���ýڵ�[args]������[heart_recv_port]ʧ��,���������ļ��Ƿ���ȷ��");
        printf("��ȡ���[arbmgr]��xml���ýڵ�[args]������[heart_recv_port]ʧ��,���������ļ��Ƿ���ȷ��\n");
        return -101;
    }    
    
    return atoi(lpValue);
}

int CArbManager::GetHeartAnswerRecvPort()
{
    ///��ȡ������Ϣ
    if ( !m_lpConfig)
    {
        LOGERROR(-99, "[m_lpConfig]ָ��Ϊ��,��ȡ����Ĳ����Ϣʧ�ܣ�����arbmgr�������Ƿ���ȷ��");
        printf("[m_lpConfig]ָ��Ϊ��,��ȡ����Ĳ����Ϣʧ�ܣ�����arbmgr�������Ƿ���ȷ��\n");
        return -99;
    }

    // ��ȡ����
    IRCfgObj *lpChild = m_lpConfig ->GetChild("args");
    if (NULL == lpChild)
    {
        LOGERROR(-100, "��ȡ���[arbmgr]��xml���ýڵ�[args]ʧ��,���������ļ��Ƿ���ȷ��");
        printf("��ȡ���[arbmgr]��xml���ýڵ�[args]ʧ��,���������ļ��Ƿ���ȷ��\n");
        return -100;
    }

    //��ȡinfo�ֶ���Ϣ
    const char *lpValue = lpChild ->GetAttrValue("heart_answer_recv_port");
    if (NULL == lpValue)
    {
        LOGERROR(-101, "��ȡ���[arbmgr]��xml���ýڵ�[args]������[heart_answer_recv_port]ʧ��,���������ļ��Ƿ���ȷ��");
        printf("��ȡ���[arbmgr]��xml���ýڵ�[args]������[heart_answer_recv_port]ʧ��,���������ļ��Ƿ���ȷ��\n");
        return -101;
    }    
    
    return atoi(lpValue);
}

int CArbManager::GetHeartSendPort()
{
         ///��ȡ������Ϣ
    if ( !m_lpConfig)
    {
        LOGERROR(-99, "[m_lpConfig]ָ��Ϊ��,��ȡ����Ĳ����Ϣʧ�ܣ�����arbmgr�������Ƿ���ȷ��");
        printf("[m_lpConfig]ָ��Ϊ��,��ȡ����Ĳ����Ϣʧ�ܣ�����arbmgr�������Ƿ���ȷ��\n");
        return -99;
    }

    // ��ȡ����
    IRCfgObj *lpChild = m_lpConfig ->GetChild("args");
    if (NULL == lpChild)
    {
        LOGERROR(-100, "��ȡ���[arbmgr]��xml���ýڵ�[args]ʧ��,���������ļ��Ƿ���ȷ��");
        printf("��ȡ���[arbmgr]��xml���ýڵ�[args]ʧ��,���������ļ��Ƿ���ȷ��\n");
        return -100;
    }

    //��ȡinfo�ֶ���Ϣ
    const char *lpValue = lpChild ->GetAttrValue("send_port");
    if (NULL == lpValue)
    {
        LOGERROR(-101, "��ȡ���[arbmgr]��xml���ýڵ�[args]������[send_port]ʧ��,���������ļ��Ƿ���ȷ��");
        printf("��ȡ���[arbmgr]��xml���ýڵ�[args]������[send_port]ʧ��,���������ļ��Ƿ���ȷ��\n");
        return -101;
    }    
    
    return atoi(lpValue);
}

string CArbManager::GetBakNodeIpAddress()
{
    string baknodeIp = "";
    
    // ��ȡ��ǰ�ڵ��IP
   IRCfgObj *lpAppInfoObj = m_lpCoPub->GetChild(CO_APP_INFO);
   const char * lpID = lpAppInfoObj->GetAttrValue(CO_ATTR_APP_ID);
   int id = atoi(lpID);   
   
   // ��ȡ����ڵ��IP
    IRCfgObj *lpChild = m_lpConfig ->GetChild("nodes");
    if (NULL == lpChild)
    {
        LOGERROR(-100, "��ȡ���[arbmgr]��xml���ýڵ�[nodes]ʧ��,���������ļ��Ƿ���ȷ��");
        printf("��ȡ���[arbmgr]��xml���ýڵ�[nodes]ʧ��,���������ļ��Ƿ���ȷ��\n");
        return baknodeIp;
    }

    //��ȡinfo�ֶ���Ϣ
    IRCfgObj* lpNode = lpChild ->GetChild("node");
    if (NULL == lpNode)
    {
        LOGERROR(-101, "��ȡ���[arbmgr]��xml���ýڵ�[nodes]���ӽڵ�[node]ʧ��,���������ļ��Ƿ���ȷ��");
        printf("��ȡ���[arbmgr]��xml���ýڵ�[nodes]���ӽڵ�[node]ʧ��,���������ļ��Ƿ���ȷ��\n");
        return baknodeIp;
    }    
    
    while(lpNode)
    {
        const char * lpsid = lpNode->GetAttrValue("sid");
        if (NULL == lpsid)
        {
            LOGERROR(-101, "��ȡ���[arbmgr]��xml���ýڵ�[nodes]���ӽڵ�[node]�������в�����sid,���������ļ��Ƿ���ȷ��");
            printf("��ȡ���[arbmgr]��xml���ýڵ�[nodes]���ӽڵ�[node]�������в�����sid,���������ļ��Ƿ���ȷ��\n");
            return baknodeIp;
        }
        
        if (id != atoi(lpsid))
            return lpNode->GetAttrValue("ip");
        
        lpNode = lpNode->GetSibling();
    }
      
    return "";
}
        

