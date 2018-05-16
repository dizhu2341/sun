/* 
 * File:   DataSync.h
 * Author: zhouyx11685
 * Description: ����ͬ������
 * Created on 2015��11��9��, ����4:10
 */

#ifndef DATASYNC_H
#define DATASYNC_H

#include <pthread.h>
#include <string>
#include <vector>
#include "hshead.h"
#include "Common.h"

using namespace std;

// ��Ҫͬ�����ֶ���, jc_tsyncField

class CSyncFieldInfo
{
public:
    string FieldName;
    string ColName;
    char FieldType;
    string ColType;
    int FieldWidth;
    int FieldScale;
    string DefaultValue;
    bool IsUse;

    CSyncFieldInfo(string fieldName, string colName, char fieldType, int fieldWidth, int fieldScale, string defaultValue, bool isUse)
    {
        FieldName = fieldName;
        ColName = colName;
        FieldType = fieldType;
        if ('I' == fieldType || 'D' == fieldType)
            ColType = "NUMBER";
        else if ('C' == fieldType)
            ColType = "CHAR";
        else
            ColType = "VARCHAR2";
        FieldWidth = fieldWidth;
        FieldScale = fieldScale;
        DefaultValue = defaultValue;
        IsUse = isUse;
    }
};

// ORA���ݿ��ֶ���Ϣ��, o3

class COraColInfo
{
public:
    string ColName;
    string ColType;
    int DataLen;
    int DataPrec;
    int DataScale;

    COraColInfo(string colName, string colType, int dataLen, int dataPrec, int dataScale)
    {
        ColName = colName;
        ColType = colType;
        DataLen = dataLen;
        DataPrec = dataPrec;
        DataScale = dataScale;
    }
};

// ����ͬ������
class CDataSync
{
public:
    CDataSync(IAS2Context * lpContext);
    virtual ~CDataSync();

    bool doSync(char cSyncFlag);
    int GetErrorNo();
    char *GetErrorInfo();

protected:
    virtual bool ExpO3View2Temp(); // ��O32�������ݵ���ʱ��
    virtual bool ExpTemp2Dst(); // ����ʱ�������ݵ�Ŀ���
    virtual bool AfterAction();

protected:
    bool Lock();
    bool UnLock();
    bool Init();
    void SqlErrorAction();

    bool SyncToMDB(char *sTableName, char* sWhereStr);
    void SetErrorInfo(int nErrNo, const char* sErrInfoFmt, ...);

    // �ֶξ���У����غ���
    bool CheckSyncFieldValid();
    bool GetSyncFieldLst();
    bool GetO32ColInfoLst(vector<COraColInfo*> &oraColVec);

    // ���м�ת����Ĳ��ݵĺ���
    bool ClearTempTable();
    bool IsTmpTableExists();
    bool DropTmpTable();
    bool CreateTmpTable();

    // ͬ��ǰ����������غ���
    bool BeforeAction();
    bool SyncAction();
    bool GetLoopInfo();
    int GetViewRecordCount();
    bool CheckO3DataValid();

    //���ݱ�����������غ���
    bool DropTableIndex();
    bool RecoverTableIndex();

protected:
    IAS2Context* m_lpContext;
    IConnection *m_lpO3Conn;
    IConnection *m_lpO4Conn;

    pthread_mutex_t* m_syncLock;

    vector<CSyncFieldInfo*> syncFieldVec;

    void* m_lpDataRecord;
    char m_cSyncFlag; //1-�ճ�ͬ��; 2-�ռ�ͬ����ȫ��
    int m_nTotalRows; //������������
    unsigned int m_nLoopTimes; //ѭ������
    unsigned int m_nBatchRows; //ÿ����ָ�����������
    unsigned int m_nRemainRows; //���һ���β������������
    unsigned int m_nFetchRows; //ʵ��ÿ���β������������

    char m_sSrcTable[128];
    char m_sSrcView[128];
    char m_sTmpTable[128];
    char m_sDstTable[128];

    // ������Ϣ
    int m_nErrNo;
    char m_sErrInfo[2048];
};

//O3��ͼ��Ϣ��
class CO3ViewInfo
{
public:
    string m_sViewName;
    IConnection *m_lpO3Conn;
    // ������Ϣ
    int m_nErrNo;
    string m_sErrInfo;
    
public:
    CO3ViewInfo(IConnection * lpO3Conn, string sViewName);
    ~CO3ViewInfo();
    
    bool IsUniqueViolated(string m_sUKColList, int nColumnCount);
    int GetErrorNo();
    string GetErrorInfo();
    void SetErrorInfo(int nErrNo, const string sErrInfo);
private:
    bool IsColumnExist(string m_sUKColList, int nColumnCount);
};

//O4�������ݱ���Ϣ��
class CO4TabInfo
{
public:
    IConnection *m_lpO4Conn;
    string m_sTableName;
    
    /*�����ֶ��б�*/
    string m_sPKColList;
    
    /*Ψһ�����ֶ�����*/
    vector<string> m_vUKColArr;
    
    // ������Ϣ
    int m_nErrNo;
    string m_sErrInfo;

public:
    CO4TabInfo(IConnection * lpO4Conn, string sTableName);
    ~CO4TabInfo();
    
    string GetPKColList();
    vector<string> GetUKColArr();
    bool QueryPKColList();
    bool QueryUKColArr();
    int GetErrorNo();
    string GetErrorInfo();
    void SetErrorInfo(int nErrNo, const string sErrInfo);
    
    int GetKeyColumnCount();
    int GetIndexColumnCount(int iIndex);
    
private:
    // �����ֶθ���
    int m_nKeyColumnCount;
    // Ψһ�����ֶθ���
    int m_nIndexColumnCount[32];
};
#endif
