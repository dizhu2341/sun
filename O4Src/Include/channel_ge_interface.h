#ifndef __CHANNEL_GE_INTERFACE_H__
#define __CHANNEL_GE_INTERFACE_H__

/*
通用通道插件，为业务类消息插件提供通用通信接口，避免此类业务插件需要加入到消息流水线，降低开发难度；
通用通道插件接口定义，其他业务插件只需要依赖这个插件，作为普通插件，不需要再写流水线插件
*/

#include <Include/service_interface.h>
#include <Include/glbdef.h>
#include <Include/esb_message_interface.h>
#include <Include/biz_channel_interface.h>
//通用通道插件的接口名
#define SID_CHANNEL_GE		   	"ge"
//业务插件需要使用的接口名
#define SID_BIZ_GE		   	"biz_ge"
#define GE_OK				0
#define GE_ERR_TRANSFER		-1
#define GE_ERR_NOSENDER		-2
#define GE_ERR_NOREGISTER	-3
#define GE_ERR_NOREADY		-4

struct IBizChannel:public IKnown
{
public:
	//异步发送之前，调用这个函数向通用插件注册，进行注册
	/*
		*@param IMessageService* lpSendSvr:	需要异步发送的插件指针
		*@return	插件的发送标示，是通用插件自身维护的发送者ID，应答匹配使用，唯一的标示
					返回0表示注册失败
	*/
	virtual int Register(IBizPlugin* lpSendSvr) = 0;
	
	//如果普通插件不需要发包，可以取消注册
	/*
		*@param const char* lpServerID:	发送插件的名字
		*@return    取消成功返回true,失败返回false
	*/
	virtual bool CancelRegister(int sendID) = 0;

	//0422修改，为了方便使用者在调用函数失败的时候，还可以继续使用消息，故函数内部不释放传入的消息
	//同步发送接收接口，返回应答消息
	/*
		*@param IESBMessage* lpSendMsg:	需要发送的ESBMessage
		*@param bool& isTimeout:	 是否超时的标志，输出函数，true表示超时，false不超时
		*@param int iTimeOut:	 超时时间

		*@return    成功返回收到的应答，失败返回NULL
		注意：参数中的传入的 IESBMessage ，如果返回指针不为空，那么lpSendMsg就不需要释放
			  如果返回空指针，并且超时标志为true，那么lpSendMsg就不需要释放，
			  其他情况需要使用者自己释放lpSendMsg
	*/

	virtual IESBMessage* SYNSendRecvMsg(IESBMessage* lpSendMsg, bool& isTimeout, int iTimeOut = -1) = 0;
	
	//异步发送接口
	/*
		*@param IESBMessage* lpSendMsg:	需要发送的ESBMessage		
		*@int asySendId 前面注册之后返回的异步发送者编号
		*@return 		返回值的含义前面有宏定义
		注意：参数中的传入的 IESBMessage ，返回成功就不需要释放lpSendMsg
			  否则需要释放lpSendMsg
	*/
	//0428xuxp为了提高通用通道性能，异步发送者编号作为一个参数传入
	virtual int ASYSendMsg(IESBMessage* lpSendMsg, int asySendId) = 0;

};

#endif



