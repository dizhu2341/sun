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
// �����ʼ��
int ServerInitial();

//------------------------------------------
//����ķ����ʼ������  
int ServiceInitial(void);

//---------------------------------------
// ��ȡ��Ҫת���ı����б�, ���ػ�ȡ���ļ�¼��
int GetConvertTablesInfo(char ConvertTables[100][TABLE_NAME_LENGTH]);

//-----------------------------------------
// ִ��SQL
bool ExecuteSQL(const char* lpSQL);


#ifdef __cplusplus
}  
#endif

typedef enum ERefreshType
{
	REFRESH_RC = -1,     // �ճ�
	REFRESH_ADD = 1,
	REFRESH_UPDATE = 2,
	REFRESH_DELETE = 3,
	REFRESH_ALL = 4,
	REFRESH_UNDEFINE
}ERefreshType;

//------------------------------------------------
// ����ת����
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
	char 						m_szTableName[TABLE_NAME_LENGTH];			// ����
	int 						m_nInitDate;								// ��ʼ������
	ERefreshType   	m_refreshType;												// ˢ�����
	IF2UnPacker*    m_lpDataUnpacker;											// ˢ�µ����ݼ�
	// ת��������Ϣ�������, һ��O3����ܶ�Ӧ����O4���˴���������Ӧ5�ű�
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
	// ���ջ�ȡ��������
	IF2Packer *     m_lpResultSet;
	IF2Packer *     m_lpSvrInParam;
};

#endif
