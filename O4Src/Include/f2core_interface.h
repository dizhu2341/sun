///������������ӿڶ��� 
/*******************************************************
  Դ��������:f2core_interface.h
  �������Ȩ:�������ӹɷ����޹�˾
  ϵͳ����:  �������������ӿ�
  ģ������:  ����ģ��
  ����˵��: ����һ����ת���ƵĲ��������
            1��������������ʵ��Ҳ��װ�ɶ�̬�⣨����⣩��������ӿڱ�׼Ҳ���ز����ӿڱ�׼
            2����ת�������ԣ�Ӧ�������� --����ע��--> ������� --����ע��--> ���
  ��    ��:  �з�����
  ��������:  20071229
  ��    ע:  ��windows��ע�⺯�����÷�ʽ��__stdcall
  
  �޸����ڣ�20080310
  �޸���Ա��zhangly
  �޸�˵��������20080305����������һЩͬ���������ӿ��ϣ����Ӵ���������һ������ʱ�Ļص�����, PFOnSetTimeOut

  �޸����ڣ�20080111
  �޸���Ա��zhangly
  �޸�˵��������20080110��������IF2Core�ӿ�
*********************************************************/

#ifndef F2CoreInterface_h
#define F2CoreInterface_h

#include <Include/plugin_interface.h>


///������2.0��������ӿڶ��壬��������Ҳ�Բ����ʽ��װ����ͬʱʵ��IIoC�ӿڣ�IManger �ӿ�
/** 
 * �����Ĺ���:<br>
 * 1)�������ö�̬���ز���⣬��Ϊÿ�����������Ҫ�����������ά��һ���Ѽ��ز�����б�����֧�ַ������ز����<br>
 * 2)ΪӦ���ṩһ��ȫ����������������ά��һ��ȫ�������б�<br>
 * 3)����ά���Ĳ���ַ�����������ϵͳ�¼���<br>
 * 4)�����ڲ����fsc_msg_pipe�����ã���װ��Ϣ��ˮ��;<br>
 *
 * ������ʹ������:<br>
 * 1)Ӧ��������ͨ������̬������������GetIF2CoreInstance()����������ӿ�ʵ��IF2Core��<br>
 *
 *  ͨ����������QueryInterface()�������Ի������������ע��ӿ�IIoC���������������ö���������
 *
 *  Ӧ��������ͨ�������ӿ��е�Load()����,�������÷�����̬���ظ�����⣬��ȡ����еĸ������ʵ���ӿڣ������������ʵ��������Ӧ�����ö��������ӿڣ�
 *
 *  ������ʵ�������Ҫ�õ����������԰������ӿ�IF2Core��Ϊ���ѵ������ ��Ϊ�˱��ַ�ת�������ԣ�����ʵ����Ӧ��ͨ��IF2Core��QueryInterface����ñ��������ķ���
 *
 *  ͨ�������ӿ� SetGlbData() ,GetGlbData()����,���Դ�ȡӦ�ü�ȫ�����ݣ�
 *
 *  ������ø�ʽ�������Ÿ�ʽ��Ӧ�ó����������ȡ������IRCfgObj�ӿڶ���: plugins��ǩ��Ϊÿ���������һ�� plugin �ӱ�ǩ��
 *
 * 2) Ӧ��������ͨ�������ӿ��ṩProcMngRequest()��ProcMngAnswer()��ProcSysEvent()�������������ڵ����в���ַ�����������ϵͳ�¼�������������ֹͣ��
 *
 * 3) Ӧ��������ͨ�������ӿڵ�QueryInterface()��������������Ĺ������ӿ�IManager��ͨ������ӿڲ�ѯ�����ڲ�״̬
 *
 */
struct IF2Core:IKnown
{
	///����ָ������Ĳ��������һ��������ϵ�Ը�������г�ʼ��
    /**���ò��ʱͨ��ָ�����ؼ��𣬿���ʹ��������ּ���˳��
     *@param int iLoadLevel    ������ؼ���ÿ�����õĲ������ָ�����ؼ���(ȱʡΪ1���Ϸ�ȡֵ0��1��2)��������ʹ���߿��Էּ��������ز��
     *@param PFOnSetTimeOut pfOnSetTimeOut   ���ó�ʱ�Ļص�����,ȱʡΪNULL,����֪ͨ�����߱��β������ƻ���Ҫ����ʱ�������ɶԸ��¼��Ĵ������ָ��ʱ����ٴλص��ú���
     *@return int �ɹ�����I_OK��������I_NONE
     */
    virtual int  FUNCTION_CALL_MODE Load(int iLoadLevel, 
		                                 PFOnSetTimeOut pfOnSetTimeOut = NULL ) = 0;

	///����ȫ������ID������ָ��ȫ������ָ��
    /**
     *@param const char  * sGlbDataID  Ӧ�ü�ȫ������ID����Ӧ�ÿ��������Ѷ���
     *@return void * �ɹ�������Ӧ��������ָ�룬������NULL
     */
    virtual void *  FUNCTION_CALL_MODE GetGlbData(const char * sGlbDataID)=0;

	///����ȫ������ID������ָ��ȫ������ָ��
    /**
     *@param char * sGlbDataID  Ӧ�ü�ȫ������ID����Ӧ�ÿ��������Ѷ���
     *@param const void * pData      ����ָ��(����ΪNULL)
     *@return int �ɹ�����I_OK��������I_NONE
     */
    virtual int  FUNCTION_CALL_MODE SetGlbData(const char * sGlbDataID,void * pData)=0;


	///ͨ�������ṩ�������������������ָ��������ݹ�������
	/**ָ������Ĺ������ӿ��е�ProcMngRequest()�����ᱻ���õ���
	 *@param  HS_SID iid  ���ID
	 *@param IF2UnPacker * lpInput  ���������������ӿ�
     *@param IF2Packer * lpOutput   ���Ӧ���������ӿ�[�������]
	 *@return RET_PM_OK �ɹ���RET_PM_NONE �����ݣ�RET_PM_ERR ϵͳ����������������ʾҵ���Դ���
	 */
	virtual  int  FUNCTION_CALL_MODE ProcMngRequest(HS_SID iid,IF2UnPacker * lpInput,IF2Packer * lpOutput)=0;

	///ͨ�������ṩ�������������������ָ��������ݹ���Ӧ��
    /**ָ������Ĺ������ӿ��е�ProcMngAnswer()�����ᱻ���õ���
	 *@param  HS_SID iid  ���ID
 	 *@param IF2UnPacker * lpInput  ����Ӧ���������ӿ�
	 *@return int �ɹ�����I_OK��������I_NONE
     */
	virtual  int  FUNCTION_CALL_MODE ProcMngAnswer(HS_SID iid,IF2UnPacker * lpInput)=0;

	///ͨ�������ṩ�������������ָ�����˳��㲥ϵͳ�¼�
    /**���в���Ĺ������ӿ��е�ProcSysEvent()�������ᱻ���õ���
	 *@param char * lpIDs ��˳��Ҫ��Ĳ���б��б����һ���Ϊ���ַ���,���磺 "xxxxx\0yyyyy\0\0"����ʾ˳��Ϊxxxxx,yyyyy��������
                                ������NULL����ʾ˳���޹�;
	 *@param unsigned long dwMessageID ϵͳ�¼����(�μ�MSG_XXXX����)
	 *@param unsigned long dwWParam  ��Ϣ����1(�ɲ�ͬ��dwMessageID�����嶨��)
     *@param unsigned long dwLParam  ��Ϣ����2(�ɲ�ͬ��dwMessageID�����嶨��)
     *@param PFOnSetTimeOut pfOnSetTimeOut   ���ó�ʱ�Ļص�����,ȱʡΪNULL,����֪ͨ�����߱��β������ƻ���Ҫ����ʱ�������ɶԸ��¼��Ĵ������ָ��ʱ����ٴλص��ú���
	 *@return int �ɹ�����I_OK��������I_NONE
     */
	virtual  int  FUNCTION_CALL_MODE ProcSysEvent( char * lpIDs,unsigned long dwMessageID,unsigned long dwWParam,unsigned long dwLParam,
		                                           PFOnSetTimeOut pfOnSetTimeOut = NULL ) = 0;

};

//������ӿ�---------------------------
#ifdef __cplusplus
extern "C" { 
#endif

///��������������
IF2Core * FUNCTION_CALL_MODE GetIF2CoreInstance();

#ifdef __cplusplus
}
#endif

#endif
