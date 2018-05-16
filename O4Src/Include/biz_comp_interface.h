/*******************************************************
  源程序名称:biz_comp_interface.h
  软件著作权:恒生电子股份有限公司
  系统名称:  金融基础件V2.0
  模块名称:  AS模块
  功能说明:  业务逻辑组件标准头文件
             1、定义了功能组件动态库/共享库输出函数原型。
             2、开发新的AS功能组件时，应包含此文件，并实现此处定义的输出函数。
             3、此头文件仅供开发AS功能组件使用
             
  相关文档:  概要设计接口部分
  作    者:  zhangly
  开发日期:  20080728
  备    注:  linux\unix平台定义 OS_UNIX
  修改人员：
  修改日期：
  修改说明：

  20130705 xuxp 增加订阅发布接口
*********************************************************/

#ifndef AS_BIZ_COMP_H
#define AS_BIZ_COMP_H

#ifdef __win32
#ifndef FUNCTION_CALL_MODE
	#define FUNCTION_CALL_MODE  __stdcall 
#endif
#endif

#include <Include/pack_interface.h>
#include <Include/config_interface.h>
#include <Include/esb_message_factory_interface.h>
#include <Include/hsdb_interface.h>
#include <Include/mdb_interface.h>
//20130705 xuxp 增加订阅发布接口头文件
#include <Include/mc_bizcomponent_interface.h>

#define SID_TM "com.hundsun.fbase.tm"
#define SID_FUND_CTX "com.hundsun.fbase.fund"
#define SID_SCRIPT_CTX "com.hundsun.fbase.script"

struct IScriptContext : public IKnown
{
	///获得指定索引的结果集（解包器接口）
	/**
	 *@param int iIndex 索引值，表示要取脚本配置中组件编号为iIndex的那次组件调用的返回结果集
	 *@return IF2UnPacker * 解包器指针，使用即可，不需要release。找不到时返回NULL。
	 */
	virtual IF2UnPacker * FUNCTION_CALL_MODE GetUnPackerByIndex(int iIndex) = 0;

	///<脚本使用>，获得脚本组件调用序列
	/**
	 *@return char * 脚本组件的调用序列，存放的是调用组件顺序的下标。
	 */
	virtual char * FUNCTION_CALL_MODE GetScriptTransSeq() = 0;
};

//基金上下问接口，由处理器上下文的Queryinterface取得
struct IFundContext : public IKnown
{
	///根据服务名取得功能号的接口
	/**
	 *@param const char * lpServiceName 服务名
	 *@return int 服务名对应的功能号。找不到时返回-1。
	 */
	virtual int FUNCTION_CALL_MODE GetFuncNo(const char * lpServiceName) = 0;

	///根据功能号取得服务名的接口
	/**
	 *@param int iFuncNo 功能号
	 *@return const char * 功能号对应的服务名。找不到时返回NULL。
	 */
	virtual const char * FUNCTION_CALL_MODE GetSvrName(int iFuncNo) = 0;

	///根据索引取得功能号的接口
	/**
	 *@param int iIndex 索引值
	 *@return int 索引值对应的功能号。找不到时返回-1。
	 */
	virtual int FUNCTION_CALL_MODE GetFuncNoByIndex(int iIndex) = 0;

	///根据索引取得服务名的接口
	/**
	 *@param int iIndex 索引值
	 *@return const char * 索引值对应的服务名。找不到时返回NULL。
	 */
	virtual const char * FUNCTION_CALL_MODE GetSvrNameByIndex(int iIndex) = 0; 

	///取得配置文件（服务名-功能号对应关系）记录条数
	/**
	 *@return int 记录条数
	 */
	virtual int FUNCTION_CALL_MODE GetRecordNum() = 0;

	///取得指定服务名的已启动进程数量
	/**
	 *@param const char * lpServiceName 服务名
	 *@return int 指定服务名的已启动进程数量
	 */
	virtual int FUNCTION_CALL_MODE GetProcessNum(const char * lpServiceName) = 0;

	///等待消息
	/**
	 *@param IESBMessage ** lpMsg 等待消息
	 *@param int iTimeOut 等待时间
	 *@return int 返回成功与否，0成功，其他失败
	 */
	virtual int FUNCTION_CALL_MODE waitForMsg(IESBMessage ** lpMsg, int iTimeOut) = 0;

	///推送消息
	/**
	 *@param int iCd 会话编号
	 *@param IESBMessage * lpMsg 待发送的消息
	 *@return int 指定服务名的已启动进程数量
	 */
	virtual int FUNCTION_CALL_MODE SendMsg(int iCd, IESBMessage * lpMsg) = 0;
};

///事务监视器接口，通过处理器上下文的QueryInterface可以获得
struct IAS2TM : public IKnown
{
    ///开始事务，生成一个前端唯一序列号(组成:节点名#编号#时间戳#顺序号)，该号可用于系统级事务保证，理论最大长度32+1+4+1+12+1+12
	virtual char * FUNCTION_CALL_MODE BeginTrans() =0;	

    ///异常交易记录(功能号、前端序列号、原始请求消息)
    virtual void FUNCTION_CALL_MODE Assert() =0;

	///当前事务已提交的交易个数
    virtual int FUNCTION_CALL_MODE GetCommitNum() =0;

    ///事务结束
    virtual void FUNCTION_CALL_MODE EndTrans() =0;	
};

///处理器上下文，供业务逻辑处理组件使用
struct IAS2Context : public IKnown
{
	///取原请求消息
	virtual IESBMessage * FUNCTION_CALL_MODE GetOrgRequest() = 0;

	///取ESB消息工厂插件接口
	virtual IESBMessageFactory * FUNCTION_CALL_MODE GetESBMsgFactory() = 0;

	///取业务包服务插件接口
	virtual IF2PackSvr * FUNCTION_CALL_MODE GetF2PackSvr() = 0;
	
	///取数据库连接
	/**如果输入的数据源名为NULL，则取AS配置的缺省数据源名
	 *@param const char * szDataSourceName 数据源名
	 *@return char *  缺省数据源名 
	 */
	virtual IConnection *  FUNCTION_CALL_MODE GetDBConnection(const char * szDataSourceName = NULL ) = 0; 
	
	///取当前处理线程的内存数据库连接
	/**
	 *@return int  数据连接接口 
	 */
	virtual int  FUNCTION_CALL_MODE GetMDBSession() = 0; 

	///同步调用子服务
	/**
	 *@param IESBMessage * lpReqMessage 子服务调用消息[in]
	 *@param IESBMessage ** lppAnsMessage 子服务应答消息[out]
	 *@param int iTimeOut  超时时间(ms)[in]
	 *@return 返回0表示成功，需要调用者释放获得的应答消息；返回-1时，发送失败(请求消息已被释放)；返回-2,表示该调用超时，事务性服务可能需要冲正或重发；
	 */
	virtual int FUNCTION_CALL_MODE CallSubService(IESBMessage * lpReqMessage, IESBMessage ** lppAnsMessage, int iTimeOut) =0;	
	
	///异步发送消息
	/**
	 *@param IESBMessage * lpMessage 要发送的消息[in]
	 *@return 返回0表示成功，非0表示失败，失败时需要释放该消息。
	 */
	virtual int FUNCTION_CALL_MODE PostMsg(IESBMessage * lpMessage ) = 0;	
	
	///取全局配置信息
	virtual IRCfgObj * FUNCTION_CALL_MODE GetPubInfo() = 0;

	///从上下文的打包器池中获得一个打包器
	/**
	 *@return IF2Packer * 打包器指针。使用者不需要release
	 */
	virtual IF2Packer * FUNCTION_CALL_MODE GetPackerFromPool() = 0;

	///从上下文的解包器池中获得一个解包器
	/**
	 *@return IF2UnPacker * 解包器指针，使用者不需要release
	 */
	virtual IF2UnPacker * FUNCTION_CALL_MODE GetUnPackerFromPool() = 0;

	//2030705 xuxp 下面增加订阅发布接口
	//////////////////////////////////////////////////////////////////////////
	/** 构造一个过滤器接口指针
	* @return 返回NULL表示失败。
	**/
	virtual IPluginFilterInterface* FUNCTION_CALL_MODE NewFilter()=0;

	/** 构造一个订阅属性接口指针
	* @return 返回NULL表示失败。
	**/
	virtual IPluginSubscribeParamInterface* FUNCTION_CALL_MODE NewSubscribeParam()=0;

	/**订阅主题
	* @param lpSubscribeParam 上面定义的订阅参数结构
	* @param uiTimeout 超时时间
	* @param lpBizPack 业务校验需要增加的业务字段以及值，没有就根据过滤属性作为业务校验字段
	* @return 返回0表示订阅成功，返回2是重复订阅，可以当成订阅成功处理。返回其他值，根据错误号获取错误信息。
	**/
	virtual int FUNCTION_CALL_MODE SubscribeTopic(IPluginSubscribeParamInterface* lpSubscribeParamInter ,unsigned int uiTimeout,IF2Packer* lpBizPack=NULL) = 0;

	/**取消订阅主题
	* @param topicName 主题名字，不知道名字就传NULL
	* @param lpFilter 对应的过滤条件
	* @param uiTimeout 超时时间
	* @return 返回0表示取消订阅成功，返回其他值，根据错误号获取错误信息。
	**/
	virtual int FUNCTION_CALL_MODE CancelSubscribeTopic(int index) = 0;

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
	
	//20130923 xuxp 添加取消订阅接口
		/**
    * 取消订阅主题
    * @param topicName 主题名字
    * @param lpFilterInterface 对应的过滤条件
    * @return 返回0表示取消订阅成功，返回其他值，根据错误号获取错误信息.
    */
	virtual int FUNCTION_CALL_MODE CancelSubscribeTopicEx(char* topicName,IPluginFilterInterface* lpFilterInterface) = 0;

	//201309123 xuxp 添加返回错误函数
	/** 根据错误号获取错误信息
	* @param nErrorNo 错误号
	* @return 返回对应错误信息
	**/
	virtual char* FUNCTION_CALL_MODE GetErrorMsg(int nErrorNo) = 0;
	
	//20140605 majc 添加
	/** 如果是订阅推送的消息可以获取主题和过滤条件
	  * @return 返回订阅信息相关信息；
	**/
	virtual SUB_RECVDATA_FOR_PROC* FUNCTION_CALL_MODE GetRecvData() = 0;
	//////////////////////////////////////////////////////////////////////////
	
};


///业务逻辑处理函数指针类型，返回1表示不需要框架作出应答，子服务原则上不返回1.
typedef int ( FUNCTION_CALL_MODE *TBizFunctionEntry ) (IAS2Context * context_handle, IF2UnPacker * in,IF2Packer * out);
///脚本解释执行时的子服务调用函数指针。
typedef int ( FUNCTION_CALL_MODE *TScriptSubCall ) (IAS2Context * lpContext,IF2UnPacker * lpInUnPacker, IF2Packer * lpOutPacker,unsigned int iTimeOut,unsigned int iFuncNo,unsigned int iBranchNo,unsigned int iSystemNo,unsigned int iSubSystemNo);

///业务逻辑处理函数组件信息
typedef struct tagBizFunctionInfo
{
	///功能号
	unsigned long dwFunctionNo;
	///处理函数版本信息yyyymmdd
	int iVersion;
	///请求处理函数
    TBizFunctionEntry ReqProc;
	
	///请求处理函数中所发出的子服务调用的应答处理函数入口
	/** 一般情况下为空,使用subcall接口时与请求处理函数相同 */
    TBizFunctionEntry AnsProc;
	///功能描述信息
	const char * Caption;
}BIZ_FUNC_INFO,* LPBIZ_FUNC_INFO;

///相应序号的功能存在
#define ASFC_EXISTS  1

///相应序号的功能不存在
#define ASFC_NONE    0
//不需要框架作出应答
#define ASFC_NO_ANSWER 1

//子服务调用返回值定义
//成功
#define SUB_CALL_OK  0
//错误
#define SUB_CALL_ERR -1
//超时
#define SUB_CALL_TIMEOUT -2


///每一个被业务逻辑处理器插件加载的业务组件库，必须引出以下函数:

#ifdef __cplusplus
extern "C" { 
#endif

///组件库加载事件响应函数
/**
 *@param char * arg  组件运行参数，每个动态库可以配置一个运行参数串，格式由组件自行解析
 */
void  FUNCTION_CALL_MODE OnLoad(char * arg);

///组件库卸载事件响应函数
void  FUNCTION_CALL_MODE OnUnload(); 
 
///服务器启动事件响应函数(AS开始对外服务)
void  FUNCTION_CALL_MODE OnStart();

///服务器停止对外服务事件响应函数
void  FUNCTION_CALL_MODE OnStop( ); 

///取组件库内业务功能信息（业务功能组件库接口查询函数）
/**组件内实现此函数，AS在加载组件库之后，通过此函数从序号0开始，查询当前组件库所支持的功能函数,直到此函数返回ASFC_NONE；
 *@param int Index           要查询的功能函数序号（从0开始）
 *@param LPFUNC_INFO  ppv    返回当前功能的相关信息[out]
 *@return int 指定序号的功能函数存在，则返回 ASFC_EXISTS ，否则返回 ASFC_NONE
 */
int  FUNCTION_CALL_MODE GetBizFunctionsInfo(int Index, LPBIZ_FUNC_INFO  ppv );

///取组件库版本
char *  FUNCTION_CALL_MODE GetLibVersion( );

///设置插件查询接口，在OnStart()调用之前被设置
void  FUNCTION_CALL_MODE SetIKnown( IKnown * lp ); 

#ifdef __cplusplus
  }
#endif

#endif
