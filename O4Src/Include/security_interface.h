#ifndef SECURITY_H
#define SECURITY_H

#include <Include/plugin_interface.h>

#define SID_CERT			"com.hundsun.fbase.cert"
#define SID_SECURITY		"com.hundsun.fbase.security"

struct ICert : public IKnown
{
	/// ȡ��ǰʹ�õ�����֤���Ӧ��Կ, �������ɵ����߹���, ͨ��FreeMem�ͷ�
	/**
	 *@param pLen: ��Կ���ݳ���ָ��
	 *@return:     ��Կ����ָ��(ͨ��FreeMem�����ͷ�)
	 */	
	virtual unsigned char* FUNCTION_CALL_MODE GetPublicKey(int* pLen = NULL) = 0;
	
	/// ȡ��ǰʹ�õ�����֤���Ӧ˽Կ, �������ɵ����߹���, ͨ��FreeMem�ͷ�
	/**
	 *@param pLen: ˽Կ���ݳ���ָ��
	 *@return:     ˽Կ����ָ��(ͨ��FreeMem�����ͷ�)
	 */	
	virtual unsigned char* FUNCTION_CALL_MODE GetPrivateKey(int* pLen = NULL) = 0;
	
	/// ȡ��ǰʹ�õ�����֤��, �������ɵ����߹���, ͨ��FreeMem�ͷ�
	/**
	 *@param pLen: ֤�����ݳ���ָ��
	 *@return:     ֤�����ݻ���ָ��(ͨ��FreeMem�����ͷ�)
	 */		
	virtual unsigned char* FUNCTION_CALL_MODE GetCertBuf(int* pLen) = 0;
	
	///
	/**
	 *@param lpBuf: ���ͷŵĻ���ָ��
	 */
	virtual void FUNCTION_CALL_MODE FreeMem(void* lpBuf) = 0;
};

/// ����ֵΪ0��ʾ�����ɹ�, <0��ʾ����ʧ��

enum EVPCipher {EVP_ENC_NULL = 0, EVP_DES_CBC};

struct ISecurity : public IKnown
{
	/// ����֤��Ŀ¼, ��ģ����һĬ�ϵ�֤��Ŀ¼, Ĭ��Ŀ¼���������֤���Ŀ¼��ͨ���÷���������ʽ����
	/**
	 *@param szPath: ������֤��Ŀ¼
	 *@return:
	 */
	virtual int FUNCTION_CALL_MODE SetCertsPath(const char* szPath) = 0;
	
	/// ����ָ�������Ӧ��֤�鼰˽Կ
	/**
	 *@param szIdentity: ��ݱ�ʶ
	 *@param lpPwd: ����˽Կ�ĶԳƼ�����Կ
	 *@return:֤�����ָ��, nullΪ����ʧ��
	 */
	virtual ICert* FUNCTION_CALL_MODE LoadCertStuff(const char* szIdentity, const char* szPwd) = 0;	
	
	/// ����֤�黺�壬����֤�����
	/**
	 *@param lpCertBuf: ����֤�黺��ָ��
	 *@param iCertLen: ֤�鳤��
	 *@return:֤�����ָ��, nullΪ����ʧ��
	 */
	virtual ICert* FUNCTION_CALL_MODE LoadCertBuf(const void* lpCertBuf, int iCertLen) = 0;
	
	/// У��֤��Ϸ���
	/**
	 *@param pCert:	��У��֤��
	 *@param szName:��У��֤�������
	 *@param pAu:	У��֤��
	 *@return:
	 */
	virtual int FUNCTION_CALL_MODE ValidateCert(const ICert* pCert, const char* szName, const ICert *pAu) = 0;
	
	///
	/**
	 *@param key:	��Կ
	 *@param in:	���Ļ���
	 *@param inlen:	�������ݳ���
	 *@return	0:  �ɹ�
	 			-1: ʧ��
	 */
	virtual int FUNCTION_CALL_MODE  SymmetryEnc(const unsigned char* key, const unsigned char *in, const unsigned inlen) = 0;
							
	///
	/**
	 *@param key:	��Կ
	 *@param in:	���Ļ���
	 *@param inlen:	�������ݳ���
	 *@return	0:  �ɹ�
	 			-1: ʧ��
	 */
	virtual int FUNCTION_CALL_MODE  SymmetryDec(const unsigned char* key, const unsigned char *in, const unsigned inlen) = 0;

	///
	/**
	 *@param keydata:	˽Կ
	 *@param keylen:	˽Կ����
	 *@param in:		���������Ļ���
	 *@param inlen:		�������ݳ���
	 *@param out:		���ܺ����Ļ���				
	 *@param outlen:	�����������, �������Ļ��峤��, ������������ʵ�ʳ���
	 *@return	0:  �ɹ�
	 			-1: �ڴ治��
	 			-2: ����ʶ�����Կ
				-3: ���Ϸ�����Կ����
				-4: �����ĳ�ʼ��ʧ��
				-5: ��Կ���Ͳ�ƥ��
				-6: δ֧�ֵ���Կ����
				-7: δ֪����
	 */
	virtual	int FUNCTION_CALL_MODE  PrivateEnc(const unsigned char* keydata, unsigned keylen,
											const unsigned char *in, const unsigned inlen, 
											unsigned char *out, unsigned *outlen) = 0;
											
	virtual	int FUNCTION_CALL_MODE  PrivateDec(const unsigned char* keydata, unsigned keylen,
											const unsigned char *in, const unsigned inlen, 
											unsigned char *out, unsigned *outlen) = 0;
											
	virtual	int FUNCTION_CALL_MODE  PublicEnc(const unsigned char* keydata, unsigned keylen,
											const unsigned char *in, const unsigned inlen, 
											unsigned char *out, unsigned *outlen) = 0;
											
	virtual	int FUNCTION_CALL_MODE  PublicDec(const unsigned char* keydata, unsigned keylen,
											const unsigned char *in, const unsigned inlen, 
											unsigned char *out, unsigned *outlen) = 0;
											
	virtual int FUNCTION_CALL_MODE DecCfgObj(IRCfgObj* lpCo) = 0;
};

#ifdef __cplusplus
extern "C" {
#endif

	int  FUNCTION_CALL_MODE SecurityInit(void*, PFOnSetTimeOut = NULL);

	IKnown * FUNCTION_CALL_MODE GetSecurityInstance(void);

	char* FUNCTION_CALL_MODE GetSecurityDependence(void*);

	int FUNCTION_CALL_MODE GetSecurityInfo(int, tagBaseServiceInfo*);

#ifdef __cplusplus
  }
#endif

#endif
