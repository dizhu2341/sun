///Service_init ����ӿ�ID���弰���׼��������
/*********************************************************************************************
  Դ��������: service_init_interface.h
  �������Ȩ: �������ӹɷ����޹�˾
  ��������:  
  ģ������:  fsc_service_init

  �������:  �ɹ���ɷ�ת��ͨ���

  ����˵��:  

  ����ĵ�:  

  ��    ��:  �з�����chengjin
  ��������:  2014-11-17
  ��    ע:  
  �޸ļ�¼�� 
*********************************************************************************************/

#ifndef __Service_init_Interface_H__
#define __Service_init_Interface_H__
#include <Include/plugin_interface.h>

///����ӿ�ID����
#define SID_SERVICE_INIT "com.hundsun.fbase.service_init"

///����ӿڶ���
struct IService_init: public IKnown
{
    ///@todo���ݹ淶����ӿں��������麯�������磺
    //virtual const char * FUNCTION_CALL_MODE GetName(int iIndex) = 0;
    
};

///���������׼�������������ܼ�����˵���μ�Include/plugin_interface.h
#ifdef __cplusplus
extern "C" {
#endif
    ///��ѯ������еĲ����Ϣ
    int FUNCTION_CALL_MODE GetService_initInfo(int iIndex, tagBaseServiceInfo * ppv );
    ///ȡ���ʵ��
    IKnown * FUNCTION_CALL_MODE GetService_initInstance();
    ///ȡ����������������ID��
    char *  FUNCTION_CALL_MODE GetService_initDependSvr(void * lpInstance);
    ///�����ʼ��
    int FUNCTION_CALL_MODE Service_initInit(void * lpInstance, PFOnSetTimeOut pfOnSetTimeOut);
#ifdef __cplusplus
}
#endif

#endif       /*end def __Service_init_Interface_H__*/

