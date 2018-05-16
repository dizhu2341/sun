///����ESBȫ�ֳ�������
/**
 *Դ��������:glbdef.h
 *�������Ȩ:�������ӹɷ����޹�˾
 *ϵͳ����:������ҵ��������ESB
 *ģ������:Include
 *����˵��:����ESBȫ�ֳ�������
 *��    ��: ��Ŀ��
 *��������: 2008-7-2 9:49:29
 *��    ע: 
 */
#ifndef __MC_GLBDEF_H__
#define __MC_GLBDEF_H__

#include <Include/plugin_interface.h>
#include <Include/esb_message_interface.h>
#include <Include/esb_message_factory_interface.h>
#include <Include/pack_interface.h>
#include <Include/tag_def.h>
#include <Include/log_interface.h>


#define FUNC_SUBCRIBE 620701 
#define FUNC_CANCELSUBCRIBE 620702
#define FUNC_HEARTBEAT 620703
#define FUNC_PUBLISH 620704
#define FUNC_SESSION_CONNECT 620705
#define FUNC_SESSION_PUB 620706
#define FUNC_GETTOPICINFO 620707
#define FUNC_NOTIFY 620708
#define FUNC_NOTIFY_BORN 620709
#define FUNC_VERTIFY 620710
#define FUNC_REBULID 620711
#define FUNC_REGISTER 620712
#define FUNC_CANCELREGISTER 620713
#define FUNC_GETREGISTERLIST 620714
#define FUNC_TICKSUBSCRIBE 620715
#define FUNC_PUBLISH_HEART 620716

//�¼���Ϣ�������ϼ�����Ĺ��ܺŶ���
#define FUNC_MC_PUBLISH 620804
#define FUNC_MC_SESSION_CONNECT 620805
#define FUNC_MC_GETTOPICINFO 620807 
//�¼���Ϣ�������ϼ���ʱ��ȡ������Ϣ�Ĺ��ܺ�
#define FUNC_MC2MC_GETTOPICINFO 620817
#define FUNC_MC2MC_GETDUALSUB 620818

/* �ļ����²�����ܺŶ��� */
#define FUNC_MC_UPDATE_FILELIST_OLD     620005  /* ����1.0�汾���ļ��б���Ϣ */
#define FUNC_MC_UPDATE_ONEFILE_OLD      620006  /* ����1.0�汾�������ļ���Ϣ */
#define FUNC_MC_UPDATE_ONEFILEBLOCK_OLD 620007  /* ����1.0�汾���ļ�����Ϣ */
#define FUNC_MC_UPDATE_FILELIST_CS      620901  /* �ͻ�����Ӫҵ�������ܲ���֮�䣺�ļ��б���Ϣ */
#define FUNC_MC_UPDATE_ONEFILE_CS       620902  /* �ͻ�����Ӫҵ�������ܲ���֮�䣺�����ļ���Ϣ */
#define FUNC_MC_UPDATE_ONEFILEBLOCK_CS  620903  /* �ͻ�����Ӫҵ�������ܲ���֮�䣺�ļ�����Ϣ */
#define FUNC_MC_UPDATE_FILELIST_SS      620911  /* Ӫҵ�����ܲ�֮�䣺�ļ��б���Ϣ */
#define FUNC_MC_UPDATE_ONEFILE_SS       620912  /* Ӫҵ�����ܲ�֮�䣺�����ļ���Ϣ */
#define FUNC_MC_UPDATE_ONEFILEBLOCK_SS  620913  /* Ӫҵ�����ܲ�֮�䣺�ļ�����Ϣ */

//////////////////////////////////////////////////////////////////////////
/* ��ʱ���������ܺŶ��� */
#define FUNC_IM_USER_LOGIN              620921  /* �û���¼��Ϣ */
#define FUNC_IM_USER_GET_LIST           620922  /* �û��б��ȡ��Ϣ */
#define FUNC_IM_USER_LOGOUT             620923  /* �û�ע����Ϣ */
#define FUNC_IM_USER_STATE_NOTIFY       620924  /* �û�״̬��ʱ����֪ͨ��Ϣ */

#define FUNC_IM_GROUP_CREATE            620925  /* �����鴴����Ϣ */
#define FUNC_IM_GROUP_ADD_USERS         620926  /* ���������ӳ�Ա��Ϣ */
#define FUNC_IM_GROUP_QUIT              620927  /* �������Ա�˳���Ϣ */
#define FUNC_IM_GROUP_DELETE            620928  /* ������ɾ����Ϣ */
#define FUNC_IM_GROUP_ADD_USERS_NOTIFY  620929  /* ���������ӳ�Ա֪ͨ��Ϣ */
#define FUNC_IM_GROUP_JOIN_NOTIFY       620930  /* �������Ա����֪ͨ��Ϣ */
#define FUNC_IM_GROUP_QUIT_NOTIFY       620931  /* �������Ա�˳�֪ͨ��Ϣ */
#define FUNC_IM_GROUP_DELETE_NOTIFY     620932  /* ������ɾ��֪ͨ��Ϣ */

#define FUNC_IM_CHAT_SINGLE_MSG         620933  /* ������Ϣ����Ե� */
#define FUNC_IM_CHAT_GROUP_MSG          620934  /* ������Ϣ�������� */
#define FUNC_IM_CHAT_SINGLE_MSG_NOTIFY  620935  /* ����֪ͨ��Ϣ����Ե� */
#define FUNC_IM_CHAT_GROUP_MSG_NOTIFY   620936  /* ����֪ͨ��Ϣ�������� */

#define FUNC_IM_FILE_SEND               620937  /* �ļ�������Ϣ */
#define FUNC_IM_FILE_RECV               620938  /* �ļ�������Ϣ */
#define FUNC_IM_FILE_SEND_NOTIFY        620939  /* �ļ�����֪ͨ��Ϣ */
#define FUNC_IM_FILE_RECV_NOTIFY        620940  /* �ļ�����֪ͨ��Ϣ */
#define FUNC_IM_FILE_SEND_BLOCK         620941  /* �ļ�Ƭ������Ϣ */

#define FUNC_IM_HEART_BEAT              620942  /* ������Ϣ */
//////////////////////////////////////////////////////////////////////////


///����Ŀ�����ռ䶨��
#define FBASE2_MC_NAMESPACE			FBASE2_MC
///define the namesapce
#define NAMESPACE_BEGIN(x)		namespace x {
#define NAMESPACE_END			}
#define USING_NAMESPACE(x)		using namespace x;

#define BEGIN_FBASE2_MC_NAMESPACE	NAMESPACE_BEGIN(FBASE2_MC_NAMESPACE)
#define END_FBASE2_MC_NAMESPACE		NAMESPACE_END
#define USING_FBASE2_MC_NAMESPACE	USING_NAMESPACE(FBASE2_MC_NAMESPACE)

BEGIN_FBASE2_MC_NAMESPACE
END_FBASE2_MC_NAMESPACE


#endif
