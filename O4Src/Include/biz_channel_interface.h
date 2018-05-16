#ifndef __CHANNEL_BIZ_INTERFACE_H__
#define __CHANNEL_BIZ_INTERFACE_H__


#include <Include/glbdef.h>
#include <Include/esb_message_interface.h>

struct IBizPlugin:public IKnown
{
public:
	//�յ���Ϣʱ��ҵ�����ṩ����Ϣ����ӿڣ��ṩ��ͨ�ò���첽�ص�
	/*
		*@param IESBMessage* lpMsg:	���յ�����Ϣ
		ע�⣺�ص��������������IESBMessage�ǵ������Լ�ά��������Ҫʹ�õ�ʱ����ͷ�
			  Ҳ����˵��lpMsg��Ҫ�ص����������Լ��ͷ�
	*/
	virtual int OnMsgRecv(IESBMessage* lpMsg) = 0;

	/// ��÷���Ĳ����
	virtual const char*  GetServiceID()=0;

};


#endif
