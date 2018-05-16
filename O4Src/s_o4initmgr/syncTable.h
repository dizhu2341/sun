/* 
 * File:   syncTable.h
 * Author: wangzh19004
 *
 * Created on 2017��1��10��, ����7:29
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
    int m_nPriorityLevel;// ���ȼ�
    char m_cAvailableProduct;// ���õĶԽ���ϵͳ
    char m_sPrcName[256];// �ճ�ͬ���洢����
	char m_sTopicName[128];
};

#endif	/* SYNCTABLE_H */

