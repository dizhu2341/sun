/// 总说明
/*******************************************************
源程序名称:
软件著作权:恒生电子股份有限公司
系统名称:  恒生插件容器库接口
模块名称:  Fix
功能说明:  实现fix与恒生报文协议转换接口
作    者:  dongpf
开发日期:  
备    注:  

  修改人员：
  修改日期：
  修改说明：
*********************************************************/


#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_FIXBEHAVIORPARA_4736C1D80021_INCLUDED
#define _INC_FIXBEHAVIORPARA_4736C1D80021_INCLUDED

#include <Include/MessageInterface.h>
#include <Include/plugin_interface.h>
#include <Include/esb_message_factory_interface.h>


#define SID_SERVICE_FIX							"fixSvr"
#define SID_CHANNEL_FIX                         "fix"

struct IFixService : public IKnown
{
public:
   
	/// 将fix协议报文转换为恒生报文
    /**
      *@ Param  const IMessage * srcMsg: fix协议报文
	  *@ Param  IESBMessage * dstMsg:    恒生中间件协议报文
	  *@ Param  const char * szdictName: 数据字典名字
      *@ return:						 0表示成功，非0表示失败
      */
    virtual int FUNCTION_CALL_MODE ChangeFixToPack( const IMessage * srcMsg, IESBMessage * dstMsg, const char * szdictName ) = 0;

	/// 将fix协议报文转换为恒生报文
    /**
	  *@ Param  const IESBMessage * srcMsg: 恒生中间件协议报文
	  *@ Param  IMessage * dstMsg:       fix协议报文
	  *@ Param  const char * szdictName: 数据字典名字
      *@ return:						 0表示成功，非0表示失败
      */
    virtual int FUNCTION_CALL_MODE ChangePackToFix( IESBMessage * srcMsg, IMessage * dstMsg, const char * szdictName ) = 0;

	/// 根据错误码返回错误信息
    /**
	  *@ Param  int iError_No:			 错误码
      *@ return:						 错误信息
      */
	virtual const char * FUNCTION_CALL_MODE GetErrorInfo( int iError_No ) = 0;
};

#ifdef __cplusplus
extern "C" {
#endif

    int FUNCTION_CALL_MODE GetFixServiceInfo( int iIndex, tagBaseServiceInfo * ppv );

	IKnown * FUNCTION_CALL_MODE GetFixServiceInstance();

	int   FUNCTION_CALL_MODE GetFixServiceInit( void * lpInstance, PFOnSetTimeOut pfOnSetTimeOut );
	
	char *  FUNCTION_CALL_MODE GetFixServiceDependSvr( void * lpInstance );

#ifdef __cplusplus
}
#endif


#endif /* _INC_FIXBEHAVIORPARA_4736C1D80021_INCLUDED */
