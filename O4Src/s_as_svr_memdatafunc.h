

#ifndef _S_AS_SVR_MEMDATAFUNC_H
#define _S_AS_SVR_MEMDATAFUNC_H

#include "hshead.h" 
//AF_�ڴ����ݿ�_��ѯ��Ϣ
int FUNCTION_CALL_MODE F990011(IAS2Context * lpContext,IF2UnPacker * lpInUnPacker,IF2Packer * lpOutPacker,IConnection * lpParentConn=NULL);

//AF_�ڴ����ݿ�_�޸���Ϣ
int FUNCTION_CALL_MODE F990012(IAS2Context * lpContext,IF2UnPacker * lpInUnPacker,IF2Packer * lpOutPacker,IConnection * lpParentConn=NULL);

//AF_�ڴ����ݿ�_ɾ����Ϣ
int FUNCTION_CALL_MODE F990013(IAS2Context * lpContext,IF2UnPacker * lpInUnPacker,IF2Packer * lpOutPacker,IConnection * lpParentConn=NULL);

#endif /* _S_AS_SVR_MEMDATAFUNC_H */
