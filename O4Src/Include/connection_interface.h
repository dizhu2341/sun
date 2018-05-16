/** @file
* T2_SDK接口定义文件
* @author  何仲君
* @author  恒生电子股份有限公司
* @version 1.0
* @date    20081022
*
* 20101129 xuxp 连接增加发送接口，按照指定中间件发送的接口SendBiz
*
* 20101228 xuxp 增加接口函数，增加订阅推送等等参数，通过结构体的方式添加。

* 20120111 dongpf 新增GetAddressInfo函数，来获取ip地址和端口
* 20120118 dongpf 新增CreateByMemCert函数，用以支持SSL模式下读取二进制证书文件（比如UKEY）
* 20130527 xuxp 新增GetSelfAddress函数，来获取服自己本地的IP和端口
* 20130609 xuxp 在连接里面增加订阅发布的接口
* 20131024 majc 在获取发布者接口中增加业务名参数并修改函数名
* 20140609 majc 增加获取最后错误的详细信息接口
*/

#ifndef _CONNECTION_INTERFACE_H_
#define _CONNECTION_INTERFACE_H_

#include <Include/plugin_interface.h>


#include "mc_interface.h"
#include "bizmsg_interface.h"
#include "fileupdate_interface_sdk.h"

//20110302 xuxp 增加路由信息的结构体定义
typedef struct tagRouteInfo
{
	char ospfName[ID_STR_LEN+1];
	char nbrName[ID_STR_LEN+1];
	char svrName[SVRINSTANCE_NAME_LENGTH+1];
	char pluginID[PLUGIN_NAME_LENGTH+1];
	int connectID;
	int memberNO;

	tagRouteInfo()
	{
		memset(this,0,sizeof(tagRouteInfo));
	}
}Route_Info;


//20101228 xuxp 为了发送和返回订阅推送信息而增加的结构体的定义
typedef struct tagRequestData
{	
	int sequeceNo;
	int issueType;
	void* lpKeyInfo;
	int keyInfoLen;
	void* lpFileHead;
	int fileHeadLen;
	int packetType;//20100111 xuxp 新加的包类型
	Route_Info routeInfo;//20110302 xuxp 请求里面增加路由信息
	int iSubSystemNo;//20130508 xuxp 参数中增加子系统号传入
}REQ_DATA, *LPREQ_DATA;
typedef struct tagRespondData
{
	int functionID;
	int returnCode;
	int errorNo;
	char* errorInfo;
	int issueType;
	void* lpKeyInfo;
	int keyInfoLen;
	Route_Info sendInfo;//20110302 xuxp 应答里面增加发送者信息
}RET_DATA, *LPRET_DATA;


///连接对象 CConnectionInterface 的参数配置对象
/**
* 包括从文件加载、保存到文件，读写操作
*/
class CConfigInterface: public IKnown
{
public:
	/**
	* 从文件加载
	* @param szFileName 文件名，格式类似ini，具体参考开发包示例
	* @return 返回0表示成功，否则失败
	*/
	virtual int FUNCTION_CALL_MODE Load(const char *szFileName) = 0;

	/**
	* 保存到文件
	* @param szFileName 文件名
	* @return 返回0表示成功，否则失败
	*/
	virtual int FUNCTION_CALL_MODE Save(const char *szFileName) = 0;

	/**
	* 取字符串值
	* @param szSection 节名
	* @param szEntry   变量名
	* @param szDefault 缺省值
	* @return 字符串值，没有找到时返回szDefault
	*/
	virtual const char * FUNCTION_CALL_MODE GetString(const char *szSection, const char *szEntry, const char *szDefault) = 0;

	/**
	* 取整数值
	* @param szSection 节名
	* @param szEntry   变量名
	* @param iDefault  缺省值
	* @return 整数值，没有找到时返回iDefault
	*/
	virtual int FUNCTION_CALL_MODE GetInt(const char *szSection, const char *szEntry, int iDefault) = 0;

	/**
	* 设置字符串值
	* @param szSection 节名
	* @param szEntry   变量名
	* @param szValue   值
	* @return 0表示成功，否则失败
	*/
	virtual int FUNCTION_CALL_MODE SetString(const char *szSection, const char *szEntry, const char *szValue) = 0;

	/**
	* 设置整数值
	* @param szSection 节名
	* @param szEntry   变量名
	* @param iValue    值
	* @return 0表示成功，否则失败
	*/
	virtual int FUNCTION_CALL_MODE SetInt(const char *szSection, const char *szEntry, int iValue) = 0;
};

class CConnectionInterface;

///连接对象 CConnectionInterface 需要的回调对象接口定义
/**
* 包括连接成功、连接断开、发送完成、收到数据、应答到达等事件    
*/
class CCallbackInterface: public IKnown
{
public:
	/**
	* 套接字连接成功
	* @param lpConnection 发生该事件的连接对象
	*/
	virtual void FUNCTION_CALL_MODE OnConnect(CConnectionInterface *lpConnection) = 0;

	/**
	* 完成安全连接
	* @param lpConnection 发生该事件的连接对象
	*/
	virtual void FUNCTION_CALL_MODE OnSafeConnect(CConnectionInterface *lpConnection) = 0;

	/**
	* 完成注册
	* @param lpConnection 发生该事件的连接对象
	*/
	virtual void FUNCTION_CALL_MODE OnRegister(CConnectionInterface *lpConnection) = 0;

	/**
	* 连接被断开
	* @param lpConnection 发生该事件的连接对象
	*/
	virtual void FUNCTION_CALL_MODE OnClose(CConnectionInterface *lpConnection) = 0;

	/**
	* 发送完成
	* @param lpConnection 发生该事件的连接对象
	* @param hSend        发送句柄
	* @param lpData       数据指针
	* @param nLength      数据长度
	* @param nQueuingData 发送队列中剩余个数，使用者可以用此数值控制发送的速度，即小于某值时进行发送
	* @see Send()
	*/
	virtual void FUNCTION_CALL_MODE OnSent(CConnectionInterface *lpConnection, int hSend, const void *lpData, int nLength, int nQueuingData) = 0;

	/**
	* 收到数据通知，之后对此hSend调用Receive应该会成功（必须调用Receive，否则数据一直会被缓存而占用内存）
	* @param lpConnection 发生该事件的连接对象
	* @param hSend        发送句柄
	* @param lpData       数据指针
	* @param nLength      数据长度
	*/
	virtual void FUNCTION_CALL_MODE OnReceiveNotify(CConnectionInterface *lpConnection, int hSend, const void *lpData, int nLength) = 0;

	/**
	* 收到发送时指定了ReplyCallback选项的请求的应答或者是没有对应请求的数据
	* @param lpConnection 发生该事件的连接对象
	* @param hSend        发送句柄
	* @param lpData       数据指针
	* @param nLength      数据长度
	*/
	virtual void FUNCTION_CALL_MODE OnReceived(CConnectionInterface *lpConnection, int hSend, const void *lpData, int nLength) = 0;

	/**
	* 收到大块数据传输协商请求
	* @param lpConnection    发生该事件的连接对象
	* @param uiLength        数据总长
	* @param szComment       关于该数据的说明文字
	* @param szFileName      当对方使用SendFile时传入的是文件名，否则其长度为0；传出指定接收到的数据写入到的文件名，长度为0时使用内存
	* @param lpPieceSize     传入对方建议分片的大小；传出自己要求的分片的大小，不能大于传入的分片大小
	* @param lpBulkReceiveID 传出此大块数据接收的标识
	* @return 返回0表示接受该大块数据传输，否则表示拒绝
	*/
	virtual int FUNCTION_CALL_MODE OnBulkReceiveStart(CConnectionInterface *lpConnection, unsigned int uiLength, const char *szComment, char *szFileName, unsigned int *lpPieceSize, int * lpBulkReceiveID) = 0;

	/**
	* 收到大块数据传输的一片数据
	* @param lpConnection     发生该事件的连接对象
	* @param lpBulkReceiveID  大块数据接收的标识
	* @param uiLength         数据总长
	* @param uiReceivedLength 已收到的数据长度
	*/
	virtual void FUNCTION_CALL_MODE OnBulkReceivePiece(CConnectionInterface *lpConnection, int lpBulkReceiveID, unsigned int uiLength, unsigned int uiReceivedLength) = 0;

	/**
	* 大块数据接收结束
	* @param lpBulkReceiveID 大块数据接收的标识
	* @param lpConnection    发生该事件的连接对象
	* @param lpData          当OnBulkStart中szFileName指定了输出文件名，为szFileName，否则为数据指针
	* @param uiLength        数据长度
	*/
	virtual void FUNCTION_CALL_MODE OnBulkReceiveEnd(CConnectionInterface *lpConnection, int lpBulkReceiveID, const void *lpData, unsigned int uiLength) = 0;

	/**
	* 大块数据发送一片数据
	* @param lpConnection 发生该事件的连接对象
	* @param iBulkSendID  大块数据发送的标识
	* @param uiLength     数据总长
	* @param uiSentLength 已发送的数据长度
	*/
	virtual void FUNCTION_CALL_MODE OnBulkSendPiece(CConnectionInterface *lpConnection, int iBulkSendID, unsigned int uiLength, unsigned int uiSentLength) = 0;

	/**
	* 大块数据发送结束
	* @param lpConnection 发生该事件的连接对象
	* @param iBulkSendID  大块数据发送的标识
	* @param iError       0表示成功，否则失败
	*/
	virtual void FUNCTION_CALL_MODE OnBulkSendEnd(CConnectionInterface *lpConnection, int iBulkSendID, int iError) = 0;
    
    /**
    * 收到SendBiz异步发送的请求的应答
    * @param lpConnection    发生该事件的连接对象
    * @param hSend           发送句柄
    * @param lpUnPackerOrStr 指向解包器指针或者错误信息
    * @param nResult         收包结果
    * 如果nResult等于0，表示业务数据接收成功，并且业务操作成功，lpUnpackerOrStr指向一个解包器，此时应首先将该指针转换为IF2UnPacker *。
    * 如果nResult等于1，表示业务数据接收成功，但业务操作失败了，lpUnpackerOrStr指向一个解包器，此时应首先将该指针转换为IF2UnPacker *。
    * 如果nResult等于2，表示收到非业务错误信息，lpUnpackerOrStr指向一个可读的字符串错误信息。
    * 如果nResult等于3，表示业务包解包失败。lpUnpackerOrStr指向NULL。
	* 如果返回值等于4，表示业务包为空。lpUnpackerOrStr指向NULL。
    */
    virtual void FUNCTION_CALL_MODE OnReceivedBiz(CConnectionInterface *lpConnection, int hSend, const void *lpUnpackerOrStr, int nResult) = 0;

	/**
    * 收到SendBiz异步发送的请求的应答
    * @param lpConnection    发生该事件的连接对象
    * @param hSend           发送句柄
    * @param lpRetData 其他需要返回的应答内容，根据需要获取
    * @param lpUnPackerOrStr 指向解包器指针或者错误信息
    * @param nResult         收包结果
    * 如果nResult等于0，表示业务数据接收成功，并且业务操作成功，lpUnpackerOrStr指向一个解包器，此时应首先将该指针转换为IF2UnPacker *。
    * 如果nResult等于1，表示业务数据接收成功，但业务操作失败了，lpUnpackerOrStr指向一个解包器，此时应首先将该指针转换为IF2UnPacker *。
    * 如果nResult等于2，表示收到非业务错误信息，lpUnpackerOrStr指向一个可读的字符串错误信息。
    * 如果nResult等于3，表示业务包解包失败。lpUnpackerOrStr指向NULL。
	* 如果返回值等于4，表示业务包为空。lpUnpackerOrStr指向NULL。lpRetData这部分结果还会存在
    */
    virtual void FUNCTION_CALL_MODE OnReceivedBizEx(CConnectionInterface *lpConnection, int hSend, LPRET_DATA lpRetData, const void *lpUnpackerOrStr, int nResult) = 0;


	//20130624 xuxp 回调增加BizMessage接口
	/**
	* 收到发送时指定了ReplyCallback选项的请求的应答或者是没有对应请求的数据
	* @param lpConnection 发生该事件的连接对象
	* @param hSend        发送句柄
	* @param lpMsg        业务消息指针
	*/
	virtual void FUNCTION_CALL_MODE OnReceivedBizMsg(CConnectionInterface *lpConnection, int hSend, IBizMessage* lpMsg) = 0;
};

///T2_SDK连接对象接口
/**
* 包括连接、断开、发送、接收等
*/
class CConnectionInterface: public IKnown
{
public:
	///连接状态，可组合
	enum ConnectionStatus
	{
		Disconnected	= 0x0000, /**< 未连接 */
		Connecting		= 0x0001, /**< socket正在连接 */
		Connected		= 0x0002, /**< socket已连接 */
		SafeConnecting	= 0x0004, /**< 正在建立安全连接 */
		SafeConnected	= 0x0008, /**< 已建立安全连接 */
		Registering		= 0x0010, /**< 正注册 */
		Registered		= 0x0020, /**< 已注册 */
		Rejected		= 0x0040  /**< 被拒绝，将被关闭 */
	};

    ///发送选项（可组合，0表示同步发送，通过Receive取应答）
	enum SendFlags
	{
		ReplyCallback    = 0x0001,   /**< 通过回调取应答 */
		MultiReply	     = 0x0002,   /**< 有多个应答，即可以针对一个hSend多次 Receive */
        IsESBMessage     = 0x0100,   /**< 发送一个ESBMessage，此时Send方法的第一个参数为ESBMessage的地址，第二个参数忽略 */
        ThroughLine      = 0x0200,   /**< 不另行添加PacketID，以buffer自带的PacketID为此次发送的PacketID*/
        ThirdParty       = 0x0400    /**< 通过回调取应答（第三方专用） */
	};

    ///接收选项（可组合，0表示接收超时时，不删除包ID，仍可再次调用Receive方法来尝试接收）
    enum RecvFlags
    {
        JustRemoveHandle = 0x0001   /**< 当接收超时时，把packet_id删除（以后再收到，则会以异步的方式收到），
                                     注意，此参数是在Receive方法中传递（如果需要的话） */
    };

	/**
	* 初始化连接对象
	* @param lpCallback 回调对象
	* @return 返回0表示成功，否则表示失败，通过调用GetErrorMsg可以获取详细错误信息
    * 如果应用不需要任何回调方法，则可向该方法传递NULL，而不必自定义回调类和对象
	*/
	virtual int FUNCTION_CALL_MODE Create(CCallbackInterface *lpCallback) = 0;
		
	/**
	* 启动连接
	* @param uiTimeout 超时时间，单位毫秒，0表示不等待（使用代理连接服务器时，该参数不起作用）
	* @return 返回0表示成功，否则表示失败，通过调用GetErrorMsg可以获取详细错误信息
	*/
	virtual int FUNCTION_CALL_MODE Connect(unsigned int uiTimeout) = 0;
	
	/**
	* 断开连接
	* @return 返回0表示成功，否则表示失败，通过调用GetErrorMsg可以获取详细错误信息
	*/
	virtual int FUNCTION_CALL_MODE Close() = 0;
	
	/**
	* 发送数据
	* @param lpData  待发送数据指针
	* @param nLength 待发送数据长度，最大长度为16M - 1
	* @param uiFlag  发送选项
	* @return 返回发送句柄（正数），否则表示失败，通过调用GetErrorMsg可以获取详细错误信息
	*/
	virtual int FUNCTION_CALL_MODE Send(const void *lpData, int nLength, unsigned int uiFlag) = 0;

	/**
	* 接收数据
	* @param hSend     发送句柄
	* @param lppData   收到数据指针的地址
	* @param lpnLength 收到数据长度的地址
	* @param uiTimeout 超时时间，单位毫秒，0表示不等待
	* @param uiFlag    接收选项，0表示接收超时后仍可继续调用Receive来接收，
    *                  JustRemoveHandle表示当接收超时时，把packet_id删除（以后再收到，则会以异步的方式收到）
	* @return 返回0表示成功，否则表示失败，通过调用GetErrorMsg可以获取详细错误信息
	*/
	virtual int FUNCTION_CALL_MODE Receive(int hSend, void **lppData, int *lpnLength, unsigned int uiTimeout, unsigned int uiFlag) = 0;
	
	/**
	* 使用大块数据传输协议发送大块数据
	* @param lpData      待发送数据指针
	* @param uiLength    待发送数据长度
	* @param szComment   关于该数据的说明文字
	* @param uiPieceSize 建议分片的大小
	* @param lpRouteInfo 路由设置，实际类型为IESBMessage *，指定大块传输的接收者
	* @return 0表示失败，否则为该大块数据发送标识
	*/
	virtual int FUNCTION_CALL_MODE BulkSend(const void *lpData, unsigned int uiLength, const char *szComment, unsigned int uiPieceSize, const void *lpRouteInfo) = 0;
	
	/**
	* 使用大块数据传输协议发送文件，目标通过ESBMessage指定
	* @param szFileName  待发送文件名
	* @param szComment   关于该文件的说明文字
	* @param uiPieceSize 建议分片的大小
	* @param lpRouteInfo 路由设置，实际类型为IESBMessage *，指定大块传输的接收者
	* @return 0表示失败，否则为该大块数据发送标识
	*/
	virtual int FUNCTION_CALL_MODE SendFile(const char *szFileName, const char *szComment, unsigned int uiPieceSize, const void *lpRouteInfo) = 0;

	/**
	* 取消大块数据发送
	* @param iBulkSendID 大块数据发送标识
	* @return 0表示成功
	*/
	virtual int FUNCTION_CALL_MODE CancelBulkSend(int iBulkSendID) = 0;

	/**
	* 取消大块数据接收
	* @param iBulkReceiveID 大块数据接收标识
	* @return 0表示成功，否则表示失败，通过调用GetErrorMsg可以获取详细错误信息
	*/
	virtual int FUNCTION_CALL_MODE CancelBulkReceive(int iBulkReceiveID) = 0;

	/**
	* 取服务器地址
	* @param lpPort 输出的服务器端口，可以为NULL
	* @return 返回服务器地址
	*/
	virtual const char * FUNCTION_CALL_MODE GetServerAddress(int *lpPort) = 0;

	/**
	* 取连接状态
	* @return 返回连接状态
	*/
	virtual int FUNCTION_CALL_MODE GetStatus() = 0;

	/**
	* 取服务器负载，使用者可以同时创建多个连接实例同时连接不同的服务器，根据完成连接的时间以及负载决定使用哪个服务器
	* @return 返回服务器负载（非负数），越大表示越繁忙，否则表示失败，通过调用GetErrorMsg可以获取详细错误信息
	*/
	virtual int FUNCTION_CALL_MODE GetServerLoad() = 0;

	/**
	* 取错误码对应的错误信息，目前支持简体中文和英文，支持其他语言可以通过连接对象配置errormsg
	* @param nErrorCode 错误码
	* @return 返回错误信息
	*/
	virtual const char * FUNCTION_CALL_MODE GetErrorMsg(int nErrorCode) = 0;

    /**
    * 取连接错误号，当连接无法与服务端完成注册时，调用该方法可获取错误号，然后用该错误号调用GetErrorMsg
    * 可获取可读的错误信息
    * @return 返回连接错误号
    */
    virtual int FUNCTION_CALL_MODE GetConnectError() = 0;

    /**
    * 发送业务数据
    * @param iFunID      功能号
    * @param lpPacker    打包器指针
    * @param nAsy        0表示同步，否则表示异步。
    * @param iSystemNo   如果iSystemNo > 0则设置系统号
    * @param nCompressID 对业务包体进行压缩的压缩算法ID，目前只支持ID = 1的压缩算法。
    * ID = 0表示不压缩。注意，压缩只是向SDK提出建议，是否真正压缩还取决于包的实际大小。
    * 同步发送的包，通过调用RecvBiz来接收，异步发送的包，当收到应答包后，自动触发回调函数OnReceivedBiz。
    * @return 返回发送句柄（正数），否则表示失败，通过调用GetErrorMsg可以获取详细错误信息
    */
    virtual int FUNCTION_CALL_MODE SendBiz(int iFunID, IF2Packer *lpPacker, int nAsy = 0, int iSystemNo = 0, int nCompressID = 1) = 0;

    /**
    * 接收业务数据
    * @param hSend            发送句柄（SendBiz的成功返回值）
    * @param lppUnPackerOrStr 如果返回值等于0，表示业务数据接收成功，并且业务操作成功，*lppUnPackerOrStr指向一个解包器，此时应首先将该指针转换为IF2UnPacker *。
    *                         如果返回值等于1，表示业务数据接收成功，但业务操作失败了，*lppUnPackerOrStr指向一个解包器，此时应首先将该指针转换为IF2UnPacker *。
    *                         如果返回值等于2，表示收到非业务错误信息，*lppUnPackerOrStr指向一个可读的字符串错误信息。
    *                         如果返回值等于3，表示业务包解包失败。*lppUnPackerOrStr原先所指向的内容不会被改变。
    *						  如果返回值等于4，表示业务包为空。*lppUnPackerOrStr原先所指向的内容不会被改变。
	* @param uiTimeout        超时时间，单位毫秒，0表示不等待。
    * @param uiFlag           接收选项，0表示接收超时后仍可继续调用RecvBiz来接收，
    *                         JustRemoveHandle表示当接收超时后，把hSend相关数据删除
    * @return 小于0表示RecvBiz操作本身失败，通过调用GetErrorMsg可以获取详细错误信息
    * 注意！外部指针所指向的解包器的内存由SDK内部管理，外部切勿释放！
    */
    virtual int FUNCTION_CALL_MODE RecvBiz(int hSend, void **lppUnPackerOrStr, unsigned uiTimeout = 1000, unsigned uiFlag = 0) = 0;

	//20101228 xuxp 导出库的接口名字不可以重名的，否则有不可预知的错误
	//20101129 xuxp 向指定中间件发送请求
	/**
    * 发送业务数据
    * @param iFunID      功能号
    * @param lpPacker    打包器指针
	* @param svrName     指定中间件的节点
    * @param nAsy        0表示同步，否则表示异步。
    * @param iSystemNo   如果iSystemNo > 0则设置系统号
    * @param nCompressID 对业务包体进行压缩的压缩算法ID，目前只支持ID = 1的压缩算法。
    * ID = 0表示不压缩。注意，压缩只是向SDK提出建议，是否真正压缩还取决于包的实际大小。
    * 同步发送的包，通过调用RecvBiz来接收，异步发送的包，当收到应答包后，自动触发回调函数OnReceivedBiz。
    * @return 返回发送句柄（正数），否则表示失败，通过调用GetErrorMsg可以获取详细错误信息
    */
    //virtual int FUNCTION_CALL_MODE SendBiz(int iFunID, IF2Packer *lpPacker, char* svrName, int nAsy = 0, int iSystemNo = 0, int nCompressID = 1) = 0;

	//20101228 xuxp 新增发送和接受的两个接口函数，用于订阅和推送
	/**
    * 发送业务数据
    * @param iFunID      功能号
    * @param lpPacker    打包器指针
	* @param svrName     指定中间件的节点
    * @param nAsy        0表示同步，否则表示异步。
    * @param iSystemNo   如果iSystemNo > 0则设置系统号
    * @param nCompressID 对业务包体进行压缩的压缩算法ID，目前只支持ID = 1的压缩算法。
    * ID = 0表示不压缩。注意，压缩只是向SDK提出建议，是否真正压缩还取决于包的实际大小。
    * 同步发送的包，通过调用RecvBiz来接收，异步发送的包，当收到应答包后，自动触发回调函数OnReceivedBiz。
    * @param branchNo  营业部号。
    * @param lpRequest  请求里面的其他内容，根据结构体定义赋值。
    * @return 返回发送句柄（正数），否则表示失败，通过调用GetErrorMsg可以获取详细错误信息
    */
    virtual int FUNCTION_CALL_MODE SendBizEx(int iFunID, IF2Packer *lpPacker,char* svrName, int nAsy = 0, int iSystemNo = 0, int nCompressID = 1,int branchNo=0,LPREQ_DATA lpRequest=NULL) = 0;
    
	//20110308 xuxp 增加返回值，用来判断TAG_MESSAGE_BODY字段为空的情况
    /**
    * 接收业务数据
    * @param hSend            发送句柄（SendBiz的成功返回值）
    * @param lppUnPackerOrStr 如果返回值等于0，表示业务数据接收成功，并且业务操作成功，*lppUnPackerOrStr指向一个解包器，此时应首先将该指针转换为IF2UnPacker *。
    *                         如果返回值等于1，表示业务数据接收成功，但业务操作失败了，*lppUnPackerOrStr指向一个解包器，此时应首先将该指针转换为IF2UnPacker *。
    *                         如果返回值等于2，表示收到非业务错误信息，*lppUnPackerOrStr指向一个可读的字符串错误信息。
    *                         如果返回值等于3，表示业务包解包失败。*lppUnPackerOrStr原先所指向的内容不会被改变。
	*						  如果返回值等于4，表示业务包为空。*lppUnPackerOrStr原先所指向的内容不会被改变。同时lpRetData结构体的内容还是存在的
    * @param lpRetData 其他需要返回的应答内容，根据需要获取
    * @param uiTimeout        超时时间，单位毫秒，0表示不等待。
    * @param uiFlag           接收选项，0表示接收超时后仍可继续调用RecvBiz来接收，
    *                         JustRemoveHandle表示当接收超时后，把hSend相关数据删除
    * @return 小于0表示RecvBiz操作本身失败，通过调用GetErrorMsg可以获取详细错误信息
    * 注意！外部指针所指向的解包器的内存由SDK内部管理，外部切勿释放！
	* 注意！外部指针所指向的LPRET_DATA的内存由SDK内部管理，外部切勿释放！
    */
    virtual int FUNCTION_CALL_MODE RecvBizEx(int hSend, void **lppUnpackerOrStr, LPRET_DATA* lpRetData, unsigned uiTimeout = 1000, unsigned uiFlag = 0) = 0;


	//20101228 xuxp 新增Create函数，来保证回调用新的OnReceivedBizEx的接口
	/**
	* 初始化连接对象
	* @param lpCallback 回调对象
	* @return 返回0表示成功，否则表示失败，通过调用GetErrorMsg可以获取详细错误信息
    * 如果应用不需要任何回调方法，则可向该方法传递NULL，而不必自定义回调类和对象
	*/
	virtual int FUNCTION_CALL_MODE CreateEx(CCallbackInterface *lpCallback) = 0;

	//20120111 dongpf 新增GetRealAddress函数，来获取服务端上自己的ip地址和端口
	/**
	* 获取ip地址和端口
	* @return 获取ip地址和端口，格式：ip地址+端口
	*/
	virtual const char* FUNCTION_CALL_MODE GetRealAddress() = 0;

	//20120118 dongpf 用以支持SSL模式下读取二进制证书文件（比如UKEY）
    /**
    * 初始化连接对象
    * @param lpCallback 回调对象
    * @param lpCertData 二进制证书文件缓存
    * @param nLength    二进制证书文件长度
    * @param szPWD      证书密码
    * @return 返回0表示成功，否则表示失败，通过调用GetErrorMsg可以获取详细错误信息
      * 如果应用不需要任何回调方法，则可向该方法传递NULL，而不必自定义回调类和对象
    */
	virtual int FUNCTION_CALL_MODE CreateByMemCert(CCallbackInterface *lpCallback, void * lpCertData, int nLength, const char * szPWD) = 0;

	//20130329 xuxp 增加一个Create函数，用于mcapi来调用，在第三方接口里面通过这个标识来标记回调内部的接口
    /**
	* 初始化连接对象，只能用于mcapi
	* @param lpCallback 回调对象
	* @return 返回0表示成功，否则表示失败，通过调用GetErrorMsg可以获取详细错误信息
    * 如果应用不需要任何回调方法，则可向该方法传递NULL，而不必自定义回调类和对象
	*/
	virtual int FUNCTION_CALL_MODE Create2Mcapi(CCallbackInterface *lpCallback) = 0;


	//20130527 xuxp 新增GetSelfAddress函数，来获取自己本地的IP和端口
	/**
	* 获取ip地址和端口
	* @return 获取ip地址和端口，格式：ip地址+端口
	*/
	virtual const char* FUNCTION_CALL_MODE GetSelfAddress() = 0;

	//20130529 xuxp 新增GetSelfMac函数，来获取自己本地使用的网卡MAC
	/**
	* 获取MAC地址
	* @return MAC的地址字符串格式，类似“D067E5556D83”,中间没有分隔符
	*/
	virtual const char* FUNCTION_CALL_MODE GetSelfMac() = 0;

	//20130609 xuxp 新增订阅发布接口
	///////////////////////////////////下面增加订阅发布的接口///////////////////////////////////////

	/**
    * 创建一个订阅者
    * @param lpCallback 回调接口
    * @param SubScribeName 订阅者名字，多订阅者的名字必须不一样，不可以相同.最大长度32个字节
    * @param iTimeOut 超时时间
    * @param iInitRecvQLen 初始化接收队列的长度
    * @param iStepRecvQLen 接受队列的扩展步长
    * @return 返回订阅接口实例，一个会话接口对应一个回调.
    */
    virtual CSubscribeInterface* FUNCTION_CALL_MODE NewSubscriber(CSubCallbackInterface *lpCallback,char* SubScribeName,int iTimeOut,
        int iInitRecvQLen=INIT_RECVQ_LEN,int iStepRecvQLen=STEP_RECVQ_LEN) = 0;
   //20131024 majc 在获取发布者接口中增加业务名参数
   /**
    * 获取发布者
    * @param PublishName 发布者业务名
    * @param msgCount 本地缓存消息的个数
	  * @param iTimeOut 初始化的时候的超时时间
    * @param bResetNo 是否重置序
    * @return 返回发送接口实例，返回对应的指针
    */
    //virtual CPublishInterface* FUNCTION_CALL_MODE GetPublisher(int msgCount,int iTimeOut,bool bResetNo = false) = 0;
    virtual CPublishInterface* FUNCTION_CALL_MODE NewPublisher(char* PublishName,int msgCount,int iTimeOut,bool bResetNo = false) = 0;
  


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
    virtual IF2UnPacker* FUNCTION_CALL_MODE GetTopic(bool byForce,int iTimeOut) = 0;
	
	/**
	* 获取订阅发布的最后错误
	*/
	virtual const char* FUNCTION_CALL_MODE GetMCLastError() = 0;
	////////////////////////////////////////////////////////////////////////////////

	//20130624 xuxp 连接接口增加下面三个接口，用来作为服务端的接口，客户端开发也推荐使用
	///////////////////////////////////新的一套操作接口///////////////////////////////////////
	/**
	* 初始化连接对象
	* @param lpCallback 回调对象
	* @return 返回0表示成功，否则表示失败，通过调用GetErrorMsg可以获取详细错误信息
    * 如果应用不需要任何回调方法，则可向该方法传递NULL，而不必自定义回调类和对象
	*/
	virtual int FUNCTION_CALL_MODE Create2BizMsg(CCallbackInterface *lpCallback) = 0;

	/**
    * 发送业务数据
    * @param lpMsg       业务消息接口指针
    * @param nAsy        0表示同步，否则表示异步。
    * 同步发送的包，通过调用RecvBizMsg来接收，异步发送的包，当收到应答包后，自动触发回调函数OnReceivedBizMsg。
    * @return 返回发送句柄（正数），否则表示失败，通过调用GetErrorMsg可以获取详细错误信息
    */
	virtual int FUNCTION_CALL_MODE SendBizMsg(IBizMessage* lpMsg,int nAsy = 0) = 0;
	
	/**
	* 接收数据
	* @param hSend     发送句柄
	* @param lpMsg	   收到业务消息指针的地址
	* @param uiTimeout 超时时间，单位毫秒，0表示不等待
	* @param uiFlag    接收选项，0表示接收超时后仍可继续调用Receive来接收，
    *                  JustRemoveHandle表示当接收超时时，把packet_id删除（以后再收到，则会以异步的方式收到）
	* @return 返回0表示成功，否则表示失败，通过调用GetErrorMsg可以获取详细错误信息
	*/
	virtual int FUNCTION_CALL_MODE RecvBizMsg(int hSend, IBizMessage** lpMsg, unsigned uiTimeout = 1000, unsigned uiFlag = 0) = 0;

	/**
    * 获取文件更新,一个连接里面只有一个文件更新，如果存在就返回之前的接口
    * @param szTopicName 文件更新主题，来自于服务端消息中心文件更新主题 
	* @param lpCallBack 回调接口
	* @param szScanDir 扫描文件根目录
    * @param szUpdateDir 文件更新存放根目录
	* @param iTimeOut 超时时间
    * @return 返回文件更新接口指针
    */
    virtual CFileUpdateInterface* FUNCTION_CALL_MODE NewFileUpdate(const char* szTopicName,CFileUpdateCallbackInterface* lpCallBack ,const char* szScanDir,const char* szUpdateDir,unsigned int uiTimeOut = 5000) = 0;
	/**
	* 获取文件更新的最后错误
	*/
	virtual const char* FUNCTION_CALL_MODE GetFileUpdateLastError() = 0;
	//20140609 majc 增加获取最后一个应答错误的详细信息接口
	/**
	* 取返回错误消息的详细信息
	* @param bAsyError 0表示同步(默认)，否则表示异步。
	* @return 返回详细错误信息
	* @note 返回信息格式：packType:xxx;funtionId:xxx;branchNo:zxx;systemNo:xxx;subSystemNO:xxx;packId:xxx;routerInfo:xxx,xxx,xxx,xxx,xxx,xxx;sendPath:xxx,xxx,xxx,xxx,xxx,xxx;returnCode:xxx;errorNo:xxx;errorInfo:xxx
	* packType-包类型
	* funtionId-功能号
	* branchNo-分支号
	* systemNo-系统号
	* subSystemNO-子系统号
	* packId-包序号
	* routerInfo-目标路由
	* sendPath-发送者路由
	* returnCode-返回错误码
	* errorNo-错误号
	* errorInfo-错误信息
	* 调用说明：1：同步调用时，方法Receive返回的lppData解析ESBMessage后RetuenCode不为0时调用；方法RecvBiz、RecvBizEx是在返回值为1、2、3、4时调用；方法RecvBizMsg是在GetReturnCode()不为0时调用
	*           2：异步调用时，回调OnReceived的lpData解析ESBMessage后RetuenCode不为0时调用；回调OnReceivedBiz、OnReceivedBizEx的nResult为1、2、3、4时调用；回调OnReceivedBizMsg的lpMsg在GetReturnCode()不为0时调用
	*/
	virtual const char * FUNCTION_CALL_MODE GetLastAnsError(bool bAsyError = 0) = 0;
	////////////////////////////////////////////////////////////////////////////////
};

#endif // _CONNECTION_INTERFACE_H_
