/* 
 * File:   CRecvHeartThread.cpp
 * Author: wangbh
 * 
 * Created on 2016��8��3��, ����9:19
 */

#include "CRecvHeartThread.h"

CRecvHeartThread::CRecvHeartThread(CArbManager* lpOwner, int heartRecvPort, int heartAnswerRecvPort, string bakNodeIp) 
{
     m_lpOwner = lpOwner;
     m_heartLoseTimes = 0;
    m_heartRecvPort = heartRecvPort;
    m_heartAnswerRecvPort = heartAnswerRecvPort;
    m_bakNodeIp = bakNodeIp;
}

CRecvHeartThread::~CRecvHeartThread() 
{
}

 bool CRecvHeartThread::BeforeRun()
 {
     // ��ʼ������socket
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(m_heartRecvPort);
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
    
    // ��ʼ������socket
    m_clientSocket = socket(AF_INET, SOCK_DGRAM, 0);
    if (m_clientSocket <0)
    {
        perror("socket");
        exit(1);
    }
        
    return true;
 }
 
 bool CRecvHeartThread::Run()
 {
    while (true)
    {
        sleep(2);
        
        pthread_mutex_lock(&mutex);
        while (STATUS_PAUSE == m_nStatus)
            pthread_cond_wait(&cond, &mutex);
        pthread_mutex_unlock(&mutex);
        
        // ����������
        bool bRet = RecvASKHeart();
        if (!bRet)
        {
            m_heartLoseTimes ++;
            if (m_heartLoseTimes >= 5)
            {
                m_lpOwner->DealLoseHeart();
                m_heartLoseTimes = 0;
            }
            continue;
        }
        m_lpOwner->DealRecvHeart();
        m_heartLoseTimes = 0;   // ����
        
        // ����Ӧ���
        SendAnswerHeart();
    }
 }
 
 bool CRecvHeartThread::AfterRun()
 {
    return true;  
 } 

bool CRecvHeartThread::RecvASKHeart()
{
    struct sockaddr_in clientAddr;
    socklen_t nlen = sizeof(clientAddr);
    char buffer[32];
    memset(buffer, 0, sizeof(buffer));
    int nByte = recvfrom(m_serverSocket, buffer, sizeof(buffer)-1, 0, (struct sockaddr*)&clientAddr, &nlen);
    if (nByte < 0)   // ���û���յ�
        return false; 
  //  printf("���յ������� [%s]\n", buffer);    
    return true;
 }
 
 bool CRecvHeartThread::SendAnswerHeart()
 {
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(m_heartAnswerRecvPort);
    addr.sin_addr.s_addr = inet_addr(m_bakNodeIp.c_str());
    
    char buffer[20] = {"ANSWER"};
    int nByte = sendto(m_clientSocket, buffer, strlen(buffer), 0, (struct sockaddr *)&addr, sizeof(addr));
    if (nByte < 0)
    {
        LOGERROR(-203, "��������Ӧ���ʧ��")
        return false;
    }
  //  printf("��������Ӧ��� [%s]\n", buffer); 
    return true;
 }
