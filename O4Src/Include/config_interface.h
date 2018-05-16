/// ���÷���ӿ�
/*******************************************************
  Դ��������:config.h
  �������Ȩ:�������ӹɷ����޹�˾
  ϵͳ����:  HS ESB
  ģ������:  config
  ����˵��: 
  ��    ��:  �з�����
  ��������:  20071108
  ��    ע:  

  �޸���Ա��
  �޸����ڣ�
  �޸�˵����
  20140613 majc ���ȡ��������Ϣ�ӿ�
*********************************************************/
#ifndef CONFIG_H
#define CONFIG_H
#include <Include/plugin_interface.h>

#define SID_RCFGOBJ			"com.hundsun.fbase.rcfgobj"
#define SID_WCFGOBJ			"com.hundsun.fbase.wcfgobj"
#define SID_CFGOBJMAKER		"com.hundsun.fbase.cfgobjmaker"
#define SID_CFGSVR			"com.hundsun.fbase.config"

struct IWCfgObj;

/// ֻ�����ö���ӿ�
struct IRCfgObj : public IKnown
{
	/// ����ָ�������������ö���
	/**
	 *@param szLocation: ���ö�����������Ϣ�е�λ��
	 * ��ͬ���͵��ļ��˲��������ĺ������в���,��������:
	 * XML: �Ӷ�����/�������/.../��n������ǩ��
	 * INI: �Ӷ�����
	 *@return : �������������ö���ָ��;ʧ�ܷ���NULL
	 */
	virtual IRCfgObj* FUNCTION_CALL_MODE GetChild(const char * szLocation) = 0;
        
	/// ������Ż��������
	/**
	 *@param iIndex:���Ե����(�ڼ�������)����Ϊ0
	 *@return :������;Խ�緵��NULL
	 */
	virtual const char * FUNCTION_CALL_MODE GetAttrName(int iIndex) = 0;
		
	///�����������������ֵ
	/**
	 *@param szName:������
	 *@return ����ֵ;δ�ҵ�Ŀ�귵��NULL
	 */
	virtual const char * FUNCTION_CALL_MODE GetAttrValue(const char * szName) = 0;
		
	/// ��ȡ�����ö�����ı����ݡ����ı�ֵ֮�н��пո��ַ�ʱ,��ΪNULL,����Ϊû���ı�ֵ;
	virtual const char * FUNCTION_CALL_MODE GetText(void) = 0;
		
	/// ��ö�����
	virtual const char * FUNCTION_CALL_MODE GetName(void) = 0;

	/// ��õ�һ�������ö���,�������ö�����ʧ�ܷ���NULL
	virtual IRCfgObj * FUNCTION_CALL_MODE GetFirstChild(void) = 0;
		
	/// ��ȡ��ǰ�������һ�ֵ����ö���,����һ�ֵ����ö��󷵻�NULL
	virtual IRCfgObj * FUNCTION_CALL_MODE GetSibling(void) = 0;
	
	virtual IWCfgObj * FUNCTION_CALL_MODE GetWritable(void) = 0;
	
//	/// ��������(�������Ӷ���)
//	virtual void FUNCTION_CALL_MODE Free(void) = 0;
};

/// ��д���ö���ӿ�
struct IWCfgObj : public IKnown
{      
	/// ������ԣ�������������򸲸�
	/**
	 *@param szName: ������
	 *@param szValue: ����ֵ
	 *@return: �ɹ�����0; ʧ�ܷ���-1
	 */
	virtual int FUNCTION_CALL_MODE SetAttr(const char * szName, const char * szValue) = 0;
		
	/// �����ı���Ϣ;
	/**
	 *@param szText: �ı���Ϣ
	 *@return: �ɹ�����0; ʧ�ܷ���-1
	 */
	virtual int FUNCTION_CALL_MODE SetText(const char * szText, int iLen = 0) = 0;
		
	/// ����ָ�������������ö������Ϊ��ǰ������Ӷ���
	/**
	 *@param szName:	Ҫ��ӵ��Ӷ�����
	 *@return:�ɹ�����0; ʧ�ܷ���-1
	 */
	virtual IWCfgObj * FUNCTION_CALL_MODE CreateChild(const char * szName) = 0;

	/// ɾ�������ö���
	/**
	 *@param lpCo: �Ӷ���ָ��
	 *@return: �ɹ�����0; �ö����Ǵ����ö���ĺ��ӷ���1��ʧ�ܷ���-1;
	 */
	virtual int FUNCTION_CALL_MODE OffChild(IRCfgObj * lpCo) = 0;
	
	///
	/**
	 *@
	 *@return: �ɹ�����0; �����ڸ����Է���1; ʧ�ܷ���-1;
	 */
	virtual int FUNCTION_CALL_MODE RemoveAttr(const char* szName) = 0;
};

/// ���ö������л��������л��ӿ�
struct ICfgObjMaker : public IKnown
{
	/// ����ָ���������Ŀ����ö���
	/** 
	 *@param szName:��ǩ��
	 *@return:�����ö���ָ��
	 */
	virtual IWCfgObj * FUNCTION_CALL_MODE MakeObject(const char * szName) = 0;
	///�������ļ���ȡ���ö���
	/**
	 *@param szFileUrl:		�ļ���Url���ļ���.
	 *@param szLocation:	���ö���λ�á���ͬ���͵��ļ��˲��������ĺ������в���,��������:
	 * XML: /����ǩ��/�β��ǩ��/.../��n����ǩ�����������ȱʡֵ,�򷵻ظ���ǩ��.
	 * INI: /��һά��; �������ȱ��ֵ���򷵻����ļ���Ϊ��һά���Ƶ�������
	 *@return: ���ö���ָ��.��������Ƿ�����Ŀ�����ö��󲻴����򷵻�NULL
	 */
	virtual IRCfgObj * FUNCTION_CALL_MODE LoadFromFile(const char * szFileUrl, const char * szLocation = "") = 0;

	///�������ö����д�ļ�.�������ļ����ڣ�����֮�����򴴽����ļ���
	/**
	 *@param lpCo:		���ö���
     *@param szFileUrl:	�ļ���
	 *@return: �ɹ�����0; ʧ�ܷ���-1
	 */
	virtual int FUNCTION_CALL_MODE SaveToFile(IRCfgObj * lpCo, const char * szFileUrl) = 0;

	///�ӻ�������ȡ���ö���
	/**
	 *@param lpBuf:			��������ַ
	 *@param iBufSize:		��������С
	 *@param szLocation:	���ö���λ��
	 *@return: ���ö���ָ��.��������Ƿ�����Ŀ�����ö��󲻴����򷵻�NULL
	 */
	virtual IRCfgObj * FUNCTION_CALL_MODE LoadFromBuf(void * lpBuf, int iBufSize, const char * szLocation = "") = 0;
    
	///�����ö���ת����xml��ʽд��buf��
	/**
	 ��Σ�
	 *@param lpCo:		���ö���ָ��
	 ���Σ�
	 *@param lpBuf:		��������ַ
	 *@param iBufSize:	���ݴ�С
	 *@return: �ɹ�����0; ʧ�ܷ���-1
	 */
	virtual int  FUNCTION_CALL_MODE SaveToBuf(IRCfgObj * lpCo, void ** lpBuf, long * iBufSize) = 0;

	///�ͷ���SavaToBuf���ɵ�lpBuf
	/**
	 *@param lpBuf:		��������ַ
	*/
	virtual void FUNCTION_CALL_MODE FreeMem(void* lpBuf) = 0;
	
	//20140613 majc ��ӻ�ȡ���һ��������Ϣ
	/**LoadFromFile��LoadFromBuf���������ʱ�����
	 * �̲߳���ȫ�ӿ�
	 *@return: ����д�����Ϣ�򷵻�
	 */
	virtual char * FUNCTION_CALL_MODE GetLastErr() = 0;
};

/// ���÷���ӿ�
struct ICfgSvr : public IKnown
{
	/// ��ȡ���ö���������ʵ��
	virtual ICfgObjMaker *  FUNCTION_CALL_MODE GetCfgObjMaker(void) = 0;
};

#ifdef __cplusplus
extern "C" { 
#endif

	///���÷�������ʼ������, ͨ��GetCfgSvrInstance��ȡ��������, ���ʹ�ø÷������г�ʼ��
	///Ȼ����ʹ��, �������Ĵ�����޷�����
	int  FUNCTION_CALL_MODE CfgSvrInit(void*, PFOnSetTimeOut);

	///ȡ����ӿھ��
	IKnown * FUNCTION_CALL_MODE GetCfgSvrInstance(void);

	///ȡ����ӿڵķ���������
	char* FUNCTION_CALL_MODE GetCfgSvrDependService(void*);

	///����ͳһ�Ļ������������ѯ�ӿ�
	/**���������������̬����ʱ��ͨ�����ӿڻ��Ի�ȡ������Ϣ(����xxxxInit(),getxxxxInterface()����ָ��)
	 *@param iIndex  ������������(����Ϊ0)
	 *@param lpSvrInfo    �������������Ϣ(�������)��
	 *@return ����0��ʾ�鵽��Ҫ�Ľӿڣ����򷵻ظ���
	 */
	int FUNCTION_CALL_MODE GetCfgSvrInfo(int iIndex, tagBaseServiceInfo * lpSvrInfo);

#ifdef __cplusplus
  }
#endif

#endif
