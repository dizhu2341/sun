#include "syncTask.h"
#include "hshead.h"

CSyncTask::CSyncTask(char* pErrPathInfo)
{
    m_nTaskStatus = TASK_STATUS_NEW;
    m_nErrNo = 0;
    strcpy(m_sErrInfo, "");
    strcpy(m_sErrPathInfo, pErrPathInfo);
    m_pTableInfo = NULL;
    m_nPriorityLevel = 0;
}

CSyncTask::~CSyncTask()
{
    if (m_pTableInfo != NULL)
    {
        delete m_pTableInfo; /*lint !e1551*/
    }
}

bool CSyncTask::IsNew()
{
    return (m_nTaskStatus == TASK_STATUS_NEW);
}

bool CSyncTask::IsAssigned()
{
    return (m_nTaskStatus == TASK_STATUS_ASSIGNED);
}

bool CSyncTask::IsFinished()
{
    return (m_nTaskStatus == TASK_STATUS_FINISHED);
}

void CSyncTask::SetStatus(int status)
{
    m_nTaskStatus = status;
}

void CSyncTask::SetErrInfo(int nErrNo, const char* sErrInfoFmt, ...)
{
    va_list oArglst;
    memset(&oArglst, 0, sizeof (va_list));

    va_start(oArglst, sErrInfoFmt);
    vsprintf(m_sErrInfo, sErrInfoFmt, oArglst);
    va_end(oArglst);

    m_nErrNo = nErrNo;
    SetStatus(TASK_STATUS_FINISHED);
}

void CSyncTask::SetErrPathInfo(const char* pErrPathInfo)
{
    strcpy(m_sErrPathInfo, pErrPathInfo);
}

int CSyncTask::GetErrNo()
{
    return m_nErrNo;
}

char* CSyncTask::GetErrInfo()
{
    return m_sErrInfo;
}

char* CSyncTask::GetErrPathInfo()
{
    return m_sErrPathInfo;
}

void CSyncTask::SetSyncTableInfo(CSyncTableInfo* pTableInfo)
{
    m_pTableInfo = pTableInfo;
    SetPriorityLevel(m_pTableInfo->GetPriorityLevel());
}

CSyncTableInfo* CSyncTask::GetSyncTableInfo()
{
    return m_pTableInfo;
}

void CSyncTask::SetPriorityLevel(int nPriorityLevel)
{
    m_nPriorityLevel = nPriorityLevel;
}

int CSyncTask::GetPriorityLevel()
{
    return m_nPriorityLevel;
}
