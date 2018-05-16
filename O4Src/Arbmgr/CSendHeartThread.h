/* 
 * File:   CSendHeartThread.h
 * Author: wangbh
 *
 * Created on 2016年8月2日, 下午1:41
 */

#ifndef CSENDHEARTTHREAD_H
#define	CSENDHEARTTHREAD_H

#include "thread.h"
#include "CArbManager.h"
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <string>
using namespace std;

class CArbManager;
class CSendHeartThread : public CThread
{
public:
    CSendHeartThread(CArbManager* lpOwner, int heartRecvPort, int heartAnswerRecvPort, string bakNodeIp);
    virtual ~CSendHeartThread();

protected:
    bool BeforeRun();
    bool Run();
    bool AfterRun(); 
    
private:
    bool SendASKHeart();
    bool RecvAnswerHeart();

private:
    CArbManager * m_lpOwner;
    int m_heartLoseTimes;
    int m_heartAnswerRecvPort;
    int m_heartRecvPort;
    string m_bakNodeIp;
    int m_clientSocket;
    int m_serverSocket;
};

#endif	/* CSENDHEARTTHREAD_H */

