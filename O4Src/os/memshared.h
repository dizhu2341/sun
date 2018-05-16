/**��ƽ̨���̼乲���ڴ� CSharedMem �ඨ��
Դ��������: memshared.h
�������Ȩ: �������ӹɷ����޹�˾ ��Ȩ����
ϵͳ����: ���ü���ƽ̨
ģ������: ��ƽ̨����� 
����˵��: ��ƽ̨���̼乲���ڴ���
	      ������WIN32��֧��posix��sys v��׼��linux/unixƽ̨
	      ���ϵͳ��֧��posix�������ڴ�ӳ����ʹ�� sys v ��ʵ�֣������ڵ�linux
	      ��linux/unix�£�ʹ��sys v��׼������Ҫ���� USE_SYSV_SHAREMEM

����ĵ�: 
����:
���: (��ѡ��)
	
�޸ļ�¼
�޸�����:
�޸���Ա:
�޸�˵��:
*******************************************************************/


#ifndef _MEMSHARED_INC_
#define _MEMSHARED_INC_

#if defined(_MSC_VER)
#pragma warning(disable:4284)
#endif

#include <os/config_env.h>

//#define TRADER_API_EXPORT

BEGIN_FBASE2_NAMESPACE

/// �����ڴ涨��, ����ּ�ڽ��̼乲���ڴ棬����ʹ�þ������ڴ�ӳ�����
/**
 *������WIN32��֧��posix��׼��unixƽ̨��sys v
 */
class API_EXPORT CSharedMem
{
public:
    ///���캯������ʼ����Դ
    CSharedMem();
    
    ///���캯�����������ߴ�һ�������ڴ棬����Ѿ������������
    /**
     * @param filename �ļ���
     * @param size �����ڴ�Ĵ�С
     */
    CSharedMem(const char* filename, unsigned size = 1024 * 1024);
    
    ///�����������ͷ�ռ�õ���Դ
    ~CSharedMem();

    ///��ʼ��һ�ι����ڴ�
    /**
     * @param filename �ļ���
     * @param size �����ڴ�Ĵ�С
     * @return ����ɹ��򷵻ع����ڴ��׵�ַ��ʧ�ܷ���NULL
     */
    void *Create(const char* filename, unsigned size = 1024 * 1024);

    ///��һ�ι����ڴ�
    /**
     * @param filename �ļ���
     * @return ����ɹ��򷵻ع����ڴ��׵�ַ��ʧ�ܷ���NULL
     */
    void *Open(const char* filename);

    ///��ȡ�����ڴ�Ĵ�С
    const size_t Size() const;

    ///�رչ����ڴ���
    /**
     * @return ����0��ʾʧ�ܣ������ʾ�ɹ�
     */
    int Close();


    int UnLink();


    ///��ȡ�����ڴ���׵�ַ
    const void * operator*() const; 

    ///�ж��Ƿ���Ч
    bool operator!() const;
private:

    ///��չ�����ڴ�Ĵ�С����������������, ��չ�����ڴ��С�����ڶ�ռģʽ�²��ܳɹ�
    /**
     * @param appendsize ��չ�ĳ���
     * @return �����µ��׵�ַ�����ʧ�ܷ���NULL
     */
    const void* Resize(size_t appendsize);
    
    ///ӳ����ļ���
    char  m_szName[255];
    
    ///�ڴ�����ַ
    void *  m_pStart;
    
    ///����
    size_t  m_iSize;
    
#if !defined(_WIN32)
    ///�ں˶���ľ��
    int m_lFd;
    
    // liangyong ɾ�� 20080221
//    ///�Ƿ�Ϊ�����ߣ�posix�´����߸���ɾ���ļ�shm_unlink() ��
//    bool m_bCreater;
#else
    ///ӳ���ļ����
    HANDLE  m_hFile;
    ///ӳ����
    HANDLE m_hMapHandle;
#endif
};

END_FBASE2_NAMESPACE

#endif
