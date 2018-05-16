#include "IncludeFm/SyncLock.h"
#include "Mutex.h"
extern CMutexMgr *gCMutexMgr;

CSyncLock::CSyncLock(const char *sToken)
{
    strcpy(m_sToken, sToken);
}

CSyncLock::~CSyncLock()
{
    gCMutexMgr->FreeLock(m_sToken);
}

bool CSyncLock::Lock()
{
    pthread_mutex_t *pMutex = gCMutexMgr->GetLock(m_sToken);
    if (NULL != pMutex)
    {
        return (0 == pthread_mutex_lock(pMutex)) ? true : false;
    }
    return false;
}
