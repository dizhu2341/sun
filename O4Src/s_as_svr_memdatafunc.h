

#ifndef _S_AS_SVR_MEMDATAFUNC_H
#define _S_AS_SVR_MEMDATAFUNC_H

#include "hshead.h" 
//AF_内存数据库_查询信息
int FUNCTION_CALL_MODE F990011(IAS2Context * lpContext,IF2UnPacker * lpInUnPacker,IF2Packer * lpOutPacker,IConnection * lpParentConn=NULL);

//AF_内存数据库_修改信息
int FUNCTION_CALL_MODE F990012(IAS2Context * lpContext,IF2UnPacker * lpInUnPacker,IF2Packer * lpOutPacker,IConnection * lpParentConn=NULL);

//AF_内存数据库_删除信息
int FUNCTION_CALL_MODE F990013(IAS2Context * lpContext,IF2UnPacker * lpInUnPacker,IF2Packer * lpOutPacker,IConnection * lpParentConn=NULL);

#endif /* _S_AS_SVR_MEMDATAFUNC_H */
