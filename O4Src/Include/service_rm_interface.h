///service_rm 插件接口ID定义及其标准引出函数
/*********************************************************************************************
  源程序名称: service_rm_interface.h
  软件著作权: 恒生电子股份有限公司
  服务名称:  
  模块名称:  fsc_service_rm
  插件类型:  可靠组播插件
  功能说明:  

  相关文档:  

  作    者:  zhujinqi
  开发日期:  2013-11-11
  备    注:  
  修改记录: 
*********************************************************************************************/

#ifndef __SERVICE_RM_INTERFACE_H__
#define __SERVICE_RM_INTERFACE_H__

#include <Include/plugin_interface.h>
#include <Include/inttypes.h>

///插件接口ID定义
#define SID_SERVICE_RM "com.hundsun.service_rm"




///可靠组播发送者的私有配置信息
typedef struct tgRMSenderCfg
{
	uint8					nSenderID;

	///组播组名
	const char *			szRMName;

	///需加入组播的IP地址（网卡）A
	const char *			szIPa;

	///需加入组播的IP地址（网卡）B
	const char *			szIPb;

	///组播数据回送，等于0时禁止，本机将收不到自己组播出去的数据
	uint8					nMulticastLoop;
	///占位
	//uint8					dummy0[7];
}RMSenderCfg;

///可靠组播接收者的私有配置信息
typedef struct tgRMReceiverCfg
{
	///接收者编号，范围1~31，0保留给发送者
	uint8					nReceiverID;

	///组播组名
	const char *			szRMName;

	///需加入组播的IP地址（网卡）A
	const char *			szIPa;
	///需加入组播的IP地址（网卡）B
	const char *			szIPb;
	
	///占位
	//uint8					dummy0[7];
}RMReceiverCfg;

class CRMSenderInterface;

class IRMSenderCallback : public IKnown
{
public:
	/**
	* 确认状态回调函数，固定每秒回调一次
	* @param lpSender 可靠组播发送者
	* @param lpArg CRMSenderInterface.Create 时传入的参数
	* @param lpIndex 当前待确认记录序号，共nReceiverCount+1个，第1~nReceiverCount个，分别对应一个接收者，第0个是所有中的最大值
	* @param lpIndex2 当前待确认记录序号，与前面的差别是本字段会无条件更新，上面的会判断增加才更新
	* @param lpNoACKTime 上次收到ACK到现在的时间，单位毫秒，共nReceiverCount+1个，第1~nReceiverCoun个分别对应一个接收者，第0个是所有中的最大值
	* @return 目前必须为0
	*/
	virtual int FUNCTION_CALL_MODE OnAckStatus(CRMSenderInterface *lpSender, void *lpArg, uint32 *lpIndex, uint32 *lpIndex2, uint32 *lpNoACKTime) = 0;

	/**
	* 处理回调函数，发送者/接收者在数据已连续后调用
	* @param lpSender 可靠组播发送者
	* @param lpArg IRMSender.Create / IRMReceiver.Create 时传入的参数
	* @param nIndex 数据记录序号
	* @param lpData 数据记录指针，是指单条记录
	* @param nLength 数据记录长度
	* @return 目前必须为0
	*/
	//virtual int FUNCTION_CALL_MODE OnProcess(CRMSenderInterface *lpSender, void *lpArg, uint32 nIndex, uint8 nCategory, const void *lpData, uint32 nLength) = 0;
	virtual int FUNCTION_CALL_MODE OnProcess(CRMSenderInterface *lpSender, void *lpArg, uint32 nIndex, const void *lpData, uint32 nLength) = 0;

	/**
	* 错误回调函数，一般启动后运行过程中的一些错误才会回调
	* @param lpSender 可靠组播发送者
	* @param lpArg CRMSenderInterface.Create 时传入的参数
	* @param nErrorNo 错误号，小于 \ref RM_ERR_BASE 的是errno
	* @param szErrorMsg 错误信息
	* @return 目前必须为0
	*/
	virtual int FUNCTION_CALL_MODE OnError(CRMSenderInterface *lpSender, void *lpArg, int32 nErrorNo, const char *szErrorMsg) = 0;
	
	/**
	* 流控状态回调函数，每次进入流控就回调，让应用层可以统计流控情况
	* @param lpSender 可靠组播发送者
	* @param lpArg CRMSenderInterface.Create / CRMReceiverInterface.Create 时传入的参数
	* @param nCurrentIndex 当前发送的记录序号
	* @param nMaxOfAllMinNotAck 所有接收者的最小未确认序号中的最大值
	* @return 目前必须为0
	*/
	//virtual int FUNCTION_CALL_MODE OnFlowControlStatus(CRMSenderInterface *lpSender, void *lpArg, uint32 nCurrentIndex, uint32 nMaxOfAllMinNotAck) = 0;


	////////////////////////////////////以下为本次增加//////////////////////////////////////
	/**
	* 发送者补缺时发现数据不存在，向应用层请求获取记录回调函数
	* @param lpSender 可靠组播发送者
	* @param lpArg IRMSender.Create 时传入的参数
	* @param nIndex 数据记录序号
	* @param lpLength 传出数据记录长度
	* @return 记录指针
	*/
	virtual void * FUNCTION_CALL_MODE OnGetData(CRMSenderInterface *lpSender, void *lpArg, uint32 nIndex, uint32 *lpLength) = 0;


	/**
	* 流控状态回调函数，每次进入流控就回调，让应用层可以统计流控情况
	* @param lpSender 可靠组播发送者
	* @param lpArg IRMSender.Create 时传入的参数
	* @param nToSendUDPNo 当前待发送的UDP包序号
	* @param nWaitAckUDPNo 当前待确认的UDP包序号
	* @return 目前必须为0
	*/
	virtual int FUNCTION_CALL_MODE OnFlowControl(CRMSenderInterface *lpSender, void *lpArg, uint32 nToSendUDPNo, uint32 nWaitAckUDPNo) = 0;

};


///可靠组播发送者。注：不能多线程调用其方法
class CRMSenderInterface : public IKnown
{
public:	
	//回调函数注册状态，可组合，不注册的函数回调类中的实现可为空
	enum CallbackRegStatus
	{
		ON_GET_DATA 			= 0x01, 	/**< OnGetData */
		ON_PROCESS 				= 0x02, 	/**< OnProcess */
		ON_ERROR 				= 0x04, 	/**< OnError */
		ON_FLOW_CONTROL 		= 0x08,		/**< OnFlowControl */
		ON_ACK_STATUS 			= 0x10		/**< OnAckStatus */
	};
	
	/**
	* 读取配置，并初始化。
	* @param lpSenderCfg 组播的私有配置，包括AB网卡等信息。
	* @param lpCallback 回调类
	* @param lpArg 调用者任意指定，回调函数中将原样传入
	* @param nCallbackStatus 回调函数使用标志，不使用的回调函数回调类中实现可以为空
	* @return 0表示成功，否则表示失败
	*/
	virtual int FUNCTION_CALL_MODE Create(RMSenderCfg *lpSenderCfg, IRMSenderCallback *lpCallback, void *lpArg = NULL, uint32 nCallbackStatus = ON_PROCESS|ON_ERROR) = 0;

	/**
	* 启动
	* @param nInitialIndex 启动时从指定序号的记录开始组播
	* @param nFlowFlag 启动时指定是否带流启动 0-不带流 1-带流
	* @return 0表示成功，否则表示失败
	*/
	virtual int FUNCTION_CALL_MODE Start(uint32 nInitialIndex = 0, uint8 nFlowFlag = 0) = 0;

	/**
	* 停止
	* @return 0表示成功，否则表示失败
	*/
	virtual int FUNCTION_CALL_MODE Stop() = 0;

	/**
	* 添加需要组播的记录数据，供外部在有新数据时调用，内部会复制一份内存
	* @param lpData 数据记录指针，是指单条记录
	* @param nLength 数据记录长度
	* @return 序号，-1表示错误
	*/
	//virtual uint32 FUNCTION_CALL_MODE PushData(uint8 nCategory, const void *lpData, uint32 nLength) = 0;
	virtual uint32 FUNCTION_CALL_MODE PushData(const void *lpData, uint32 nLength) = 0;

	/**
	* 添加需要组播的记录数据，供外部在有新数据时调用，内部只记录指针，调用者需保证指针一直有效
	* @param lpData 数据记录指针，是指单条记录
	* @param nLength 数据记录长度
	* @return 序号，-1表示错误
	*/
	//virtual uint32 FUNCTION_CALL_MODE PushDataPtr(uint8 nCategory, const void *lpData, uint32 nLength) = 0;
	virtual uint32 FUNCTION_CALL_MODE PushDataPtr(const void *lpData, uint32 nLength) = 0;

	/**
	* 忽略接收者，即不关心其确认
	* @param nReceiverID 接收者编号，范围1~31
	* @return 无
	*/
	virtual void FUNCTION_CALL_MODE IgnoreReceiver(uint8 nReceiverID) = 0;

	/**
	* 取添加进去的数据记录
	* @param nIndex 数据记录序号
	* @param nLength 传出数据记录长度
	* @return 数据记录指针，NULL表示失败
	*/
	//virtual void * FUNCTION_CALL_MODE GetData(uint32 nIndex, uint16 &nLength, uint8 &nCategory) = 0;
	virtual void * FUNCTION_CALL_MODE GetData(uint32 nIndex, uint32 &nLength) = 0;

	/**
	* 设置伙伴组播发送者，即在本对象的OnProcess事件中向另一组播地址发送，两者内部共用数据
	*建立伙伴关系的两实例必须已经调用Create但未调用Start，不能都是ackQuick模式
	* @param lpRMSenderInterface 组播发送者指针
	* @return 0表示成功，否则表示失败
	*/
	//virtual int FUNCTION_CALL_MODE SetBuddy(CRMSenderInterface *lpRMSenderInterface) = 0;

	///////////////////////////////////以下为本次增加///////////////////////////////////////
	/**
	* 重置记录指针，如果设置成NULL，在补缺将通过lpfnOnGetData回调
	* @param nIndex 数据记录序号
	* @param lpData 数据记录指针，可以为NULL，不为NULL时必须是有效的指针
	* @return 序号，-1表示错误
	*/
	virtual int FUNCTION_CALL_MODE ResetDataPtr(uint32 nIndex, const void *lpData) = 0;


};

class CRMReceiverInterface;

class IRMReceiverCallback : public IKnown
{
public:
	/**
	* 接收状态回调函数，固定每秒回调一次
	* @param lpReceiver 可靠组播接收者
	* @param lpArg CRMReceiverInterface.Create 时传入的参数
	* @param nNoRecvTime 上次收到有效数据到现在的时间
	* @param nIndex 当前待接收记录序号
	* @return 目前必须为0
	*/
	//virtual int FUNCTION_CALL_MODE OnRecvStatus(CRMReceiverInterface *lpReceiver, void *lpArg, uint32 nMinGapIndex, uint32 nNoRecvTime)= 0;
	//virtual int FUNCTION_CALL_MODE OnRecvStatus(CRMReceiverInterface *lpReceiver, void *lpArg, uint32 *lpNoRecvTime, uint32 nIndex) = 0;
	virtual int FUNCTION_CALL_MODE OnRecvStatus(CRMReceiverInterface *lpReceiver, void *lpArg, uint32 lpNoRecvTime, uint32 nIndex) = 0;

	/**
	* 处理回调函数，在数据已连续后调用
	* @param lpReceiver 可靠组播接收者
	* @param lpArg CRMReceiverInterface.Create 时传入的参数
	* @param nIndex 数据记录序号
	* @param lpData 数据记录指针，是指单条记录
	* @param nLength 数据记录长度
	* @return 目前必须为0
	*/
	//virtual int FUNCTION_CALL_MODE OnProcess(CRMReceiverInterface *lpReceiver, void *lpArg, uint32 nIndex, uint8 nCategory, const void *lpData, uint32 nLength)= 0;
	virtual int FUNCTION_CALL_MODE OnProcess(CRMReceiverInterface *lpReceiver, void *lpArg, uint32 nIndex, const void *lpData, uint32 nLength)= 0;

	/**
	* 接收者申请内存回调函数，接收者收到数据后为每条记录申请存放所需的内存。回调函数
	* 为NULL时接收者内部自行申请。
	* @param lpReceiver 可靠组播接收者
	* @param lpArg IRMReceiver.Create 时传入的参数
	* @param nIndex 数据记录序号
	* @param nLength 数据记录长度
	* @return 分配的内存指针，NULL表示失败
	*/
	//virtual void * FUNCTION_CALL_MODE OnGetMemory(CRMReceiverInterface *lpReceiver, void *lpArg, uint32 nIndex, uint8 nCategory, const void *lpData, uint32 nLength)= 0;
	virtual void * FUNCTION_CALL_MODE OnGetMemory(CRMReceiverInterface *lpReceiver, void *lpArg, uint32 nIndex, uint32 nLength)= 0;


	/**
	* 错误回调函数，一般启动后运行过程中的一些错误才会回调
	* @param lpReceiver 可靠组播接收者
	* @param lpArg CRMSenderInterface.Create / CRMReceiverInterface.Create 时传入的参数
	* @param nErrorNo 错误号，小于 \ref RM_ERR_BASE 的是errno
	* @param szErrorMsg 错误信息
	* @return 目前必须为0
	*/
	virtual int FUNCTION_CALL_MODE OnError(CRMReceiverInterface *lpReceiver, void *lpArg, int32 nErrorNo, const char *szErrorMsg)= 0;
			
	/**
	* 补缺状态回调函数，每次发起补缺就回调，让应用层可以统计补缺情况
	* @param pReceiver 可靠组播接收者
	* @param lpArg CRMSenderInterface.Create / CRMReceiverInterface.Create 时传入的参数
	* @param nMinGapIndex 最小所缺的记录序号
	* @return 目前必须为0
	*/
	//virtual int FUNCTION_CALL_MODE OnFilGapStatus(CRMReceiverInterface *lpReceiver, void *lpArg, uint32 nMinGapIndex)= 0;


	////////////////////////////////////以下为本次增加//////////////////////////////////////
	/**
	* 接收者收到新分片回调函数
	* @param lpReceiver 可靠组播接收者
	* @param lpArg IRMReceiver.Create 时传入的参数
	* @param nIndex 数据记录序号
	* @param lpData 数据记录指针，是指单条记录
	* @param nLength 数据记录长度
	* @param nOffset 当前分片的偏移量
	* @param nSegmentLength 当前分片的长度
	* @param bCompleted 是否已经收完整
	* @return 目前应返回0，暂未使用
	*/
	virtual int FUNCTION_CALL_MODE OnNewSegment(CRMReceiverInterface *lpReceiver, void *lpArg, uint32 nIndex, const void *lpData, uint32 nLength, uint32 nOffset, uint32 nSegmentLength, uint8 bCompleted)= 0;

	/**
	* 补缺状态回调函数，可以为空，每次发起补缺就回调，让应用层可以统计补缺情况
	* @param pReceiver 可靠组播接收者
	* @param lpArg CRMReceiverInterface.Create 时传入的参数
	* @param nMinGapIndex 最小所缺的记录序号
	* @return 目前必须为0
	*/
	virtual int FUNCTION_CALL_MODE OnFillGap(CRMReceiverInterface *lpReceiver, void *lpArg, uint32 nMinGapIndex)= 0;
};

///可靠组播接收者。注：不能多线程调用其方法
class CRMReceiverInterface : public IKnown
{
public:
	//回调函数注册状态，可组合，不注册的函数回调类中的实现可为空
	enum CallbackRegStatus
	{
		ON_NEW_SEGMENT 		= 0x01, 	/**< OnNewSegment */
		ON_PROCESS 			= 0x02, 	/**< OnProcess */
		ON_GET_MEMORY 		= 0x04, 	/**< OnGetMemory */
		ON_ERROR 			= 0x08, 	/**< OnError */
		ON_FILL_GAP 		= 0x10,		/**< OnFillGap */
		ON_RECV_STATUS 		= 0x20		/**< OnRecvStatus */
	};

	/**
	* 读取配置，并初始化。
	* @param lpReceiverCfg 组播的私有配置，包括AB网卡等信息。
	* @param lpCallback 回调类
	* @param lpArg 调用者任意指定，回调函数中将原样传入
	* @param nCallbackStatus 回调函数使用标志，不使用的回调函数回调类中实现可以为空
	* @return 0表示成功，否则表示失败
	*/
	virtual int FUNCTION_CALL_MODE Create(RMReceiverCfg *lpReceiverCfg, IRMReceiverCallback *lpCallback, void *lpArg = NULL, uint32 nCallbackStatus = ON_PROCESS|ON_ERROR)= 0;
	
	/**
	* 启动
	* @param nInitialIndex 启动时不对指定序号之前的记录进行补缺
	* @param nFlowFlag 启动时指定是否带流启动 0-不带流 1-带流
	* @return 0表示成功，否则表示失败
	*/
	virtual int FUNCTION_CALL_MODE Start(uint32 nInitialIndex = 0, uint8 nFlowFlag = 0) = 0;

	/**
	* 停止
	* @return 0表示成功，否则表示失败
	*/
	virtual int FUNCTION_CALL_MODE Stop() = 0;

	/**
	* 取收到的数据记录
	* @param nIndex 数据记录序号
	* @param nLength 传出数据记录长度
	* @return 数据记录指针，NULL表示失败
	*/
	//virtual void * FUNCTION_CALL_MODE GetData(uint32 nIndex, uint16 &nLength, uint8 &nCategory) = 0;
	virtual void * FUNCTION_CALL_MODE GetData(uint32 nIndex, uint32 &nLength) = 0;
	
	/**
	* 设置伙伴组播发送者，即在本对象的OnProcess事件中向另一组播地址发送，两者内部共用数据
	*建立伙伴关系的两实例必须已经调用Create但未调用Start
	* @param lpRMSenderInterface 组播发送者指针
	* @return 0表示成功，否则表示失败
	*/
	//virtual int FUNCTION_CALL_MODE SetBuddy(CRMSenderInterface *lpRMSenderInterface) = 0;

	////////////////////////////////////以下为本次增加//////////////////////////////////////
	/**
	* 重置记录指针，一般用来在OnProcess回调处理完成后设置成NULL
	* @param nIndex 数据记录序号
	* @param lpData 数据记录指针，可以为NULL，不为NULL时必须是有效的指针
	* @return 序号，-1表示错误
	*/
	virtual int FUNCTION_CALL_MODE ResetDataPtr(uint32 nIndex, const void *lpData) = 0;
};


///插件接口定义
class IF2RMService : public IKnown
{
public:
	/**
	* 获取可靠组播发送者
	*/
	virtual CRMSenderInterface * FUNCTION_CALL_MODE NewRMSender() = 0; 

	/**
	* 获取可靠组播接收者
	*/
	virtual CRMReceiverInterface * FUNCTION_CALL_MODE NewRMReceiver() = 0;

	/**
	* 释放可靠组播发送者
	*/
	virtual void FreeRMSender(CRMSenderInterface *lpRMSender) = 0;

	/**
	* 释放可靠组播接收者
	*/
	virtual void FreeRMReceiver(CRMReceiverInterface *lpRMReceiver) = 0;

};



///定义插件库标准引出函数，功能及参数说明参见Include/plugin_interface.h
#ifdef __cplusplus
extern "C" {
#endif
	///取插件实例
	IKnown *FUNCTION_CALL_MODE GetServiceRMInstance();
	
	///插件初始化
	int FUNCTION_CALL_MODE ServiceRMInit(void *lpInstance,PFOnSetTimeOut pfOnSetTimeOut = NULL);
	
	///取插件依赖的其他插件ID串
	char *FUNCTION_CALL_MODE GetSvrServiceRMDependSvr(void *lpInstance);
	
	///查询插件库中的插件信息
	int FUNCTION_CALL_MODE GetServiceRMInfo(int iIndex, tagBaseServiceInfo *ppv );
	
#ifdef __cplusplus
}
#endif

#endif       /*end def __SERVICE_RM_INTERFACE_H__*/

