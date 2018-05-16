#ifndef _PROC_MAIN_H_
#define _PROC_MAIN_H_	 

#ifdef __cplusplus
extern "C"  
{  
#endif

#include <stdlib.h>
#include <string.h>
#include <memory.h>
#include <assert.h>
#include <ctype.h>


#include <Include/connection_interface.h>
#include <Include/esb_message_interface.h>
#include <Include/tag_def.h>
#include "global_func.h"
#include "hsencrypt.h"
#include "spub.h"
#include "initenable.h"

//------------------------------------------
// 插件初始化
int ServerInitial();

//------------------------------------------
//具体的服务初始化操作  
int ServiceInitial(void);

//---------------------------------------
// 获取需要转换的表名列表, 返回获取到的记录数
int GetConvertTablesInfo(char ConvertTables[100][TABLE_NAME_LENGTH]);

//-----------------------------------------
// 执行SQL
bool ExecuteSQL(const char* lpSQL);


#ifdef __cplusplus
}  
#endif

typedef enum ERefreshType
{
	REFRESH_RC = -1,     // 日初
	REFRESH_ADD = 1,
	REFRESH_UPDATE = 2,
	REFRESH_DELETE = 3,
	REFRESH_ALL = 4,
	REFRESH_UNDEFINE
}ERefreshType;

//------------------------------------------------
// 数据转换类
class CDataConvert
{
public:
	CDataConvert(const char* pTableName, const char * pRefreshType, IF2UnPacker* unPacker);
	CDataConvert(const char* pTableName, int nInitDate);
	~CDataConvert();

	void Convert();	

private:
	bool GetConvertConfig();
	void PrintConvertConfig();
	bool SelectSQL(const char* lpSQL);
	char* GetExecSQL(int nIndex);
	void PackSvrInParam(int nIndex);
	void PackRcInParam(int nIndex);
	void PackRjInParam(int nIndex);
	bool SyncData(int nIndex);
	
private:
	char 						m_szTableName[TABLE_NAME_LENGTH];			// 表名
	int 						m_nInitDate;								// 初始化日期
	ERefreshType   	m_refreshType;												// 刷新类别
	IF2UnPacker*    m_lpDataUnpacker;											// 刷新的数据集
	// 转换配置信息保存变量, 一张O3表可能对应多张O4表，此处设置最多对应5张表
	char						m_szO4TableName[MAX_TABLE_MAP][TABLE_NAME_LENGTH];
	char            m_szPrimaryStr[MAX_TABLE_MAP][256];
	char            m_szConvertSQL[MAX_TABLE_MAP][MAX_SQL_LENGTH]; 
	char            m_szPreSQL[MAX_TABLE_MAP][256];
	int             m_nRcFuncNo[MAX_TABLE_MAP];
	int 						m_nRjFuncNo[MAX_TABLE_MAP];
	char 						m_szFilePath[MAX_TABLE_MAP][512];
	char 						m_szExportFileName[MAX_TABLE_MAP][512];
	char						m_bSaveToDB[MAX_TABLE_MAP];
	int							m_nMapCount; 
	// 最终获取到的数据
	IF2Packer *     m_lpResultSet;
	IF2Packer *     m_lpSvrInParam;
};

#endif
