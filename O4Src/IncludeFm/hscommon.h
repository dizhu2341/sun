/*
 * Headfile : hscommon.h
 * Author   : 周伟明
 * Date     : 2006-09-24
 * Notes    : 公共对象定义(例如结构、类定义等)
 *
 */
#ifndef _HSCOMMON_H
#define _HSCOMMON_H

/*================== 函数返回类型====================================================================*/
#ifndef PLATFORM_EXPORT
#ifdef  OS_UNIX
  #define PLATFORM_EXPORT
#else
  #ifdef PLATFORM_UNIX
    #define PLATFORM_EXPORT
  #else
    #define PLATFORM_EXPORT     __declspec(dllexport)
  #endif
#endif
#endif

/*================== 用户令牌 ======================================================================*/
typedef struct tagUserToken
{
	char sUserID[12];
	char cTokenType;
}USER_TOKEN,*LPUSER_TOKEN;


#endif /* _HSCOMMON_H */
