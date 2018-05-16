#include "rj_msg_mgr.h"
#include "IncludeFm/s_liblogpublic.h"

CRjMsgMgr::CRjMsgMgr()
{
	pthread_mutex_init(&m_Mutex, NULL);
}

CRjMsgMgr::~CRjMsgMgr()
{
	pthread_mutex_destroy(&m_Mutex);
}


void CRjMsgMgr::AddRjMsg(CRjMsg *lpMsg)
{	
	pthread_mutex_lock(&m_Mutex);

	// 如果工作现场未创建,则创建并启动日间处理现场
	if (NULL == m_dealThread)
  {
  	m_dealThread = new CDealThread();
  	m_dealThread->Start();
    DLOGEVENT(lpMsg->GetContext(), "启动日间处理线程成功");
  }
   
  // 给处理现场新增未处理消息
  m_dealThread->AddRjMsg(lpMsg);
	
	pthread_mutex_unlock(&m_Mutex);
}
