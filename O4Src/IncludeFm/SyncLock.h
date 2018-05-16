/* 
 * File:   SyncLock.h
 * Author: zhouyx11685
 *
 * Created on 2016年8月24日, 上午8:53
 */

#ifndef SYNCLOCK_H
#define	SYNCLOCK_H

#include <stdlib.h>
#include <pthread.h>

class CSyncLock
{
public:
    CSyncLock(const char* sToken);
    ~CSyncLock();

	bool Lock();

public:
    pthread_mutex_t *m_syncLock;
    char m_sToken[256];
};

#endif	/* SYNCLOCK_H */

