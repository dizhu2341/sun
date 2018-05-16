#ifndef __COMM_AGENT_INTERFACE_H__
#define __COMM_AGENT_INTERFACE_H__

#define ICOMM_AGENT "iCommAgent"
///��tuxedo���TPNOREPLY���ȡֵ��һ�µ�
#define TPNOREPLY	0x00000004

#include <Include/glbdef.h>
#include <Include/esb_message_interface.h>

struct ICommAgent : public IKnown
{
	///ͬ���շ����ӿ�
	virtual int FUNCTION_CALL_MODE SynSendRecvMsg(IESBMessage * lpSendMsg, IESBMessage ** lpBackMsg, int iTimeOut) = 0;
	///�첽�����ӿڣ�����һ��handle���ڽ���ʱʹ��
	///iFlagsΪtpacallʱ���ݽ�����ȡֵ
	///��iFlags==TPNORPLYʱ�����ͳɹ�����0��ʧ�ܷ���-1
	///��iFlagsΪ����ֵʱ�����ͳɹ�����һ������0�ľ�������ڽ���ʱʹ�á�ʧ�ܷ���С��0��ֵ
	virtual int FUNCTION_CALL_MODE AsynSendMsg(IESBMessage * lpSendMsg, int iFlags) = 0;
	///�첽���սӿ�
	virtual int FUNCTION_CALL_MODE AsynGetMsg(int iHandle, IESBMessage ** lpBackMsg, int iTimeOut) = 0;
};


#endif
