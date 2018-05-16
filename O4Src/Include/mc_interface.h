/** @file mcapi_interface.h
 *  @brief MC2.0 SDK�����ӿ��ļ�
 *  @author      xuxp
 *  @date        20120809
 *  @copyright   �������ӹɷ����޹�˾
 *  @version     1.0.0.0
 *
 *  @par �޸ļ�¼ <����> <�汾> <�޸���Ա> <�޸�����>
 *  -# 2013-02-04 1.0.0.0 xuxp ������ʼ�汾
 */
#ifndef _MC_INTERFACE_H_
#define _MC_INTERFACE_H_
#if defined(_WIN32)&& _MSC_VER < 1300
#pragma warning(disable: 4786)				//����ڱ�������STLͷ�ļ�ǰ
#pragma warning(disable: 4710)				//����ڱ�������STLͷ�ļ�ǰ
#endif
#include <Include/plugin_interface.h>
#include <string.h>

#ifdef _WIN32
typedef unsigned int		uint32;
#else
#include <sys/types.h>
#if defined(__linux__)
#include <stdint.h>
#endif
typedef uint32_t			uint32;
#endif

#define IDENTITY_NAME_LENGTH    32  /**< �ͻ������ֳ��� */
#define MAX_MACADDRESS_LEN	    18  /**< MAC ��ַ���� */
#define MAX_RAND_LEN	        4   /**< ��������� */

/** �ͻ���ʶ���� */
#define MAX_BIZNAME_LEN \
	IDENTITY_NAME_LENGTH+1+MAX_MACADDRESS_LEN+1+MAX_RAND_LEN+2

#define INIT_RECVQ_LEN 256          /**< ���ն��г�ʼ���� */
#define STEP_RECVQ_LEN 512          /**< ���ն�����չ���� */
#define SIMPLIFIED_CHINESE      0   /**< ������Ϣ����:�������� */
#define ENGLISH                 1   /**< ������Ϣ����:Ӣ�� */
#define MAX_FILTERFIELD_LEN 63      /**< �����ֶγ��� */

/** ����ɿ��ȼ� */
enum ReliableLevel
{
    LEVEL_DOBEST            = 0,    /**< ������Ϊ */
    LEVEL_DOBEST_BYSEQ      = 1,    /**< �������� */
    LEVEL_MEM               = 2,    /**< �ڴ� */
    LEVEL_FILE              = 3,    /**< �ļ� */
    LEVEL_SYSTEM            = 4     /**< ϵͳ */
};

/** 
 * �������ӿ�
 */
class CFilterInterface:public IKnown
{
public:
   /**
    * �����±��ȡ��������������
    * @param index ��Ӧ�Ĺ��������±�
    * @return ���ض�Ӧ���±�������������֣����򷵻�NULL.
    */
    virtual char* FUNCTION_CALL_MODE GetFilterNameByIndex(int index) = 0;

   /**
    * �����±��ȡ����������ֵ
    * @param index ��Ӧ�Ĺ��������±�
    * @return ���ض�Ӧ���±����������ֵ�����򷵻�NULL.
    */
    virtual char* FUNCTION_CALL_MODE GetFilterValueByIndex(int index)= 0;

   /**
    * ���ݹ������������ֻ�ȡ����������ֵ
    * @param fileName ��Ӧ�Ĺ�����������
    * @return ���ض�Ӧ�Ĺ����������ֵ�����ֵ�����򷵻�NULL.
    */
    virtual char* FUNCTION_CALL_MODE GetFilterValue(char*  fileName)= 0;

   /**
    * ��ȡ���������ĸ���
    * @return ���ض�Ӧ���������ĸ�����û�з���0
    */
    virtual int   FUNCTION_CALL_MODE GetCount() = 0;

   /**
    * ���ù������������ݹ����������ֺ�ֵ
    * @param filterName ��Ӧ�Ĺ�����������
    * @param filterValue ��Ӧ�Ĺ����������ֵ�ֵ
    */
    virtual void FUNCTION_CALL_MODE  SetFilter(char* filterName,char* filterValue) =0;
};

/**
 * ���Ĳ�����ӿ�
 */
class CSubscribeParamInterface:public IKnown
{
public:

   /**
    * ������������
    * @param szName ��Ӧ����������
    */
    virtual void FUNCTION_CALL_MODE  SetTopicName(char* szName) =0;

   /**
    * ���ø�������
    * @param lpData �������ݵ��׵�ַ
    * @param iLen �������ݵĳ���
    */
    virtual void FUNCTION_CALL_MODE  SetAppData(void* lpData,int iLen)=0;
    
   /**
    * ��ӹ�������
    * @param filterName ��������������
    * @param filterValue ����������ֵ
    */
    virtual void FUNCTION_CALL_MODE  SetFilter(char* filterName,char* filterValue)=0;

   /**
    * ��ӷ����ֶ�
    * @param filedName ��Ҫ��ӵķ����ֶ�
    */
    virtual void FUNCTION_CALL_MODE  SetReturnFiled(char* filedName)=0;

   /**
    * �����Ƿ�ȱ��־
    * @param bFromNow true��ʾ��Ҫ֮ǰ�����ݣ�Ҳ���ǲ�ȱ��false��ʾ����Ҫ��ȱ
    */
    virtual void FUNCTION_CALL_MODE  SetFromNow(bool bFromNow)=0;

   /**
    * ���ø��Ƕ��ı�־
    * @param bReplace true��ʾ���Ƕ��ģ�ȡ��֮ǰ�����ж��ģ�ֻ������ǰ�Ķ��ģ�false��ʾ׷�Ӷ���
    */
    virtual void FUNCTION_CALL_MODE  SetReplace(bool bReplace)=0;

   /**
    * ���÷��ͼ��
    * @param nSendInterval ��λ����
    */
    virtual void FUNCTION_CALL_MODE  SetSendInterval(int nSendInterval)=0;

   /**
    * ��ȡ��������
    * @return ��������������Ϣ
    */
    virtual char* FUNCTION_CALL_MODE  GetTopicName() =0;

   /**
    * ��ȡ��������
    * @param iLen ���Σ���ʾ�������ݵĳ���
    * @return ���ظ��������׵�ַ��û�з���NULL
    */
    virtual void* FUNCTION_CALL_MODE  GetAppData(int *iLen) =0;

   /**
    * ��ȡ��Ӧ�Ĺ����ֶε�����
    * @param index ��Ӧ�Ĺ��������±�
    * @return ���ض�Ӧ���±�������������֣����򷵻�NULL.
    */
    virtual char* FUNCTION_CALL_MODE  GetFilterNameByIndex(int index) = 0;

   /**
    * �����±��ȡ����������ֵ
    * @param index ��Ӧ�Ĺ��������±�
    * @return ���ض�Ӧ���±����������ֵ�����򷵻�NULL.
    */
    virtual char* FUNCTION_CALL_MODE  GetFilterValueByIndex(int index)= 0;

   /**
    * ���ݹ������������ֻ�ȡ����������ֵ
    * @param fileName ��Ӧ�Ĺ�����������
    * @return ���ض�Ӧ�Ĺ����������ֵ�����ֵ�����򷵻�NULL.
    */
    virtual char* FUNCTION_CALL_MODE  GetFilterValue(char*  fileName)= 0;

   /**
    * ��ȡ���������ĸ���
    * @return ���ض�Ӧ���������ĸ�����û�з���0
    */
    virtual int   FUNCTION_CALL_MODE  GetFilterCount() = 0;

   /**
    * ��ȡ�����ֶ�
    * @return ���ض�Ӧ�ķ����ֶ���Ϣ
    */
    virtual char* FUNCTION_CALL_MODE  GetReturnFiled()=0;

   /**
    * ��ȡ�Ƿ�ȱ�ı�־
    * @return ���ض�Ӧ�Ĳ�ȱ��־
    */
    virtual bool  FUNCTION_CALL_MODE  GetFromNow()=0 ;

   /**
    * ��ȡ�Ƿ񸲸Ƕ��ĵı�־
    * @return ���ض�Ӧ�ĸ��Ƕ��ı�־
    */
    virtual bool  FUNCTION_CALL_MODE  GetReplace() =0;

   /**
    * ��ȡ��Ӧ�ķ���Ƶ��
    * @return ���ض�Ӧ�ķ��ͼ��
    */
    virtual int   FUNCTION_CALL_MODE  GetSendInterval()=0;
};

class CSubscribeInterface;

/**
 * @brief ���Ļص��ӿڷ��ص����ݶ��壬���˶�����Ҫ��ҵ����֮�⣬����Ҫ���ص�����
 */
typedef struct tagSubscribeRecvData
{
	char* lpFilterData;     /**< �����ֶε�����ͷָ�룬�ý������� */
	int iFilterDataLen;     /**< �����ֶε����ݳ��� */
	char* lpAppData;        /**< �������ݵ�����ͷָ�� */
	int iAppDataLen;        /**< �������ݵĳ��� */
	char szTopicName[260];  /**< �������� */
	
   /**
    * tagSubscribeRecvData ���캯��
    */
	tagSubscribeRecvData()
	{
		memset(this,0,sizeof(tagSubscribeRecvData));
	}
}SUBSCRIBE_RECVDATA, *LPSUBSCRIBE_RECVDATA;

/**
 * ���Ļص��ӿڣ��ϲ�Ӧ��ͨ������ӿڣ��������ƹ�������Ϣ
 */
class CSubCallbackInterface: public IKnown
{
public:

   /**
    * �յ�������Ϣ�Ļص�
    * @param lpSub �ص��Ķ���ָ��
    * @param subscribeIndex ��Ϣ��Ӧ�Ķ��ı�ʶ�������ʶ������SubscribeTopic�����ķ���
    * @param lpData ������Ϣ�Ķ�����ָ�룬һ������Ϣ��ҵ����������
    * @param nLength ���������ݵĳ���
	* @param lpRecvData ������Ϣ�������ֶη��أ���Ҫ�����˸������ݣ�������Ϣ���������֣���ϸ�ο�ǰ��ṹ�嶨��
    * @return ��
    */
    virtual void FUNCTION_CALL_MODE OnReceived(CSubscribeInterface *lpSub,int subscribeIndex, const void *lpData, int nLength,LPSUBSCRIBE_RECVDATA lpRecvData) = 0;

   /**
    * �յ��޳����������Ϣ�ص���һ����ӵ�����˲��Ե������»�ص�����ӿ�,����ص����治��Ҫȡ�����ģ��ײ��Ѿ�ȡ��������ģ�ֻ��һ��֪ͨ�ӿ�
    * @param lpSub �ص��Ķ���ָ��
    * @param subscribeIndex ��Ϣ��Ӧ�Ķ��ı�ʶ�������ʶ������SubscribeTopic�����ķ���
    * @param TickMsgInfo ���˵Ĵ�����Ϣ����Ҫ�ǰ��������ظ��Ķ�����λ����Ϣ
    * @return ��
    */
    virtual void FUNCTION_CALL_MODE OnRecvTickMsg(CSubscribeInterface *lpSub,int subscribeIndex,const char* TickMsgInfo) = 0;
};


/**
 * ���ĽӿڵĶ���
 */
class CSubscribeInterface: public IKnown
{
public:

   /**
    * ��������
    * @param lpSubscribeParamInter ���涨��Ķ��Ĳ����ṹ
    * @param uiTimeout ��ʱʱ��
    * @param lppBizUnPack ҵ��У��ʱ��ʧ�ܷ��ص�ҵ�������Ϣ��������ĳɹ�û�з��أ������������Ҫ�������Release�ͷ�
                          �������ҵ��У��Ĵ�����Ϣ��д�����£�
                          IF2UnPacker* lpBizUnPack =NULL;
                          SubscribeTopic(...,&lpBizUnPack);
                          �����ݷ���ֵ�������ʧ�ܵľ��ж� lpBizUnPack �ǲ���NULL.
                          ��������Ϣ��ȡ��֮��,�ͷ�
                          lpBizUnPack->Release();
    * @param lpBizPack ҵ��У����Ҫ���ӵ�ҵ���ֶ��Լ�ֵ��û�о͸��ݹ���������Ϊҵ��У���ֶ�
    * @return ����ֵ����0����ʾ��ǰ���ĳɹ��Ķ��ı�ʶ������Ҫ��ס�����ʶ�Ͷ�����֮���ӳ���ϵ�������ʶ��Ҫ����ȡ�����ĺͽ�����Ϣ�Ļص�����.
	*		  ��������ֵ�����ݴ���Ż�ȡ������Ϣ.
    */
    virtual int FUNCTION_CALL_MODE SubscribeTopic(CSubscribeParamInterface* lpSubscribeParamInter ,unsigned int uiTimeout,IF2UnPacker** lppBizUnPack=NULL,IF2Packer* lpBizPack=NULL) = 0;

   /**
    * ȡ����������
    * @param subscribeIndex ��Ϣ��Ӧ�Ķ��ı�ʶ�������ʶ������SubscribeTopic�����ķ���
    * @return ����0��ʾȡ�����ĳɹ�����������ֵ�����ݴ���Ż�ȡ������Ϣ.
    */
    virtual int FUNCTION_CALL_MODE CancelSubscribeTopic(int subscribeIndex) = 0;


	/**
    * ȡ����������
    * @param topicName ��������
    * @param lpFilterInterface ��Ӧ�Ĺ�������
    * @return ����0��ʾȡ�����ĳɹ�����������ֵ�����ݴ���Ż�ȡ������Ϣ.
    */
    virtual int FUNCTION_CALL_MODE CancelSubscribeTopicEx(char* topicName,CFilterInterface* lpFilterInterface) = 0;



   /**
    * ��ȡ��ǰ���Ľӿ��Ѿ����ĵ����������Լ�����������Ϣ
    * @param lpPack ���洫��Ĵ����
    * @note packer�����ֶ�
        - SubcribeIndex
        - IsBornTopic
        - TopicName
        - TopicNo
        - FilterRaw
        - Appdata
        - SendInterval
        - ReturnFileds
        - isReplace
        - isFromNow
        - Stutas
        - QueueCount
    */
    virtual void FUNCTION_CALL_MODE GetSubcribeTopic(IF2Packer* lpPack)=0;

   /**
    * ȡ��������ַ
    * @param lpPort ����ķ������˿ڣ�����ΪNULL
    * @return ���ط�������ַ
    */
    virtual const char * FUNCTION_CALL_MODE GetServerAddress(int *lpPort) = 0;
};

/**
 * �����ӿ�
 */
class CPublishInterface: public IKnown
{
public:

   /**
    * ҵ������ʽ�����ݷ����ӿ�
    * @param topicName �������֣���֪�����־ʹ�NULL
    * @param lpUnPacker ���������
    * @param iTimeOut ��ʱʱ��
    * @param lppBizUnPack ҵ��У��ʱ��ʧ�ܷ��ص�ҵ�������Ϣ����������ɹ�û�з��أ������������Ҫ�������Release�ͷ�
                            �������ҵ��У��Ĵ�����Ϣ��д�����£�
                            IF2UnPacker* lpBizUnPack =NULL;
                            PubMsgByPacker(...,&lpBizUnPack);
                            �����ݷ���ֵ�������ʧ�ܵľ��ж� lpBizUnPack �ǲ���NULL.
                            ��������Ϣ��ȡ��֮��,�ͷ�
                            lpBizUnPack->Release();
    * @param bAddTimeStamp �Ƿ����ʱ�������ϵ������ܲ���
    * @return ����0��ʾ�ɹ�����������ֵ�����ݴ���Ż�ȡ������Ϣ.
    */
    virtual int FUNCTION_CALL_MODE PubMsgByPacker(char* topicName ,IF2UnPacker* lpUnPacker,int iTimeOut=-1,
        IF2UnPacker** lppBizUnPack=NULL,bool bAddTimeStamp=false) = 0;
    
   /**
    * ��ҵ������ʽ�����ݷ����ӿڣ�һ������Ƹ�ʽ���ķ���
    * @param topicName �������֣���֪�����־ʹ�NULL
    * @param lpFilterInterface ������������Ҫ�ϲ��Լ�ָ��������Ĭ��û�й�������
    * @param lpData ���������
    * @param nLength ���ݳ���
    * @param iTimeOut ��ʱʱ��
    * @param lppBizUnPack ҵ��У��ʱ��ʧ�ܷ��ص�ҵ�������Ϣ����������ɹ�û�з��أ������������Ҫ�������Release�ͷ�
                            �������ҵ��У��Ĵ�����Ϣ��д�����£�
                            IF2UnPacker* lpBizUnPack =NULL;
                            PubMsgByPacker(...,&lpBizUnPack);
                            �����ݷ���ֵ�������ʧ�ܵľ��ж� lpBizUnPack �ǲ���NULL.
                            ��������Ϣ��ȡ��֮��,�ͷ�
                            lpBizUnPack->Release();
    * @param bAddTimeStamp �Ƿ����ʱ�������ϵ������ܲ���
    * @return ����0��ʾ�ɹ�����������ֵ�����ݴ���Ż�ȡ������Ϣ.
    */
    virtual int FUNCTION_CALL_MODE PubMsg(char* topicName, CFilterInterface* lpFilterInterface, const void *lpData, int nLength,int iTimeOut=-1,
        IF2UnPacker** lppBizUnPack=NULL,bool bAddTimeStamp=false) = 0;

   /**
    * ���ص�ǰ����ķ������
    * @param topicName ��������
    * @return ����0��ʾû�ж�Ӧ�����⣬��������ֵ��ʾ�ɹ�
    */
    virtual uint32 FUNCTION_CALL_MODE GetMsgNoByTopicName(char* topicName)=0;

   /**
    * ȡ��������ַ
    * @param lpPort ����ķ������˿ڣ�����ΪNULL
    * @return ���ط�������ַ
    */
    virtual const char * FUNCTION_CALL_MODE GetServerAddress(int *lpPort) = 0;
};


#endif


