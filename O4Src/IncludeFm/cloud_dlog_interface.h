///分布式日志插件接口ID定义及其标准引出函数
/*********************************************************************************************
  源程序名称:cloud_dlog_interface.h
  软件著作权:恒生电子股份有限公司
  系统名称:  
  模块名称:
  功能说明: 
  作    者:  研发中心 huxb
  开发日期:  20141223
  备    注:  
  20160603 huxb 定义AddCloudLog错误号
  20160826 huxb 是否写本地文件由配置决定，同时修改为异步记录日志
  20161117 huxb 新增日志接口AddLogByArgsEx
*********************************************************************************************/

#ifndef __Cloud_Dlog__Interface_H__
#define __Cloud_Dlog__Interface_H__
#include <Include/esb_message_interface.h>
#include <Include/plugin_interface.h>
#include <os/inttypes.h>

#define SID_CLOUD_DLOG "cloud.dlog"


///20160603 huxb 定义错误号
#define KAFKA_ERROR_BASE 200
#define KAFKA_ERROR_UNKNOWN ((KAFKA_ERROR_BASE) + 1)
#define KAFKA_ERROR_NEW_TOPIC ((KAFKA_ERROR_BASE) + 10)
#define KAFKA_ERROR_QUEUE_FULL ((KAFKA_ERROR_BASE) + 11)
#define KAFKA_ERROR_MSG_SIZE_TOO_LARGE ((KAFKA_ERROR_BASE) + 12)
#define KAFKA_ERROR_UNKNOWN_PARTITION ((KAFKA_ERROR_BASE) + 13)
#define KAFKA_ERROR_UNKNOWN_TOPIC ((KAFKA_ERROR_BASE) + 14)
#define KAFKA_ERROR_WAIT_TIMEOUT ((KAFKA_ERROR_BASE) + 15)
#define KAFKA_ERROR_SYNC_FAILED ((KAFKA_ERROR_BASE) + 16)

///日志级别
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
    /// 日志全局唯一标识，日志服务将用这个值作索引
    int iLogID;

    /// 日志的紧急程度
    DLOG_LEVEL iLevel;

    /// 想要记录日志的源模块
    char * szSrcModule;

	///主题名
	char * szTopic;

	///20161117 huxb 默认级别
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
	///添加日志信息
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

	//20161117 huxb 新增设置、获取ESBMSG接口
	virtual int SetInfoByESBMsg(IESBMessage * lpESBMsg) = 0;
	virtual void SetFunctionID(int iFuncID) = 0;
	virtual void SetGlobalNo(const char * szGlobalNo) = 0;
	virtual int GetFunctionID() = 0;
	virtual const char * GetGlobalNo() = 0;
};

class ICloud_Dlog : public IKnown{
public:
    /***记录日志，该接口会根据日志信息组装为JSon串
    *@param iLogID 该值为dlog.xml中日志信息的索引
    *@param lpLog 业务日志信息
    *@param szMsg 日志信息
    *@param bWriteFile 是否记录本地日志
    *@return 0 成功，其他 失败
	* 其中KAFKA_ERROR_QUEUE_FULL表示kafka发布端队列满
    */
    virtual int FUNCTION_CALL_MODE AddCloudLog(int iLogID, SCloudDlog * lpLog, const char * szMsg, int bWriteFile = 1) = 0;

    /***记录流日志
    *@param lpData 二进制日志信息
    *@param uLen 日志长度
    *@param bWriteFile 是否记录本地日志
    *@return 0 成功，其他 失败
    */
    virtual int FUNCTION_CALL_MODE AddStreamCloudLog(const void * lpData, unsigned int uLen, int bWriteFile = 1) = 0;

	///20160826 huxb 是否写本地文件由配置决定，同时修改为异步记录日志
	/***记录日志，该接口会根据日志信息组装为JSon串
    *@param iLogID 该值为dlog.xml中日志信息的索引
    *@param lpLog 业务日志信息
    *@param szMsg 日志信息
    *@return 0 成功，其他 失败
	* 其中KAFKA_ERROR_QUEUE_FULL表示kafka发布端队列满
    */
    virtual int FUNCTION_CALL_MODE AddCloudLogEx(int iLogID, SCloudDlog * lpLog, const char * szMsg) = 0;
	
	///20161017 huxb 获取日志参数接口
	/***记录日志，该接口会根据日志信息组装为JSon串
    *@return 日志参数接口
    */
	virtual ICloud_DLogArgs * FUNCTION_CALL_MODE GetDLogArgs() = 0;

	///20161017 huxb 新增日志接口
	/***记录日志，该接口会根据日志信息组装为JSon串
    *@param szTopic 主题
    *@param lpArgs 日志参数
    *@return 0 成功，其他 失败
	* 其中KAFKA_ERROR_QUEUE_FULL表示kafka发布端队列满
    */
	virtual int FUNCTION_CALL_MODE AddLogByArgs(const char * szTopic, ICloud_DLogArgs * lpArgs) = 0;

	///20161117 huxb 新增日志接口
	/***记录日志，该接口支持异步记录本地文件，并组装为JSon串发往kafka日志服务器
    *@param iLogID 该值为dlog.xml中日志信息的索引
	*@param iLevel 日志级别
    *@param lpArgs 日志参数
    *@return 0 成功，其他 失败
	* 其中KAFKA_ERROR_QUEUE_FULL表示kafka发布端队列满
    */
	virtual int FUNCTION_CALL_MODE AddLogByArgsEx(int iLogID, int iLevel, ICloud_DLogArgs * lpDlogArgs) = 0;
};

#endif       /*end def __Cloud_Dlog__Interface_H__*/
