/*******************************************************
  Դ��������:rm_interface.h
  �������Ȩ:�������ӹɷ����޹�˾
  ϵͳ����:  ��Ϣ����2.0
  ģ������:  ��Ϣ�����鲥ģ��
  ����˵��:  
				ͨ�õĿɿ��鲥�ӿ�,
				ʵ�־�������Χ�ڵĿɿ��鲥
				�������κ�ҵ������߼�
				���ӿڱ���Ϣ���Ŀɿ��鲥ʹ��,Դ�뼶����,�Ժ���Ե�������Ϊ������Ŀʹ��
				
  ��    ��:  maoyj
  ��������:  20120509
  ��    ע:  
*********************************************************/

#ifndef _rm_interface_h
#define _rm_interface_h

#include <Include/plugin_interface.h>
#include <os/inttypes.h>
#include <os/config_env.h>

// ������
typedef enum ERM_ERR
{
	RM_SUCC = 0,
	RM_ERR_SOCKET,		//	�����׽���ʧ��
	RM_ERR_BIND,		//	��ʧ��
	RM_ERR_GET_IP_ADDR,	//	��ȡ����IPʧ��
	RM_ERR_TIMEOUT,		//	��ʱ
	RM_ERR_NOT_SUPPORT,	//	ϵͳ��֧��
	RM_ERR_JOIN,		//	����ಥ��ʧ��
	RM_ERR_INTERFACE,	//	ָ�������Ƿ�
	RM_ERR_NO_BUFF,		//	û���㹻�Ļ���
	RM_ERR_NO_DATA,		//	û������
	RM_ERR_TOO_LONG,	//	����̫��
	RM_ERR_INIT,		//	δ��ʼ��
	RM_ERR_CFT_NOT_SUPPORT,	//	���ò�֧���鲥
};

//	ҵ���޹صĿɿ��鲥�ӿ�
struct IRMSessionInterface
{
	//	���Ѿ����յ����ݶ����л�ȡ.(�ɿ��鲥�ײ�������ݺ�,���ᴥ���ص�,���ǵȴ��ϲ��Լ���ȡ����)
	virtual ERM_ERR FUNCTION_CALL_MODE Recv(char *lpBuff, int& iSize, int iTimeOut, sockaddr_in* lpAddrFrom)=0;
	//	���鲥�鷢������
	virtual ERM_ERR FUNCTION_CALL_MODE Send(char *lpBizData, int iBizDataLen)=0;
	//	���鲥�鷢������
	virtual ERM_ERR FUNCTION_CALL_MODE Send(char *lpBizHead, int iBizHeadLen, char *lpBizData, int iBizDataLen)=0;
	//	��õ�ǰά�����鲥���Ա����
	virtual int FUNCTION_CALL_MODE GetMemberCount()=0;
	//	��ʼ����ǰ�鲥��Ҫ�õ���ͨ�Ų���
	//20130221 xuxp ���ӽӿڲ������Ƿ��ֹ�鲥ѭ��
	virtual ERM_ERR FUNCTION_CALL_MODE InitRM(const char* lpMAddr, uint16 wPort, const char* lpMInterFace,int bForbidMultiLoop=1)=0;	//	��ʼ���ಥͨ�Ų���
	virtual int FUNCTION_CALL_MODE Start()=0;	//	��ʼ�鲥ͨ��
	virtual int FUNCTION_CALL_MODE Stop()=0;	//	ֹͣ�鲥ͨ��
	virtual int FUNCTION_CALL_MODE Syning()=0;	//	�鲥�ڲ�ͬ�������Ϣ
};

IRMSessionInterface*  FUNCTION_CALL_MODE CreatRM();
int  FUNCTION_CALL_MODE DestroyRM(IRMSessionInterface* lpRMSession);

#endif
