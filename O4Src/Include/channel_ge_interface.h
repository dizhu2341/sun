#ifndef __CHANNEL_GE_INTERFACE_H__
#define __CHANNEL_GE_INTERFACE_H__

/*
ͨ��ͨ�������Ϊҵ������Ϣ����ṩͨ��ͨ�Žӿڣ��������ҵ������Ҫ���뵽��Ϣ��ˮ�ߣ����Ϳ����Ѷȣ�
ͨ��ͨ������ӿڶ��壬����ҵ����ֻ��Ҫ��������������Ϊ��ͨ���������Ҫ��д��ˮ�߲��
*/

#include <Include/service_interface.h>
#include <Include/glbdef.h>
#include <Include/esb_message_interface.h>
#include <Include/biz_channel_interface.h>
//ͨ��ͨ������Ľӿ���
#define SID_CHANNEL_GE		   	"ge"
//ҵ������Ҫʹ�õĽӿ���
#define SID_BIZ_GE		   	"biz_ge"
#define GE_OK				0
#define GE_ERR_TRANSFER		-1
#define GE_ERR_NOSENDER		-2
#define GE_ERR_NOREGISTER	-3
#define GE_ERR_NOREADY		-4

struct IBizChannel:public IKnown
{
public:
	//�첽����֮ǰ���������������ͨ�ò��ע�ᣬ����ע��
	/*
		*@param IMessageService* lpSendSvr:	��Ҫ�첽���͵Ĳ��ָ��
		*@return	����ķ��ͱ�ʾ����ͨ�ò������ά���ķ�����ID��Ӧ��ƥ��ʹ�ã�Ψһ�ı�ʾ
					����0��ʾע��ʧ��
	*/
	virtual int Register(IBizPlugin* lpSendSvr) = 0;
	
	//�����ͨ�������Ҫ����������ȡ��ע��
	/*
		*@param const char* lpServerID:	���Ͳ��������
		*@return    ȡ���ɹ�����true,ʧ�ܷ���false
	*/
	virtual bool CancelRegister(int sendID) = 0;

	//0422�޸ģ�Ϊ�˷���ʹ�����ڵ��ú���ʧ�ܵ�ʱ�򣬻����Լ���ʹ����Ϣ���ʺ����ڲ����ͷŴ������Ϣ
	//ͬ�����ͽ��սӿڣ�����Ӧ����Ϣ
	/*
		*@param IESBMessage* lpSendMsg:	��Ҫ���͵�ESBMessage
		*@param bool& isTimeout:	 �Ƿ�ʱ�ı�־�����������true��ʾ��ʱ��false����ʱ
		*@param int iTimeOut:	 ��ʱʱ��

		*@return    �ɹ������յ���Ӧ��ʧ�ܷ���NULL
		ע�⣺�����еĴ���� IESBMessage ���������ָ�벻Ϊ�գ���ôlpSendMsg�Ͳ���Ҫ�ͷ�
			  ������ؿ�ָ�룬���ҳ�ʱ��־Ϊtrue����ôlpSendMsg�Ͳ���Ҫ�ͷţ�
			  ���������Ҫʹ�����Լ��ͷ�lpSendMsg
	*/

	virtual IESBMessage* SYNSendRecvMsg(IESBMessage* lpSendMsg, bool& isTimeout, int iTimeOut = -1) = 0;
	
	//�첽���ͽӿ�
	/*
		*@param IESBMessage* lpSendMsg:	��Ҫ���͵�ESBMessage		
		*@int asySendId ǰ��ע��֮�󷵻ص��첽�����߱��
		*@return 		����ֵ�ĺ���ǰ���к궨��
		ע�⣺�����еĴ���� IESBMessage �����سɹ��Ͳ���Ҫ�ͷ�lpSendMsg
			  ������Ҫ�ͷ�lpSendMsg
	*/
	//0428xuxpΪ�����ͨ��ͨ�����ܣ��첽�����߱����Ϊһ����������
	virtual int ASYSendMsg(IESBMessage* lpSendMsg, int asySendId) = 0;

};

#endif



