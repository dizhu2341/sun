/*
	�޸ļ�¼
		maoyinjie 2011/04/19	���ӱ���TAG�Ľӿ�
		maoyinjie 2012/08/14	����ֱ�Ӵ���ҵ����Ľӿ�
*/

#ifndef ESB_MESSAGE_INTERFACE_H
#define ESB_MESSAGE_INTERFACE_H

#if defined(_WIN32)&& _MSC_VER < 1300
#pragma warning(disable: 4786)				//����ڱ�������STLͷ�ļ�ǰ
#pragma warning(disable: 4710)				//����ڱ�������STLͷ�ļ�ǰ
#endif


#include <Include/plugin_interface.h>




//	���ȼ������Լ����ֽ������ȼ�(Ӧ�ÿ��Ը���ʵ����Ҫ���µ���,���Բ���������Ӧ��ʹ��>=14�����ȼ�)
#define MAX_PRIORITYQ			16	//	�ܹ�֧��16�����ȼ�
#define PRIORITY_REAL			15	//	������ȼ�,����Э���ڲ���ʹ��
#define PRIORITY_OSPF			14	//	OSPFЭ��ʹ�õ����ȼ�
#define PRIORITY_HIGHER			13	//	�����ȼ�,���ý���������ָ��
#define PRIORITY_HIGH			10	//	�ϸ����ȼ�,ʵʱ������ָ������,��������Ӧ��Ҳ���ø����ȼ�
#define PRIORITY_NORMAL			8	//	�����ȼ�,ʵʱ�Ĳ�ѯָ������
#define PRIORITY_LOW			6	//	�ϵ����ȼ�,��ʷ���ѯ����
#define PRIORITY_LOWER			3	//	�����ȼ�,������������(������Ӱ�����ݵĴ���)
#define PRIORITY_LAZY			0	//	�����ķ���(������Ӧ��?)

/// ��HSESB�䴫�ݵ���Ϣ,��Ϣ�ڸ�������䴫��,��Ϊ����ESB�ڲ�����Ϣ��ʽ,����ͨ������Ϣ������ת���ɸ���Ϣ��ʽ
///	����������䴫��
///	���ڶ��̳߳�ͻ,��������̲߳�������

/*
	��ȡ��Ϣ�е���ֵʱ,�����TAG���������ڸ���Ϣ��,�򷵻�ȱʡֵ ,ȱʡֵ����:
		����int��,		����0
		����string��	����""
		����rawdata��	����"",���ҳ���Ϊ0
IESBMessage:
	ITagItems
		ITagItem
		...
		ITagItem
	...
	ITagItems
		ITagItem
		...
		ITagItem
*/


/// rawdata�����������������
struct ITagItem : IKnown
{
	/// ��ȡֵ

	/**
	* ����ִ���ʽ��ֵ:
	*@param int	iIndex:	��Ҫ��������ڵڼ���Ԫ�ص�ֵ
	*@return	ָ����ֵ��ָ��
	**/
	virtual const char* FUNCTION_CALL_MODE GetString(int iIndex=0) =0;			//	""
	/**
	* ���������ʽ��ֵ
	*@param int	iIndex:	��Ҫ��������ڵڼ���Ԫ�ص�ֵ
	*@return	��ֵ
	**/
	virtual int			FUNCTION_CALL_MODE GetInt(int iIndex=0)=0;				//	0
	//	���rawdata��ֵ
	/**
	* ���rawdata��ֵ
	*@param int* ilpRawDataLen:	����rawdata�ĳ���
	*@param int iIndex:			��ȡ�����ڵڼ���
	*@return	ָ����ֵ��ָ��
	**/
	virtual const void* FUNCTION_CALL_MODE GetRawData(int* ilpRawDataLen=NULL, int iIndex=0)=0;
	/**
	* ���rawdata�ĳ���
	*@param int iIndex:			��ȡ�����ڵڼ���
	*@return	����
	**/
	virtual int		FUNCTION_CALL_MODE 	GetRawDataLen(int iIndex=0)=0;		//	0
	

	///	����ֵ

	/**
	* �����ִ���ʽ��ֵ
	*@param int	iIndex:	��Ҫ���������ڵڼ���Ԫ�ص�ֵ
	*@param const char* lpValue:	��ֵ
	*@return	��
	**/
	virtual void FUNCTION_CALL_MODE SetString(const char* lpValue, int iIndex=0)=0;
	/**
	* ����������ʽ��ֵ
	*@param int	iIndex:	��Ҫ���������ڵڼ���Ԫ�ص�ֵ
	*@param int iValue:	��ֵ
	*@return	��
	**/
	virtual void FUNCTION_CALL_MODE SetInt(int iValue, int iIndex=0)=0;
	/**
	* ����rawdata��ʽ��ֵ
	*@param const void* lpRawData:	��ֵ
	*@param int iRawDataLen:	��ֵ����
	*@return	��
	**/
	virtual void FUNCTION_CALL_MODE SetRawData(const void* lpRawData, int iRawDataLen)=0;

	/// ��������ڳ�Ա���� 
	virtual int FUNCTION_CALL_MODE GetCount()=0;

	/// �Ƿ���ڵ�iIndex����Ա
	virtual bool FUNCTION_CALL_MODE IsExist(int iIndex=0)=0;

	/**
	* �����ִ���ʽ��ֵ,���ڵ�ǰ�����β��,����������
	*@param const char* lpValue:	��ֵ
	*@return	��
	**/
	virtual void FUNCTION_CALL_MODE SetStringAtTail(const char* lpValue)=0;
};


/// �̲߳���ȫ
struct IESBMessage : IKnown
{
	/**
	*	���ĳ����ֵ�Ķ���ָ��
	*@param int	iFieldTag:��Ҫ�����ֵ��TAG
	*@return	ָ����ֵ�����ָ��(�����Ϣ�ڲ����ڸ�TAG,��᷵��һ��ȱʡ�Ķ���,ȷ�����طǿ�)
	**/
	virtual ITagItem*	FUNCTION_CALL_MODE GetItem(int iFieldTag)=0;
	///	���ݱ���������Ϣ�����ڵĸ�����
	/**
	* ���ݱ���������Ϣ�����ڵĸ�����
	*@param const void* lpMessageBuffer:	����
	*@param int iMsgLen:					���ĳ���
	*@return
		SUCC�ɹ�
		����ʧ��
	**/
	virtual int			FUNCTION_CALL_MODE SetBuffer(const void* lpMessageBuffer, int iMsgLen) = 0;
	/**
	* ���������ڵĸ�����ֵ�������շ�װ�ɱ��ķ���,(����װЭ���ڲ�����ֵ)
	*@param int* ilpMsgLen:	��װ���ĵĳ���
	*@return ����
	**/
	virtual void*		FUNCTION_CALL_MODE GetBuffer(int* ilpMsgLen) = 0;
	/**
	* ���������ڵĸ�����ֵ�������շ�װ�ɱ��ķ���(��װ������ֵ)
	*@param int* ilpMsgLen:	��װ���ĵĳ���
	*@return ����
	**/
	virtual void*		FUNCTION_CALL_MODE GetInternalBuffer(int* ilpMsgLen) = 0;
	/// �����Ϣ���Ƿ����iTag��
	/**
		����0:������
			��0����
	**/
	virtual int			FUNCTION_CALL_MODE IsExist(int iTag) = 0;




	///	������Ϣ��һЩ��������
	/**
	* ����������Ϣ,
	* �ڲ�����:
	*	һ:�����Ϣ��������ֵ
	*	��:����Ϣ��������ΪiPacketType,���ܺ�����ΪiFuncID
	*	��:���������,��ȱʡ������Ҫ�Է�Ӧ��(���Ӧ���߲���Ҫ�Է�����Ӧ,�����Ӧ����ʽ�ĵ���ExpectResponse,
	*		�����������óɲ���Ҫ�Է���Ӧ)
	*		�����Ӧ��,��ȱʡ���óɲ���Ҫ�Է���Ӧ(���Ӧ����ʵ����Ҫ�Է�����Ӧ,�����Ӧ����ʽ�ĵ���ExpectResponse,
	*		�����������ó���Ҫ�Է���Ӧ)
	*
	*	����Ҫ�Է���Ӧ�ı��Ľ�����Ҫ�Է���Ӧ�ı���ҪС.

	*@param int iPacketType:	��������
	*@param int iFuncID:		���ܺ�
	*@return
		SUCC�ɹ�
		����ʧ��
	**/
	virtual int			FUNCTION_CALL_MODE Prepare(int iPacketType, int iFuncID) = 0;
	/**
	* ����Ϣ��������ʽת����Ӧ����ʽ
	*	�ú���ִ�����²���:
	*		һ:����Ϣ���ʹ�����ת����Ӧ��
	*		��:����Ϣ��ȡ����������Ϣ,�������ó�·����Ϣ.
	*		��:������Ϣ���óɲ���Ҫ�Է�����Ӧ(���Ӧ������Ҫ��֪�Է�����Ӧ,����Ҫ��ʽ�ĵ���ExpectResponse,�����������ó���Ҫ�Է���Ӧ)
	*		��:��   !!!!������������ֵ!!!!!!  ����Ϊ��
	*
	*	���������ƻ�ԭʼ��Ϣ,���Ӧ������Ҫ����ԭʼ��Ϣ�Ļ�,�����ñ���������

	*@return
			SUCC�ɹ�
			����ʧ��,ʧ�ܵ�ԭ�������¼���:
				һ:����Ϣ����������
				��:����Ϣ�в���������������Ϣ

		˵��:
			
	**/
	virtual int			FUNCTION_CALL_MODE ChangeReq2AnsMessage() = 0;
	/// �ڴ�����һ��������Ϣ֮��,�ڷ���֮ǰ,Ӧ�ÿ��������Լ��Ƿ���Ҫ�Է�����Ӧ
	/**
		ͨ�����ñ���������,Ӧ����ʾ��֪ͨrouter,��Ը���Ϣ,�Լ��Ƿ������ӶԷ��յ���Ӧ��Ϣ
		һ����˵,������������Ҫ�Է���Ӧ
		��Ӧ����һ�㲻ϣ���Է�����Ӧ
	**/
	virtual int			FUNCTION_CALL_MODE ExpectResponse(bool bNeedResponse) = 0;
	/// ����Ϣ��ɾ��һ����
	virtual int			FUNCTION_CALL_MODE RemoveTag(int iTag) = 0;



	//�޸���:xuqq
	//�޸�ʱ��:2008-11-11
	//�޸�Ŀ��:���ӽӿ�Ϊ�������ɵ�����ѹ������
	//����Ϊ�����ӵĴ���

	///�ɹ�����0,ʧ�ܷ���1
	///Ĭ��ʹ��1��ѹ�����ܣ�Ҳ����minilzoѹ���㷨
	virtual int			FUNCTION_CALL_MODE SetCompressID(int iCompressID = 1) = 0;

	virtual void		FUNCTION_CALL_MODE SetOwner(void* lpOwner) = 0;
	virtual void*       FUNCTION_CALL_MODE GetOwner() = 0;

	//�õ����ü���
	virtual int			FUNCTION_CALL_MODE GetRef() = 0;
	//--------------------------------------xuqq�Ĵ��뵽��Ϊֹ



	virtual int			FUNCTION_CALL_MODE AddTimeStamp(char* lpText) = 0;

	//	maoyinjie 2011/04/19	���ӱ���TAG�Ľӿ�
	virtual int FUNCTION_CALL_MODE BeginTour() = 0;		//	��ʼ����
	//	����<0	˵���Ѿ��������
	virtual int FUNCTION_CALL_MODE GetItemTag() = 0;	//	��õ�ǰTAG
	virtual int FUNCTION_CALL_MODE NextItem() = 0;		//	����һ��TAG

	
	//	maoyinjie 2012/08/14	����ֱ�Ӵ���ҵ����Ľӿ�
	//	ҵ��������	ҵ�������ݳ���	iNoCompressInForce=1:ǿ�Ʋ�ѹ��,  0:��������,����ѹ��,Ҳ���ܲ�ѹ��
	virtual int FUNCTION_CALL_MODE SetBizData(char* lpBizData, int iBizDataLen, int iNoCompressInForce=0) = 0;
	//	����ҵ��������	
	//	����:	ҵ�������ݳ���	iNoCompressInForce=1:ǿ�Ʋ���ѹ��,  0:��������,���ܽ�ѹ��,Ҳ���ܲ���ѹ��
	virtual const void*	FUNCTION_CALL_MODE GetBizData(int* ilpRawDataLen, int iNoCompressInForce=0) = 0;
};


#endif
