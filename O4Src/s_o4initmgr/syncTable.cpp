#include <string.h>
#include "syncTable.h"

CSyncTableInfo::CSyncTableInfo(const char *pTableName, int nPriorityLevel, const char cAvailableProduct, const char *pPrcName, char *pTopicName)
{
    strcpy(m_sTableName, pTableName);
    m_nPriorityLevel = nPriorityLevel;
    m_cAvailableProduct = cAvailableProduct;
    strcpy(m_sPrcName, pPrcName);
	strcpy(m_sTopicName, pTopicName);
}

CSyncTableInfo::~CSyncTableInfo()
{
}

char *CSyncTableInfo::GetTableName()
{
    return m_sTableName;
}

int CSyncTableInfo::GetPriorityLevel()
{
    return m_nPriorityLevel;
}

char CSyncTableInfo::GetAvailableProduct()
{
    return m_cAvailableProduct;
}

char *CSyncTableInfo::GetPrcName()
{
    return m_sPrcName;
}

char *CSyncTableInfo::GetTopicName()
{
	return m_sTopicName;
}