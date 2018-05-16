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

	// ��������ֳ�δ����,�򴴽��������ռ䴦���ֳ�
	if (NULL == m_dealThread)
  {
  	m_dealThread = new CDealThread();
  	m_dealThread->Start();
    DLOGEVENT(lpMsg->GetContext(), "�����ռ䴦���̳߳ɹ�");
  }
   
  // �������ֳ�����δ������Ϣ
  m_dealThread->AddRjMsg(lpMsg);
	
	pthread_mutex_unlock(&m_Mutex);
}
