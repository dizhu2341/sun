/*******************************************************
  Դ��������:
  �������Ȩ:�������ӹɷ����޹�˾
  ϵͳ����:  ��Ϣ����2.0
  ģ������:  ���API��
  ����˵��:  ���API�ӿ�˵��
  ��    ��:  wushuai
  ��������:  20130621
  ��    ע: 
  20130913 majc ��ӷ��ش�����
  20130917 majc ���ȡ�����Ľӿ�CancelSubscribeTopicEx
  20140605 majc ���Ӷ������ݽṹ
*********************************************************/


#ifndef __MC_COMMONAPI_INTERFACE_H__
#define __MC_COMMONAPI_INTERFACE_H__

#if defined(_WIN32)&& _MSC_VER < 1300
#pragma warning(disable: 4786)				//����ڱ�������STLͷ�ļ�ǰ
#pragma warning(disable: 4710)				//����ڱ�������STLͷ�ļ�ǰ
#endif

#ifdef _WIN32
typedef unsigned int		uint32;
#else
#include <sys/types.h>
#if defined(__linux__)
#include <stdint.h>
#endif
typedef uint32_t			uint32;
#endif

#include <Include/plugin_interface.h>
#include <string.h>
#include <Include/service_interface.h>
#include <Include/mcapi_plugin_interface.h>

#define SID_MC_BIZCOMPONENT_SERVICE   "mc_bizcomponent"
#define SID_MC_BIZCOMPONENT_API "mc_bizcomponent_api"

#define MAX_FILTER_FIELDS_BIZ 16
#define MAX_FILTERFIELD_LEN_BIZ 63

//20140605 majc ���Ӷ������ݽṹ
typedef struct tagSubRecvDataForProc
{
	char* lpFilterData;     /**< �����ֶε�����ͷָ�룬�ý������� */
	int iFilterDataLen;     /**< �����ֶε����ݳ��� */
	char* lpAppData;        /**< �������ݵ�����ͷָ�� */
	int iAppDataLen;        /**< �������ݵĳ��� */
	char szTopicName[260];  /**< �������� */
	
   /**
    * tagSubscribeRecvData ���캯��
    */
	tagSubRecvDataForProc()
	{
		Clear();
	}
	void Clear()
	{
		memset(this,0,sizeof(tagSubRecvDataForProc));
	}
}SUB_RECVDATA_FOR_PROC, *LPSUB_RECVDATA_FOR_PROC;

struct IMCBizComponentApi:public IKnown
{
public:
/*----------------------------------------------------����----------------------------------------------*/
	/** ����һ���������ӿ�ָ��
	* @return ����NULL��ʾʧ�ܡ�
	**/
	virtual IPluginFilterInterface* FUNCTION_CALL_MODE NewFilter()=0;

	/** ����һ���������Խӿ�ָ��
	* @return ����NULL��ʾʧ�ܡ�
	**/
	virtual IPluginSubscribeParamInterface* FUNCTION_CALL_MODE NewSubscribeParam()=0;

/*-----------------------------------------------����----------------------------------------------------*/

	/**��������
	* @param lpSubscribeParam ���涨��Ķ��Ĳ����ṹ
	* @param uiTimeout ��ʱʱ��
	* @param lpBizPack ҵ��У����Ҫ���ӵ�ҵ���ֶ��Լ�ֵ��û�о͸��ݹ���������Ϊҵ��У���ֶ�
	* @return ����ֵ����0����ʾ��ǰ���ĳɹ��Ķ��ı�ʶ������Ҫ��ס�����ʶ�Ͷ�����֮���ӳ���ϵ�������ʶ��Ҫ����ȡ�����ĺͽ�����Ϣ�Ļص�����.
	*		  ��������ֵ�����ݴ���Ż�ȡ������Ϣ.
	**/
	virtual int FUNCTION_CALL_MODE SubscribeTopic(IPluginSubscribeParamInterface* lpSubscribeParamInter ,unsigned int uiTimeout,IF2Packer* lpBizPack=NULL) = 0;

	/**ȡ����������
	* @param topicName �������֣���֪�����־ʹ�NULL
	* @param lpFilter ��Ӧ�Ĺ�������
	* @param uiTimeout ��ʱʱ��
	* @return ����0��ʾȡ�����ĳɹ�����������ֵ�����ݴ���Ż�ȡ������Ϣ��
	**/
	virtual int FUNCTION_CALL_MODE CancelSubscribeTopic(int index) = 0;

/*-----------------------------------------------------------����---------------------------------------------/
	/**ҵ������ʽ�����ݷ����ӿ�
	* @param topicName �������֣���֪�����־ʹ�NULL
	* @param topicNo �����ţ���֪����žʹ�0
	* @param lpPacker ���������
	* @param iTimeOut ��ʱʱ��
	* @param bCompatible ����1.0�ı�־��ֻ�м��ݲ��������ʱ�����true����������false��
	* @return ����0��ʾ�ɹ�����������ֵ�����ݴ���Ż�ȡ������Ϣ��
	**/
	virtual int FUNCTION_CALL_MODE PubMsgByPacker(char* topicName,IF2UnPacker* lpUnPacker,int iTimeOut=-1,bool bCompatible=false) = 0;
	
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
	virtual int FUNCTION_CALL_MODE PubMsg(char* topicName, IPluginFilterInterface* lpFilterInter, const void *lpData, int nLength,int iTimeOut=-1,bool bCompatible=false) = 0;

	/** �������һ��ִ�еĴ�����Ϣ
	* @return ���ض�Ӧ������Ϣ
	**/
	virtual char* FUNCTION_CALL_MODE GetMCLastError() = 0;
	
	
	//20130917 majc ���ȡ�����Ľӿ�
		/**
    * ȡ����������
    * @param topicName ��������
    * @param lpFilterInterface ��Ӧ�Ĺ�������
    * @return ����0��ʾȡ�����ĳɹ�����������ֵ�����ݴ���Ż�ȡ������Ϣ.
    */
  virtual int FUNCTION_CALL_MODE CancelSubscribeTopicEx(char* topicName,IPluginFilterInterface* lpFilterInterface) = 0;

  //20130913 majc ��ӷ��ش�����
	/** ���ݴ���Ż�ȡ������Ϣ
	* @param nErrorNo �����
	* @return ���ض�Ӧ������Ϣ
	**/
	virtual char* FUNCTION_CALL_MODE GetErrorMsg(int nErrorNo) = 0;
};

#endif
