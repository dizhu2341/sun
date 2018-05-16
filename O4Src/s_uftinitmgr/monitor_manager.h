#ifndef _MONITOR_MANAGER_H_
#define _MONITOR_MANAGER_H_

#include <Include/pack_interface.h>
#include <Include/esb_message_interface.h>
#include <Include/tag_def.h>
#include <Include/f2core_interface.h>
#include <Include/biz_comp_interface.h>
#include <Include/comm_agent_interface.h>
#include <IncludeFm/s_jc_public.h>

#include <list>
#include "hshead.h"
#include "monitor_thread.h"

extern IAS2Context * glb_lpcontext;
extern IF2Packer * glb_lpoutpacker;
extern ICommAgent * glb_lpcommagent;
extern IF2Core * glb_lpCore;

using namespace std;

typedef list<CTradeCenter *> TRADELIST;
typedef list<CMonitorAgent *> MNTRLIST;

class CMonitorManager
{
public:
	CMonitorManager(IAS2Context * lpContext, ICommAgent* lpCommAgent, IF2UnPacker * lpInUnPacker, IF2Packer * lpOutPacker);
	~CMonitorManager();
public:
	bool CallMonitorService();
	bool GetTradeCenterList();
	bool ResetTradeCenterFlag();
	bool UpdateInitFlag(CTradeCenter* lpTrdCnt);
	bool CheckTradeCenterInit();
	bool GetUFMStatus();
	int  GetErrNo();
	char* GetErrInfo();
	void SetErrInfo(int errNo, const char* pErrInfo);
private:
	IAS2Context * m_lpContext;
	ICommAgent  * m_lpCommAgent;
	IF2UnPacker * m_lpInUnPacker;
	IF2Packer	* m_lpOutPacker;

	TRADELIST	  m_lstTrd;
	MNTRLIST	  m_lstMntr;
	int			  m_nErrNo;
	char		  m_sErrInfo[1024];
	char		  error_pathinfo[4001];
};

#endif
