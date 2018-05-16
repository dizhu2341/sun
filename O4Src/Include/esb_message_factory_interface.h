///������Ϣ����ӿڶ���
/*******************************************************
  Դ��������:esbq_interface.h
  �������Ȩ:�������ӹɷ����޹�˾
  ϵͳ����:  ������Ϣ����ӿڶ���
  ģ������:  ��Ϣ����
  ����˵��:  ��Ϣ����ӿڶ���
             
  ��    ��:  maoyinjie
  ��������:  20071217
  ��    ע:  ��windows��ע�⺯�����÷�ʽ��__stdcall

  �޸���Ա��
  �޸����ڣ�
  �޸�˵����
  maoyinjie	2010/02/26
  �޸�IESBQ�ӿڵ�GetDealMsgs��������

  20130719 xuxp ���ӽӿڣ����ڻ�ȡ��ǰ���������Ƿ���ڶ�Ӧ�Ĺ��ܺ�
*********************************************************/


#ifndef ESB_MESSAGE_FACTORY_INTERFACE_H
#define ESB_MESSAGE_FACTORY_INTERFACE_H

#include <Include/esb_message_interface.h>


#define SID_ESB_MESSAGEFACTORY					"com.hundsun.fbase.esbmessagefactory"



///	�����Ϣ��Q�ӿ�,ȷ���̰߳�ȫ
struct IESBQ : IKnown
{
	///	����Ϣ�����л��һ����Ϣ
	virtual IESBMessage* FUNCTION_CALL_MODE Pop(int iWaitTime, void** lppOwner, int iID=0)=0;
	///	����Ϣ�����в���һ���µ���Ϣ
	virtual int FUNCTION_CALL_MODE Push(IESBMessage* lpMsg, void* lpOwner, int iID=0)=0;
	/// ���Q����Ϣ����
	virtual int FUNCTION_CALL_MODE GetMSGsInQ()=0;
	//	��ʼ����Q�����������ڵ���Ϣ������0������
	virtual int FUNCTION_CALL_MODE Init(int iMaxMsgsInQ=0)=0;
	//	���Q�ڲ����������ڵ�������Ϣ����
	virtual int FUNCTION_CALL_MODE GetMaxMSGsInQ()=0;

	//	
	virtual int FUNCTION_CALL_MODE GetIdles()=0;

	//	maoyinjie	2010/02/26
//	virtual inline int FUNCTION_CALL_MODE GetDealMsgs()=0;
	virtual int FUNCTION_CALL_MODE GetDealMsgs()=0;

	//20130719 xuxp ��ǰ���������Ƿ���ڹ��ܺ�
	virtual bool FUNCTION_CALL_MODE IsFuncExist(int iFunction)=0;
};




///	�����Ϣ�����ȼ�Q�ӿ�,ȷ���̰߳�ȫ
struct IPriESBQ : IKnown
{
	///	�����ȼ���Ϣ�����л��һ����Ϣ
	virtual IESBMessage* FUNCTION_CALL_MODE Pop(int iWaitTime, void** lppOwner)=0;
	///	�����ȼ���Ϣ�����в���һ���µ���Ϣ
	virtual int FUNCTION_CALL_MODE Push(IESBMessage* lpMsg, void* lpOwner)=0;
	/// ������ȼ�Q����Ϣ����
	virtual int FUNCTION_CALL_MODE GetMSGsInQ()=0;
	//	���Q�ڲ����������ڵ�������Ϣ����
	virtual int FUNCTION_CALL_MODE GetMaxMSGsInQ()=0;
	

	//	��ʼ����Q�����������ڵ���Ϣ������0������
	virtual void FUNCTION_CALL_MODE SetMaxMsgs(int iMaxMsgsInQ)=0;
	//	��ʼ����Q����Ϣ��౻�Ƴٶ��ٴξ�����һ��
	virtual void FUNCTION_CALL_MODE SetMaxDelays(int iMaxDealys)=0;
	//	ִ���ϻ�����
	virtual int FUNCTION_CALL_MODE Age()=0;
	//	ɾ�����ȼ�������,�ȴ�ʱ�䳬��ָ��ʱ�����Ϣ(ɾ���ȴ�ʱ��>=iWaitTime��������Ϣ)
	virtual int FUNCTION_CALL_MODE DeleteOldMsg(int iWaitTime)=0;
	//	������ȼ������е���Ϣ�ֲ�,��Ҫ����:
	//	�������ȼ�����Ϣ����,�ض��ȴ�ʱ�����Ϣ����
	virtual int FUNCTION_CALL_MODE GetMsgInfoInQ(int iSpecifyPriMsgs[16], int* iSpecifyWaitTimeMsgs, int* iSpecifyWaitTimes, int* iMsgs)=0;
	virtual int FUNCTION_CALL_MODE GetDealMsgs()=0;
};


//	��Ϣ���湤��,Ӧ����Ҫ�õ���Ϣ�Լ�QʱӦ���򹤳�����,�̰߳�ȫ
struct IESBMessageFactory  : IKnown
{
	// ����Q����
	virtual IESBQ* FUNCTION_CALL_MODE CreateESBQ()=0;
	// �ͷ�Q����
	virtual void FUNCTION_CALL_MODE DestroyESBQ(IESBQ* lpESBQ)=0;

	// ������Ϣ
	virtual IESBMessage* FUNCTION_CALL_MODE GetESBMsg()=0;

	// �������ȼ�Q����
	virtual IPriESBQ* FUNCTION_CALL_MODE CreatePriESBQ()=0;
	// �ͷ����ȼ�Q����
	virtual void FUNCTION_CALL_MODE DestroyPriESBQ(IPriESBQ* lpESBQ)=0;

	//�޸���:xuqq
	//�޸�����:2008-01-09
	//�޸�ԭ��:����һ��OpenBuffer�Ľӿ�
	virtual IESBMessage* FUNCTION_CALL_MODE OpenBuffer(char *lpBuffer, int iLen)=0;
	//-----------------------xuqq



	//	maqoyinjie 2009/06/19
	//	ǿ�ƻ��һ��esbmsg,����esbmsg����������
	virtual IESBMessage* FUNCTION_CALL_MODE GetESBMsgByForce()=0;
};




//��Ϣ���湤����������---------------------------
#ifdef __cplusplus
extern "C" { 
#endif
	
IKnown*	FUNCTION_CALL_MODE GetESBMessageFactoryInstance();
int		FUNCTION_CALL_MODE GetESBMessageFactoryInit(void * lpInstance,PFOnSetTimeOut pfOnSetTimeOut = NULL);
char*	FUNCTION_CALL_MODE GetESBMessageFactoryDependSvr(void * lpInstance);
int		FUNCTION_CALL_MODE GetESBMessageFactoryInfo(int iIndex, tagBaseServiceInfo * ppv );
	
#ifdef __cplusplus
}
#endif


#endif
