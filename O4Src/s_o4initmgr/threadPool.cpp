#include "threadPool.h"

CThreadPool::CThreadPool()
{
}

CThreadPool::~CThreadPool()
{
    ReleaseThread(); /*lint !e1551*/
}

CSyncThread* CThreadPool::GetIdleThread()
{
    CSyncThread* pThread = NULL;

    //�������̳߳��У�Ѱ�ҿ����̣߳�������򷵻�
    for (unsigned int i = 0; i < m_vecSyncThread.size(); ++i)
    {
        pThread = (CSyncThread*) m_vecSyncThread[i];
        if (STATUS_IDLE == pThread->GetStatus())
        {
            pThread->SetStatus(STATUS_BUSY); //��Ϊæµױ̬��������
            return pThread;
        }
    }

    // �жϵ�ǰ�ǲ����Ѿ��ﵽ�߳�������
    if (glb_nthreadcount == m_vecSyncThread.size())
        return NULL;

    // �½��߳�	
    pThread = new CSyncThread();
    m_vecSyncThread.push_back(pThread);

    // ��Ϊæµױ̬��������
    pThread->SetStatus(STATUS_BUSY);
    return pThread;
}

int CThreadPool::GetBusyThreadCount()
{
    int count = 0;
    CSyncThread* pThread = NULL;
    for (unsigned int i = 0; i < m_vecSyncThread.size(); ++i)
    {
        pThread = (CSyncThread*) m_vecSyncThread[i];
        if (STATUS_BUSY == pThread->GetStatus())
        {
            count++;
        }
    }
    return count;
}

void CThreadPool::ReleaseThread()
{
    for (unsigned int i = 0; i < m_vecSyncThread.size(); ++i)
    {
        CSyncThread* pThread = (CSyncThread*) (m_vecSyncThread[i]);
        delete pThread;
    }
}