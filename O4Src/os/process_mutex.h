/** ��ƽ̨���̻�����CProcessMutex�ඨ��
Դ��������: process_mutex.h
�������Ȩ: �������ӹɷ����޹�˾ ��Ȩ����
ϵͳ����: ���ü���ƽ̨
ģ������: ��ƽ̨����� 
����˵��: ��ƽ̨���̻�������װ��
	      ��windows��ʹ�û�����ʵ��;
	      ��linux/unix��ʹ�������ź���ʵ�֣���posix��sys v����,
	      ��Ҫ�ڱ���ʱ��USE_POSIX_SEMAPHORES��ָ���Ƿ���POSIX��׼���ź���,
          ʹ�������ź���ʵ�֣�����semaphore.cpp��
          
����ĵ�: 
����:
���: (��ѡ��)
	
�޸ļ�¼
�޸�����:
�޸���Ա:
�޸�˵��:
*******************************************************************/
#ifndef _PROCESS_MUTEX_INC_
#define _PROCESS_MUTEX_INC_

#include <os/config_env.h>
#include <os/semaphore.h>  //����������������ź���

BEGIN_FBASE2_NAMESPACE
/// ���̼�������
/*
 * ����UNIX/LINUXƽ̨���������ǻ����ź�����ʵ�ֵġ�������POSIX���ź���
 * �ڽ����쳣�˳�ʱû���Զ�������λ�Ĺ��ܣ���Ϊ�˱�֤�����߼���ȷ�ԣ���
 * ��ʹ��SYSV�ź������˰汾�Ľ��������ź���Ĭ��ʹ��SYSV�ź�����ʵ�֡���
 * �û���Ҫʹ��POSIX�ź����������ڱ���ʱ���� USE_POSIX_SEMAPHORES ��
 */
class API_EXPORT CProcessMutex
{
public:
	///���캯��
    CProcessMutex();
    
    ///���캯��
    /**
     *@param lpName, �����ƣ�����ȫ��Ψһ
     */
    CProcessMutex(const char lpName[]);

    ///��ʼ������
    /**
     *@param name, �����ƣ��������ֲ�ͬ����ʵ��
     *@return ���ط�0��ʾʧ��
     */
    int Init(const char name[]);
    
    ///��������
    ~CProcessMutex();

    ///����
    /**
        *@return 0��ʾ�ɹ���
    */
    int Acquire();
    ///���Ի����������ò�����������
    /**
     * @return 0��ʾ�ɹ��õ�������ʵʧ��
     */

    int TryAcquire();
    ///�ͷ�
    /**
        *@return 0�ɹ�������ʧ��
    */
    int Release();

private:
	///�ڲ�����������ͬƽ̨��һ��
#ifdef _WIN32
    HANDLE     m_hMutex;   
#else

    CSemaphore * m_lpSem;
#endif

};

class CProcAutoLock
{
public:
    CProcAutoLock( CProcessMutex *pm )
    {
        lpMut = pm;
        lpMut->Acquire();
    }
    ~CProcAutoLock()
    {
        lpMut->Release();
    }
private:
    CProcessMutex *lpMut;
};


END_FBASE2_NAMESPACE

#endif

