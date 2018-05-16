/* 
 * File:   DataSync.h
 * Author: zhouyx11685
 * Description: 数据同步基类
 * Created on 2015年11月9日, 下午4:10
 */

#ifndef DATASYNC_H
#define DATASYNC_H

#include <pthread.h>
#include <string>
#include <vector>
#include "hshead.h"
#include "Common.h"

using namespace std;

// 需要同步的字段类, jc_tsyncField

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

// ORA数据库字段信息类, o3

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

// 数据同步基类
class CDataSync
{
public:
    CDataSync(IAS2Context * lpContext);
    virtual ~CDataSync();

    bool doSync(char cSyncFlag);
    int GetErrorNo();
    char *GetErrorInfo();

protected:
    virtual bool ExpO3View2Temp(); // 从O32表导入数据到临时表
    virtual bool ExpTemp2Dst(); // 从临时表导入数据到目标表
    virtual bool AfterAction();

protected:
    bool Lock();
    bool UnLock();
    bool Init();
    void SqlErrorAction();

    bool SyncToMDB(char *sTableName, char* sWhereStr);
    void SetErrorInfo(int nErrNo, const char* sErrInfoFmt, ...);

    // 字段精度校验相关函数
    bool CheckSyncFieldValid();
    bool GetSyncFieldLst();
    bool GetO32ColInfoLst(vector<COraColInfo*> &oraColVec);

    // 对中间转换表的操纵的函数
    bool ClearTempTable();
    bool IsTmpTableExists();
    bool DropTmpTable();
    bool CreateTmpTable();

    // 同步前公共动作相关函数
    bool BeforeAction();
    bool SyncAction();
    bool GetLoopInfo();
    int GetViewRecordCount();
    bool CheckO3DataValid();

    //数据表主键操作相关函数
    bool DropTableIndex();
    bool RecoverTableIndex();

protected:
    IAS2Context* m_lpContext;
    IConnection *m_lpO3Conn;
    IConnection *m_lpO4Conn;

    pthread_mutex_t* m_syncLock;

    vector<CSyncFieldInfo*> syncFieldVec;

    void* m_lpDataRecord;
    char m_cSyncFlag; //1-日初同步; 2-日间同步（全表）
    int m_nTotalRows; //表数据总行数
    unsigned int m_nLoopTimes; //循环次数
    unsigned int m_nBatchRows; //每批次指定插入的数据
    unsigned int m_nRemainRows; //最后一批次插入的数据行数
    unsigned int m_nFetchRows; //实际每批次插入的数据行数

    char m_sSrcTable[128];
    char m_sSrcView[128];
    char m_sTmpTable[128];
    char m_sDstTable[128];

    // 错误信息
    int m_nErrNo;
    char m_sErrInfo[2048];
};

//O3视图信息类
class CO3ViewInfo
{
public:
    string m_sViewName;
    IConnection *m_lpO3Conn;
    // 错误信息
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

//O4基础数据表信息类
class CO4TabInfo
{
public:
    IConnection *m_lpO4Conn;
    string m_sTableName;
    
    /*主键字段列表*/
    string m_sPKColList;
    
    /*唯一索引字段数组*/
    vector<string> m_vUKColArr;
    
    // 错误信息
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
    // 主键字段个数
    int m_nKeyColumnCount;
    // 唯一索引字段个数
    int m_nIndexColumnCount[32];
};
#endif
