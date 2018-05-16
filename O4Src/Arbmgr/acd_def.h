///�����Ŷӻ����ͷ�ļ�����
/**
 *Դ��������:acd_def.h
 *�������Ȩ:�������ӹɷ����޹�˾
 *ϵͳ����:�Ŷӻ�
 *ģ������:Include
 *����˵��:���ͷ�ļ�����
 *��    ��: dongpf
 *��������: 
 *��    ע: 
 */
#ifndef __ACD_DEF_H__
#define __ACD_DEF_H__
#include <os/config_env.h>
#include <Include/inttypes.h>
#include <os/memshared.h>

USING_FBASE2_NAMESPACE

//���׹����ڴ�����
#define TRADE_SHARE_NAME      "tradeACDShm"

//״̬�����ڴ�
#define STATUS_SHARE_NAME     "statusACDShm"

//�Ŷӻ������ڴ�����
#define ACD_MON_SHARE_NAME     ".acd"

//�ٲô������ڴ�����
#define ARBPROXY_MON_SHARE_NAME     ".arbproxy"

//�ٲû������ڴ�����
#define ARB_MON_SHARE_NAME     ".arb"

//�����¼�����
#define EVENT_QUEUE           "acd_event_queue"

//�ٲý������
#define ARB_RESULT_QUEUE      "arb_result_queue"

//�Ŷӻ�״̬����
#define MASK_MACHINE_STATUS   0x0F

//�Ŷӻ��ڲ�״̬����
#define MASK_INTER_STATUS   0xF0

//������
#define CHECK_HEARTBEAT   0

#define MAX_RM_COUNT   255

///20151216 huxb ��rm_adapter_def.h��Ų���˴�����
#define MAX_RM3_RM_COUNT 0xFFFF

#define MAX_SESSION_COUNT 0xFF

#define RM3_SHIFT_COUNT 8
///

//����ַ����
#define MAX_ADDRESS_FILE_LEN  255

//���׹����ڴ�Ĭ�Ϸ�Ƭ��С
#define DEFAULT_SEGMENT_SIZE 1024

//����׹����Ƭ����
#define MAX_SEGMENT_COUNT  256

//д��־
#ifndef ACD_WRITE_LOG
#define ACD_WRITE_LOG  if (m_lpOwner->m_lpLogService) m_lpOwner->m_lpLogService->AddLocalLog 
#endif

//�ֽڶ���
#define ACDALIGN(size, boundary) \
 (((size) + ((boundary) - 1)) & ~((boundary) - 1))

//�Ŷӻ�״̬
enum ACD_MACHINE_STATUS
{
	ACD_NONE               = 0x00,             //��״̬
	ACD_INIT               = 0x01,             //��ʼ״̬
	ACD_SINGLE	           = 0x02,             //����״̬
	ACD_PREPARE	           = 0x03,             //����׼��״̬
	ACD_ACTIVE	           = 0x04,             //����״̬
	ACD_INACTIVE           = 0x05,             //����״̬
	ACD_SEPARATE           = 0x06,             //�˳�״̬
	ACD_SINGLE_TO_ACTIVE   = 0x07,             //����ת����׼��״̬
	ACD_ERROR              = 0x08              //����״̬���Ŷӻ�����ʧ���Ժ��״̬
};

enum ACD_INTER_STATUS
{
	ACD_CLEAR              = 0x10,             //����״̬
	ACD_NORMAL             = 0x20,             //����״̬	
	ACD_DEBUG              = 0x30              //����״̬
};

//����ģʽ
enum ACD_START_MODEL
{
	START_MODEL_ARBPROXY   = 0x00,             //�ٲô���ģʽ
	START_MODEL_LOCAL      = 0x01              //����ģʽ
};

//�Ŷӻ�״̬��
static const char * g_lpStatusName[20] = 
{
	"NONE",                 //��״̬
	"INIT",                 //��ʼ״̬
	"SINGLE",               //����״̬
	"PREPARE",              //����׼��״̬
	"ACTIVE",               //����״̬
	"INACTIVE",             //����״̬
	"SEPARATE",             //�˳�״̬
	"SINGLE_TO_ACTIVE",     //����ת����׼��״̬
	"ERROR",                //����״̬ 
	"","","","","","","",   //����ֵ
	"CLEAR",                //����״̬
	"NORMAL",               //����״̬
	"DEBUG"                 //����״̬
};



//����������
enum  ADAPTER_TYPE
{
    ADAPTER_TYPE_RM			= 0,			//�鲥
    ADAPTER_TYPE_BROADCAST	= 1,			//�㲥
    ADAPTER_TYPE_TCP		= 2,			//TCP
    ADAPTER_TYPE_SIGNAL		= 3,			//�ź�
    ADAPTER_TYPE_MSG_QUEUE	= 4,			//��Ϣ����
    ADAPTER_TYPE_PLUGIN		= 5,			//hsserver���
	ADAPTER_TYPE_TIME		= 6,			//ʱ��Ƭ
	ADAPTER_TYPE_UDP		= 7,			//UDP������
    ADAPTER_TYPE_UNKNOW		= 8				//δ֪����
};

//����������
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

//�������
enum PLUGIN_TYPE
{
	PLUGIN_TYPE_CORE       = 7,             //���Ĳ��
	PLUGIN_TYPE_QUEUE      = 8,             //�ŶӲ��
	PLUGIN_TYPE_MONITOR    = 9              //��ش�����
};

//ҵ�����ͣ�
enum BIZ_TYPE
{
	BIZ_TYPE_NONE          = 0,             //���κ�ҵ������
	BIZ_TYPE_NORMAL        = 1,             //��ͨ���ģ�ί��/�ɽ�/��ʼ�����ݵȣ�
	BIZ_TYPE_SYNC          = 2,             //��ͬ��
	BIZ_TYPE_SYNC_ACK      = 3,             //��ͬ��ȷ��
	BIZ_TYPE_SYNC_STATUS   = 4,             //����ͬ����ʱ�㱨״̬
	BIZ_TYPE_TRADE         = 5,             //���ݸ���������
	BIZ_TYPE_BAK_SYNC      = 6,             //��ͬ��
	BIZ_TYPE_BAK_UPDATE    = 7,             //��ͬ�������鲥�������
	BIZ_TYPE_SEND_NEW_COMM = 8,             //֪ͨ�µ�ͨ�Ž׶κ�
	BIZ_TYPE_NEW_COMM      = 9,             //�µ�ͨ�Ž׶κ�
	BIZ_TYPE_CLEAR         = 10,            //����rm���ڴ�
	BIZ_TYPE_FRONT_STATUS  = 11,            //ǰ�ö�ʱ�㱨״̬
	BIZ_TYPE_TRADE_STATUS  = 12,            //���׶�ʱ�㱨״̬
	BIZ_TYPE_HOST_STATUS   = 13,            //����ͬ����ʱ�㱨״̬
	BIZ_TYPE_BAK_ACK	   = 14,            //����ͬ��ȷ��
	BIZ_TYPE_RESET_COMM    = 15,            //����ͨ�Ž׶κ�
	BIZ_TYPE_RECV_RESET    = 16,            //�յ����ý׶κ�
	BIZ_TYPE_ALARM         = 17,            //�澯
	BIZ_TYPE_ARB           = 18,            //�ٲ���Ϣ
	BIZ_TYPE_TO_HSSERVER   = 19,            //��hsserver��Ϣ
	BIZ_TYPE_FROM_HSSERVER = 20             //��hsserver������Ϣ
	
};

//�澯����
enum ALARM_TYPE
{
	ALARM_TYPE_SYNC_COMPLETED    = 0,       //�뱸��ͬ�����
	ALARM_TYPE_SYNC_FAILED       = 1,       //�뱸��ͬ��ʧ��
	ALARM_TYPE_ARB_ACK           = 2,       //�ٲ�ȷ��
	ALARM_TYPE_ARB_NACK          = 3,       //�ٲ�ʧ��
	ALARM_TYPE_NONE_FRONT        = 4,       //ǰ��������
	ALARM_TYPE_NONE_TRADE        = 5,       //����������
	ALARM_TYPE_NONE_HOST         = 6        //����ͬ������
};

enum ACD_CONN_STATUS
{
	ACD_CONN_STATUS_CLOSED    = 0,         //���ӶϿ�
	ACD_CONN_STATUS_CONNECTED = 1          //������
};

//�������Ӧ��
enum ACD_REQ_ANS_PACK
{
	ACD_PACK_REQ              = 0,        //����
	ACD_PACK_ANS              = 1         //Ӧ��
};

//��������ͷ
typedef struct PriMsg
{
	uint32   dwLength;           //���ĳ���
	uint8    byAdapterType;      //����������
	uint8    byReqOrAns;         //�������Ӧ��
	uint8    byBizType;          //ҵ������
	uint8    byPriority;         //���ȼ���Լ��0-2��Ĭ����1
	uint32   dwID;               //�Զ����ţ��鲥��/���Ӻ�
	uint32   dwID2;              //�Զ�����2, һ����ͨ�Ž׶κŻ�������״̬
	uint32   dwPacketId;         //����š�
	int32    iTimeStamp;         //����ʱ���
	PriMsg * lpNext;             //��һ������
	void   * lpBuffer;           //���յı���
	PriMsg(){memset(this,0,sizeof(*this));}
}AdapterHeader;

///20151211 huxb uft2.0ͷ���ṹ�޸�
//uft2.0��ͷ
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

//��Ϣ���б���
typedef struct tgMsgQueueHead
{
	uint32 dwPackId;                 //�����
	uint32 dwResult;                 //���
}MsgQueueHead;

//�����ڴ泤��
typedef struct tgShmBufHead
{
	uint32         dwBufLen;      //���ĳ��ȣ���8�ֽڶ��룬������tgShmBufHead
	uint32         dwLastFlag;    //��ǰ��Ƭ�е����һ������
}ShmBufHead;

//����
#define SHM_HEAD_LEN   sizeof(ShmBufHead)

/* rm_msg��tag�� */
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

//���һ��Ƭ������
#define ACD_LAST_FLAG  36485

//���׹����ڴ��Ƭ��Ϣ
typedef struct tgShmSegMentInfo
{
	char        * lpTradeMem;      //�����ڴ棬���Թ����ڴ�
	CSharedMem  * lpTradeShm;      //���׹����ڴ���
	uint32        dwTradeMemLen;   //���׹����ڴ�ĳ���	
	uint32        dwReverse;       //ռλ
}ShmSegMentInfo;

//�鲥���
typedef struct tgRmRecvInfo
{
	uint32        dwCommNo;       //ͨ�Ž׶κ�
	uint32        dwIndex;        //���
}RmRecvInfo;

//�Ŷӻ������ڴ�ά��״̬
struct tgShmAcdStatus
{
	uint32         m_dwCurrentIndex;         //��ǰ���
	uint32         m_dwConfirmIndex;         //ȷ�����
	uint8          m_byMachineStatus;        //��ǰ״̬
	uint8          m_bySyncConnectStatus;    //ͬ������״̬, 0�������ӿ��ɣ�1��������
	uint8          m_byFrontConnectStatus;   //ǰ������״̬, 0�������ӿ��ɣ�1��������
	uint8          m_byTradeConnectStatus;   //��������״̬, 0�������ӿ��ɣ�1��������
	int32          m_iCurrentTime;           //�Ŷӻ�ʱ��
	uint32         m_dwCurSegUseLen;         //��ǰ��Ƭʹ���ڴ��С
	uint32         m_dwConfirmSegLen;        //��ǰ�Ѿ���ȷ�Ϸ�Ƭ�����ڴ��С�����Ա�����������
	uint32         m_dwBeginSegOffset;       //��ʼ��Ƭ��ƫ����
	uint8          m_byCurSegNo;             //��ǰ����ʹ�õķ�Ƭ��
	uint8          m_byConfirmSegNo;         //��ǰ���ڱ�ȷ�Ϸ�Ƭ��
	uint8          m_byBeginSegNo;           //��ʼ��Ƭ��
	uint8          m_byStartModel;           //����ģʽ���ٲ�ģʽ������ģʽ
	uint8          m_byMaxSegCount;          //����Ƭ��
	uint8          m_byReverse[3];           //ռλ��
	uint32         m_dwToClearCommNo;        //�´�����ͨ�Ž׶κ�
	uint32         m_dwCurrentCommNo;        //��ǰͨ�Ž׶κ�
	uint32         m_dwSegmentSize;          //��Ƭ�ڴ��С
	int64          m_i64StartTime;           //����ʱ��
	int32          m_ipid;                   //�Ŷӻ����̺�
	RmRecvInfo     m_aReceiveInfos[MAX_RM_COUNT]; //��������ͨ�鲥�������ţ������ǵ�ǰ����ʱ��
};


struct ShmAcdStatus : public tgShmAcdStatus
{
	//20151211 huxb �����޸ļ�ؽṹ(tgShmAcdStatus)���������ݳ�Ա
	///�Ŷ�����
	int32			m_iCurrentDate;
	///20151216 �°��鲥�У�ÿ����ͨ�鲥������ж���Ự��֮ǰ�����ݽṹ�����Ա���������ͨ�鲥�����Ϣ
	RmRecvInfo		m_aReceiveInfosEx[MAX_RM3_RM_COUNT + 1];

	/* ����״̬ */
	void ResetStatus()
	{	
		m_iCurrentTime = -1;
		///20151211 huxb �Ŷ�ʱ�临λ
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
	
	/* ������� */
	void ResetIndex()
	{
		m_dwCurrentIndex = (uint32)-1;         //��ǰ���
		m_dwConfirmIndex = (uint32)-1;         //ȷ�����
	}
};

///20160117 huxb �ٲô���ע��״̬��0-δע�ᡢ2-��ע��
enum ARBPROXY_REGISTER_STATUS{
	ARBPROXY_UNREGISTER = 0,
	//ARBPROXY_REGISTERING = 1,
	ARBPROXY_REGISTERED = 2
};

#endif
