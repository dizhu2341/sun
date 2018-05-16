#include "dealThread.h"
#include "hshead.h"
#include <iostream>
using namespace std;

CDealThread::CDealThread()
{
	pthread_mutex_init(&m_Mutex, NULL);
}

CDealThread::~CDealThread()
{
	pthread_mutex_destroy(&m_Mutex);
}

void CDealThread::Start()
{
    pthread_attr_t attr;
    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED); //确保该线程处于detached状态, 线程结束自动释放系统资源
    int nRet = pthread_create(&m_nTid, &attr, ThreadProc, this);
    if (0 != nRet)
        return;
}

void CDealThread::AddRjMsg(CRjMsg* lpMsg)
{
	pthread_mutex_lock(&m_Mutex);
	
	DLOGEVENT(lpMsg->GetContext(), "新增表【" << lpMsg->GetTableName() << "】日间更新");
	unsigned int i=0;
	for (i=0 ;i<m_undealMsgVector.size(); ++i)
  {
  	CRjMsg* tmpMsg = m_undealMsgVector[i];
  	
  	// 对于其他主题,掠过
    if (lpMsg->GetTableName() == tmpMsg->GetTableName())
    {
    	DLOGDEBUG(lpMsg->GetContext(), "表【" << lpMsg->GetTableName() << "】日间更新队列中已经存在,所以略过");
    	break;
    }
  } 
   
  // 如果没有找到同表名的主题
  if (m_undealMsgVector.size() == i)
  {
  	m_undealMsgVector.push_back(lpMsg);
  	DLOGEVENT(lpMsg->GetContext(), "新增表【" << lpMsg->GetTableName() << "】日间更新成功,当前队列中存在未同步表数【" << m_undealMsgVector.size() << "】");
  }
  
	pthread_mutex_unlock(&m_Mutex);
}

void CDealThread::GetMsgLst(vector<CRjMsg*>& msgVector)
{
	pthread_mutex_lock(&m_Mutex);
	msgVector.assign(m_undealMsgVector.begin(), m_undealMsgVector.end());
	m_undealMsgVector.clear();
	pthread_mutex_unlock(&m_Mutex); 
}

bool CDealThread::Run()
{
	vector<CRjMsg*> msgVector;
	
	while (1)
	{
		// 获取待处理的消息
		GetMsgLst(msgVector);
		
		// 获取任务为空.则等待50ms，重新再去获取
		if(0 == msgVector.size())
		{
			usleep(50000);
			continue;
		}
		
		//LOGDETAIL("从队列中获取更新对象["<< msgVector.size() <<"]个");
		
		// 工作
		for(unsigned int i=0; i<msgVector.size(); ++i)
		{
			CRjMsg* lpMsg = msgVector[i];
			
			// O3数据增量同步到基础
			lpMsg->SyncRj();
		}
	}
}


