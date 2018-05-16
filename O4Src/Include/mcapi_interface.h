/** @file mcapi_interface.h
 *  @brief MC2.0 SDK开发接口文件
 *  @author      xuxp
 *  @date        20120809
 *  @copyright   恒生电子股份有限公司
 *  @version     1.0.0.0
 *
 *  @par 修改记录 <日期> <版本> <修改人员> <修改内容>
 *  -# 2013-02-04 1.0.0.0 xuxp 发布初始版本
 */

/**
 * @example publish.cpp
 * @example fileupdate.cpp
 * @example subscribe.cpp
 */

/**
 * @mainpage MCAPI 开发文档
 * 文档内容
 *
 * -# MCAPI 接口文档
 * -# 订阅、发布、文件更新示例
 * -# 配置示例
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
 * - subscribe_count=10     ;每个会话订阅项个数
 * 
 * - connect_count=10       ;会话个数
 * 
 * - biz_name=test          ;业务名字
 * 
 * - topic_name=file_update ;主题名字
 * 
 * - is_rebulid=false       ;是否需要补缺
 * 
 * - is_replace=false       ;是否覆盖以前的订阅，不覆盖就是追加
 * 
 * - send_interval=0        ;发送间隔,单位是秒
 * 
 * - filter_count=1         ;过滤字段的个数，指明下面的过滤有几个，一共可以设置六个
 *
 * - filter_name1=update_type   ; 过滤字段1的名字
 *
 * - filter_value1=1            ;过滤字段1的取值
 *
 * - return_count=3             ;返回字段的个数
 *
 * - return_filed1=update_type  ; 返回字段1的名字
 *
 * - return_filed2=account_no   ; 返回字段2的名字
 *
 * - return_filed2=name         ; 返回字段3的名字
 *
 * [publish]
 * - biz_name=xuxp          ;业务名字
 * 
 * - topic_name=file_update ;主题名字
 *
 * [fileupdate]
 * - fileupdate=1           ; 文件更新开关
 *
 * - topicName=fileupdate   ; 文件更新主题名字
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

#define SIMPLIFIED_CHINESE      0   /**< 错误信息语言:简体中文 */
#define ENGLISH                 1   /**< 错误信息语言:英文 */

#define IDENTITY_NAME_LENGTH    32  /**< 客户端名字长度 */
#define MAX_MACADDRESS_LEN	    18  /**< MAC 地址长度 */
#define MAX_RAND_LEN	        4   /**< 随机数长度 */

/** 客户标识长度 */
#define MAX_BIZNAME_LEN \
	IDENTITY_NAME_LENGTH+1+MAX_MACADDRESS_LEN+1+MAX_RAND_LEN+2

#define INIT_RECVQ_LEN 256          /**< 接收队列初始长度 */
#define STEP_RECVQ_LEN 512          /**< 接收队列扩展步长 */

#define MAX_FILTERFIELD_LEN 63      /**< 过滤字段长度 */

#define TYPE_SUBCRIBER      0       /**< 订阅类型 */
#define TYPE_PUBLISH        1       /**< 发布类型 */
#define TYPE_SUB_PUB        2       /**< 订阅和发布类型 */

/** 主题可靠等级 */
enum ReliableLevel
{
    LEVEL_DOBEST            = 0,    /**< 尽力而为 */
    LEVEL_DOBEST_BYSEQ      = 1,    /**< 尽力有序 */
    LEVEL_MEM               = 2,    /**< 内存 */
    LEVEL_FILE              = 3,    /**< 文件 */
    LEVEL_SYSTEM            = 4     /**< 系统 */
};

/** @defgroup t2sdk t2sdk 接口
 *  t2sdk 输出函数
 *  @{
 */
#ifdef __cplusplus
extern "C"
{
#endif
   /**
    * 获得一个配置对象
    * @return 配置对象指针
    */
    CConfigInterface * FUNCTION_CALL_MODE NewConfig();

   /**
    * 获得一个连接对象
    * @param lpConfig 配置对象指针
    * @return 连接对象指针
    */
    CConnectionInterface * FUNCTION_CALL_MODE NewConnection(CConfigInterface *lpConfig);

   /**
    * 获得一个ESBMessage对象
    * @param nCompressID 是否压缩 1表示压缩
    * @return ESBMessage对象指针
    */
    IESBMessage *  FUNCTION_CALL_MODE NewESBMessage(int nCompressID = 1);

   /**
    * 获取t2sdk版本信息
    */
    int FUNCTION_CALL_MODE GetVersionInfo();

   /**
    * 获取IF2Packer对象
    * @param iVersion 版本信息，2.0传入0x21
    * @return 返回IF2Packer指针
    */
    IF2Packer * FUNCTION_CALL_MODE NewPacker(int iVersion);

   /**
    * 获取IF2UnPacker对象
    * @param lpBuffer 待解包的数据
    * @param iLen 数据长度
    * @return 返回IF2UnPacker指针
    */
    IF2UnPacker * FUNCTION_CALL_MODE NewUnPacker(void * lpBuffer, unsigned int iLen);
#ifdef __cplusplus
};
#endif
/** @} */

/** 
 * 过滤器接口
 */
class CFilterInterface:public IKnown
{
public:
   /**
    * 根据下标获取过滤条件的名字
    * @param index 对应的过滤条件下标
    * @return 返回对应的下标过滤条件的名字，否则返回NULL.
    */
    virtual char* FUNCTION_CALL_MODE GetFilterNameByIndex(int index) = 0;

   /**
    * 根据下标获取过滤条件的值
    * @param index 对应的过滤条件下标
    * @return 返回对应的下标过滤条件的值，否则返回NULL.
    */
    virtual char* FUNCTION_CALL_MODE GetFilterValueByIndex(int index)= 0;

   /**
    * 根据过滤条件的名字获取过滤条件的值
    * @param fileName 对应的过滤条件名字
    * @return 返回对应的过滤条件名字的条件值，否则返回NULL.
    */
    virtual char* FUNCTION_CALL_MODE GetFilterValue(char*  fileName)= 0;

   /**
    * 获取过滤条件的个数
    * @return 返回对应过滤条件的个数，没有返回0
    */
    virtual int   FUNCTION_CALL_MODE GetCount() = 0;

   /**
    * 设置过滤条件，根据过滤条件名字和值
    * @param filterName 对应的过滤条件名字
    * @param filterValue 对应的过滤条件名字的值
    */
    virtual void FUNCTION_CALL_MODE  SetFilter(char* filterName,char* filterValue) =0;
};

/**
 * 订阅参数类接口
 */
class CSubscribeParamInterface:public IKnown
{
public:

   /**
    * 设置主题名字
    * @param szName 对应的主题名字
    */
    virtual void FUNCTION_CALL_MODE  SetTopicName(char* szName) =0;

   /**
    * 设置附加数据
    * @param lpData 附加数据的首地址
    * @param iLen 附加数据的长度
    */
    virtual void FUNCTION_CALL_MODE  SetAppData(void* lpData,int iLen)=0;
    
   /**
    * 添加过滤条件
    * @param filterName 过滤条件的名字
    * @param filterValue 过滤条件的值
    */
    virtual void FUNCTION_CALL_MODE  SetFilter(char* filterName,char* filterValue)=0;

   /**
    * 添加返回字段
    * @param filedName 需要添加的返回字段
    */
    virtual void FUNCTION_CALL_MODE  SetReturnFiled(char* filedName)=0;

   /**
    * 设置是否补缺标志
    * @param bFromNow true表示需要之前的数据，也就是补缺，false表示不需要补缺
    */
    virtual void FUNCTION_CALL_MODE  SetFromNow(bool bFromNow)=0;

   /**
    * 设置覆盖订阅标志
    * @param bReplace true表示覆盖订阅，取消之前的所有订阅，只保留当前的订阅，false表示追加订阅
    */
    virtual void FUNCTION_CALL_MODE  SetReplace(bool bReplace)=0;

   /**
    * 设置发送间隔
    * @param nSendInterval 单位是秒
    */
    virtual void FUNCTION_CALL_MODE  SetSendInterval(int nSendInterval)=0;

   /**
    * 获取主题名字
    * @return 返回主题名字信息
    */
    virtual char* FUNCTION_CALL_MODE  GetTopicName() =0;

   /**
    * 获取附加数据
    * @param iLen 出参，表示附加数据的长度
    * @return 返回附加数据首地址，没有返回NULL
    */
    virtual void* FUNCTION_CALL_MODE  GetAppData(int *iLen) =0;

   /**
    * 获取对应的过滤字段的名字
    * @param index 对应的过滤条件下标
    * @return 返回对应的下标过滤条件的名字，否则返回NULL.
    */
    virtual char* FUNCTION_CALL_MODE  GetFilterNameByIndex(int index) = 0;

   /**
    * 根据下标获取过滤条件的值
    * @param index 对应的过滤条件下标
    * @return 返回对应的下标过滤条件的值，否则返回NULL.
    */
    virtual char* FUNCTION_CALL_MODE  GetFilterValueByIndex(int index)= 0;

   /**
    * 根据过滤条件的名字获取过滤条件的值
    * @param fileName 对应的过滤条件名字
    * @return 返回对应的过滤条件名字的条件值，否则返回NULL.
    */
    virtual char* FUNCTION_CALL_MODE  GetFilterValue(char*  fileName)= 0;

   /**
    * 获取过滤条件的个数
    * @return 返回对应过滤条件的个数，没有返回0
    */
    virtual int   FUNCTION_CALL_MODE  GetFilterCount() = 0;

   /**
    * 获取返回字段
    * @return 返回对应的返回字段信息
    */
    virtual char* FUNCTION_CALL_MODE  GetReturnFiled()=0;

   /**
    * 获取是否补缺的标志
    * @return 返回对应的补缺标志
    */
    virtual bool  FUNCTION_CALL_MODE  GetFromNow()=0 ;

   /**
    * 获取是否覆盖订阅的标志
    * @return 返回对应的覆盖订阅标志
    */
    virtual bool  FUNCTION_CALL_MODE  GetReplace() =0;

   /**
    * 获取对应的发送频率
    * @return 返回对应的发送间隔
    */
    virtual int   FUNCTION_CALL_MODE  GetSendInterval()=0;
};

class CSubscribeInterface;

/**
 * @brief 订阅回调接口返回的数据定义，除了订阅需要的业务体之外，还需要返回的数据
 */
typedef struct tagSubscribeRecvData
{
	char* lpFilterData;     /**< 过滤字段的数据头指针，用解包器解包 */
	int iFilterDataLen;     /**< 过滤字段的数据长度 */
	char* lpAppData;        /**< 附加数据的数据头指针 */
	int iAppDataLen;        /**< 附加数据的长度 */
	char szTopicName[260];  /**< 主题名字 */
	
   /**
    * tagSubscribeRecvData 构造函数
    */
	tagSubscribeRecvData()
	{
		memset(this,0,sizeof(tagSubscribeRecvData));
	}
}SUBSCRIBE_RECVDATA, *LPSUBSCRIBE_RECVDATA;

/**
 * 订阅回调接口，上层应用通过这个接口，接收主推过来的消息
 */
class CSubCallbackInterface: public IKnown
{
public:

   /**
    * 收到发布消息的回调
    * @param lpSub 回调的订阅指针
    * @param subscribeIndex 消息对应的订阅标识，这个标识来自于SubscribeTopic函数的返回
    * @param lpData 返回消息的二进制指针，一般是消息的业务体打包内容
    * @param nLength 二进制数据的长度
	* @param lpRecvData 主推消息的其他字段返回，主要包含了附加数据，过滤信息，主题名字，详细参看前面结构体定义
    * @return 无
    */
    virtual void FUNCTION_CALL_MODE OnReceived(CSubscribeInterface *lpSub,int subscribeIndex, const void *lpData, int nLength,LPSUBSCRIBE_RECVDATA lpRecvData) = 0;

   /**
    * 收到剔除订阅项的消息回调，一般在拥有踢人策略的主题下会回调这个接口,这个回调里面不需要取消订阅，底层已经取消这个订阅，只是一个通知接口
    * @param lpSub 回调的订阅指针
    * @param subscribeIndex 消息对应的订阅标识，这个标识来自于SubscribeTopic函数的返回
    * @param TickMsgInfo 踢人的错误信息，主要是包含具体重复的订阅项位置信息
    * @return 无
    */
    virtual void FUNCTION_CALL_MODE OnRecvTickMsg(CSubscribeInterface *lpSub,int subscribeIndex,const char* TickMsgInfo) = 0;
};


/**
 * 订阅接口的定义
 */
class CSubscribeInterface: public IKnown
{
public:

   /**
    * 订阅主题
    * @param lpSubscribeParamInter 上面定义的订阅参数结构
    * @param uiTimeout 超时时间
    * @param lppBizUnPack 业务校验时，失败返回的业务错误信息，如果订阅成功没有返回，输出参数，需要外面调用Release释放
                          如果接受业务校验的错误信息，写法如下：
                          IF2UnPacker* lpBizUnPack =NULL;
                          SubscribeTopic(...,&lpBizUnPack);
                          最后根据返回值，如果是失败的就判断 lpBizUnPack 是不是NULL.
                          最后错误信息获取完之后,释放
                          lpBizUnPack->Release();
    * @param lpBizPack 业务校验需要增加的业务字段以及值，没有就根据过滤属性作为业务校验字段
    * @return 返回值大于0，表示当前订阅成功的订阅标识，外面要记住这个标识和订阅项之间的映射关系，这个标识需要用于取消订阅和接收消息的回调里面.
	*		  返回其他值，根据错误号获取错误信息.
    */
    virtual int FUNCTION_CALL_MODE SubscribeTopic(CSubscribeParamInterface* lpSubscribeParamInter ,unsigned int uiTimeout,IF2UnPacker** lppBizUnPack=NULL,IF2Packer* lpBizPack=NULL) = 0;

   /**
    * 取消订阅主题
    * @param subscribeIndex 消息对应的订阅标识，这个标识来自于SubscribeTopic函数的返回
    * @return 返回0表示取消订阅成功，返回其他值，根据错误号获取错误信息.
    */
    virtual int FUNCTION_CALL_MODE CancelSubscribeTopic(int subscribeIndex) = 0;


	/**
    * 取消订阅主题
    * @param topicName 主题名字
    * @param lpFilterInterface 对应的过滤条件
    * @return 返回0表示取消订阅成功，返回其他值，根据错误号获取错误信息.
    */
    virtual int FUNCTION_CALL_MODE CancelSubscribeTopicEx(char* topicName,CFilterInterface* lpFilterInterface) = 0;



   /**
    * 获取当前订阅接口已经订阅的所有主题以及过滤条件信息
    * @param lpPack 外面传入的打包器
    * @note packer报文字段
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
    * 取服务器地址
    * @param lpPort 输出的服务器端口，可以为NULL
    * @return 返回服务器地址
    */
    virtual const char * FUNCTION_CALL_MODE GetServerAddress(int *lpPort) = 0;
};

/**
 * 发布接口
 */
class CPublishInterface: public IKnown
{
public:

   /**
    * 业务打包格式的内容发布接口
    * @param topicName 主题名字，不知道名字就传NULL
    * @param lpUnPacker 具体的内容
    * @param iTimeOut 超时时间
    * @param lppBizUnPack 业务校验时，失败返回的业务错误信息，如果发布成功没有返回，输出参数，需要外面调用Release释放
                            如果接受业务校验的错误信息，写法如下：
                            IF2UnPacker* lpBizUnPack =NULL;
                            PubMsgByPacker(...,&lpBizUnPack);
                            最后根据返回值，如果是失败的就判断 lpBizUnPack 是不是NULL.
                            最后错误信息获取完之后,释放
                            lpBizUnPack->Release();
    * @param bAddTimeStamp 是否添加时间戳，配合单笔性能查找
    * @return 返回0表示成功，返回其他值，根据错误号获取错误信息.
    */
    virtual int FUNCTION_CALL_MODE PubMsgByPacker(char* topicName ,IF2UnPacker* lpUnPacker,int iTimeOut=-1,
        IF2UnPacker** lppBizUnPack=NULL,bool bAddTimeStamp=false) = 0;
    
   /**
    * 非业务打包格式的内容发布接口，一般二进制格式报文发布
    * @param topicName 主题名字，不知道名字就传NULL
    * @param lpFilterInterface 过滤条件，需要上层自己指定，否则默认没有过滤条件
    * @param lpData 具体的内容
    * @param nLength 内容长度
    * @param iTimeOut 超时时间
    * @param lppBizUnPack 业务校验时，失败返回的业务错误信息，如果发布成功没有返回，输出参数，需要外面调用Release释放
                            如果接受业务校验的错误信息，写法如下：
                            IF2UnPacker* lpBizUnPack =NULL;
                            PubMsgByPacker(...,&lpBizUnPack);
                            最后根据返回值，如果是失败的就判断 lpBizUnPack 是不是NULL.
                            最后错误信息获取完之后,释放
                            lpBizUnPack->Release();
    * @param bAddTimeStamp 是否添加时间戳，配合单笔性能查找
    * @return 返回0表示成功，返回其他值，根据错误号获取错误信息.
    */
    virtual int FUNCTION_CALL_MODE PubMsg(char* topicName, CFilterInterface* lpFilterInterface, const void *lpData, int nLength,int iTimeOut=-1,
        IF2UnPacker** lppBizUnPack=NULL,bool bAddTimeStamp=false) = 0;

   /**
    * 返回当前主题的发布序号
    * @param topicName 主题名字
    * @return 返回0表示没有对应的主题，返回其他值表示成功
    */
    virtual uint32 FUNCTION_CALL_MODE GetMsgNoByTopicName(char* topicName)=0;

   /**
    * 取服务器地址
    * @param lpPort 输出的服务器端口，可以为NULL
    * @return 返回服务器地址
    */
    virtual const char * FUNCTION_CALL_MODE GetServerAddress(int *lpPort) = 0;
};

/**
 * @struct tagregisterrouteinfo
 * @brief 路由信息
 */

/**
 * @typedef REGROUTE_INFO
 * @brief 路由信息类型
 */

/**
 * @typedef LPREGROUTE_INFO 
 * @brief 路由信息指针类型
 */
typedef struct tagregisterrouteinfo
{
    char m_ospfName[ID_STR_LEN+1];              /**< ospf 名 */
    char m_nbrName[IDENTITY_NAME_LENGTH+1];     /**< 邻居 名 */
    char m_svrName[SVRINSTANCE_NAME_LENGTH+1];  /**< 服务 名 */
    char m_pluginId[PLUGIN_NAME_LENGTH+1];      /**< 插件 名 */
    int  m_connectId;                           /**< 连接号 */
    int  m_memberNo;                            /**< 会话号 */

   /**
    * 构造函数
    */
    tagregisterrouteinfo()
    {
        memset(this, 0, sizeof(tagregisterrouteinfo));
    }
} REGROUTE_INFO,*LPREGROUTE_INFO;

/**
 * 注册的回调函数接口，用来接收别人的主推消息
 * @param lpData 返回消息的二进制指针，一般是消息的业务打包内容
 * @param nLength 二进制数据的长度
 * @param lpSendInfo 发送者的路由信息
 * @return 无
 */
typedef void (FUNCTION_CALL_MODE *TRecvFunctionEntry)(const void *lpData, int nLength,LPREGROUTE_INFO lpSendInfo);

/** 文件更新：以下宏为API库中文件更新功能与界面间交互的打包器中的字段 */
#define PACKER_INT_FILE_LIST            "file_list"     /**< 文件列表 */
#define PACKER_INT_FILE_ID              "file_id"       /**< 文件id */
#define PACKER_INT_FILE_SIZE            "file_size"     /**< 文件大小 */
#define PACKER_INT_TIME                 "time"          /**< 文件时间 */
#define PACKER_STRING_FILE_NAME         "file_name"     /**< 文件名 */
#define PACKER_STRING_FILE_PATH         "file_path"     /**< 文件路径 */
#define PACKER_STRING_LOCAL_PATH        "local_path"    /**< 本地文件路径 */
#define PACKER_STRING_MD5_CODE          "md5_code"      /**< 文件md5值 */

/**
 * 文件更新：界面接收文件更新filelist的回调函数
 * @param lpData 数据地址
 * @param nLength 数据长度
 * @note 
 * -# 返回正常文件列表：lpData非空               
 * -# 返回错误码：lpData为空，nLength填错误码
 */
typedef void (FUNCTION_CALL_MODE *UiRecvFileListFuntion)(const void *lpData, int nLength);

/**
 * 文件更新：界面展示进度条的回调函数
 * @param iOneFileProcessBar 单个文件进度
 * @param iTotalProcessBar 整个更新进度
 * @note 
 * -# 进度条iOneFileProcessBar正常返回1-100之间的数字，其余值为错误码，100或者错误码表示当前文件更新结束
 * -# 进度条iTotalProcessBar正常返回1-100之间的数字，-1表示错误，100或者错误码表示结束更新过程
 */
typedef void (FUNCTION_CALL_MODE *UiShowProcessBarFuntion)(int iOneFileProcessBar, int iTotalProcessBar);

/** 
 * @defgroup MCAPI MCAPI 接口
 * MCAPI 引出函数
 * @{
 */
#ifdef __cplusplus
extern "C" {
#endif

   /** 
    * API的初始化，调用其他函数之前必须先调用这个函数进行初始化
    * @param lpConnectionConfig t2sdk的连接配置
    * @param selfName 当前客户端的名字
    * @param iTimeOut 超时时间，获取主题的超时时间，建立连接的超时时间是3秒
    * @param initType 初始化类型，是要初始化成发布者还是订阅者TYPE_SUBCRIBER/TYPE_PUBLISH/TYPE_SUB_PUB
    * @param nClearDays 需要清理多少天以前的订阅者序号信息
    *   - 小于等于0表示不清理
    *   - 大于0在启动的时候就会清理文件，由上层应用决定清理多久之前的文件
    * @param lang 错误信息编码格式，支持英文和中文两种，默认为中文
    * @return 返回0表示成功，返回其他值，根据错误号获取错误信息.
    */
    int FUNCTION_CALL_MODE MCInit(CConfigInterface* lpConnectionConfig,char* selfName, int iTimeOut, 
        int initType = TYPE_SUBCRIBER,int nClearDays=0, int lang=SIMPLIFIED_CHINESE);

   /**
    * 构造一个过滤器接口指针
    * @return 返回NULL表示失败.
    */
    CFilterInterface* FUNCTION_CALL_MODE NewFilter();

   /**
    * 构造一个订阅属性接口指针
    * @return 返回NULL表示失败.
    */
    CSubscribeParamInterface* FUNCTION_CALL_MODE NewSubscribeParam();

   /**
    * 初始化一个订阅会话信息，主要附件创建会话
    * @param lpCallback 回调接口
    * @param SubScribeName 订阅者名字，多订阅者的名字必须不一样，不可以相同.最大长度32个字节
    * @param iTimeOut 超时时间
    * @param iInitRecvQLen 初始化接收队列的长度
    * @param iStepRecvQLen 接受队列的扩展步长
    * @return 返回订阅接口实例，一个会话接口对应一个回调.
    */
    CSubscribeInterface* FUNCTION_CALL_MODE NewSubscribe(CSubCallbackInterface *lpCallback,char* SubScribeName,int iTimeOut,
        int iInitRecvQLen=INIT_RECVQ_LEN,int iStepRecvQLen=STEP_RECVQ_LEN);
    
   /**
    * 创建一个发布接口实例
    * @param msgCount 本地缓存消息的个数
    * @param bResetNo 是否重置序号
    * @return 返回发送接口实例，这是一个单例，如果已经new了，就直接返回对应的指针
    */
    CPublishInterface* FUNCTION_CALL_MODE NewPublish(int msgCount,bool bResetNo = false);
    
   /**
    * 开启文件更新功能，并设置与界面交互的回调函数，必须在MCInit订阅初始化后调用.
    * @param lpConnectionConfig 底层真正发送的t2sdk的连接
    * @param fun1 函数指针，用于向界面回调显示需要更新的文件列表
    * @param fun2 函数指针，用于向界面回调显示文件更新的进度
    * @param updatedir 更新的总目录
    * @return 返回0表示成功，其他值表示失败
    */
    int FUNCTION_CALL_MODE FileUpdateInit(CConfigInterface* lpConnectionConfig, UiRecvFileListFuntion fun1, UiShowProcessBarFuntion fun2, const char* updatedir = NULL);

   /**
    * UI根据前面回调显示的文件列表，由用户选择后下发需要更新的文件列表
    * @param lpData 二进制打包数据
    * @param nLength 二进制数据的长度
    * @return 返回0表示成功，其他值表示失败.
    */
    int FUNCTION_CALL_MODE FileUpdateBegin(const void *lpData, int nLength);

   /**
    * 界面取消正在更新中的更新动作
    * @return 返回0表示成功，其他值表示失败
    */
    int FUNCTION_CALL_MODE FileUpdateCancel();


   /**
    * 获取服务端的所有主题信息
    * @param byForce 是否强制从后台获取
    * @param iTimeOut 超时时间
    * @return 成功就返回所有主题信息
    * @note 解包器外面需要调用release接口进行释放.
    * @note packer返回字段
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
    * 最后释放所有订阅和发布接口
    * @return 返回0表示成功，返回其他值，根据错误号获取错误信息.
    */
    int FUNCTION_CALL_MODE Destroy();


   /**
    * 根据错误号获取错误信息
    * @param nErrorNo 错误号
    * @return 返回对应错误信息
    */
    char* FUNCTION_CALL_MODE GetErrorMsg(int nErrorNo);

   /** 
    * 返回最后一次执行的错误信息
    * @return 返回对应错误信息
    */
    char* FUNCTION_CALL_MODE GetMCLastError();
  
#ifdef __cplusplus
}
#endif
/** @} */

#endif


