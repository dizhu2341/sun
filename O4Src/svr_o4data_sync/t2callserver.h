#ifndef _T2_CALLSVR_H_
#define _T2_CALLSVR_H_

#include <string.h>

#include <Include/connection_interface.h>
#include <Include/esb_message_interface.h>
#include <Include/tag_def.h>
#include <Include/pack_interface.h>

//#define  SEND_WINDOWS_SIZE 32

//调用服务
IF2UnPacker* CallSvr(int nFuncNo, IF2Packer* packer);

//发布主题
void SubscribeTopic();
									
//打印Unpacker
void PrintUnpacker(IF2UnPacker* lpUnPack);

//----------------------------------------------
// 自定义回调函数
class CCallback : public CCallbackInterface
{
public:
    //因为CCallbackInterface的最终纯虚基类是IKnown，所以需要实现一下3个方法
    //实际实现时，可以直接返回0
    unsigned long  FUNCTION_CALL_MODE QueryInterface(HS_SID iid, IKnown **ppv) { return 0; }
    unsigned long  FUNCTION_CALL_MODE AddRef() { return 0; }
    unsigned long  FUNCTION_CALL_MODE Release() { return 0; }

    //各种事件发生时的回调方法，实际使用时可以根据需要来选择实现，对于不需要的事件回调方法，可直接return
    void FUNCTION_CALL_MODE OnConnect(CConnectionInterface *lpConnection) { puts("CCallback::OnConnect"); }
    void FUNCTION_CALL_MODE OnSafeConnect(CConnectionInterface *lpConnection) { puts("CCallback::OnSafeConnect"); }
    void FUNCTION_CALL_MODE OnRegister(CConnectionInterface *lpConnection) { puts("CCallback::OnRegister"); }
    void FUNCTION_CALL_MODE OnClose(CConnectionInterface *lpConnection) { puts("CCallback::OnClose"); }
    void FUNCTION_CALL_MODE OnSent(CConnectionInterface *lpConnection, int hSend, const void *lpData, int nLength, int nQueuingData) { } 
    void FUNCTION_CALL_MODE OnReceiveNotify(CConnectionInterface *lpConnection, int hSend, const void *lpData, int nLength) { }
    void FUNCTION_CALL_MODE OnReceived(CConnectionInterface *lpConnection, int hSend, const void *lpData, int nLength)
    {  
    	printf("CCallback::OnReceived PacketID=%d, Length=%d\n", hSend, nLength); 	
    }
    int  FUNCTION_CALL_MODE OnBulkReceiveStart(CConnectionInterface *lpConnection, unsigned int uiLength, const char *szComment, char *szFileName, unsigned int *lpPieceSize, int * lpBulkReceiveID)
    {
    	puts("CCallback::OnBulkReceiveStart");
    	return 0;
		}
    void FUNCTION_CALL_MODE OnBulkReceivePiece(CConnectionInterface *lpConnection, int lpBulkReceiveID, unsigned int uiLength, unsigned int uiReceivedLength)
    {
    	puts("CCallback::OnBulkReceivePiece");
		}
    void FUNCTION_CALL_MODE OnBulkReceiveEnd(CConnectionInterface *lpConnection, int lpBulkReceiveID, const void *lpData, unsigned int uiLength)
    {
    	puts("CCallback::OnBulkReceiveEnd");
		}
    void FUNCTION_CALL_MODE OnBulkSendPiece(CConnectionInterface *lpConnection, int iBulkSendID, unsigned int uiLength, unsigned int uiSentLength)
    {
    	puts("CCallback::OnBulkSendPiece");
    }
    void FUNCTION_CALL_MODE OnBulkSendEnd(CConnectionInterface *lpConnection, int iBulkSendID, int iError)
    {
    	puts("CCallback::OnBulkSendEnd");
    }
    void FUNCTION_CALL_MODE OnReceivedBiz(CConnectionInterface *lpConnection, int hSend, const void *lpUnpackerOrStr, int nResult)
		{
			return;
		}
		void FUNCTION_CALL_MODE OnReceivedBizEx(CConnectionInterface *lpConnection, int hSend, LPRET_DATA lpRetData, const void *lpUnpackerOrStr, int nResult) { }
		void FUNCTION_CALL_MODE OnReceivedBizMsg(CConnectionInterface *lpConnection, int hSend, IBizMessage* lpMsg) { }
};

//--------------------------------------------
// 接受发布主题的回调事件类
class CSubCallback : public CSubCallbackInterface
{
	unsigned long  FUNCTION_CALL_MODE QueryInterface(HS_SID iid, IKnown **ppv) { return 0; }
  	unsigned long  FUNCTION_CALL_MODE AddRef() 	{ return 0; }
  	unsigned long  FUNCTION_CALL_MODE Release() { return 0; }
	void FUNCTION_CALL_MODE OnReceived(CSubscribeInterface *lpSub,int subscribeIndex, const void *lpData, int nLength,LPSUBSCRIBE_RECVDATA lpRecvData);
	void FUNCTION_CALL_MODE OnRecvTickMsg(CSubscribeInterface *lpSub,int subscribeIndex,const char* TickMsgInfo) { };
};

//------------------------------------------
// T2操作管理类
class CT2Manager
{
public:
	static CT2Manager& GetSingleInstance()
	{
		static CT2Manager g_t2manager;
		return g_t2manager;
	}	
	
public:
	CT2Manager();
	~CT2Manager();
	
	bool SubscribeTopic(char* lpSuberName,  char* lpTopicName, 
											bool bIsRebuild, bool bIsReplace,
				              char* lpFilterName1 = NULL, char* lpFilterValue1 = NULL,
											char* lpFilterName2 = NULL, char* lpFilterValue2 = NULL,
											char* lpFilterName3 = NULL, char* lpFilterValue3 = NULL,
											char* lpFilterName4 = NULL, char* lpFilterValue4 = NULL,
											char* lpFilterName5 = NULL, char* lpFilterValue5 = NULL,
											char* lpFilterName6 = NULL, char* lpFilterValue6 = NULL
                    );
	IF2UnPacker* CallSvr(int nFuncNo, IF2Packer* packer);
	void PrintSubTopicInfo();
	void PrintUnPack(IF2UnPacker* lpUnPack);
private:
	bool Connect();
	CSubscribeParamInterface* SetSubscribeParam(
					      char* lpTopicName, bool bIsRebuild, bool bIsReplace,
				              char* lpFilterName1, char* lpFilterValue1, 	
				              char* lpFilterName2, char* lpFilterValue2,
				              char* lpFilterName3, char* lpFilterValue3,
				              char* lpFilterName4, char* lpFilterValue4,
				              char* lpFilterName5, char* lpFilterValue5,
				              char* lpFilterName6, char* lpFilterValue6);
	bool NewSubscriber(const char* lpSuberName);
	bool SetESBMessage(int nFuncNo, IF2Packer* packer);
private:
	CConfigInterface*		m_lpConfig;         	// 配置文件接口
	CConnectionInterface* 	m_lpConnection;  		// 连接对象
	CSubscribeInterface* 		m_lpSub;          		// 订阅接口
	IESBMessage*			m_lpESBMessage; 			// ESB消息，用于收发ESB消息包
	CCallback *                       m_lpCallBack;                 // 回调函数对象,创建T2连接时需传递此对象
	CSubCallback* 			m_lpSubScriberCallback;				// 订阅回调函数
	char 					m_szServers[64];   //服务器地址
};

#endif
