/***********************************************************************
��Ȩ����: �������ӹɷ����޹�˾
��Ŀ����: MC2.0��Ŀ
��    ��: V1.0
����ϵͳ: Windows/Linux/HP-UX
�� �� ��: im_interface.h
�ļ�����: 
�� Ŀ ��: CRES
�� �� Ա: 05909
��������: 2013-1-16   11:57:23
��    ��:
�޸�����:
***********************************************************************/
#ifndef IM_INTERFACE_H
#define IM_INTERFACE_H

#include <Include/plugin_interface.h>


/* ����ӿ�ID���� */
#define SID_IM "hsim"

/* ���������׼�������������ܼ�����˵���μ�Include/plugin_interface.h */
#ifdef __cplusplus
extern "C" {
#endif
    ///ȡ���ʵ��
    IKnown* FUNCTION_CALL_MODE GetIMInstance();
    ///�����ʼ��
    int FUNCTION_CALL_MODE IMInit(void* lpInstance, PFOnSetTimeOut pfOnSetTimeOuts);
    ///ȡ����������������ID��
    char*  FUNCTION_CALL_MODE GetIMDependSvr(void* lpInstance);
    ///��ѯ������еĲ����Ϣ
    int FUNCTION_CALL_MODE GetIMInfo(int iIndex, tagBaseServiceInfo* ppv);
#ifdef __cplusplus
}
#endif

#endif
