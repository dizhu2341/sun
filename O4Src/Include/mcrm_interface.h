/*******************************************************
  Դ��������:mcrm_interface.h
  �������Ȩ:�������ӹɷ����޹�˾
  ϵͳ����:  ��Ϣ����2.0
  ģ������:  ��Ϣ�����鲥ģ��
  ����˵��:  
  ��    ��:  maoyj
  ��������:  20120509
  ��    ע:  
	��Ϣ������Ŀʹ�ÿɿ��鲥,����Ҫ���ı��ļ��Ľӿڼ���,������ĸ��ײ��rm_interface�ӿ�

	���������龰��ʹ���鲥�ӿڵ�����:
		1:	�ܿ�ͨ��AR���յ�ĳ������ķ�����Ϣ
		2:	�����鲥ģ�齫����Ϣ���͸�����������Ա
			2.1:	������ڴ漶�ɿ���Ϣ,�����첽����,��������
			2.2:	������ļ����ɿ�,����ͬ������,iFlagΪ0
			2.3:	�����ϵͳ���ɿ�,����ͬ������,iFlagΪ1
			2.4:	����ͬ�����͵ĵ���,�����ᱻ����,ֱ��һ��ACK��������ACK����
		3:	����յ��鲥����,�ж϶Է��Ƿ���ҪACK,����Ҫ�����ϲ�ص������ɹ����غ�,�Զ�����ACK.
	������ȱ��,�ʱʹ���鲥������
		1:	������ĵڶ��׶�,����ȱ�ڵ��ϲ���֯һ�������ش��ı����鲥
		2:	

*********************************************************/

#ifndef _mcrm_interface_h
#define _mcrm_interface_h

#include <Include/rm_interface.h>		//	�ײ�Ŀɿ��鲥�ӿ�

//	������Ϣ���Ŀɿ��鲥�����
#define SID_MSGCENTER_RM   "mc_rm"


//	�߱���Ϣ����ҵ��㺬�������:
/*
	����������ȱ��,����
	��һ��tʱ��,�ǵȴ�,����ȱ�ڱ��Զ��
	�ڶ���tʱ���ǳ����ڼ�Ⱥ�ڲ����(���ɱ��ӿڰ������)
		��ô��Ҫ:
			rebuild����			�鲥����
			���rebuild��Ӧ��	��������
	������tʱ���ǳ������󷢲����ش�(�����ͨ����AR���ͱ���ʵ��)
*/


//	��Ϣ���ջص�����
/*
	����:	��Ϣ���Եĳ�ԱIP��ַ		���յ���Ϣ��������		�������ݳ���
	��ʵ���ݿ��ܲ�����ͨ���鲥����,���ǵ�������,���ܿ�ģ���ڵڶ���tʱ�����,����Ⱥ�ڷ��������ش����鲥
	��Ⱥ�ڲ��ĳ�Աͨ��UniSend�ӿ���Ӧ������.
	��������Ա��Ӧrebuild�����,���յ�����,Ҳ�Իص�����ʽ��Ӧ.
	����:
	0:	�ɹ�	����ʧ��
	���ص������ɹ����غ�,����ͬ�����͹������鲥����,���ӿڻ��Զ��ظ��Զ�һ��ACK,�԰����Զ�
	�������н��.
	��ע:	ָ���ַ���ڻص�˲��Ϸ�,֮��,����ȷ����Ч
*/
typedef int (FUNCTION_CALL_MODE * OnMultiRecv)(sockaddr_in* lpFrom, const char* lpBuff, int iLen);
//	�鲥�ӿ�,�ϲ��ڵ��÷��ͽӿ�ʱ,�������һ��Ψһ��dwmsgid,�Թ���Ӧ��ƥ��(��Ȼ����ϲ���Ϊû�б�Ҫ
//	��ȫ����Ϊ���еķ��;�����0,��������һ��,�ͻᵼ��Ӧ��ƥ����ֹ���)
struct IMCRMSessionInterface : IKnown
{
public:
	//	�����鲥���ݽ���ʱ�Ļص�,�鲥ͨ�Ų���,�ɲ���Լ������ò�������(Ҳ���������ش�ʱ�ĵ�����Ӧ���ݵ���)
	virtual ERM_ERR FUNCTION_CALL_MODE SetCallBack(OnMultiRecv RecvFunc)=0;
	//	�첽�����鲥(���ײ�ķ��Ͷ��л�ѹʱ,���������)
	virtual ERM_ERR FUNCTION_CALL_MODE MultiSend(char *lpBuff, int iDataLen)=0;
	//	ͬ�������鲥�������ɹ�����ʱ��������һ����Ա�Ѿ��ɹ������˸��鲥, int iTimeOut ͬ���ȴ��ĳ�ʱʱ��
	//	iFlag 0:ֻ��Ҫһ��Ӧ��  1 ��Ҫȫ��Ӧ��
	virtual ERM_ERR FUNCTION_CALL_MODE SynMultiSend(char *lpBuff, int iDataLen, int iFlag, int iTimeOut)=0;
	//	��Ⱥ��Ա��Ӧ������Ա�Ĳ�ȱ����,�Ե�����ʽ����
	virtual ERM_ERR FUNCTION_CALL_MODE UniSendTo(char *lpBuff, int iDataLen, sockaddr_in* lpAddr)=0;
	//	��ȡ��Ⱥ�ڲ���Ա����
	virtual int FUNCTION_CALL_MODE GetMemberCount()=0;
};

//	���������������,����������ܵ���
#ifdef __cplusplus
extern "C" {
#endif
    int		FUNCTION_CALL_MODE GetMCRMInfo( int iIndex, tagBaseServiceInfo * ppv );
	IKnown* FUNCTION_CALL_MODE GetMCRMInstance();
	int		FUNCTION_CALL_MODE GetMCRMInit( void * lpInstance, PFOnSetTimeOut pfOnSetTimeOut );
	char*	FUNCTION_CALL_MODE GetMCRMDependSvr( void * lpInstance );
	
#ifdef __cplusplus
}
#endif

#endif
