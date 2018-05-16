/*******************************************************
  源程序名称:rm_interface.h
  软件著作权:恒生电子股份有限公司
  系统名称:  消息中心2.0
  模块名称:  消息中心组播模块
  功能说明:  
				通用的可靠组播接口,
				实现局域网范围内的可靠组播
				不处理任何业务相关逻辑
				本接口被消息中心可靠组播使用,源码级共享,以后可以单独剥离为其他项目使用
				
  作    者:  maoyj
  开发日期:  20120509
  备    注:  
*********************************************************/

#ifndef _rm_interface_h
#define _rm_interface_h

#include <Include/plugin_interface.h>
#include <os/inttypes.h>
#include <os/config_env.h>

// 错误码
typedef enum ERM_ERR
{
	RM_SUCC = 0,
	RM_ERR_SOCKET,		//	创建套接字失败
	RM_ERR_BIND,		//	绑定失败
	RM_ERR_GET_IP_ADDR,	//	获取本地IP失败
	RM_ERR_TIMEOUT,		//	超时
	RM_ERR_NOT_SUPPORT,	//	系统不支持
	RM_ERR_JOIN,		//	加入多播组失败
	RM_ERR_INTERFACE,	//	指定网卡非法
	RM_ERR_NO_BUFF,		//	没有足够的缓存
	RM_ERR_NO_DATA,		//	没有数据
	RM_ERR_TOO_LONG,	//	数据太长
	RM_ERR_INIT,		//	未初始化
	RM_ERR_CFT_NOT_SUPPORT,	//	配置不支持组播
};

//	业务无关的可靠组播接口
struct IRMSessionInterface
{
	//	从已经接收的数据队列中获取.(可靠组播底层接收数据后,不会触发回调,而是等待上层自己来取数据)
	virtual ERM_ERR FUNCTION_CALL_MODE Recv(char *lpBuff, int& iSize, int iTimeOut, sockaddr_in* lpAddrFrom)=0;
	//	往组播组发送数据
	virtual ERM_ERR FUNCTION_CALL_MODE Send(char *lpBizData, int iBizDataLen)=0;
	//	往组播组发送数据
	virtual ERM_ERR FUNCTION_CALL_MODE Send(char *lpBizHead, int iBizHeadLen, char *lpBizData, int iBizDataLen)=0;
	//	获得当前维护的组播组成员个数
	virtual int FUNCTION_CALL_MODE GetMemberCount()=0;
	//	初始化当前组播需要用到的通信参数
	//20130221 xuxp 增加接口参数，是否禁止组播循环
	virtual ERM_ERR FUNCTION_CALL_MODE InitRM(const char* lpMAddr, uint16 wPort, const char* lpMInterFace,int bForbidMultiLoop=1)=0;	//	初始化多播通信参数
	virtual int FUNCTION_CALL_MODE Start()=0;	//	开始组播通信
	virtual int FUNCTION_CALL_MODE Stop()=0;	//	停止组播通信
	virtual int FUNCTION_CALL_MODE Syning()=0;	//	组播内部同步序号信息
};

IRMSessionInterface*  FUNCTION_CALL_MODE CreatRM();
int  FUNCTION_CALL_MODE DestroyRM(IRMSessionInterface* lpRMSession);

#endif
