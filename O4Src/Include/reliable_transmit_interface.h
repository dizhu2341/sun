#ifndef __RELIABLE_TRANSMIT_INTERFACE_H__
#define __RELIABLE_TRANSMIT_INTERFACE_H__



#include <Include/service_interface.h>
#include <Include/glbdef.h>
#include <Include/esb_message_interface.h>


#define SID_RELIABLE_TRANS		"rtransmit"



struct IReliableTrans:IMessageService
{
	/**
	 *	������������õķ��ͽӿ�, �ӿ���������, Ȼ���������, ������
	 *	֧�ֶ�����, �����ɶԷ��ڵ���������, ����packID
	**/
	virtual int Push(IESBMessage *lpMsg, char *lpPluginID, uint32 dwTimeOut = -1) = 0;

	virtual IESBMessage *Pop(const char *lpPluginID = NULL) = 0;

};



#ifdef __cplusplus
extern "C" { 
#endif

	///�����ʼ��
	/**
	 *@return int �汾�� yyyymmdd��ʽ
	 */
	int  FUNCTION_CALL_MODE ReliableTrans_Init(void *lp, PFOnSetTimeOut);
	
	///ȡ����ӿھ��
	/**
	 *@return void * ����ģʽ
	 */
	IKnown * FUNCTION_CALL_MODE GetReliableTransInstance(void);

	///ȡ����ӿ���������
	/**
	 *@param iIndex 
	 *@return IKnown * ���������ʶ 
	 */
	char * FUNCTION_CALL_MODE GetReliableTransDependService(void *lp);
	
	///����ͳһ��AS�������������ѯ�ӿ� getxxxInfo()
	/**���������������̬����ʱ��ͨ�����ӿڻ��Ի�ȡ������Ϣ(����xxxxInit(),getxxxxInterface()����ָ��)
	 *@param void ** ppv    �������������Ϣ(�������)��
	 *@return ����0��ʾ�鵽��Ҫ�Ľӿڣ����򷵻ظ���
	 */
	int FUNCTION_CALL_MODE GetRTransmitInfo(int iIndex, tagBaseServiceInfo * ppv);

#ifdef __cplusplus
}
#endif



#endif



