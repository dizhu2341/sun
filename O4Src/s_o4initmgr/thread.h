#ifndef _THREAD_H_
#define _THREAD_H_

#include <IncludeFm/s_liblogpublic.h>
#include <pthread.h>
#include <signal.h>
#include <unistd.h>
#include <errno.h>
#include <stdio.h>
#include "IncludeFm/writedlog.h"
#define STATUS_BUSY		0		//Ïß³ÌÃ¦Âµ×´Ì¬
#define STATUS_IDLE		1		//Ïß³Ì¿ÕÏÐ×´Ì¬

class CThread
{	
public:
	CThread();
	virtual ~CThread();

public:
	virtual void Start();
    void SetStatus(int status);
    int  GetStatus();

public:
	virtual void SetThreadTask(void* lpTask);

	virtual bool BeforeRun();
	virtual bool Run();
	virtual bool AfterRun();

public:
	static void* ThreadProc(void* pParam);

protected:
	int m_nStatus;
	pthread_t m_nTid;   // thread id
	void* m_lpThreadTask;
};

#endif
