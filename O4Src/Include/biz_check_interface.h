/*******************************************************
  源程序名称:biz_check_interface.h
  软件著作权:恒生电子股份有限公司
  系统名称:  消息中心V2.0
  模块名称:  业务组件api
  功能说明:
  作    者:  dongpf
  开发日期:  20120516
*********************************************************/

#ifndef _BIZ_CHECK_H
#define _BIZ_CHECK_H

#ifdef _WIN32
#ifndef FUNCTION_CALL_MODE
	#define FUNCTION_CALL_MODE  __stdcall 
#endif
#endif

#include <Include/pack_interface.h>
#include <Include/config_interface.h>
#include <Include/esb_message_factory_interface.h>
#include <Include/hsdb_interface.h>

///处理器上下文，供业务组件使用
struct IAppContext : public IKnown
{
	///取业务包服务插件接口
	virtual IF2PackSvr * FUNCTION_CALL_MODE GetF2PackSvr() = 0;
	
	///取数据库连接
	/**如果输入的数据源名为NULL，则取AS配置的缺省数据源名
	 *@param const char * szDataSourceName 数据源名
	 *@return char *  缺省数据源名 
	 */
	virtual IConnection *  FUNCTION_CALL_MODE GetDBConnection(const char * szDataSourceName = NULL ) = 0; 

	///同步调用子服务
	/**
	 *@param int iFunID 子服务调用的功能号[in]
	 *@param IF2UnPacker *lpInPacker 请求包[in]
	 *@param IF2Packer *lpOutPacker 应答包[in]， 如果返回值不等于0，那么可以在lpOutPacker里面取error_no和error_info
	 *@param int iTimeOut  超时时间(ms)[in]
	 *@return 返回0表示成功，需要调用者释放获得的应答消息；返回-1时，发送失败；返回-2,表示该调用超时; 返回-3,其他错误
	 */
	virtual int FUNCTION_CALL_MODE CallSubService(int iFunID, IF2UnPacker *lpInPacker, IF2Packer *lpOutPacker, int iTimeOut) =0;
};

//
#ifdef __cplusplus
extern "C" { 
#endif

///获取主题列表
/*
 *@param IAppContext * lpContext   上下文接口[in]
 *@param IF2Packer * lpAnswer    应答包[in]
 *@param int iTimeOut            超时时间[in]
 *@return 返回错误代码，0成功，如果不等于0，错误码放在lpAnswer的error_no字段,错误信息应该放在error_info字段
 */
int FUNCTION_CALL_MODE GetTopicList(IAppContext * lpContext, IF2Packer * lpAnswer, int iTimeOut);
	
///获取先天订阅者
/*
 *@param IAppContext * lpContext   上下文接口[in]
 *@param IF2Packer * lpAnswer    应答包[in]
 *@param int iTimeOut            超时时间[in]
 *@return 返回错误代码，0成功，如果不等于0，错误码放在lpAnswer的error_no字段,错误信息应该放在error_info字段
 */
int FUNCTION_CALL_MODE GetDualSub(IAppContext * lpContext, IF2Packer * lpAnswer, int iTimeOut);
	
///发布者权限校验
/*
 *@param IAppContext * lpContext   上下文接口[in]
 *@param char* lpTopic    主题名字[in]
 *@param char* lpPublisher  发布者名字[in]
 *@param IF2Packer * lpAnswer 应答包[in]
 *@return 返回错误代码，0成功，如果不等于0，错误码放在lpAnswer的error_no字段,错误信息应该放在error_info字段
 */
int FUNCTION_CALL_MODE CheckPub(IAppContext * lpContext, char* lpTopic, char* lpPublisher, IF2Packer * lpAnswer);
	
///校验订阅权限
/*
 *@param IAppContext * lpContext   上下文接口[in]
 *@param char* lpTopic    主题名字[in]
 *@param IF2UnPacker * lpSubReq 请求包[in]
 *@param char* lpSub  发布者名字[in]
 *@param IF2Packer * lpAnswer 应答包[in]
 *@return 返回错误代码，0成功，如果不等于0，错误码放在lpAnswer的error_no字段,错误信息应该放在error_info字段
 */
int FUNCTION_CALL_MODE CheckSub(IAppContext * lpContext, char* lpTopic, IF2UnPacker * lpSubReq, char* lpSub, IF2Packer * lpAnswer);

#ifdef __cplusplus
  }
#endif
#endif
