#include "basepub.h"
#include "d3des.h"

CBasePublic gBasePublic;

CBasePublic::CBasePublic()
{
	memset(m_asciiTranA, 0, sizeof(m_asciiTranA));
	memset(m_asciiTranB, 0, sizeof(m_asciiTranB));
	InitAsciiMap();
	pthread_mutex_init(&encryptLock, NULL);
	pthread_mutex_init(&intercodeLock, NULL);
}

CBasePublic::~CBasePublic()
{
	pthread_mutex_destroy(&encryptLock);
	pthread_mutex_destroy(&intercodeLock); 
}

int CBasePublic::HsEncrypt(const char *key,const char *s1,char *s2)
{
	unsigned char key2[16],tmp1[16],tmp2[16];
	char tmpKey[16];
	int i;

	if(strlen(s1)>16)
	{
		return -1;
	}
	if(strlen(key)>15)
	{
		return -1;
	}

	pthread_mutex_lock(&encryptLock);   //����

	memset(tmpKey, 0, sizeof(tmpKey));
	memcpy(tmpKey, key, strlen(key));

	make2key(tmpKey,key2);
	des2key(key2,0);

	memset(tmp1, 0, sizeof(tmp1));
	memcpy(tmp1, s1, strlen(s1));

	D2des(tmp1,(unsigned char *)tmp2);

	for (i=0; i<16;i++) 
	{
		s2[i*2]   = (char)(tmp2[i]/16 +( (tmp2[i]/16>=10)?'A'-10:'0' ));
		s2[i*2+1] = (char)(tmp2[i]%16 +( (tmp2[i]%16>=10)?'A'-10:'0' ));
	} 
	s2[32]='\0';

	pthread_mutex_unlock(&encryptLock);  //�ͷ���

	return 0;
}

int CBasePublic::HsDecrypt(const char *key,const char *s1,char *s2)
{
	unsigned char key2[16],tmp1[16],tmp2[16];
	char tmpKey[16];
	int i;

	if(strlen(s1)!=32)
		return -1;
	if(strlen(key)>15)
		return -1;
	
	pthread_mutex_lock(&encryptLock);   //����

	memset(tmpKey, 0, sizeof(tmpKey));
	memcpy(tmpKey, key, strlen(key));

	make2key(tmpKey,key2);
	des2key(key2,1);

	for (i=0; i < 32; i+=2) 
	{
		tmp1[i/2] = (char)((s1[i] - ((s1[i] >= 'A')?('A'-10) : '0')) * 16 + (s1[i+1] - ((s1[i+1] >= 'A')?('A'-10) : '0')));
	}

	D2des(tmp1,(unsigned char *)tmp2);
	memcpy(s2,tmp2,sizeof(tmp2));
	if (strlen(s2)>16)
	{
		s2[16]='\0';
	}

	pthread_mutex_unlock(&encryptLock);  //�ͷ���

	return 0;
}

int CBasePublic::LockCreateInterCode()
{
	return pthread_mutex_lock(&intercodeLock);		/*lint !e454*/
}													/*lint !e456*/

int CBasePublic::UnlockCreateInterCode()
{
	return pthread_mutex_unlock(&intercodeLock);	/*lint !e455*/
}

void CBasePublic::InitAsciiMap()
{
	char src1[] = {"abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789 &"};
	char src2[] = {"cA1aBb2d Ce3fD4E5&Flm6nopGq7rHsjkt8uIv9wJxKyLzMNOPQgh0iRSTUVWXYZ"};
	int i=0, len = strlen(src1);
	for (i=0; i<len; ++i)
	{
		m_asciiTranA[src1[i]] = src2[i];
		m_asciiTranB[src2[i]] = src1[i];
	}
}

int CBasePublic::InterCodeEncrypt(int srcInterCode)
{
	int dstInterCode = 0;
	if (srcInterCode <= 0)
	{
		return srcInterCode;
	}

	int	one = srcInterCode % 10; srcInterCode /= 10;  one = (one+2)%10;
	int two = srcInterCode % 10; srcInterCode /= 10;  two = (two+2)%10;
	int three = srcInterCode %10; srcInterCode /= 10; three = (three+2)%10;
	int four = srcInterCode %10; srcInterCode /= 10;  four = (four+2)%10;
	int five = srcInterCode %10; srcInterCode /= 10;  five = (five+2)%10;
	int six = srcInterCode %10; srcInterCode /= 10;   six = (six+2)%10;
	int seven = srcInterCode %10; srcInterCode /= 10; seven = (seven+2)%10;
    int eight = srcInterCode %10; srcInterCode /= 10; eight = (eight+2)%10;

	dstInterCode = srcInterCode*100000000 +
			four*10000000 +
			three*1000000 +
			two*100000 + 
			one*10000 + 
			eight*1000 + 
			seven*100 + 
			six*10 + 
			five; 
    return dstInterCode;
}

int CBasePublic::InterCodeDectypt(int srcInterCode)
{
	int dstInterCode = 0;
	if (srcInterCode <= 0)
	{
		return srcInterCode;
	}

	int	one = srcInterCode % 10; srcInterCode /= 10;  one = (one+8)%10;
	int two = srcInterCode % 10; srcInterCode /= 10;  two = (two+8)%10;
	int three = srcInterCode %10; srcInterCode /= 10; three = (three+8)%10;
	int four = srcInterCode %10; srcInterCode /= 10;  four = (four+8)%10;
	int five = srcInterCode %10; srcInterCode /= 10;  five = (five+8)%10;
	int six = srcInterCode %10; srcInterCode /= 10;   six = (six+8)%10;
	int seven = srcInterCode %10; srcInterCode /= 10; seven = (seven+8)%10;
	int eight = srcInterCode %10; srcInterCode /= 10; eight = (eight+8)%10;

    dstInterCode = srcInterCode*100000000 +
        four*10000000 +
        three*1000000 +
        two*100000 + 
        one*10000 + 
        eight*1000 + 
        seven*100 + 
        six*10 + 
        five; 
    return dstInterCode;
}

char* CBasePublic::ReportCodeEncrypt(const char* srcReportCode, char* dstReportCode)
{
	if (NULL == srcReportCode || NULL == dstReportCode)
		return NULL;
	
	int i = 0, len = strlen(srcReportCode);
	memset(dstReportCode, 0, sizeof(dstReportCode));
	
	for (i=0; i<len; ++i)
	{
		dstReportCode[i] = m_asciiTranA[srcReportCode[i]];
	}
	dstReportCode[i] = '\0';
	return dstReportCode;
}

char* CBasePublic::ReportCodeDecrypt(const char* srcReportCode, char* dstReportCode)
{
	if (NULL == srcReportCode || NULL == dstReportCode)
		return NULL;

	int i = 0, len  = strlen(srcReportCode);
	memset(dstReportCode, 0, sizeof(dstReportCode));
	
	for (i=0; i<len; ++i)
	{
		dstReportCode[i] = m_asciiTranB[srcReportCode[i]];
	}
	dstReportCode[i] = '\0';
	return dstReportCode;
}

bool CBasePublic::InsertHashInterCode(int marketNo, char *reportCode, int interCode)
{
	char temp[128] = {0};
	int len = 0;
	len = sprintf(temp, "%d%s", marketNo, reportCode);
	if (len > 0)
	{
		string sIndex(temp);
		m_ICHash[sIndex] = interCode;
		return true;
	}
	return false;
}

int CBasePublic::SearchHashInterCode(int marketNo, char *reportCode)
{
	char temp[128] = {0};
	sprintf(temp, "%d%s", marketNo, reportCode);
	string sIndex(temp);
	return m_ICHash[sIndex];
}


//========================================================================================================
// �������ⲿ�ĺ���

/*********************************
�������ƣ�hsEncryptExNew
�������ܣ�����
���������
 key: ��Կ��֧��0-15λ����
 s1: ���룬֧��0-16λ����
����������
 s2: ���ܺ������,����32
����ֵ��
 0:  ����
 -1: ��Կ������ĳ���Խ��
 -2: ��������
**************************************/
int hsEncryptExNew(const char *key,const char *s1,char *s2)
{
	return gBasePublic.HsEncrypt(key, s1, s2);
}


/*************************************
�������ƣ�hsDecryptExNew
�������ܣ�����
���������
 key: ��Կ��֧��0-15λ����
 s1: ���ģ�32λ����
����������
 s2: ���ܺ�����ģ�֧��0-16λ����
����ֵ��
 0: ����
 -1: ��Կ������ĳ���Խ��
 -2: ��������
**************************************/
int hsDecryptExNew(const char *key,const char *s1,char *s2)
{
	return gBasePublic.HsDecrypt(key, s1, s2);
}

/*************************************
�������ƣ�hsLockInterCode
�������ܣ���֤ȯ���������߳�����
���������
����������
����ֵ��
 0: ����
 ��������
**************************************/
int hsLockCreateInterCode()
{
	return gBasePublic.LockCreateInterCode();
}

/*************************************
�������ƣ�hsUnlockInterCode
�������ܣ���֤ȯ���������߳̽���
���������
����������
����ֵ��
 0: ����
 ��������
**************************************/
int hsUnlockCreateInterCode()
{
	return gBasePublic.UnlockCreateInterCode();
}

/*************************************
�������ƣ�hsInterCodeEncrypt
�������ܣ�����֤ȯ����
���������
 srcInterCode: ����ǰ��֤ȯ����
����ֵ��
 dstInterCode: ���ܺ��֤ȯ����
**************************************/
int hsInterCodeEncrypt(int srcInterCode)
{
	return gBasePublic.InterCodeEncrypt(srcInterCode);
}

/*************************************
�������ƣ�hsInterCodeDectypt
�������ܣ�����֤ȯ����
���������
 srcInterCode: ����ǰ��֤ȯ����
����ֵ��
 dstInterCode: ���ܺ��֤ȯ����
**************************************/
int hsInterCodeDectypt(int srcInterCode)
{
	return gBasePublic.InterCodeDectypt(srcInterCode);
}

/*************************************
�������ƣ�hsReportCodeEncrypt
�������ܣ�����֤ȯ����
���������
 srcReportCode: ����ǰ��֤ȯ����
 dstReportCode: ���ܺ��֤ȯ����
����ֵ��
 dstReportCode: ���ܺ��֤ȯ����
**************************************/
char* hsReportCodeEncrypt(const char* srcReportCode, char* dstReportCode)
{
	return gBasePublic.ReportCodeEncrypt(srcReportCode, dstReportCode);
}

/*************************************
�������ƣ�hsReportCodeDecrypt
�������ܣ�����֤ȯ����
���������
 srcReportCode: ����ǰ��֤ȯ����
 dstReportCode: ���ܺ��֤ȯ����
����ֵ��
 dstReportCode: ���ܺ��֤ȯ����
**************************************/
char* hsReportCodeDecrypt(const char* srcReportCode, char* dstReportCode)
{
	return gBasePublic.ReportCodeDecrypt(srcReportCode, dstReportCode);
}

/*************************************
�������ƣ�hsInterCodeInsert
�������ܣ�����֤ȯ����
���������
 marketNo: �����г�
 reportCode: �걨����
 interCode:	֤ȯ����
**************************************/

bool hsInterCodeInsert(int marketNo, char *reportCode, int interCode)
{
	return gBasePublic.InsertHashInterCode(marketNo, reportCode, interCode);
}

/*************************************
�������ƣ�hsInterCodeSearch
�������ܣ���ѯ֤ȯ����
���������
 marketNo: �����г�
 reportCode: �걨����
����ֵ��
 interCode: ֤ȯ����
**************************************/
int hsInterCodeSearch(int marketNo, char *reportCode)
{
	return gBasePublic.SearchHashInterCode(marketNo, reportCode);
}
