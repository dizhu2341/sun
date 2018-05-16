#ifndef _TRADE_CENTER_H_
#define _TRADE_CENTER_H_

#include <Include/pack_interface.h>
#include <Include/esb_message_interface.h>
#include <Include/tag_def.h>
#include <Include/f2core_interface.h>
#include <Include/biz_comp_interface.h>
#include <Include/comm_agent_interface.h>

class CTradeCenter
{
public:
	  	CTradeCenter(IAS2Context* lpContext, ICommAgent* lpCommAgent, int tradeID, int initDate,int FuncID = 615011);
		~CTradeCenter();
		
		IAS2Context* GetLpContext();
		ICommAgent* GetLpCommAgent();
		int GetTradeID();
		int GetInitDate();
		char GetInitFlag();
		void SetInitFlag(char init_flag);
		int GetFuncID();
		
private:
		int m_nTradeID;
		int m_nInitDate;
		char m_sInitFlag;
		int m_nFuncID;
		IAS2Context* m_lpContext;
		ICommAgent* m_lpCommAgent;
};

#endif