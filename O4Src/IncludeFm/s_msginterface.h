/**************************************************************************
单元名称：消息API
单元说明：消息中心相关的公共函数。
**************************************************************************/

#ifndef _MSG_INTERFACE_H_
#define _MSG_INTERFACE_H_ 

#include <Include/biz_comp_interface.h>
#include <Include/mc_bizcomponent_interface.h>
#include <IncludeFm/s_jc_public.h>
#include <string.h>

extern "C"
{
        
	int FUNCTION_CALL_MODE SubscribeTopic(IAS2Context * lpContext, IF2UnPacker * lpInUnPacker);
	int FUNCTION_CALL_MODE PublishTopic(IAS2Context * lpContext, IF2UnPacker * lpInUnPacker);
	int FUNCTION_CALL_MODE CancelSubscribe(IAS2Context * lpContext, IF2UnPacker * lpInUnPacker);
};

#endif
