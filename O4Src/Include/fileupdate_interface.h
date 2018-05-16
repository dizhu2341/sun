/***********************************************************************
版权所有: 恒生电子股份有限公司
项目名称: MC2.0项目
版    本: V1.0
操作系统: Windows/Linux/HP-UX
文 件 名: fileupdate_interface.h
文件描述: 
项 目 组: CRES
程 序 员: 05909
发布日期: 2012-7-17   14:40:54
修    订:
修改日期:
***********************************************************************/
#ifndef FILEUPDATE_INTERFACE_H
#define FILEUPDATE_INTERFACE_H

#include <Include/plugin_interface.h>


/* 插件接口ID定义 */
#define SID_FILEUPDATE "fileupdate"

/* 定义插件库标准引出函数，功能及参数说明参见Include/plugin_interface.h */
#ifdef __cplusplus
extern "C" {
#endif
    ///取插件实例
    IKnown* FUNCTION_CALL_MODE GetFileUpdateInstance();
    ///插件初始化
    int FUNCTION_CALL_MODE FileUpdateInit(void* lpInstance, PFOnSetTimeOut pfOnSetTimeOuts);
    ///取插件依赖的其他插件ID串
    char*  FUNCTION_CALL_MODE GetFileUpdateDependSvr(void* lpInstance);
    ///查询插件库中的插件信息
    int FUNCTION_CALL_MODE GetFileUpdateInfo(int iIndex, tagBaseServiceInfo* ppv);
#ifdef __cplusplus
}
#endif

#endif
