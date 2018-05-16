/** ��ƽ̨��̬�⶯̬������CLib�ඨ��
Դ��������: lib_loader.h
�������Ȩ: �������ӹɷ����޹�˾ ��Ȩ����
ϵͳ����: ���ü���ƽ̨
ģ������: ��ƽ̨����� 
����˵��: ��ƽ̨��̬�⶯̬������
	      ͬʱ�ṩһ������ת�����ߺ���ConvertFileName()��
	      �ڲ�ͬƽ̨�¶�̬�⣨����⣩���ֿ���ͳһ���ò���ǰ��׺�����֣��ɴ˺���ת��ʵ���ļ�����
����ĵ�: 
����:
���: (��ѡ��)
	
�޸ļ�¼
�޸�����:
�޸���Ա:
�޸�˵��:
*******************************************************************/

#ifndef _LIB_LOADER_INC_
#define _LIB_LOADER_INC_

#include <os/config_env.h>

BEGIN_FBASE2_NAMESPACE

#ifndef _WIN32

///��̬����
#define HMODULE		void *

///�������
#define FARPROC		void *

///�򿪶�̬��
#define LoadLibrary		dlopen

///ȡ������ַ
#define GetProcAddress	dlsym

///�رն�̬��
#define FreeLibrary		dlclose

#endif /* end of no  _win32 */

///��̬�������
/**
*@������win32��֧��posix��׼��unixƽ̨
*/

class API_EXPORT CLib
{
public:
	///�ڲ�ͬƽ̨�°�һ����ǰ��׺�Ķ�̬����ת����ʵ���ļ���
	/**
	 *@param char * lpNew ���������ת�����ʵ���ļ����������������׼���ռ�
	 *@param const char *libfile ���������һ����ǰ��׺�Ķ�̬����
	 */
	static void ConvertFileName(char * lpNew,const char *libfile);
public:	
	CLib();
	
	/**���캯��
	 *@param _libname  ��̬����������ǰ��׺
	 */
	CLib(const char * _libname );
	
	///����һ����̬��ģ��
	/**
	 *@param _libname  ��̬����������ǰ��׺
	 *@return ����ʧ�ܷ���NULL�� �������ؾ��
	 */
	HMODULE Load(const char *libname = NULL);
	
	///����һ����̬���еĵĺ���
	/**
	 *@param hModule  ��̬����
	 *@param lpProcName ���صĺ�������
	 *@return  ����ʧ�ܷ���NULL�� �������ؾ��
	 */
	FARPROC LoadFunc(const char *ProcName);
	
	///ж�ض�̬��
	/**
	 *@return 0 �ɹ�������ʧ��
	 */
	int Free();
	
	///ȡ�ö�̬��ľ��
	const HMODULE GetHandle() const;
	
	///ȡ��̬����ʧ�ܺ�Ĵ�����Ϣ
	/**��windows�·��ش�����ַ�����������ƽ̨�·��ش�����Ϣ��
	 *@retrun ������Ϣ
	 */
	char * GetLastErrorInfo();
	
	///ȡ�ö�̬���ļ���
	const char* GetName() const;
	
	const char* GetPath();
	///�Ƿ���Ч
	bool operator!();
	
private:
#if defined(_WIN32)
	char *m_szErrInfo;
#endif
	
	HMODULE m_hLib;   //��̬����
	char  m_szLibName[256];  //��̬����
	char  m_szPath[256];
};

END_FBASE2_NAMESPACE

#endif
