#ifndef __CHANNEL_BIZ_INTERFACE_H__
#define __CHANNEL_BIZ_INTERFACE_H__


#include <Include/glbdef.h>
#include <Include/esb_message_interface.h>

struct IBizPlugin:public IKnown
{
public:
	//收到消息时，业务插件提供的消息处理接口，提供给通用插件异步回调
	/*
		*@param IESBMessage* lpMsg:	接收到的消息
		注意：回调函数参数里面的IESBMessage是调用者自己维护，不需要使用的时候就释放
			  也就是说，lpMsg需要回调函数里面自己释放
	*/
	virtual int OnMsgRecv(IESBMessage* lpMsg) = 0;

	/// 获得服务的插件名
	virtual const char*  GetServiceID()=0;

};


#endif
