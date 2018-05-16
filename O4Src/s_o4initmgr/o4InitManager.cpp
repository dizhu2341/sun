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

// 日初始化主流程

bool CO4InitManager::Init()
{
    // 初始化模式是日初始化
    m_nInitMode = 1;
    
    if (!InitDBConnection())
        return false;
    // 获取所有子系统状态，如果没有对接外部子系统,或者qs和hg子系统都未启用,则直接退出初始化流程
    if (false == GetAllSubSysStatus())
    {
        return false;
    }
    if (1 != m_subSysStatus.jc_subsys_status)
    {
       DLOGWARNING(m_lpContext, "未启用基础接入子系统,退出日初始化流程,日初始化结束");
        return true;
    }
    if ((1 != m_subSysStatus.hg_subsys_status) && (1 != m_subSysStatus.qs_subsys_status))
    {
        DLOGWARNING(m_lpContext, "合规子系统和清算子系统均未启用,日初始化结束。");
        return true;
    }

    // 同步前处理
    if (!doPreInit())
    {
        return false;
    }

    // 数据同步
    if (!doInit())
    {
        return false;
    }

    //同步后处理
    if (!doNextInit())
    {
        return false;
    }
    return true;
}

// 正式清算

bool CO4InitManager::Clear()
{
    // 初始化模式是正式清算
    m_nInitMode = 3;
    if (!InitDBConnection())
        return false;

    // 获取所有子系统状态，如果没有对接外部子系统,或者qs和hg子系统都未启用,则直接退出初始化流程
    if (false == GetAllSubSysStatus())
    {
        return false;
    }
    if (1 != m_subSysStatus.jc_subsys_status)
    {
      DLOGWARNING(m_lpContext, "未启用基础接入子系统，退出正式清算流程，正式清算结束");
        return true;
    }
    if ((1 != m_subSysStatus.hg_subsys_status) && (1 != m_subSysStatus.qs_subsys_status))
    {
        DLOGWARNING(m_lpContext, "合规子系统和清算子系统均未启用，日初始化结束。");
        return true;
    }
    if (1 != IsOpenUFT())
    {
		DLOGWARNING(m_lpContext, "极速交易未启用，正式初始化结束");
        return false;
		
    }
    // 同步前处理
    if (!doPreInit())
    {
        return false;
    }

    // 数据同步
    if (!doInit())
    {
        return false;
    }

    //同步后处理
    if (!doNextInit())
    {
        return false;
    }

    return true;
}

// 判断是否需要进行后续初始化动作

bool CO4InitManager::IsCanInit()
{
    return true;
}

bool CO4InitManager::InitDBConnection()
{
    m_lpDBConn = m_lpContext->GetDBConnection(O3DB);
    if (!m_lpDBConn)
    {
        SetErrInfo(-110, "获取ORACLE连接失败！请检查JC_AR是否正常连接数据库！");
        return false;
    }
    return true;
}

bool CO4InitManager::doPreInit()
{
    //判断是清算使用还是只有UFT使用，且做整个日初始化
    if ((1 == m_subSysStatus.hg_subsys_status) && (1 == m_nInitMode) && (1 == IsOpenUFT()))
    {
        //调用hg功能号2415002[AS_异步落库_组播序号清空]
        if (false == ClearMulticastNo())
        {
            strcat(m_sErrorMessage, "异步落库_组播序号清空失败!");
            SetErrInfo(-103, m_sErrorMessage);
            return false;
        }
    }
    // 删除记录表 jc_tbasedellog
    if(!DeleteBasedellog())
    {
    	strcat(m_sErrorMessage, "删除jc_tbasedellog数据失败");
		SetErrInfo(-103, m_sErrorMessage);
		return false;
    }
    // 退订所有主题，防止日初的时候有日间的操作
    if (!CancelSubscribeTopics())
    {
        strcat(m_sErrorMessage, "取消订阅日间更新主题失败");
        SetErrInfo(-103, m_sErrorMessage);
        return false;
    }
    // 获取对接子系统
    if (!GetDockSystem())
    {
        strcat(m_sErrorMessage, "获取对接子系统失败");
        SetErrInfo(-104, m_sErrorMessage);
        return false;
    }
    // 获取日初始化任务列表，并按优先级分组
    if (!GetSyncTaskList())
    {
        strcat(m_sErrorMessage, "查询任务列表失败!");
        SetErrInfo(-102, m_sErrorMessage);
        return false;
    }
    GroupSyncTask();
    return true;
}

bool CO4InitManager::doInit()
{
    // 进行同步
    for (unsigned int i = 0; i < m_vecMgrTask.size(); ++i)
    {
        time_t tStart, tEnd;
        tStart = time(NULL);
        vector<CSyncTask*> vecTask = m_vecMgrTask[i];

        for (unsigned int j = 0; j < vecTask.size(); ++j)
        {
            CSyncTask* lpTask = (CSyncTask*) vecTask[j];
            // 获取空闲线程
            CSyncThread* lpThread = NULL;
            while (NULL == lpThread)
            {
                lpThread = CThreadPool::GetInstance().GetIdleThread();
                if (NULL == lpThread)
                {
                    DLOGDEBUG(m_lpContext, "同步线程已占满，无法获取空闲线程，当前忙碌线程数（" << CThreadPool::GetInstance().GetBusyThreadCount() << ")，当前同步接口(" << GetRunningTasks() << ")");
                    sleep(1);
                }
            }
            // 设置任务对象，并让线程开始工作
            lpThread->SetThreadTask((void *) lpTask);
            lpThread->SetContext(m_lpContext);
            lpThread->SetCommAgent(m_lpCommAgent);
            lpThread->Start();
            // 校验当前已经分配出的同步任务，是否有接口同步出错，出错则退出函数
            if (IsHaveSyncErr())
            {
                return false;
            }
        }

        // 检查是否所有都完成， 或者中途已经有任务出错
        while (true)
        {
            bool bAllFinished = IsAllFinished();
            bool bHaveSyncErr = IsHaveSyncErr();
            if (true == bHaveSyncErr) // 如果已经出错则退出同步
            {
                return false;
            }

            if (bAllFinished && (!bHaveSyncErr)) //假如所有任务都完成，并且没有错误则 
            {
                break;
            }
            DLOGDEBUG(m_lpContext, "1秒后等待剩余同步任务完成(" << GetRunningTasks() << ")");
            sleep(1);
        }

        tEnd = time(NULL);
        DLOGEVENT(m_lpContext,"--------------------------------数据同步第【" << i << "】批次同步完成，耗时【" << difftime(tEnd, tStart) << "s】--------------------------------");
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
    //新增获取UFT开启状态判断的代码IsOpenUFT()
    if ((1 == m_subSysStatus.hg_subsys_status) && (1 == IsOpenUFT()))
    {
		/* 校验方案对性能影响大，重新考虑，这里先移除
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
        strcat(m_sErrorMessage, "订阅日间更新主题失败");
        SetErrInfo(-106, m_sErrorMessage);
        return false;
    }

    return true;
}

// 极速交易是否开启

int CO4InitManager::IsOpenUFT()
{
    if (NULL == m_lpDBConn)
    {
        SetErrInfo(-110, "获取O3数据库连接失败");
        return false;
    }

    char sSql[1024] = {0};
    sprintf(sSql, "select vc_value from tsysparameter where l_serial_no = 60962"); // 判断系统参数60962, 1表示极速交易开启，2表示极速交易关闭
    IF2ResultSet *lpResultValue = m_lpDBConn->executeQuery(sSql);
    if (NULL == lpResultValue)
    {
        DLOGWARNING(m_lpContext, "查询o3表tsysparameter的对接系统类型失败，" << m_lpDBConn->getErrInfo());
        return false;
    }
    int nStatus = atoi(lpResultValue->GetStr("vc_value"));
    lpResultValue->Destroy();

    return nStatus;
}

bool CO4InitManager::ValidUFTData()
{
    // 打包入参
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
    // 打包入参
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
        strcat(m_sErrorMessage, "获取系统初始化日期失败！");
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
        SetErrInfo(-110, "获取O3数据库连接失败");
        return false;
    }

    char sSql[1024] = {0};
    sprintf(sSql, "select vc_value from tsysparameter where l_serial_no = 61022"); // 判断系统参数61022, 如果值为7则对接pb，否则对接O32
    IF2ResultSet *lpResultValue = m_lpDBConn->executeQuery(sSql);
    if (NULL == lpResultValue)
    {
        DLOGWARNING(m_lpContext, "查询o3表tsysparameter的对接系统类型失败，" << m_lpDBConn->getErrInfo());
        return false;
    }
    char cSysParameterValue = lpResultValue->GetChar("vc_value");
    m_sDockSystem = ('7' == cSysParameterValue ? '2' : '1');
	DLOGDEBUG(m_lpContext, "基础对接子系统类型为" << m_sDockSystem << "，1表示O3,2表示PB");
    lpResultValue->Destroy();
    return true;
}

// 从JC_TRcInterfaceCfg表中获取日初始化任务列表

bool CO4InitManager::GetSyncTaskList()
{
	DLOGEVENT(m_lpContext,"开始查询任务列表");

    if (NULL == m_lpDBConn)
    {
        SetErrInfo(-110, "获取O3数据库连接失败");
        return false;
    }

    char sSql[1024] = {0};
    if (4 == m_nInitMode)
    {
    	sprintf(sSql, "select * from jc_trcinterfacecfg where (available_range = '1' or available_range = '3') and (available_product='0' or available_product='%c') order by priority_level", m_sDockSystem == '1' ? '1' : '2');
    }
    else
    {	// 如果是正式清算，获取available_range为2的表进行正式清算
        // 其他情况全部获取available_range为1的表进行日初
    	sprintf(sSql, "select * from jc_trcinterfacecfg where available_range = '%c' and (available_product='0' or available_product='%c') order by priority_level", m_nInitMode == 3 ? '2' : '1', m_sDockSystem == '1' ? '1' : '2');
    }

    IF2ResultSet *lpResult = m_lpDBConn->executeQuery(sSql);
    if (NULL == lpResult)
    {
        DLOGWARNING(m_lpContext, "查询表jc_trcinterfacecfg失败，" << m_lpDBConn->getErrInfo());
        return false;
    }

    //解析返回结果集
    for (; !lpResult->IsEOF(); lpResult->Next())
    {
        char sTableName[128] = {0};
        strcpy(sTableName, lpResult->GetStr("table_name"));
        char cUseFlag = lpResult->GetChar("use_flag");
        if ('0' == cUseFlag)
        {
			DLOGEVENT(m_lpContext,"表【" << sTableName << "】未启用同步");
            continue;
        }       

        int nPriorityLevel = lpResult->GetInt("priority_level");
        char cAvailableProduct = lpResult->GetChar("available_product");
		char sTopicName[128] = {0};
		strcpy(sTopicName, lpResult->GetStr("topic_name"));

        DLOGDEBUG(m_lpContext, "表【" << sTableName << "】同步优先级【" << nPriorityLevel << "】");

        // 新建任务对象，添加到列表中
        CSyncTask* pTask = new CSyncTask(m_sErrPathInfo);
        pTask->SetSyncTableInfo(new CSyncTableInfo(sTableName, nPriorityLevel, cAvailableProduct, lpResult->GetStr("prc_name"), sTopicName));
        m_vecTask.push_back(pTask);
    } /*lint !e429*/

    // 记录日志
    DLOGEVENT(m_lpContext,"查询到" << m_vecTask.size() << "个启用的日初任务");

    lpResult->Destroy();
    return true;
}


// 根据任务的优先级分组到二维数组中

void CO4InitManager::GroupSyncTask()
{
    // 从数据库获取优先级的时候，已经排序
    int nTmpLevel = -1; // 优先级
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

    //打印日志输出任务明细
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
        DLOGDEBUG(m_lpContext, "任务优先级【" << nPriorityLevel << "】的任务有" << sTableList); /*lint !e539*/
    }
}

int CO4InitManager::CallService(int FuncNo, IF2Packer* inPack, IF2Packer* outPack, int TimeOut)
{
    if (NULL == m_lpContext)
        return -100;

    // 设置ESB请求包
    IESBMessage* lpRequestESB = NULL;
    lpRequestESB = m_lpContext->GetESBMsgFactory()->GetESBMsg();
    if (NULL == lpRequestESB)
    {
        SetErrInfo(-105, "ESB请求包申请失败!");
        return -105;
    }
    lpRequestESB->Prepare(REQUEST_PACKET, FuncNo);
    lpRequestESB->GetItem(TAG_MESSAGE_BODY)->SetRawData(inPack->GetPackBuf(), inPack->GetPackLen()); //业务体复制到消息中

    //调用子服务,发送请求
    IESBMessage* lpAnswerESB = NULL;
    int iRet = m_lpContext->CallSubService(lpRequestESB, &lpAnswerESB, TimeOut);
    if ((iRet != 0) || (NULL == lpAnswerESB))
    {
        switch (iRet)
        {
            case -1:
            {
                sprintf(m_sErrorMessage, "服务调用异常:[%d]发送失败,请求消息已被释放", FuncNo);
                break;
            }
            case -2:
            {
                sprintf(m_sErrorMessage, "服务调用异常:[%d]调用超时", FuncNo);
                break;
            }
            default:
            {
                sprintf(m_sErrorMessage, "服务调用异常:[%d]未知错误", FuncNo);
            }
        };
        //sprintf(m_sErrorMessage, "服务调用异常: %s", m_sErrorMessage);
        SetErrInfo(iRet, m_sErrorMessage);
        return iRet;
    }

    // 检查ESB层是否出错
    iRet = lpAnswerESB->GetItem(TAG_ERROR_NO)->GetInt();
    if (iRet)
    {
        sprintf(m_sErrorMessage, "ESB层错误,服务调用异常:%s", lpAnswerESB->GetItem(TAG_ERROR_INFO)->GetString());
        SetErrInfo(lpAnswerESB->GetItem(TAG_ERROR_NO)->GetInt(), m_sErrorMessage);
        char lpErrPathInfo[101] = {0};
        sprintf(lpErrPathInfo, "->F%d()", FuncNo);
        strcat(m_sErrPathInfo, lpErrPathInfo);
        return iRet;
    }

    // 检查业务层是否出错
    void *lpData = NULL;
    int nLen = 0;
    iRet = lpAnswerESB->GetItem(TAG_RETURN_CODE)->GetInt();
    lpData = (void*) lpAnswerESB->GetItem(TAG_MESSAGE_BODY)->GetRawData(&nLen);
    if ((NULL == lpData) || (nLen <= 0))
    {
        lpAnswerESB->Release();
        sprintf(m_sErrorMessage, "服务调用异常:%s", lpAnswerESB->GetItem(TAG_ERROR_INFO)->GetString());
        SetErrInfo(lpAnswerESB->GetItem(TAG_ERROR_NO)->GetInt(), m_sErrorMessage);
        return iRet;
    }

    //解析业务包体
    IF2UnPacker* unPacker = m_lpContext->GetF2PackSvr()->GetUnPacker(lpData, nLen);
    if (NULL == unPacker)
    {
        lpAnswerESB->Release();
        sprintf(m_sErrorMessage, "[%d]解析业务包体失败!", FuncNo);
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

        sprintf(m_sErrorMessage, "[%d]服务调用异常:%s", FuncNo, lpErrInfo);

        SetErrInfo(atoi(lpErrNo), m_sErrorMessage);
        unPacker->Release();
        lpAnswerESB->Release();
        return iRet;
    }

    //拷贝结果集内存到出参打包器
    PackResultSet(unPacker, outPack);
    unPacker->Release();

    //释放ESB内存资源
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

// 获取子系统状态， 失败返回-1

int CO4InitManager::GetSysStatus(int sysNo)
{
    if (NULL == m_lpDBConn)
    {
        SetErrInfo(-110, "获取O3数据库连接失败");
        return false;
    }

    char sSql[1024] = {0};
    sprintf(sSql, "select subsys_status from jc_tsubsysteminfo where subsys_no = %d", sysNo); // 判断系统参数61022, 如果值为7则对接pb，否则对接O32
    IF2ResultSet *lpResultValue = m_lpDBConn->executeQuery(sSql);
    if (NULL == lpResultValue)
    {
        return -1;
    }
    int nStatus = lpResultValue->GetChar("subsys_status") - '0';
    lpResultValue->Destroy();
    return nStatus;
}

//异步落库_组播序号清空

bool CO4InitManager::ClearMulticastNo()
{
	DLOGEVENT(m_lpContext,"开始异步落库_组播序号清空");

    int iRet = 0;
    // 打包入参
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
	DLOGEVENT(m_lpContext,"异步落库_组播序号清空完成");
    return true;
}

bool CO4InitManager::SubsribeTopics()
{
    // 如果是正式清算，不会取消订阅的主题
    if (3 == m_nInitMode)
    {
        return true;
    }
	DLOGEVENT(m_lpContext,"开始订阅日间更新主题");

    if (NULL == m_lpDBConn)
    {
        SetErrInfo(-110, "获取O3数据库连接失败");
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
        //打包消息包
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
            DLOGERROR(m_lpContext,-110, "订阅主题【" << sTopicTname << "】失败");
            lpResultSet->Destroy();
            return false;
        }
		DLOGDEBUG(m_lpContext, "订阅主题【" << sTopicTname << "】成功");
        lpResultSet->Next();
    }
    
    if (lpSubscribePacker)
    {
            free(lpSubscribePacker->GetPackBuf());
            lpSubscribePacker->Release();
    }
    if (lpResultSet)
        lpResultSet->Destroy();
	DLOGEVENT(m_lpContext,"订阅日间更新主题完成");
    return true;
}

bool CO4InitManager::CancelSubscribeTopics()
{
    // 如果是正式清算，不会取消订阅的主题，夜盘升级不需要取消订阅主题
    if (3 == m_nInitMode || 4 == m_nInitMode )
    {
        return true;
    }


	DLOGEVENT(m_lpContext,"开始取消订阅日间更新主题");
    if (NULL == m_lpDBConn)
    {
        SetErrInfo(-110, "获取O3数据库连接失败");
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
        //打包消息包
        lpSubscribePacker->BeginPack();
        lpSubscribePacker->AddField("topic_name");
        lpSubscribePacker->AddStr(sTopicTname);
        lpSubscribePacker->EndPack();

        CancelSubscribe(m_lpContext, lpSubscribePacker->UnPack());
		DLOGDEBUG(m_lpContext, "取消订阅主题" << sTopicTname << "完成");
        lpResultSet->Next();
    }
    
    if (lpSubscribePacker)
    {
            free(lpSubscribePacker->GetPackBuf());
            lpSubscribePacker->Release();
    }
    if (lpResultSet)
        lpResultSet->Destroy();


	DLOGEVENT(m_lpContext,"取消订阅日间更新主题完成");
    return true;
}

bool CO4InitManager::MultiCast()
{
	DLOGEVENT(m_lpContext,"开始数据组播");

    int iRet = 0;
    int nInitDate = GetInitDate();
    int nFuncId = 0;
    // 打包入参
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

	DLOGEVENT(m_lpContext,"数据组播完成");
    return true;
}

bool CO4InitManager::ExportDataToCsv()
{
	DLOGEVENT(m_lpContext,"开始导出数据到CSV");

    int iRet = 0;
    int nInitDate = GetInitDate();
    // 打包入参
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

	DLOGEVENT(m_lpContext,"导出数据到CSV完成");
    return true;
}


//O4数据同步

bool CO4InitManager::Sync()
{
    // 初始化模式是日初前半段
    m_nInitMode = 2;

    if (!InitDBConnection())
        return false;
    // 获取所有子系统状态，如果没有对接外部子系统,或者qs和hg子系统都未启用,则直接退出初始化流程
    if (false == GetAllSubSysStatus())
    {
        return false;
    }
    if (1 != m_subSysStatus.jc_subsys_status)
    {
        DLOGWARNING(m_lpContext, "未启用基础接入子系统，退出日初始化流程，日初始化结束");
        return true;
    }

    // 判断当前是否需要初始化
    if (!IsCanInit())
    {
        return false;
    }

    // 同步前处理
    if (!doPreInit())
    {
        return false;
    }

    // 数据同步
    if (!doInit())
    {
        return false;
    }

    //同步后处理
    if (!doNextInit())
    {
        return false;
    }
    return true;
}

//夜盘升级数据同步
bool CO4InitManager::UpgradeSync()
{
    // 初始化模式是夜盘升级数据初始化
    m_nInitMode = 4;

    if (!InitDBConnection())
        return false;
    // 获取所有子系统状态，如果没有对接外部子系统,或者qs和hg子系统都未启用,则直接退出初始化流程
    if (false == GetAllSubSysStatus())
    {
        return false;
    }
    if (1 != m_subSysStatus.jc_subsys_status)
    {
        DLOGWARNING(m_lpContext, "未启用基础接入子系统，退出夜盘升级初始化流程");
        return true;
    }

    // 同步前处理
    if (!doPreInit())
    {
        return false;
    }

    // 数据同步
    if (!doInit())
    {
        return false;
    }

    //同步后处理
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
		SetErrInfo(-110, "获取O3数据库连接失败");
		return false;
	}
	DLOGDEBUG(m_lpContext,"删除jc_tbassdellog表数据");
	char sSql[256] = {"delete from jc_tbasedellog"};
	int nRet = m_lpDBConn->executeUpdate(sSql);
	if(0 != nRet)
	{
		DLOGWARNING(m_lpContext,"error_no"<<m_lpDBConn->getErrNo()<<":info:"<<m_lpDBConn->getErrInfo());
		return false;
	}
	DLOGDEBUG(m_lpContext,"jc_tbassdellog表数据删除成功");
	return true;
}
