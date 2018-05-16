#include "o4InitManager.h"
#include "syncThread.h"

CO4InitManager::CO4InitManager(IAS2Context * lpContext, ICommAgent* lpCommAgent, IF2UnPacker * lpInUnPacker, IF2Packer * lpOutPacker, char* pErrPathInfo)
{
    m_lpContext = lpContext;
    m_lpCommAgent = lpCommAgent;
    m_lpInUnPacker = lpInUnPacker;
    m_lpOutPacker = lpOutPacker;
    m_nInitDate = 0;
    m_nInitMode = 1;
    m_sDockSystem = '1';
    m_nErrNo = 0;
    m_lpDBConn = NULL;
    strcpy(m_sErrInfo, "");
    strcpy(m_sErrPathInfo, pErrPathInfo);
    strcpy(m_sRunTaskLst, " ");
    strcpy(m_sErrorMessage, " ");

}

CO4InitManager::~CO4InitManager()
{
    if (m_lpDBConn)
        m_lpDBConn->toFree();
    m_lpContext = NULL;
    m_lpCommAgent = NULL;
    m_lpInUnPacker = NULL;
    m_lpOutPacker = NULL;
    //    for (unsigned int i = 0; i < m_vecMgrTask.size(); ++i)
    //    {
    //        vector<CSyncTask*> vecTask = m_vecMgrTask[i];
    //        for (unsigned int j = 0; j < vecTask.size(); ++j)
    //        {
    //            CSyncTask* lpTask = (CSyncTask*) vecTask[j];
    //            if (lpTask != NULL)
    //                delete lpTask;
    //        }
    //    }
}

int CO4InitManager::GetErrNo()
{
    return m_nErrNo;
}

char* CO4InitManager::GetErrInfo()
{
    return m_sErrInfo;
}

char* CO4InitManager::GetErrPathInfo()
{
    return m_sErrPathInfo;
}

void CO4InitManager::SetErrInfo(int nErrNo, const char* pErrInfo)
{
    m_nErrNo = nErrNo;
    strcpy(m_sErrInfo, pErrInfo);
    DLOGERROR(m_lpContext,m_nErrNo, m_sErrInfo);
}

void CO4InitManager::SetErrPathInfo(const char* pErrPathInfo)
{
    strcpy(m_sErrPathInfo, pErrPathInfo);
}

// �ճ�ʼ��������

bool CO4InitManager::Init()
{
    // ��ʼ��ģʽ���ճ�ʼ��
    m_nInitMode = 1;
    
    if (!InitDBConnection())
        return false;
    // ��ȡ������ϵͳ״̬�����û�жԽ��ⲿ��ϵͳ,����qs��hg��ϵͳ��δ����,��ֱ���˳���ʼ������
    if (false == GetAllSubSysStatus())
    {
        return false;
    }
    if (1 != m_subSysStatus.jc_subsys_status)
    {
       DLOGWARNING(m_lpContext, "δ���û���������ϵͳ,�˳��ճ�ʼ������,�ճ�ʼ������");
        return true;
    }
    if ((1 != m_subSysStatus.hg_subsys_status) && (1 != m_subSysStatus.qs_subsys_status))
    {
        DLOGWARNING(m_lpContext, "�Ϲ���ϵͳ��������ϵͳ��δ����,�ճ�ʼ��������");
        return true;
    }

    // ͬ��ǰ����
    if (!doPreInit())
    {
        return false;
    }

    // ����ͬ��
    if (!doInit())
    {
        return false;
    }

    //ͬ������
    if (!doNextInit())
    {
        return false;
    }
    return true;
}

// ��ʽ����

bool CO4InitManager::Clear()
{
    // ��ʼ��ģʽ����ʽ����
    m_nInitMode = 3;
    if (!InitDBConnection())
        return false;

    // ��ȡ������ϵͳ״̬�����û�жԽ��ⲿ��ϵͳ,����qs��hg��ϵͳ��δ����,��ֱ���˳���ʼ������
    if (false == GetAllSubSysStatus())
    {
        return false;
    }
    if (1 != m_subSysStatus.jc_subsys_status)
    {
      DLOGWARNING(m_lpContext, "δ���û���������ϵͳ���˳���ʽ�������̣���ʽ�������");
        return true;
    }
    if ((1 != m_subSysStatus.hg_subsys_status) && (1 != m_subSysStatus.qs_subsys_status))
    {
        DLOGWARNING(m_lpContext, "�Ϲ���ϵͳ��������ϵͳ��δ���ã��ճ�ʼ��������");
        return true;
    }
    if (1 != IsOpenUFT())
    {
		DLOGWARNING(m_lpContext, "���ٽ���δ���ã���ʽ��ʼ������");
        return false;
		
    }
    // ͬ��ǰ����
    if (!doPreInit())
    {
        return false;
    }

    // ����ͬ��
    if (!doInit())
    {
        return false;
    }

    //ͬ������
    if (!doNextInit())
    {
        return false;
    }

    return true;
}

// �ж��Ƿ���Ҫ���к�����ʼ������

bool CO4InitManager::IsCanInit()
{
    return true;
}

bool CO4InitManager::InitDBConnection()
{
    m_lpDBConn = m_lpContext->GetDBConnection(O3DB);
    if (!m_lpDBConn)
    {
        SetErrInfo(-110, "��ȡORACLE����ʧ�ܣ�����JC_AR�Ƿ������������ݿ⣡");
        return false;
    }
    return true;
}

bool CO4InitManager::doPreInit()
{
    //�ж�������ʹ�û���ֻ��UFTʹ�ã����������ճ�ʼ��
    if ((1 == m_subSysStatus.hg_subsys_status) && (1 == m_nInitMode) && (1 == IsOpenUFT()))
    {
        //����hg���ܺ�2415002[AS_�첽���_�鲥������]
        if (false == ClearMulticastNo())
        {
            strcat(m_sErrorMessage, "�첽���_�鲥������ʧ��!");
            SetErrInfo(-103, m_sErrorMessage);
            return false;
        }
    }
    // ɾ����¼�� jc_tbasedellog
    if(!DeleteBasedellog())
    {
    	strcat(m_sErrorMessage, "ɾ��jc_tbasedellog����ʧ��");
		SetErrInfo(-103, m_sErrorMessage);
		return false;
    }
    // �˶��������⣬��ֹ�ճ���ʱ�����ռ�Ĳ���
    if (!CancelSubscribeTopics())
    {
        strcat(m_sErrorMessage, "ȡ�������ռ��������ʧ��");
        SetErrInfo(-103, m_sErrorMessage);
        return false;
    }
    // ��ȡ�Խ���ϵͳ
    if (!GetDockSystem())
    {
        strcat(m_sErrorMessage, "��ȡ�Խ���ϵͳʧ��");
        SetErrInfo(-104, m_sErrorMessage);
        return false;
    }
    // ��ȡ�ճ�ʼ�������б��������ȼ�����
    if (!GetSyncTaskList())
    {
        strcat(m_sErrorMessage, "��ѯ�����б�ʧ��!");
        SetErrInfo(-102, m_sErrorMessage);
        return false;
    }
    GroupSyncTask();
    return true;
}

bool CO4InitManager::doInit()
{
    // ����ͬ��
    for (unsigned int i = 0; i < m_vecMgrTask.size(); ++i)
    {
        time_t tStart, tEnd;
        tStart = time(NULL);
        vector<CSyncTask*> vecTask = m_vecMgrTask[i];

        for (unsigned int j = 0; j < vecTask.size(); ++j)
        {
            CSyncTask* lpTask = (CSyncTask*) vecTask[j];
            // ��ȡ�����߳�
            CSyncThread* lpThread = NULL;
            while (NULL == lpThread)
            {
                lpThread = CThreadPool::GetInstance().GetIdleThread();
                if (NULL == lpThread)
                {
                    DLOGDEBUG(m_lpContext, "ͬ���߳���ռ�����޷���ȡ�����̣߳���ǰæµ�߳�����" << CThreadPool::GetInstance().GetBusyThreadCount() << ")����ǰͬ���ӿ�(" << GetRunningTasks() << ")");
                    sleep(1);
                }
            }
            // ����������󣬲����߳̿�ʼ����
            lpThread->SetThreadTask((void *) lpTask);
            lpThread->SetContext(m_lpContext);
            lpThread->SetCommAgent(m_lpCommAgent);
            lpThread->Start();
            // У�鵱ǰ�Ѿ��������ͬ�������Ƿ��нӿ�ͬ�������������˳�����
            if (IsHaveSyncErr())
            {
                return false;
            }
        }

        // ����Ƿ����ж���ɣ� ������;�Ѿ����������
        while (true)
        {
            bool bAllFinished = IsAllFinished();
            bool bHaveSyncErr = IsHaveSyncErr();
            if (true == bHaveSyncErr) // ����Ѿ��������˳�ͬ��
            {
                return false;
            }

            if (bAllFinished && (!bHaveSyncErr)) //��������������ɣ�����û�д����� 
            {
                break;
            }
            DLOGDEBUG(m_lpContext, "1���ȴ�ʣ��ͬ���������(" << GetRunningTasks() << ")");
            sleep(1);
        }

        tEnd = time(NULL);
        DLOGEVENT(m_lpContext,"--------------------------------����ͬ���ڡ�" << i << "������ͬ����ɣ���ʱ��" << difftime(tEnd, tStart) << "s��--------------------------------");
    }

    return true;
}

bool CO4InitManager::IsHaveSyncErr()
{
    for (unsigned int i = 0; i < m_vecMgrTask.size(); ++i)
    {
        vector<CSyncTask*> vecTask = m_vecMgrTask[i];
        for (unsigned int j = 0; j < vecTask.size(); ++j)
        {
            CSyncTask* lpTask = (CSyncTask*) vecTask[j];
            if (lpTask->IsFinished() && lpTask->GetErrNo())
            {
                SetErrInfo(lpTask->GetErrNo(), lpTask->GetErrInfo());
                SetErrPathInfo(lpTask->GetErrPathInfo());
                return true;
            }
        }
    }
    return false;
}

bool CO4InitManager::IsAllFinished()
{
    for (unsigned int i = 0; i < m_vecMgrTask.size(); ++i)
    {
        vector<CSyncTask*> vecTask = m_vecMgrTask[i];
        for (unsigned int j = 0; j < vecTask.size(); ++j)
        {
            CSyncTask* lpTask = (CSyncTask*) vecTask[j];
            if (lpTask->IsNew())
            {
                continue;
            }
            if (!lpTask->IsFinished())
            {
                return false;
            }
        }
    }

    return true;
}

bool CO4InitManager::doNextInit()
{
    //������ȡUFT����״̬�жϵĴ���IsOpenUFT()
    if ((1 == m_subSysStatus.hg_subsys_status) && (1 == IsOpenUFT()))
    {
		/* У�鷽��������Ӱ������¿��ǣ��������Ƴ�
        if (1 == m_nInitMode)
        {
            if (!ValidUFTData())
            {
                return false;
            }                
        }*/

        if ((1 == m_nInitMode) || (3 == m_nInitMode) || (4 == m_nInitMode))
        {
            if (!MultiCast())
            {
                return false;
            }  
        }        
    }
        
    if (!SubsribeTopics())
    {
        strcat(m_sErrorMessage, "�����ռ��������ʧ��");
        SetErrInfo(-106, m_sErrorMessage);
        return false;
    }

    return true;
}

// ���ٽ����Ƿ���

int CO4InitManager::IsOpenUFT()
{
    if (NULL == m_lpDBConn)
    {
        SetErrInfo(-110, "��ȡO3���ݿ�����ʧ��");
        return false;
    }

    char sSql[1024] = {0};
    sprintf(sSql, "select vc_value from tsysparameter where l_serial_no = 60962"); // �ж�ϵͳ����60962, 1��ʾ���ٽ��׿�����2��ʾ���ٽ��׹ر�
    IF2ResultSet *lpResultValue = m_lpDBConn->executeQuery(sSql);
    if (NULL == lpResultValue)
    {
        DLOGWARNING(m_lpContext, "��ѯo3��tsysparameter�ĶԽ�ϵͳ����ʧ�ܣ�" << m_lpDBConn->getErrInfo());
        return false;
    }
    int nStatus = atoi(lpResultValue->GetStr("vc_value"));
    lpResultValue->Destroy();

    return nStatus;
}

bool CO4InitManager::ValidUFTData()
{
    // ������
    IF2Packer *lpInPack = m_lpContext->GetF2PackSvr()->GetPacker(2);
    IF2Packer *lpOutPack = m_lpContext->GetF2PackSvr()->GetPacker(2);
    lpInPack->BeginPack();
    lpInPack->EndPack();

    IF2UnPacker *lpOutUnPack = NULL;
    lpOutPack->BeginPack();
    int iRet = CallService(2615431, lpInPack, lpOutPack, 30000);
    lpOutPack->EndPack();
    lpOutUnPack = lpOutPack->UnPack();

    if (lpOutUnPack)
    {
        lpOutUnPack->Release();
    }
    if (lpOutPack)
    {
        free(lpOutPack->GetPackBuf());
        lpOutPack->Release();
    }
    if (lpInPack)
    {
        free(lpInPack->GetPackBuf());
        lpInPack->Release();
    }

    return iRet == 0 ? true : false;
}

int CO4InitManager::GetInitDate()
{
    if (m_nInitDate != 0)
    {
        return m_nInitDate;
    }

    int iRet = 0;
    // ������
    IF2Packer *lpInPack = m_lpContext->GetF2PackSvr()->GetPacker(2);
    IF2Packer *lpOutPack = m_lpContext->GetF2PackSvr()->GetPacker(2);
    lpInPack->BeginPack();
    lpInPack->AddField("error_pathinfo", 'S', 4000);
    lpInPack->AddStr(m_sErrPathInfo);
    lpInPack->EndPack();

    IF2UnPacker *lpOutUnPack = NULL;
    lpOutPack->BeginPack();
    iRet = CallService(2617005, lpInPack, lpOutPack, 5000);
    lpOutPack->EndPack();
    if (iRet != 0)
    {
        strcat(m_sErrorMessage, "��ȡϵͳ��ʼ������ʧ�ܣ�");
        SetErrInfo(-101, m_sErrorMessage);
        return -1;
    }
    lpOutUnPack = lpOutPack->UnPack();

    m_nInitDate = lpOutUnPack->GetInt("init_date");

    if (lpOutUnPack)
    {
        lpOutUnPack->Release();
    }

    if (lpOutPack)
    {
        free(lpOutPack->GetPackBuf());
        lpOutPack->Release();
    }

    if (lpInPack)
    {
        free(lpInPack->GetPackBuf());
        lpInPack->Release();
    }
    return m_nInitDate;

}

bool CO4InitManager::GetDockSystem()
{
    if (NULL == m_lpDBConn)
    {
        SetErrInfo(-110, "��ȡO3���ݿ�����ʧ��");
        return false;
    }

    char sSql[1024] = {0};
    sprintf(sSql, "select vc_value from tsysparameter where l_serial_no = 61022"); // �ж�ϵͳ����61022, ���ֵΪ7��Խ�pb������Խ�O32
    IF2ResultSet *lpResultValue = m_lpDBConn->executeQuery(sSql);
    if (NULL == lpResultValue)
    {
        DLOGWARNING(m_lpContext, "��ѯo3��tsysparameter�ĶԽ�ϵͳ����ʧ�ܣ�" << m_lpDBConn->getErrInfo());
        return false;
    }
    char cSysParameterValue = lpResultValue->GetChar("vc_value");
    m_sDockSystem = ('7' == cSysParameterValue ? '2' : '1');
	DLOGDEBUG(m_lpContext, "�����Խ���ϵͳ����Ϊ" << m_sDockSystem << "��1��ʾO3,2��ʾPB");
    lpResultValue->Destroy();
    return true;
}

// ��JC_TRcInterfaceCfg���л�ȡ�ճ�ʼ�������б�

bool CO4InitManager::GetSyncTaskList()
{
	DLOGEVENT(m_lpContext,"��ʼ��ѯ�����б�");

    if (NULL == m_lpDBConn)
    {
        SetErrInfo(-110, "��ȡO3���ݿ�����ʧ��");
        return false;
    }

    char sSql[1024] = {0};
    if (4 == m_nInitMode)
    {
    	sprintf(sSql, "select * from jc_trcinterfacecfg where (available_range = '1' or available_range = '3') and (available_product='0' or available_product='%c') order by priority_level", m_sDockSystem == '1' ? '1' : '2');
    }
    else
    {	// �������ʽ���㣬��ȡavailable_rangeΪ2�ı������ʽ����
        // �������ȫ����ȡavailable_rangeΪ1�ı�����ճ�
    	sprintf(sSql, "select * from jc_trcinterfacecfg where available_range = '%c' and (available_product='0' or available_product='%c') order by priority_level", m_nInitMode == 3 ? '2' : '1', m_sDockSystem == '1' ? '1' : '2');
    }

    IF2ResultSet *lpResult = m_lpDBConn->executeQuery(sSql);
    if (NULL == lpResult)
    {
        DLOGWARNING(m_lpContext, "��ѯ��jc_trcinterfacecfgʧ�ܣ�" << m_lpDBConn->getErrInfo());
        return false;
    }

    //�������ؽ����
    for (; !lpResult->IsEOF(); lpResult->Next())
    {
        char sTableName[128] = {0};
        strcpy(sTableName, lpResult->GetStr("table_name"));
        char cUseFlag = lpResult->GetChar("use_flag");
        if ('0' == cUseFlag)
        {
			DLOGEVENT(m_lpContext,"��" << sTableName << "��δ����ͬ��");
            continue;
        }       

        int nPriorityLevel = lpResult->GetInt("priority_level");
        char cAvailableProduct = lpResult->GetChar("available_product");
		char sTopicName[128] = {0};
		strcpy(sTopicName, lpResult->GetStr("topic_name"));

        DLOGDEBUG(m_lpContext, "��" << sTableName << "��ͬ�����ȼ���" << nPriorityLevel << "��");

        // �½����������ӵ��б���
        CSyncTask* pTask = new CSyncTask(m_sErrPathInfo);
        pTask->SetSyncTableInfo(new CSyncTableInfo(sTableName, nPriorityLevel, cAvailableProduct, lpResult->GetStr("prc_name"), sTopicName));
        m_vecTask.push_back(pTask);
    } /*lint !e429*/

    // ��¼��־
    DLOGEVENT(m_lpContext,"��ѯ��" << m_vecTask.size() << "�����õ��ճ�����");

    lpResult->Destroy();
    return true;
}


// ������������ȼ����鵽��ά������

void CO4InitManager::GroupSyncTask()
{
    // �����ݿ��ȡ���ȼ���ʱ���Ѿ�����
    int nTmpLevel = -1; // ���ȼ�
    vector<CSyncTask*> vecTask;
    for (unsigned int i = 0; i < m_vecTask.size(); ++i)
    {
        CSyncTask* lpTask = m_vecTask[i];
        int curLevel = lpTask->GetPriorityLevel();
        if (curLevel > nTmpLevel)
        {
            nTmpLevel = curLevel;
            if (vecTask.size() > 0)
            {
                m_vecMgrTask.push_back(vecTask);
            }
            vecTask.clear();
        }
        vecTask.push_back(lpTask);
    }
    if (!vecTask.empty())
    {
        m_vecMgrTask.push_back(vecTask);
    }

    //��ӡ��־���������ϸ
    for (unsigned int i = 0; i < m_vecMgrTask.size(); ++i)
    {
        vecTask = m_vecMgrTask[i];
        char sTableList[10240] = {0};
        int nPriorityLevel = -1;

        for (unsigned int j = 0; j < vecTask.size(); ++j)
        {
            CSyncTask* lpTask = (CSyncTask*) vecTask[j];
            CSyncTableInfo* lpSyncInfo = lpTask->GetSyncTableInfo();
            if (j == 0)
            {
                sprintf(sTableList, "%s", lpSyncInfo->GetTableName());
            } else
            {
                sprintf(sTableList, "%s,%s", sTableList, lpSyncInfo->GetTableName());
            }
            nPriorityLevel = lpTask->GetPriorityLevel();
        }
        DLOGDEBUG(m_lpContext, "�������ȼ���" << nPriorityLevel << "����������" << sTableList); /*lint !e539*/
    }
}

int CO4InitManager::CallService(int FuncNo, IF2Packer* inPack, IF2Packer* outPack, int TimeOut)
{
    if (NULL == m_lpContext)
        return -100;

    // ����ESB�����
    IESBMessage* lpRequestESB = NULL;
    lpRequestESB = m_lpContext->GetESBMsgFactory()->GetESBMsg();
    if (NULL == lpRequestESB)
    {
        SetErrInfo(-105, "ESB���������ʧ��!");
        return -105;
    }
    lpRequestESB->Prepare(REQUEST_PACKET, FuncNo);
    lpRequestESB->GetItem(TAG_MESSAGE_BODY)->SetRawData(inPack->GetPackBuf(), inPack->GetPackLen()); //ҵ���帴�Ƶ���Ϣ��

    //�����ӷ���,��������
    IESBMessage* lpAnswerESB = NULL;
    int iRet = m_lpContext->CallSubService(lpRequestESB, &lpAnswerESB, TimeOut);
    if ((iRet != 0) || (NULL == lpAnswerESB))
    {
        switch (iRet)
        {
            case -1:
            {
                sprintf(m_sErrorMessage, "��������쳣:[%d]����ʧ��,������Ϣ�ѱ��ͷ�", FuncNo);
                break;
            }
            case -2:
            {
                sprintf(m_sErrorMessage, "��������쳣:[%d]���ó�ʱ", FuncNo);
                break;
            }
            default:
            {
                sprintf(m_sErrorMessage, "��������쳣:[%d]δ֪����", FuncNo);
            }
        };
        //sprintf(m_sErrorMessage, "��������쳣: %s", m_sErrorMessage);
        SetErrInfo(iRet, m_sErrorMessage);
        return iRet;
    }

    // ���ESB���Ƿ����
    iRet = lpAnswerESB->GetItem(TAG_ERROR_NO)->GetInt();
    if (iRet)
    {
        sprintf(m_sErrorMessage, "ESB�����,��������쳣:%s", lpAnswerESB->GetItem(TAG_ERROR_INFO)->GetString());
        SetErrInfo(lpAnswerESB->GetItem(TAG_ERROR_NO)->GetInt(), m_sErrorMessage);
        char lpErrPathInfo[101] = {0};
        sprintf(lpErrPathInfo, "->F%d()", FuncNo);
        strcat(m_sErrPathInfo, lpErrPathInfo);
        return iRet;
    }

    // ���ҵ����Ƿ����
    void *lpData = NULL;
    int nLen = 0;
    iRet = lpAnswerESB->GetItem(TAG_RETURN_CODE)->GetInt();
    lpData = (void*) lpAnswerESB->GetItem(TAG_MESSAGE_BODY)->GetRawData(&nLen);
    if ((NULL == lpData) || (nLen <= 0))
    {
        lpAnswerESB->Release();
        sprintf(m_sErrorMessage, "��������쳣:%s", lpAnswerESB->GetItem(TAG_ERROR_INFO)->GetString());
        SetErrInfo(lpAnswerESB->GetItem(TAG_ERROR_NO)->GetInt(), m_sErrorMessage);
        return iRet;
    }

    //����ҵ�����
    IF2UnPacker* unPacker = m_lpContext->GetF2PackSvr()->GetUnPacker(lpData, nLen);
    if (NULL == unPacker)
    {
        lpAnswerESB->Release();
        sprintf(m_sErrorMessage, "[%d]����ҵ�����ʧ��!", FuncNo);
        SetErrInfo(-106, m_sErrorMessage);
        return -106;
    }

    if (iRet != 0)
    {
        const char *lpErrNo = unPacker->GetStr("error_no");
        const char *lpErrInfo = unPacker->GetStr("error_info");
        if (unPacker->GetStr("error_pathinfo") == NULL)
        {
            char lpErrPathInfo[4001] = {0};
            sprintf(lpErrPathInfo, "->F%d()", FuncNo);
            strcat(m_sErrPathInfo, lpErrPathInfo);
        } else
        {
            SetErrPathInfo(unPacker->GetStr("error_pathinfo"));
        }

        sprintf(m_sErrorMessage, "[%d]��������쳣:%s", FuncNo, lpErrInfo);

        SetErrInfo(atoi(lpErrNo), m_sErrorMessage);
        unPacker->Release();
        lpAnswerESB->Release();
        return iRet;
    }

    //����������ڴ浽���δ����
    PackResultSet(unPacker, outPack);
    unPacker->Release();

    //�ͷ�ESB�ڴ���Դ
    lpAnswerESB->Release();
    return 0;
}

bool CO4InitManager::GetAllSubSysStatus()
{
    m_subSysStatus.jc_subsys_status = GetSysStatus(999);
    if (-1 == m_subSysStatus.jc_subsys_status)
    {
        return false;
    }

    m_subSysStatus.hg_subsys_status = GetSysStatus(34);
    if (-1 == m_subSysStatus.hg_subsys_status)
    {
        return false;
    }

    m_subSysStatus.qs_subsys_status = GetSysStatus(38);
    if (-1 == m_subSysStatus.qs_subsys_status)
    {
        return false;
    }

    return true;
}

// ��ȡ��ϵͳ״̬�� ʧ�ܷ���-1

int CO4InitManager::GetSysStatus(int sysNo)
{
    if (NULL == m_lpDBConn)
    {
        SetErrInfo(-110, "��ȡO3���ݿ�����ʧ��");
        return false;
    }

    char sSql[1024] = {0};
    sprintf(sSql, "select subsys_status from jc_tsubsysteminfo where subsys_no = %d", sysNo); // �ж�ϵͳ����61022, ���ֵΪ7��Խ�pb������Խ�O32
    IF2ResultSet *lpResultValue = m_lpDBConn->executeQuery(sSql);
    if (NULL == lpResultValue)
    {
        return -1;
    }
    int nStatus = lpResultValue->GetChar("subsys_status") - '0';
    lpResultValue->Destroy();
    return nStatus;
}

//�첽���_�鲥������

bool CO4InitManager::ClearMulticastNo()
{
	DLOGEVENT(m_lpContext,"��ʼ�첽���_�鲥������");

    int iRet = 0;
    // ������
    IF2Packer *lpInPack = m_lpContext->GetF2PackSvr()->GetPacker(2);
    IF2Packer *lpOutPack = m_lpContext->GetF2PackSvr()->GetPacker(2);
    lpInPack->BeginPack();
    lpInPack->AddField("error_pathinfo", 'S', 4000);
    lpInPack->AddStr(m_sErrPathInfo);
    lpInPack->EndPack();

    lpOutPack->BeginPack();
    iRet = CallService(2415002, lpInPack, lpOutPack, 180000);
    lpOutPack->EndPack();
    if (iRet != 0)
    {
        return false;
    }

    if (lpOutPack)
    {
        free(lpOutPack->GetPackBuf());
        lpOutPack->Release();
    }

    if (lpInPack)
    {
        free(lpInPack->GetPackBuf());
        lpInPack->Release();
    }
	DLOGEVENT(m_lpContext,"�첽���_�鲥���������");
    return true;
}

bool CO4InitManager::SubsribeTopics()
{
    // �������ʽ���㣬����ȡ�����ĵ�����
    if (3 == m_nInitMode)
    {
        return true;
    }
	DLOGEVENT(m_lpContext,"��ʼ�����ռ��������");

    if (NULL == m_lpDBConn)
    {
        SetErrInfo(-110, "��ȡO3���ݿ�����ʧ��");
        return false;
    }
    IF2ResultSet *lpResultSet = NULL;
    char sQuerySql[256] = {0};
    sprintf(sQuerySql, "select topic_name from jc_trcinterfacecfg where available_range = '1' and use_flag = '1' and  topic_name is not null");
    lpResultSet = m_lpDBConn->executeQuery(sQuerySql);

    char sTopicTname[128] = {0};
    IF2Packer * lpSubscribePacker = m_lpContext->GetF2PackSvr()->GetPacker(2);
    while (!lpResultSet->IsEOF())
    {
        memset(sTopicTname, 0, sizeof (sTopicTname));
        strcpy(sTopicTname, lpResultSet->GetStr("topic_name"));
        if ((strcmp(sTopicTname, " ")==0) || sTopicTname[0]=='\0')
        {
            lpResultSet->Next();
            continue;
        }
        //�����Ϣ��
        lpSubscribePacker->BeginPack();
        lpSubscribePacker->AddField("topic_name");
        lpSubscribePacker->AddField("is_from_now");
        lpSubscribePacker->AddField("is_sub_replace");
        lpSubscribePacker->AddStr(sTopicTname);
        lpSubscribePacker->AddChar('1');
        lpSubscribePacker->AddChar('0');
        lpSubscribePacker->EndPack();

        int nRet = SubscribeTopic(m_lpContext, lpSubscribePacker->UnPack());
        if (nRet)
        {
            DLOGERROR(m_lpContext,-110, "�������⡾" << sTopicTname << "��ʧ��");
            lpResultSet->Destroy();
            return false;
        }
		DLOGDEBUG(m_lpContext, "�������⡾" << sTopicTname << "���ɹ�");
        lpResultSet->Next();
    }
    
    if (lpSubscribePacker)
    {
            free(lpSubscribePacker->GetPackBuf());
            lpSubscribePacker->Release();
    }
    if (lpResultSet)
        lpResultSet->Destroy();
	DLOGEVENT(m_lpContext,"�����ռ�����������");
    return true;
}

bool CO4InitManager::CancelSubscribeTopics()
{
    // �������ʽ���㣬����ȡ�����ĵ����⣬ҹ����������Ҫȡ����������
    if (3 == m_nInitMode || 4 == m_nInitMode )
    {
        return true;
    }


	DLOGEVENT(m_lpContext,"��ʼȡ�������ռ��������");
    if (NULL == m_lpDBConn)
    {
        SetErrInfo(-110, "��ȡO3���ݿ�����ʧ��");
        return false;
    }
    IF2ResultSet *lpResultSet = NULL;
    char sQuerySql[256] = {0};
    sprintf(sQuerySql, "select topic_name from jc_trcinterfacecfg where available_range = '1' and use_flag = '1' and  topic_name is not null");
    lpResultSet = m_lpDBConn->executeQuery(sQuerySql);

    char sTopicTname[128] = {0};
    IF2Packer * lpSubscribePacker = m_lpContext->GetF2PackSvr()->GetPacker(2);
    while (!lpResultSet->IsEOF())
    {
        memset(sTopicTname, 0, sizeof (sTopicTname));
        strcpy(sTopicTname, lpResultSet->GetStr("topic_name"));
        if ((strcmp(sTopicTname, " ")==0) || sTopicTname[0]=='\0')
        {
            lpResultSet->Next();
            continue;
        }
        //�����Ϣ��
        lpSubscribePacker->BeginPack();
        lpSubscribePacker->AddField("topic_name");
        lpSubscribePacker->AddStr(sTopicTname);
        lpSubscribePacker->EndPack();

        CancelSubscribe(m_lpContext, lpSubscribePacker->UnPack());
		DLOGDEBUG(m_lpContext, "ȡ����������" << sTopicTname << "���");
        lpResultSet->Next();
    }
    
    if (lpSubscribePacker)
    {
            free(lpSubscribePacker->GetPackBuf());
            lpSubscribePacker->Release();
    }
    if (lpResultSet)
        lpResultSet->Destroy();


	DLOGEVENT(m_lpContext,"ȡ�������ռ�����������");
    return true;
}

bool CO4InitManager::MultiCast()
{
	DLOGEVENT(m_lpContext,"��ʼ�����鲥");

    int iRet = 0;
    int nInitDate = GetInitDate();
    int nFuncId = 0;
    // ������
    IF2Packer *lpInPack = m_lpContext->GetF2PackSvr()->GetPacker(2);
    IF2Packer *lpOutPack = m_lpContext->GetF2PackSvr()->GetPacker(2);
    IF2UnPacker *lpOutUnPack = NULL;
    lpInPack->BeginPack();
    lpInPack->AddField("error_pathinfo", 'S', 4000);
    lpInPack->AddField("init_date", 'I');
    lpInPack->AddStr(m_sErrPathInfo);
    lpInPack->AddInt(nInitDate);
    lpInPack->EndPack();

    if (1 == m_nInitMode)
    {
        nFuncId = 615010;
    }
    else if (3 == m_nInitMode)
    {
        nFuncId = 615014;
    }
    else if (4 == m_nInitMode)
	{
		nFuncId = 615015;
	}
    lpOutPack->BeginPack();
    iRet = CallService(nFuncId, lpInPack, lpOutPack, 900000);
    lpOutPack->EndPack();
    lpOutUnPack = lpOutPack->UnPack();
    if (iRet != 0)
    {
        return false;
    }

    m_nErrNo = 0;
    strcpy(m_sErrInfo, lpOutUnPack->GetStr("error_info"));

    if (lpOutPack)
    {
        free(lpOutPack->GetPackBuf());
        lpOutPack->Release();
    }

    if (lpInPack)
    {
        free(lpInPack->GetPackBuf());
        lpInPack->Release();
    }

	DLOGEVENT(m_lpContext,"�����鲥���");
    return true;
}

bool CO4InitManager::ExportDataToCsv()
{
	DLOGEVENT(m_lpContext,"��ʼ�������ݵ�CSV");

    int iRet = 0;
    int nInitDate = GetInitDate();
    // ������
    IF2Packer *lpInPack = m_lpContext->GetF2PackSvr()->GetPacker(2);
    IF2Packer *lpOutPack = m_lpContext->GetF2PackSvr()->GetPacker(2);
    lpInPack->BeginPack();
    lpInPack->AddField("error_pathinfo", 'S', 4000);
    lpInPack->AddField("init_date", 'I');
    lpInPack->AddStr(m_sErrPathInfo);
    lpInPack->AddInt(nInitDate);
    lpInPack->EndPack();

    lpOutPack->BeginPack();
    iRet = CallService(615003, lpInPack, lpOutPack, 600000);
    lpOutPack->EndPack();
    if (iRet != 0)
    {
        return false;
    }

    if (lpOutPack)
    {
        free(lpOutPack->GetPackBuf());
        lpOutPack->Release();
    }

    if (lpInPack)
    {
        free(lpInPack->GetPackBuf());
        lpInPack->Release();
    }

	DLOGEVENT(m_lpContext,"�������ݵ�CSV���");
    return true;
}


//O4����ͬ��

bool CO4InitManager::Sync()
{
    // ��ʼ��ģʽ���ճ�ǰ���
    m_nInitMode = 2;

    if (!InitDBConnection())
        return false;
    // ��ȡ������ϵͳ״̬�����û�жԽ��ⲿ��ϵͳ,����qs��hg��ϵͳ��δ����,��ֱ���˳���ʼ������
    if (false == GetAllSubSysStatus())
    {
        return false;
    }
    if (1 != m_subSysStatus.jc_subsys_status)
    {
        DLOGWARNING(m_lpContext, "δ���û���������ϵͳ���˳��ճ�ʼ�����̣��ճ�ʼ������");
        return true;
    }

    // �жϵ�ǰ�Ƿ���Ҫ��ʼ��
    if (!IsCanInit())
    {
        return false;
    }

    // ͬ��ǰ����
    if (!doPreInit())
    {
        return false;
    }

    // ����ͬ��
    if (!doInit())
    {
        return false;
    }

    //ͬ������
    if (!doNextInit())
    {
        return false;
    }
    return true;
}

//ҹ����������ͬ��
bool CO4InitManager::UpgradeSync()
{
    // ��ʼ��ģʽ��ҹ���������ݳ�ʼ��
    m_nInitMode = 4;

    if (!InitDBConnection())
        return false;
    // ��ȡ������ϵͳ״̬�����û�жԽ��ⲿ��ϵͳ,����qs��hg��ϵͳ��δ����,��ֱ���˳���ʼ������
    if (false == GetAllSubSysStatus())
    {
        return false;
    }
    if (1 != m_subSysStatus.jc_subsys_status)
    {
        DLOGWARNING(m_lpContext, "δ���û���������ϵͳ���˳�ҹ��������ʼ������");
        return true;
    }

    // ͬ��ǰ����
    if (!doPreInit())
    {
        return false;
    }

    // ����ͬ��
    if (!doInit())
    {
        return false;
    }

    //ͬ������
    if (!doNextInit())
    {
        return false;
    }
    return true;
}


char* CO4InitManager::GetRunningTasks()
{
    char sTableName[128] = "";
    int nLength = 0;
    strcpy(m_sRunTaskLst, "");
    for (unsigned int i = 0; i < m_vecMgrTask.size(); ++i)
    {
        vector<CSyncTask*> vecTask = m_vecMgrTask[i];
        for (unsigned int j = 0; j < vecTask.size(); ++j)
        {
            CSyncTask* lpTask = (CSyncTask*) vecTask[j];
            if (lpTask->IsAssigned())
            {
                sprintf(sTableName, "%s,", lpTask->GetSyncTableInfo()->GetTableName());
                strcat(m_sRunTaskLst, sTableName);
            }
        }
    }
    nLength = strlen(m_sRunTaskLst);
    if (nLength > 0)
    {
        m_sRunTaskLst[nLength - 1] = '\0';
    } else
    {
        m_sRunTaskLst[0] = '\0';
    }
    return m_sRunTaskLst;
}
bool CO4InitManager::DeleteBasedellog()
{
	if (NULL == m_lpDBConn)
	{
		SetErrInfo(-110, "��ȡO3���ݿ�����ʧ��");
		return false;
	}
	DLOGDEBUG(m_lpContext,"ɾ��jc_tbassdellog������");
	char sSql[256] = {"delete from jc_tbasedellog"};
	int nRet = m_lpDBConn->executeUpdate(sSql);
	if(0 != nRet)
	{
		DLOGWARNING(m_lpContext,"error_no"<<m_lpDBConn->getErrNo()<<":info:"<<m_lpDBConn->getErrInfo());
		return false;
	}
	DLOGDEBUG(m_lpContext,"jc_tbassdellog������ɾ���ɹ�");
	return true;
}
