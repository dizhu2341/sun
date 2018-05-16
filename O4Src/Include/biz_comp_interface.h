/*******************************************************
  Դ��������:biz_comp_interface.h
  �������Ȩ:�������ӹɷ����޹�˾
  ϵͳ����:  ���ڻ�����V2.0
  ģ������:  ASģ��
  ����˵��:  ҵ���߼������׼ͷ�ļ�
             1�������˹��������̬��/������������ԭ�͡�
             2�������µ�AS�������ʱ��Ӧ�������ļ�����ʵ�ִ˴���������������
             3����ͷ�ļ���������AS�������ʹ��
             
  ����ĵ�:  ��Ҫ��ƽӿڲ���
  ��    ��:  zhangly
  ��������:  20080728
  ��    ע:  linux\unixƽ̨���� OS_UNIX
  �޸���Ա��
  �޸����ڣ�
  �޸�˵����

  20130705 xuxp ���Ӷ��ķ����ӿ�
*********************************************************/

#ifndef AS_BIZ_COMP_H
#define AS_BIZ_COMP_H

#ifdef __win32
#ifndef FUNCTION_CALL_MODE
	#define FUNCTION_CALL_MODE  __stdcall 
#endif
#endif

#include <Include/pack_interface.h>
#include <Include/config_interface.h>
#include <Include/esb_message_factory_interface.h>
#include <Include/hsdb_interface.h>
#include <Include/mdb_interface.h>
//20130705 xuxp ���Ӷ��ķ����ӿ�ͷ�ļ�
#include <Include/mc_bizcomponent_interface.h>

#define SID_TM "com.hundsun.fbase.tm"
#define SID_FUND_CTX "com.hundsun.fbase.fund"
#define SID_SCRIPT_CTX "com.hundsun.fbase.script"

struct IScriptContext : public IKnown
{
	///���ָ�������Ľ������������ӿڣ�
	/**
	 *@param int iIndex ����ֵ����ʾҪȡ�ű�������������ΪiIndex���Ǵ�������õķ��ؽ����
	 *@return IF2UnPacker * �����ָ�룬ʹ�ü��ɣ�����Ҫrelease���Ҳ���ʱ����NULL��
	 */
	virtual IF2UnPacker * FUNCTION_CALL_MODE GetUnPackerByIndex(int iIndex) = 0;

	///<�ű�ʹ��>����ýű������������
	/**
	 *@return char * �ű�����ĵ������У���ŵ��ǵ������˳����±ꡣ
	 */
	virtual char * FUNCTION_CALL_MODE GetScriptTransSeq() = 0;
};

//���������ʽӿڣ��ɴ����������ĵ�Queryinterfaceȡ��
struct IFundContext : public IKnown
{
	///���ݷ�����ȡ�ù��ܺŵĽӿ�
	/**
	 *@param const char * lpServiceName ������
	 *@return int ��������Ӧ�Ĺ��ܺš��Ҳ���ʱ����-1��
	 */
	virtual int FUNCTION_CALL_MODE GetFuncNo(const char * lpServiceName) = 0;

	///���ݹ��ܺ�ȡ�÷������Ľӿ�
	/**
	 *@param int iFuncNo ���ܺ�
	 *@return const char * ���ܺŶ�Ӧ�ķ��������Ҳ���ʱ����NULL��
	 */
	virtual const char * FUNCTION_CALL_MODE GetSvrName(int iFuncNo) = 0;

	///��������ȡ�ù��ܺŵĽӿ�
	/**
	 *@param int iIndex ����ֵ
	 *@return int ����ֵ��Ӧ�Ĺ��ܺš��Ҳ���ʱ����-1��
	 */
	virtual int FUNCTION_CALL_MODE GetFuncNoByIndex(int iIndex) = 0;

	///��������ȡ�÷������Ľӿ�
	/**
	 *@param int iIndex ����ֵ
	 *@return const char * ����ֵ��Ӧ�ķ��������Ҳ���ʱ����NULL��
	 */
	virtual const char * FUNCTION_CALL_MODE GetSvrNameByIndex(int iIndex) = 0; 

	///ȡ�������ļ���������-���ܺŶ�Ӧ��ϵ����¼����
	/**
	 *@return int ��¼����
	 */
	virtual int FUNCTION_CALL_MODE GetRecordNum() = 0;

	///ȡ��ָ������������������������
	/**
	 *@param const char * lpServiceName ������
	 *@return int ָ������������������������
	 */
	virtual int FUNCTION_CALL_MODE GetProcessNum(const char * lpServiceName) = 0;

	///�ȴ���Ϣ
	/**
	 *@param IESBMessage ** lpMsg �ȴ���Ϣ
	 *@param int iTimeOut �ȴ�ʱ��
	 *@return int ���سɹ����0�ɹ�������ʧ��
	 */
	virtual int FUNCTION_CALL_MODE waitForMsg(IESBMessage ** lpMsg, int iTimeOut) = 0;

	///������Ϣ
	/**
	 *@param int iCd �Ự���
	 *@param IESBMessage * lpMsg �����͵���Ϣ
	 *@return int ָ������������������������
	 */
	virtual int FUNCTION_CALL_MODE SendMsg(int iCd, IESBMessage * lpMsg) = 0;
};

///����������ӿڣ�ͨ�������������ĵ�QueryInterface���Ի��
struct IAS2TM : public IKnown
{
    ///��ʼ��������һ��ǰ��Ψһ���к�(���:�ڵ���#���#ʱ���#˳���)���úſ�����ϵͳ������֤��������󳤶�32+1+4+1+12+1+12
	virtual char * FUNCTION_CALL_MODE BeginTrans() =0;	

    ///�쳣���׼�¼(���ܺš�ǰ�����кš�ԭʼ������Ϣ)
    virtual void FUNCTION_CALL_MODE Assert() =0;

	///��ǰ�������ύ�Ľ��׸���
    virtual int FUNCTION_CALL_MODE GetCommitNum() =0;

    ///�������
    virtual void FUNCTION_CALL_MODE EndTrans() =0;	
};

///�����������ģ���ҵ���߼��������ʹ��
struct IAS2Context : public IKnown
{
	///ȡԭ������Ϣ
	virtual IESBMessage * FUNCTION_CALL_MODE GetOrgRequest() = 0;

	///ȡESB��Ϣ��������ӿ�
	virtual IESBMessageFactory * FUNCTION_CALL_MODE GetESBMsgFactory() = 0;

	///ȡҵ����������ӿ�
	virtual IF2PackSvr * FUNCTION_CALL_MODE GetF2PackSvr() = 0;
	
	///ȡ���ݿ�����
	/**������������Դ��ΪNULL����ȡAS���õ�ȱʡ����Դ��
	 *@param const char * szDataSourceName ����Դ��
	 *@return char *  ȱʡ����Դ�� 
	 */
	virtual IConnection *  FUNCTION_CALL_MODE GetDBConnection(const char * szDataSourceName = NULL ) = 0; 
	
	///ȡ��ǰ�����̵߳��ڴ����ݿ�����
	/**
	 *@return int  �������ӽӿ� 
	 */
	virtual int  FUNCTION_CALL_MODE GetMDBSession() = 0; 

	///ͬ�������ӷ���
	/**
	 *@param IESBMessage * lpReqMessage �ӷ��������Ϣ[in]
	 *@param IESBMessage ** lppAnsMessage �ӷ���Ӧ����Ϣ[out]
	 *@param int iTimeOut  ��ʱʱ��(ms)[in]
	 *@return ����0��ʾ�ɹ�����Ҫ�������ͷŻ�õ�Ӧ����Ϣ������-1ʱ������ʧ��(������Ϣ�ѱ��ͷ�)������-2,��ʾ�õ��ó�ʱ�������Է��������Ҫ�������ط���
	 */
	virtual int FUNCTION_CALL_MODE CallSubService(IESBMessage * lpReqMessage, IESBMessage ** lppAnsMessage, int iTimeOut) =0;	
	
	///�첽������Ϣ
	/**
	 *@param IESBMessage * lpMessage Ҫ���͵���Ϣ[in]
	 *@return ����0��ʾ�ɹ�����0��ʾʧ�ܣ�ʧ��ʱ��Ҫ�ͷŸ���Ϣ��
	 */
	virtual int FUNCTION_CALL_MODE PostMsg(IESBMessage * lpMessage ) = 0;	
	
	///ȡȫ��������Ϣ
	virtual IRCfgObj * FUNCTION_CALL_MODE GetPubInfo() = 0;

	///�������ĵĴ�������л��һ�������
	/**
	 *@return IF2Packer * �����ָ�롣ʹ���߲���Ҫrelease
	 */
	virtual IF2Packer * FUNCTION_CALL_MODE GetPackerFromPool() = 0;

	///�������ĵĽ�������л��һ�������
	/**
	 *@return IF2UnPacker * �����ָ�룬ʹ���߲���Ҫrelease
	 */
	virtual IF2UnPacker * FUNCTION_CALL_MODE GetUnPackerFromPool() = 0;

	//2030705 xuxp �������Ӷ��ķ����ӿ�
	//////////////////////////////////////////////////////////////////////////
	/** ����һ���������ӿ�ָ��
	* @return ����NULL��ʾʧ�ܡ�
	**/
	virtual IPluginFilterInterface* FUNCTION_CALL_MODE NewFilter()=0;

	/** ����һ���������Խӿ�ָ��
	* @return ����NULL��ʾʧ�ܡ�
	**/
	virtual IPluginSubscribeParamInterface* FUNCTION_CALL_MODE NewSubscribeParam()=0;

	/**��������
	* @param lpSubscribeParam ���涨��Ķ��Ĳ����ṹ
	* @param uiTimeout ��ʱʱ��
	* @param lpBizPack ҵ��У����Ҫ���ӵ�ҵ���ֶ��Լ�ֵ��û�о͸��ݹ���������Ϊҵ��У���ֶ�
	* @return ����0��ʾ���ĳɹ�������2���ظ����ģ����Ե��ɶ��ĳɹ�������������ֵ�����ݴ���Ż�ȡ������Ϣ��
	**/
	virtual int FUNCTION_CALL_MODE SubscribeTopic(IPluginSubscribeParamInterface* lpSubscribeParamInter ,unsigned int uiTimeout,IF2Packer* lpBizPack=NULL) = 0;

	/**ȡ����������
	* @param topicName �������֣���֪�����־ʹ�NULL
	* @param lpFilter ��Ӧ�Ĺ�������
	* @param uiTimeout ��ʱʱ��
	* @return ����0��ʾȡ�����ĳɹ�����������ֵ�����ݴ���Ż�ȡ������Ϣ��
	**/
	virtual int FUNCTION_CALL_MODE CancelSubscribeTopic(int index) = 0;

	/**ҵ������ʽ�����ݷ����ӿ�
	* @param topicName �������֣���֪�����־ʹ�NULL
	* @param topicNo �����ţ���֪����žʹ�0
	* @param lpPacker ���������
	* @param iTimeOut ��ʱʱ��
	* @param bCompatible ����1.0�ı�־��ֻ�м��ݲ��������ʱ�����true����������false��
	* @return ����0��ʾ�ɹ�����������ֵ�����ݴ���Ż�ȡ������Ϣ��
	**/
	virtual int FUNCTION_CALL_MODE PubMsgByPacker(char* topicName,IF2UnPacker* lpUnPacker,int iTimeOut=-1,bool bCompatible=false) = 0;
	
	/**��ҵ������ʽ�����ݷ����ӿڣ�һ������Ƹ�ʽ���ķ���
	* @param topicName �������֣���֪�����־ʹ�NULL
	* @param topicNo �����ţ���֪����žʹ�0
	* @param lpFilter ������������Ҫ�ϲ��Լ�ָ��������Ĭ��û�й�������
	* @param lpData ���������
	* @param nLength ���ݳ���
	* @param iTimeOut ��ʱʱ��
	* @param bCompatible ����1.0�ı�־��ֻ�м��ݲ��������ʱ�����true����������false��
	* @return ����0��ʾ�ɹ�����������ֵ�����ݴ���Ż�ȡ������Ϣ��
	**/
	virtual int FUNCTION_CALL_MODE PubMsg(char* topicName, IPluginFilterInterface* lpFilterInter, const void *lpData, int nLength,int iTimeOut=-1,bool bCompatible=false) = 0;
	
	//20130923 xuxp ���ȡ�����Ľӿ�
		/**
    * ȡ����������
    * @param topicName ��������
    * @param lpFilterInterface ��Ӧ�Ĺ�������
    * @return ����0��ʾȡ�����ĳɹ�����������ֵ�����ݴ���Ż�ȡ������Ϣ.
    */
	virtual int FUNCTION_CALL_MODE CancelSubscribeTopicEx(char* topicName,IPluginFilterInterface* lpFilterInterface) = 0;

	//201309123 xuxp ��ӷ��ش�����
	/** ���ݴ���Ż�ȡ������Ϣ
	* @param nErrorNo �����
	* @return ���ض�Ӧ������Ϣ
	**/
	virtual char* FUNCTION_CALL_MODE GetErrorMsg(int nErrorNo) = 0;
	
	//20140605 majc ���
	/** ����Ƕ������͵���Ϣ���Ի�ȡ����͹�������
	  * @return ���ض�����Ϣ�����Ϣ��
	**/
	virtual SUB_RECVDATA_FOR_PROC* FUNCTION_CALL_MODE GetRecvData() = 0;
	//////////////////////////////////////////////////////////////////////////
	
};


///ҵ���߼�������ָ�����ͣ�����1��ʾ����Ҫ�������Ӧ���ӷ���ԭ���ϲ�����1.
typedef int ( FUNCTION_CALL_MODE *TBizFunctionEntry ) (IAS2Context * context_handle, IF2UnPacker * in,IF2Packer * out);
///�ű�����ִ��ʱ���ӷ�����ú���ָ�롣
typedef int ( FUNCTION_CALL_MODE *TScriptSubCall ) (IAS2Context * lpContext,IF2UnPacker * lpInUnPacker, IF2Packer * lpOutPacker,unsigned int iTimeOut,unsigned int iFuncNo,unsigned int iBranchNo,unsigned int iSystemNo,unsigned int iSubSystemNo);

///ҵ���߼������������Ϣ
typedef struct tagBizFunctionInfo
{
	///���ܺ�
	unsigned long dwFunctionNo;
	///�������汾��Ϣyyyymmdd
	int iVersion;
	///��������
    TBizFunctionEntry ReqProc;
	
	///�������������������ӷ�����õ�Ӧ���������
	/** һ�������Ϊ��,ʹ��subcall�ӿ�ʱ������������ͬ */
    TBizFunctionEntry AnsProc;
	///����������Ϣ
	const char * Caption;
}BIZ_FUNC_INFO,* LPBIZ_FUNC_INFO;

///��Ӧ��ŵĹ��ܴ���
#define ASFC_EXISTS  1

///��Ӧ��ŵĹ��ܲ�����
#define ASFC_NONE    0
//����Ҫ�������Ӧ��
#define ASFC_NO_ANSWER 1

//�ӷ�����÷���ֵ����
//�ɹ�
#define SUB_CALL_OK  0
//����
#define SUB_CALL_ERR -1
//��ʱ
#define SUB_CALL_TIMEOUT -2


///ÿһ����ҵ���߼�������������ص�ҵ������⣬�����������º���:

#ifdef __cplusplus
extern "C" { 
#endif

///���������¼���Ӧ����
/**
 *@param char * arg  ������в�����ÿ����̬���������һ�����в���������ʽ��������н���
 */
void  FUNCTION_CALL_MODE OnLoad(char * arg);

///�����ж���¼���Ӧ����
void  FUNCTION_CALL_MODE OnUnload(); 
 
///�����������¼���Ӧ����(AS��ʼ�������)
void  FUNCTION_CALL_MODE OnStart();

///������ֹͣ��������¼���Ӧ����
void  FUNCTION_CALL_MODE OnStop( ); 

///ȡ�������ҵ������Ϣ��ҵ���������ӿڲ�ѯ������
/**�����ʵ�ִ˺�����AS�ڼ��������֮��ͨ���˺��������0��ʼ����ѯ��ǰ�������֧�ֵĹ��ܺ���,ֱ���˺�������ASFC_NONE��
 *@param int Index           Ҫ��ѯ�Ĺ��ܺ�����ţ���0��ʼ��
 *@param LPFUNC_INFO  ppv    ���ص�ǰ���ܵ������Ϣ[out]
 *@return int ָ����ŵĹ��ܺ������ڣ��򷵻� ASFC_EXISTS �����򷵻� ASFC_NONE
 */
int  FUNCTION_CALL_MODE GetBizFunctionsInfo(int Index, LPBIZ_FUNC_INFO  ppv );

///ȡ�����汾
char *  FUNCTION_CALL_MODE GetLibVersion( );

///���ò����ѯ�ӿڣ���OnStart()����֮ǰ������
void  FUNCTION_CALL_MODE SetIKnown( IKnown * lp ); 

#ifdef __cplusplus
  }
#endif

#endif
