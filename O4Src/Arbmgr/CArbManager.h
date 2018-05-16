/* 仲裁管理类, 接收仲裁代理的消息,并调用监控插件的动作  */

#ifndef __CArbManager_H__
#define __CArbManager_H__

///插件接口定义头文件
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

///插件接口定义
struct IArbmgr: public IKnown
{
    ///@todo根据规范定义接口函数，纯虚函数，例如：
    //virtual const char * FUNCTION_CALL_MODE GetName(int iIndex) = 0;

};

class CArbMgrIOC; //反转控制器类
class CStatusMonitorMgr; //管理器类
class CArbManager; //插件实现类
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

    ///初始化，被插件库引出函数ArbmgrInit()调用
    int OnInit(PFOnSetTimeOut pfOnSetTimeOut = NULL);
    ///管理器事件处理函数
    //启动，管理器在处理MSG_START事件时调用
    void OnStart(PFOnSetTimeOut pfOnSetTimeOut = NULL);
    //停止，管理器在处理MSG_STOP事件时调用
    void OnStop(PFOnSetTimeOut pfOnSetTimeOut = NULL);
    //退出，管理器在处理MSG_EXIT事件时调用
    void OnExit(PFOnSetTimeOut pfOnSetTimeOut = NULL);
    
private:
    ///反转控制器
    CArbMgrIOC * m_lpIoC;
    ///管理器
    CStatusMonitorMgr * m_lpMgr;
    ///配置对象<plugins>(收到MSG_START事件之后即释放)
    IRCfgObj * m_lpConfig;
    ///配置对象<pub>(收到MSG_START事件之后即释放)
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
