/* �ٲù�����, �����ٲô������Ϣ,�����ü�ز���Ķ���  */

#ifndef __CArbManager_H__
#define __CArbManager_H__

///����ӿڶ���ͷ�ļ�
#include "ArbMgrMain.h"
#include "CRecvHeartThread.h"
#include "CSendHeartThread.h"
#include "CArbMsgRWThread.h"
#include "arbmgr_interface.h"
#include "acd_def.h"
#include "arb_def.h"
#include "IncludeFm/s_liblogpublic.h"
#include <vector>
using namespace std;

///����ӿڶ���
struct IArbmgr: public IKnown
{
    ///@todo���ݹ淶����ӿں��������麯�������磺
    //virtual const char * FUNCTION_CALL_MODE GetName(int iIndex) = 0;

};

class CArbMgrIOC; //��ת��������
class CStatusMonitorMgr; //��������
class CArbManager; //���ʵ����
class CArbMsgRWThread;
class CRecvHeartThread;
class CSendHeartThread;

class CArbManager: public IArbmgr
{
    friend class CArbMgrIOC;
    friend class CStatusMonitorMgr;
    friend class CArbMsgRWThread;
    friend class CRecvHeartThread;
    friend class CSendHeartThread;
    
public:
    unsigned long  FUNCTION_CALL_MODE QueryInterface( HS_SID iid, IKnown **ppv );
    unsigned long  FUNCTION_CALL_MODE AddRef();
    unsigned long  FUNCTION_CALL_MODE Release();
    
public:
    CArbManager();
    ~CArbManager();

    ///��ʼ�������������������ArbmgrInit()����
    int OnInit(PFOnSetTimeOut pfOnSetTimeOut = NULL);
    ///�������¼�������
    //�������������ڴ���MSG_START�¼�ʱ����
    void OnStart(PFOnSetTimeOut pfOnSetTimeOut = NULL);
    //ֹͣ���������ڴ���MSG_STOP�¼�ʱ����
    void OnStop(PFOnSetTimeOut pfOnSetTimeOut = NULL);
    //�˳����������ڴ���MSG_EXIT�¼�ʱ����
    void OnExit(PFOnSetTimeOut pfOnSetTimeOut = NULL);
    
private:
    ///��ת������
    CArbMgrIOC * m_lpIoC;
    ///������
    CStatusMonitorMgr * m_lpMgr;
    ///���ö���<plugins>(�յ�MSG_START�¼�֮���ͷ�)
    IRCfgObj * m_lpConfig;
    ///���ö���<pub>(�յ�MSG_START�¼�֮���ͷ�)
    IRCfgObj * m_lpCoPub;
    
public:
    void DealLoseHeart();
    void DealRecvHeart();
    
private:
    void DealArbMsg(int arbResultId, int arbResultMsg);
    void SwitchToPrepare(int arbResultId);
    void SwitchToInactive(int arbResultId);
    void SwitchToSingle(int arbResultId);
    void SwitchToActive(int arbResultId);
    void SwitchToSeparate(int arbResultId);
    void AnswerToArb(int arbResultId, int ackResult);
    int GetAppSID();
    string GetAppName();
    string GetAppFullName();
    int GetHeartRecvPort();
    int GetHeartAnswerRecvPort();
    int GetHeartSendPort();
    string GetBakNodeIpAddress();
    bool GetManagerPlugin();
    
private:
    vector<string> m_vecMgrPlugin;
    vector<IArbmgrInterface*> m_lstArbMgrInterface;  
    CArbMsgRWThread* m_lpArbMsgRWThread;
    CSendHeartThread* m_lpSendThread;
    CRecvHeartThread* m_lpRecvThread;
    ShmAcdStatus*  m_lpShmStatusStruct;
    int m_CurrStatus;
};

#endif
