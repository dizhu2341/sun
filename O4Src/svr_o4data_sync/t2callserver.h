#ifndef _T2_CALLSVR_H_
#define _T2_CALLSVR_H_

#include <string.h>

#include <Include/connection_interface.h>
#include <Include/esb_message_interface.h>
#include <Include/tag_def.h>
#include <Include/pack_interface.h>

//#define  SEND_WINDOWS_SIZE 32

//���÷���
IF2UnPacker* CallSvr(int nFuncNo, IF2Packer* packer);

//��������
void SubscribeTopic();
									
//��ӡUnpacker
void PrintUnpacker(IF2UnPacker* lpUnPack);

//----------------------------------------------
// �Զ���ص�����
class CCallback : public CCallbackInterface
{
public:
    //��ΪCCallbackInterface�����մ��������IKnown��������Ҫʵ��һ��3������
    //ʵ��ʵ��ʱ������ֱ�ӷ���0
    unsigned long  FUNCTION_CALL_MODE QueryInterface(HS_SID iid, IKnown **ppv) { return 0; }
    unsigned long  FUNCTION_CALL_MODE AddRef() { return 0; }
    unsigned long  FUNCTION_CALL_MODE Release() { return 0; }

    //�����¼�����ʱ�Ļص�������ʵ��ʹ��ʱ���Ը�����Ҫ��ѡ��ʵ�֣����ڲ���Ҫ���¼��ص���������ֱ��return
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
// ���ܷ�������Ļص��¼���
class CSubCallback : public CSubCallbackInterface
{
	unsigned long  FUNCTION_CALL_MODE QueryInterface(HS_SID iid, IKnown **ppv) { return 0; }
  	unsigned long  FUNCTION_CALL_MODE AddRef() 	{ return 0; }
  	unsigned long  FUNCTION_CALL_MODE Release() { return 0; }
	void FUNCTION_CALL_MODE OnReceived(CSubscribeInterface *lpSub,int subscribeIndex, const void *lpData, int nLength,LPSUBSCRIBE_RECVDATA lpRecvData);
	void FUNCTION_CALL_MODE OnRecvTickMsg(CSubscribeInterface *lpSub,int subscribeIndex,const char* TickMsgInfo) { };
};

//------------------------------------------
// T2����������
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
	CConfigInterface*		m_lpConfig;         	// �����ļ��ӿ�
	CConnectionInterface* 	m_lpConnection;  		// ���Ӷ���
	CSubscribeInterface* 		m_lpSub;          		// ���Ľӿ�
	IESBMessage*			m_lpESBMessage; 			// ESB��Ϣ�������շ�ESB��Ϣ��
	CCallback *                       m_lpCallBack;                 // �ص���������,����T2����ʱ�贫�ݴ˶���
	CSubCallback* 			m_lpSubScriberCallback;				// ���Ļص�����
	char 					m_szServers[64];   //��������ַ
};

#endif
