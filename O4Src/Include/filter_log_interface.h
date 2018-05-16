///��־�������������
/*******************************************************
Դ��������:filter_log_interface.h
�������Ȩ:�������ӹɷ����޹�˾
ϵͳ����:  ����ͨ����Ϣ�������ӿڱ�׼
ģ������:  ��־���˲��
����˵��:  ����־���й�����ˣ�ʵ�ּ�¼�����صĹ���
           ��صĹ������ͨ������������ӡ���ѯ��ɾ����

  
	��    ��:  xuqq
	��������:  20081009
	��    ע:  ��windows��ע�⺯�����÷�ʽ��__stdcall
	
	  �޸���Ա��
	  �޸����ڣ�
	  �޸�˵����
*********************************************************/


#ifndef FILTER_LOG
#define FILTER_LOG

#include <Include/plugin_interface.h>


///filter_log�������ķ�����
//#define SID_LOG_FILTER_SERVICE		"com.hundsun.fbase.filter_log"

///�ⲿ���ͨ��QueryInterface�õ�IF2WriteClassʱ�ķ�����
#define SID_WRITE_CLASS		   	    "com.hundsun.fbase.write_class"

////�ⲿд��ӿ�
////����ⲿ�����filter_log����һ����ˮ���ϣ�������Ҫ����filter_log�ļ�¼����ʱ
////�ⲿ��������ȵõ�filter_log��ʵ��,Ȼ��ͨ��QueryInterface����SID_WRITE_CLASS���룬����IF2WriteClass��ʵ��
////Ȼ�����IF2WriteClass����¼��־
////�����־д��ʧ�ܣ���ESBMessage�����ϼ�¼����,������false
struct IF2WriteClass : public IKnown
{
public:
	///��������һ�������ESBMessage����һ�����ص����ݰ�
	///�ȸ���ESBMessage�������ݹ�����ˣ������Ҫ��¼�����Ļ�����ôESBMessage�Լ�pBuffer���ᱻ��¼����
	///��һ�����ݰ�д�뵽��־ �ļ��У�����־ �ļ���esbcfg.xml�еĲ�������
	virtual bool Write(IESBMessage* lpMessage, void *pBuffer, int iBufferLen) = 0;
};


//�����ṩ�Ľӿ�
#ifdef __cplusplus
extern "C" { 
#endif
	
	IKnown*	FUNCTION_CALL_MODE GetFilterLogInstance();
	int		FUNCTION_CALL_MODE GetFilterLogInit(void * lpInstance ,PFOnSetTimeOut pfOnSetTimeOut = NULL);
	char*	FUNCTION_CALL_MODE GetFilterLogDependSvr(void * lpInstance);
	int		FUNCTION_CALL_MODE GetFilterLogInfo(int iIndex, tagBaseServiceInfo * ppv );
	
#ifdef __cplusplus
}
#endif

#endif
