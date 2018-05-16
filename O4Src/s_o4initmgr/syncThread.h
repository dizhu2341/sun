#ifndef _WORK_THREAD_H_
#define _WORK_THREAD_H_

#include <Include/pack_interface.h>
#include <Include/esb_message_interface.h>
#include <Include/tag_def.h>
#include <Include/biz_comp_interface.h>
#include <Include/comm_agent_interface.h>

#include <string.h>
#include <pthread.h>
#include "thread.h"
#include "syncTask.h"

class CSyncThread : public CThread {
public:
    CSyncThread();
    ~CSyncThread();

    void Start();
    
    CSyncTask *GetThreadTask();
    void SetThreadTask(void* lpTask);
    void SetContext(IAS2Context *lpContext);
    void SetCommAgent(ICommAgent  * lpCommAgent);

protected:
    bool BeforeRun();
    bool Run();
    bool AfterRun();
    bool SyncTable();

    bool LockTable(char *pTableName);
    bool UnLockTable(char *pTableName);

    void SetErrInfo(int nErrNo, const char* sErrInfoFmt, ...);
    void SetErrPathInfo(const char* pErrPathInfo);
    int GetErrNo();
    
    bool CallProcedure(CSyncTableInfo* lpSyncTable);
    bool ExecProcNoParam(char *sProcName);
    bool ExecProcWithParam(char *sProcName);
    int CallSubService(int nAsFuncNo);
    int AsynSend(IAS2Context* lpContext, ICommAgent* lpCommAgent, IF2Packer* lpInPack, int nFuncNo);
    int AsynRecv(IAS2Context* lpContext, ICommAgent* lpCommAgent, IF2Packer* lpOutPack, int nHandle, int nTimeOut);

private:
    int nErrorNo;
    IAS2Context * m_lpContext;
    ICommAgent  * m_lpCommAgent;
};

#endif


