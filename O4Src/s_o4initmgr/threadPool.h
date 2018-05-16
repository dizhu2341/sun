#ifndef _THREAD_H
#define _THREAD_H

#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include "syncThread.h"

extern int glb_nthreadcount;

using namespace std;

class CThreadPool
{
public:
	static CThreadPool& GetInstance()
    {   
	    static CThreadPool m_pInstance;  
	    return m_pInstance; 
	}
	 
	~CThreadPool();
	
	CSyncThread* GetIdleThread();
	int GetBusyThreadCount();
	void ReleaseThread();

private:
	CThreadPool();
	vector<CSyncThread *> m_vecSyncThread;
};

#endif
