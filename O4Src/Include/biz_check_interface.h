/*******************************************************
  Դ��������:biz_check_interface.h
  �������Ȩ:�������ӹɷ����޹�˾
  ϵͳ����:  ��Ϣ����V2.0
  ģ������:  ҵ�����api
  ����˵��:
  ��    ��:  dongpf
  ��������:  20120516
*********************************************************/

#ifndef _BIZ_CHECK_H
#define _BIZ_CHECK_H

#ifdef _WIN32
#ifndef FUNCTION_CALL_MODE
	#define FUNCTION_CALL_MODE  __stdcall 
#endif
#endif

#include <Include/pack_interface.h>
#include <Include/config_interface.h>
#include <Include/esb_message_factory_interface.h>
#include <Include/hsdb_interface.h>

///�����������ģ���ҵ�����ʹ��
struct IAppContext : public IKnown
{
	///ȡҵ����������ӿ�
	virtual IF2PackSvr * FUNCTION_CALL_MODE GetF2PackSvr() = 0;
	
	///ȡ���ݿ�����
	/**������������Դ��ΪNULL����ȡAS���õ�ȱʡ����Դ��
	 *@param const char * szDataSourceName ����Դ��
	 *@return char *  ȱʡ����Դ�� 
	 */
	virtual IConnection *  FUNCTION_CALL_MODE GetDBConnection(const char * szDataSourceName = NULL ) = 0; 

	///ͬ�������ӷ���
	/**
	 *@param int iFunID �ӷ�����õĹ��ܺ�[in]
	 *@param IF2UnPacker *lpInPacker �����[in]
	 *@param IF2Packer *lpOutPacker Ӧ���[in]�� �������ֵ������0����ô������lpOutPacker����ȡerror_no��error_info
	 *@param int iTimeOut  ��ʱʱ��(ms)[in]
	 *@return ����0��ʾ�ɹ�����Ҫ�������ͷŻ�õ�Ӧ����Ϣ������-1ʱ������ʧ�ܣ�����-2,��ʾ�õ��ó�ʱ; ����-3,��������
	 */
	virtual int FUNCTION_CALL_MODE CallSubService(int iFunID, IF2UnPacker *lpInPacker, IF2Packer *lpOutPacker, int iTimeOut) =0;
};

//
#ifdef __cplusplus
extern "C" { 
#endif

///��ȡ�����б�
/*
 *@param IAppContext * lpContext   �����Ľӿ�[in]
 *@param IF2Packer * lpAnswer    Ӧ���[in]
 *@param int iTimeOut            ��ʱʱ��[in]
 *@return ���ش�����룬0�ɹ������������0�����������lpAnswer��error_no�ֶ�,������ϢӦ�÷���error_info�ֶ�
 */
int FUNCTION_CALL_MODE GetTopicList(IAppContext * lpContext, IF2Packer * lpAnswer, int iTimeOut);
	
///��ȡ���충����
/*
 *@param IAppContext * lpContext   �����Ľӿ�[in]
 *@param IF2Packer * lpAnswer    Ӧ���[in]
 *@param int iTimeOut            ��ʱʱ��[in]
 *@return ���ش�����룬0�ɹ������������0�����������lpAnswer��error_no�ֶ�,������ϢӦ�÷���error_info�ֶ�
 */
int FUNCTION_CALL_MODE GetDualSub(IAppContext * lpContext, IF2Packer * lpAnswer, int iTimeOut);
	
///������Ȩ��У��
/*
 *@param IAppContext * lpContext   �����Ľӿ�[in]
 *@param char* lpTopic    ��������[in]
 *@param char* lpPublisher  ����������[in]
 *@param IF2Packer * lpAnswer Ӧ���[in]
 *@return ���ش�����룬0�ɹ������������0�����������lpAnswer��error_no�ֶ�,������ϢӦ�÷���error_info�ֶ�
 */
int FUNCTION_CALL_MODE CheckPub(IAppContext * lpContext, char* lpTopic, char* lpPublisher, IF2Packer * lpAnswer);
	
///У�鶩��Ȩ��
/*
 *@param IAppContext * lpContext   �����Ľӿ�[in]
 *@param char* lpTopic    ��������[in]
 *@param IF2UnPacker * lpSubReq �����[in]
 *@param char* lpSub  ����������[in]
 *@param IF2Packer * lpAnswer Ӧ���[in]
 *@return ���ش�����룬0�ɹ������������0�����������lpAnswer��error_no�ֶ�,������ϢӦ�÷���error_info�ֶ�
 */
int FUNCTION_CALL_MODE CheckSub(IAppContext * lpContext, char* lpTopic, IF2UnPacker * lpSubReq, char* lpSub, IF2Packer * lpAnswer);

#ifdef __cplusplus
  }
#endif
#endif
