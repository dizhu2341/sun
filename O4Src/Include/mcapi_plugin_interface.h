/*******************************************************
  源程序名称:mcapi_plugin_interface.h  (plugin)
  软件著作权:恒生电子股份有限公司
  系统名称:  消息中心2.0
  模块名称:  插件API类
  功能说明:  插件API接口说明
  作    者:  xuxp
  开发日期:  20120809
  备    注:
  20130917 majc 添加取消订阅接口CancelSubscribeTopicEx
*********************************************************/


#ifndef __MCAPI_PLUGIN_INTERFACE_H__
#define __MCAPI_PLUGIN_INTERFACE_H__

/*
订阅发布接口插件，是一个流水线插件和普通接口插件
*/

#include <Include/service_interface.h>
#include <Include/glbdef.h>
#include <Include/esb_message_interface.h>


//通用通道插件的接口名
#define SID_MCAPI		   	"mcapi"
#define SID_MCCLIENTAPI		"mcclientapi"
#define MAX_TOPICNAME_LEN 256
#define IDENTITY_NAME_LENGTH 32
#define MAX_MACADDRESS_LEN	18
#define MAX_RAND_LEN	4
#define MAX_BIZNAME_LEN IDENTITY_NAME_LENGTH+1+MAX_MACADDRESS_LEN+1+MAX_RAND_LEN+2



enum ReliableLevelPlugin{API_LEVEL_DOBEST =0,//尽力而为
					API_LEVEL_DOBEST_BYSEQ = 1,//尽力有序
					API_LEVEL_MEM = 2,//内存
					API_LEVEL_FILE = 3,//文件
					API_LEVEL_SYSTEM= 4};//系统

class IPluginFilterInterface: public IKnown
{
public:
  	//设置过滤条件，过滤条件名字和值
    /**
    * @param filterName 过滤条件名字
    * @param filterValue 过滤条件名字的值
    **/
    virtual void FUNCTION_CALL_MODE SetFilterPlugin(const char* filterName, const char* filterValue) = 0;

    //根据过滤条件的名字获取过滤条件的值
    /**
    * @param filterName 对应的过滤条件名字
    * @return 返回对应的过滤条件名字的条件值，否则返回NULL。
    **/
    virtual const char* FUNCTION_CALL_MODE GetFilterValuePlugin(const char* filterName) = 0;

	//根据下标获取过滤条件的名字
	/**
	* @param index 对应的过滤条件下标
	* @return 返回对应的下标过滤条件的名字，否则返回NULL。
	**/
	virtual const char* FUNCTION_CALL_MODE GetFilterNameByIndexPlugin(int index) = 0;

    //根据下标获取过滤条件的值
	/**
	* @param index 对应的过滤条件下标
	* @return 返回对应的下标过滤条件的值，否则返回NULL。
	**/
	virtual const char* FUNCTION_CALL_MODE GetFilterValueByIndexPlugin(int index) = 0;

	//获取过滤条件的个数
	/**
	* @return 返回对应过滤条件的个数，没有返回0
	**/
	virtual int FUNCTION_CALL_MODE GetCountPlugin() = 0;
};

class IPluginSubscribeParamInterface:public IKnown
{
public:
	//设置主题名字
	/**
	* @param szName 对应的主题名字
	**/
	virtual void FUNCTION_CALL_MODE SetTopicNamePlugin(const char* szName) = 0;

	//设置附加数据
	/**
	* @param lpData 附加数据的首地址
	* @param iLen 附加数据的长度
	**/
	virtual void FUNCTION_CALL_MODE SetAppDataPlugin(const void* lpData,int iLen) = 0;
	
	//添加过滤条件
	/**
	* @param filterName 过滤条件的名字
	* @param filterValue 过滤条件的值
	**/
	virtual void FUNCTION_CALL_MODE SetFilterPlugin(const char* filterName, const char* filterValue) = 0;

	//添加返回字段
	/**
	* @param fieldName 需要添加的返回字段
	**/
	virtual void FUNCTION_CALL_MODE SetReturnFieldPlugin(const char* fieldName) = 0;

	//设置是否补缺标志
	/**
	* @param bFromNow true表示需要之前的数据，也就是补缺，false表示不需要补缺
	**/
	virtual void FUNCTION_CALL_MODE SetFromNowPlugin(bool bFromNow) = 0;

	//设置覆盖订阅标志
	/**
	* @param bReplace true表示覆盖订阅，取消之前的所有订阅，只保留当前的订阅，false表示追加订阅
	**/
	virtual void FUNCTION_CALL_MODE SetReplacePlugin(bool bReplace) = 0;

	//设置发送间隔
	/**
	* @param nSendInterval 单位是秒
	**/
	virtual void FUNCTION_CALL_MODE SetSendIntervalPlugin(int nSendInterval) = 0;

	//获取主题名字
	/**
	* @return 返回主题名字信息
	**/
	virtual const char* FUNCTION_CALL_MODE GetTopicNamePlugin() = 0;

	//获取附加数据
	/**
	* @param iLen 出参，表示附加数据的长度
	* @return 返回附加数据首地址，没有返回NULL
	**/
	virtual const void* FUNCTION_CALL_MODE GetAppDataPlugin(int *iLen) = 0;

	//获取对应的过滤字段的名字
	/**
	* @param index 对应的过滤条件下标
	* @return 返回对应的下标过滤条件的名字，否则返回NULL。
	**/
	virtual const char* FUNCTION_CALL_MODE GetFilterNameByIndexPlugin(int index) = 0;

	//根据下标获取过滤条件的值
	/**
	* @param index 对应的过滤条件下标
	* @return 返回对应的下标过滤条件的值，否则返回NULL。
	**/
	virtual const char* FUNCTION_CALL_MODE GetFilterValueByIndexPlugin(int index) = 0;

	//根据过滤条件的名字获取过滤条件的值
	/**
	* @param filterName 对应的过滤条件名字
	* @return 返回对应的过滤条件名字的条件值，否则返回NULL。
	**/
	virtual const char* FUNCTION_CALL_MODE GetFilterValuePlugin(const char* filterName) = 0;

	//获取过滤条件的个数
	/**
	* @return 返回对应过滤条件的个数，没有返回0
	**/
	virtual int FUNCTION_CALL_MODE GetFilterCountPlugin() = 0;

	//获取返回字段
	/**
	* @return 返回对应的返回字段信息
	**/
	virtual const char* FUNCTION_CALL_MODE GetReturnFieldPlugin()=0;

	//获取是否补缺的标志
	/**
	* @return 返回对应的补缺标志
	**/
	virtual bool FUNCTION_CALL_MODE GetFromNowPlugin() = 0 ;

	//获取是否覆盖订阅的标志
	/**
	* @return 返回对应的覆盖订阅标志
	**/
	virtual bool FUNCTION_CALL_MODE GetReplacePlugin() = 0;

	//获取对应的发送频率
	/**
	* @return 返回对应的发送间隔
	**/
	virtual int FUNCTION_CALL_MODE GetSendIntervalPlugin() = 0;
};


class IPluginSubscribeInterface;
//回调接口，上传应用同个这个接口，接收主推过来的消息
class IPluginSubCallbackInterface: public IKnown
{
public:
	//收到发布消息的回调
	/**
	* @param lpSub 回调的订阅指针
	* @param topicName 消息对应的主题
	* @param lpData 返回消息的二进制指针，一般是消息的业务打包内容
	* @param nLength 二进制数据的长度
	* @return 
	**/
	virtual void FUNCTION_CALL_MODE OnReceivedPlugin(IPluginSubscribeInterface *lpSub,char* topicName, const void *lpData, int nLength) = 0;

	//收到剔除订阅项的消息回调，一般在拥有踢人策略的主题下会回调这个接口
	/**
	* @param lpSub 回调的订阅指针
	* @param lpSubParam 剔除的订阅项参数
	* @param TickMsgInfo 踢人的错误信息，主要是包含具体重复的订阅项位置信息
	* @return 
	**/
	virtual void FUNCTION_CALL_MODE OnRecvTickMsgPlugin(IPluginSubscribeInterface *lpSub,IPluginSubscribeParamInterface* lpSubParam,const char* TickMsgInfo) = 0;
};


//订阅接口的定义
class IPluginSubscribeInterface: public IKnown
{
public:
	/**订阅主题
	* @param lpSubscribeParam 上面定义的订阅参数结构
	* @param uiTimeout 超时时间
	* @param lpBizPack 业务校验需要增加的业务字段以及值，没有就根据过滤属性作为业务校验字段
	* @return 返回值大于0，表示当前订阅成功的订阅标识，外面要记住这个标识和订阅项之间的映射关系，这个标识需要用于取消订阅和接收消息的回调里面.
	*		  返回其他值，根据错误号获取错误信息.
	**/
	virtual int FUNCTION_CALL_MODE SubscribeTopicPlugin(IPluginSubscribeParamInterface* lpSubscribeParamInter ,unsigned int uiTimeout,IF2Packer* lpBizPack=NULL) = 0;

	/**取消订阅主题
	* @param topicName 主题名字，不知道名字就传NULL
	* @param lpFilter 对应的过滤条件
	* @param uiTimeout 超时时间
	* @return 返回0表示取消订阅成功，返回其他值，根据错误号获取错误信息。
	**/
	virtual int FUNCTION_CALL_MODE CancelSubscribeTopicPlugin(int index) = 0;
	
	/**获取当前订阅接口已经订阅的所有主题以及过滤条件信息
	* @param lpPack 外面传入的打包器
	*报文字段“SubcribeIndex IsBornTopic TopicName TopicNo FilterRaw Appdata SendInterval ReturnFileds isReplace isFromNow Stutas QueueCount
	**/
	virtual void FUNCTION_CALL_MODE GetSubcribeTopicPlugin(IF2Packer* lpPack)=0;
	
	//20130917 majc 添加取消订阅接口
	/**
    * 取消订阅主题
    * @param topicName 主题名字
    * @param lpFilterInterface 对应的过滤条件
    * @return 返回0表示取消订阅成功，返回其他值，根据错误号获取错误信息.
    */
    virtual int FUNCTION_CALL_MODE CancelSubscribeTopicExPlugin(char* topicName,IPluginFilterInterface* lpFilterInterface) = 0;

};

//发布接口的定义
class IPluginPublishInterface: public IKnown
{
public:
	/**业务打包格式的内容发布接口
	* @param topicName 主题名字，不知道名字就传NULL
	* @param topicNo 主题编号，不知道编号就传0
	* @param lpPacker 具体的内容
	* @param iTimeOut 超时时间
	* @param bCompatible 兼容1.0的标志，只有兼容插件发布的时候出入true，其他都是false。
	* @return 返回0表示成功，返回其他值，根据错误号获取错误信息。
	**/
	virtual int FUNCTION_CALL_MODE PubMsgByPackerPlugin(char* topicName,IF2UnPacker* lpUnPacker,int iTimeOut=-1,bool bCompatible=false) = 0;
	
	/**非业务打包格式的内容发布接口，一般二进制格式报文发布
	* @param topicName 主题名字，不知道名字就传NULL
	* @param topicNo 主题编号，不知道编号就传0
	* @param lpFilter 过滤条件，需要上层自己指定，否则默认没有过滤条件
	* @param lpData 具体的内容
	* @param nLength 内容长度
	* @param iTimeOut 超时时间
	* @param bCompatible 兼容1.0的标志，只有兼容插件发布的时候出入true，其他都是false。
	* @return 返回0表示成功，返回其他值，根据错误号获取错误信息。
	**/
	virtual int FUNCTION_CALL_MODE PubMsgPlugin(char* topicName, IPluginFilterInterface* lpFilterInter, const void *lpData, int nLength,int iTimeOut=-1,bool bCompatible=false) = 0;
	
};


struct IMCClient:public IKnown
{
public:

	/** 构造一个过滤器接口指针
	* @return 返回NULL表示失败。
	**/
	virtual IPluginFilterInterface* FUNCTION_CALL_MODE NewFilter()=0;

	/** 构造一个订阅属性接口指针
	* @return 返回NULL表示失败。
	**/
	virtual IPluginSubscribeParamInterface* FUNCTION_CALL_MODE NewSubscribeParam()=0;

	/** 初始化一个订阅会话信息，主要附件创建会话
	* @param lpCallback 回调接口
	* @param subscribeName 订阅者名字必须保证唯一性
	* @param uiTimeout 超时时间
	* @param bChild 只有下级消息中心插件才可以设置成true，其他插件全部是false，不可以设置成true
	* @return 返回订阅接口实例，一个会话接口对应一个回调。
	**/
	virtual IPluginSubscribeInterface* FUNCTION_CALL_MODE NewSubscribe(IPluginSubCallbackInterface *lpCallback,char* subscribeName,int iTimeOut,bool bChild=false) =0;
	
	/** 创建一个发布接口实例
	* @param msgCount 本地缓存消息的个数
	* @param bResetNo 是否重置序号
	* @return 返回发送接口实例，这是一个单例，如果已经new了，就直接返回对应的指针
	**/
	virtual IPluginPublishInterface* FUNCTION_CALL_MODE NewPublish(int msgCount,bool bResetNo = false) =0;
	

	/** 获取服务端的所有主题信息
	* @param byForce 是否强制从后台获取
	* @param uiTimeout 超时时间
	* @return 成功就返回所有主题信息
	*解包器外面需要调用release接口进行释放。
	*返回字段：TopicName TopicNo ReliableLevel IssuePriority MsgLifetime Stutas TickStrategy BusinessVerify Local
	* FilterFileld1 FilterFileld2 FilterFileld3 FilterFileld4 FilterFileld5 FilterFileld6 subcribeStr publishStr
	**/
	virtual IF2UnPacker* FUNCTION_CALL_MODE GetTopic(bool byForce,int iTimeOut)=0;

	/** 根据错误号获取错误信息
	* @param nErrorNo 错误号
	* @return 返回对应错误信息
	**/
	virtual char* FUNCTION_CALL_MODE GetErrorMsg(int nErrorNo)=0;

	/** 返回最后一次执行的错误信息
	* @return 返回对应错误信息
	**/
	virtual char* FUNCTION_CALL_MODE GetMCLastError()=0;
};

#endif








