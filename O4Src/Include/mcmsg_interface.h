/*******************************************************
  源程序名称:mcmsg_interface.h
  软件著作权:恒生电子股份有限公司
  系统名称:  消息中心2.0
  模块名称:  消息封装模块接口
 作    者:  maoyj
  开发日期:  20120618
  备    注:  
  //	maoyinjie	2012-11-29	获取发布者的名字,并保留

*********************************************************/


#ifndef _HUNDSUN_MCMSG_INTERFACE_H_
#define _HUNDSUN_MCMSG_INTERFACE_H_

#include <Include/esb_message_interface.h>
#include <Include/service_interface.h>
class IMCMemCachedMsg
{
public:
	virtual int FUNCTION_CALL_MODE SetEsbMsg(IESBMessage* lpEsbMsg, bool bIsINMemCached=false)=0;
	virtual int FUNCTION_CALL_MODE Copy2EsbMsg(IESBMessage* lpEsbMsg)=0;

	virtual uint16 FUNCTION_CALL_MODE GetTopicNo()=0;
	virtual uint16 FUNCTION_CALL_MODE GetPublisherNo()=0;
	virtual uint32 FUNCTION_CALL_MODE GetGlbSeq()=0;
	virtual uint32 FUNCTION_CALL_MODE GetTimeStamp()=0;
	virtual uint32 FUNCTION_CALL_MODE GetInternalSeq()=0;
	virtual int	   FUNCTION_CALL_MODE GetMemSize()=0;
	virtual void*  FUNCTION_CALL_MODE GetBody(int &iBodyLen, int iLoops=0)=0;

	virtual int FUNCTION_CALL_MODE AddRef()=0;
	virtual int FUNCTION_CALL_MODE Release()=0;
	//	maoyinjie	2012-11-29	获取发布者的名字,并保留
	//	获得消息发布者的MC应用名,如果消息体没有该名字,则返回NULL
	virtual char* FUNCTION_CALL_MODE GetMCAppName()=0;
};

class IMCMessagePtr
{
public:
	virtual int FUNCTION_CALL_MODE SetMsg(IMCMemCachedMsg* lpMCMsg)=0;
	virtual int FUNCTION_CALL_MODE Release()=0;	//	释放消息,这里的消息没有引用计数的概念只能一次性使用,使用完毕加入池
	virtual ITagItem* FUNCTION_CALL_MODE GetRouteItemForChange()=0;		//	获得路由信息,以准备更改
	virtual ITagItem* FUNCTION_CALL_MODE GetSessionItemForChange()=0;	//	获得会话信息,以准备更改
	virtual int FUNCTION_CALL_MODE SetSubHead(void* lpHead, int iLen)=0;	//	直接更改订阅头部信息
	virtual int FUNCTION_CALL_MODE Copy2EsbMsg(IESBMessage* lpEsbMsg)=0;
	virtual uint16 FUNCTION_CALL_MODE GetTopicNo()=0;
	virtual uint16 FUNCTION_CALL_MODE GetPublisherNo()=0;
	virtual uint32 FUNCTION_CALL_MODE GetGlbSeq()=0;
	virtual void FUNCTION_CALL_MODE SetFlagTag(uint32 dwTag)=0;
	virtual uint32 FUNCTION_CALL_MODE GetFlagTag(void)=0;
	virtual int FUNCTION_CALL_MODE GetMemSize()=0;
};

#endif
