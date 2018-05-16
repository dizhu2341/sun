

#ifndef _S_AS_JC_PUBLICFUNC_H
#define _S_AS_JC_PUBLICFUNC_H

#include "s_as_jc_syspubfunc.h" 
#include "hshead.h" 
//AF_基础公共_取消订阅主题
int FUNCTION_CALL_MODE F3617011(IAS2Context * lpContext,IF2UnPacker * lpInUnPacker,IF2Packer * lpOutPacker,IConnection * lpParentConn=NULL);

//AF_基础公共_生成证券内码
int FUNCTION_CALL_MODE F3617007(IAS2Context * lpContext,IF2UnPacker * lpInUnPacker,IF2Packer * lpOutPacker,IConnection * lpParentConn=NULL);

//AF_基础公共_删除SQL动态拼接
int FUNCTION_CALL_MODE F3617000(IAS2Context * lpContext,IF2UnPacker * lpInUnPacker,IF2Packer * lpOutPacker,IConnection * lpParentConn=NULL);

//AF_基础公共_新增SQL动态拼接
int FUNCTION_CALL_MODE F3617001(IAS2Context * lpContext,IF2UnPacker * lpInUnPacker,IF2Packer * lpOutPacker,IConnection * lpParentConn=NULL);

//AF_基础公共_更新SQL动态拼接
int FUNCTION_CALL_MODE F3617005(IAS2Context * lpContext,IF2UnPacker * lpInUnPacker,IF2Packer * lpOutPacker,IConnection * lpParentConn=NULL);

//AF_基础公共_执行SQL
int FUNCTION_CALL_MODE F3617002(IAS2Context * lpContext,IF2UnPacker * lpInUnPacker,IF2Packer * lpOutPacker,IConnection * lpParentConn=NULL);

//AF_基础公共_获取和生成证券内码
int FUNCTION_CALL_MODE F3617008(IAS2Context * lpContext,IF2UnPacker * lpInUnPacker,IF2Packer * lpOutPacker,IConnection * lpParentConn=NULL);

//AF_基础公共_获取和同步证券内码
int FUNCTION_CALL_MODE F3617009(IAS2Context * lpContext,IF2UnPacker * lpInUnPacker,IF2Packer * lpOutPacker,IConnection * lpParentConn=NULL);

//AF_基础公共_获取证券内码
int FUNCTION_CALL_MODE F3617006(IAS2Context * lpContext,IF2UnPacker * lpInUnPacker,IF2Packer * lpOutPacker,IConnection * lpParentConn=NULL);

//AF_基础公共_查询系统参数值
int FUNCTION_CALL_MODE F3617017(IAS2Context * lpContext,IF2UnPacker * lpInUnPacker,IF2Packer * lpOutPacker,IConnection * lpParentConn=NULL);

//AF_基础公共_获取交易中心信息
int FUNCTION_CALL_MODE F3617014(IAS2Context * lpContext,IF2UnPacker * lpInUnPacker,IF2Packer * lpOutPacker,IConnection * lpParentConn=NULL);

//AF_基础公共_插入哈希证券内码
int FUNCTION_CALL_MODE F3617019(IAS2Context * lpContext,IF2UnPacker * lpInUnPacker,IF2Packer * lpOutPacker,IConnection * lpParentConn=NULL);

//AF_基础公共_发布缓存更新主题
int FUNCTION_CALL_MODE F3617003(IAS2Context * lpContext,IF2UnPacker * lpInUnPacker,IF2Packer * lpOutPacker,IConnection * lpParentConn=NULL);

//AF_基础公共_发布缓存更新主题Ex
int FUNCTION_CALL_MODE F3617012(IAS2Context * lpContext,IF2UnPacker * lpInUnPacker,IF2Packer * lpOutPacker,IConnection * lpParentConn=NULL);

//AF_基础公共_发布缓存全表删除主题
int FUNCTION_CALL_MODE F3617004(IAS2Context * lpContext,IF2UnPacker * lpInUnPacker,IF2Packer * lpOutPacker,IConnection * lpParentConn=NULL);

//AF_基础公共_发布缓存全表删除主题Ex
int FUNCTION_CALL_MODE F3617013(IAS2Context * lpContext,IF2UnPacker * lpInUnPacker,IF2Packer * lpOutPacker,IConnection * lpParentConn=NULL);

//AF_基础公共_重置交易中心状态
int FUNCTION_CALL_MODE F3617015(IAS2Context * lpContext,IF2UnPacker * lpInUnPacker,IF2Packer * lpOutPacker,IConnection * lpParentConn=NULL);

//AF_基础公共_查询哈希证券内码
int FUNCTION_CALL_MODE F3617020(IAS2Context * lpContext,IF2UnPacker * lpInUnPacker,IF2Packer * lpOutPacker,IConnection * lpParentConn=NULL);

//AF_基础公共_设置交易中心状态
int FUNCTION_CALL_MODE F3617016(IAS2Context * lpContext,IF2UnPacker * lpInUnPacker,IF2Packer * lpOutPacker,IConnection * lpParentConn=NULL);

//AF_基础公共_订阅主题
int FUNCTION_CALL_MODE F3617010(IAS2Context * lpContext,IF2UnPacker * lpInUnPacker,IF2Packer * lpOutPacker,IConnection * lpParentConn=NULL);

#endif /* _S_AS_JC_PUBLICFUNC_H */
