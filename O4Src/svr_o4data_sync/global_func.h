#ifndef _GLOBAL_FUNC_H_
#define _GLOBAL_FUNC_H_

#define TABLE_NAME_LENGTH 32      /*������󳤶�*/ 
#define MAX_SQL_LENGTH 10001       /*SQL����󳤶�*/
#define MAX_TABLE_MAP 30 					//һ��O3����ܲ�ֳɶ���O4�������Ӧ������¼���˴�Ϊ����ӳ����*/           

extern int GErrorNo;
extern char GErrorMessage[10240];
extern char GConfigFile[260];

extern "C"
{
//-------------------------------
// �������ܣ��������ļ���ȡ������Ϣ
int hsGetConfig(const char *sKey, const char *sParam, char *sValue);

}

#endif
