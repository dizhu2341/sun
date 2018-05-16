/** ��ƽ̨�¼� CReadWriteLock �ඨ��
Դ��������: read_write_lock.h
�������Ȩ: �������ӹɷ����޹�˾ ��Ȩ����
ϵͳ����: ���ü���ƽ̨
ģ������: ��ƽ̨����� 
����˵��: ��ƽ̨��д����װ��
����ĵ�: 
����:
���: (��ѡ��)
	
�޸ļ�¼
�޸�����:
�޸���Ա:
�޸�˵��:
*******************************************************************/
#ifndef READ_WRITE_LOCK_INC_
#define READ_WRITE_LOCK_INC_

#include <os/config_env.h>

BEGIN_FBASE2_NAMESPACE

///��д������
class API_EXPORT CReadWriteLock
{
public:
	CReadWriteLock();
	~CReadWriteLock();

	///��ö���
	/**
	 *@return ���� ��ʾʧ�ܣ�ԭ������ϵͳ���� 0��ʾ�ɹ�
	 */
	int ReadAcquire();

	///�ͷŶ���
	/**
	 *@return ���� ��ʾʧ�ܣ�ԭ������ϵͳ���� 0��ʾ�ɹ�
	 */
	int ReadRelease();

	///���д��
	/**
	 *@return ���� ��ʾʧ�ܣ�ԭ������ϵͳ���� 0��ʾ�ɹ�
	 */
	int WriteAcquire();

	///�ͷ�д��
	/**
	 *@return ���� ��ʾʧ�ܣ�ԭ������ϵͳ���� 0��ʾ�ɹ�
	 */
	int WriteRelease();
private:
#ifdef _WIN32
	///���߳���
	long				m_nReaderCount;
	///�������������ٽ���
	CRITICAL_SECTION	m_Mutex;
	///������
	CRITICAL_SECTION	m_hDataLock;
#else			//for posix unix
	///��д������
	pthread_rwlock_t	m_Lock;
#endif
	///��յ����溯��
	CReadWriteLock(CReadWriteLock &lock);
	CReadWriteLock & operator=(CReadWriteLock &lock);
};

END_FBASE2_NAMESPACE

#endif
