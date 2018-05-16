/*******************************************************
  源程序名称:mcrm_interface.h
  软件著作权:恒生电子股份有限公司
  系统名称:  消息中心2.0
  模块名称:  消息中心组播模块
  功能说明:  
  作    者:  maoyj
  开发日期:  20120509
  备    注:  
	消息中心项目使用可靠组播,仅需要关心本文件的接口即可,无须关心更底层的rm_interface接口

	正常发布情景下使用组播接口的流程:
		1:	总控通过AR接收到某个主题的发布消息
		2:	调用组播模块将该消息发送给组内其他成员
			2.1:	如果是内存级可靠消息,调用异步发送,立即返回
			2.2:	如果是文件级可靠,调用同步发送,iFlag为0
			2.3:	如果是系统级可靠,调用同步发送,iFlag为1
			2.4:	对于同步发送的调用,函数会被堵塞,直到一个ACK或者所有ACK到达
		3:	如果收到组播数据,判断对方是否需要ACK,若需要则在上层回调函数成功返回后,自动发送ACK.
	当发现缺口,填补时使用组播的流程
		1:	在重组的第二阶段,发现缺口的上层组织一个请求重传的报文组播
		2:	

*********************************************************/

#ifndef _mcrm_interface_h
#define _mcrm_interface_h

#include <Include/rm_interface.h>		//	底层的可靠组播接口

//	定义消息中心可靠组播插件名
#define SID_MSGCENTER_RM   "mc_rm"


//	具备消息中心业务层含义的数据:
/*
	当主服务发现缺口,他的
	第一个t时间,是等待,期望缺口被自动填补
	第二个t时间是尝试在集群内部解决(这由本接口帮助解决)
		那么需要:
			rebuild请求			组播发送
			针对rebuild的应答	单播发送
	第三个t时间是尝试请求发布者重传(这个是通过给AR发送报文实现)
*/


//	消息接收回调函数
/*
	参数:	消息来自的成员IP地址		接收的消息二进制流		接收数据长度
	其实数据可能并不是通过组播过来,而是单播过来,如总控模块在第二个t时间段内,会向集群内发送请求重传的组播
	集群内部的成员通过UniSend接口响应该请求.
	当其他成员响应rebuild请求后,接收到数据,也以回调的形式响应.
	返回:
	0:	成功	其他失败
	当回调函数成功返回后,对于同步发送过来的组播报文,本接口会自动回复对端一个ACK,以帮助对端
	从阻塞中解除.
	备注:	指针地址仅在回调瞬间合法,之后,不再确保有效
*/
typedef int (FUNCTION_CALL_MODE * OnMultiRecv)(sockaddr_in* lpFrom, const char* lpBuff, int iLen);
//	组播接口,上层在调用发送接口时,必须分配一个唯一的dwmsgid,以供和应答匹配(当然如果上层认为没有必要
//	完全可以为所有的发送均传入0,但是这样一类,就会导致应答匹配出现故障)
struct IMCRMSessionInterface : IKnown
{
public:
	//	设置组播数据接收时的回调,组播通信参数,由插件自己的配置参数管理(也包括请求重传时的单播响应数据到达)
	virtual ERM_ERR FUNCTION_CALL_MODE SetCallBack(OnMultiRecv RecvFunc)=0;
	//	异步发送组播(当底层的发送队列积压时,会堵塞调用)
	virtual ERM_ERR FUNCTION_CALL_MODE MultiSend(char *lpBuff, int iDataLen)=0;
	//	同步发送组播，函数成功返回时，至少有一个成员已经成功处理了该组播, int iTimeOut 同步等待的超时时间
	//	iFlag 0:只需要一个应答  1 需要全部应答
	virtual ERM_ERR FUNCTION_CALL_MODE SynMultiSend(char *lpBuff, int iDataLen, int iFlag, int iTimeOut)=0;
	//	集群成员响应其他成员的补缺请求,以单播形式发送
	virtual ERM_ERR FUNCTION_CALL_MODE UniSendTo(char *lpBuff, int iDataLen, sockaddr_in* lpAddr)=0;
	//	获取集群内部成员个数
	virtual int FUNCTION_CALL_MODE GetMemberCount()=0;
};

//	插件引出函数定义,供基础件框架调用
#ifdef __cplusplus
extern "C" {
#endif
    int		FUNCTION_CALL_MODE GetMCRMInfo( int iIndex, tagBaseServiceInfo * ppv );
	IKnown* FUNCTION_CALL_MODE GetMCRMInstance();
	int		FUNCTION_CALL_MODE GetMCRMInit( void * lpInstance, PFOnSetTimeOut pfOnSetTimeOut );
	char*	FUNCTION_CALL_MODE GetMCRMDependSvr( void * lpInstance );
	
#ifdef __cplusplus
}
#endif

#endif
