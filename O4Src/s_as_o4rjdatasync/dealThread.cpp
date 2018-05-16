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
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED); //ȷ�����̴߳���detached״̬, �߳̽����Զ��ͷ�ϵͳ��Դ
    int nRet = pthread_create(&m_nTid, &attr, ThreadProc, this);
    if (0 != nRet)
        return;
}

void CDealThread::AddRjMsg(CRjMsg* lpMsg)
{
	pthread_mutex_lock(&m_Mutex);
	
	DLOGEVENT(lpMsg->GetContext(), "������" << lpMsg->GetTableName() << "���ռ����");
	unsigned int i=0;
	for (i=0 ;i<m_undealMsgVector.size(); ++i)
  {
  	CRjMsg* tmpMsg = m_undealMsgVector[i];
  	
  	// ������������,�ӹ�
    if (lpMsg->GetTableName() == tmpMsg->GetTableName())
    {
    	DLOGDEBUG(lpMsg->GetContext(), "��" << lpMsg->GetTableName() << "���ռ���¶������Ѿ�����,�����Թ�");
    	break;
    }
  } 
   
  // ���û���ҵ�ͬ����������
  if (m_undealMsgVector.size() == i)
  {
  	m_undealMsgVector.push_back(lpMsg);
  	DLOGEVENT(lpMsg->GetContext(), "������" << lpMsg->GetTableName() << "���ռ���³ɹ�,��ǰ�����д���δͬ��������" << m_undealMsgVector.size() << "��");
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
		// ��ȡ���������Ϣ
		GetMsgLst(msgVector);
		
		// ��ȡ����Ϊ��.��ȴ�50ms��������ȥ��ȡ
		if(0 == msgVector.size())
		{
			usleep(50000);
			continue;
		}
		
		//LOGDETAIL("�Ӷ����л�ȡ���¶���["<< msgVector.size() <<"]��");
		
		// ����
		for(unsigned int i=0; i<msgVector.size(); ++i)
		{
			CRjMsg* lpMsg = msgVector[i];
			
			// O3��������ͬ��������
			lpMsg->SyncRj();
		}
	}
}


