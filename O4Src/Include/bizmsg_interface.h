/** @file
* ҵ����Ϣ�Ľӿ��ļ�
* @author  �����M
* @author  �������ӹɷ����޹�˾
* @version 1.0
* @date    20130625
*/
#ifndef BIZ_MESSAGE_INTERFACE_H
#define BIZ_MESSAGE_INTERFACE_H

#if defined(_WIN32)&& _MSC_VER < 1300
#pragma warning(disable: 4786)				//����ڱ�������STLͷ�ļ�ǰ
#pragma warning(disable: 4710)				//����ڱ�������STLͷ�ļ�ǰ
#endif
#include <string.h>
#include <Include/plugin_interface.h>
#include <Include/tag_def.h>

///ESB�������ȣ�����Ϊ�ɼ��ַ������ܰ���ʵ���ָ������ո񡢷ֺ�;
#define IDENTITY_NAME_LENGTH	32
///ʵ��������ռλ����
#define ID_LENGTH               4 
///�ڵ���ȫ��,����ʱʹ��char sName[ID_STR_LEN+1]
#define ID_STR_LEN		       (IDENTITY_NAME_LENGTH + ID_LENGTH + 1)


//	����ӿ�������󳤶�,����ʱʹ��char sName[PLUGINID_LENGTH+1]
#define PLUGINID_LENGTH	256
//	���ʵ��������󳤶�,����ʱʹ��char sName[PLUGIN_NAME_LENGTH+1]
#define PLUGIN_NAME_LENGTH	(PLUGINID_LENGTH+ID_LENGTH+1)
//	��������󳤶�.����ʱʹ��char sName[SVR_NAME_LENGTH+1]
#define SVR_NAME_LENGTH	256
//	����ʵ������󳤶�.����ʱʹ��char sName[PLUGINID_NAME_LENGTH+1]
#define SVRINSTANCE_NAME_LENGTH	(SVR_NAME_LENGTH+ID_LENGTH+1)

typedef struct tagBizRouteInfo
{
	char ospfName[ID_STR_LEN+1];//·��Ŀ��ڵ��м������
	char nbrName[ID_STR_LEN+1];//�м���ڵ���ھ�����
	char svrName[SVRINSTANCE_NAME_LENGTH+1];//�м���Ľ�������
	char pluginID[PLUGIN_NAME_LENGTH+1];//�м�������
	int connectID;//���Ӻ�
	int memberNO;//��Ա���
	
	tagBizRouteInfo()
	{
		memset(this,0,sizeof(tagBizRouteInfo));
	}
}BIZROUTE_INFO;


struct IBizMessage : public IKnown
{
	//���ù��ܺ�
	virtual void FUNCTION_CALL_MODE SetFunction(const int nFUnctionNo) = 0;
	//��ȡ���ܺ�
	virtual int FUNCTION_CALL_MODE GetFunction() = 0;

	//���ð�����
	virtual void FUNCTION_CALL_MODE SetPacketType(const int nPacketType) = 0;
	//��ȡ������
	virtual int FUNCTION_CALL_MODE GetPacketType() = 0;

	//����Ӫҵ����
	virtual void FUNCTION_CALL_MODE SetBranchNo(const int nBranchNo) = 0;
	//��ȡӪҵ����
	virtual int FUNCTION_CALL_MODE GetBranchNo() = 0;

	//����ϵͳ��
	virtual void FUNCTION_CALL_MODE SetSystemNo(const int nSystemNo) = 0;
	//��ȡϵͳ��
	virtual int FUNCTION_CALL_MODE GetSystemNo() = 0;

	//������ϵͳ��
	virtual void FUNCTION_CALL_MODE SetSubSystemNo(const int nSubSystemNo) = 0;
	//��ȡ��ϵͳ��
	virtual int FUNCTION_CALL_MODE GetSubSystemNo() = 0;

	//���÷����߱��
	virtual void FUNCTION_CALL_MODE SetSenderId(const int nSenderId) = 0;
	//��ȡ�����߱��
	virtual int FUNCTION_CALL_MODE GetSenderId() = 0;

	//���ð����
	virtual void FUNCTION_CALL_MODE SetPacketId(const int nPacketId) = 0;
	//��ȡ�����
	virtual int FUNCTION_CALL_MODE GetPacketId() = 0;

	//����Ŀ�ĵ�·��
	virtual void FUNCTION_CALL_MODE SetTargetInfo(const BIZROUTE_INFO targetInfo) = 0;
	//��ȡĿ�ĵ�·��
	virtual void FUNCTION_CALL_MODE GetTargetInfo(BIZROUTE_INFO& targetInfo) = 0;
	
	//���÷�����·��
	virtual void FUNCTION_CALL_MODE SetSendInfo(const BIZROUTE_INFO sendInfo) = 0;
	//��ȡ������·��
	virtual void FUNCTION_CALL_MODE GetSendInfo(BIZROUTE_INFO& sendInfo) = 0;

	//���ô����
	virtual void FUNCTION_CALL_MODE SetErrorNo(const int nErrorNo) = 0;
	//��ȡ�����
	virtual int FUNCTION_CALL_MODE GetErrorNo() = 0;
	
	//���ô�����Ϣ
	virtual void FUNCTION_CALL_MODE SetErrorInfo(const char* strErrorInfo) = 0;
	//��ȡ������Ϣ
	virtual const char* FUNCTION_CALL_MODE GetErrorInfo() = 0;
	
	//���÷�����
	virtual void FUNCTION_CALL_MODE SetReturnCode(const int nReturnCode) = 0;
	//��ȡ������
	virtual int FUNCTION_CALL_MODE GetReturnCode() = 0;

	//����ҵ������
	virtual void FUNCTION_CALL_MODE SetContent(void* lpContent,int iLen) = 0;
	//��ȡҵ������
	virtual const void* FUNCTION_CALL_MODE GetContent(int& iLen) = 0;

	//���½ӿ�������Ϣ����1.0�Ķ���
	//���ö�������
	virtual void FUNCTION_CALL_MODE SetIssueType(const int nIssueType) = 0;
	//��ȡ��������
	virtual int FUNCTION_CALL_MODE GetIssueType() = 0;

	//�������
	virtual void FUNCTION_CALL_MODE SetSequeceNo(const int nSequeceNo) = 0;
	//��ȡ���
	virtual int FUNCTION_CALL_MODE GetSequeceNo() = 0;

	//���ùؼ��ֶ���Ϣ
	virtual void FUNCTION_CALL_MODE SetKeyInfo(void* lpKeyData,int iLen) = 0;
	//��ȡ�ؼ��ֶ���Ϣ
	virtual const void* FUNCTION_CALL_MODE GetKeyInfo(int& iLen) = 0;

	//���ø������ݣ���������ʱԭ������
	virtual void FUNCTION_CALL_MODE SetAppData(const void* lpAppdata,int nAppLen) = 0;
	//��ȡ�������ݣ���������ʱԭ������
	virtual const void* FUNCTION_CALL_MODE GetAppData(int& nAppLen) = 0;

	//����תӦ��
	virtual int	FUNCTION_CALL_MODE ChangeReq2AnsMessage() = 0;

	//��ȡ������
	virtual void* FUNCTION_CALL_MODE GetBuff(int& nBuffLen) = 0;
	//����������
	virtual int	FUNCTION_CALL_MODE SetBuff(const void* lpBuff,int nBuffLen) = 0;

	//20131227 xuxp ����Reset�ӿڣ�ȷ����Ϣ�����ظ�ʹ��
	//�����Ϣ�ڵ��ֶΣ������´θ��á�
	virtual void FUNCTION_CALL_MODE ReSet() = 0;
};


#endif
