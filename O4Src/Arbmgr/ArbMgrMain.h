#ifndef __ArbMgrMain_H__
#define __ArbMgrMain_H__

#include <string.h>
#include <map>
#include <Include/plugin_interface.h>
#include <Include/config_interface.h>
#include <Include/pack_interface.h>
#include <Include/plugin_interface.h>

///插件接口ID定义
#define SID_O4ARBMGR "hundsun.o4.arbmgr"

///定义插件库标准引出函数，功能及参数说明参见Include/plugin_interface.h
#ifdef __cplusplus
extern "C" {
#endif
    ///查询插件库中的插件信息
    int FUNCTION_CALL_MODE GetArbmgrInfo(int iIndex, tagBaseServiceInfo * ppv );
    ///取插件实例
    IKnown * FUNCTION_CALL_MODE GetArbmgrInstance();
    ///取插件依赖的其他插件ID串
    char *  FUNCTION_CALL_MODE GetArbmgrDependSvr(void * lpInstance);
    ///插件初始化
    int FUNCTION_CALL_MODE ArbmgrInit(void * lpInstance, PFOnSetTimeOut pfOnSetTimeOut);
#ifdef __cplusplus
}
#endif

#endif       /*end def __ArbMgrMain_H__*/

