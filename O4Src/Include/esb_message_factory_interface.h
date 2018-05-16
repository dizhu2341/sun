///恒生消息缓存接口定义
/*******************************************************
  源程序名称:esbq_interface.h
  软件著作权:恒生电子股份有限公司
  系统名称:  恒生消息缓存接口定义
  模块名称:  消息缓存
  功能说明:  消息缓存接口定义
             
  作    者:  maoyinjie
  开发日期:  20071217
  备    注:  在windows下注意函数调用方式：__stdcall

  修改人员：
  修改日期：
  修改说明：
  maoyinjie	2010/02/26
  修改IESBQ接口的GetDealMsgs函数声明

  20130719 xuxp 增加接口，用于获取当前队列里面是否存在对应的功能号
*********************************************************/


#ifndef ESB_MESSAGE_FACTORY_INTERFACE_H
#define ESB_MESSAGE_FACTORY_INTERFACE_H

#include <Include/esb_message_interface.h>


#define SID_ESB_MESSAGEFACTORY					"com.hundsun.fbase.esbmessagefactory"



///	存放消息的Q接口,确保线程安全
struct IESBQ : IKnown
{
	///	从消息队列中获得一个消息
	virtual IESBMessage* FUNCTION_CALL_MODE Pop(int iWaitTime, void** lppOwner, int iID=0)=0;
	///	往消息队列中插入一个新的消息
	virtual int FUNCTION_CALL_MODE Push(IESBMessage* lpMsg, void* lpOwner, int iID=0)=0;
	/// 获得Q中消息个数
	virtual int FUNCTION_CALL_MODE GetMSGsInQ()=0;
	//	初始化本Q内最多允许存在的消息个数，0不限制
	virtual int FUNCTION_CALL_MODE Init(int iMaxMsgsInQ=0)=0;
	//	获得Q内部的曾经存在的最多的消息个数
	virtual int FUNCTION_CALL_MODE GetMaxMSGsInQ()=0;

	//	
	virtual int FUNCTION_CALL_MODE GetIdles()=0;

	//	maoyinjie	2010/02/26
//	virtual inline int FUNCTION_CALL_MODE GetDealMsgs()=0;
	virtual int FUNCTION_CALL_MODE GetDealMsgs()=0;

	//20130719 xuxp 当前队列里面是否存在功能号
	virtual bool FUNCTION_CALL_MODE IsFuncExist(int iFunction)=0;
};




///	存放消息的优先级Q接口,确保线程安全
struct IPriESBQ : IKnown
{
	///	从优先级消息队列中获得一个消息
	virtual IESBMessage* FUNCTION_CALL_MODE Pop(int iWaitTime, void** lppOwner)=0;
	///	往优先级消息队列中插入一个新的消息
	virtual int FUNCTION_CALL_MODE Push(IESBMessage* lpMsg, void* lpOwner)=0;
	/// 获得优先级Q中消息个数
	virtual int FUNCTION_CALL_MODE GetMSGsInQ()=0;
	//	获得Q内部的曾经存在的最多的消息个数
	virtual int FUNCTION_CALL_MODE GetMaxMSGsInQ()=0;
	

	//	初始化本Q内最多允许存在的消息个数，0不限制
	virtual void FUNCTION_CALL_MODE SetMaxMsgs(int iMaxMsgsInQ)=0;
	//	初始化本Q内消息最多被推迟多少次就升级一次
	virtual void FUNCTION_CALL_MODE SetMaxDelays(int iMaxDealys)=0;
	//	执行老化过程
	virtual int FUNCTION_CALL_MODE Age()=0;
	//	删除优先级队列中,等待时间超过指定时间的消息(删除等待时间>=iWaitTime的所有消息)
	virtual int FUNCTION_CALL_MODE DeleteOldMsg(int iWaitTime)=0;
	//	获得优先级队列中的消息分布,主要返回:
	//	各个优先级的消息个数,特定等待时间的消息个数
	virtual int FUNCTION_CALL_MODE GetMsgInfoInQ(int iSpecifyPriMsgs[16], int* iSpecifyWaitTimeMsgs, int* iSpecifyWaitTimes, int* iMsgs)=0;
	virtual int FUNCTION_CALL_MODE GetDealMsgs()=0;
};


//	消息缓存工厂,应用需要用到消息以及Q时应该向工厂申请,线程安全
struct IESBMessageFactory  : IKnown
{
	// 申请Q队列
	virtual IESBQ* FUNCTION_CALL_MODE CreateESBQ()=0;
	// 释放Q队列
	virtual void FUNCTION_CALL_MODE DestroyESBQ(IESBQ* lpESBQ)=0;

	// 申请消息
	virtual IESBMessage* FUNCTION_CALL_MODE GetESBMsg()=0;

	// 申请优先级Q队列
	virtual IPriESBQ* FUNCTION_CALL_MODE CreatePriESBQ()=0;
	// 释放优先级Q队列
	virtual void FUNCTION_CALL_MODE DestroyPriESBQ(IPriESBQ* lpESBQ)=0;

	//修改人:xuqq
	//修改日期:2008-01-09
	//修改原因:增加一个OpenBuffer的接口
	virtual IESBMessage* FUNCTION_CALL_MODE OpenBuffer(char *lpBuffer, int iLen)=0;
	//-----------------------xuqq



	//	maqoyinjie 2009/06/19
	//	强制获得一个esbmsg,不受esbmsg工厂的限制
	virtual IESBMessage* FUNCTION_CALL_MODE GetESBMsgByForce()=0;
};




//消息缓存工厂引出函数---------------------------
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
