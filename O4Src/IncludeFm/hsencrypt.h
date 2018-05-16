#ifndef _HS_ENCRYPT_H_
#define _HS_ENCRYPT_H_

#include <pthread.h>

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
private:
	pthread_mutex_t encryptLock;
	pthread_mutex_t intercodeLock;
	
	char m_asciiTranA[128];
	char m_asciiTranB[128];
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
#ifdef __cplusplus
  }
#endif

#endif

