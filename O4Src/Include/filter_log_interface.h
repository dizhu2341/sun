///日志过滤器插件定义
/*******************************************************
源程序名称:filter_log_interface.h
软件著作权:恒生电子股份有限公司
系统名称:  恒生通用消息处理插件接口标准
模块名称:  日志过滤插件
功能说明:  对日志进行规则过滤，实现记录、拦截的功能
           相关的规则可以通过管理功能来添加、查询及删除等

  
	作    者:  xuqq
	开发日期:  20081009
	备    注:  在windows下注意函数调用方式：__stdcall
	
	  修改人员：
	  修改日期：
	  修改说明：
*********************************************************/


#ifndef FILTER_LOG
#define FILTER_LOG

#include <Include/plugin_interface.h>


///filter_log插件自身的服务名
//#define SID_LOG_FILTER_SERVICE		"com.hundsun.fbase.filter_log"

///外部插件通过QueryInterface得到IF2WriteClass时的服务名
#define SID_WRITE_CLASS		   	    "com.hundsun.fbase.write_class"

////外部写入接口
////如果外部插件与filter_log不在一条流水线上，但又需要调用filter_log的记录功能时
////外部插件可以先得到filter_log的实例,然后通过QueryInterface，将SID_WRITE_CLASS传入，返回IF2WriteClass的实例
////然后根据IF2WriteClass来记录日志
////如果日志写入失败，或ESBMessage不符合记录规则,将返回false
struct IF2WriteClass : public IKnown
{
public:
	///参数传入一个请求的ESBMessage，以一个返回的数据包
	///先根据ESBMessage进行数据规则过滤，如果需要记录下来的话，那么ESBMessage以及pBuffer都会被记录下来
	///将一个数据包写入到日志 文件中，该日志 文件由esbcfg.xml中的参数决定
	virtual bool Write(IESBMessage* lpMessage, void *pBuffer, int iBufferLen) = 0;
};


//对外提供的接口
#ifdef __cplusplus
extern "C" { 
#endif
	
	IKnown*	FUNCTION_CALL_MODE GetFilterLogInstance();
	int		FUNCTION_CALL_MODE GetFilterLogInit(void * lpInstance ,PFOnSetTimeOut pfOnSetTimeOut = NULL);
	char*	FUNCTION_CALL_MODE GetFilterLogDependSvr(void * lpInstance);
	int		FUNCTION_CALL_MODE GetFilterLogInfo(int iIndex, tagBaseServiceInfo * ppv );
	
#ifdef __cplusplus
}
#endif

#endif
