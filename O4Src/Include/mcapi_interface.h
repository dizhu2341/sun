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

/**
 * @example publish.cpp
 * @example fileupdate.cpp
 * @example subscribe.cpp
 */

/**
 * @mainpage MCAPI �����ĵ�
 * �ĵ�����
 *
 * -# MCAPI �ӿ��ĵ�
 * -# ���ġ��������ļ�����ʾ��
 * -# ����ʾ��
 *
 * 
 * [t2sdk]
 * - servers=192.168.51.246:8001
 *
 * - safe_level=none
 *
 * - license_no=HS-HUNDSUN001-FBASE2-0000-4ePWxzscBVtY9ZKdgDKhSyk2
 *
 * - mclog_write=0
 *
 * - mclog_dir=./
 *
 * [subcribe]
 * - subscribe_count=10     ;ÿ���Ự���������
 * 
 * - connect_count=10       ;�Ự����
 * 
 * - biz_name=test          ;ҵ������
 * 
 * - topic_name=file_update ;��������
 * 
 * - is_rebulid=false       ;�Ƿ���Ҫ��ȱ
 * 
 * - is_replace=false       ;�Ƿ񸲸���ǰ�Ķ��ģ������Ǿ���׷��
 * 
 * - send_interval=0        ;���ͼ��,��λ����
 * 
 * - filter_count=1         ;�����ֶεĸ�����ָ������Ĺ����м�����һ��������������
 *
 * - filter_name1=update_type   ; �����ֶ�1������
 *
 * - filter_value1=1            ;�����ֶ�1��ȡֵ
 *
 * - return_count=3             ;�����ֶεĸ���
 *
 * - return_filed1=update_type  ; �����ֶ�1������
 *
 * - return_filed2=account_no   ; �����ֶ�2������
 *
 * - return_filed2=name         ; �����ֶ�3������
 *
 * [publish]
 * - biz_name=xuxp          ;ҵ������
 * 
 * - topic_name=file_update ;��������
 *
 * [fileupdate]
 * - fileupdate=1           ; �ļ����¿���
 *
 * - topicName=fileupdate   ; �ļ�������������
 */
#ifndef __mcapi_interface__
#define __mcapi_interface__

#include <Include/glbdef.h>
#include <Include/plugin_interface.h>
#include <Include/connection_interface.h>
#include <Include/pack_interface.h>
#include <Include/esb_message_interface.h>
#include <os/config_env.h>
#include <map>
#include <os/inttypes.h>
#include <Include/tag_def.h>

using namespace std;

#define SIMPLIFIED_CHINESE      0   /**< ������Ϣ����:�������� */
#define ENGLISH                 1   /**< ������Ϣ����:Ӣ�� */

#define IDENTITY_NAME_LENGTH    32  /**< �ͻ������ֳ��� */
#define MAX_MACADDRESS_LEN	    18  /**< MAC ��ַ���� */
#define MAX_RAND_LEN	        4   /**< ��������� */

/** �ͻ���ʶ���� */
#define MAX_BIZNAME_LEN \
	IDENTITY_NAME_LENGTH+1+MAX_MACADDRESS_LEN+1+MAX_RAND_LEN+2

#define INIT_RECVQ_LEN 256          /**< ���ն��г�ʼ���� */
#define STEP_RECVQ_LEN 512          /**< ���ն�����չ���� */

#define MAX_FILTERFIELD_LEN 63      /**< �����ֶγ��� */

#define TYPE_SUBCRIBER      0       /**< �������� */
#define TYPE_PUBLISH        1       /**< �������� */
#define TYPE_SUB_PUB        2       /**< ���ĺͷ������� */

/** ����ɿ��ȼ� */
enum ReliableLevel
{
    LEVEL_DOBEST            = 0,    /**< ������Ϊ */
    LEVEL_DOBEST_BYSEQ      = 1,    /**< �������� */
    LEVEL_MEM               = 2,    /**< �ڴ� */
    LEVEL_FILE              = 3,    /**< �ļ� */
    LEVEL_SYSTEM            = 4     /**< ϵͳ */
};

/** @defgroup t2sdk t2sdk �ӿ�
 *  t2sdk �������
 *  @{
 */
#ifdef __cplusplus
extern "C"
{
#endif
   /**
    * ���һ�����ö���
    * @return ���ö���ָ��
    */
    CConfigInterface * FUNCTION_CALL_MODE NewConfig();

   /**
    * ���һ�����Ӷ���
    * @param lpConfig ���ö���ָ��
    * @return ���Ӷ���ָ��
    */
    CConnectionInterface * FUNCTION_CALL_MODE NewConnection(CConfigInterface *lpConfig);

   /**
    * ���һ��ESBMessage����
    * @param nCompressID �Ƿ�ѹ�� 1��ʾѹ��
    * @return ESBMessage����ָ��
    */
    IESBMessage *  FUNCTION_CALL_MODE NewESBMessage(int nCompressID = 1);

   /**
    * ��ȡt2sdk�汾��Ϣ
    */
    int FUNCTION_CALL_MODE GetVersionInfo();

   /**
    * ��ȡIF2Packer����
    * @param iVersion �汾��Ϣ��2.0����0x21
    * @return ����IF2Packerָ��
    */
    IF2Packer * FUNCTION_CALL_MODE NewPacker(int iVersion);

   /**
    * ��ȡIF2UnPacker����
    * @param lpBuffer �����������
    * @param iLen ���ݳ���
    * @return ����IF2UnPackerָ��
    */
    IF2UnPacker * FUNCTION_CALL_MODE NewUnPacker(void * lpBuffer, unsigned int iLen);
#ifdef __cplusplus
};
#endif
/** @} */

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

/**
 * @struct tagregisterrouteinfo
 * @brief ·����Ϣ
 */

/**
 * @typedef REGROUTE_INFO
 * @brief ·����Ϣ����
 */

/**
 * @typedef LPREGROUTE_INFO 
 * @brief ·����Ϣָ������
 */
typedef struct tagregisterrouteinfo
{
    char m_ospfName[ID_STR_LEN+1];              /**< ospf �� */
    char m_nbrName[IDENTITY_NAME_LENGTH+1];     /**< �ھ� �� */
    char m_svrName[SVRINSTANCE_NAME_LENGTH+1];  /**< ���� �� */
    char m_pluginId[PLUGIN_NAME_LENGTH+1];      /**< ��� �� */
    int  m_connectId;                           /**< ���Ӻ� */
    int  m_memberNo;                            /**< �Ự�� */

   /**
    * ���캯��
    */
    tagregisterrouteinfo()
    {
        memset(this, 0, sizeof(tagregisterrouteinfo));
    }
} REGROUTE_INFO,*LPREGROUTE_INFO;

/**
 * ע��Ļص������ӿڣ��������ձ��˵�������Ϣ
 * @param lpData ������Ϣ�Ķ�����ָ�룬һ������Ϣ��ҵ��������
 * @param nLength ���������ݵĳ���
 * @param lpSendInfo �����ߵ�·����Ϣ
 * @return ��
 */
typedef void (FUNCTION_CALL_MODE *TRecvFunctionEntry)(const void *lpData, int nLength,LPREGROUTE_INFO lpSendInfo);

/** �ļ����£����º�ΪAPI�����ļ����¹��������佻���Ĵ�����е��ֶ� */
#define PACKER_INT_FILE_LIST            "file_list"     /**< �ļ��б� */
#define PACKER_INT_FILE_ID              "file_id"       /**< �ļ�id */
#define PACKER_INT_FILE_SIZE            "file_size"     /**< �ļ���С */
#define PACKER_INT_TIME                 "time"          /**< �ļ�ʱ�� */
#define PACKER_STRING_FILE_NAME         "file_name"     /**< �ļ��� */
#define PACKER_STRING_FILE_PATH         "file_path"     /**< �ļ�·�� */
#define PACKER_STRING_LOCAL_PATH        "local_path"    /**< �����ļ�·�� */
#define PACKER_STRING_MD5_CODE          "md5_code"      /**< �ļ�md5ֵ */

/**
 * �ļ����£���������ļ�����filelist�Ļص�����
 * @param lpData ���ݵ�ַ
 * @param nLength ���ݳ���
 * @note 
 * -# ���������ļ��б�lpData�ǿ�               
 * -# ���ش����룺lpDataΪ�գ�nLength�������
 */
typedef void (FUNCTION_CALL_MODE *UiRecvFileListFuntion)(const void *lpData, int nLength);

/**
 * �ļ����£�����չʾ�������Ļص�����
 * @param iOneFileProcessBar �����ļ�����
 * @param iTotalProcessBar �������½���
 * @note 
 * -# ������iOneFileProcessBar��������1-100֮������֣�����ֵΪ�����룬100���ߴ������ʾ��ǰ�ļ����½���
 * -# ������iTotalProcessBar��������1-100֮������֣�-1��ʾ����100���ߴ������ʾ�������¹���
 */
typedef void (FUNCTION_CALL_MODE *UiShowProcessBarFuntion)(int iOneFileProcessBar, int iTotalProcessBar);

/** 
 * @defgroup MCAPI MCAPI �ӿ�
 * MCAPI ��������
 * @{
 */
#ifdef __cplusplus
extern "C" {
#endif

   /** 
    * API�ĳ�ʼ����������������֮ǰ�����ȵ�������������г�ʼ��
    * @param lpConnectionConfig t2sdk����������
    * @param selfName ��ǰ�ͻ��˵�����
    * @param iTimeOut ��ʱʱ�䣬��ȡ����ĳ�ʱʱ�䣬�������ӵĳ�ʱʱ����3��
    * @param initType ��ʼ�����ͣ���Ҫ��ʼ���ɷ����߻��Ƕ�����TYPE_SUBCRIBER/TYPE_PUBLISH/TYPE_SUB_PUB
    * @param nClearDays ��Ҫ�����������ǰ�Ķ����������Ϣ
    *   - С�ڵ���0��ʾ������
    *   - ����0��������ʱ��ͻ������ļ������ϲ�Ӧ�þ���������֮ǰ���ļ�
    * @param lang ������Ϣ�����ʽ��֧��Ӣ�ĺ��������֣�Ĭ��Ϊ����
    * @return ����0��ʾ�ɹ�����������ֵ�����ݴ���Ż�ȡ������Ϣ.
    */
    int FUNCTION_CALL_MODE MCInit(CConfigInterface* lpConnectionConfig,char* selfName, int iTimeOut, 
        int initType = TYPE_SUBCRIBER,int nClearDays=0, int lang=SIMPLIFIED_CHINESE);

   /**
    * ����һ���������ӿ�ָ��
    * @return ����NULL��ʾʧ��.
    */
    CFilterInterface* FUNCTION_CALL_MODE NewFilter();

   /**
    * ����һ���������Խӿ�ָ��
    * @return ����NULL��ʾʧ��.
    */
    CSubscribeParamInterface* FUNCTION_CALL_MODE NewSubscribeParam();

   /**
    * ��ʼ��һ�����ĻỰ��Ϣ����Ҫ���������Ự
    * @param lpCallback �ص��ӿ�
    * @param SubScribeName ���������֣��ඩ���ߵ����ֱ��벻һ������������ͬ.��󳤶�32���ֽ�
    * @param iTimeOut ��ʱʱ��
    * @param iInitRecvQLen ��ʼ�����ն��еĳ���
    * @param iStepRecvQLen ���ܶ��е���չ����
    * @return ���ض��Ľӿ�ʵ����һ���Ự�ӿڶ�Ӧһ���ص�.
    */
    CSubscribeInterface* FUNCTION_CALL_MODE NewSubscribe(CSubCallbackInterface *lpCallback,char* SubScribeName,int iTimeOut,
        int iInitRecvQLen=INIT_RECVQ_LEN,int iStepRecvQLen=STEP_RECVQ_LEN);
    
   /**
    * ����һ�������ӿ�ʵ��
    * @param msgCount ���ػ�����Ϣ�ĸ���
    * @param bResetNo �Ƿ��������
    * @return ���ط��ͽӿ�ʵ��������һ������������Ѿ�new�ˣ���ֱ�ӷ��ض�Ӧ��ָ��
    */
    CPublishInterface* FUNCTION_CALL_MODE NewPublish(int msgCount,bool bResetNo = false);
    
   /**
    * �����ļ����¹��ܣ�����������潻���Ļص�������������MCInit���ĳ�ʼ�������.
    * @param lpConnectionConfig �ײ��������͵�t2sdk������
    * @param fun1 ����ָ�룬���������ص���ʾ��Ҫ���µ��ļ��б�
    * @param fun2 ����ָ�룬���������ص���ʾ�ļ����µĽ���
    * @param updatedir ���µ���Ŀ¼
    * @return ����0��ʾ�ɹ�������ֵ��ʾʧ��
    */
    int FUNCTION_CALL_MODE FileUpdateInit(CConfigInterface* lpConnectionConfig, UiRecvFileListFuntion fun1, UiShowProcessBarFuntion fun2, const char* updatedir = NULL);

   /**
    * UI����ǰ��ص���ʾ���ļ��б����û�ѡ����·���Ҫ���µ��ļ��б�
    * @param lpData �����ƴ������
    * @param nLength ���������ݵĳ���
    * @return ����0��ʾ�ɹ�������ֵ��ʾʧ��.
    */
    int FUNCTION_CALL_MODE FileUpdateBegin(const void *lpData, int nLength);

   /**
    * ����ȡ�����ڸ����еĸ��¶���
    * @return ����0��ʾ�ɹ�������ֵ��ʾʧ��
    */
    int FUNCTION_CALL_MODE FileUpdateCancel();


   /**
    * ��ȡ����˵�����������Ϣ
    * @param byForce �Ƿ�ǿ�ƴӺ�̨��ȡ
    * @param iTimeOut ��ʱʱ��
    * @return �ɹ��ͷ�������������Ϣ
    * @note �����������Ҫ����release�ӿڽ����ͷ�.
    * @note packer�����ֶ�
    * - TopicName
    * - TopicNo
    * - ReliableLevel
    * - IssuePriority
    * - MsgLifetime
    * - Stutas 
    * - TickStrategy 
    * - BusinessVerify
    * - Local
    * - FilterField1 
    * - FilterField2 
    * - FilterField3 
    * - FilterField4 
    * - FilterField5 
    * - FilterField6
    * - SubscribeStr 
    * - PublishStr
    */
    IF2UnPacker* FUNCTION_CALL_MODE GetTopic(bool byForce,int iTimeOut);

   /**
    * ����ͷ����ж��ĺͷ����ӿ�
    * @return ����0��ʾ�ɹ�����������ֵ�����ݴ���Ż�ȡ������Ϣ.
    */
    int FUNCTION_CALL_MODE Destroy();


   /**
    * ���ݴ���Ż�ȡ������Ϣ
    * @param nErrorNo �����
    * @return ���ض�Ӧ������Ϣ
    */
    char* FUNCTION_CALL_MODE GetErrorMsg(int nErrorNo);

   /** 
    * �������һ��ִ�еĴ�����Ϣ
    * @return ���ض�Ӧ������Ϣ
    */
    char* FUNCTION_CALL_MODE GetMCLastError();
  
#ifdef __cplusplus
}
#endif
/** @} */

#endif


