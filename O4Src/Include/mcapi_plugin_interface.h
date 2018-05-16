/*******************************************************
  Դ��������:mcapi_plugin_interface.h  (plugin)
  �������Ȩ:�������ӹɷ����޹�˾
  ϵͳ����:  ��Ϣ����2.0
  ģ������:  ���API��
  ����˵��:  ���API�ӿ�˵��
  ��    ��:  xuxp
  ��������:  20120809
  ��    ע:
  20130917 majc ���ȡ�����Ľӿ�CancelSubscribeTopicEx
*********************************************************/


#ifndef __MCAPI_PLUGIN_INTERFACE_H__
#define __MCAPI_PLUGIN_INTERFACE_H__

/*
���ķ����ӿڲ������һ����ˮ�߲������ͨ�ӿڲ��
*/

#include <Include/service_interface.h>
#include <Include/glbdef.h>
#include <Include/esb_message_interface.h>


//ͨ��ͨ������Ľӿ���
#define SID_MCAPI		   	"mcapi"
#define SID_MCCLIENTAPI		"mcclientapi"
#define MAX_TOPICNAME_LEN 256
#define IDENTITY_NAME_LENGTH 32
#define MAX_MACADDRESS_LEN	18
#define MAX_RAND_LEN	4
#define MAX_BIZNAME_LEN IDENTITY_NAME_LENGTH+1+MAX_MACADDRESS_LEN+1+MAX_RAND_LEN+2



enum ReliableLevelPlugin{API_LEVEL_DOBEST =0,//������Ϊ
					API_LEVEL_DOBEST_BYSEQ = 1,//��������
					API_LEVEL_MEM = 2,//�ڴ�
					API_LEVEL_FILE = 3,//�ļ�
					API_LEVEL_SYSTEM= 4};//ϵͳ

class IPluginFilterInterface: public IKnown
{
public:
  	//���ù��������������������ֺ�ֵ
    /**
    * @param filterName ������������
    * @param filterValue �����������ֵ�ֵ
    **/
    virtual void FUNCTION_CALL_MODE SetFilterPlugin(const char* filterName, const char* filterValue) = 0;

    //���ݹ������������ֻ�ȡ����������ֵ
    /**
    * @param filterName ��Ӧ�Ĺ�����������
    * @return ���ض�Ӧ�Ĺ����������ֵ�����ֵ�����򷵻�NULL��
    **/
    virtual const char* FUNCTION_CALL_MODE GetFilterValuePlugin(const char* filterName) = 0;

	//�����±��ȡ��������������
	/**
	* @param index ��Ӧ�Ĺ��������±�
	* @return ���ض�Ӧ���±�������������֣����򷵻�NULL��
	**/
	virtual const char* FUNCTION_CALL_MODE GetFilterNameByIndexPlugin(int index) = 0;

    //�����±��ȡ����������ֵ
	/**
	* @param index ��Ӧ�Ĺ��������±�
	* @return ���ض�Ӧ���±����������ֵ�����򷵻�NULL��
	**/
	virtual const char* FUNCTION_CALL_MODE GetFilterValueByIndexPlugin(int index) = 0;

	//��ȡ���������ĸ���
	/**
	* @return ���ض�Ӧ���������ĸ�����û�з���0
	**/
	virtual int FUNCTION_CALL_MODE GetCountPlugin() = 0;
};

class IPluginSubscribeParamInterface:public IKnown
{
public:
	//������������
	/**
	* @param szName ��Ӧ����������
	**/
	virtual void FUNCTION_CALL_MODE SetTopicNamePlugin(const char* szName) = 0;

	//���ø�������
	/**
	* @param lpData �������ݵ��׵�ַ
	* @param iLen �������ݵĳ���
	**/
	virtual void FUNCTION_CALL_MODE SetAppDataPlugin(const void* lpData,int iLen) = 0;
	
	//��ӹ�������
	/**
	* @param filterName ��������������
	* @param filterValue ����������ֵ
	**/
	virtual void FUNCTION_CALL_MODE SetFilterPlugin(const char* filterName, const char* filterValue) = 0;

	//��ӷ����ֶ�
	/**
	* @param fieldName ��Ҫ��ӵķ����ֶ�
	**/
	virtual void FUNCTION_CALL_MODE SetReturnFieldPlugin(const char* fieldName) = 0;

	//�����Ƿ�ȱ��־
	/**
	* @param bFromNow true��ʾ��Ҫ֮ǰ�����ݣ�Ҳ���ǲ�ȱ��false��ʾ����Ҫ��ȱ
	**/
	virtual void FUNCTION_CALL_MODE SetFromNowPlugin(bool bFromNow) = 0;

	//���ø��Ƕ��ı�־
	/**
	* @param bReplace true��ʾ���Ƕ��ģ�ȡ��֮ǰ�����ж��ģ�ֻ������ǰ�Ķ��ģ�false��ʾ׷�Ӷ���
	**/
	virtual void FUNCTION_CALL_MODE SetReplacePlugin(bool bReplace) = 0;

	//���÷��ͼ��
	/**
	* @param nSendInterval ��λ����
	**/
	virtual void FUNCTION_CALL_MODE SetSendIntervalPlugin(int nSendInterval) = 0;

	//��ȡ��������
	/**
	* @return ��������������Ϣ
	**/
	virtual const char* FUNCTION_CALL_MODE GetTopicNamePlugin() = 0;

	//��ȡ��������
	/**
	* @param iLen ���Σ���ʾ�������ݵĳ���
	* @return ���ظ��������׵�ַ��û�з���NULL
	**/
	virtual const void* FUNCTION_CALL_MODE GetAppDataPlugin(int *iLen) = 0;

	//��ȡ��Ӧ�Ĺ����ֶε�����
	/**
	* @param index ��Ӧ�Ĺ��������±�
	* @return ���ض�Ӧ���±�������������֣����򷵻�NULL��
	**/
	virtual const char* FUNCTION_CALL_MODE GetFilterNameByIndexPlugin(int index) = 0;

	//�����±��ȡ����������ֵ
	/**
	* @param index ��Ӧ�Ĺ��������±�
	* @return ���ض�Ӧ���±����������ֵ�����򷵻�NULL��
	**/
	virtual const char* FUNCTION_CALL_MODE GetFilterValueByIndexPlugin(int index) = 0;

	//���ݹ������������ֻ�ȡ����������ֵ
	/**
	* @param filterName ��Ӧ�Ĺ�����������
	* @return ���ض�Ӧ�Ĺ����������ֵ�����ֵ�����򷵻�NULL��
	**/
	virtual const char* FUNCTION_CALL_MODE GetFilterValuePlugin(const char* filterName) = 0;

	//��ȡ���������ĸ���
	/**
	* @return ���ض�Ӧ���������ĸ�����û�з���0
	**/
	virtual int FUNCTION_CALL_MODE GetFilterCountPlugin() = 0;

	//��ȡ�����ֶ�
	/**
	* @return ���ض�Ӧ�ķ����ֶ���Ϣ
	**/
	virtual const char* FUNCTION_CALL_MODE GetReturnFieldPlugin()=0;

	//��ȡ�Ƿ�ȱ�ı�־
	/**
	* @return ���ض�Ӧ�Ĳ�ȱ��־
	**/
	virtual bool FUNCTION_CALL_MODE GetFromNowPlugin() = 0 ;

	//��ȡ�Ƿ񸲸Ƕ��ĵı�־
	/**
	* @return ���ض�Ӧ�ĸ��Ƕ��ı�־
	**/
	virtual bool FUNCTION_CALL_MODE GetReplacePlugin() = 0;

	//��ȡ��Ӧ�ķ���Ƶ��
	/**
	* @return ���ض�Ӧ�ķ��ͼ��
	**/
	virtual int FUNCTION_CALL_MODE GetSendIntervalPlugin() = 0;
};


class IPluginSubscribeInterface;
//�ص��ӿڣ��ϴ�Ӧ��ͬ������ӿڣ��������ƹ�������Ϣ
class IPluginSubCallbackInterface: public IKnown
{
public:
	//�յ�������Ϣ�Ļص�
	/**
	* @param lpSub �ص��Ķ���ָ��
	* @param topicName ��Ϣ��Ӧ������
	* @param lpData ������Ϣ�Ķ�����ָ�룬һ������Ϣ��ҵ��������
	* @param nLength ���������ݵĳ���
	* @return 
	**/
	virtual void FUNCTION_CALL_MODE OnReceivedPlugin(IPluginSubscribeInterface *lpSub,char* topicName, const void *lpData, int nLength) = 0;

	//�յ��޳����������Ϣ�ص���һ����ӵ�����˲��Ե������»�ص�����ӿ�
	/**
	* @param lpSub �ص��Ķ���ָ��
	* @param lpSubParam �޳��Ķ��������
	* @param TickMsgInfo ���˵Ĵ�����Ϣ����Ҫ�ǰ��������ظ��Ķ�����λ����Ϣ
	* @return 
	**/
	virtual void FUNCTION_CALL_MODE OnRecvTickMsgPlugin(IPluginSubscribeInterface *lpSub,IPluginSubscribeParamInterface* lpSubParam,const char* TickMsgInfo) = 0;
};


//���ĽӿڵĶ���
class IPluginSubscribeInterface: public IKnown
{
public:
	/**��������
	* @param lpSubscribeParam ���涨��Ķ��Ĳ����ṹ
	* @param uiTimeout ��ʱʱ��
	* @param lpBizPack ҵ��У����Ҫ���ӵ�ҵ���ֶ��Լ�ֵ��û�о͸��ݹ���������Ϊҵ��У���ֶ�
	* @return ����ֵ����0����ʾ��ǰ���ĳɹ��Ķ��ı�ʶ������Ҫ��ס�����ʶ�Ͷ�����֮���ӳ���ϵ�������ʶ��Ҫ����ȡ�����ĺͽ�����Ϣ�Ļص�����.
	*		  ��������ֵ�����ݴ���Ż�ȡ������Ϣ.
	**/
	virtual int FUNCTION_CALL_MODE SubscribeTopicPlugin(IPluginSubscribeParamInterface* lpSubscribeParamInter ,unsigned int uiTimeout,IF2Packer* lpBizPack=NULL) = 0;

	/**ȡ����������
	* @param topicName �������֣���֪�����־ʹ�NULL
	* @param lpFilter ��Ӧ�Ĺ�������
	* @param uiTimeout ��ʱʱ��
	* @return ����0��ʾȡ�����ĳɹ�����������ֵ�����ݴ���Ż�ȡ������Ϣ��
	**/
	virtual int FUNCTION_CALL_MODE CancelSubscribeTopicPlugin(int index) = 0;
	
	/**��ȡ��ǰ���Ľӿ��Ѿ����ĵ����������Լ�����������Ϣ
	* @param lpPack ���洫��Ĵ����
	*�����ֶΡ�SubcribeIndex IsBornTopic TopicName TopicNo FilterRaw Appdata SendInterval ReturnFileds isReplace isFromNow Stutas QueueCount
	**/
	virtual void FUNCTION_CALL_MODE GetSubcribeTopicPlugin(IF2Packer* lpPack)=0;
	
	//20130917 majc ���ȡ�����Ľӿ�
	/**
    * ȡ����������
    * @param topicName ��������
    * @param lpFilterInterface ��Ӧ�Ĺ�������
    * @return ����0��ʾȡ�����ĳɹ�����������ֵ�����ݴ���Ż�ȡ������Ϣ.
    */
    virtual int FUNCTION_CALL_MODE CancelSubscribeTopicExPlugin(char* topicName,IPluginFilterInterface* lpFilterInterface) = 0;

};

//�����ӿڵĶ���
class IPluginPublishInterface: public IKnown
{
public:
	/**ҵ������ʽ�����ݷ����ӿ�
	* @param topicName �������֣���֪�����־ʹ�NULL
	* @param topicNo �����ţ���֪����žʹ�0
	* @param lpPacker ���������
	* @param iTimeOut ��ʱʱ��
	* @param bCompatible ����1.0�ı�־��ֻ�м��ݲ��������ʱ�����true����������false��
	* @return ����0��ʾ�ɹ�����������ֵ�����ݴ���Ż�ȡ������Ϣ��
	**/
	virtual int FUNCTION_CALL_MODE PubMsgByPackerPlugin(char* topicName,IF2UnPacker* lpUnPacker,int iTimeOut=-1,bool bCompatible=false) = 0;
	
	/**��ҵ������ʽ�����ݷ����ӿڣ�һ������Ƹ�ʽ���ķ���
	* @param topicName �������֣���֪�����־ʹ�NULL
	* @param topicNo �����ţ���֪����žʹ�0
	* @param lpFilter ������������Ҫ�ϲ��Լ�ָ��������Ĭ��û�й�������
	* @param lpData ���������
	* @param nLength ���ݳ���
	* @param iTimeOut ��ʱʱ��
	* @param bCompatible ����1.0�ı�־��ֻ�м��ݲ��������ʱ�����true����������false��
	* @return ����0��ʾ�ɹ�����������ֵ�����ݴ���Ż�ȡ������Ϣ��
	**/
	virtual int FUNCTION_CALL_MODE PubMsgPlugin(char* topicName, IPluginFilterInterface* lpFilterInter, const void *lpData, int nLength,int iTimeOut=-1,bool bCompatible=false) = 0;
	
};


struct IMCClient:public IKnown
{
public:

	/** ����һ���������ӿ�ָ��
	* @return ����NULL��ʾʧ�ܡ�
	**/
	virtual IPluginFilterInterface* FUNCTION_CALL_MODE NewFilter()=0;

	/** ����һ���������Խӿ�ָ��
	* @return ����NULL��ʾʧ�ܡ�
	**/
	virtual IPluginSubscribeParamInterface* FUNCTION_CALL_MODE NewSubscribeParam()=0;

	/** ��ʼ��һ�����ĻỰ��Ϣ����Ҫ���������Ự
	* @param lpCallback �ص��ӿ�
	* @param subscribeName ���������ֱ��뱣֤Ψһ��
	* @param uiTimeout ��ʱʱ��
	* @param bChild ֻ���¼���Ϣ���Ĳ���ſ������ó�true���������ȫ����false�����������ó�true
	* @return ���ض��Ľӿ�ʵ����һ���Ự�ӿڶ�Ӧһ���ص���
	**/
	virtual IPluginSubscribeInterface* FUNCTION_CALL_MODE NewSubscribe(IPluginSubCallbackInterface *lpCallback,char* subscribeName,int iTimeOut,bool bChild=false) =0;
	
	/** ����һ�������ӿ�ʵ��
	* @param msgCount ���ػ�����Ϣ�ĸ���
	* @param bResetNo �Ƿ��������
	* @return ���ط��ͽӿ�ʵ��������һ������������Ѿ�new�ˣ���ֱ�ӷ��ض�Ӧ��ָ��
	**/
	virtual IPluginPublishInterface* FUNCTION_CALL_MODE NewPublish(int msgCount,bool bResetNo = false) =0;
	

	/** ��ȡ����˵�����������Ϣ
	* @param byForce �Ƿ�ǿ�ƴӺ�̨��ȡ
	* @param uiTimeout ��ʱʱ��
	* @return �ɹ��ͷ�������������Ϣ
	*�����������Ҫ����release�ӿڽ����ͷš�
	*�����ֶΣ�TopicName TopicNo ReliableLevel IssuePriority MsgLifetime Stutas TickStrategy BusinessVerify Local
	* FilterFileld1 FilterFileld2 FilterFileld3 FilterFileld4 FilterFileld5 FilterFileld6 subcribeStr publishStr
	**/
	virtual IF2UnPacker* FUNCTION_CALL_MODE GetTopic(bool byForce,int iTimeOut)=0;

	/** ���ݴ���Ż�ȡ������Ϣ
	* @param nErrorNo �����
	* @return ���ض�Ӧ������Ϣ
	**/
	virtual char* FUNCTION_CALL_MODE GetErrorMsg(int nErrorNo)=0;

	/** �������һ��ִ�еĴ�����Ϣ
	* @return ���ض�Ӧ������Ϣ
	**/
	virtual char* FUNCTION_CALL_MODE GetMCLastError()=0;
};

#endif








