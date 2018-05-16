///Service_init 插件接口ID定义及其标准引出函数
/*********************************************************************************************
  源程序名称: service_init_interface.h
  软件著作权: 恒生电子股份有限公司
  服务名称:  
  模块名称:  fsc_service_init

  插件类型:  可管理可反转普通插件

  功能说明:  

  相关文档:  

  作    者:  研发中心chengjin
  开发日期:  2014-11-17
  备    注:  
  修改记录： 
*********************************************************************************************/

#ifndef __Service_init_Interface_H__
#define __Service_init_Interface_H__
#include <Include/plugin_interface.h>

///插件接口ID定义
#define SID_SERVICE_INIT "com.hundsun.fbase.service_init"

///插件接口定义
struct IService_init: public IKnown
{
    ///@todo根据规范定义接口函数，纯虚函数，例如：
    //virtual const char * FUNCTION_CALL_MODE GetName(int iIndex) = 0;
    
};

///定义插件库标准引出函数，功能及参数说明参见Include/plugin_interface.h
#ifdef __cplusplus
extern "C" {
#endif
    ///查询插件库中的插件信息
    int FUNCTION_CALL_MODE GetService_initInfo(int iIndex, tagBaseServiceInfo * ppv );
    ///取插件实例
    IKnown * FUNCTION_CALL_MODE GetService_initInstance();
    ///取插件依赖的其他插件ID串
    char *  FUNCTION_CALL_MODE GetService_initDependSvr(void * lpInstance);
    ///插件初始化
    int FUNCTION_CALL_MODE Service_initInit(void * lpInstance, PFOnSetTimeOut pfOnSetTimeOut);
#ifdef __cplusplus
}
#endif

#endif       /*end def __Service_init_Interface_H__*/

