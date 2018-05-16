#ifndef _HS_ENCRYPT_H_
#define _HS_ENCRYPT_H_

#include <iostream>
#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
//#include <ext/hash_map>
#include <tr1/unordered_map>
#include <string>

//using __gnu_cxx::hash_map;
using std::string;
using std::tr1::unordered_map;

typedef unordered_map<string, int>	ICMAP;

class CBasePublic
{
public:
	CBasePublic();
	~CBasePublic();

public:
	int HsEncrypt(const char *key,const char *s1,char *s2);
	int HsDecrypt(const char *key,const char *s1,char *s2);
	
	int LockCreateInterCode();
	int UnlockCreateInterCode();
	
	int InterCodeEncrypt(int srcInterCode);
	int InterCodeDectypt(int srcInterCode);
	char* ReportCodeEncrypt(const char* srcReportCode, char* dstReportCode);
	char* ReportCodeDecrypt(const char* srcReportCode, char* dstReportCode);
	void InitAsciiMap();
	
	bool InsertHashInterCode(int marketNo, char *reportCode, int interCode);
	int SearchHashInterCode(int marketNo, char *reportCode);
private:
	pthread_mutex_t encryptLock;
	pthread_mutex_t intercodeLock;
	
	char m_asciiTranA[128];
	char m_asciiTranB[128];
	
	ICMAP m_ICHash;
};

#ifdef __cplusplus
extern "C" { 
#endif

int hsEncryptExNew(const char *key,const char *s1,char *s2);
int hsDecryptExNew(const char *key,const char *s1,char *s2);

int hsLockCreateInterCode();
int hsUnlockCreateInterCode();

int hsInterCodeEncrypt(int srcInterCode);
int hsInterCodeDectypt(int srcInterCode);
char* hsReportCodeEncrypt(const char* srcReportCode, char* dstReportCode);
char* hsReportCodeDecrypt(const char* srcReportCode, char* dstReportCode);

//证券内码哈希表相关函数
bool hsInterCodeInsert(int marketNo, char *reportCode, int interCode);
int hsInterCodeSearch(int marketNo, char *reportCode);

#ifdef __cplusplus
  }
#endif

#endif

