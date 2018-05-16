/** @file
* T2_SDK�ӿڶ����ļ�
* @author  ���پ�
* @author  �������ӹɷ����޹�˾
* @version 1.0
* @date    20081022
*
* 20101129 xuxp �������ӷ��ͽӿڣ�����ָ���м�����͵Ľӿ�SendBiz
*
* 20101228 xuxp ���ӽӿں��������Ӷ������͵ȵȲ�����ͨ���ṹ��ķ�ʽ��ӡ�

* 20120111 dongpf ����GetAddressInfo����������ȡip��ַ�Ͷ˿�
* 20120118 dongpf ����CreateByMemCert����������֧��SSLģʽ�¶�ȡ������֤���ļ�������UKEY��
* 20130527 xuxp ����GetSelfAddress����������ȡ���Լ����ص�IP�Ͷ˿�
* 20130609 xuxp �������������Ӷ��ķ����Ľӿ�
* 20131024 majc �ڻ�ȡ�����߽ӿ�������ҵ�����������޸ĺ�����
* 20140609 majc ���ӻ�ȡ���������ϸ��Ϣ�ӿ�
*/

#ifndef _CONNECTION_INTERFACE_H_
#define _CONNECTION_INTERFACE_H_

#include <Include/plugin_interface.h>


#include "mc_interface.h"
#include "bizmsg_interface.h"
#include "fileupdate_interface_sdk.h"

//20110302 xuxp ����·����Ϣ�Ľṹ�嶨��
typedef struct tagRouteInfo
{
	char ospfName[ID_STR_LEN+1];
	char nbrName[ID_STR_LEN+1];
	char svrName[SVRINSTANCE_NAME_LENGTH+1];
	char pluginID[PLUGIN_NAME_LENGTH+1];
	int connectID;
	int memberNO;

	tagRouteInfo()
	{
		memset(this,0,sizeof(tagRouteInfo));
	}
}Route_Info;


//20101228 xuxp Ϊ�˷��ͺͷ��ض���������Ϣ�����ӵĽṹ��Ķ���
typedef struct tagRequestData
{	
	int sequeceNo;
	int issueType;
	void* lpKeyInfo;
	int keyInfoLen;
	void* lpFileHead;
	int fileHeadLen;
	int packetType;//20100111 xuxp �¼ӵİ�����
	Route_Info routeInfo;//20110302 xuxp ������������·����Ϣ
	int iSubSystemNo;//20130508 xuxp ������������ϵͳ�Ŵ���
}REQ_DATA, *LPREQ_DATA;
typedef struct tagRespondData
{
	int functionID;
	int returnCode;
	int errorNo;
	char* errorInfo;
	int issueType;
	void* lpKeyInfo;
	int keyInfoLen;
	Route_Info sendInfo;//20110302 xuxp Ӧ���������ӷ�������Ϣ
}RET_DATA, *LPRET_DATA;


///���Ӷ��� CConnectionInterface �Ĳ������ö���
/**
* �������ļ����ء����浽�ļ�����д����
*/
class CConfigInterface: public IKnown
{
public:
	/**
	* ���ļ�����
	* @param szFileName �ļ�������ʽ����ini������ο�������ʾ��
	* @return ����0��ʾ�ɹ�������ʧ��
	*/
	virtual int FUNCTION_CALL_MODE Load(const char *szFileName) = 0;

	/**
	* ���浽�ļ�
	* @param szFileName �ļ���
	* @return ����0��ʾ�ɹ�������ʧ��
	*/
	virtual int FUNCTION_CALL_MODE Save(const char *szFileName) = 0;

	/**
	* ȡ�ַ���ֵ
	* @param szSection ����
	* @param szEntry   ������
	* @param szDefault ȱʡֵ
	* @return �ַ���ֵ��û���ҵ�ʱ����szDefault
	*/
	virtual const char * FUNCTION_CALL_MODE GetString(const char *szSection, const char *szEntry, const char *szDefault) = 0;

	/**
	* ȡ����ֵ
	* @param szSection ����
	* @param szEntry   ������
	* @param iDefault  ȱʡֵ
	* @return ����ֵ��û���ҵ�ʱ����iDefault
	*/
	virtual int FUNCTION_CALL_MODE GetInt(const char *szSection, const char *szEntry, int iDefault) = 0;

	/**
	* �����ַ���ֵ
	* @param szSection ����
	* @param szEntry   ������
	* @param szValue   ֵ
	* @return 0��ʾ�ɹ�������ʧ��
	*/
	virtual int FUNCTION_CALL_MODE SetString(const char *szSection, const char *szEntry, const char *szValue) = 0;

	/**
	* ��������ֵ
	* @param szSection ����
	* @param szEntry   ������
	* @param iValue    ֵ
	* @return 0��ʾ�ɹ�������ʧ��
	*/
	virtual int FUNCTION_CALL_MODE SetInt(const char *szSection, const char *szEntry, int iValue) = 0;
};

class CConnectionInterface;

///���Ӷ��� CConnectionInterface ��Ҫ�Ļص�����ӿڶ���
/**
* �������ӳɹ������ӶϿ���������ɡ��յ����ݡ�Ӧ�𵽴���¼�    
*/
class CCallbackInterface: public IKnown
{
public:
	/**
	* �׽������ӳɹ�
	* @param lpConnection �������¼������Ӷ���
	*/
	virtual void FUNCTION_CALL_MODE OnConnect(CConnectionInterface *lpConnection) = 0;

	/**
	* ��ɰ�ȫ����
	* @param lpConnection �������¼������Ӷ���
	*/
	virtual void FUNCTION_CALL_MODE OnSafeConnect(CConnectionInterface *lpConnection) = 0;

	/**
	* ���ע��
	* @param lpConnection �������¼������Ӷ���
	*/
	virtual void FUNCTION_CALL_MODE OnRegister(CConnectionInterface *lpConnection) = 0;

	/**
	* ���ӱ��Ͽ�
	* @param lpConnection �������¼������Ӷ���
	*/
	virtual void FUNCTION_CALL_MODE OnClose(CConnectionInterface *lpConnection) = 0;

	/**
	* �������
	* @param lpConnection �������¼������Ӷ���
	* @param hSend        ���;��
	* @param lpData       ����ָ��
	* @param nLength      ���ݳ���
	* @param nQueuingData ���Ͷ�����ʣ�������ʹ���߿����ô���ֵ���Ʒ��͵��ٶȣ���С��ĳֵʱ���з���
	* @see Send()
	*/
	virtual void FUNCTION_CALL_MODE OnSent(CConnectionInterface *lpConnection, int hSend, const void *lpData, int nLength, int nQueuingData) = 0;

	/**
	* �յ�����֪ͨ��֮��Դ�hSend����ReceiveӦ�û�ɹ����������Receive����������һֱ�ᱻ�����ռ���ڴ棩
	* @param lpConnection �������¼������Ӷ���
	* @param hSend        ���;��
	* @param lpData       ����ָ��
	* @param nLength      ���ݳ���
	*/
	virtual void FUNCTION_CALL_MODE OnReceiveNotify(CConnectionInterface *lpConnection, int hSend, const void *lpData, int nLength) = 0;

	/**
	* �յ�����ʱָ����ReplyCallbackѡ��������Ӧ�������û�ж�Ӧ���������
	* @param lpConnection �������¼������Ӷ���
	* @param hSend        ���;��
	* @param lpData       ����ָ��
	* @param nLength      ���ݳ���
	*/
	virtual void FUNCTION_CALL_MODE OnReceived(CConnectionInterface *lpConnection, int hSend, const void *lpData, int nLength) = 0;

	/**
	* �յ�������ݴ���Э������
	* @param lpConnection    �������¼������Ӷ���
	* @param uiLength        �����ܳ�
	* @param szComment       ���ڸ����ݵ�˵������
	* @param szFileName      ���Է�ʹ��SendFileʱ��������ļ����������䳤��Ϊ0������ָ�����յ�������д�뵽���ļ���������Ϊ0ʱʹ���ڴ�
	* @param lpPieceSize     ����Է������Ƭ�Ĵ�С�������Լ�Ҫ��ķ�Ƭ�Ĵ�С�����ܴ��ڴ���ķ�Ƭ��С
	* @param lpBulkReceiveID �����˴�����ݽ��յı�ʶ
	* @return ����0��ʾ���ܸô�����ݴ��䣬�����ʾ�ܾ�
	*/
	virtual int FUNCTION_CALL_MODE OnBulkReceiveStart(CConnectionInterface *lpConnection, unsigned int uiLength, const char *szComment, char *szFileName, unsigned int *lpPieceSize, int * lpBulkReceiveID) = 0;

	/**
	* �յ�������ݴ����һƬ����
	* @param lpConnection     �������¼������Ӷ���
	* @param lpBulkReceiveID  ������ݽ��յı�ʶ
	* @param uiLength         �����ܳ�
	* @param uiReceivedLength ���յ������ݳ���
	*/
	virtual void FUNCTION_CALL_MODE OnBulkReceivePiece(CConnectionInterface *lpConnection, int lpBulkReceiveID, unsigned int uiLength, unsigned int uiReceivedLength) = 0;

	/**
	* ������ݽ��ս���
	* @param lpBulkReceiveID ������ݽ��յı�ʶ
	* @param lpConnection    �������¼������Ӷ���
	* @param lpData          ��OnBulkStart��szFileNameָ��������ļ�����ΪszFileName������Ϊ����ָ��
	* @param uiLength        ���ݳ���
	*/
	virtual void FUNCTION_CALL_MODE OnBulkReceiveEnd(CConnectionInterface *lpConnection, int lpBulkReceiveID, const void *lpData, unsigned int uiLength) = 0;

	/**
	* ������ݷ���һƬ����
	* @param lpConnection �������¼������Ӷ���
	* @param iBulkSendID  ������ݷ��͵ı�ʶ
	* @param uiLength     �����ܳ�
	* @param uiSentLength �ѷ��͵����ݳ���
	*/
	virtual void FUNCTION_CALL_MODE OnBulkSendPiece(CConnectionInterface *lpConnection, int iBulkSendID, unsigned int uiLength, unsigned int uiSentLength) = 0;

	/**
	* ������ݷ��ͽ���
	* @param lpConnection �������¼������Ӷ���
	* @param iBulkSendID  ������ݷ��͵ı�ʶ
	* @param iError       0��ʾ�ɹ�������ʧ��
	*/
	virtual void FUNCTION_CALL_MODE OnBulkSendEnd(CConnectionInterface *lpConnection, int iBulkSendID, int iError) = 0;
    
    /**
    * �յ�SendBiz�첽���͵������Ӧ��
    * @param lpConnection    �������¼������Ӷ���
    * @param hSend           ���;��
    * @param lpUnPackerOrStr ָ������ָ����ߴ�����Ϣ
    * @param nResult         �հ����
    * ���nResult����0����ʾҵ�����ݽ��ճɹ�������ҵ������ɹ���lpUnpackerOrStrָ��һ�����������ʱӦ���Ƚ���ָ��ת��ΪIF2UnPacker *��
    * ���nResult����1����ʾҵ�����ݽ��ճɹ�����ҵ�����ʧ���ˣ�lpUnpackerOrStrָ��һ�����������ʱӦ���Ƚ���ָ��ת��ΪIF2UnPacker *��
    * ���nResult����2����ʾ�յ���ҵ�������Ϣ��lpUnpackerOrStrָ��һ���ɶ����ַ���������Ϣ��
    * ���nResult����3����ʾҵ������ʧ�ܡ�lpUnpackerOrStrָ��NULL��
	* �������ֵ����4����ʾҵ���Ϊ�ա�lpUnpackerOrStrָ��NULL��
    */
    virtual void FUNCTION_CALL_MODE OnReceivedBiz(CConnectionInterface *lpConnection, int hSend, const void *lpUnpackerOrStr, int nResult) = 0;

	/**
    * �յ�SendBiz�첽���͵������Ӧ��
    * @param lpConnection    �������¼������Ӷ���
    * @param hSend           ���;��
    * @param lpRetData ������Ҫ���ص�Ӧ�����ݣ�������Ҫ��ȡ
    * @param lpUnPackerOrStr ָ������ָ����ߴ�����Ϣ
    * @param nResult         �հ����
    * ���nResult����0����ʾҵ�����ݽ��ճɹ�������ҵ������ɹ���lpUnpackerOrStrָ��һ�����������ʱӦ���Ƚ���ָ��ת��ΪIF2UnPacker *��
    * ���nResult����1����ʾҵ�����ݽ��ճɹ�����ҵ�����ʧ���ˣ�lpUnpackerOrStrָ��һ�����������ʱӦ���Ƚ���ָ��ת��ΪIF2UnPacker *��
    * ���nResult����2����ʾ�յ���ҵ�������Ϣ��lpUnpackerOrStrָ��һ���ɶ����ַ���������Ϣ��
    * ���nResult����3����ʾҵ������ʧ�ܡ�lpUnpackerOrStrָ��NULL��
	* �������ֵ����4����ʾҵ���Ϊ�ա�lpUnpackerOrStrָ��NULL��lpRetData�ⲿ�ֽ���������
    */
    virtual void FUNCTION_CALL_MODE OnReceivedBizEx(CConnectionInterface *lpConnection, int hSend, LPRET_DATA lpRetData, const void *lpUnpackerOrStr, int nResult) = 0;


	//20130624 xuxp �ص�����BizMessage�ӿ�
	/**
	* �յ�����ʱָ����ReplyCallbackѡ��������Ӧ�������û�ж�Ӧ���������
	* @param lpConnection �������¼������Ӷ���
	* @param hSend        ���;��
	* @param lpMsg        ҵ����Ϣָ��
	*/
	virtual void FUNCTION_CALL_MODE OnReceivedBizMsg(CConnectionInterface *lpConnection, int hSend, IBizMessage* lpMsg) = 0;
};

///T2_SDK���Ӷ���ӿ�
/**
* �������ӡ��Ͽ������͡����յ�
*/
class CConnectionInterface: public IKnown
{
public:
	///����״̬�������
	enum ConnectionStatus
	{
		Disconnected	= 0x0000, /**< δ���� */
		Connecting		= 0x0001, /**< socket�������� */
		Connected		= 0x0002, /**< socket������ */
		SafeConnecting	= 0x0004, /**< ���ڽ�����ȫ���� */
		SafeConnected	= 0x0008, /**< �ѽ�����ȫ���� */
		Registering		= 0x0010, /**< ��ע�� */
		Registered		= 0x0020, /**< ��ע�� */
		Rejected		= 0x0040  /**< ���ܾ��������ر� */
	};

    ///����ѡ�����ϣ�0��ʾͬ�����ͣ�ͨ��ReceiveȡӦ��
	enum SendFlags
	{
		ReplyCallback    = 0x0001,   /**< ͨ���ص�ȡӦ�� */
		MultiReply	     = 0x0002,   /**< �ж��Ӧ�𣬼��������һ��hSend��� Receive */
        IsESBMessage     = 0x0100,   /**< ����һ��ESBMessage����ʱSend�����ĵ�һ������ΪESBMessage�ĵ�ַ���ڶ����������� */
        ThroughLine      = 0x0200,   /**< ���������PacketID����buffer�Դ���PacketIDΪ�˴η��͵�PacketID*/
        ThirdParty       = 0x0400    /**< ͨ���ص�ȡӦ�𣨵�����ר�ã� */
	};

    ///����ѡ�����ϣ�0��ʾ���ճ�ʱʱ����ɾ����ID���Կ��ٴε���Receive���������Խ��գ�
    enum RecvFlags
    {
        JustRemoveHandle = 0x0001   /**< �����ճ�ʱʱ����packet_idɾ�����Ժ����յ���������첽�ķ�ʽ�յ�����
                                     ע�⣬�˲�������Receive�����д��ݣ������Ҫ�Ļ��� */
    };

	/**
	* ��ʼ�����Ӷ���
	* @param lpCallback �ص�����
	* @return ����0��ʾ�ɹ��������ʾʧ�ܣ�ͨ������GetErrorMsg���Ի�ȡ��ϸ������Ϣ
    * ���Ӧ�ò���Ҫ�κλص������������÷�������NULL���������Զ���ص���Ͷ���
	*/
	virtual int FUNCTION_CALL_MODE Create(CCallbackInterface *lpCallback) = 0;
		
	/**
	* ��������
	* @param uiTimeout ��ʱʱ�䣬��λ���룬0��ʾ���ȴ���ʹ�ô������ӷ�����ʱ���ò����������ã�
	* @return ����0��ʾ�ɹ��������ʾʧ�ܣ�ͨ������GetErrorMsg���Ի�ȡ��ϸ������Ϣ
	*/
	virtual int FUNCTION_CALL_MODE Connect(unsigned int uiTimeout) = 0;
	
	/**
	* �Ͽ�����
	* @return ����0��ʾ�ɹ��������ʾʧ�ܣ�ͨ������GetErrorMsg���Ի�ȡ��ϸ������Ϣ
	*/
	virtual int FUNCTION_CALL_MODE Close() = 0;
	
	/**
	* ��������
	* @param lpData  ����������ָ��
	* @param nLength ���������ݳ��ȣ���󳤶�Ϊ16M - 1
	* @param uiFlag  ����ѡ��
	* @return ���ط��;�����������������ʾʧ�ܣ�ͨ������GetErrorMsg���Ի�ȡ��ϸ������Ϣ
	*/
	virtual int FUNCTION_CALL_MODE Send(const void *lpData, int nLength, unsigned int uiFlag) = 0;

	/**
	* ��������
	* @param hSend     ���;��
	* @param lppData   �յ�����ָ��ĵ�ַ
	* @param lpnLength �յ����ݳ��ȵĵ�ַ
	* @param uiTimeout ��ʱʱ�䣬��λ���룬0��ʾ���ȴ�
	* @param uiFlag    ����ѡ�0��ʾ���ճ�ʱ���Կɼ�������Receive�����գ�
    *                  JustRemoveHandle��ʾ�����ճ�ʱʱ����packet_idɾ�����Ժ����յ���������첽�ķ�ʽ�յ���
	* @return ����0��ʾ�ɹ��������ʾʧ�ܣ�ͨ������GetErrorMsg���Ի�ȡ��ϸ������Ϣ
	*/
	virtual int FUNCTION_CALL_MODE Receive(int hSend, void **lppData, int *lpnLength, unsigned int uiTimeout, unsigned int uiFlag) = 0;
	
	/**
	* ʹ�ô�����ݴ���Э�鷢�ʹ������
	* @param lpData      ����������ָ��
	* @param uiLength    ���������ݳ���
	* @param szComment   ���ڸ����ݵ�˵������
	* @param uiPieceSize �����Ƭ�Ĵ�С
	* @param lpRouteInfo ·�����ã�ʵ������ΪIESBMessage *��ָ����鴫��Ľ�����
	* @return 0��ʾʧ�ܣ�����Ϊ�ô�����ݷ��ͱ�ʶ
	*/
	virtual int FUNCTION_CALL_MODE BulkSend(const void *lpData, unsigned int uiLength, const char *szComment, unsigned int uiPieceSize, const void *lpRouteInfo) = 0;
	
	/**
	* ʹ�ô�����ݴ���Э�鷢���ļ���Ŀ��ͨ��ESBMessageָ��
	* @param szFileName  �������ļ���
	* @param szComment   ���ڸ��ļ���˵������
	* @param uiPieceSize �����Ƭ�Ĵ�С
	* @param lpRouteInfo ·�����ã�ʵ������ΪIESBMessage *��ָ����鴫��Ľ�����
	* @return 0��ʾʧ�ܣ�����Ϊ�ô�����ݷ��ͱ�ʶ
	*/
	virtual int FUNCTION_CALL_MODE SendFile(const char *szFileName, const char *szComment, unsigned int uiPieceSize, const void *lpRouteInfo) = 0;

	/**
	* ȡ��������ݷ���
	* @param iBulkSendID ������ݷ��ͱ�ʶ
	* @return 0��ʾ�ɹ�
	*/
	virtual int FUNCTION_CALL_MODE CancelBulkSend(int iBulkSendID) = 0;

	/**
	* ȡ��������ݽ���
	* @param iBulkReceiveID ������ݽ��ձ�ʶ
	* @return 0��ʾ�ɹ��������ʾʧ�ܣ�ͨ������GetErrorMsg���Ի�ȡ��ϸ������Ϣ
	*/
	virtual int FUNCTION_CALL_MODE CancelBulkReceive(int iBulkReceiveID) = 0;

	/**
	* ȡ��������ַ
	* @param lpPort ����ķ������˿ڣ�����ΪNULL
	* @return ���ط�������ַ
	*/
	virtual const char * FUNCTION_CALL_MODE GetServerAddress(int *lpPort) = 0;

	/**
	* ȡ����״̬
	* @return ��������״̬
	*/
	virtual int FUNCTION_CALL_MODE GetStatus() = 0;

	/**
	* ȡ���������أ�ʹ���߿���ͬʱ�����������ʵ��ͬʱ���Ӳ�ͬ�ķ�����������������ӵ�ʱ���Լ����ؾ���ʹ���ĸ�������
	* @return ���ط��������أ��Ǹ�������Խ���ʾԽ��æ�������ʾʧ�ܣ�ͨ������GetErrorMsg���Ի�ȡ��ϸ������Ϣ
	*/
	virtual int FUNCTION_CALL_MODE GetServerLoad() = 0;

	/**
	* ȡ�������Ӧ�Ĵ�����Ϣ��Ŀǰ֧�ּ������ĺ�Ӣ�ģ�֧���������Կ���ͨ�����Ӷ�������errormsg
	* @param nErrorCode ������
	* @return ���ش�����Ϣ
	*/
	virtual const char * FUNCTION_CALL_MODE GetErrorMsg(int nErrorCode) = 0;

    /**
    * ȡ���Ӵ���ţ��������޷����������ע��ʱ�����ø÷����ɻ�ȡ����ţ�Ȼ���øô���ŵ���GetErrorMsg
    * �ɻ�ȡ�ɶ��Ĵ�����Ϣ
    * @return �������Ӵ����
    */
    virtual int FUNCTION_CALL_MODE GetConnectError() = 0;

    /**
    * ����ҵ������
    * @param iFunID      ���ܺ�
    * @param lpPacker    �����ָ��
    * @param nAsy        0��ʾͬ���������ʾ�첽��
    * @param iSystemNo   ���iSystemNo > 0������ϵͳ��
    * @param nCompressID ��ҵ��������ѹ����ѹ���㷨ID��Ŀǰֻ֧��ID = 1��ѹ���㷨��
    * ID = 0��ʾ��ѹ����ע�⣬ѹ��ֻ����SDK������飬�Ƿ�����ѹ����ȡ���ڰ���ʵ�ʴ�С��
    * ͬ�����͵İ���ͨ������RecvBiz�����գ��첽���͵İ������յ�Ӧ������Զ������ص�����OnReceivedBiz��
    * @return ���ط��;�����������������ʾʧ�ܣ�ͨ������GetErrorMsg���Ի�ȡ��ϸ������Ϣ
    */
    virtual int FUNCTION_CALL_MODE SendBiz(int iFunID, IF2Packer *lpPacker, int nAsy = 0, int iSystemNo = 0, int nCompressID = 1) = 0;

    /**
    * ����ҵ������
    * @param hSend            ���;����SendBiz�ĳɹ�����ֵ��
    * @param lppUnPackerOrStr �������ֵ����0����ʾҵ�����ݽ��ճɹ�������ҵ������ɹ���*lppUnPackerOrStrָ��һ�����������ʱӦ���Ƚ���ָ��ת��ΪIF2UnPacker *��
    *                         �������ֵ����1����ʾҵ�����ݽ��ճɹ�����ҵ�����ʧ���ˣ�*lppUnPackerOrStrָ��һ�����������ʱӦ���Ƚ���ָ��ת��ΪIF2UnPacker *��
    *                         �������ֵ����2����ʾ�յ���ҵ�������Ϣ��*lppUnPackerOrStrָ��һ���ɶ����ַ���������Ϣ��
    *                         �������ֵ����3����ʾҵ������ʧ�ܡ�*lppUnPackerOrStrԭ����ָ������ݲ��ᱻ�ı䡣
    *						  �������ֵ����4����ʾҵ���Ϊ�ա�*lppUnPackerOrStrԭ����ָ������ݲ��ᱻ�ı䡣
	* @param uiTimeout        ��ʱʱ�䣬��λ���룬0��ʾ���ȴ���
    * @param uiFlag           ����ѡ�0��ʾ���ճ�ʱ���Կɼ�������RecvBiz�����գ�
    *                         JustRemoveHandle��ʾ�����ճ�ʱ�󣬰�hSend�������ɾ��
    * @return С��0��ʾRecvBiz��������ʧ�ܣ�ͨ������GetErrorMsg���Ի�ȡ��ϸ������Ϣ
    * ע�⣡�ⲿָ����ָ��Ľ�������ڴ���SDK�ڲ������ⲿ�����ͷţ�
    */
    virtual int FUNCTION_CALL_MODE RecvBiz(int hSend, void **lppUnPackerOrStr, unsigned uiTimeout = 1000, unsigned uiFlag = 0) = 0;

	//20101228 xuxp ������Ľӿ����ֲ����������ģ������в���Ԥ֪�Ĵ���
	//20101129 xuxp ��ָ���м����������
	/**
    * ����ҵ������
    * @param iFunID      ���ܺ�
    * @param lpPacker    �����ָ��
	* @param svrName     ָ���м���Ľڵ�
    * @param nAsy        0��ʾͬ���������ʾ�첽��
    * @param iSystemNo   ���iSystemNo > 0������ϵͳ��
    * @param nCompressID ��ҵ��������ѹ����ѹ���㷨ID��Ŀǰֻ֧��ID = 1��ѹ���㷨��
    * ID = 0��ʾ��ѹ����ע�⣬ѹ��ֻ����SDK������飬�Ƿ�����ѹ����ȡ���ڰ���ʵ�ʴ�С��
    * ͬ�����͵İ���ͨ������RecvBiz�����գ��첽���͵İ������յ�Ӧ������Զ������ص�����OnReceivedBiz��
    * @return ���ط��;�����������������ʾʧ�ܣ�ͨ������GetErrorMsg���Ի�ȡ��ϸ������Ϣ
    */
    //virtual int FUNCTION_CALL_MODE SendBiz(int iFunID, IF2Packer *lpPacker, char* svrName, int nAsy = 0, int iSystemNo = 0, int nCompressID = 1) = 0;

	//20101228 xuxp �������ͺͽ��ܵ������ӿں��������ڶ��ĺ�����
	/**
    * ����ҵ������
    * @param iFunID      ���ܺ�
    * @param lpPacker    �����ָ��
	* @param svrName     ָ���м���Ľڵ�
    * @param nAsy        0��ʾͬ���������ʾ�첽��
    * @param iSystemNo   ���iSystemNo > 0������ϵͳ��
    * @param nCompressID ��ҵ��������ѹ����ѹ���㷨ID��Ŀǰֻ֧��ID = 1��ѹ���㷨��
    * ID = 0��ʾ��ѹ����ע�⣬ѹ��ֻ����SDK������飬�Ƿ�����ѹ����ȡ���ڰ���ʵ�ʴ�С��
    * ͬ�����͵İ���ͨ������RecvBiz�����գ��첽���͵İ������յ�Ӧ������Զ������ص�����OnReceivedBiz��
    * @param branchNo  Ӫҵ���š�
    * @param lpRequest  ����������������ݣ����ݽṹ�嶨�帳ֵ��
    * @return ���ط��;�����������������ʾʧ�ܣ�ͨ������GetErrorMsg���Ի�ȡ��ϸ������Ϣ
    */
    virtual int FUNCTION_CALL_MODE SendBizEx(int iFunID, IF2Packer *lpPacker,char* svrName, int nAsy = 0, int iSystemNo = 0, int nCompressID = 1,int branchNo=0,LPREQ_DATA lpRequest=NULL) = 0;
    
	//20110308 xuxp ���ӷ���ֵ�������ж�TAG_MESSAGE_BODY�ֶ�Ϊ�յ����
    /**
    * ����ҵ������
    * @param hSend            ���;����SendBiz�ĳɹ�����ֵ��
    * @param lppUnPackerOrStr �������ֵ����0����ʾҵ�����ݽ��ճɹ�������ҵ������ɹ���*lppUnPackerOrStrָ��һ�����������ʱӦ���Ƚ���ָ��ת��ΪIF2UnPacker *��
    *                         �������ֵ����1����ʾҵ�����ݽ��ճɹ�����ҵ�����ʧ���ˣ�*lppUnPackerOrStrָ��һ�����������ʱӦ���Ƚ���ָ��ת��ΪIF2UnPacker *��
    *                         �������ֵ����2����ʾ�յ���ҵ�������Ϣ��*lppUnPackerOrStrָ��һ���ɶ����ַ���������Ϣ��
    *                         �������ֵ����3����ʾҵ������ʧ�ܡ�*lppUnPackerOrStrԭ����ָ������ݲ��ᱻ�ı䡣
	*						  �������ֵ����4����ʾҵ���Ϊ�ա�*lppUnPackerOrStrԭ����ָ������ݲ��ᱻ�ı䡣ͬʱlpRetData�ṹ������ݻ��Ǵ��ڵ�
    * @param lpRetData ������Ҫ���ص�Ӧ�����ݣ�������Ҫ��ȡ
    * @param uiTimeout        ��ʱʱ�䣬��λ���룬0��ʾ���ȴ���
    * @param uiFlag           ����ѡ�0��ʾ���ճ�ʱ���Կɼ�������RecvBiz�����գ�
    *                         JustRemoveHandle��ʾ�����ճ�ʱ�󣬰�hSend�������ɾ��
    * @return С��0��ʾRecvBiz��������ʧ�ܣ�ͨ������GetErrorMsg���Ի�ȡ��ϸ������Ϣ
    * ע�⣡�ⲿָ����ָ��Ľ�������ڴ���SDK�ڲ������ⲿ�����ͷţ�
	* ע�⣡�ⲿָ����ָ���LPRET_DATA���ڴ���SDK�ڲ������ⲿ�����ͷţ�
    */
    virtual int FUNCTION_CALL_MODE RecvBizEx(int hSend, void **lppUnpackerOrStr, LPRET_DATA* lpRetData, unsigned uiTimeout = 1000, unsigned uiFlag = 0) = 0;


	//20101228 xuxp ����Create����������֤�ص����µ�OnReceivedBizEx�Ľӿ�
	/**
	* ��ʼ�����Ӷ���
	* @param lpCallback �ص�����
	* @return ����0��ʾ�ɹ��������ʾʧ�ܣ�ͨ������GetErrorMsg���Ի�ȡ��ϸ������Ϣ
    * ���Ӧ�ò���Ҫ�κλص������������÷�������NULL���������Զ���ص���Ͷ���
	*/
	virtual int FUNCTION_CALL_MODE CreateEx(CCallbackInterface *lpCallback) = 0;

	//20120111 dongpf ����GetRealAddress����������ȡ��������Լ���ip��ַ�Ͷ˿�
	/**
	* ��ȡip��ַ�Ͷ˿�
	* @return ��ȡip��ַ�Ͷ˿ڣ���ʽ��ip��ַ+�˿�
	*/
	virtual const char* FUNCTION_CALL_MODE GetRealAddress() = 0;

	//20120118 dongpf ����֧��SSLģʽ�¶�ȡ������֤���ļ�������UKEY��
    /**
    * ��ʼ�����Ӷ���
    * @param lpCallback �ص�����
    * @param lpCertData ������֤���ļ�����
    * @param nLength    ������֤���ļ�����
    * @param szPWD      ֤������
    * @return ����0��ʾ�ɹ��������ʾʧ�ܣ�ͨ������GetErrorMsg���Ի�ȡ��ϸ������Ϣ
      * ���Ӧ�ò���Ҫ�κλص������������÷�������NULL���������Զ���ص���Ͷ���
    */
	virtual int FUNCTION_CALL_MODE CreateByMemCert(CCallbackInterface *lpCallback, void * lpCertData, int nLength, const char * szPWD) = 0;

	//20130329 xuxp ����һ��Create����������mcapi�����ã��ڵ������ӿ�����ͨ�������ʶ����ǻص��ڲ��Ľӿ�
    /**
	* ��ʼ�����Ӷ���ֻ������mcapi
	* @param lpCallback �ص�����
	* @return ����0��ʾ�ɹ��������ʾʧ�ܣ�ͨ������GetErrorMsg���Ի�ȡ��ϸ������Ϣ
    * ���Ӧ�ò���Ҫ�κλص������������÷�������NULL���������Զ���ص���Ͷ���
	*/
	virtual int FUNCTION_CALL_MODE Create2Mcapi(CCallbackInterface *lpCallback) = 0;


	//20130527 xuxp ����GetSelfAddress����������ȡ�Լ����ص�IP�Ͷ˿�
	/**
	* ��ȡip��ַ�Ͷ˿�
	* @return ��ȡip��ַ�Ͷ˿ڣ���ʽ��ip��ַ+�˿�
	*/
	virtual const char* FUNCTION_CALL_MODE GetSelfAddress() = 0;

	//20130529 xuxp ����GetSelfMac����������ȡ�Լ�����ʹ�õ�����MAC
	/**
	* ��ȡMAC��ַ
	* @return MAC�ĵ�ַ�ַ�����ʽ�����ơ�D067E5556D83��,�м�û�зָ���
	*/
	virtual const char* FUNCTION_CALL_MODE GetSelfMac() = 0;

	//20130609 xuxp �������ķ����ӿ�
	///////////////////////////////////�������Ӷ��ķ����Ľӿ�///////////////////////////////////////

	/**
    * ����һ��������
    * @param lpCallback �ص��ӿ�
    * @param SubScribeName ���������֣��ඩ���ߵ����ֱ��벻һ������������ͬ.��󳤶�32���ֽ�
    * @param iTimeOut ��ʱʱ��
    * @param iInitRecvQLen ��ʼ�����ն��еĳ���
    * @param iStepRecvQLen ���ܶ��е���չ����
    * @return ���ض��Ľӿ�ʵ����һ���Ự�ӿڶ�Ӧһ���ص�.
    */
    virtual CSubscribeInterface* FUNCTION_CALL_MODE NewSubscriber(CSubCallbackInterface *lpCallback,char* SubScribeName,int iTimeOut,
        int iInitRecvQLen=INIT_RECVQ_LEN,int iStepRecvQLen=STEP_RECVQ_LEN) = 0;
   //20131024 majc �ڻ�ȡ�����߽ӿ�������ҵ��������
   /**
    * ��ȡ������
    * @param PublishName ������ҵ����
    * @param msgCount ���ػ�����Ϣ�ĸ���
	  * @param iTimeOut ��ʼ����ʱ��ĳ�ʱʱ��
    * @param bResetNo �Ƿ�������
    * @return ���ط��ͽӿ�ʵ�������ض�Ӧ��ָ��
    */
    //virtual CPublishInterface* FUNCTION_CALL_MODE GetPublisher(int msgCount,int iTimeOut,bool bResetNo = false) = 0;
    virtual CPublishInterface* FUNCTION_CALL_MODE NewPublisher(char* PublishName,int msgCount,int iTimeOut,bool bResetNo = false) = 0;
  


   /**
    * ��ȡ����˵�����������Ϣ
    * @param byForce �Ƿ�ǿ�ƴӺ�̨��ȡ
    * @param iTimeOut ��ʱʱ��
    * @return �ɹ��ͷ�������������Ϣ
    * @note �����������Ҫ����release�ӿڽ����ͷ�.
    * @note packer�����ֶ�
    * - TopicName
    * - TopicNo
    * - ReliableLevel
    * - IssuePriority
    * - MsgLifetime
    * - Stutas 
    * - TickStrategy 
    * - BusinessVerify
    * - Local
    * - FilterField1 
    * - FilterField2 
    * - FilterField3 
    * - FilterField4 
    * - FilterField5 
    * - FilterField6
    * - SubscribeStr 
    * - PublishStr
    */
    virtual IF2UnPacker* FUNCTION_CALL_MODE GetTopic(bool byForce,int iTimeOut) = 0;
	
	/**
	* ��ȡ���ķ�����������
	*/
	virtual const char* FUNCTION_CALL_MODE GetMCLastError() = 0;
	////////////////////////////////////////////////////////////////////////////////

	//20130624 xuxp ���ӽӿ��������������ӿڣ�������Ϊ����˵Ľӿڣ��ͻ��˿���Ҳ�Ƽ�ʹ��
	///////////////////////////////////�µ�һ�ײ����ӿ�///////////////////////////////////////
	/**
	* ��ʼ�����Ӷ���
	* @param lpCallback �ص�����
	* @return ����0��ʾ�ɹ��������ʾʧ�ܣ�ͨ������GetErrorMsg���Ի�ȡ��ϸ������Ϣ
    * ���Ӧ�ò���Ҫ�κλص������������÷�������NULL���������Զ���ص���Ͷ���
	*/
	virtual int FUNCTION_CALL_MODE Create2BizMsg(CCallbackInterface *lpCallback) = 0;

	/**
    * ����ҵ������
    * @param lpMsg       ҵ����Ϣ�ӿ�ָ��
    * @param nAsy        0��ʾͬ���������ʾ�첽��
    * ͬ�����͵İ���ͨ������RecvBizMsg�����գ��첽���͵İ������յ�Ӧ������Զ������ص�����OnReceivedBizMsg��
    * @return ���ط��;�����������������ʾʧ�ܣ�ͨ������GetErrorMsg���Ի�ȡ��ϸ������Ϣ
    */
	virtual int FUNCTION_CALL_MODE SendBizMsg(IBizMessage* lpMsg,int nAsy = 0) = 0;
	
	/**
	* ��������
	* @param hSend     ���;��
	* @param lpMsg	   �յ�ҵ����Ϣָ��ĵ�ַ
	* @param uiTimeout ��ʱʱ�䣬��λ���룬0��ʾ���ȴ�
	* @param uiFlag    ����ѡ�0��ʾ���ճ�ʱ���Կɼ�������Receive�����գ�
    *                  JustRemoveHandle��ʾ�����ճ�ʱʱ����packet_idɾ�����Ժ����յ���������첽�ķ�ʽ�յ���
	* @return ����0��ʾ�ɹ��������ʾʧ�ܣ�ͨ������GetErrorMsg���Ի�ȡ��ϸ������Ϣ
	*/
	virtual int FUNCTION_CALL_MODE RecvBizMsg(int hSend, IBizMessage** lpMsg, unsigned uiTimeout = 1000, unsigned uiFlag = 0) = 0;

	/**
    * ��ȡ�ļ�����,һ����������ֻ��һ���ļ����£�������ھͷ���֮ǰ�Ľӿ�
    * @param szTopicName �ļ��������⣬�����ڷ������Ϣ�����ļ��������� 
	* @param lpCallBack �ص��ӿ�
	* @param szScanDir ɨ���ļ���Ŀ¼
    * @param szUpdateDir �ļ����´�Ÿ�Ŀ¼
	* @param iTimeOut ��ʱʱ��
    * @return �����ļ����½ӿ�ָ��
    */
    virtual CFileUpdateInterface* FUNCTION_CALL_MODE NewFileUpdate(const char* szTopicName,CFileUpdateCallbackInterface* lpCallBack ,const char* szScanDir,const char* szUpdateDir,unsigned int uiTimeOut = 5000) = 0;
	/**
	* ��ȡ�ļ����µ�������
	*/
	virtual const char* FUNCTION_CALL_MODE GetFileUpdateLastError() = 0;
	//20140609 majc ���ӻ�ȡ���һ��Ӧ��������ϸ��Ϣ�ӿ�
	/**
	* ȡ���ش�����Ϣ����ϸ��Ϣ
	* @param bAsyError 0��ʾͬ��(Ĭ��)�������ʾ�첽��
	* @return ������ϸ������Ϣ
	* @note ������Ϣ��ʽ��packType:xxx;funtionId:xxx;branchNo:zxx;systemNo:xxx;subSystemNO:xxx;packId:xxx;routerInfo:xxx,xxx,xxx,xxx,xxx,xxx;sendPath:xxx,xxx,xxx,xxx,xxx,xxx;returnCode:xxx;errorNo:xxx;errorInfo:xxx
	* packType-������
	* funtionId-���ܺ�
	* branchNo-��֧��
	* systemNo-ϵͳ��
	* subSystemNO-��ϵͳ��
	* packId-�����
	* routerInfo-Ŀ��·��
	* sendPath-������·��
	* returnCode-���ش�����
	* errorNo-�����
	* errorInfo-������Ϣ
	* ����˵����1��ͬ������ʱ������Receive���ص�lppData����ESBMessage��RetuenCode��Ϊ0ʱ���ã�����RecvBiz��RecvBizEx���ڷ���ֵΪ1��2��3��4ʱ���ã�����RecvBizMsg����GetReturnCode()��Ϊ0ʱ����
	*           2���첽����ʱ���ص�OnReceived��lpData����ESBMessage��RetuenCode��Ϊ0ʱ���ã��ص�OnReceivedBiz��OnReceivedBizEx��nResultΪ1��2��3��4ʱ���ã��ص�OnReceivedBizMsg��lpMsg��GetReturnCode()��Ϊ0ʱ����
	*/
	virtual const char * FUNCTION_CALL_MODE GetLastAnsError(bool bAsyError = 0) = 0;
	////////////////////////////////////////////////////////////////////////////////
};

#endif // _CONNECTION_INTERFACE_H_
