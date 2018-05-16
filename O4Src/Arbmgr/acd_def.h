///恒生排队机相关头文件定义
/**
 *源程序名称:acd_def.h
 *软件著作权:恒生电子股份有限公司
 *系统名称:排队机
 *模块名称:Include
 *功能说明:相关头文件定义
 *作    者: dongpf
 *开发日期: 
 *备    注: 
 */
#ifndef __ACD_DEF_H__
#define __ACD_DEF_H__
#include <os/config_env.h>
#include <Include/inttypes.h>
#include <os/memshared.h>

USING_FBASE2_NAMESPACE

//交易共享内存名称
#define TRADE_SHARE_NAME      "tradeACDShm"

//状态共享内存
#define STATUS_SHARE_NAME     "statusACDShm"

//排队机共享内存名称
#define ACD_MON_SHARE_NAME     ".acd"

//仲裁代理共享内存名称
#define ARBPROXY_MON_SHARE_NAME     ".arbproxy"

//仲裁机共享内存名称
#define ARB_MON_SHARE_NAME     ".arb"

//有名事件队列
#define EVENT_QUEUE           "acd_event_queue"

//仲裁结果队列
#define ARB_RESULT_QUEUE      "arb_result_queue"

//排队机状态掩码
#define MASK_MACHINE_STATUS   0x0F

//排队机内部状态掩码
#define MASK_INTER_STATUS   0xF0

//有心跳
#define CHECK_HEARTBEAT   0

#define MAX_RM_COUNT   255

///20151216 huxb 从rm_adapter_def.h中挪到此处定义
#define MAX_RM3_RM_COUNT 0xFFFF

#define MAX_SESSION_COUNT 0xFF

#define RM3_SHIFT_COUNT 8
///

//最大地址长度
#define MAX_ADDRESS_FILE_LEN  255

//交易共享内存默认分片大小
#define DEFAULT_SEGMENT_SIZE 1024

//最大交易共享分片个数
#define MAX_SEGMENT_COUNT  256

//写日志
#ifndef ACD_WRITE_LOG
#define ACD_WRITE_LOG  if (m_lpOwner->m_lpLogService) m_lpOwner->m_lpLogService->AddLocalLog 
#endif

//字节对齐
#define ACDALIGN(size, boundary) \
 (((size) + ((boundary) - 1)) & ~((boundary) - 1))

//排队机状态
enum ACD_MACHINE_STATUS
{
	ACD_NONE               = 0x00,             //无状态
	ACD_INIT               = 0x01,             //初始状态
	ACD_SINGLE	           = 0x02,             //单机状态
	ACD_PREPARE	           = 0x03,             //备机准备状态
	ACD_ACTIVE	           = 0x04,             //主机状态
	ACD_INACTIVE           = 0x05,             //备机状态
	ACD_SEPARATE           = 0x06,             //退出状态
	ACD_SINGLE_TO_ACTIVE   = 0x07,             //单机转主机准备状态
	ACD_ERROR              = 0x08              //错误状态，排队机启动失败以后的状态
};

enum ACD_INTER_STATUS
{
	ACD_CLEAR              = 0x10,             //清流状态
	ACD_NORMAL             = 0x20,             //正常状态	
	ACD_DEBUG              = 0x30              //重演状态
};

//启动模式
enum ACD_START_MODEL
{
	START_MODEL_ARBPROXY   = 0x00,             //仲裁代理模式
	START_MODEL_LOCAL      = 0x01              //本地模式
};

//排队机状态名
static const char * g_lpStatusName[20] = 
{
	"NONE",                 //无状态
	"INIT",                 //初始状态
	"SINGLE",               //单机状态
	"PREPARE",              //备机准备状态
	"ACTIVE",               //主机状态
	"INACTIVE",             //备机状态
	"SEPARATE",             //退出状态
	"SINGLE_TO_ACTIVE",     //单机转主机准备状态
	"ERROR",                //错误状态 
	"","","","","","","",   //其他值
	"CLEAR",                //清流状态
	"NORMAL",               //带流状态
	"DEBUG"                 //重演状态
};



//适配器类型
enum  ADAPTER_TYPE
{
    ADAPTER_TYPE_RM			= 0,			//组播
    ADAPTER_TYPE_BROADCAST	= 1,			//广播
    ADAPTER_TYPE_TCP		= 2,			//TCP
    ADAPTER_TYPE_SIGNAL		= 3,			//信号
    ADAPTER_TYPE_MSG_QUEUE	= 4,			//消息队列
    ADAPTER_TYPE_PLUGIN		= 5,			//hsserver插件
	ADAPTER_TYPE_TIME		= 6,			//时间片
	ADAPTER_TYPE_UDP		= 7,			//UDP适配器
    ADAPTER_TYPE_UNKNOW		= 8				//未知类型
};

//适配器描述
static const char * g_lpAdapterDescribe[9] = 
{
	"RM ADAPTER",	
	"BROADCAST ADAPTER",	
	"TCP ADAPTER",	
	"SIGNAL ADAPTER",	
	"MSG QUEUE ADAPTER",
	"PLUGIN ADAPTER",	
	"TIME ADAPTER",
	"UDP ADAPTER",
	""
};

//插件类型
enum PLUGIN_TYPE
{
	PLUGIN_TYPE_CORE       = 7,             //核心插件
	PLUGIN_TYPE_QUEUE      = 8,             //排队插件
	PLUGIN_TYPE_MONITOR    = 9              //监控代理插件
};

//业务类型：
enum BIZ_TYPE
{
	BIZ_TYPE_NONE          = 0,             //无任何业务意义
	BIZ_TYPE_NORMAL        = 1,             //普通报文（委托/成交/初始化数据等）
	BIZ_TYPE_SYNC          = 2,             //主同步
	BIZ_TYPE_SYNC_ACK      = 3,             //主同步确认
	BIZ_TYPE_SYNC_STATUS   = 4,             //主备同步定时汇报状态
	BIZ_TYPE_TRADE         = 5,             //传递给交易中心
	BIZ_TYPE_BAK_SYNC      = 6,             //备同步
	BIZ_TYPE_BAK_UPDATE    = 7,             //备同步更新组播接收序号
	BIZ_TYPE_SEND_NEW_COMM = 8,             //通知新的通信阶段号
	BIZ_TYPE_NEW_COMM      = 9,             //新的通信阶段号
	BIZ_TYPE_CLEAR         = 10,            //清理rm的内存
	BIZ_TYPE_FRONT_STATUS  = 11,            //前置定时汇报状态
	BIZ_TYPE_TRADE_STATUS  = 12,            //交易定时汇报状态
	BIZ_TYPE_HOST_STATUS   = 13,            //备机同步定时汇报状态
	BIZ_TYPE_BAK_ACK	   = 14,            //备机同步确认
	BIZ_TYPE_RESET_COMM    = 15,            //重置通信阶段号
	BIZ_TYPE_RECV_RESET    = 16,            //收到重置阶段号
	BIZ_TYPE_ALARM         = 17,            //告警
	BIZ_TYPE_ARB           = 18,            //仲裁消息
	BIZ_TYPE_TO_HSSERVER   = 19,            //给hsserver消息
	BIZ_TYPE_FROM_HSSERVER = 20             //从hsserver来的消息
	
};

//告警类型
enum ALARM_TYPE
{
	ALARM_TYPE_SYNC_COMPLETED    = 0,       //与备机同步完毕
	ALARM_TYPE_SYNC_FAILED       = 1,       //与备机同步失败
	ALARM_TYPE_ARB_ACK           = 2,       //仲裁确认
	ALARM_TYPE_ARB_NACK          = 3,       //仲裁失败
	ALARM_TYPE_NONE_FRONT        = 4,       //前置网故障
	ALARM_TYPE_NONE_TRADE        = 5,       //交易网故障
	ALARM_TYPE_NONE_HOST         = 6        //主机同步故障
};

enum ACD_CONN_STATUS
{
	ACD_CONN_STATUS_CLOSED    = 0,         //连接断开
	ACD_CONN_STATUS_CONNECTED = 1          //已连接
};

//请求或者应答
enum ACD_REQ_ANS_PACK
{
	ACD_PACK_REQ              = 0,        //请求
	ACD_PACK_ANS              = 1         //应答
};

//适配器包头
typedef struct PriMsg
{
	uint32   dwLength;           //报文长度
	uint8    byAdapterType;      //适配器类型
	uint8    byReqOrAns;         //请求或者应答
	uint8    byBizType;          //业务类型
	uint8    byPriority;         //优先级，约定0-2，默认是1
	uint32   dwID;               //自定义编号，组播号/连接号
	uint32   dwID2;              //自定义编号2, 一般是通信阶段号或者连接状态
	uint32   dwPacketId;         //包序号。
	int32    iTimeStamp;         //接收时间戳
	PriMsg * lpNext;             //下一个报文
	void   * lpBuffer;           //接收的报文
	PriMsg(){memset(this,0,sizeof(*this));}
}AdapterHeader;

///20151211 huxb uft2.0头部结构修改
//uft2.0包头
typedef struct tagESBHead
{
	uint32 m_iPackType:6;
	uint32 m_iTimeStampFlag:4;
	uint32 m_iMsgOffset:22;

	uint32 m_iPackLen;
	uint32 m_iFuncID;
	uint32 m_iPackID;
	uint32 m_iReturnCode;
	uint32 m_iSenderID;
	uint8  m_iPriority;
	uint8  m_iReverse;
	uint16 m_iRmGroupNO;
	uint32 m_iCommNO;
	uint32 m_iRmNO;
	uint32 m_iQueueNO;
	uint32 m_iQueueTime;

	uint32 m_iQueueDate;
	uint32 m_iReserve1;
	uint32 m_iReserve2;
	uint32 m_iReserve3;
	uint32 m_iReserve4;

}UFT2Head;

//消息队列报文
typedef struct tgMsgQueueHead
{
	uint32 dwPackId;                 //包序号
	uint32 dwResult;                 //结果
}MsgQueueHead;

//共享内存长度
typedef struct tgShmBufHead
{
	uint32         dwBufLen;      //报文长度，按8字节对齐，不包含tgShmBufHead
	uint32         dwLastFlag;    //当前分片中的最后一个报文
}ShmBufHead;

//长度
#define SHM_HEAD_LEN   sizeof(ShmBufHead)

/* rm_msg的tag域 */
union tagHeadInfo 
{
	struct tagHead
	{
		uint32 m_iType:2;
		uint32 m_iTag:6;
		uint32 m_iLen:24;
	}head;
	uint32 m_iVal;
};

#define UFT2_TAG_TIMESTAMP   3

#define BEGIN_TIME_STAMP   "star queue"

#define END_TIME_STAMP   "queue over"  

#define TIME_STAMP_LEN   (11 + 2 + 11)

//最后一分片特征码
#define ACD_LAST_FLAG  36485

//交易共享内存分片信息
typedef struct tgShmSegMentInfo
{
	char        * lpTradeMem;      //交易内存，来自共享内存
	CSharedMem  * lpTradeShm;      //交易共享内存句柄
	uint32        dwTradeMemLen;   //交易共享内存的长度	
	uint32        dwReverse;       //占位
}ShmSegMentInfo;

//组播序号
typedef struct tgRmRecvInfo
{
	uint32        dwCommNo;       //通信阶段号
	uint32        dwIndex;        //序号
}RmRecvInfo;

//排队机共享内存维护状态
struct tgShmAcdStatus
{
	uint32         m_dwCurrentIndex;         //当前序号
	uint32         m_dwConfirmIndex;         //确认序号
	uint8          m_byMachineStatus;        //当前状态
	uint8          m_bySyncConnectStatus;    //同步网络状态, 0代表连接可疑，1代表正常
	uint8          m_byFrontConnectStatus;   //前置网络状态, 0代表连接可疑，1代表正常
	uint8          m_byTradeConnectStatus;   //交易网络状态, 0代表连接可疑，1代表正常
	int32          m_iCurrentTime;           //排队机时间
	uint32         m_dwCurSegUseLen;         //当前分片使用内存大小
	uint32         m_dwConfirmSegLen;        //当前已经被确认分片共享内存大小，用以备机回退所用
	uint32         m_dwBeginSegOffset;       //起始分片的偏移量
	uint8          m_byCurSegNo;             //当前正在使用的分片号
	uint8          m_byConfirmSegNo;         //当前正在被确认分片号
	uint8          m_byBeginSegNo;           //起始分片号
	uint8          m_byStartModel;           //启动模式：仲裁模式，本地模式
	uint8          m_byMaxSegCount;          //最大分片数
	uint8          m_byReverse[3];           //占位用
	uint32         m_dwToClearCommNo;        //下次清理通信阶段号
	uint32         m_dwCurrentCommNo;        //当前通信阶段号
	uint32         m_dwSegmentSize;          //分片内存大小
	int64          m_i64StartTime;           //启动时间
	int32          m_ipid;                   //排队机进程号
	RmRecvInfo     m_aReceiveInfos[MAX_RM_COUNT]; //备机是普通组播组接收序号，主机是当前接收时间
};


struct ShmAcdStatus : public tgShmAcdStatus
{
	//20151211 huxb 避免修改监控结构(tgShmAcdStatus)，新增数据成员
	///排队日期
	int32			m_iCurrentDate;
	///20151216 新版组播中，每个普通组播组可能有多个会话，之前的数据结构不足以保存所有普通组播组的信息
	RmRecvInfo		m_aReceiveInfosEx[MAX_RM3_RM_COUNT + 1];

	/* 重置状态 */
	void ResetStatus()
	{	
		m_iCurrentTime = -1;
		///20151211 huxb 排队时间复位
		m_iCurrentDate = -1;

		m_dwCurSegUseLen = 0;
		m_dwConfirmSegLen = 0;
		m_byCurSegNo = 0;
		m_byConfirmSegNo = 0;
		m_dwCurrentCommNo = 0;
		m_dwBeginSegOffset = 0;
		m_byBeginSegNo = 0;
		m_dwToClearCommNo = 0;
		ResetIndex();
	}
	
	/* 重置序号 */
	void ResetIndex()
	{
		m_dwCurrentIndex = (uint32)-1;         //当前序号
		m_dwConfirmIndex = (uint32)-1;         //确认序号
	}
};

///20160117 huxb 仲裁代理注册状态，0-未注册、2-已注册
enum ARBPROXY_REGISTER_STATUS{
	ARBPROXY_UNREGISTER = 0,
	//ARBPROXY_REGISTERING = 1,
	ARBPROXY_REGISTERED = 2
};

#endif
