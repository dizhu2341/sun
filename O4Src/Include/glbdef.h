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
#ifndef __FBASE2_GLBDEF_H__
#define __FBASE2_GLBDEF_H__
#include <Include/inttypes.h>
///ESB�������ȣ�����Ϊ�ɼ��ַ������ܰ���ʵ���ָ������ո񡢷ֺ�;
#define IDENTITY_NAME_LENGTH	32
///ʵ��������ռλ����
#define ID_LENGTH               4   
///ʵ���ָ���������ESB�ڵ��������ʵ�������������ʵ�����������ֶ��󶼻��ж��ʵ����ÿ��ʵ����Ψһ���ֱ�ţ���������֮����ô˷ָ���
#define DELAM_FLAG				'#'	
#define DELAM_FLAG_SZ			"#"
///�ڵ���ȫ��,����ʱʹ��char sName[ID_STR_LEN+1]
#define ID_STR_LEN		       (IDENTITY_NAME_LENGTH + ID_LENGTH + 1)


//	����ӿ�������󳤶�,����ʱʹ��char sName[PLUGINID_LENGTH+1]
#define PLUGINID_LENGTH	256
//	���ʵ��������󳤶�,����ʱʹ��char sName[PLUGIN_NAME_LENGTH+1]
#define PLUGIN_NAME_LENGTH	(PLUGINID_LENGTH+ID_LENGTH+1)
//	��������󳤶�.����ʱʹ��char sName[SVR_NAME_LENGTH+1]
#define SVR_NAME_LENGTH	256
//	����ʵ������󳤶�.����ʱʹ��char sName[PLUGINID_NAME_LENGTH+1]
#define SVRINSTANCE_NAME_LENGTH	(SVR_NAME_LENGTH+ID_LENGTH+1)

///�����޴�����
#define ERR_NONE									0

/*
  �޸���Ա��xuxp
  �޸����ڣ�2009.04.10
  �޸�˵�������ú궨���������

  �޸����ڣ�2009.04.20
  �޸�˵��������ǰ׺����Ϊ��F1�ĺ궨���ͻ
*/
#define ESB_IDENTITY_AR  "ar"
#define ESB_IDENTITY_BAR "bar"
#define ESB_IDENTITY_LS  "ls"
#define ESB_IDENTITY_AS  "as"


/*
  �޸���Ա��xuxp
  �޸����ڣ�2009.04.10
  �޸�˵����������ݱ�ʾ���壬����ö�ٶ��壬���ú궨�����������
*/
enum HS_IDENTITY 
{ 
HSSERVER_UNKNOWN=0,
HSSERVER_AR=1, 
HSSERVER_BAR=2, 
HSSERVER_LS=3,
HSSERVER_AS=4
}; 


#endif
