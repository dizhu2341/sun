/*******************************************************
  Դ��������:mcmsg_interface.h
  �������Ȩ:�������ӹɷ����޹�˾
  ϵͳ����:  ��Ϣ����2.0
  ģ������:  ��Ϣ��װģ��ӿ�
 ��    ��:  maoyj
  ��������:  20120618
  ��    ע:  
  //	maoyinjie	2012-11-29	��ȡ�����ߵ�����,������

*********************************************************/


#ifndef _HUNDSUN_MCMSG_INTERFACE_H_
#define _HUNDSUN_MCMSG_INTERFACE_H_

#include <Include/esb_message_interface.h>
#include <Include/service_interface.h>
class IMCMemCachedMsg
{
public:
	virtual int FUNCTION_CALL_MODE SetEsbMsg(IESBMessage* lpEsbMsg, bool bIsINMemCached=false)=0;
	virtual int FUNCTION_CALL_MODE Copy2EsbMsg(IESBMessage* lpEsbMsg)=0;

	virtual uint16 FUNCTION_CALL_MODE GetTopicNo()=0;
	virtual uint16 FUNCTION_CALL_MODE GetPublisherNo()=0;
	virtual uint32 FUNCTION_CALL_MODE GetGlbSeq()=0;
	virtual uint32 FUNCTION_CALL_MODE GetTimeStamp()=0;
	virtual uint32 FUNCTION_CALL_MODE GetInternalSeq()=0;
	virtual int	   FUNCTION_CALL_MODE GetMemSize()=0;
	virtual void*  FUNCTION_CALL_MODE GetBody(int &iBodyLen, int iLoops=0)=0;

	virtual int FUNCTION_CALL_MODE AddRef()=0;
	virtual int FUNCTION_CALL_MODE Release()=0;
	//	maoyinjie	2012-11-29	��ȡ�����ߵ�����,������
	//	�����Ϣ�����ߵ�MCӦ����,�����Ϣ��û�и�����,�򷵻�NULL
	virtual char* FUNCTION_CALL_MODE GetMCAppName()=0;
};

class IMCMessagePtr
{
public:
	virtual int FUNCTION_CALL_MODE SetMsg(IMCMemCachedMsg* lpMCMsg)=0;
	virtual int FUNCTION_CALL_MODE Release()=0;	//	�ͷ���Ϣ,�������Ϣû�����ü����ĸ���ֻ��һ����ʹ��,ʹ����ϼ����
	virtual ITagItem* FUNCTION_CALL_MODE GetRouteItemForChange()=0;		//	���·����Ϣ,��׼������
	virtual ITagItem* FUNCTION_CALL_MODE GetSessionItemForChange()=0;	//	��ûỰ��Ϣ,��׼������
	virtual int FUNCTION_CALL_MODE SetSubHead(void* lpHead, int iLen)=0;	//	ֱ�Ӹ��Ķ���ͷ����Ϣ
	virtual int FUNCTION_CALL_MODE Copy2EsbMsg(IESBMessage* lpEsbMsg)=0;
	virtual uint16 FUNCTION_CALL_MODE GetTopicNo()=0;
	virtual uint16 FUNCTION_CALL_MODE GetPublisherNo()=0;
	virtual uint32 FUNCTION_CALL_MODE GetGlbSeq()=0;
	virtual void FUNCTION_CALL_MODE SetFlagTag(uint32 dwTag)=0;
	virtual uint32 FUNCTION_CALL_MODE GetFlagTag(void)=0;
	virtual int FUNCTION_CALL_MODE GetMemSize()=0;
};

#endif
