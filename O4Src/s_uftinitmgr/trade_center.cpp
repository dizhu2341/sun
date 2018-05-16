#include "trade_center.h"

CTradeCenter::CTradeCenter(IAS2Context* lpContext, ICommAgent* lpCommAgent, int tradeID, int initDate,int FuncID)
{
	m_lpContext 	= lpContext;
	m_lpCommAgent 	= lpCommAgent;
	m_nTradeID 		= tradeID;
	m_nInitDate		= initDate;
	m_sInitFlag		= '0';
	m_nFuncID = FuncID;
	
}

CTradeCenter::~CTradeCenter()
{
    //遵循pclint指针释放机制
    m_lpContext = NULL;
    m_lpCommAgent = NULL;
}

IAS2Context* CTradeCenter::GetLpContext()
{
	return m_lpContext;
}

ICommAgent* CTradeCenter::GetLpCommAgent()
{
	return m_lpCommAgent;
}

int CTradeCenter::GetTradeID()
{
	return m_nTradeID;
}

int CTradeCenter::GetInitDate()
{
	return m_nInitDate;
}

char CTradeCenter::GetInitFlag()
{
	return m_sInitFlag;
}

void CTradeCenter::SetInitFlag(char init_flag)
{
	m_sInitFlag = init_flag;
}

int CTradeCenter::GetFuncID()
{
	return m_nFuncID;
}


