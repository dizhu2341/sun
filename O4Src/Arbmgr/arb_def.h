///恒生仲裁机相关头文件定义
/**
 *源程序名称:arb_def.h
 *软件著作权:恒生电子股份有限公司
 *系统名称:仲裁机
 *模块名称:Include
 *功能说明:相关头文件定义
 *作    者: dongpf
 *开发日期: 
 *备    注: 
 */
#ifndef __ARB_DEF_H__
#define __ARB_DEF_H__
#include <Include/inttypes.h>
#include "acd_def.h"

#define   ACD_NUM     2
//状态共享内存
#define STATUS_ARB_SHARE_NAME     "statusARBShm"

//尝试发送次数
#define SEND_TRY_COUNT  3

//发送超时时间
#define SEND_WAIT_TIMEOUT  2000

//文件名长度
#define   MAX_ARB_FILE_LEN   255

//报文协议包头
typedef struct tgARBHeader
{
	uint8          byReqOrAns;     //请求或者应答
	uint8          byMsgType;      //消息类型
	uint8          byHostID;       //排队机编号
	uint8          byResultType;   //结果类型， 0普通，1强制
	uint32         dwPacketId;     //包序号，通过序号的大小来控制仲裁命令顺序。
	uint32         dwArbPackNo;    //仲裁序号。同一个仲裁序号代表同一个仲裁消息。
	uint32         dwAlarmPackNo;  //告警的编号。
	uint8          byCurStatus;    //报告当前状态
	uint8          byStartStatus;  //20150812 dongpf 增加启动状态，带流、清流、重演
	uint8          byReverse2;     //备2
	uint8          byReverse3;     //备3
	uint32         dwCurQueueNo;   //20150812 dongpf 增加当前排队序号
}ARBHeader;
	

//消息类型
enum ARBMsgType
{
	SWITCH_TO_SINGLE   = 2,    //仲裁机 -> 排队机, 指示排队机切换到SINGLE状态	
	SWITCH_TO_PREPARE  = 3,    //仲裁机 -> 排队机, 指示排队机切换到PREPARE状态
	SWITCH_TO_ACTIVE   = 4,    //仲裁机 -> 排队机, 指示排队机切换到ACTIVE状态
	SWITCH_TO_INACTIVE = 5,    //仲裁机 -> 排队机, 指示排队机切换到INACTIVE状态	
	SWITCH_TO_SEPARATE = 6,    //仲裁机 -> 排队机, 指示排队机从集群中分离
	RECV_ACK           = 7,    //仲裁机 -> 排队机, 代表收到告警，但是未作出抉择
	REGISTER_ACD       = 10,   //排队机 -> 仲裁机, 注册一个排队机
	APP_STOP           = 11,   //排队机 -> 仲裁机, 应用崩溃告警
	SYNC_COMPLETED     = 12,   //排队机 -> 仲裁机, 历史同步完成消息
	SYNC_FAILED        = 13,   //排队机 -> 仲裁机, 同步失败告警	
	ACK                = 14,   //排队机 -> 仲裁机, 切换完成
	NACK               = 15,   //排队机 -> 仲裁机, 拒绝切换或者切换失败	
	NONE_FRONT         = 16,   //排队机 -> 仲裁机, 前置网故障的告警
	NONE_TRADE         = 17,   //排队机 -> 仲裁机, 交易网故障的告警
	NONE_HOST          = 18,   //排队机 -> 仲裁机，主机网故障的告警，由备机发起
	ARB_STOP           = 19    //仲裁机自己停止
	//LOST_ACD_CONNECT   = 31    //仲裁机自己，丢失排队机的连接
};

//消息类型描述
static const char * g_lpArbMsgName[21] = 
{
	"",                     //无状态
	"",                     //无状态
	"TO_SINGLE",            //切换到SINGLE状态
	"TO_PREPARE",           //切换到SINGLE状态
	"TO_ACTIVE",            //切换到SINGLE状态
	"TO_INACTIVE",          //切换到SINGLE状态
	"TO_SEPARATE",          //切换到SINGLE状态状态
	"RECV_ACK",             //告警应答
	"",                     //无状态
	"",                     //无状态
	"REGISTER_ACD",         //注册排队机
	"APP_STOP",             //应用崩溃告警
	"SYNC_COMPLETED",       //同步完成消息
	"SYNC_FAILED",          //同步失败告警	
	"ACK",                  //切换完成
	"NACK",                 //切换失败	
	"NONE_FRONT",           //前置网故障告警
	"NONE_TRADE",           //交易网故障告警
	"NONE_HOST",            //主机网故障的告警
	"ARB_STOP",             //仲裁机停止
	""                      //无状态
};

//结果类型
enum ARBResult
{
	RESULT_TYPE_NORMAL = 0,     //普通
	RESULT_TYPE_FORCE  = 1      //强制发送
};

// 排队机状态结构定义
typedef struct tgAcdStatus  
{               
    uint8      byAcdId;              // 排队机标示ID
    uint8      byMachineStatus;      // 排队机状态
    bool       bUsable;              // 可用标记 true:可用， 
	uint8      byLastStop;            // 两个排队机中最后一个停止的
}AcdStatus;

typedef struct tgOneDecision
{
	AcdStatus  astatus;
	uint32     dwAlarmNo;
	uint32     dwArbPackNo;
}OneDecision, AcdStatusInfo;

#endif
