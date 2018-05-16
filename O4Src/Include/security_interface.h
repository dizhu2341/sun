#ifndef SECURITY_H
#define SECURITY_H

#include <Include/plugin_interface.h>

#define SID_CERT			"com.hundsun.fbase.cert"
#define SID_SECURITY		"com.hundsun.fbase.security"

struct ICert : public IKnown
{
	/// 取当前使用的数字证书对应公钥, 缓冲区由调用者管理, 通过FreeMem释放
	/**
	 *@param pLen: 公钥数据长度指针
	 *@return:     公钥缓冲指针(通过FreeMem方法释放)
	 */	
	virtual unsigned char* FUNCTION_CALL_MODE GetPublicKey(int* pLen = NULL) = 0;
	
	/// 取当前使用的数字证书对应私钥, 缓冲区由调用者管理, 通过FreeMem释放
	/**
	 *@param pLen: 私钥数据长度指针
	 *@return:     私钥缓冲指针(通过FreeMem方法释放)
	 */	
	virtual unsigned char* FUNCTION_CALL_MODE GetPrivateKey(int* pLen = NULL) = 0;
	
	/// 取当前使用的数字证书, 缓冲区由调用者管理, 通过FreeMem释放
	/**
	 *@param pLen: 证书数据长度指针
	 *@return:     证书数据缓冲指针(通过FreeMem方法释放)
	 */		
	virtual unsigned char* FUNCTION_CALL_MODE GetCertBuf(int* pLen) = 0;
	
	///
	/**
	 *@param lpBuf: 需释放的缓冲指针
	 */
	virtual void FUNCTION_CALL_MODE FreeMem(void* lpBuf) = 0;
};

/// 返回值为0表示操作成功, <0表示操作失败

enum EVPCipher {EVP_ENC_NULL = 0, EVP_DES_CBC};

struct ISecurity : public IKnown
{
	/// 设置证书目录, 本模块有一默认的证书目录, 默认目录外的受信任证书的目录都通过该方法进行显式设置
	/**
	 *@param szPath: 受信任证书目录
	 *@return:
	 */
	virtual int FUNCTION_CALL_MODE SetCertsPath(const char* szPath) = 0;
	
	/// 导入指定身份相应的证书及私钥
	/**
	 *@param szIdentity: 身份标识
	 *@param lpPwd: 保护私钥的对称加密密钥
	 *@return:证书对象指针, null为导入失败
	 */
	virtual ICert* FUNCTION_CALL_MODE LoadCertStuff(const char* szIdentity, const char* szPwd) = 0;	
	
	/// 导入证书缓冲，生成证书对象
	/**
	 *@param lpCertBuf: 数字证书缓冲指针
	 *@param iCertLen: 证书长度
	 *@return:证书对象指针, null为导入失败
	 */
	virtual ICert* FUNCTION_CALL_MODE LoadCertBuf(const void* lpCertBuf, int iCertLen) = 0;
	
	/// 校验证书合法性
	/**
	 *@param pCert:	待校验证书
	 *@param szName:待校验证书持有者
	 *@param pAu:	校验证书
	 *@return:
	 */
	virtual int FUNCTION_CALL_MODE ValidateCert(const ICert* pCert, const char* szName, const ICert *pAu) = 0;
	
	///
	/**
	 *@param key:	密钥
	 *@param in:	明文缓冲
	 *@param inlen:	明文数据长度
	 *@return	0:  成功
	 			-1: 失败
	 */
	virtual int FUNCTION_CALL_MODE  SymmetryEnc(const unsigned char* key, const unsigned char *in, const unsigned inlen) = 0;
							
	///
	/**
	 *@param key:	密钥
	 *@param in:	密文缓冲
	 *@param inlen:	密文数据长度
	 *@return	0:  成功
	 			-1: 失败
	 */
	virtual int FUNCTION_CALL_MODE  SymmetryDec(const unsigned char* key, const unsigned char *in, const unsigned inlen) = 0;

	///
	/**
	 *@param keydata:	私钥
	 *@param keylen:	私钥长度
	 *@param in:		待加密明文缓冲
	 *@param inlen:		明文数据长度
	 *@param out:		加密后密文缓冲				
	 *@param outlen:	输入输出参数, 传入明文缓冲长度, 传出明文数据实际长度
	 *@return	0:  成功
	 			-1: 内存不足
	 			-2: 不可识别的密钥
				-3: 不合法的密钥长度
				-4: 上下文初始化失败
				-5: 密钥类型不匹配
				-6: 未支持的密钥长度
				-7: 未知错误
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
