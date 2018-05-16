/**Win32ƽ̨��������ͷ�ļ�����
Դ��������: config_win32.h
�������Ȩ: �������ӹɷ����޹�˾ ��Ȩ����
ϵͳ����: ���ü���ƽ̨
ģ������: ��ƽ̨����� 
����˵��: ���ļ���config_env.h����������Ӧֱ�Ӱ�����ͷ�ļ���
����ĵ�: 
����:
���: (��ѡ��)
	
�޸ļ�¼
�޸�����:
�޸���Ա:
�޸�˵��:
*******************************************************************/

#if !defined _CONFIG_WIN32_INC_ && defined _WIN32
#define _CONFIG_POSIX_INC_

#define _WINSOCKAPI_ // ��ֹwindows.h����winsock.h
#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <io.h>
#include <direct.h>
#include <time.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/timeb.h>

#define USE_IPX			//	֧��IPXЭ��
#include <wsipx.h>

///socket��ض���
#ifndef SOCKET_LEN_TYPE
#define SOCKET_LEN_TYPE			int
#endif

typedef int		socklen_t;

///����һ�����׼c��ͬ���ĺ�������
#define strcasecmp			  _stricmp
#define strncasecmp			  _strnicmp
#define snprintf			  _snprintf
#define stat				  _stat
#define access				  _access
#define mkdir                 _mkdir
#define splitpath             _splitpath
#define bzero				  ZeroMemory

///�ļ�����
#define F_OK					0
///�ļ���д
#define W_OK					2
///�ļ��ɶ�
#define R_OK					4
#define DIR_SLASH			'\\'


///�����Ļ��ϵͳ����
#define CLEAR_CMD			"cls"

///��̬���ļ���׺
#define LIB_POSTFIX		".DLL"
///��̬���ļ�ǰ׺
#define LIB_PREFIX		""

#ifdef _CRT_ ///ʹ��c���п�
# ifdef _USE_BEGINTHREAD
#   define THREAD_CALL                __cdecl
#   define THREAD_HANDLE              uintptr_t
#   define THREAD_RET_T               void
#   define CREATE_THREAD_FAILED       (-1L)
#   define CREATE_THREAD_ERROR        (errno)
#   define CREATE_THREAD(_S,_F,_P)    ((Handle)_beginthread((void (__cdecl *)(void *))_F,_S,(void *)_P))
#   define EXIT_THREAD                _endthread()
#   define CLOSE_HANDLE(x)            1
#   define THREAD_RETURN(x)           return
# else
#   define THREAD_CALL                WINAPI
#   define THREAD_HANDLE              HANDLE
#   define THREAD_RET_T               UINT
#   define CREATE_THREAD_FAILED       (0L)
#   define CREATE_THREAD_ERROR        (errno)
#   define CREATE_THREAD(_S,_F,_P)    ((Handle)_beginthreadex(0,_S,(UINT (WINAPI *)(void *))_F,(void *)_P,0,0))
#   define EXIT_THREAD                _endthreadex(0)
#   define CLOSE_HANDLE(x)            CloseHandle(x)
#   define THREAD_RETURN(x)           return(x)
# endif
#else                ///ʹ��MFC���п�
# define THREAD_CALL                WINAPI
# define THREAD_HANDLE              HANDLE
# define THREAD_RET_T               long
# define CREATE_THREAD_FAILED       (0L)
# define CREATE_THREAD_ERROR        GetLastError()
# define CREATE_THREAD(_S,_F,_P)    ((Handle)CreateThread(0,_S,(long (WINAPI *)(void *))_F,(void *)_P,0,0))
# define EXIT_THREAD                ExitThread(0)
# define CLOSE_HANDLE(x)            CloseHandle(x)
# define THREAD_RETURN(x)           return(x)
#endif

#if !defined( PLUGINS_CALL )
#define PLUGINS_CALL		__stdcall
#endif


#endif
