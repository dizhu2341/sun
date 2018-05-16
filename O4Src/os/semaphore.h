/**��ƽ̨�ź��� CSemaphore �ඨ��
Դ��������: semaphore.h
�������Ȩ: �������ӹɷ����޹�˾ ��Ȩ����
ϵͳ����: ���ü���ƽ̨
ģ������: ��ƽ̨����� 
����˵��: ��ƽ̨�ź�����(����������)
	      ��linux/unix���ź�����posix��sys v����ʵ�֣���Ҫ�ڱ���ʱ�� USE_SYSV_SEMAPHORES��ָ��.	      
����ĵ�: 
����:
���: (��ѡ��)
	
�޸ļ�¼
�޸�����:
�޸���Ա:
�޸�˵��:
*******************************************************************/

#ifndef SEMAPHORE_TYPE_INC_
#define SEMAPHORE_TYPE_INC_

#include <os/config_env.h>

#if !defined(_WIN32)
	#include <sys/types.h>
	#include <sys/ipc.h>
	#include <sys/sem.h>
	#if defined(__GNU_LIBRARY__) && !defined(_SEM_SEMUN_UNDEFINED)
		/* union semun is defined by including <sys/sem.h> */
	#else
		/* according to X/OPEN we have to define it ourselves */
		union semun {
			int val;					/* value for SETVAL */
			struct semid_ds *buf;		/* buffer for IPC_STAT, IPC_SET */
			unsigned short *array;		/* array for GETALL, SETALL */
										/* Linux specific part: */
			struct seminfo *__buf;		/* buffer for IPC_INFO */
		};
	#endif

#endif

BEGIN_FBASE2_NAMESPACE

///�����ź������ֳ���
#define SEM_NAME_LEN 255

///�ź�����
/**
 * ������win32��֧��posix��׼��unixƽ̨, �ṩ�̼߳���߽��̼�ͬ���Ļ���
 *
 *
 * unixƽ̨sysv��posix����ʵ�ֵ���Ҫ����Ϊ
 * sysv 
 * (1) �ź����ṩundo����, ���������˳�ʱ(�����쳣�˳�), ��������undo�Ĳ������ᱻ��ת, 
 *     �ʿɱ�����Ϊ���̱���������������. 
 * (2) ���, sysv���ṩ�����ź���
 * (3) sysv�ź���Ч�ʽϵ�, ������ƽ��
 *
 * posix
 * (1) posix��undo����, ���ڶ����ͬ��ʱ, ��������̱����������������������Ŀ���
 * (2) posix�ṩ����(�����ļ�) �� ����(�����ڴ�)
 * (3) ���ܽ�sysvΪ��, ����ƽ��
 *
 */

enum SemStyle{SYSV_STYLE, POSIX_STYLE};

class API_EXPORT CSemaphore
{
public:
	///���캯��
	CSemaphore(SemStyle style = SYSV_STYLE);

	///���캯������ʼ���ź���
	/**һ��ʹ���������,����Ѵ�����Open
	 * @param init ��ʼ�ź���ֵ
	 * @param sem_name ������ڽ��̼�ͬ��,����Ҫʹ�þ������źŵ�,�ò�������ָ���źŵƵ�����
	 * @param style ʵ�ֱ�׼, win32ƽ̨���Դ˲��� 
	 				0 sysv 
					1 posix
	 */
	CSemaphore( int init , const char *sem_name = "", SemStyle style = SYSV_STYLE);

	///�����ź���
	/**
	 * @param init ��ʼ�ź���ֵ
	 * @param sem_name ������ڽ��̼�ͬ��������Ҫʹ�þ������źŵƣ��ò�������ָ���źŵƵ�����
	 * @return int �ɹ�����0
	 */
	int Create( int init , const char *sem_name = "");

	/**һ����Create,����Ѵ�����Open
	 * @param sem_name ������ڽ��̼�ͬ��������Ҫʹ�þ������źŵƣ��ò�������ָ���źŵƵ�����
	 * @return 0,�ɹ�������ʧ��
	 */
	int Open(const char* sem_name);
 
	///���������� �ر��ź���
	~CSemaphore();

	///�ȴ�һ���ź���,����ʱ�ź���ֵ-1
	int Wait(int iTimeOut = INFINITE) const;

	///���Եȴ�һ���ź�,������
	/**
	 * @return 0��ʾ�ɹ�(���ź���,�ҷ���ʱ�ź���ֵ-1)������ʧ��
	 */
	int TryWait() const;

	///����һ���źţ����ź���ֵ+1
	/**
	 * @return 0��ʾ�ɹ�������ʧ��
	 */
	int Post() const;

	///���³�ʼ���ź���
	/**
	 * @param init �ź����ĳ�ʼֵ
	 */
	void Reset( int init = 0 );

	///�����źŵȶ�����Ч
	bool operator!();

	///ȡ�źŵ�����
	const char* Name() const;

	///�źŵƶ����Ƿ���Ч
	bool IsValid();

protected:
    ///��ǰ�ź�����ֵ�� ��ΪĿǰwindows�ϵ�ʵ�ֲ�����ȷȡ����ֵ������δ����
	int Value() const;
private:
	///�źŵ�����
	char m_szName[SEM_NAME_LEN + 1];

#ifdef _WIN32
	HANDLE	m_hWin32_Sem;
#else
	int		m_hSYSV_Sem;
	sem_t*	m_hPOSIX_Sem;

	SemStyle	m_iStyle;
#endif

	CSemaphore(CSemaphore &);
	CSemaphore &operator=(CSemaphore &);
};

END_FBASE2_NAMESPACE
#endif

