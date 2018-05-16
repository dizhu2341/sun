#ifndef _GLOBAL_FUNC_H_
#define _GLOBAL_FUNC_H_

#define TABLE_NAME_LENGTH 32      /*表名最大长度*/ 
#define MAX_SQL_LENGTH 10001       /*SQL的最大长度*/
#define MAX_TABLE_MAP 30 					//一张O3表可能拆分成多张O4表，随意对应多条记录，此处为最大的映射数*/           

extern int GErrorNo;
extern char GErrorMessage[10240];
extern char GConfigFile[260];

extern "C"
{
//-------------------------------
// 函数功能：从配置文件读取配置信息
int hsGetConfig(const char *sKey, const char *sParam, char *sValue);

}

#endif
