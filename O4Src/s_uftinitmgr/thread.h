#ifndef _THREAD_H_
#define _THREAD_H_

#include <IncludeFm/s_liblogpublic.h>
#include <pthread.h>
#include <signal.h>
#include <unistd.h>
#include <errno.h>
#include <stdio.h>

class CThread
{	
public:
	CThread(void);
	virtual ~CThread(void);

public:
	void Start();
	void Stop();
	bool WaitForTid();

public:
	virtual void SetThreadData(void* lpData);
	virtual void* GetThreadData();

	virtual bool BeforeRun();
	virtual bool Run();
	virtual bool AfterRun();

public:
	static void* ThreadProc(void* pParam);

protected:
	pthread_t m_nTid;   // thread id
	void* m_lpThreadData;
};

#endif
