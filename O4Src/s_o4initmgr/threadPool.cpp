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

    //从现有线程池中，寻找空闲线程，如果有则返回
    for (unsigned int i = 0; i < m_vecSyncThread.size(); ++i)
    {
        pThread = (CSyncThread*) m_vecSyncThread[i];
        if (STATUS_IDLE == pThread->GetStatus())
        {
            pThread->SetStatus(STATUS_BUSY); //置为忙碌妆态，并返回
            return pThread;
        }
    }

    // 判断当前是不是已经达到线程数上限
    if (glb_nthreadcount == m_vecSyncThread.size())
        return NULL;

    // 新建线程	
    pThread = new CSyncThread();
    m_vecSyncThread.push_back(pThread);

    // 置为忙碌妆态，并返回
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