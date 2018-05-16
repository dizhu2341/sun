/*******************************************************
  源程序名称:
  软件著作权:恒生电子股份有限公司
  系统名称:  消息中心2.0
  模块名称:  插件API类
  功能说明:  插件API接口说明
  作    者:  wushuai
  开发日期:  20130621
  备    注: 
  20130913 majc 添加返回错误函数
  20130917 majc 添加取消订阅接口CancelSubscribeTopicEx
  20140605 majc 增加订阅数据结构
*********************************************************/


#ifndef __MC_COMMONAPI_INTERFACE_H__
#define __MC_COMMONAPI_INTERFACE_H__

#if defined(_WIN32)&& _MSC_VER < 1300
#pragma warning(disable: 4786)				//需加在被包含的STL头文件前
#pragma warning(disable: 4710)				//需加在被包含的STL头文件前
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

//20140605 majc 增加订阅数据结构
typedef struct tagSubRecvDataForProc
{
	char* lpFilterData;     /**< 过滤字段的数据头指针，用解包器解包 */
	int iFilterDataLen;     /**< 过滤字段的数据长度 */
	char* lpAppData;        /**< 附加数据的数据头指针 */
	int iAppDataLen;        /**< 附加数据的长度 */
	char szTopicName[260];  /**< 主题名字 */
	
   /**
    * tagSubscribeRecvData 构造函数
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
/*----------------------------------------------------构造----------------------------------------------*/
	/** 构造一个过滤器接口指针
	* @return 返回NULL表示失败。
	**/
	virtual IPluginFilterInterface* FUNCTION_CALL_MODE NewFilter()=0;

	/** 构造一个订阅属性接口指针
	* @return 返回NULL表示失败。
	**/
	virtual IPluginSubscribeParamInterface* FUNCTION_CALL_MODE NewSubscribeParam()=0;

/*-----------------------------------------------订阅----------------------------------------------------*/

	/**订阅主题
	* @param lpSubscribeParam 上面定义的订阅参数结构
	* @param uiTimeout 超时时间
	* @param lpBizPack 业务校验需要增加的业务字段以及值，没有就根据过滤属性作为业务校验字段
	* @return 返回值大于0，表示当前订阅成功的订阅标识，外面要记住这个标识和订阅项之间的映射关系，这个标识需要用于取消订阅和接收消息的回调里面.
	*		  返回其他值，根据错误号获取错误信息.
	**/
	virtual int FUNCTION_CALL_MODE SubscribeTopic(IPluginSubscribeParamInterface* lpSubscribeParamInter ,unsigned int uiTimeout,IF2Packer* lpBizPack=NULL) = 0;

	/**取消订阅主题
	* @param topicName 主题名字，不知道名字就传NULL
	* @param lpFilter 对应的过滤条件
	* @param uiTimeout 超时时间
	* @return 返回0表示取消订阅成功，返回其他值，根据错误号获取错误信息。
	**/
	virtual int FUNCTION_CALL_MODE CancelSubscribeTopic(int index) = 0;

/*-----------------------------------------------------------发布---------------------------------------------/
	/**业务打包格式的内容发布接口
	* @param topicName 主题名字，不知道名字就传NULL
	* @param topicNo 主题编号，不知道编号就传0
	* @param lpPacker 具体的内容
	* @param iTimeOut 超时时间
	* @param bCompatible 兼容1.0的标志，只有兼容插件发布的时候出入true，其他都是false。
	* @return 返回0表示成功，返回其他值，根据错误号获取错误信息。
	**/
	virtual int FUNCTION_CALL_MODE PubMsgByPacker(char* topicName,IF2UnPacker* lpUnPacker,int iTimeOut=-1,bool bCompatible=false) = 0;
	
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
	virtual int FUNCTION_CALL_MODE PubMsg(char* topicName, IPluginFilterInterface* lpFilterInter, const void *lpData, int nLength,int iTimeOut=-1,bool bCompatible=false) = 0;

	/** 返回最后一次执行的错误信息
	* @return 返回对应错误信息
	**/
	virtual char* FUNCTION_CALL_MODE GetMCLastError() = 0;
	
	
	//20130917 majc 添加取消订阅接口
		/**
    * 取消订阅主题
    * @param topicName 主题名字
    * @param lpFilterInterface 对应的过滤条件
    * @return 返回0表示取消订阅成功，返回其他值，根据错误号获取错误信息.
    */
  virtual int FUNCTION_CALL_MODE CancelSubscribeTopicEx(char* topicName,IPluginFilterInterface* lpFilterInterface) = 0;

  //20130913 majc 添加返回错误函数
	/** 根据错误号获取错误信息
	* @param nErrorNo 错误号
	* @return 返回对应错误信息
	**/
	virtual char* FUNCTION_CALL_MODE GetErrorMsg(int nErrorNo) = 0;
};

#endif
