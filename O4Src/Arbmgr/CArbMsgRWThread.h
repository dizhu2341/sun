#pragma once

#include "CArbManager.h"
#include "thread.h"
#include "msg_queue.h"
#include "IncludeFm/s_liblogpublic.h"
#include <string>

using namespace std;

class CArbManager;
class CArbMsgRWThread : public CThread
{
public:
    CArbMsgRWThread(CArbManager* lpOwner, 
                    string eventQueueName, 
                    string arbResultQueueName);
    virtual ~CArbMsgRWThread();
    
    void Start();
    void AnswerToArb(int arbResultId, int ackResult);
    
protected:
    bool BeforeRun();
    bool Run();
    bool AfterRun();
    
private:
    CArbManager * m_lpOwner;
    string m_strEventQueueName;
    string m_strArbResultQueueName;
    
    CMsgQueue *  m_lpReadQueue;   // 消息读队列
    CMsgQueue *  m_lpWriteQueue;  // 消息写队列
};


