/*
 * Headfile : hscommon.h
 * Author   : ��ΰ��
 * Date     : 2006-09-24
 * Notes    : ����������(����ṹ���ඨ���)
 *
 */
#ifndef _HSCOMMON_H
#define _HSCOMMON_H

/*================== ������������====================================================================*/
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

/*================== �û����� ======================================================================*/
typedef struct tagUserToken
{
	char sUserID[12];
	char cTokenType;
}USER_TOKEN,*LPUSER_TOKEN;


#endif /* _HSCOMMON_H */
