/**CThread��ƽ̨�߳��ඨ��
Դ��������: thread.h
�������Ȩ: �������ӹɷ����޹�˾ ��Ȩ����
ϵͳ����: ���ü���ƽ̨
ģ������: ��ƽ̨����� 
����˵��: ��ƽ̨�̷߳�װ��
����ĵ�: 
����:
���: (��ѡ��)
	
�޸ļ�¼
�޸�����:
�޸���Ա:
�޸�˵��:
*******************************************************************/

#ifndef _THREAD_INC_
#define _THREAD_INC_

#include <os/config_env.h>
#include <os/thread_mutex.h>  
#include <os/inttypes.h>

//#define TRADER_API_EXPORT

BEGIN_FBASE2_NAMESPACE

///һ���򵥵Ŀ�ƽ̨�߳��ඨ��
/**
 * ʹ�÷�����class myThread:public CThread{...}
 * ע������Run���������ִ���壬����ͨ�����ع��캯�����������������������ݲ���
 * ʵ�����������ʵ��ΪObj, �����Obj.Start()�������߳�
 * Run()
 * {
 *     ....
 *   }
 */
/**
*����������_win32��֧��POSIX��׼��unixƽ̨
*/
class API_EXPORT CThread
{
public:
#ifndef _WIN32
    typedef     pthread_t THREAD;
#else
    typedef     HANDLE    THREAD;
#endif
	CThread();
	///�����߳�
	int Start();		

	///������������ֹ�̲߳��ͷ���Դ
	virtual ~CThread();

	///ȡ���߳��ڲ����
	CThread::THREAD GetId() const
	{
		return m_hThread;
	}	

	///�߳��Ƿ��Ѿ�����
	/**
		*���״̬Ϊtrue���ʾ�߳�����
	*/
	bool IsRunning()const
	{ 
		return m_bStarted;
	};

	void SetStatus(bool bStatus);
	///����߳���ֹ״̬
	/**
		*���״̬Ϊtrue���ʾ��ֹ�����У����Լ���ֵ�Խ����߳�������
	*/
	bool IsTerminated()const
	{
		return m_bTerminateRequest;
	}
	

	/// �����߳����ѭ��ִ�д���
	void IncreaseLoops()
	{
		m_dwLoopTimes++;
		return;
	}
	/// ����߳�ѭ������
	uint32 GetLoops()
	{
		return m_dwLoopTimes;
	}

	/// ����߳��Ƿ�������(�ϵ�ѭ�������͵�ǰ��ѭ�������Ƚϣ����߲�һ����˵���̹߳���
	/// һ������������ʱ���������㹻��������ͻ�ó�����Ľ���)
	bool IsActive()
	{
		bool bResult;
		bResult = (m_dwOldLoopTimes != m_dwLoopTimes);
		m_dwOldLoopTimes = m_dwLoopTimes;
		return bResult;
	}

	///�߳���ֹ
	virtual void Stop(long dwWait = INFINITE);

	virtual void Signal();
#ifdef _WIN32
	friend static unsigned WINAPI thread_function(void* pArg);
#else
	friend void * thread_function(void *pArg);
#endif

protected:
	///�߳�ִ���壬ʹ���������ظú����������߳�ִ����
	virtual long Run() = 0;
	///�Ƿ���ֹ�߳�
	bool m_bTerminateRequest;
private:
	///��ֹ���ƺ͸�ֵ
	CThread( const CThread& );
	CThread& operator=(const CThread& );

	bool m_bStarted;
	///�ڲ��߳̾��
    THREAD  m_hThread;
protected:
	//	�߳̾�����ѭ������
	uint32			m_dwLoopTimes;
	uint32			m_dwOldLoopTimes;
	CThreadMutex 	m_Mutex;  //������
};

//---------------------------------------------------------------------------------------------

class API_EXPORT CThreadEx
{
public:
#ifndef _WIN32
    typedef     pthread_t THREAD;
#else
    typedef     HANDLE    THREAD;
#endif

	CThreadEx();
	///�����߳�
	int Start();		

	///������������ֹ�̲߳��ͷ���Դ
	virtual ~CThreadEx();

	///ȡ���߳��ڲ����
	CThreadEx::THREAD GetId() const
	{
		return m_hThread;
	}	

	///�߳��Ƿ��Ѿ�����
	/**
		*���״̬Ϊtrue���ʾ�߳�����
	*/
	bool IsRunning()
	{
#if defined(_WIN32)
	    EnterCriticalSection(&m_hMutex);
		bool ret = m_bStarted;
		LeaveCriticalSection(&m_hMutex);
		return ret;
#else
	   	pthread_mutex_lock(&m_CondMutex);
	 	bool ret = m_bStarted;
		pthread_mutex_unlock(&m_CondMutex);
		return ret;
#endif
	};

	void SetStatus(bool bStatus);
	///����߳���ֹ״̬
	/**
		*���״̬Ϊtrue���ʾ��ֹ�����У����Լ���ֵ�Խ����߳�������
	*/
	bool IsTerminated() const
	{
		return m_bTerminateRequest;
	}

	/// �����߳����ѭ��ִ�д���
	void IncreaseLoops()
	{
		m_dwLoopTimes++;
		return;
	}
	/// ����߳�ѭ������
	uint32 GetLoops()
	{
		return m_dwLoopTimes;
	}

	/// ����߳��Ƿ�������(�ϵ�ѭ�������͵�ǰ��ѭ�������Ƚϣ����߲�һ����˵���̹߳���
	/// һ������������ʱ���������㹻��������ͻ�ó�����Ľ���)
	bool IsActive()
	{
		bool bResult;
		bResult = (m_dwOldLoopTimes != m_dwLoopTimes);
		m_dwOldLoopTimes = m_dwLoopTimes;
		return bResult;
	}

	// �߳���ֹ, ��Ŀǰ��ʵ����, ������̺߳����е��������Stop, ���������
	virtual void Stop(long dwWait = INFINITE);

	virtual void Signal();

#if defined(_WIN32)
	friend static unsigned WINAPI thread_function_ex(void* pArg);
#else
    friend void OnThreadExit(void* pArg);
	friend void * thread_function_ex(void *pArg);
#endif

protected:
	///�߳�ִ���壬ʹ���������ظú����������߳�ִ����
	virtual long Run() = 0;
	///�Ƿ���ֹ�߳�
	bool m_bTerminateRequest;
private:
	///��ֹ���ƺ͸�ֵ
	CThreadEx( const CThreadEx& );
	CThreadEx& operator=(const CThreadEx& );

	bool m_bStarted;

    THREAD  m_hThread;
protected:
	//	�߳̾�����ѭ������
	uint32			m_dwLoopTimes;
	uint32			m_dwOldLoopTimes;

#if defined(_WIN32)
	CRITICAL_SECTION	m_hMutex;
#else
    pthread_mutex_t		m_CondMutex;
    pthread_cond_t		m_Cond;

    pthread_mutex_t		m_ExitMutex;
#endif
};

END_FBASE2_NAMESPACE

#endif
