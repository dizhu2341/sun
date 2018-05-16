#ifndef __RELIABLE_TRANSMIT_INTERFACE_H__
#define __RELIABLE_TRANSMIT_INTERFACE_H__



#include <Include/service_interface.h>
#include <Include/glbdef.h>
#include <Include/esb_message_interface.h>


#define SID_RELIABLE_TRANS		"rtransmit"



struct IReliableTrans:IMessageService
{
	/**
	 *	供其他插件调用的发送接口, 接口里进行落地, 然后遍历发送, 堵塞型
	 *	支持多连接, 连接由对方节点名来区分, 返回packID
	**/
	virtual int Push(IESBMessage *lpMsg, char *lpPluginID, uint32 dwTimeOut = -1) = 0;

	virtual IESBMessage *Pop(const char *lpPluginID = NULL) = 0;

};



#ifdef __cplusplus
extern "C" { 
#endif

	///组件初始化
	/**
	 *@return int 版本号 yyyymmdd形式
	 */
	int  FUNCTION_CALL_MODE ReliableTrans_Init(void *lp, PFOnSetTimeOut);
	
	///取服务接口句柄
	/**
	 *@return void * 孤子模式
	 */
	IKnown * FUNCTION_CALL_MODE GetReliableTransInstance(void);

	///取服务接口依赖服务
	/**
	 *@param iIndex 
	 *@return IKnown * 依赖服务标识 
	 */
	char * FUNCTION_CALL_MODE GetReliableTransDependService(void *lp);
	
	///返回统一的AS基础服务组件查询接口 getxxxInfo()
	/**当基础服务组件动态加载时，通过本接口或以获取服务信息(包括xxxxInit(),getxxxxInterface()函数指针)
	 *@param void ** ppv    基础服务组件信息(输出参数)，
	 *@return 返回0表示查到所要的接口，否则返回负数
	 */
	int FUNCTION_CALL_MODE GetRTransmitInfo(int iIndex, tagBaseServiceInfo * ppv);

#ifdef __cplusplus
}
#endif



#endif



