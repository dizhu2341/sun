#ifndef _DATASYNC_AS_INFO_H_
#define _DATASYNC_AS_INFO_H_

#include "syncTable.h"

#define TASK_STATUS_NEW         0       //任务状态-未分配
#define TASK_STATUS_ASSIGNED    1       //任务状态-已分配
#define TASK_STATUS_FINISHED    2       //任务状态-已完成

class CSyncTask {
public:
    CSyncTask(char* pErrPathInfo);
    ~CSyncTask();

    bool IsAssigned();
    bool IsFinished();
    bool IsNew();
    void SetSyncTableInfo(CSyncTableInfo* pTableInfo);
    CSyncTableInfo* GetSyncTableInfo();
    void SetPriorityLevel(int nPriorityLevel);
    int GetPriorityLevel();
    void SetErrInfo(int nErrNo, const char* sErrInfoFmt, ...);
    void SetErrPathInfo(const char* pErrPathInfo);
    int GetErrNo();
    char* GetErrInfo();
    char* GetErrPathInfo();
    void SetStatus(int status);

private:
    int m_nTaskStatus;
    int m_nErrNo;
    char m_sErrInfo[1024];
    char m_sErrPathInfo[4001];
    int m_nPriorityLevel;
    CSyncTableInfo* m_pTableInfo;
};

#endif//_DATASYNC_AS_INFO_H_
