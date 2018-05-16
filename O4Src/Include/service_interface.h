///�������ӿڶ���
/*******************************************************
  Դ��������:service_interface.h
  �������Ȩ:�������ӹɷ����޹�˾
  ϵͳ����:  ����ͨ����Ϣ�������ӿڱ�׼
  ģ������:  ����ģ��
  ����˵��:  ��Ϣ�������ӿڶ���
 
             
  ��    ��:  maoyinjie
  ��������:  20071217
  ��    ע:  ��windows��ע�⺯�����÷�ʽ��__stdcall

  �޸���Ա��zhangly
  �޸����ڣ�20081219
  �޸�˵����ȥ������Ϣ��������SID��ǰ׺������С��Ϣ��ͷ����
*********************************************************/


#ifndef	SERVICE_INTERFACE_H
#define SERVICE_INTERFACE_H

//#define NODE_NAME_FLAG		'.'			/// ��Ϊ����Ⱥ�������ǽڵ����ı�־

#define SID_IMESSAGE_SERVICE	"com.hundsun.fbase.messageservice"

///�����Ǹ�����IMessageService�ӿڼ̳еĲ��ID,zhangly 20081219����
///���߳�ҵ������SID
#define SID_BIZ_PROC_C			"proc_c"      //�����ҵ������/�ӽ���
#define SID_PROC_S              "proc"      //�����ҵ������/������
#define SID_SERVICE_PROC		"proc"        //���߳�ҵ������
#define SID_SERVICE_MPROXY		"mproxy"      //���������
#define SID_SERVICE_ROUTER		"router"      //·�ɲ��
#define SID_CHANNEL_F2			"f2"          //F2ͨ�����
#define	SID_CHANNEL_F1			"f1"	      //F1ͨ�����
#define SID_CHANNEL_T2			"t2"          //T2/T1ͨ�����
#define SID_CHANNEL_IPC			"ipc"         //�ڴ�ͨ�����
#define SID_LOG_FILTER_SERVICE	"filter_log"  //��־���������
#define SID_OSPF				"ospf"        //OSPF���  


#include <Include/esb_message_factory_interface.h>

enum ServiceStatus
{
		ServiceUnInite		= 0x0000, /**< ��δ��ʼ�� */
		ServiceInitializing	= 0x0001, /**< ���ڳ�ʼ�� */
		ServiceInitialized	= 0x0002, /**< �Ѿ���ʼ�� */
		ServiceStarting		= 0x0003, /**< �������� */
		ServiceStarted		= 0x0004, /**< �Ѿ����� */
		ServiceUnRegister	= 0x0005, /**< ��δ��Routerע�� */ 
		ServiceRegistering	= 0x0006, /**< ������Routerע��,��δ�յ�router�Ļ�Ӧ */ 
		ServiceReady		= 0x0007, /**< ׼������,������������ */
		ServicePause		= 0x0008, /**< ������ͣ */
		ServiceStopping		= 0x0009, /**< ����ֹͣ */
		ServiceStoped		= 0x000a, /**< �Ѿ�ֹͣ */
		ServiceDisbale		= 0x0010  /**< ���񲻿���(�����������񲻿���,��������������) */
};


///	���д�����Ϣ�ĺ�����������ͨ�ýӿ�
/**
	�����͵Ĳ�������µ��ص�:
		�������ӵ�д�����Ϣ���߳�
		���ӵ�л�����Ϣ�Ķ���
		��Ϣ��������Թ���һ��������,����������ù���һ�����ʵķ�������.�����ڵ�ǰ�ķ��������в���һ���µķ������
		ɾ����ǰ�Ѿ������ڷ��������е��ض�����



	��Ϣ��һ����������ķ������ת,	�����е�ÿ�����񶼿��Ի�ô�����Ϣ�Ļ���.
	��Ϣת���Ĺ���:
		����Լ�ӵ���ϲ�����Լ��²����
		��ô�����²�������Ϣ�����Լ��Ĵ�����ת�����Լ����ϲ����
		�������ϲ�������Ϣ�����Լ��Ĵ����ת�����Լ����²����
	����û���²����ֻ���ϲ����ķ���,���յ����������Լ��ϲ�������Ϣ���Լ��������ת�����Լ����ϲ����
		���ڽ��յ������ϲ�ķ����,ֻ�����Լ��Ĵ���.����ת����Ϣ����������
	����û���ϲ����ֻ���²����ķ���,���յ����������Լ��²�������Ϣ���Լ��������ת�����Լ����²����
		���ڽ��յ������²�ķ����,ֻ�����Լ��Ĵ���.����ת����Ϣ����������
	
	һ�������ǵ�ʵ����,ʵ����ֻ��ͨ�����յ������������ڷ��������������������Ϣ,�����������,
	���������͵ķ����յ�����Ϣ�϶��������Լ����²�����ϲ�ķ���
	router�������ڶ���²����,�����Ĳ��һ��������һ���ϲ�������һ���²����.
	
**/


struct IMessageService : IKnown
{
public:
	///	Ϊ�������ṩ���������Ϣ,
	/**
		�÷������������������ⲿ����,��ʹ����Ϣ���뱾����.
		������ʵ��ʱ,����Ϣ�����Լ�����Ϣ���к󼴷���,��Ҫ�ڸú�����ֱ�ӽ�����Ϣ����
		�����Լ��Ĺ����߳����ʵ���ʱ��ȡ������Ϣ���д���
		�������ڲ�û���Լ��Ĺ����߳�,����ֱ�ӽ����˵����ߵ��̶߳���Ϣ���д���,����ʵ���߱�����ȷָ��
		��������Ϣ�Ĵ����б������ĳЩ����,�Ա����̵߳ľ�������
		���:
			IESBMessage*	 lpMessage:		�ⲿ�ṩ����Ϣ
			IMessageService* lpServiceFrom	Post��Ϣ�ķ���
		����:
			��
		����
			SUCC:	�ɹ�
			����:	ʧ��
	**/
	virtual int FUNCTION_CALL_MODE PostMsg(IESBMessage* lpMessage, IMessageService* lpServiceFrom)=0;
	


	///	ע����һ��������(��Ϣ�������һ������)
	virtual int FUNCTION_CALL_MODE RegisterNextService(IMessageService* lpService)=0;
	virtual int FUNCTION_CALL_MODE RegisterPrevService(IMessageService* lpService)=0;
	///	���Լ��ӷ���������ɾ��???
	virtual int FUNCTION_CALL_MODE RemoveService()=0;

	
	
	/// ��÷�������(�����ɿ�ܸ��ݼ���˳�������������)
	virtual const char* FUNCTION_CALL_MODE GetServiceID()=0;

	///	�ڴ�������ʱָ���÷�������
	/**
	���±��,��δ����ǰ,ȱʡΪ-1,����-1�ı��,������ת����Ϣʱ,���ؼ�¼ServiceSeqNo��ServiceInstantID����Ϣ
	**/
	virtual void FUNCTION_CALL_MODE SetServiceID(const char* HSID)=0;



	/// ���ӷ���״̬�Ĵ���
 	virtual  ServiceStatus  FUNCTION_CALL_MODE GetServiceStatus()=0;
 	virtual  int  FUNCTION_CALL_MODE RegisterService()=0;
 	virtual  int  FUNCTION_CALL_MODE SendSvrHeartBeat()=0;


};

#endif
