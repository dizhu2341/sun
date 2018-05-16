#include "thread.h"

void* CThread::ThreadProc(void* pParam)
{
	int iRet = 0;
	CThread * pThread = (CThread*)pParam;
	if(NULL == pThread)
	{
	    iRet = -1;
            return (void *)(iRet);
	}
	
	//-----------------------
	// 开始运行前准备
	if (!pThread->BeforeRun())
        {
            // TODO
            iRet = -2;
            return (void *)(iRet);
        }
        
	if (!pThread->Run())
        {
            // TODO
            iRet = -3;
            return (void *)(iRet);
        }

        if (!pThread->AfterRun())
        {
            // TODO
            iRet = -4;
            return (void *)(iRet);    
        }
	
	return (void *)(iRet);
}

CThread::CThread()
{
	m_nTid = 0;
	m_lpThreadTask = NULL;
	m_nStatus = STATUS_NONE;   // 初始化为停止状态
        cond = PTHREAD_COND_INITIALIZER; 
        mutex = PTHREAD_MUTEX_INITIALIZER;
}

CThread::~CThread()
{
	m_lpThreadTask = NULL;
        pthread_mutex_destroy(&mutex);  
        pthread_cond_destroy(&cond);  
}

void CThread::SetStatus(int status)
{
	m_nStatus = status;
}

int  CThread::GetStatus()
{
	return m_nStatus;
}

void CThread::Start()
{
    if (STATUS_NONE == m_nStatus)
    {
        pthread_attr_t attr;
        pthread_attr_init(&attr);
        pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);		//确保该线程处于detached状态, 线程结束自动释放系统资源
        int nRet = pthread_create(&m_nTid, &attr, ThreadProc, this);
        if (0 != nRet)
        {
            // TODO
            return;
        } 
        m_nStatus = STATUS_BUSY;
    }
    else if (STATUS_PAUSE == m_nStatus)
    {
        pthread_mutex_lock(&mutex);
        pthread_cond_signal(&cond);
        m_nStatus = STATUS_BUSY;
        pthread_mutex_unlock(&mutex);
    }
}

void CThread::Pause()
{
    m_nStatus = STATUS_PAUSE;
}

// 
void CThread::Stop()
{
 //   if (pthread_kill(m_nTid, 0) != ESRCH)
 //   {
 //       pthread_kill(m_nTid, SIGQUIT);
 //   }
}

void CThread::SetThreadTask(void *lpThreadTask)
{
	if(lpThreadTask == m_lpThreadTask)
		return;
	m_lpThreadTask = lpThreadTask;
}

void* CThread::GetThreadTask()
{
	return m_lpThreadTask;
}

bool CThread::BeforeRun()
{
    return true;
}

bool CThread::Run()
{
    return true;
}

bool CThread::AfterRun()
{
	m_nStatus = STATUS_IDLE;
    return true;
}
