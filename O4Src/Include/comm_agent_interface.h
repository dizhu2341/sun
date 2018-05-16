#ifndef __COMM_AGENT_INTERFACE_H__
#define __COMM_AGENT_INTERFACE_H__

#define ICOMM_AGENT "iCommAgent"
///和tuxedo里的TPNOREPLY宏的取值是一致的
#define TPNOREPLY	0x00000004

#include <Include/glbdef.h>
#include <Include/esb_message_interface.h>

struct ICommAgent : public IKnown
{
	///同步收发包接口
	virtual int FUNCTION_CALL_MODE SynSendRecvMsg(IESBMessage * lpSendMsg, IESBMessage ** lpBackMsg, int iTimeOut) = 0;
	///异步发包接口，返回一个handle用于接收时使用
	///iFlags为tpacall时传递进来的取值
	///当iFlags==TPNORPLY时，发送成功返回0，失败返回-1
	///当iFlags为其他值时，发送成功返回一个大于0的句柄，用于接收时使用。失败返回小于0的值
	virtual int FUNCTION_CALL_MODE AsynSendMsg(IESBMessage * lpSendMsg, int iFlags) = 0;
	///异步接收接口
	virtual int FUNCTION_CALL_MODE AsynGetMsg(int iHandle, IESBMessage ** lpBackMsg, int iTimeOut) = 0;
};


#endif
