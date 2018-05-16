///����ESB��Ϣ��س�������
/**
 *Դ��������:tag_def.h
 *�������Ȩ:�������ӹɷ����޹�˾
 *ϵͳ����:������ҵ��������ESB
 *ģ������:ESB Message
 *����˵��:����ESB��Ϣ����س���
 *         ESB��Ϣ����tag=value����ʽ��ʾ��ÿ����֮����\0�ָ�;
 *         ÿ��tag��Ϊһ������ֵ���ڱ��ļ��ж���;
 *         ��Ϣ����ȡֵ���������ͷ�Ϊ��
 *           (1)�����򣬼�Int�������ַ�����
 *           (2)�ַ����򣬼�String������ɼ��ַ�����
 *           (3)�������򣬼�RawData�򣬿���Ϊ�����ַ���ɣ�����ǰ��������һ�������͵� TAG_RAWDATALEN ������ʾ�ö������򳤶ȣ�
 *           (4)�����򣬼�Array�򣬿���Ϊ�����ַ���ɣ�����ǰ��������һ�������͵� TAG_ARRAYLEN ������ʾ�������С��
 *         ��Ϣ����ʹ��������ж��ֱȽ��ر����
 *           (1)ϵͳ���ж�����TAG_RAWDATALEN �����Ƴ�����TAG_ARRAYLEN ���ݴ�С�� ��
 *           (2)�ڲ�����Ϣ�е�������ֻ��ESB�ڵ�Ķ�������ӽ���֮�䴫�ݣ����������ϴ��ݣ�
 *��    ��:  maoyinjie
 *��������:2013/12/12 15:17:56
 *��    ע: �����ĵ���ESBMessage���ݴʵ�.xls������
 */

#ifndef _TAG_DEF_H
#define _TAG_DEF_H

const int INTERNAL_TAG_BEGIN = 100; //�ڲ���tag��ʼֵ(��) 
const int INTERNAL_TAG_END   = 199; //�ڲ���tag����ֵ(��) 

///������RawData�򳤶�  �������ͣ�����
const int TAG_RAWDATALEN = 1 ; //ϵͳTAG,������������һ����ΪRawData��,��ֵ��Ϊ�¸�RawData������ݳ���

///�������������С  �������ͣ�����
const int TAG_ARRAYLEN = 2 ; //ϵͳTAG,������������һ����Ϊ������,��ֵ��Ϊ�¸�������ĳ�Ա����

///������������  �������ͣ�����
const int TAG_PACKET_TYPE = 3 ; //��������ҵ����������
    const int REQUEST_PACKET = 0 ; //����
    const int ANSWER_PACKET = 1 ; //Ӧ��
    const int INTERNAL_REQUEST_PACKET = 2 ; //�ڲ�����
    const int INTERNAL_ANSWER_PACKET = 3 ; //�ڲ�Ӧ��

///������������ϵͳ��  �������ͣ�����
const int TAG_SUB_SYSTEM_NO = 4 ; //��ϵͳID���൱��һ�����ܣ�

///���������ܺ�  �������ͣ�����
const int TAG_FUNCTION_ID = 5 ; //��ҵ��ϵͳ��Ʒ���з���,����ΪESB�ڲ�����
    const int FUNCTION_PLUGIN_REGISTER = 2 ; //���ע��
    const int FUNCTION_NBR_CHANGED = 3 ; //�ھӱ仯
    const int FUNCTION_OSPF = 4 ; //OSPF����
    const int FUNCTION_NBR_PAUSE = 5 ; ////20091029 xuxp ���� ����֪ͨ�ھ���ͣ�õĹ��ܺ�
    const int FUNCTION_PUBLISH = 6 ; //����
    const int FUNCTION_SUBSCIBE = 7 ; //����
    const int FUNCTION_PLUGIN_MANAGE = 8 ; //���������
    const int FUNCTION_SVR_STATUS = 9 ; //����״̬���
    const int FUNCTION_SVR_RESET = 10 ; //���̸�λ
    const int FUNCTION_MEMBER_ACTIVE = 11 ; //f1Э�������ڳ�Ա��Ϣ�仯֪ͨ�Ĺ��ܺ�
    const int FUNCTION_F2_REG = 20 ; //F2�ھ�ע��
    const int FUNCTION_F2_EXCHPWD = 21 ; //F2������Կ
    const int FUNCTION_F2_VALIDATE_CERT = 22 ; //F2�����֤
    const int FUNCTION_T2_DATAPWD = 30 ; //T2������������
    const int FUNCTION_T2_CHG_COMMPWD = 31 ; //T2�޸�ͨ������
    const int FUNCTION_T2_REG = 32 ; //T2�ھ�ע��
    const int FUNCTION_T2_HEARTBEAT = 33 ; //T2����
    const int FUNCTION_BULK_BEGIN = 40 ; //������ݴ���Э��
    const int FUNCTION_BULK_DATA = 41 ; //������ݷ�Ƭ����
    const int FUNCTION_BULK_END = 42 ; //������ݴ��ͽ���
    const int FUNCTION_BULK_CANCEL = 43 ; //������ݴ���ȡ��
    const int FUNCTION_LINK_STATUS = 44 ; //��·״̬��Ϣ
    const int FUNCTION_RELIABLE_TRANS = 59 ; //�ɿ������ǩ
    const int FUNCTION_UFX_NOTIFY = 60 ; //UFX֪ͨ����

///��������֧��  �������ͣ�����
const int TAG_BRANCH_NO = 6 ; //��ҵ��ϵͳ��Ʒ�����趨

///������������  �������ͣ�����
const int TAG_RETURN_CODE = 7 ; //��ҵ��ϵͳ��Ʒ�����趨,�������������뱻����
    const int RT_ERR_NONE = 0 ; //��������
    const int RT_ERR_PROCESS = -1 ; //��Ϣ����ʱ����ϵͳ����
    const int RT_ERR_TRANSFER = 1 ; //��Ϣת��ʱ����ϵͳ����(����ת��)

///��������Ϣ��  �������ͣ�RawData
const int TAG_MESSAGE_BODY = 8 ; //һ�����ڴ��ҵ����

///������Ŀ��·����Ϣ  �������ͣ�����
const int TAG_ROUTE_INFO = 9 ; //Ŀ�����ϸ��λ��Ϣ
    const int IDX_OSPF_NAME = 0 ; //�����±�,��OSPF·�ɵ�Ӧ��ʵ����,���û�и��ֶ�,������Ǳ�Ӧ��ʵ������Ӧ������.���
    const int IDX_NBR_NAME = 1 ; //�����±�,�ھ���,���û�и��ֶ�,�����Ǳ�Ӧ��ʵ��
    const int IDX_SVR_NAME = 2 ; //�����±�,���ʷ����ӽ�����:���������.���
    const int IDX_PLUGIN_ID = 3 ; //�����±�,���ʵķ�����ID�����ID�����
    const int IDX_CONNECT_ID = 4 ; //�����±�,����ͨ��ͨ�����,���ڱ�ʶ��ͨ����ĳ��ͨ�����ӡ�����F1���ͨ�����ڱ�ʶĳ��Session.
    const int IDX_MEMBER_NO = 5 ; //�����±�,����F1ͨ�����,���ڱ���ĳ��Session�ڵĳ�ԱID�����ڱ�ţ�

///��������������Ϣ  �������ͣ�����
const int TAG_SENDER_PATH = 10 ; //�����ߵ���Ϣ,���Ը��ݸ���Ϣ�������߷��ͷ�����Ϣ,��ͬ��TAG_ROUTE_INFO

///����������ˮ��  �������ͣ�����
const int TAG_PACKET_ID = 11 ; //��Ϣ���������ۼ�,��������Ӧ�����ƥ��,Ӧ���ԭ������

///�����������߱��  �������ͣ�����
const int TAG_SENDERID = 12 ; //��Ϣ������������,������һ��������ʶ�����Ӧ��,Ӧ���ԭ������

///���������ȼ�  �������ͣ�����
const int TAG_PRIORITY = 13 ; //��ֵԽ�����ȼ�Խ��,�����ȼ��߻ᱻ���ȴ���,���ȴ���,ҵ����Ϣ�Ͻ�ʹ��>13�����ȼ�.>13�ĸ����ȼ�ֻ����ESBϵͳ�ڲ�ʹ��,ȷ���ڲ��Ŀɿ�.ҵ����Ϣ�ĺϷ�ȡֵΪ4--13.����4��13.�����Ϣ�в����ֱ��ֶ�,�������ȼ�8����

///������������������  �������ͣ�����
const int TAG_TTL = 14 ; //����ÿ����һ��ת��,����ᱻ��1,����ֵ������0,����Ϣ�ᱻ����,�����Ϣ�в����ֱ��ֶ�,��Ը���Ϣ����TTL����

///������������ڵ�ʱ��  �������ͣ�����
const int TAG_LIVE_TIME = 15 ; //��λ����,һ�������ڶ����еȴ�����ʱ��,�������Ϊ0���߲����ֱ��ֶ�,���������������

///��������������  �������ͣ�����
const int TAG_LOAD = 16 ; //�������ھӽڵ�㱨���ڵ�ĸ������,�Ա����ڽڵ���ת������ʱ���и��ؾ���

///������F1��ַ����Ϣ  �������ͣ�RawData
const int TAG_F1_SENDER = 17 ; //F1�ĸ��������ֶ�APPEND_ADDRESS��Ϣ����

///������ͨ����ȫ����  �������ͣ�����
const int TAG_SAFE_TYPE = 18 ; //ͨ��˫��Э�̵İ�ȫ����
    const int ENM_ST_NONE = 0 ; //����
    const int ENM_ST_PWD = 1 ; //ͨ������
    const int ENM_ST_SSL = 2 ; //����֤��

///�����������  �������ͣ�����
const int TAG_ERROR_NO = 19 ; //

///������������Ϣ  �������ͣ��ַ���
const int TAG_ERROR_INFO = 20 ; //

///����������  �������ͣ�RawData
const int TAG_PASSWORD = 21 ; //

///������֤��  �������ͣ�RawData
const int TAG_CERT = 22 ; //

///�������ӷ������״̬  �������ͣ�����
const int TAG_SERVICE_STATUS = 23 ; //�����ģʽ�Ľڵ�,���ӽ��̼�����״̬
    const int ENM_CS_NONE = 0 ; //������
    const int ENM_CS_OK = 1 ; //����

///�������ͻ�ID  �������ͣ��ַ���
const int TAG_CLIENT_ID = 24 ; //�ͻ�ID,T2Э��

///���������ܵĿͻ�ID  �������ͣ�RawData
const int TAG_EN_CLIENT_ID = 25 ; //��ͨ��������ܺ�Ŀͻ�ID,T2Э��

///��������������  �������ͣ�RawData
const int TAG_DATA_PWD = 26 ; //��������,T2Э��

///�������Ƿ���Ҫ����  �������ͣ�����
const int TAG_CHANGE_PWD = 27 ; //�Ƿ���Ҫ�޸�ͨ������,T2Э��
    const int ENM_CP_YES = 0 ; //����Ҫ
    const int ENM_CP_NO = 1 ; //��Ҫ

///������ԭͨ������  �������ͣ��ַ���
const int TAG_OLD_COMM_PWD = 28 ; //ԭͨ������,T2Э��

///������ͨ������  �������ͣ��ַ���
const int TAG_COMM_PWD = 29 ; //ͨ������,T2Э��

///��������ݱ�ʶ  �������ͣ��ַ���
const int TAG_IDENTITY_NAME = 30 ; //

///���������֤���  �������ͣ��ַ���
const int TAG_LICENSE_NO = 31 ; //���֤���,T2Э��

///���������֤����  �������ͣ�����
const int TAG_LICENSE_DATA = 32 ; //���֤����,T2Э��
    const int IDX_MAX_SEND_PACKETS = 0 ; //�����±�,ÿ�������ÿ����������
    const int IDX_MAX_SEND_BYTES = 1 ; //�����±�,ÿ�������ÿ���ӷ����ֽ���
    const int IDX_ROUTE_BY_NAME = 2 ; //�����±�,�Ƿ���������ע�ᣬʹ�ɸ�������·��
    const int IDX_BULK_SEND = 3 ; //�����±�,�Ƿ����������ݴ���

///�������������˵��  �������ͣ��ַ���
const int TAG_BULK_COMMENT = 33 ; //��������й�˵����Ϣ,��鴫��Э��

///�������ܳ�  �������ͣ�����
const int TAG_TOTAL_LEN = 34 ; //�ܳ�,��鴫��Э��

///������ÿ���С  �������ͣ�����
const int TAG_PIECES_SIZE = 35 ; //ÿ���С,��鴫��Э��

///���������ܷ��ỰID  �������ͣ�����
const int TAG_RECE_SESSION_ID = 36 ; //���ܷ��ỰID,��鴫��Э��

///��������Ƭ���  �������ͣ�����
const int TAG_PIECES_NUMBER = 37 ; //��Ƭ��ţ���0��ʼ,��鴫��Э��

///��������Ƭ����  �������ͣ�RawData
const int TAG_PIECES_DATA = 38 ; //��Ƭ����,��鴫��Э��

///��������ʧ�ķ�Ƭ��  �������ͣ��ַ���
const int TAG_MISS_PIECES = 39 ; //��ʧ�ķ�Ƭ��,��鴫��Э��

///������·�ɷ�ʽ  �������ͣ�����
const int TAG_ROUTE_TYPE = 40 ; //1.0��·�ɷ�ʽ

///������·�ɷ�ʽֵ  �������ͣ��ַ���
const int TAG_ROUTE_VALUE = 41 ; //����TAG_ROUTE_TYPEֵ��ʹ��TAG_ROUTE_VALUE����TAG_INTERNAL_ROUTE·��

///������F1��ԭʼ·����Ϣ  �������ͣ�RawData
const int TAG_F1_ROUTE = 42 ; //ȡ��F1��APPEND_ROUTE_INFO���洢��

///������ѹ���㷨���  �������ͣ�����
const int TAG_COMPRESS_ID = 43 ; //msgbody���ݵ�ѹ���㷨��������ѹ��

///�������ڲ����֤���  �������ͣ�����
const int TAG_INTERNAL_LICENSE_NO = 44 ; //�ڲ����֤���

///������T1ͷ������  �������ͣ�RawData
const int TAG_T1_HEAD = 45 ; //T1ͷ������,������ַ������

///����������ϵͳ��  �������ͣ�����
const int TAG_SYSTEM_NO = 46 ; //ϵͳID���൱��һ��Ӫҵ����

///�������������ݱ�ʶ  �������ͣ�����
const int TAG_F1_APPEND_FLAG = 47 ; //

///������  �������ͣ�����
const int TAG_F1_RESERVED = 48 ; //

///������F1�ĸ������ݳ���  �������ͣ�����
const int TAG_F1_APPEND_LEN = 49 ; //���ڱ�������F1�յ��ĸ������ݵĳ���

///�����������  �������ͣ�����
const int TAG_SEQUECE_NO = 50 ; //��Ϣ����ʱ�ı����,���Լ�ⱨ�Ƿ�����

///��������Ϣ���ı���  �������ͣ�RawData
const int TAG_MSG_CENTER_RESERVED = 51 ; //��Ϣ����ʱ�ı����,���Լ�ⱨ�Ƿ�����

///������ʱ���,��������ģ��������м���ʱ���  �������ͣ�����
const int TAG_TIMESTAMP = 52 ; //ÿ������ģ������Լ���ʱ���,���Ի��ÿ��ģ��Ĵ���ʱ��

///��������Ϣ����  �������ͣ�����
const int TAG_ISSUE_TYPE = 53 ; //

///����������  �������ͣ�RawData
const int TAG_KEY_INFO = 54 ; //

///�������ļ�ͷ��  �������ͣ�RawData
const int TAG_FILE_HEAD = 55 ; //

///������F1�ĸ�������  �������ͣ�RawData
const int TAG_F1_APPEND_DATA = 56 ; //���ڱ�������F1�յ��ĸ�������

///����������ѹ�����ܱ�־  �������ͣ�����
const int TAG_UNCOMPRESS_MSGBODY = 57 ; //T2_SDK��T2_Channelע��ʱ�������Լ��Ƿ���ѹ������
    const int ENM_COMPRESS = 0 ; //��ѹ������
    const int ENM_UNCOMPRESS = 1 ; //��ѹ������

///�������ɿ�����ͷ��  �������ͣ�RawData
const int TAG_RELIABLE_BODY = 58 ; //�ɿ�����ͷ��������������

///������ҵ������  �������ͣ�ҵ�����ж���
const int TAG_APP_RESERVED = 59 ; //Ŀǰ���ƿ��ܻᶨ��ɻỰ��

///������������ڴ����ݿ�����  �������ͣ�����
const int TAG_MDB_RPC = 60 ; //mdbԶ�̵���
    const int IDX_MDB_RPC_REQUESTID = 0 ; //�����±�,����ID
    const int IDX_MDB_RPC_PROCEDURE = 1 ; //�����±�,����
    const int IDX_MDB_RPC_RETCODE = 2 ; //�����±�,���÷���
    const int IDX_MDB_RPC_ARG1 = 3 ; //�����±�,���ò���1
    const int IDX_MDB_RPC_ARG2 = 4 ; //�����±�,���ò���2
    const int IDX_MDB_RPC_ARG3 = 5 ; //�����±�,���ò���3
    const int IDX_MDB_RPC_ARG4 = 6 ; //�����±�,���ò���3

///����������̴�����Ϣ  �������ͣ�����
const int TAG_MULT_PROC = 61 ; //proc_s��proc_c����ͨ��
    const int IDX_DEST_SUBPROC_ID = 0 ; //�����±�,�ӷ������Ŀ���ӽ��̺�
    const int IDX_PROC_PACKET_ID = 1 ; //�����±�,���������ӽ��̰�ƥ���
    const int IDX_SOUR_SUBPROC_ID = 2 ; //�����±�,Դ�ӽ��̺�
    const int IDX_SEND_MODE = 3 ; //�����±�,�ӽ��̷���ȥ�İ���ģʽ��ͬ�����첽��������ʹ��
    const int IDX_DEST_SERVER_ID = 4 ; //�����±�,Ŀ���������ڱ��

///������  �������ͣ�����
const int TAG_IDENTITY_TYPE = 62 ; //�������:  0:AR, 1:BAR, 2:LS, 3:AS

///������  �������ͣ�����
const int TAG_ASYN_REGISTER_ID = 63 ; //ͨ��ͨ��������첽����ע��ID,��ͨ��ͨ������,����������첽����ʱָ��

///������  �������ͣ�����
const int TAG_JAVA_SENDID = 64 ; //Java��t2ͨ��sdkר�õģ�ʹ���߲�������ӣ���������Ӧ�����ӵ�ƥ��,Ӧ���ԭ������

///������fix�����Ϣ  �������ͣ�����
const int TAG_FIX_INFO = 65 ; //
    const int IDX_FIX_SENDID = 0 ; //�����±�,�����߱��
    const int IDX_FIX_DEST_NAME = 1 ; //�����±�,Ŀ��fix������
    const int IDX_FIX_MODE = 2 ; //�����±�,ͬ��0���첽1
    const int IDX_FIX_ARG2 = 3 ; //�����±�,����2

///������bypass��Ϣ  �������ͣ�����
const int TAG_BYPASS_ORGREQ = 66 ; //����sendpath

///������ԭʼ��������Ϣ  �������ͣ�����
const int TAG_BRIDGE_ORGREQ = 67 ; //��������ԭʼ��������Ϣ���������TAG_SENDER_PATHһ��

///�������Ų����Ϣ  �������ͣ�����
const int TAG_BRIDGE_SEND = 68 ; //���������Ų���ķ�������Ϣ���������TAG_SENDER_PATHһ��

///�������������ֻ�ƽ̨��  �������ͣ�RawData
const int TAG_MOBILE_RESERVED = 69 ; //

///�������ֻ�ƽ̨��  �������ͣ�RawData
const int TAG_MOBILE_NV = 70 ; //

///�������������,Ŀǰû���õ�  �������ͣ�����
const int TAG_COMP_ID = 71 ; //

///����������̻Ự  �������ͣ�����
const int TAG_MULTI_CONVERSATION = 72 ; //����̵ĻỰ,ģ��texudo�Ự
    const int IDX_CONVER_FLAG = 0 ; //�����±�,��ǰ�Ự��־������syn��ack��fin�����  
    const int IDX_CONVER_NO = 1 ; //�����±�,��ǰ�Ự��                             
    const int IDX_CONVER_APP_FLAG = 2 ; //�����±�,Ӧ�ò��־������tuxedo�ı�־           
    const int IDX_CONVER_SEQ_NO = 3 ; //�����±�,�������                               
    const int IDX_CONVER_ACK_NO = 4 ; //�����±�,ȷ�����                               

///������ҵ������,ͳһ�����õ�  �������ͣ�����
const int TAG_BIZTYPE_ID = 45 ; //����,�ǹ��⽫��TAG����ɺ�TAG_T1_HEADһ��,��ʹ����06��Ҳ����ʹ��

///����������5�ֶ�ΪJRES����,JRES������  �������ͣ�����
const int TAG_JRES_SENDER_INFO = 73 ; //
    const int IDX_JRES_NODE_NAME = 0 ; //�����±�,JRES�ڵ���
    const int IDX_JRES_NODE_NO = 1 ; //�����±�,�ڵ���
    const int IDX_JRES_CONNECT_ID = 2 ; //�����±�,����T2ͨ���������ʾ���Ӻ�
    const int IDX_JRES_PLUGIN_NAME = 3 ; //�����±�,JRES�����
    const int IDX_JRES_MEMBER_NO = 4 ; //�����±�,��T2ͨ���������ʾͨ�����ӵ����ڱ�ţ���ʱ����

///������JRES·��Ŀ�ĵ�  �������ͣ�����
const int TAG_JRES_ROUTE_INFO = 74 ; //Jresָ��·����Ϣ

///������JRES������  �������ͣ��ַ���
const int TAG_JRES_SERVICE_ID = 75 ; //JRES������

///������JRES·���ڵ���  �������ͣ��ַ���
const int TAG_JRES_PASSED_NODES = 76 ; //�����¼��������ڵ��б�ÿ���ڵ��÷ֺŸ���

///������JRES�ھ�����  �������ͣ�����
const int TAG_NODE_TYPE = 77 ; //
    const int NODE_TYPE_JRES = 1 ; //
    const int NODE_TYPE_CRES = 2 ; //

///������ͳһ���뱣��  �������ͣ�array
const int TAG_SYSTEM_INFO = 80 ; //
    const int IDX_SDK_VER = 0 ; //�ͻ���SDK�İ汾
    const int IDX_SDK_CHECKSUM = 1 ; //�ͻ���SDK��У���
    const int IDX_SDK_IP_MAC = 2 ; //�ͻ��˻�����IP��ַ��MAC��ַ
    const int IDX_SDK_HEARTBEAT = 3 ; //�����Ҫ��ͻ��˵�����ʱ��
    const int SDK_DEADLINE = 4 ; //���֤��Ч�ڽ�ֹ����
    const int IDX_UFX_TIME = 5 ; //ufx�������ݵ�ʱ��
    const int IDX_COMM_INDEX = 6 ; //���������
    const int IDX_COMM_CHANNELID = 7 ; //ͨ����
    const int IDX_COMM_CONNECTID = 8 ; //���Ӻ�
    const int IDX_HD_SERIALNO = 9 ; //Ӳ�����к�
    const int IDX_CPU_SERIALNO = 10 ; //CPU���к�
    const int IDX_MACHINE_CODE = 11 ; //����������
    const int IDX_WIDE_IP_MAC = 13 ; //����IP    
    const int IDX_USER_CODE = 14 ; //UserCode  
    const int IDX_SESSION_NO = 15 ; //SessionNo 
    const int IDX_USER_PARAM1 = 16 ; //UserParam1
    const int IDX_USER_PARAM2 = 17 ; //UserParam2
    const int IDX_USER_PARAM3 = 18 ; //UserParam3
    const int IDX_AUTH_PRODUCT_TYPE = 19 ; //
    const int IDX_AUTH_KEY = 20 ; //

///������ͳһ���뱣��  �������ͣ�RawData
const int TAG_CLIENTFIX_PWD = 81 ; //�̶���Կ���ܺ����ݱ�ʶ

///������ͳһ���뱣��  �������ͣ�RawData
const int TAG_CLIENTDYN_PWD = 82 ; //���ܺ����ݱ�ʶ

///������ͳһ���뱣��  �������ͣ�RawData
const int TAG_COMMPRI_PWD = 83 ; //�̶���Կ���ܺ��������Կ

///������ͳһ���뱣��  �������ͣ�RawData
const int TAG_COMMPUB_PWD = 84 ; //���ܺ��������Կ

///������ͬ�����ͱ��ı�־  �������ͣ�����
const int TAG_SYN_FLAG = 85 ; //���������,����0,�������첽���͵�,������ͬ������

///������ѹ�����ݱ���  �������ͣ�����
const int TAG_COMMPRESS_RATE = 86 ; //��ѹ��ʱ,Ϊ�˿��ٻ���ڴ��С,����һ����ʾѹ��������TAG,���������û�г��ָ��ֶ�,���밴��ǰ��ģʽ����,�������ѹ������

///������������  �������ͣ�����
const int TAG_MC_TOPICNO = 87 ; //������

///��������������  �������ͣ��ַ���
const int TAG_MC_TOPICNAME = 88 ; //�������֣���������֮����.�ָ�

///�������Ự���ӵ�״̬  �������ͣ�����
const int TAG_MCSESSION_CONNECT = 89 ; //�Ự�������ӵ�״̬��1��ʾSYN���ģ�2��ʾSYN|ACK���ģ�3��ʾSYN|ACK��ACK����

///�������Ự��ͨ����Ϣ  �������ͣ�����
const int TAG_MCSESSION_INFO = 90 ; //�Ự����Ϣ������ά���Ự�ɿ�����
    const int IDX_SELF_CONNECTNO = 0 ; //�����±�,��ǰ�������Լ������
    const int IDX_OPPOSITE_CONNECTNO = 1 ; //�����±�,��ǰ�����ڶԷ������
    const int IDX_SEND_SEQUENO = 2 ; //�����±�,��ǰ�ķ������
    const int IDX_NEXTRECV_SEQUENO = 3 ; //�����±�,��һ���������յ����
    const int IDX_SUBCRIBE_INDEX = 4 ; //�����±�,�������ʶ��������Ϣʱ����
    const int IDX_HEART_TIME = 5 ; //�����±�,������ʱ����

///���������ĵĲ���  �������ͣ�����
const int TAG_MCSUBCRIBE_INFO = 91 ; //�������в�����Ϣ���������ṹ�������˵��(����)
    const int IDX_MCSUBCRIBE_INDEX = 0 ; //�����±�,���ı�ʶ�����ĵ�ʱ�����
    const int IDX_SENDINTERVAL = 1 ; //�����±�,Ƶ��
    const int IDX_RETURNFILEDS = 2 ; //�����±�,�����ֶ�,��'\2'����
    const int IDX_REPLACE = 3 ; //�����±�,�Ƿ񸲸�
    const int IDX_REBULID = 4 ; //�����±�,�Ƿ�ȱ
    const int IDX_BORN_SUBSCRIBE = 5 ; //�����±�,�Ƿ������충��

///��������������  �������ͣ�����������
const int TAG_MCADDITION_DATA = 92 ; //���ĵĸ������ݣ����͵�ʱ��ԭ������

///���������ĵ�֪ͨ״̬  �������ͣ�����
const int TAG_MCNOTIFY_STATUS = 93 ; //���ĳɹ���״̬֪ͨ���ǽ��벹ȫ״̬��������״̬

///������������Ϣ  �������ͣ�����
const int TAG_MCFILTER_INFO = 94 ; //ÿ�������й̶���6�������������Զ���Ĺ����������±�6��ʼ��һ���ֶ�����һ���ֶ�ֵ���ֶ�ֵҪ�󲻿�����\0 \1 \2�����ַ�
    const int IDX_FILTERINDEX_1 = 0 ; //�����±�,�Ѷ���Ĺ�������1��ֵ
    const int IDX_FILTERINDEX_2 = 1 ; //�����±�,�Ѷ���Ĺ�������2��ֵ
    const int IDX_FILTERINDEX_3 = 2 ; //�����±�,�Ѷ���Ĺ�������3��ֵ
    const int IDX_FILTERINDEX_4 = 3 ; //�����±�,�Ѷ���Ĺ�������4��ֵ
    const int IDX_FILTERINDEX_5 = 4 ; //�����±�,�Ѷ���Ĺ�������5��ֵ
    const int IDX_FILTERINDEX_6 = 5 ; //�����±�,�Ѷ���Ĺ�������6��ֵ

///������ҵ�������  �������ͣ��ַ���
const int TAG_MCAPPLICATION_NAME = 95 ; //��Ϣ���ĵ��ϲ�Ӧ�����֣�����Ψһ

///��������Ϣ���  �������ͣ�����
const int TAG_MCMSG_ID = 96 ; //�����˷��͵���Ϣ��ţ�һ������������

///���������Ʊ�ʶ  �������ͣ�����
const int TAG_MCTOKEN_ID = 97 ; //ҵ���У�鷵�صļ�����

///��������Ϣ����1.0�������ݱ�־  �������ͣ�����
const int TAG_MCCOMPATIBLE_FLAG = 98 ; //������Ϣ����1.0�ķ�����־����־�ŷ�����Ϣ�Ƿ���key_info����message_body

///������������ű�־  �������ͣ�����
const int TAG_MCRESET_MSGNO = 99 ; //������Ϣ��ŵı�־�������ڷ����Ϸ����ĵ�һ�����Ķ���Ҫ���������־��1��ʾ�������

///������ͬ��֮��ʹ�õ��ڲ���  �������ͣ�����
const int TAG_MCMSGCENTER_INFO = 110 ; //��Ҫ��������ͬ������ʶ��ͬ�Ĺ��ܺ�
    const int IDX_MSGCENTER_FUNCID = 0 ; //�����±�,���ܺ�
    const int IDX_MSGCENTER_PACKTYPE = 1 ; //�����±�,������
    const int IDX_MSGCENTER_PACKID = 2 ; //�����±�,�����
    const int IDX_MSGCENTER_SENDERPATH = 3 ; //�����±�,��������ͬ����Ϣ����Դ���м������
    const int IDX_MSGCENTER_LOGINCNT = 4 ; //�����±�,��½����

///�������־û���Ҫ�������Ϣ  �������ͣ�����
const int TAG_MCPERSIS_INFO = 111 ; //�־û���Ҫ���ӵ��ڲ��ֶ����
    const int IDX_PERSIS_INTERNELNO = 0 ; //�����±�,��Ϣ�ڲ����
    const int IDX_PERSIS_MSGLIFE = 1 ; //�����±�,��Ϣ��Ч��
    const int IDX_MSG_TIME = 2 ; //�����±�,��Ϣ�����ľ���ʱ��
    const int IDX_PUBLISHER_NO = 3 ; //�����±�,�������ڲ����
    const int IDX_MSG_OPPOTIME = 4 ; //�����±�,��Ϣ�Ѿ�����ʱ�䣬���ڿ�����ȱ

///�������¼���Ϣ���ĵı�־λ  �������ͣ�����
const int TAG_MC_CHILDFLAG = 112 ; //�¼���Ϣ���ĵı�־λ������֪ͨ����ģ��������ֱ������⴦�����û�Ӧ�𣬲���У�飬������ͻ��˲�ȱ��0��ʾ�ϼ���1��ʾ�¼�

///�������ڲ�·����Ϣ  �������ͣ�����
const int TAG_INTERNAL_ROUTE = 100 ; //�ڲ�TAG
    const int IDX_IR_IPC_CHANNEL = 0 ; //�����±�,�ڲ�ͨ�������ӱ�ţ�Ӧ���Զ����ģʽʵ��ʱ��ͨ���ڲ�ͨ���Ե�Զ���ʽ������
    const int IDX_IR_SVR_NAME = 1 ; //�����±�,�����ӽ�����:���õķ��������.���
    const int IDX_IR_PLUGIN_ID = 2 ; //�����±�,������ID�����ID�����
    const int IDX_IR_CONNECT_ID = 3 ; //�����±�,����ͨ��ͨ�����,���ڱ�ʶ��ͨ����ĳ��ͨ�����ӡ�����F1���ͨ�����ڱ�ʶĳ��Session.
    const int IDX_IR_MEMBER_NO = 4 ; //�����±�,����F1ͨ�����,���ڱ���ĳ��Session�ڵĳ�ԱID�����ڱ�ţ�

///�������ھ����¼���־  �������ͣ�����
const int TAG_NBR_FLAG = 101 ; //�ڲ�TAG,�ھӽ���ʱ�����¼���ϵ
    const int ENM_NF_UP = 0 ; //�ϼ�
    const int ENM_NF_DOWN = 1 ; //�¼�
    const int ENM_NF_UNKNOWN = 2 ; //δ֪

///�������ھ��Ƿ���ҪOSPF����  �������ͣ�����
const int TAG_NBR_PROXY = 102 ; //�ڲ�TAG,��ʶ���ھ��Ƿ���ҪOSPF����, Ĭ��Ϊ0
    const int ENM_NP_YES = 0 ; //����Ҫ
    const int ENM_NP_NO = 1 ; //��Ҫ

///�������ھӱ仯  �������ͣ�����
const int TAG_CHANGE_FLAG = 103 ; //�ڲ�TAG,�ھӱ仯��ʽ��������ע��
    const int ENM_CF_CONNECT = 0 ; //����
    const int ENM_CF_DISCONNECT = 1 ; //�Ͽ�

///��������Ϣ��Դ  �������ͣ�����
const int TAG_FROM = 104 ; //�ڲ�TAG
    const int ENM_FROM_DOWN = 0 ; //�����¼�
    const int ENM_FROM_UP = 1 ; //�����ϼ�

///����������ʱ��  �������ͣ�����
const int TAG_PUSH_QUEUE_TIME = 105 ; //����ʱ�䣬���Լ���PROC�ж��е�����ʱ�䣬��λ�Ǻ���

///���������Ӻ�  �������ͣ�����
const int TAG_CONNECT_ID = 106 ; //�ڲ�TAG

///������SEE��Ʒ����  �������ͣ�array
const int TAG_SEE_KEY = 78 ; //�������鶨���������SEE��Ʒ�鶨��

#endif

