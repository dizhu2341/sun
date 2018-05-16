#ifndef __ArbMgrMain_H__
#define __ArbMgrMain_H__

#include <string.h>
#include <map>
#include <Include/plugin_interface.h>
#include <Include/config_interface.h>
#include <Include/pack_interface.h>
#include <Include/plugin_interface.h>

///����ӿ�ID����
#define SID_O4ARBMGR "hundsun.o4.arbmgr"

///���������׼�������������ܼ�����˵���μ�Include/plugin_interface.h
#ifdef __cplusplus
extern "C" {
#endif
    ///��ѯ������еĲ����Ϣ
    int FUNCTION_CALL_MODE GetArbmgrInfo(int iIndex, tagBaseServiceInfo * ppv );
    ///ȡ���ʵ��
    IKnown * FUNCTION_CALL_MODE GetArbmgrInstance();
    ///ȡ����������������ID��
    char *  FUNCTION_CALL_MODE GetArbmgrDependSvr(void * lpInstance);
    ///�����ʼ��
    int FUNCTION_CALL_MODE ArbmgrInit(void * lpInstance, PFOnSetTimeOut pfOnSetTimeOut);
#ifdef __cplusplus
}
#endif

#endif       /*end def __ArbMgrMain_H__*/

