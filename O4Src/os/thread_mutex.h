/** ��ƽ̨�̻߳�����CThreadMutex���Զ���CAutoMutex�ඨ��
Դ��������: thread_mutex.h
�������Ȩ: �������ӹɷ����޹�˾ ��Ȩ����
ϵͳ����: ���ü���ƽ̨
ģ������: ��ƽ̨����� 
����˵��: ��ƽ̨�̻߳�������װ�࣬�ڻ����������ϰ�װ��һ���Զ�����
����ĵ�: 
����:
���: (��ѡ��)
	
�޸ļ�¼
�޸�����:
�޸���Ա:
�޸�˵��:
*******************************************************************/


#ifndef _THREAD_MUTEX_INC_
#define _THREAD_MUTEX_INC_

#include <os/config_env.h>

BEGIN_FBASE2_NAMESPACE

///��ƽ̨���̻߳���������
class API_EXPORT CThreadMutex
{
public:
#ifndef _WIN32
    typedef pthread_mutex_t     THREADMUTEX;
#else
    typedef CRITICAL_SECTION    THREADMUTEX;
#endif

	///���캯������ʼ���ٽ���
	CThreadMutex();
	///���������� ����ٽ���
	~CThreadMutex();

	///�����ٽ���
	void Acquire();
	
	///�뿪�ٽ���
	void Release();

#if (defined (_WIN32_WINNT) && (_WIN32_WINNT > 0x0400)) || !defined(_WIN32)
	///���Խ����ٽ�����ʧ�ܷ��ط���
	int TryAcquire();
#endif

private:
	///���Ļ��������
	THREADMUTEX  m_hMutex;
};

///�Զ�����
/**����һ���ֲ���װ����󣬶����ǼӶ�����������Χʱ�ֲ������ͷţ�����Ҳ�Զ��ͷţ�
 * ��һ�������ڼ�����ȷ���˺����κ��˳����������ͷţ��Ա������� 
 * ע�⣺Ҫ��ֹ��Щ��������δ�����õľֲ������Ż���.
 */
class API_EXPORT CAutoMutex
{
public:
	CAutoMutex(CThreadMutex * pMutex)
	{
		m_pMutex=pMutex;
		pMutex->Acquire();
	};
	~CAutoMutex()
	{
		m_pMutex->Release();
	};
private:
	CThreadMutex * m_pMutex;
};

END_FBASE2_NAMESPACE

#endif

