/* 
 * File:   Common.h
 * Author: zhouyx11685
 * Description: ͨ�ú���������
 * Created on 2015��11��9��, ����4:10
 */

#ifndef COMMON_H
#define	COMMON_H

#include <pthread.h>
#include "hshead.h"

/*ͨ�ô���������*/

//ҵ��ͬ������
#define     SYNC_ERR_OTHER                                                      1000        //�������������Ϣ
#define     SYNC_ERR_GET_TABLE_COUNT                                            1001        //��ȡ��¼����ʧ��
#define     SYNC_ERR_CLEAR_TEMP_TABLE                                           1002        //����м�ת����ʧ��
#define     SYNC_ERR_QUERY_SRC_TABLE                                            1003        //��ѯ��Դ������ʧ��
#define     SYNC_ERR_EXPORT_DATA_TEMP                                           1004        //�������ݵ��м��ʧ��
#define     SYNC_ERR_IMPORT_DATA_DST                                            1005        //�������ݵ�Ŀ���ʧ��
#define     SYNC_ERR_MALLOC_MEMORY                                              1006        //��������ڴ�ʧ��
#define     SYNC_ERR_VALIDATE_FIELD                                             1007        //�ֶμ�����У��ʧ��
#define     SYNC_ERR_LOCK_MUTEX                                                 1008        //ͬ������������ʧ��
#define     SYNC_ERR_UNLOCK_MUTEX                                               1009        //ͬ������������ʧ��
#define     SYNC_ERR_DROP_TEMP_TABLE                                            1010        //ɾ���м�ת����ṹʧ��
#define     SYNC_ERR_CREATE_TEMP_TABLE                                          1011        //�����м�ת����ʧ��
#define     SYNC_ERR_GET_SYNC_INFO                                              1012        //��ȡͬ���ֶ�������Ϣʧ��
#define     SYNC_ERR_VIOLATED                                                   1013        //�ظ����ݴ�����Ϣ


//DB��������
#define     DB_ERR_OTHER                                                        2000        //�������ݿ����
#define     DB_ERR_CONNECTION                                                   2001        //���ݿ�����ʧ��
#define     DB_ERR_CURSOR                                                       2002        //���ݿ��α����ʧ��
#define     DB_ERR_QUERY                                                        2003        //���ݿ��ѯ����ʧ��
#define     DB_ERR_INSERT                                                       2004        //���ݿ�������ʧ��
#define     DB_ERR_UPDATE                                                       2005        //���ݿ���²���ʧ��
#define     DB_ERR_DELETE                                                       2006        //���ݿ���²���ʧ��
#define     DB_ERR_DROP_INDEX                                                   2007        //ɾ������/����ʧ��
#define     DB_ERR_RECOVER_INDEX                                                2008        //�ָ�����/����ʧ��

#ifdef __cplusplus
extern "C"
{
#endif
    //int ConnectToDB();
    int PackAnswerPackage(IF2Packer* lpOutPacker, int nErrorNo, char* sErrorInfo, char* sErrorPathInfo);
    //TODO

#ifdef __cplusplus
}
#endif

#endif	/* COMMON_H */

