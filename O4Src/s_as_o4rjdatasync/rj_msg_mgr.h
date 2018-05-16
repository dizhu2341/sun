/* 
 * File:   rj_msg_mgr.h
 * Author: wangzh19004
 *
 * Created on 2017��3��17��, ����3:44
 */

#ifndef RJ_MSG_MGR_H
#define	RJ_MSG_MGR_H

#include "rj_msg.h"
#include "dealThread.h"

// ����
class CRjMsgMgr 
{   
public:
	static CRjMsgMgr& GetInstance()
  { 
		static CRjMsgMgr m_pInstance;
		return m_pInstance;
	}
  
  void AddRjMsg(CRjMsg* lpMsg);
  
private:
	CRjMsgMgr();
  ~CRjMsgMgr();
  
	// ��Ϣ�����߳�
	pthread_mutex_t m_Mutex; 
  CDealThread *m_dealThread;
};

#endif	/* RJ_MSG_MGR_H */

