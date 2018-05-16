/* 
 * File:   CArbMsgRWThread.cpp
 * Author: wangbh
 * 
 * Created on 2016��8��3��, ����9:33
 */

#include "CArbMsgRWThread.h"
#include "acd_def.h"
#include "arb_def.h"

CArbMsgRWThread::CArbMsgRWThread(CArbManager* lpOwner, string eventQueueName, string arbResultQueueName)
{
    m_lpOwner = lpOwner;
    m_strEventQueueName = eventQueueName;
    m_strArbResultQueueName = arbResultQueueName;
}


CArbMsgRWThread::~CArbMsgRWThread() 
{
}

void CArbMsgRWThread::Start()
{
    pthread_attr_t attr;
    pthread_attr_init(&attr);
    //ȷ�����̴߳���detached״̬, �߳̽����Զ��ͷ�ϵͳ��Դ
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);		
    int nRet = pthread_create(&m_nTid, &attr, ThreadProc, this);
    if (0 != nRet)	
    	return;
}

bool CArbMsgRWThread::BeforeRun()
{
    // ���ٲû��Ľ����Ϣ����,�Խ�����Ϣ
    m_lpReadQueue = FBASE_NEW CMsgQueue();
    if (NULL == m_lpReadQueue)
    {
        // TODO
        return false;
    }
    int nRet = m_lpReadQueue->Open(m_strArbResultQueueName.c_str());
    if (0 != nRet)
    {
        // TODO
        return false;
    }
    
    // ���¼���Ϣ����,�����ٲ÷����¼���Ϣ
    m_lpWriteQueue = FBASE_NEW CMsgQueue();
    if (NULL == m_lpWriteQueue)
    {
        // TODO
        return false;
    }
    nRet = m_lpWriteQueue->Open(m_strEventQueueName.c_str());
    if (0 != nRet)
    {
        // TODO
        return false;
    }
    return true;
}

bool CArbMsgRWThread::Run()
{
    int queueMaxSize = m_lpReadQueue->GetMsgSize();
    char* lpReadBuffer = new char[queueMaxSize+1];
    while (true)
    {
      //  IncreaseLoops();
        int nBytes = m_lpReadQueue->Read(lpReadBuffer, queueMaxSize, 2000);
        if (-2 == nBytes)  // ���û�ж�ȡ���κ������������һ��ѭ��
            continue;
        
        // ���������ȡ�쳣, �������һ��ѭ��, ��Ҫ�����Ƿ�ֱ���߳��˳�
        if (nBytes < 0)
        {
            // TODO Log   strerror(errno), errno
            continue;
        }
        
        // �����Ϣ�岻����,�������һ��ѭ��
        if (nBytes != sizeof(MsgQueueHead))
        {
            // TODO log ..
            continue;
        }
        
        // ������Ϣ
        MsgQueueHead queueMsg = *(MsgQueueHead *)lpReadBuffer;
        //TODO Log(recv MSG)
        LOGSYSTEM("���յ��ٲõ�����ID["<<queueMsg.dwPackId  <<"]Action["<<g_lpStatusName[queueMsg.dwResult] <<"]");
        printf("���յ��ٲõ�����ID[%d]Action[%s]\n", queueMsg.dwPackId,  g_lpStatusName[queueMsg.dwResult]);
        m_lpOwner->DealArbMsg(queueMsg.dwPackId ,queueMsg.dwResult);
    }
}

bool CArbMsgRWThread::AfterRun()
{
}

void CArbMsgRWThread::AnswerToArb(int arbResultId, int ackResult)
{
    MsgQueueHead answerMsg;
    answerMsg.dwPackId = arbResultId;
    answerMsg.dwResult = ackResult;
    LOGSYSTEM("Ӧ���ٲû�������ID["<<arbResultId  <<"]RESULT["<< ackResult <<"]");
    printf("Ӧ���ٲû�������ID[%d]RESULT[%d]\n",arbResultId, ackResult );
    m_lpWriteQueue->Write((const char *)&answerMsg, sizeof(answerMsg));
}


