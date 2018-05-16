/**Linux/Unix平台下posix标准的环境配置头文件定义
源程序名称: config_posix.h
软件著作权: 恒生电子股份有限公司 版权所有
系统名称: 公用技术平台
模块名称: 跨平台适配层 
功能说明: 此文件被config_env.h所包含，不应直接包括此头文件。
	      
相关文档: 
作者:
审核: (可选的)
	
修改记录
修改日期:
修改人员:
修改说明:
*******************************************************************/

#if !defined _CONFIG_POSIX_INC_ && !defined _WIN32
#define _CONFIG_POSIX_INC_

#include <pthread.h>
#include <semaphore.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <sys/timeb.h>
#include <sys/ioctl.h>
#include <strings.h>
#include <sys/socket.h>
#include <dlfcn.h>
#include <netinet/in.h>
#include <inttypes.h>
#include <arpa/inet.h>
#include <stropts.h>
#include <errno.h>
#include <dirent.h>
#include <fnmatch.h>		// liangyong 081022 add

#if !defined(OS_UNIX)
#define OS_UNIX
#endif
///对hp aCC编译器
#if defined(__HP_aCC)
///对于gcc 编译器
#elif defined(__GNUC__)
#include <ctype.h>
#endif

///平台相关
///针对hpunix
#if defined(__hpux)
#include <poll.h>
#define	SEM_FAILED		((sem_t *)(-1))
///针对redhat linux
#elif defined(__linux__)
//#define USE_IPX			//	LINUX下一般不支持IPX协议
#include <sys/poll.h>
#include <netipx/ipx.h>
///针对solaris
#elif defined(sun)
#include <poll.h>
#endif

#define __stdcall

///与socket相关宏定义，与windows保持一致
//@{
	#define closesocket				close

	#ifndef SOCKET
	#define SOCKET					int
	#endif

	#ifndef INVALID_SOCKET
	#define INVALID_SOCKET			(SOCKET)(~0)
	#endif

	#ifndef SOCKET_ERROR
	#define SOCKET_ERROR			(-1)
	#endif

	#ifndef INADDR_NONE
	#define INADDR_NONE				(0xFFFFFFFFL)
	#endif

	#ifndef INADDR_ANY
	#define INADDR_ANY				((uint32)0x00000000L)
	#endif
	
	#ifndef SOCKET_LEN_TYPE
		#if defined(__hpux)				//	HP UXIX
			#define SOCKET_LEN_TYPE		int
		#elif defined(__linux__)		//	LINUX
			#define SOCKET_LEN_TYPE		socklen_t
		#elif defined(sun)				//	SUN
			#define SOCKET_LEN_TYPE		socklen_t
		#elif defined(_AIX)
			#define SOCKET_LEN_TYPE		unsigned long
		#endif
	#endif

	#define SD_RECEIVE      0x00				///停止接收
	#define SD_SEND         0x01				///停止发送
	#define SD_BOTH         0x02				///双向停止
//@}

///定义linux/unix下目录分隔符
#define DIR_SLASH			'/'
///定义linux/unix下目录路径字符串的最大长度
#define MAX_PATH			256

//typedef unsigned int  DWORD;        ///sizeof(DWORD) = 4
typedef long unsigned int DWORD;			/// 20090105 梁勇 修改

//#define OS_UNIX

static const int INFINITE = (-1);
typedef int     BOOL;


#define INVALID_HANDLE_VALUE    -1


///动态库文件后缀
#define LIB_POSTFIX		".so"
///动态库文件前缀
#define LIB_PREFIX		"lib"

///清除屏幕的系统调用
#define CLEAR_CMD			"clear"

#define SEM_NAME_LEN			255

#ifndef MAXLONG
#define MAXLONG ((1 << (sizeof(long) * 8 - 1)) - 1)			//~(1 << (sizeof(long) * 8 - 1))
#endif

#ifndef MAXULONG
#define MAXULONG ((1 << (sizeof(unsigned long) * 8)) - 1)
#endif

///与windows同义，表明创建的对象已经被传创建
#define ERROR_ALREADY_EXISTS        183L

#if !defined( PLUGINS_CALL )
#define PLUGINS_CALL	
#endif

#endif
