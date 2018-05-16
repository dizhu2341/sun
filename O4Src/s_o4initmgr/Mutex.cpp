#include "Mutex.h"
#include "IncludeFm/s_libpublic.h"

CMutexMgr::CMutexMgr()
{
    pthread_mutex_init(&m_vecLock, NULL);
}

CMutexMgr::~CMutexMgr()
{
    STMutexToken *pMToken = NULL;

    for (unsigned int i = 0; i < m_vecMutexTokens.size(); ++i)       /*lint !e1551*/
    {
        pMToken = (STMutexToken *)m_vecMutexTokens[i];          /*lint !e1551*/
        if (pMToken != NULL)
        {
            if (pthread_mutex_unlock(pMToken->mutex) == 0)    /*lint !e455*/
            {
                pthread_mutex_destroy(pMToken->mutex);
            }
            delete pMToken;
        }
    }

    pthread_mutex_destroy(&m_vecLock);
}

pthread_mutex_t* CMutexMgr::GetLock(const char* sToken)
{
    pthread_mutex_lock(&m_vecLock);
    
    char token[128] = {0};
    strcpy(token, sToken);
    hs_strtolower(token);
    
    pthread_mutex_t* pMutex = NULL;

    // 先从池中获取
    for (unsigned int i = 0; i < m_vecMutexTokens.size(); ++i)
    {
        STMutexToken* pMToken = (STMutexToken *)m_vecMutexTokens[i];
        if (0 != strcmp(token, pMToken->token))
            continue;

        pMutex = pMToken->mutex;
        break;
    }

    // 如果已经找到直接返回
    if (NULL != pMutex)
    {
        pthread_mutex_unlock(&m_vecLock);
        return pMutex;
    }

    pMutex = new pthread_mutex_t();
    // 新建互斥锁，加入到锁池中
    pthread_mutex_init(pMutex, NULL);
    if (pMutex == NULL)
    {
        pthread_mutex_unlock(&m_vecLock);
        return NULL;
    }
    m_vecMutexTokens.push_back(new STMutexToken(token, pMutex));
    pthread_mutex_unlock(&m_vecLock);
    return pMutex;
}

bool CMutexMgr::FreeLock(const char* sToken)
{
    pthread_mutex_lock(&m_vecLock);
    
    char token[128] = {0};
    strcpy(token, sToken);
    hs_strtolower(token);

    bool bRet = true;
    STMutexToken *pMToken;
    vector <STMutexToken *>::iterator itMutex;

    for (itMutex = m_vecMutexTokens.begin(); itMutex != m_vecMutexTokens.end(); )
    {
        pMToken = (STMutexToken *)*(itMutex);
        if (0 == strcmp(token, pMToken->token))
        {
            bRet = pthread_mutex_unlock(pMToken->mutex) == 0 ? true : false;
            break;
        }
        else
        {
            itMutex++;
        }
    }

    pthread_mutex_unlock(&m_vecLock);

    return bRet;
}

