/* 
 * File:   syncTable.h
 * Author: wangzh19004
 *
 * Created on 2017年1月10日, 下午7:29
 */

#ifndef SYNCTABLE_H
#define	SYNCTABLE_H

class CSyncTableInfo
{
public:
    CSyncTableInfo(const char *pTableName, int nPriorityLevel, const char cAvailableProduct, const char *pPrcName, char *pTopicName);
    ~CSyncTableInfo();
    
    char *GetTableName();
    int GetPriorityLevel();
    char GetAvailableProduct();
    char *GetPrcName();
	char *GetTopicName();
    
private:
    char m_sTableName[128];
    int m_nPriorityLevel;// 优先级
    char m_cAvailableProduct;// 适用的对接子系统
    char m_sPrcName[256];// 日初同步存储过程
	char m_sTopicName[128];
};

#endif	/* SYNCTABLE_H */

