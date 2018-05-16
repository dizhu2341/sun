///服务插件接口定义
/*******************************************************
  源程序名称:service_interface.h
  软件著作权:恒生电子股份有限公司
  系统名称:  恒生通用消息处理插件接口标准
  模块名称:  公共模块
  功能说明:  消息处理插件接口定义
 
             
  作    者:  maoyinjie
  开发日期:  20071217
  备    注:  在windows下注意函数调用方式：__stdcall

  修改人员：zhangly
  修改日期：20081219
  修改说明：去掉各消息处理插件的SID的前缀，以缩小消息包头长度
*********************************************************/


#ifndef	SERVICE_INTERFACE_H
#define SERVICE_INTERFACE_H

//#define NODE_NAME_FLAG		'.'			/// 作为区分群组名还是节点名的标志

#define SID_IMESSAGE_SERVICE	"com.hundsun.fbase.messageservice"

///以下是各个从IMessageService接口继承的插件ID,zhangly 20081219整理
///多线程业务处理插件SID
#define SID_BIZ_PROC_C			"proc_c"      //多进程业务处理插件/子进程
#define SID_PROC_S              "proc"      //多进程业务处理插件/主进程
#define SID_SERVICE_PROC		"proc"        //多线程业务处理插件
#define SID_SERVICE_MPROXY		"mproxy"      //管理代理插件
#define SID_SERVICE_ROUTER		"router"      //路由插件
#define SID_CHANNEL_F2			"f2"          //F2通道插件
#define	SID_CHANNEL_F1			"f1"	      //F1通道插件
#define SID_CHANNEL_T2			"t2"          //T2/T1通道插件
#define SID_CHANNEL_IPC			"ipc"         //内存通道插件
#define SID_LOG_FILTER_SERVICE	"filter_log"  //日志过滤器插件
#define SID_OSPF				"ospf"        //OSPF插件  


#include <Include/esb_message_factory_interface.h>

enum ServiceStatus
{
		ServiceUnInite		= 0x0000, /**< 尚未初始化 */
		ServiceInitializing	= 0x0001, /**< 正在初始化 */
		ServiceInitialized	= 0x0002, /**< 已经初始化 */
		ServiceStarting		= 0x0003, /**< 正在启动 */
		ServiceStarted		= 0x0004, /**< 已经启动 */
		ServiceUnRegister	= 0x0005, /**< 尚未向Router注册 */ 
		ServiceRegistering	= 0x0006, /**< 正在向Router注册,尚未收到router的回应 */ 
		ServiceReady		= 0x0007, /**< 准备就绪,可以正常工作 */
		ServicePause		= 0x0008, /**< 服务暂停 */
		ServiceStopping		= 0x0009, /**< 正在停止 */
		ServiceStoped		= 0x000a, /**< 已经停止 */
		ServiceDisbale		= 0x0010  /**< 服务不可用(由于其他服务不可用,而导致自身不可用) */
};


///	所有处理消息的恒生服务插件的通用接口
/**
	该类型的插件有如下的特点:
		插件本身拥有处理消息的线程
		插件拥有缓存消息的队列
		消息的流向可以构成一个服务链,允许根据配置构造一个合适的服务链表.可以在当前的服务链表中插入一个新的服务或者
		删除当前已经存在于服务链表中的特定服务



	消息在一个服务链表的服务间流转,	链表中的每个服务都可以获得处理消息的机会.
	消息转发的规则:
		如果自己拥有上层服务以及下层服务
		那么来自下层服务的消息经过自己的处理再转交给自己的上层服务
		而来自上层服务的消息经过自己的处理后转发给自己的下层服务
	对于没有下层服务只有上层服务的服务,接收到不是来自自己上层服务的消息在自己处理完后转发给自己的上层服务
		而在接收到来自上层的服务后,只进行自己的处理.不再转发消息给其他服务
	对于没有上层服务只有下层服务的服务,接收到不是来自自己下层服务的消息在自己处理完后转发给自己的下层服务
		而在接收到来自下层的服务后,只进行自己的处理.不再转发消息给其他服务
	
	一般在我们的实现中,实际上只有通道会收到不是来自于于服务链表中其他服务的消息,而来自于外界,
	而其他类型的服务收到的消息肯定来自于自己的下层或者上层的服务
	router插件会存在多个下层服务,其他的插件一般最多存在一个上层服务或者一个下层服务.
	
**/


struct IMessageService : IKnown
{
public:
	///	为本对象提供待处理的消息,
	/**
		该方法由其他服务插件在外部调用,以使得消息流入本服务.
		建议插件实现时,将消息放入自己的消息队列后即返回,不要在该函数中直接进行消息处理
		而由自己的工作线程在适当的时候取出该消息进行处理
		如果插件内部没有自己的工作线程,而是直接借用了调用者的线程对消息进行处理,则插件实现者必须明确指出
		并且在消息的处理中必须接受某些限制,以避免线程的竞争问题
		入参:
			IESBMessage*	 lpMessage:		外部提供的消息
			IMessageService* lpServiceFrom	Post消息的服务
		出参:
			无
		返回
			SUCC:	成功
			其他:	失败
	**/
	virtual int FUNCTION_CALL_MODE PostMsg(IESBMessage* lpMessage, IMessageService* lpServiceFrom)=0;
	


	///	注册下一个服务插件(消息流向的下一个服务)
	virtual int FUNCTION_CALL_MODE RegisterNextService(IMessageService* lpService)=0;
	virtual int FUNCTION_CALL_MODE RegisterPrevService(IMessageService* lpService)=0;
	///	将自己从服务链表中删除???
	virtual int FUNCTION_CALL_MODE RemoveService()=0;

	
	
	/// 获得服务的序号(可以由框架根据加载顺序决定服务的序号)
	virtual const char* FUNCTION_CALL_MODE GetServiceID()=0;

	///	在创建服务时指定该服务的序号
	/**
	以下编号,在未设置前,缺省为-1,对于-1的编号,服务在转发消息时,不必记录ServiceSeqNo和ServiceInstantID的信息
	**/
	virtual void FUNCTION_CALL_MODE SetServiceID(const char* HSID)=0;



	/// 增加服务状态的处理
 	virtual  ServiceStatus  FUNCTION_CALL_MODE GetServiceStatus()=0;
 	virtual  int  FUNCTION_CALL_MODE RegisterService()=0;
 	virtual  int  FUNCTION_CALL_MODE SendSvrHeartBeat()=0;


};

#endif
