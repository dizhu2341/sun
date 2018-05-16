/* 
 * File:   CArbMsgRWThread.cpp
 * Author: wangbh
 * 
 * Created on 2016年8月3日, 上午9:33
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
    //确保该线程处于detached状态, 线程结束自动释放系统资源
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);		
    int nRet = pthread_create(&m_nTid, &attr, ThreadProc, this);
    if (0 != nRet)	
    	return;
}

bool CArbMsgRWThread::BeforeRun()
{
    // 打开仲裁机的结果消息队列,以接收消息
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
    
    // 打开事件消息队列,以向仲裁发送事件消息
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
        if (-2 == nBytes)  // 如果没有读取到任何内容则进入下一个循环
            continue;
        
        // 如果发生读取异常, 则进入下一个循环, 需要考虑是否直接线程退出
        if (nBytes < 0)
        {
            // TODO Log   strerror(errno), errno
            continue;
        }
        
        // 如果消息体不完整,则进入下一个循环
        if (nBytes != sizeof(MsgQueueHead))
        {
            // TODO log ..
            continue;
        }
        
        // 处理消息
        MsgQueueHead queueMsg = *(MsgQueueHead *)lpReadBuffer;
        //TODO Log(recv MSG)
        LOGSYSTEM("接收到仲裁的命令ID["<<queueMsg.dwPackId  <<"]Action["<<g_lpStatusName[queueMsg.dwResult] <<"]");
        printf("接收到仲裁的命令ID[%d]Action[%s]\n", queueMsg.dwPackId,  g_lpStatusName[queueMsg.dwResult]);
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
    LOGSYSTEM("应答仲裁机处理结果ID["<<arbResultId  <<"]RESULT["<< ackResult <<"]");
    printf("应答仲裁机处理结果ID[%d]RESULT[%d]\n",arbResultId, ackResult );
    m_lpWriteQueue->Write((const char *)&answerMsg, sizeof(answerMsg));
}


