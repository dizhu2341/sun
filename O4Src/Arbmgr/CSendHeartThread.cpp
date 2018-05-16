/* 
 * File:   CSendHeartThread.cpp
 * Author: wangbh
 * 
 * Created on 2016年8月2日, 下午1:41
 */

#include "CSendHeartThread.h"

CSendHeartThread::CSendHeartThread(CArbManager* lpOwner,  int heartRecvPort, int heartAnswerRecvPort, string bakNodeIp) 
{
    m_lpOwner = lpOwner;
    m_heartAnswerRecvPort = heartAnswerRecvPort;
    m_heartRecvPort = heartRecvPort;
    m_bakNodeIp = bakNodeIp;
    m_heartLoseTimes = 0;
}

CSendHeartThread::~CSendHeartThread() 
{
}

bool CSendHeartThread::BeforeRun()
{
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(m_heartAnswerRecvPort);
    addr.sin_addr.s_addr = htonl(INADDR_ANY);
    
    m_serverSocket = socket(AF_INET, SOCK_DGRAM, 0);
    if (m_serverSocket < 0)
    {
        perror("socket");
        return false;
    }
    
    if (fcntl(m_serverSocket, F_SETFL, O_NONBLOCK) < 0)
    {
        printf("fcntl socket error!\n");
        return false;
    }
    
    if (bind(m_serverSocket, (struct sockaddr *)&addr, sizeof(addr)) < 0)
    {
        perror("bind");
        return false;
    }
    
    // 初始化发送对方的客户端socket
    m_clientSocket = socket(AF_INET, SOCK_DGRAM, 0);
    if (m_clientSocket <0)
    {
        LOGERROR(-202, "创建客户端的socket失败!心跳发送线程启动失败！");
        return false;
    }
    
    return true;
}

bool CSendHeartThread::Run()
{
    while (true)
    {
        sleep(2);
        
        pthread_mutex_lock(&mutex);
        while (STATUS_PAUSE == m_nStatus)
            pthread_cond_wait(&cond, &mutex);
        pthread_mutex_unlock(&mutex);
        
        // 发送心跳
        bool bRet = SendASKHeart();
        if (!bRet)
            continue;
        
        // 接收心跳应答
        bRet = RecvAnswerHeart();
        if (!bRet)
        {
            m_heartLoseTimes ++;
            if (m_heartLoseTimes >= 5)
            {
                m_lpOwner->DealLoseHeart();
                m_heartLoseTimes = 0;
            }
        }        
    }
}



bool CSendHeartThread::AfterRun()
{
    return true;
}

// 发送请求包
bool CSendHeartThread::SendASKHeart()
{
    // 服务端IP和端口
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(m_heartRecvPort);    // 发送是用对方节点的接收端口
    addr.sin_addr.s_addr = inet_addr(m_bakNodeIp.c_str());
    
    // 
    char buffer[20] = {"ASK"}; 
    int nByte = sendto(m_clientSocket, buffer, strlen(buffer), 0, (struct sockaddr *)&addr, sizeof(addr));
    if (nByte < 0)
    {
        LOGERROR(-201, "发送心跳包失败")
        return false;
    }
  //  printf("发送心跳 [%s]\n", buffer); 
    return true;
}

// 接收应答心跳
bool CSendHeartThread::RecvAnswerHeart()
{
    char buffer[20];
    memset(buffer,0,sizeof(buffer));
    struct sockaddr_in clientAddr;
    socklen_t nlen = sizeof(clientAddr);
    int nByte  = recvfrom(m_serverSocket, buffer, sizeof(buffer)-1, 0, (struct sockaddr*)&clientAddr, &nlen);
    if (nByte < 0)   // 如果没有收到
    {
        return false;
    }
  //  printf("接收心跳应答 [%s]\n", buffer);  
    return true;
}
    

