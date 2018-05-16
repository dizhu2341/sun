#include "thread.h"

void* CThread::ThreadProc(void* pParam)
{
	//DLOGDEBUG(NULL, "Thread["<<(unsigned int)pthread_self()<<"]Created");
	
	int iRet = 0;
	CThread * pThread = (CThread*)pParam;
	if(NULL == pThread)
		return (void *)-1;

	//-----------------------
	// 开始运行前准备
	if ( !pThread->BeforeRun() )
	{
		iRet = -2;
		return (void *)(iRet);
	}
	
	if ( !pThread->Run() )
	{
		iRet = -3;
		return (void *)(iRet);
	}
	
	//运行后工作
	if ( !pThread->AfterRun() )
	{
		iRet = -4;
		return (void *)(iRet);
	}

	return (void *)(iRet);
}

CThread::CThread(void)
{
	m_nTid = 0;
	m_lpThreadData = NULL;
}


CThread::~CThread(void)
{
	m_lpThreadData = NULL;
}

void CThread::Start()
{
	int nRet = pthread_create(&m_nTid, NULL, ThreadProc, this);
	if (0 != nRet)
	{
		return;
	}
}

void CThread::Stop()
{
	if (pthread_kill(m_nTid, 0) != ESRCH)
    {
        pthread_kill(m_nTid, SIGQUIT);
    }
}

bool CThread::WaitForTid()
{
	void* tRet = NULL;
	if (pthread_join(m_nTid, (void **)&tRet) == 0)
	{
		return ((int *)tRet == 0) ? true : false;
	}
	else
	{
		return false;
	}
}

bool CThread::Run()
{
	sleep(1);
	return true;
}

void CThread::SetThreadData(void *lpThreadData)
{
	if(lpThreadData == m_lpThreadData)
		return;
	m_lpThreadData = lpThreadData;
}

void* CThread::GetThreadData()
{
	return m_lpThreadData;
}

bool CThread::BeforeRun()
{
	printf("before run...\n");
	return true;
}

bool CThread::AfterRun()
{
	printf("after run...\n");
	return true;
}