/*******************************************************
Դ��������:msg_queue.h
�������Ȩ:�������ӹɷ����޹�˾
ϵͳ����:  posix��Ϣ���з�װ
ģ������:  
����˵��:  
��    ��:  huxb
��������:  20131128
��    ע: 
*********************************************************/
#ifndef _ACD_MSG_QUEUE_H_
#define _ACD_MSG_QUEUE_H_

#include <os/config_env.h>
#include <os/inttypes.h>

//��Ϣ�������Ƶ���󳤶�
#ifndef PATH_MAX
#define PATH_MAX 256
#endif

#ifdef _WIN32
#include <Windows.h>
#define MQD HANDLE
#else

#include <mqueue.h>
#include <sys/stat.h>
#define MQD mqd_t
#define POSIX_IPC_PREFIX "/"
#define QUEUE_MODE (S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH)

#endif

class CMsgQueue{
public:
	CMsgQueue();

	~CMsgQueue();

	/* ������Ϣ���� �����Ϣ���д��ڣ����
	* @param queueName ��Ϣ�������֣��������κ�б�ܷ�
	* @param msg_max ��Ϣ���������Ϣ��
	* @param msg_size ��Ϣ��󳤶�
	* @return 0 �ɹ�
	*		 -1 ʧ��
	*/
	int Create(const char* queueName, long msg_max = 10, long msg_size = 8192);

	/* ����Ϣ���� �����Ϣ���в����ڣ���ʧ��
	* @param queueName ��Ϣ�������֣��������κ�б�ܷ�
	* @return 0 �ɹ�
	*		 -1 ʧ��
	*/
	int Open(const char* queueName);

	/* ����Ϣ�����ж�ȡ����
	* @param lpBuf ���ջ�����
	* @param nLen  ����������
	* @param dwMillsSecond  ��ʱʱ�䣬��λΪms
	* @return -2 ��ʱ
			  -1 ��������
				 �ɹ�������Ϣ�ĳ���	  
	*/
	int Read(char* lpBuf, size_t nLen, long dwMillsSecond = INFINITE);

	/* ����Ϣ������д����
	* @param lpBuf �������ݵ�ַ
	* @param nLen  �������ݳ���
	* @param dwMillsSecond  ��ʱʱ�䣬��λΪms
	* @return -2 ��ʱ
			  -1 ��������
			   0 �ɹ�
	*/
	int Write(const char* lpBuf, size_t nLen, long dwMillsSecond = INFINITE);

	/* �ر���Ϣ����
	* @return -1 ʧ��
	*		   0 �ɹ�
	*/
	int Close();

	/* ɾ����Ϣ����
	* @return -1 ʧ��
	*		   0 �ɹ�
	*/
	int Delete();

	/*
	* @return -1 ʧ�� �ɹ�������Ϣ���������Ϣ��
	*/
	long GetMaxMsg();

	/*
	* @return -1 ʧ�� �ɹ�������Ϣ����󳤶�
	*/
	long GetMsgSize();

	/*
	* @return -1 ʧ�� �ɹ�������Ϣ���еĵ�ǰ��Ϣ����
	*/
	long GetCurMsgs();

	/*
	* @return ��Ϣ���е���Ϣ�ܸ���(���̻߳����£�����ֵ�����ο�)
	*/
	long GetTotalMsgs();

	/* ���ش����
	*/
	int GetLastErr()
	{
		return errno;
	}
private:
	int CreateQueueName(const char* queueName);

#ifndef _WIN32
	void ConvertToTimespec(long dwMillsSecond, struct timespec& tm)
	{
		struct timeval tvNow;
		gettimeofday(&tvNow, NULL);

		tm.tv_sec = tvNow.tv_sec + dwMillsSecond / 1000;
		tm.tv_nsec = (tvNow.tv_usec + (dwMillsSecond % 1000) * 1000);	//	�������Ļ�ֻ��΢��
		if( tm.tv_nsec/(1000*1000) )	//	�����Ѿ���λ
		{
			tm.tv_sec++;
			tm.tv_nsec = tm.tv_nsec%(1000*1000);
		}
		tm.tv_nsec = tm.tv_nsec*1000;	//	ת��������
	}
#endif

private:
	MQD 			m_lpQueue;
	char *			m_lpQueueName;			//��Ϣ��������
	long			m_nTotalMsgs;			//���н�����е���Ϣ����
};

#endif
