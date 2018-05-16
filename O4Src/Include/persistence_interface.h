/***********************************************************************
��Ȩ����: �������ӹɷ����޹�˾
��Ŀ����: MC2.0��Ŀ
��    ��: V1.0
����ϵͳ: Windows/Linux/HP-UX
�� �� ��: persistence_interface.h
�ļ�����: 
�� Ŀ ��: CRES
�� �� Ա: 05909
��������: 2012-6-12   17:03:00
��    ��:
�޸�����:
***********************************************************************/
#ifndef PERSISTENCE_INTERFACE_H
#define PERSISTENCE_INTERFACE_H

#include <Include/plugin_interface.h>
#include <Include/esb_message_interface.h>
#include <Include/mcgd_interface.h>


/* ����ӿ�ID���� */
#define SID_PERSISTENCE "persistence"


/* ����ӿڶ��� */
struct IPersistencePlugin: public IKnown
{
    ///�־û���Ϣ�ӿ�
    /**
     *@param const IESBMessage* msg: д�����Ϣ������Ϊ��
     *@return int: ���ز��������0��ʾ�ɹ���-1��ʾʧ��
     */
    virtual int FUNCTION_CALL_MODE writeMsg(const IESBMessage* msg) = 0;

    ///���ݡ����⡱��ȡ��ǰ��Ч��Ϣ�ķ������б�
    /**
     *@param const char* topicName: ������������Ϊ��
     *@param LPSENDER_NAME publisher: �������ⲿ���ط������б�����Ϊ��
     *@param unsigned int uiPublisher: ��ʾ���淢�����б������Դ�ŷ����ߵ�����
     *@return int: ʧ�ܷ���-1���ɹ������б���ʵ�ʷ����������������ⲿʹ��SENDER_NAME[2000]���룬���жϷ���ֵ���������2000������������ȡ
     */
    virtual int FUNCTION_CALL_MODE getPublisher(const char* topicName, LPSENDER_NAME publisher, unsigned int uiPublisher) = 0;

    ///���ݡ����⡢�����ߡ���ȡ��Ч��Ϣ�������С�ⲿ��Žӿ�
    /**
     *@param const char* topicName: ������������Ϊ��
     *@param LPSENDER_NAME publisher: ��������������Ϊ��
     *@param unsigned int* maxExtMsgId: ���������Ч��Ϣ���ⲿ���
     *@param unsigned int* minExtMsgId: ������С��Ч��Ϣ���ⲿ���
     *@return int: ���ز��������0��ʾ�ɹ���-1��ʾʧ��
     */
    virtual int FUNCTION_CALL_MODE getRange(const char* topicName, const LPSENDER_NAME publisher, unsigned int* maxExtMsgId, unsigned int* minExtMsgId) = 0;

    ///���ݡ����⡢�����ߡ���ȡ��ʷ����ⲿ���
    /**
     *@param const char* topicName: ������������Ϊ��
     *@param LPSENDER_NAME publisher: ��������������Ϊ��
     *@param unsigned int* maxExtMsgId: ������ʷ�����Ϣ���ⲿ���
     *@return int: ���ز��������0��ʾ�ɹ���-1��ʾʧ��
     */
    virtual int FUNCTION_CALL_MODE getMaxExtMsgId(const char* topicName, const LPSENDER_NAME publisher, unsigned int* maxExtMsgId) = 0;

    ///���ݡ����⡢�����ߡ���Ϣ�ⲿ��š���ȡ��Ϣ�ӿ�
    /**
     *@param const char* topicName: ������������Ϊ��
     *@param LPSENDER_NAME publisher: ��������������Ϊ��
     *@param unsigned int ExtMsgId: ��Ϣ���ⲿ���
     *@param IESBMessage* msg: ���ص���Ϣ
     *@return int: ���ز��������0��ʾ�ɹ���-1��ʾʧ��
     */
    virtual int FUNCTION_CALL_MODE readMsg(const char* topicName, const LPSENDER_NAME publisher, unsigned int ExtMsgId, IESBMessage* msg) = 0;

    ///���ݡ����⡢��Ϣ�ڲ���š���ȡ��Ϣ�ӿ�
    /**
     *@param const char* topicName: ������������Ϊ��
     *@param unsigned int IntMsgId: ��Ϣ���ڲ����
     *@param IESBMessage* msg: ���ص���Ϣ
     *@return int: ���ز��������0��ʾ�ɹ���-1��ʾʧ��
     */
    virtual int FUNCTION_CALL_MODE readMsg(const char* topicName, unsigned int IntMsgId, IESBMessage* msg) = 0;

    ///�����־û��������������������Ĺ����г־û�����������ӿڲ������ṩ����
    /**
     *@param
     *@return int: ���ز��������0��ʾ�ɹ���-1��ʾʧ��
     */
    virtual int FUNCTION_CALL_MODE triggerDump() = 0;
};

/* ���������׼�������������ܼ�����˵���μ�"Include/plugin_interface.h" */
#ifdef __cplusplus
extern "C" {
#endif
    /* ��ѯ������еĲ����Ϣ */
    int FUNCTION_CALL_MODE GetPersistenceInfo(int iIndex, tagBaseServiceInfo* ppv );

    /* ȡ���ʵ�� */
    IKnown* FUNCTION_CALL_MODE GetPersistenceInstance();

    /* ȡ����������������ID�� */
    char*  FUNCTION_CALL_MODE GetPersistenceDependSvr(void* lpInstance);

    /* �����ʼ�� */
    int FUNCTION_CALL_MODE PersistenceInit(void* lpInstance, PFOnSetTimeOut pfOnSetTimeOut);
#ifdef __cplusplus
}
#endif

#endif
