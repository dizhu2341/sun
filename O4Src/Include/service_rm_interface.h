///service_rm ����ӿ�ID���弰���׼��������
/*********************************************************************************************
  Դ��������: service_rm_interface.h
  �������Ȩ: �������ӹɷ����޹�˾
  ��������:  
  ģ������:  fsc_service_rm
  �������:  �ɿ��鲥���
  ����˵��:  

  ����ĵ�:  

  ��    ��:  zhujinqi
  ��������:  2013-11-11
  ��    ע:  
  �޸ļ�¼: 
*********************************************************************************************/

#ifndef __SERVICE_RM_INTERFACE_H__
#define __SERVICE_RM_INTERFACE_H__

#include <Include/plugin_interface.h>
#include <Include/inttypes.h>

///����ӿ�ID����
#define SID_SERVICE_RM "com.hundsun.service_rm"




///�ɿ��鲥�����ߵ�˽��������Ϣ
typedef struct tgRMSenderCfg
{
	uint8					nSenderID;

	///�鲥����
	const char *			szRMName;

	///������鲥��IP��ַ��������A
	const char *			szIPa;

	///������鲥��IP��ַ��������B
	const char *			szIPb;

	///�鲥���ݻ��ͣ�����0ʱ��ֹ���������ղ����Լ��鲥��ȥ������
	uint8					nMulticastLoop;
	///ռλ
	//uint8					dummy0[7];
}RMSenderCfg;

///�ɿ��鲥�����ߵ�˽��������Ϣ
typedef struct tgRMReceiverCfg
{
	///�����߱�ţ���Χ1~31��0������������
	uint8					nReceiverID;

	///�鲥����
	const char *			szRMName;

	///������鲥��IP��ַ��������A
	const char *			szIPa;
	///������鲥��IP��ַ��������B
	const char *			szIPb;
	
	///ռλ
	//uint8					dummy0[7];
}RMReceiverCfg;

class CRMSenderInterface;

class IRMSenderCallback : public IKnown
{
public:
	/**
	* ȷ��״̬�ص��������̶�ÿ��ص�һ��
	* @param lpSender �ɿ��鲥������
	* @param lpArg CRMSenderInterface.Create ʱ����Ĳ���
	* @param lpIndex ��ǰ��ȷ�ϼ�¼��ţ���nReceiverCount+1������1~nReceiverCount�����ֱ��Ӧһ�������ߣ���0���������е����ֵ
	* @param lpIndex2 ��ǰ��ȷ�ϼ�¼��ţ���ǰ��Ĳ���Ǳ��ֶλ����������£�����Ļ��ж����ӲŸ���
	* @param lpNoACKTime �ϴ��յ�ACK�����ڵ�ʱ�䣬��λ���룬��nReceiverCount+1������1~nReceiverCoun���ֱ��Ӧһ�������ߣ���0���������е����ֵ
	* @return Ŀǰ����Ϊ0
	*/
	virtual int FUNCTION_CALL_MODE OnAckStatus(CRMSenderInterface *lpSender, void *lpArg, uint32 *lpIndex, uint32 *lpIndex2, uint32 *lpNoACKTime) = 0;

	/**
	* ����ص�������������/�����������������������
	* @param lpSender �ɿ��鲥������
	* @param lpArg IRMSender.Create / IRMReceiver.Create ʱ����Ĳ���
	* @param nIndex ���ݼ�¼���
	* @param lpData ���ݼ�¼ָ�룬��ָ������¼
	* @param nLength ���ݼ�¼����
	* @return Ŀǰ����Ϊ0
	*/
	//virtual int FUNCTION_CALL_MODE OnProcess(CRMSenderInterface *lpSender, void *lpArg, uint32 nIndex, uint8 nCategory, const void *lpData, uint32 nLength) = 0;
	virtual int FUNCTION_CALL_MODE OnProcess(CRMSenderInterface *lpSender, void *lpArg, uint32 nIndex, const void *lpData, uint32 nLength) = 0;

	/**
	* ����ص�������һ�����������й����е�һЩ����Ż�ص�
	* @param lpSender �ɿ��鲥������
	* @param lpArg CRMSenderInterface.Create ʱ����Ĳ���
	* @param nErrorNo ����ţ�С�� \ref RM_ERR_BASE ����errno
	* @param szErrorMsg ������Ϣ
	* @return Ŀǰ����Ϊ0
	*/
	virtual int FUNCTION_CALL_MODE OnError(CRMSenderInterface *lpSender, void *lpArg, int32 nErrorNo, const char *szErrorMsg) = 0;
	
	/**
	* ����״̬�ص�������ÿ�ν������ؾͻص�����Ӧ�ò����ͳ���������
	* @param lpSender �ɿ��鲥������
	* @param lpArg CRMSenderInterface.Create / CRMReceiverInterface.Create ʱ����Ĳ���
	* @param nCurrentIndex ��ǰ���͵ļ�¼���
	* @param nMaxOfAllMinNotAck ���н����ߵ���Сδȷ������е����ֵ
	* @return Ŀǰ����Ϊ0
	*/
	//virtual int FUNCTION_CALL_MODE OnFlowControlStatus(CRMSenderInterface *lpSender, void *lpArg, uint32 nCurrentIndex, uint32 nMaxOfAllMinNotAck) = 0;


	////////////////////////////////////����Ϊ��������//////////////////////////////////////
	/**
	* �����߲�ȱʱ�������ݲ����ڣ���Ӧ�ò������ȡ��¼�ص�����
	* @param lpSender �ɿ��鲥������
	* @param lpArg IRMSender.Create ʱ����Ĳ���
	* @param nIndex ���ݼ�¼���
	* @param lpLength �������ݼ�¼����
	* @return ��¼ָ��
	*/
	virtual void * FUNCTION_CALL_MODE OnGetData(CRMSenderInterface *lpSender, void *lpArg, uint32 nIndex, uint32 *lpLength) = 0;


	/**
	* ����״̬�ص�������ÿ�ν������ؾͻص�����Ӧ�ò����ͳ���������
	* @param lpSender �ɿ��鲥������
	* @param lpArg IRMSender.Create ʱ����Ĳ���
	* @param nToSendUDPNo ��ǰ�����͵�UDP�����
	* @param nWaitAckUDPNo ��ǰ��ȷ�ϵ�UDP�����
	* @return Ŀǰ����Ϊ0
	*/
	virtual int FUNCTION_CALL_MODE OnFlowControl(CRMSenderInterface *lpSender, void *lpArg, uint32 nToSendUDPNo, uint32 nWaitAckUDPNo) = 0;

};


///�ɿ��鲥�����ߡ�ע�����ܶ��̵߳����䷽��
class CRMSenderInterface : public IKnown
{
public:	
	//�ص�����ע��״̬������ϣ���ע��ĺ����ص����е�ʵ�ֿ�Ϊ��
	enum CallbackRegStatus
	{
		ON_GET_DATA 			= 0x01, 	/**< OnGetData */
		ON_PROCESS 				= 0x02, 	/**< OnProcess */
		ON_ERROR 				= 0x04, 	/**< OnError */
		ON_FLOW_CONTROL 		= 0x08,		/**< OnFlowControl */
		ON_ACK_STATUS 			= 0x10		/**< OnAckStatus */
	};
	
	/**
	* ��ȡ���ã�����ʼ����
	* @param lpSenderCfg �鲥��˽�����ã�����AB��������Ϣ��
	* @param lpCallback �ص���
	* @param lpArg ����������ָ�����ص������н�ԭ������
	* @param nCallbackStatus �ص�����ʹ�ñ�־����ʹ�õĻص������ص�����ʵ�ֿ���Ϊ��
	* @return 0��ʾ�ɹ��������ʾʧ��
	*/
	virtual int FUNCTION_CALL_MODE Create(RMSenderCfg *lpSenderCfg, IRMSenderCallback *lpCallback, void *lpArg = NULL, uint32 nCallbackStatus = ON_PROCESS|ON_ERROR) = 0;

	/**
	* ����
	* @param nInitialIndex ����ʱ��ָ����ŵļ�¼��ʼ�鲥
	* @param nFlowFlag ����ʱָ���Ƿ�������� 0-������ 1-����
	* @return 0��ʾ�ɹ��������ʾʧ��
	*/
	virtual int FUNCTION_CALL_MODE Start(uint32 nInitialIndex = 0, uint8 nFlowFlag = 0) = 0;

	/**
	* ֹͣ
	* @return 0��ʾ�ɹ��������ʾʧ��
	*/
	virtual int FUNCTION_CALL_MODE Stop() = 0;

	/**
	* �����Ҫ�鲥�ļ�¼���ݣ����ⲿ����������ʱ���ã��ڲ��Ḵ��һ���ڴ�
	* @param lpData ���ݼ�¼ָ�룬��ָ������¼
	* @param nLength ���ݼ�¼����
	* @return ��ţ�-1��ʾ����
	*/
	//virtual uint32 FUNCTION_CALL_MODE PushData(uint8 nCategory, const void *lpData, uint32 nLength) = 0;
	virtual uint32 FUNCTION_CALL_MODE PushData(const void *lpData, uint32 nLength) = 0;

	/**
	* �����Ҫ�鲥�ļ�¼���ݣ����ⲿ����������ʱ���ã��ڲ�ֻ��¼ָ�룬�������豣ָ֤��һֱ��Ч
	* @param lpData ���ݼ�¼ָ�룬��ָ������¼
	* @param nLength ���ݼ�¼����
	* @return ��ţ�-1��ʾ����
	*/
	//virtual uint32 FUNCTION_CALL_MODE PushDataPtr(uint8 nCategory, const void *lpData, uint32 nLength) = 0;
	virtual uint32 FUNCTION_CALL_MODE PushDataPtr(const void *lpData, uint32 nLength) = 0;

	/**
	* ���Խ����ߣ�����������ȷ��
	* @param nReceiverID �����߱�ţ���Χ1~31
	* @return ��
	*/
	virtual void FUNCTION_CALL_MODE IgnoreReceiver(uint8 nReceiverID) = 0;

	/**
	* ȡ��ӽ�ȥ�����ݼ�¼
	* @param nIndex ���ݼ�¼���
	* @param nLength �������ݼ�¼����
	* @return ���ݼ�¼ָ�룬NULL��ʾʧ��
	*/
	//virtual void * FUNCTION_CALL_MODE GetData(uint32 nIndex, uint16 &nLength, uint8 &nCategory) = 0;
	virtual void * FUNCTION_CALL_MODE GetData(uint32 nIndex, uint32 &nLength) = 0;

	/**
	* ���û���鲥�����ߣ����ڱ������OnProcess�¼�������һ�鲥��ַ���ͣ������ڲ���������
	*��������ϵ����ʵ�������Ѿ�����Create��δ����Start�����ܶ���ackQuickģʽ
	* @param lpRMSenderInterface �鲥������ָ��
	* @return 0��ʾ�ɹ��������ʾʧ��
	*/
	//virtual int FUNCTION_CALL_MODE SetBuddy(CRMSenderInterface *lpRMSenderInterface) = 0;

	///////////////////////////////////����Ϊ��������///////////////////////////////////////
	/**
	* ���ü�¼ָ�룬������ó�NULL���ڲ�ȱ��ͨ��lpfnOnGetData�ص�
	* @param nIndex ���ݼ�¼���
	* @param lpData ���ݼ�¼ָ�룬����ΪNULL����ΪNULLʱ��������Ч��ָ��
	* @return ��ţ�-1��ʾ����
	*/
	virtual int FUNCTION_CALL_MODE ResetDataPtr(uint32 nIndex, const void *lpData) = 0;


};

class CRMReceiverInterface;

class IRMReceiverCallback : public IKnown
{
public:
	/**
	* ����״̬�ص��������̶�ÿ��ص�һ��
	* @param lpReceiver �ɿ��鲥������
	* @param lpArg CRMReceiverInterface.Create ʱ����Ĳ���
	* @param nNoRecvTime �ϴ��յ���Ч���ݵ����ڵ�ʱ��
	* @param nIndex ��ǰ�����ռ�¼���
	* @return Ŀǰ����Ϊ0
	*/
	//virtual int FUNCTION_CALL_MODE OnRecvStatus(CRMReceiverInterface *lpReceiver, void *lpArg, uint32 nMinGapIndex, uint32 nNoRecvTime)= 0;
	//virtual int FUNCTION_CALL_MODE OnRecvStatus(CRMReceiverInterface *lpReceiver, void *lpArg, uint32 *lpNoRecvTime, uint32 nIndex) = 0;
	virtual int FUNCTION_CALL_MODE OnRecvStatus(CRMReceiverInterface *lpReceiver, void *lpArg, uint32 lpNoRecvTime, uint32 nIndex) = 0;

	/**
	* ����ص������������������������
	* @param lpReceiver �ɿ��鲥������
	* @param lpArg CRMReceiverInterface.Create ʱ����Ĳ���
	* @param nIndex ���ݼ�¼���
	* @param lpData ���ݼ�¼ָ�룬��ָ������¼
	* @param nLength ���ݼ�¼����
	* @return Ŀǰ����Ϊ0
	*/
	//virtual int FUNCTION_CALL_MODE OnProcess(CRMReceiverInterface *lpReceiver, void *lpArg, uint32 nIndex, uint8 nCategory, const void *lpData, uint32 nLength)= 0;
	virtual int FUNCTION_CALL_MODE OnProcess(CRMReceiverInterface *lpReceiver, void *lpArg, uint32 nIndex, const void *lpData, uint32 nLength)= 0;

	/**
	* �����������ڴ�ص��������������յ����ݺ�Ϊÿ����¼������������ڴ档�ص�����
	* ΪNULLʱ�������ڲ��������롣
	* @param lpReceiver �ɿ��鲥������
	* @param lpArg IRMReceiver.Create ʱ����Ĳ���
	* @param nIndex ���ݼ�¼���
	* @param nLength ���ݼ�¼����
	* @return ������ڴ�ָ�룬NULL��ʾʧ��
	*/
	//virtual void * FUNCTION_CALL_MODE OnGetMemory(CRMReceiverInterface *lpReceiver, void *lpArg, uint32 nIndex, uint8 nCategory, const void *lpData, uint32 nLength)= 0;
	virtual void * FUNCTION_CALL_MODE OnGetMemory(CRMReceiverInterface *lpReceiver, void *lpArg, uint32 nIndex, uint32 nLength)= 0;


	/**
	* ����ص�������һ�����������й����е�һЩ����Ż�ص�
	* @param lpReceiver �ɿ��鲥������
	* @param lpArg CRMSenderInterface.Create / CRMReceiverInterface.Create ʱ����Ĳ���
	* @param nErrorNo ����ţ�С�� \ref RM_ERR_BASE ����errno
	* @param szErrorMsg ������Ϣ
	* @return Ŀǰ����Ϊ0
	*/
	virtual int FUNCTION_CALL_MODE OnError(CRMReceiverInterface *lpReceiver, void *lpArg, int32 nErrorNo, const char *szErrorMsg)= 0;
			
	/**
	* ��ȱ״̬�ص�������ÿ�η���ȱ�ͻص�����Ӧ�ò����ͳ�Ʋ�ȱ���
	* @param pReceiver �ɿ��鲥������
	* @param lpArg CRMSenderInterface.Create / CRMReceiverInterface.Create ʱ����Ĳ���
	* @param nMinGapIndex ��С��ȱ�ļ�¼���
	* @return Ŀǰ����Ϊ0
	*/
	//virtual int FUNCTION_CALL_MODE OnFilGapStatus(CRMReceiverInterface *lpReceiver, void *lpArg, uint32 nMinGapIndex)= 0;


	////////////////////////////////////����Ϊ��������//////////////////////////////////////
	/**
	* �������յ��·�Ƭ�ص�����
	* @param lpReceiver �ɿ��鲥������
	* @param lpArg IRMReceiver.Create ʱ����Ĳ���
	* @param nIndex ���ݼ�¼���
	* @param lpData ���ݼ�¼ָ�룬��ָ������¼
	* @param nLength ���ݼ�¼����
	* @param nOffset ��ǰ��Ƭ��ƫ����
	* @param nSegmentLength ��ǰ��Ƭ�ĳ���
	* @param bCompleted �Ƿ��Ѿ�������
	* @return ĿǰӦ����0����δʹ��
	*/
	virtual int FUNCTION_CALL_MODE OnNewSegment(CRMReceiverInterface *lpReceiver, void *lpArg, uint32 nIndex, const void *lpData, uint32 nLength, uint32 nOffset, uint32 nSegmentLength, uint8 bCompleted)= 0;

	/**
	* ��ȱ״̬�ص�����������Ϊ�գ�ÿ�η���ȱ�ͻص�����Ӧ�ò����ͳ�Ʋ�ȱ���
	* @param pReceiver �ɿ��鲥������
	* @param lpArg CRMReceiverInterface.Create ʱ����Ĳ���
	* @param nMinGapIndex ��С��ȱ�ļ�¼���
	* @return Ŀǰ����Ϊ0
	*/
	virtual int FUNCTION_CALL_MODE OnFillGap(CRMReceiverInterface *lpReceiver, void *lpArg, uint32 nMinGapIndex)= 0;
};

///�ɿ��鲥�����ߡ�ע�����ܶ��̵߳����䷽��
class CRMReceiverInterface : public IKnown
{
public:
	//�ص�����ע��״̬������ϣ���ע��ĺ����ص����е�ʵ�ֿ�Ϊ��
	enum CallbackRegStatus
	{
		ON_NEW_SEGMENT 		= 0x01, 	/**< OnNewSegment */
		ON_PROCESS 			= 0x02, 	/**< OnProcess */
		ON_GET_MEMORY 		= 0x04, 	/**< OnGetMemory */
		ON_ERROR 			= 0x08, 	/**< OnError */
		ON_FILL_GAP 		= 0x10,		/**< OnFillGap */
		ON_RECV_STATUS 		= 0x20		/**< OnRecvStatus */
	};

	/**
	* ��ȡ���ã�����ʼ����
	* @param lpReceiverCfg �鲥��˽�����ã�����AB��������Ϣ��
	* @param lpCallback �ص���
	* @param lpArg ����������ָ�����ص������н�ԭ������
	* @param nCallbackStatus �ص�����ʹ�ñ�־����ʹ�õĻص������ص�����ʵ�ֿ���Ϊ��
	* @return 0��ʾ�ɹ��������ʾʧ��
	*/
	virtual int FUNCTION_CALL_MODE Create(RMReceiverCfg *lpReceiverCfg, IRMReceiverCallback *lpCallback, void *lpArg = NULL, uint32 nCallbackStatus = ON_PROCESS|ON_ERROR)= 0;
	
	/**
	* ����
	* @param nInitialIndex ����ʱ����ָ�����֮ǰ�ļ�¼���в�ȱ
	* @param nFlowFlag ����ʱָ���Ƿ�������� 0-������ 1-����
	* @return 0��ʾ�ɹ��������ʾʧ��
	*/
	virtual int FUNCTION_CALL_MODE Start(uint32 nInitialIndex = 0, uint8 nFlowFlag = 0) = 0;

	/**
	* ֹͣ
	* @return 0��ʾ�ɹ��������ʾʧ��
	*/
	virtual int FUNCTION_CALL_MODE Stop() = 0;

	/**
	* ȡ�յ������ݼ�¼
	* @param nIndex ���ݼ�¼���
	* @param nLength �������ݼ�¼����
	* @return ���ݼ�¼ָ�룬NULL��ʾʧ��
	*/
	//virtual void * FUNCTION_CALL_MODE GetData(uint32 nIndex, uint16 &nLength, uint8 &nCategory) = 0;
	virtual void * FUNCTION_CALL_MODE GetData(uint32 nIndex, uint32 &nLength) = 0;
	
	/**
	* ���û���鲥�����ߣ����ڱ������OnProcess�¼�������һ�鲥��ַ���ͣ������ڲ���������
	*��������ϵ����ʵ�������Ѿ�����Create��δ����Start
	* @param lpRMSenderInterface �鲥������ָ��
	* @return 0��ʾ�ɹ��������ʾʧ��
	*/
	//virtual int FUNCTION_CALL_MODE SetBuddy(CRMSenderInterface *lpRMSenderInterface) = 0;

	////////////////////////////////////����Ϊ��������//////////////////////////////////////
	/**
	* ���ü�¼ָ�룬һ��������OnProcess�ص�������ɺ����ó�NULL
	* @param nIndex ���ݼ�¼���
	* @param lpData ���ݼ�¼ָ�룬����ΪNULL����ΪNULLʱ��������Ч��ָ��
	* @return ��ţ�-1��ʾ����
	*/
	virtual int FUNCTION_CALL_MODE ResetDataPtr(uint32 nIndex, const void *lpData) = 0;
};


///����ӿڶ���
class IF2RMService : public IKnown
{
public:
	/**
	* ��ȡ�ɿ��鲥������
	*/
	virtual CRMSenderInterface * FUNCTION_CALL_MODE NewRMSender() = 0; 

	/**
	* ��ȡ�ɿ��鲥������
	*/
	virtual CRMReceiverInterface * FUNCTION_CALL_MODE NewRMReceiver() = 0;

	/**
	* �ͷſɿ��鲥������
	*/
	virtual void FreeRMSender(CRMSenderInterface *lpRMSender) = 0;

	/**
	* �ͷſɿ��鲥������
	*/
	virtual void FreeRMReceiver(CRMReceiverInterface *lpRMReceiver) = 0;

};



///���������׼�������������ܼ�����˵���μ�Include/plugin_interface.h
#ifdef __cplusplus
extern "C" {
#endif
	///ȡ���ʵ��
	IKnown *FUNCTION_CALL_MODE GetServiceRMInstance();
	
	///�����ʼ��
	int FUNCTION_CALL_MODE ServiceRMInit(void *lpInstance,PFOnSetTimeOut pfOnSetTimeOut = NULL);
	
	///ȡ����������������ID��
	char *FUNCTION_CALL_MODE GetSvrServiceRMDependSvr(void *lpInstance);
	
	///��ѯ������еĲ����Ϣ
	int FUNCTION_CALL_MODE GetServiceRMInfo(int iIndex, tagBaseServiceInfo *ppv );
	
#ifdef __cplusplus
}
#endif

#endif       /*end def __SERVICE_RM_INTERFACE_H__*/

