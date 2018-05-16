/* 
 * File:   CRecvHeartThread.h
 * Author: wangbh
 *
 * Created on 2016年8月3日, 上午9:19
 */

#ifndef CRECVHEARTTHREAD_H
#define	CRECVHEARTTHREAD_H

#include "CArbManager.h"
#include "thread.h"
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <string>
using namespace std;

class CArbManager;
class CRecvHeartThread : public CThread
{
public:
    CRecvHeartThread(CArbManager* lpOwner, int heartRecvPort, int heartAnswerRecvPort, string bakNodeIp);
    virtual ~CRecvHeartThread();
    
protected:
    bool BeforeRun();
    bool Run();
    bool AfterRun(); 
    
private:
    bool RecvASKHeart();
    bool SendAnswerHeart();
    
private:
    CArbManager * m_lpOwner;
    int m_heartLoseTimes;
    int m_clientSocket;
    int m_serverSocket;
    int m_heartAnswerRecvPort;
    int m_heartRecvPort;
    string m_bakNodeIp; 
};

#endif	/* CRECVHEARTTHREAD_H */

