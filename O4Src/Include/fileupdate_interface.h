/***********************************************************************
��Ȩ����: �������ӹɷ����޹�˾
��Ŀ����: MC2.0��Ŀ
��    ��: V1.0
����ϵͳ: Windows/Linux/HP-UX
�� �� ��: fileupdate_interface.h
�ļ�����: 
�� Ŀ ��: CRES
�� �� Ա: 05909
��������: 2012-7-17   14:40:54
��    ��:
�޸�����:
***********************************************************************/
#ifndef FILEUPDATE_INTERFACE_H
#define FILEUPDATE_INTERFACE_H

#include <Include/plugin_interface.h>


/* ����ӿ�ID���� */
#define SID_FILEUPDATE "fileupdate"

/* ���������׼�������������ܼ�����˵���μ�Include/plugin_interface.h */
#ifdef __cplusplus
extern "C" {
#endif
    ///ȡ���ʵ��
    IKnown* FUNCTION_CALL_MODE GetFileUpdateInstance();
    ///�����ʼ��
    int FUNCTION_CALL_MODE FileUpdateInit(void* lpInstance, PFOnSetTimeOut pfOnSetTimeOuts);
    ///ȡ����������������ID��
    char*  FUNCTION_CALL_MODE GetFileUpdateDependSvr(void* lpInstance);
    ///��ѯ������еĲ����Ϣ
    int FUNCTION_CALL_MODE GetFileUpdateInfo(int iIndex, tagBaseServiceInfo* ppv);
#ifdef __cplusplus
}
#endif

#endif
