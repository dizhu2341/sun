///�ֲ�ʽ��־����ӿ�ID���弰���׼��������
/*********************************************************************************************
  Դ��������:cloud_dlog_interface.h
  �������Ȩ:�������ӹɷ����޹�˾
  ϵͳ����:  
  ģ������:
  ����˵��: 
  ��    ��:  �з����� huxb
  ��������:  20141223
  ��    ע:  
  20160603 huxb ����AddCloudLog�����
  20160826 huxb �Ƿ�д�����ļ������þ�����ͬʱ�޸�Ϊ�첽��¼��־
  20161117 huxb ������־�ӿ�AddLogByArgsEx
*********************************************************************************************/

#ifndef __Cloud_Dlog__Interface_H__
#define __Cloud_Dlog__Interface_H__
#include <Include/esb_message_interface.h>
#include <Include/plugin_interface.h>
#include <os/inttypes.h>

#define SID_CLOUD_DLOG "cloud.dlog"


///20160603 huxb ��������
#define KAFKA_ERROR_BASE 200
#define KAFKA_ERROR_UNKNOWN ((KAFKA_ERROR_BASE) + 1)
#define KAFKA_ERROR_NEW_TOPIC ((KAFKA_ERROR_BASE) + 10)
#define KAFKA_ERROR_QUEUE_FULL ((KAFKA_ERROR_BASE) + 11)
#define KAFKA_ERROR_MSG_SIZE_TOO_LARGE ((KAFKA_ERROR_BASE) + 12)
#define KAFKA_ERROR_UNKNOWN_PARTITION ((KAFKA_ERROR_BASE) + 13)
#define KAFKA_ERROR_UNKNOWN_TOPIC ((KAFKA_ERROR_BASE) + 14)
#define KAFKA_ERROR_WAIT_TIMEOUT ((KAFKA_ERROR_BASE) + 15)
#define KAFKA_ERROR_SYNC_FAILED ((KAFKA_ERROR_BASE) + 16)

///��־����
enum DLOG_LEVEL 
{
    CLOUD_LOG_DEBUG = 0,

    CLOUD_LOG_EVENT = 1,

    CLOUD_LOG_WARNING = 2,

    CLOUD_LOG_ERRER = 3,

    CLOUD_LOG_CRUSHED = 4,

    CLOUD_LOG_IMPORTANTEVENT = 5,

    CLOUD_LOG_UNKNOWN = 6
};

struct SCloudDLogInfo
{
    /// ��־ȫ��Ψһ��ʶ����־���������ֵ������
    int iLogID;

    /// ��־�Ľ����̶�
    DLOG_LEVEL iLevel;

    /// ��Ҫ��¼��־��Դģ��
    char * szSrcModule;

	///������
	char * szTopic;

	///20161117 huxb Ĭ�ϼ���
	DLOG_LEVEL iDefLevel;
};

struct SCloudDlog{
    const char * szAuthID;
    const char * szSubSysID;
    const char * szUserToken;
    const char * szCompID;

    SCloudDlog()
    {
        szAuthID = NULL;
        szSubSysID = NULL;
        szUserToken = NULL;
        szCompID = NULL;
    }
};

enum DLogType{
	DLOG_TYPE_NONE = 0,
	DLOG_TYPE_BIZ = 1,
	DLOG_TYPE_LOG = 2,
	DLOG_TYPE_BIZX = 3,
	DLOG_TYPE_FILTER_MESSAGE = 4,
	DLOG_TYPE_FILTER_PLUGIN = 5
};

class ICloud_DLogArgs : public IKnown{
public:
	virtual int Reset() = 0;

	virtual int AddMessage(const void * lpData, int iLen) = 0;
	///�����־��Ϣ
	virtual int AddBody(const char * szBodyMsg) = 0;
	virtual int AddTimeStamp(const char * szTimestamp) = 0;
	virtual int AddType(DLogType iType) = 0;

	virtual int AddItem(const char * szField, const char * szValue, int uLen = 0, bool IsRaw = false) = 0;
	virtual int GetItemCount() = 0;
	virtual const char * GetItemName(int index) = 0;
	virtual const char * GetItemInfo(int index, int &iLen, bool &isRaw) = 0;

	virtual const void * GetMessage(int &iLen) = 0;
	virtual const char * GetBody() = 0;
	virtual const char * GetTimeStamp() = 0;
	virtual int GetType() = 0;

	//20161117 huxb �������á���ȡESBMSG�ӿ�
	virtual int SetInfoByESBMsg(IESBMessage * lpESBMsg) = 0;
	virtual void SetFunctionID(int iFuncID) = 0;
	virtual void SetGlobalNo(const char * szGlobalNo) = 0;
	virtual int GetFunctionID() = 0;
	virtual const char * GetGlobalNo() = 0;
};

class ICloud_Dlog : public IKnown{
public:
    /***��¼��־���ýӿڻ������־��Ϣ��װΪJSon��
    *@param iLogID ��ֵΪdlog.xml����־��Ϣ������
    *@param lpLog ҵ����־��Ϣ
    *@param szMsg ��־��Ϣ
    *@param bWriteFile �Ƿ��¼������־
    *@return 0 �ɹ������� ʧ��
	* ����KAFKA_ERROR_QUEUE_FULL��ʾkafka�����˶�����
    */
    virtual int FUNCTION_CALL_MODE AddCloudLog(int iLogID, SCloudDlog * lpLog, const char * szMsg, int bWriteFile = 1) = 0;

    /***��¼����־
    *@param lpData ��������־��Ϣ
    *@param uLen ��־����
    *@param bWriteFile �Ƿ��¼������־
    *@return 0 �ɹ������� ʧ��
    */
    virtual int FUNCTION_CALL_MODE AddStreamCloudLog(const void * lpData, unsigned int uLen, int bWriteFile = 1) = 0;

	///20160826 huxb �Ƿ�д�����ļ������þ�����ͬʱ�޸�Ϊ�첽��¼��־
	/***��¼��־���ýӿڻ������־��Ϣ��װΪJSon��
    *@param iLogID ��ֵΪdlog.xml����־��Ϣ������
    *@param lpLog ҵ����־��Ϣ
    *@param szMsg ��־��Ϣ
    *@return 0 �ɹ������� ʧ��
	* ����KAFKA_ERROR_QUEUE_FULL��ʾkafka�����˶�����
    */
    virtual int FUNCTION_CALL_MODE AddCloudLogEx(int iLogID, SCloudDlog * lpLog, const char * szMsg) = 0;
	
	///20161017 huxb ��ȡ��־�����ӿ�
	/***��¼��־���ýӿڻ������־��Ϣ��װΪJSon��
    *@return ��־�����ӿ�
    */
	virtual ICloud_DLogArgs * FUNCTION_CALL_MODE GetDLogArgs() = 0;

	///20161017 huxb ������־�ӿ�
	/***��¼��־���ýӿڻ������־��Ϣ��װΪJSon��
    *@param szTopic ����
    *@param lpArgs ��־����
    *@return 0 �ɹ������� ʧ��
	* ����KAFKA_ERROR_QUEUE_FULL��ʾkafka�����˶�����
    */
	virtual int FUNCTION_CALL_MODE AddLogByArgs(const char * szTopic, ICloud_DLogArgs * lpArgs) = 0;

	///20161117 huxb ������־�ӿ�
	/***��¼��־���ýӿ�֧���첽��¼�����ļ�������װΪJSon������kafka��־������
    *@param iLogID ��ֵΪdlog.xml����־��Ϣ������
	*@param iLevel ��־����
    *@param lpArgs ��־����
    *@return 0 �ɹ������� ʧ��
	* ����KAFKA_ERROR_QUEUE_FULL��ʾkafka�����˶�����
    */
	virtual int FUNCTION_CALL_MODE AddLogByArgsEx(int iLogID, int iLevel, ICloud_DLogArgs * lpDlogArgs) = 0;
};

#endif       /*end def __Cloud_Dlog__Interface_H__*/
