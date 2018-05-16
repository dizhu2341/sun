/* 
 * File:   Mutex.h
 * Author: zhouyx11685
 * Description: 互斥锁类
 * Created on 2015年12月10日, 下午2:46
 */

#ifndef MUTEX_H
#define	MUTEX_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <vector>

#define MAX_MUTEX_COUNT     20

using namespace std;

typedef struct STMutexToken
{

    STMutexToken(const char *sToken, pthread_mutex_t* pMutex)
    {
        strcpy(token, sToken);
        mutex = pMutex;
    }
    char token[128];
    pthread_mutex_t* mutex;
} STMutexToken;

class CMutexMgr
{
public:

    static CMutexMgr* GetInstance()
    {
        static CMutexMgr m_pInstance;
        return &m_pInstance;
    }

    pthread_mutex_t* GetLock(const char *sToken);
    bool FreeLock(const char *sToken);

private:
    CMutexMgr();
    ~CMutexMgr();

private:
    pthread_mutex_t m_vecLock;
    vector <STMutexToken *> m_vecMutexTokens;
};

#endif	/* MUTEX_H */

