#ifndef _MONITOR_THREAD_H_
#define _MONITOR_THREAD_H_

#include <Include/pack_interface.h>
#include <Include/esb_message_interface.h>
#include <Include/tag_def.h>
#include <Include/biz_comp_interface.h>
#include <Include/comm_agent_interface.h>
#include <IncludeFm/s_liblogpublic.h>
#include "IncludeFm/writedlog.h"
#include <string.h>
#include "thread.h"
#include "trade_center.h"

class CMonitorAgent;
class CMonitorThread : public CThread
{
public:
	CMonitorThread(CMonitorAgent* lpMntrAgt);
	~CMonitorThread();

protected:
	bool BeforeRun();
	bool Run();
	bool AfterRun();
	void SetErrInfo(int error_no, const char* error_info);
    int CallSvr();
    int AsynSend(IAS2Context* lpContext, ICommAgent* lpCommAgent, IF2Packer* lpInPack, int nFuncNo, int nBranchNo);
    IF2UnPacker* AsynRecv(IAS2Context* lpContext, ICommAgent* lpCommAgent, int nHandle, int nTimeOut, int nBranchNo);
private:
	CMonitorAgent* m_lpMntrAgt;
};

class CMonitorAgent
{
public:
	CMonitorAgent();
	~CMonitorAgent();
	void Execute(void* lpThreadData);
	void SetThreadData(void* lpThreadData);
	void* GetThreadData();
	void SetErrInfo(int error_no, const char* error_info);
	int GetErrNo();
	char* GetErrInfo();
	bool WaitForTid();
	
private:
	int m_nErrNo;
	char m_sErrInfo[2048];
	CMonitorThread* m_lpMntrThread;
};

#endif
