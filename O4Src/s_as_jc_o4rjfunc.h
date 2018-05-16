

#ifndef _S_AS_JC_O4RJFUNC_H
#define _S_AS_JC_O4RJFUNC_H

#include "s_as_jc_o4initfunc.h" 
#include "hshead.h" 
#include "s_as_jc_publicfunc.h" 
//AF_日间更新_增量更新
int FUNCTION_CALL_MODE F3615222(IAS2Context * lpContext,IF2UnPacker * lpInUnPacker,IF2Packer * lpOutPacker,IConnection * lpParentConn=NULL);

//AF_日间更新_全表更新
int FUNCTION_CALL_MODE F3615213(IAS2Context * lpContext,IF2UnPacker * lpInUnPacker,IF2Packer * lpOutPacker,IConnection * lpParentConn=NULL);

//AF_日间更新_获取和生成证券内码
int FUNCTION_CALL_MODE F3615214(IAS2Context * lpContext,IF2UnPacker * lpInUnPacker,IF2Packer * lpOutPacker,IConnection * lpParentConn=NULL);

//AF_基础公共_根据表名查询存储过程
int FUNCTION_CALL_MODE F3615221(IAS2Context * lpContext,IF2UnPacker * lpInUnPacker,IF2Packer * lpOutPacker,IConnection * lpParentConn=NULL);

//AF_日间更新_通用删除
int FUNCTION_CALL_MODE F3615215(IAS2Context * lpContext,IF2UnPacker * lpInUnPacker,IF2Packer * lpOutPacker,IConnection * lpParentConn=NULL);

//AF_日间更新_通用更新
int FUNCTION_CALL_MODE F3615211(IAS2Context * lpContext,IF2UnPacker * lpInUnPacker,IF2Packer * lpOutPacker,IConnection * lpParentConn=NULL);

//AF_日间更新_生成删除SQL
int FUNCTION_CALL_MODE F3615216(IAS2Context * lpContext,IF2UnPacker * lpInUnPacker,IF2Packer * lpOutPacker,IConnection * lpParentConn=NULL);

//AF_日间更新_生成更新SQL
int FUNCTION_CALL_MODE F3615212(IAS2Context * lpContext,IF2UnPacker * lpInUnPacker,IF2Packer * lpOutPacker,IConnection * lpParentConn=NULL);

//AF_日间更新_多数据打包
int FUNCTION_CALL_MODE F3615220(IAS2Context * lpContext,IF2UnPacker * lpInUnPacker,IF2Packer * lpOutPacker,IConnection * lpParentConn=NULL);

//AF_日间更新_多数据集更新_基础数据库更新
int FUNCTION_CALL_MODE F3615218(IAS2Context * lpContext,IF2UnPacker * lpInUnPacker,IF2Packer * lpOutPacker,IConnection * lpParentConn=NULL);

//AF_日间更新_多数据集更新
int FUNCTION_CALL_MODE F3615217(IAS2Context * lpContext,IF2UnPacker * lpInUnPacker,IF2Packer * lpOutPacker,IConnection * lpParentConn=NULL);

//AF_日间更新_多数据集更新_消息主题发布
int FUNCTION_CALL_MODE F3615219(IAS2Context * lpContext,IF2UnPacker * lpInUnPacker,IF2Packer * lpOutPacker,IConnection * lpParentConn=NULL);

#endif /* _S_AS_JC_O4RJFUNC_H */
