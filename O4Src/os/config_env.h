/**��ƽ̨��������ͷ�ļ�����
Դ��������: config.h
�������Ȩ: �������ӹɷ����޹�˾ ��Ȩ����
ϵͳ����: ���ü���ƽ̨
ģ������: ��ƽ̨����� 
����˵��: ���ݸ�ƽ̨�����������Ѷ���ĺ��������ͷ�ļ���ͳһ���峣�ú�.
	      ������ƽ̨��װ����Ӧ���Ȱ������ļ������ļ�����config_win32.h��config_posix.h��
	      �����õı��������������£�
	         _MSC_VER     MS VC�������汾
	         __cplusplus  c++������
	         __GNUC__     gcc/g++������
	         __HP_aCC     HP aCC������
	         __IBMCPP__	  IBM VACPP������
	      
	      �����õĲ���ϵͳ���������£�	         
	         _WIN32       Win32�����ϵͳ
	         __linux__    linux�����ϵͳ
	         __hpux       HPUX�����ϵͳ
	         _AIX         IBM AIX�����ϵͳ
	         __sparc__    SUN Solaris����ϵͳ
	         sun          SUN Solaris����ϵͳ,������__sparc__��ʶ��
	    
����ĵ�: 
����:
���: (��ѡ��)
	
�޸ļ�¼
�޸�����:
�޸���Ա:
�޸�˵��:
*******************************************************************/

#ifndef _CONFIG_INC_
#define _CONFIG_INC_

/// the all config files include

#ifndef __cplusplus
#error "the fbase lib only be used in c++"
#endif

#if defined (_MSC_VER) && _MSC_VER < 1200
#error "please use this header only over MSVC 6.0 if using vc compiler"
#endif


#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

///����Ŀ�����ռ䶨��
#define FBASE_NAMESPACE			FBASE
#define FBASE2_NAMESPACE		FBASE2
///define the namesapce
#define NAMESPACE_BEGIN(x)		namespace x {
#define NAMESPACE_END			}
#define USING_NAMESPACE(x)		using namespace x;

#define BEGIN_FBASE_NAMESPACE	NAMESPACE_BEGIN(FBASE_NAMESPACE)
#define END_FBASE_NAMESPACE		NAMESPACE_END
#define USING_FBASE_NAMESPACE	USING_NAMESPACE(FBASE_NAMESPACE)

#define BEGIN_FBASE2_NAMESPACE	NAMESPACE_BEGIN(FBASE2_NAMESPACE)
#define END_FBASE2_NAMESPACE	NAMESPACE_END
#define USING_FBASE2_NAMESPACE	USING_NAMESPACE(FBASE2_NAMESPACE)

BEGIN_FBASE_NAMESPACE
END_FBASE_NAMESPACE

BEGIN_FBASE2_NAMESPACE
END_FBASE2_NAMESPACE

typedef unsigned char BYTE;         ///sizeof(BYTE) = 1
typedef unsigned short WORD;        ///sizeof(WORD) = 2

///��Ч�ľ��
#define InvalidHandle 0L

#ifdef _WIN32
#pragma message("_WIN32 macro activated!")

#if defined(_WIN32)&& _MSC_VER < 1300
#pragma warning(disable: 4786)				// ����ڱ�������STLͷ�ļ�ǰ
#pragma warning(disable: 4976)
#pragma warning(disable: 4291)				// ����ʹ�� new(nothrow)���쳣
#endif


#include <os/config_win32.h>
#else  ///for unix or linux
#include <os/config_posix.h>
#endif ///end of _WIN32

//TRACE�궨�壬��_DEBUG�����������Ϣ
#if defined (_DEBUG) && !defined(TRACE)
#define TRACE			printf
#else
#define TRACE			(void)
#endif

//��������֧��C++ģ�����ģʽ������Ŀ���ñ���������֧�֣�ʱ������USE_EXPORT
/*alog.h,alog.cpp���õ�����֧�ַ���ģʽʱ��ע�����cpp��ģ�����ʵ�ִ��룩��Ӧֱ�ӱ���cpp*/

#if defined(USE_EXPORT)
#define TEMPLATE_EXPORT		export
#else
#define TEMPLATE_EXPORT
#endif

//
// ��Ҫ�Ը�Ŀ¼�µ�Դ�ļ���������ʱ, �趨�� SEPARATE_COMPILE ��
#if defined(_WIN32) && !defined(SEPARATE_COMPILE)
	#ifdef DLL_API_EXPORT
		#define API_EXPORT __declspec(dllexport)
	#else
		#define API_EXPORT __declspec(dllimport)
	#endif
#else
	#define API_EXPORT
#endif

#include <new>

#define FBASE_NEW new(std::nothrow)

#endif
