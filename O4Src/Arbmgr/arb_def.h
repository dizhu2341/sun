///�����ٲû����ͷ�ļ�����
/**
 *Դ��������:arb_def.h
 *�������Ȩ:�������ӹɷ����޹�˾
 *ϵͳ����:�ٲû�
 *ģ������:Include
 *����˵��:���ͷ�ļ�����
 *��    ��: dongpf
 *��������: 
 *��    ע: 
 */
#ifndef __ARB_DEF_H__
#define __ARB_DEF_H__
#include <Include/inttypes.h>
#include "acd_def.h"

#define   ACD_NUM     2
//״̬�����ڴ�
#define STATUS_ARB_SHARE_NAME     "statusARBShm"

//���Է��ʹ���
#define SEND_TRY_COUNT  3

//���ͳ�ʱʱ��
#define SEND_WAIT_TIMEOUT  2000

//�ļ�������
#define   MAX_ARB_FILE_LEN   255

//����Э���ͷ
typedef struct tgARBHeader
{
	uint8          byReqOrAns;     //�������Ӧ��
	uint8          byMsgType;      //��Ϣ����
	uint8          byHostID;       //�Ŷӻ����
	uint8          byResultType;   //������ͣ� 0��ͨ��1ǿ��
	uint32         dwPacketId;     //����ţ�ͨ����ŵĴ�С�������ٲ�����˳��
	uint32         dwArbPackNo;    //�ٲ���š�ͬһ���ٲ���Ŵ���ͬһ���ٲ���Ϣ��
	uint32         dwAlarmPackNo;  //�澯�ı�š�
	uint8          byCurStatus;    //���浱ǰ״̬
	uint8          byStartStatus;  //20150812 dongpf ��������״̬������������������
	uint8          byReverse2;     //��2
	uint8          byReverse3;     //��3
	uint32         dwCurQueueNo;   //20150812 dongpf ���ӵ�ǰ�Ŷ����
}ARBHeader;
	

//��Ϣ����
enum ARBMsgType
{
	SWITCH_TO_SINGLE   = 2,    //�ٲû� -> �Ŷӻ�, ָʾ�Ŷӻ��л���SINGLE״̬	
	SWITCH_TO_PREPARE  = 3,    //�ٲû� -> �Ŷӻ�, ָʾ�Ŷӻ��л���PREPARE״̬
	SWITCH_TO_ACTIVE   = 4,    //�ٲû� -> �Ŷӻ�, ָʾ�Ŷӻ��л���ACTIVE״̬
	SWITCH_TO_INACTIVE = 5,    //�ٲû� -> �Ŷӻ�, ָʾ�Ŷӻ��л���INACTIVE״̬	
	SWITCH_TO_SEPARATE = 6,    //�ٲû� -> �Ŷӻ�, ָʾ�Ŷӻ��Ӽ�Ⱥ�з���
	RECV_ACK           = 7,    //�ٲû� -> �Ŷӻ�, �����յ��澯������δ��������
	REGISTER_ACD       = 10,   //�Ŷӻ� -> �ٲû�, ע��һ���Ŷӻ�
	APP_STOP           = 11,   //�Ŷӻ� -> �ٲû�, Ӧ�ñ����澯
	SYNC_COMPLETED     = 12,   //�Ŷӻ� -> �ٲû�, ��ʷͬ�������Ϣ
	SYNC_FAILED        = 13,   //�Ŷӻ� -> �ٲû�, ͬ��ʧ�ܸ澯	
	ACK                = 14,   //�Ŷӻ� -> �ٲû�, �л����
	NACK               = 15,   //�Ŷӻ� -> �ٲû�, �ܾ��л������л�ʧ��	
	NONE_FRONT         = 16,   //�Ŷӻ� -> �ٲû�, ǰ�������ϵĸ澯
	NONE_TRADE         = 17,   //�Ŷӻ� -> �ٲû�, ���������ϵĸ澯
	NONE_HOST          = 18,   //�Ŷӻ� -> �ٲû������������ϵĸ澯���ɱ�������
	ARB_STOP           = 19    //�ٲû��Լ�ֹͣ
	//LOST_ACD_CONNECT   = 31    //�ٲû��Լ�����ʧ�Ŷӻ�������
};

//��Ϣ��������
static const char * g_lpArbMsgName[21] = 
{
	"",                     //��״̬
	"",                     //��״̬
	"TO_SINGLE",            //�л���SINGLE״̬
	"TO_PREPARE",           //�л���SINGLE״̬
	"TO_ACTIVE",            //�л���SINGLE״̬
	"TO_INACTIVE",          //�л���SINGLE״̬
	"TO_SEPARATE",          //�л���SINGLE״̬״̬
	"RECV_ACK",             //�澯Ӧ��
	"",                     //��״̬
	"",                     //��״̬
	"REGISTER_ACD",         //ע���Ŷӻ�
	"APP_STOP",             //Ӧ�ñ����澯
	"SYNC_COMPLETED",       //ͬ�������Ϣ
	"SYNC_FAILED",          //ͬ��ʧ�ܸ澯	
	"ACK",                  //�л����
	"NACK",                 //�л�ʧ��	
	"NONE_FRONT",           //ǰ�������ϸ澯
	"NONE_TRADE",           //���������ϸ澯
	"NONE_HOST",            //���������ϵĸ澯
	"ARB_STOP",             //�ٲû�ֹͣ
	""                      //��״̬
};

//�������
enum ARBResult
{
	RESULT_TYPE_NORMAL = 0,     //��ͨ
	RESULT_TYPE_FORCE  = 1      //ǿ�Ʒ���
};

// �Ŷӻ�״̬�ṹ����
typedef struct tgAcdStatus  
{               
    uint8      byAcdId;              // �Ŷӻ���ʾID
    uint8      byMachineStatus;      // �Ŷӻ�״̬
    bool       bUsable;              // ���ñ�� true:���ã� 
	uint8      byLastStop;            // �����Ŷӻ������һ��ֹͣ��
}AcdStatus;

typedef struct tgOneDecision
{
	AcdStatus  astatus;
	uint32     dwAlarmNo;
	uint32     dwArbPackNo;
}OneDecision, AcdStatusInfo;

#endif
