#ifndef _S_JC_PUBLIC_H_
#define _S_JC_PUBLIC_H_

#include <map>
#include <string>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>    
#include <assert.h>    
#include <stdarg.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include <time.h>
#include <sys/timeb.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <limits.h>


#ifdef _MSC_VER
  #include <windows.h>
#endif
#ifndef _MSC_VER
  #include <sys/time.h>
  typedef struct timeval time_stru;
#else
  typedef struct _time_stru
  {
	int tv_sec;
	int tv_usec;
  }time_stru;
#ifdef __cplusplus
extern "C" { 
#endif
	int gettimeofday(time_stru *tv, void *);
#ifdef __cplusplus
}
#endif	  
#endif
double diffTimeVal(const time_stru *tv);
#ifndef FALSE
  #define FALSE               0
#endif

#ifndef TRUE
  #define TRUE                1
#endif

#define FCMP 	  0.00001       /*double 的精度，用来比较*/
#define DCMP    0.000000001   /*double 的精度，用来比较一些数值比较小的数据*/
/*add by lvxin08772 20140108 */
#define DCMPEx    0.00000000001 /*徐为雄需要精度为10,特殊处理*/
/*add by lvxin08772*/
#ifndef MAXINT
#define MAXINT  2147483647
#endif

#ifndef MAX
#define MAX(a,b)                ((a)<(b) ? (b) : (a))
#endif

#ifndef MIN
#define MIN(a,b)                ((a)>(b) ? (b) : (a))
#endif

#define ABS(x)                  ((x)>=0 ? (x) : -(x))
#define FEQ(X,Y)                (fabs((X) - (Y)) < ( (X)>10 ? FCMP:DCMP) ? 1 : 0)   /*等于*/
#define FBG(X,Y)                ((X) - (Y) > ( (X)>10 ? FCMP:DCMP) ? 1 : 0)         /*大于*/
#define FLS(X,Y)                FBG(Y,X)                                            /*小于*/

#define MAX_FILENAME_LEN 255
#define MAX_LINE_LEN 1228800
/*#define PACKAGE_MAX_LEN 2048000*/
#define PACKAGE_MAX_LEN 3145728
#define MAX_LOGFILE_SIZE 100 /*日志文件最大大小，单位为M*/
/*add by kongdl for check memory*/
#define MAX_LINE_LEN_512B  512
#define MAX_LINE_LEN_1K  1024
#define MAX_LINE_LEN_10K  10240
#define MAX_LINE_LEN_100K  102400
#define MAX_LINE_LEN_1M  1048576
/*add by kongdl*/


#define STRCHR(SOURCE,DEST) (DEST=='\0'?NULL:strchr(SOURCE,DEST))
#define STRSTR(SOURCE,DEST) (DEST[0]=='\0'?NULL:strstr(SOURCE,DEST))

#ifndef TPNOBLOCK
  #define TPNOBLOCK	0x00000001	/* non-blocking send/rcv */
  #define TPSIGRSTRT	0x00000002	/* restart rcv on interrupt */
  #define TPNOREPLY	0x00000004	/* no reply expected */
  #define TPNOTRAN	0x00000008	/* not sent in transaction mode */
  #define TPTRAN		0x00000010	/* sent in transaction mode */
  #define TPNOTIME	0x00000020	/* no timeout */
  #define TPABSOLUTE	0x00000040	/* absolute value on tmsetprio */
  #define TPGETANY	0x00000080	/* get any valid reply */
  #define TPNOCHANGE	0x00000100	/* force incoming buffer to match */
  #define RESERVED_BIT1	0x00000200	/* reserved for future use */
  #define TPCONV		0x00000400	/* conversational service */
  #define TPSENDONLY	0x00000800	/* send-only mode */
  #define TPRECVONLY	0x00001000	/* recv-only mode */
  #define TPACK		0x00002000	
#endif

using namespace std;

extern char GTmpStr[10240];  /*用于在一些函数中，需要返回字符串，通过此变量以替代函数中的静态变量*/
extern int GLogPid;
extern char GLogFile[MAX_FILENAME_LEN];
extern char sServerName[100];
extern char GEncryptKey[30];

#ifdef __cplusplus
extern "C" { 
#endif

char *GetString(char *source,char *left,char *right);
char *GetToken(char *s1,char *s2);
void StrSplit(char *src, char* dst, int splitLen);

double Precision(double f,int p,int mode);

int WrtLog(int iLevel, char * format, ...);
double GetTickCount();     
int CreateDir(const char *dir);
/*
示例：
  time_stru dwStart={0};
  gettimeofday(&dwStart,NULL);
  hsWriteLog_UFT(1,"end of parse package:%ld",UDiffTime(dwStart));
*/
unsigned long UDiffTime(time_stru dwStart);
double DiffTime(struct timeb t);
int hsdate_diff(int in_begin_hsdate, int in_end_hsdate, int *out_days);

char *GetTime();
char *IIF(int Condition,char *s1,char *s2);

time_t MakeTime(int iYear,int iMonth,int iDay);

#if defined(_MSC_VER)
int GetFileDate(char *FileName);
#endif

void HSSleep(int msec);

int GetColString(char* sSrc,char* sDes,char ch ,int num);
int GetColInteger(char * sstr, int *iDes, char ch, int num);
int GetColDouble(char * sstr, double *enDes, char ch, int num);
int IsNull(char *str);

void hs_strcpyD(char *dest, const char *src,char *defaultValue);

char * GetDate();
int adddate(const int isourcedate,const int idatediff);
int addmonths(const int isourcedate,const int imonthdiff);

long Getfilesize(char * sFileName );
int Changefilename(char *sFileName);

char *addslashes(const char *str);
int escape_sql(const char* src, char* dst, int dst_len);

/*ini读写函数*/
int read_profile_string( const char *section_pass, const char *key_pass_ini,char *value_pass, int size,const char *default_value, const char *file_pass);
int read_profile_int( const char *section_pass, const char *key_pass_ini,int default_value, const char *file_pass);
int write_profile_string( const char *section_pass, const char *key_pass_ini,const char *value_pass, const char *file_pass);

const char* GetOraPwd(const char* szLogicName);
void AddHsdbOraInfo(const char* szLogicName, const char* passwd);
#ifdef __cplusplus
  }
#endif
#endif
