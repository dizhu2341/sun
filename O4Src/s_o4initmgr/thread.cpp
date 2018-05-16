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
	pThread->BeforeRun();
	pThread->Run();
	pThread->AfterRun();
	
	return (void *)(iRet);
}

CThread::CThread()
{
	m_nTid = 0;
	m_lpThreadTask = NULL;
	m_nStatus = STATUS_IDLE;
}

CThread::~CThread()
{
	m_lpThreadTask = NULL;
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
	m_nStatus = STATUS_BUSY;
	int nRet = pthread_create(&m_nTid, NULL, ThreadProc, this);
	if (0 != nRet)
	{
		return;
	}
}

/*
void CThread::Stop()
{
	if (pthread_kill(m_nTid, 0) != ESRCH)
    {
        pthread_kill(m_nTid, SIGQUIT);
    }
}
*/

void CThread::SetThreadTask(void *lpThreadTask)
{
	if(lpThreadTask == m_lpThreadTask)
		return;
	m_lpThreadTask = lpThreadTask;
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
