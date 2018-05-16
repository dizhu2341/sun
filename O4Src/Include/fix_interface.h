/// ��˵��
/*******************************************************
Դ��������:
�������Ȩ:�������ӹɷ����޹�˾
ϵͳ����:  �������������ӿ�
ģ������:  Fix
����˵��:  ʵ��fix���������Э��ת���ӿ�
��    ��:  dongpf
��������:  
��    ע:  

  �޸���Ա��
  �޸����ڣ�
  �޸�˵����
*********************************************************/


#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_FIXBEHAVIORPARA_4736C1D80021_INCLUDED
#define _INC_FIXBEHAVIORPARA_4736C1D80021_INCLUDED

#include <Include/MessageInterface.h>
#include <Include/plugin_interface.h>
#include <Include/esb_message_factory_interface.h>


#define SID_SERVICE_FIX							"fixSvr"
#define SID_CHANNEL_FIX                         "fix"

struct IFixService : public IKnown
{
public:
   
	/// ��fixЭ�鱨��ת��Ϊ��������
    /**
      *@ Param  const IMessage * srcMsg: fixЭ�鱨��
	  *@ Param  IESBMessage * dstMsg:    �����м��Э�鱨��
	  *@ Param  const char * szdictName: �����ֵ�����
      *@ return:						 0��ʾ�ɹ�����0��ʾʧ��
      */
    virtual int FUNCTION_CALL_MODE ChangeFixToPack( const IMessage * srcMsg, IESBMessage * dstMsg, const char * szdictName ) = 0;

	/// ��fixЭ�鱨��ת��Ϊ��������
    /**
	  *@ Param  const IESBMessage * srcMsg: �����м��Э�鱨��
	  *@ Param  IMessage * dstMsg:       fixЭ�鱨��
	  *@ Param  const char * szdictName: �����ֵ�����
      *@ return:						 0��ʾ�ɹ�����0��ʾʧ��
      */
    virtual int FUNCTION_CALL_MODE ChangePackToFix( IESBMessage * srcMsg, IMessage * dstMsg, const char * szdictName ) = 0;

	/// ���ݴ����뷵�ش�����Ϣ
    /**
	  *@ Param  int iError_No:			 ������
      *@ return:						 ������Ϣ
      */
	virtual const char * FUNCTION_CALL_MODE GetErrorInfo( int iError_No ) = 0;
};

#ifdef __cplusplus
extern "C" {
#endif

    int FUNCTION_CALL_MODE GetFixServiceInfo( int iIndex, tagBaseServiceInfo * ppv );

	IKnown * FUNCTION_CALL_MODE GetFixServiceInstance();

	int   FUNCTION_CALL_MODE GetFixServiceInit( void * lpInstance, PFOnSetTimeOut pfOnSetTimeOut );
	
	char *  FUNCTION_CALL_MODE GetFixServiceDependSvr( void * lpInstance );

#ifdef __cplusplus
}
#endif


#endif /* _INC_FIXBEHAVIORPARA_4736C1D80021_INCLUDED */
