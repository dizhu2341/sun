#ifndef _WORK_THREAD_H_
#define _WORK_THREAD_H_

#include <string>
#include <vector>
#include <pthread.h>
#include "thread.h"
#include "rj_msg.h"
using namespace std;

class CDealThread : public CThread 
{
public:
  CDealThread();
  ~CDealThread();
    
  void Start();
  void AddRjMsg(CRjMsg* lpMsg);
    
protected:
  bool Run();
   
private:
	void GetMsgLst(vector<CRjMsg*>& msgVector);
   
private:
//	IConnection * m_lpConn;
  pthread_mutex_t m_Mutex;  
	vector<CRjMsg*> m_undealMsgVector;
};

#endif


