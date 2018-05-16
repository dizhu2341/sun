/******************************************************************************
 *
 *              基金投资管理系统 O3.0 
 *
 *       Copyright (C) 2004, 杭州恒生电子股份有限公司 基金事业部
 *
 *               All Rights Reserved.
 *
 * ===========================================================================
 *
 * 文 件 名：spub.c
 * 模块名称：公用c函数
 * 功能说明：
 * 作  者：沈志伟
 * 创建日期：2005.08
 * 版 本 号：
 * 修改历史：
 *
 * ===========================================================================
 *
 * N O T E:
 *       1. Platform: UNIX/Windows
 *
******************************************************************************/

#include <IncludeFm/s_jc_public.h>

int hsSnprintf(char * buf, size_t buflen, const char * format, ...);
char * hsStrncpy(char *dest, const char *src, size_t num);
char * hsStrcat(char * dest, const char * src, size_t destlen);

/*ini文件类定义*/
#define MAX_FILE_SIZE (1024*16)
#define LEFT_BRACE '['
#define RIGHT_BRACE ']'
#define IS_SPACE(c)  (c == ' '|| c == '\t'||c=='\n'|| c=='\r' )
/**************/

char GTmpStr[10240];            /*用于在一些函数中，需要返回字符串，通过此变量以替代函数中的静态变量*/
char GLogFile[MAX_FILENAME_LEN]="";     /*日志输出文件，各服务可修改成服务自己的日志文件*/
int GLogPid;                  /*进程号*/
char sServerName[100]="\0";
char GEncryptKey[30];
map<string, string> GMapOraPasswd;

const double date_delta = 693594;
int day_table_all[2][12] = 
{
	{31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
	{31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}
};

int WrtLog(int iLevel, char * format, ...)
{
	char sbuff[MAX_LINE_LEN];
  char sTmpStr[100] = "";
  char sEnter[2]="";

  struct tm t;
  time_t now;

  va_list *ap;
  FILE *fh;
  sbuff[0]='\0';

  if ((fh=fopen("./log/jclog.log", "a+")) == NULL) 
  {
    perror("Create or Open LogFile Error! \n");
    return -1;
  }
  else
  {
    ap=(va_list *)malloc(sizeof(va_list));
    if(ap!= NULL)
    {
      va_start(*ap, format);
      #ifdef WIN32
        _vsnprintf(sbuff, MAX_LINE_LEN, format, *ap);
      #else
        vsnprintf(sbuff, MAX_LINE_LEN, format, *ap);
      #endif
      va_end(*ap);
      free(ap);
    }
    if (sbuff[strlen(sbuff)-1] != '\n')
      strncpy(sEnter,"\n",sizeof(sEnter));

    time(&now);
    t = *localtime(&now);

    snprintf(sTmpStr,sizeof(sTmpStr),"%02d%02d-%02d:%02d:%02d",t.tm_mon+1,t.tm_mday,t.tm_hour,t.tm_min,t.tm_sec);
    /*使用恒生中间件不能调GetTime这个函数，否则程序会崩溃掉*/
    fprintf(fh, "%s %s%s",sTmpStr, sbuff,sEnter); 
    fclose(fh);
  }
  return 0;
}

/*************************************************
获取当前tick，精确到毫秒级
**************************************************/
double GetTickCount()
{
  struct timeb t;
  ftime(&t);
  return (double)(1000.0*t.time + t.millitm);
}

/***************************************************************************
函数名称: CreateDir
函数功能: 创建多级目录. 如创建"a/b/c"目录。
输入参数: dir 目录。可以为"a/b/c" 、"a/b/c/"、"/a/b/c" 、"/a/b/c/"
返回值：-1 创建失败 0 创建成功
***************************************************************************/
int CreateDir(const char *dir)
{
    char DirName[1024];
    strcpy(DirName, dir);
    int len = strlen(DirName);
    if(DirName[len - 1] != '/')
    {
       strcat(DirName, "/");
    }
    len = strlen(DirName);
	
    int i = 1;
    for(i = 1; i < len; i++)
    {
        if(DirName[i] == '/')
        {
            DirName[i] = '\0';
            if(access(DirName, NULL) != 0)
            {
                if(mkdir(DirName, 0755) == -1)
                {
					perror("mkdir error");
                    return   -1;
                }
            }
            DirName[i]  = '/';
        }
    }
    return   0;
}

/***************************************************************************
函数名称:StrSplit
函数功能: 从src中拷贝前splitLen个字符到dst中,如果刚好是中文，则截取splitLen， 支持带中文的字符串
		src中保存的为剩下的字符串
输入参数: src 源字符串， dst目标存放数组, splitLen 分割的长度.
返回值无：
***************************************************************************/
void StrSplit(char *src, char* dst, int splitLen)
{
	unsigned int i = 0, srcLen = 0, dstLen = splitLen;
	int num = 0;       
	srcLen = (strlen(src) > dstLen ? dstLen : strlen(src));
	for (i=0; i<srcLen; ++i)
	{
		if (src[i] < 0)
			num ++;
		dst[i] = src[i];
	}
	if (num % 2 == 1)
	{
		dst[i-1] = '\0';
		i--;
	}
	strcpy(src, src+i);
}

/***************************************************************************
函数名称:StrPos
函数功能:返回s2在s1中的位置，从1开始
输入参数:
  ...
输出参数:无
返 回 值:第几位
***************************************************************************/
int StrPos(char *s1,char *s2)
{
  char *s;
  s=strstr(s1,s2);
  if ( (s==NULL) || (s2[0]=='\0') )
    return 0;
  else
    return (s-s1)+1;
}

/***************************************************************************
函数名称:Trim
函数功能:清两边空格
输入参数:
  ...
输出参数:处理后的字符串
返 回 值:处理后的字符串
***************************************************************************/
char *Trim(char *str)
{
	char* start=NULL /*,* mid=NULL, *end=NULL*/;
	int i, len;
	if(str==NULL) return str;
	start=str;
	while( IS_SPACE(*start) ) start++;
  len = (int)strlen(start); 
  if(len == 0)
  {
    if (strlen(str)>0)
  	  str[0]='\0';
    return str;
  }
  for (i = len - 1; i >= 0; i--)
  {
    if ( !IS_SPACE(start[i]) ) 
      break;
  }
  start[i+1]='\0';
  if (str!=start)
    strcpy(str,start);
  return str;
}

/*
字符串拷贝，如果源字符串为NULL或者""，目标字符串赋默认值
*/
void hs_strcpyD(char *dest, const char *src,char *defaultValue)
{
	if (src== NULL || strcmp(src, "") == 0)
	{
		hsStrncpy(dest, defaultValue, sizeof(dest));
	}
	else
	{
		hsStrncpy(dest,src , sizeof(dest));
	}
}

/**
函数名称:GetString
函数功能:返回字符串source中，在left和right之间的串
输入参数:
**/
char *GetString(char *source,char *left,char *right)
{
  int i,j;

  i=StrPos(source,left);
  if (i==0)
  {
    GTmpStr[0]='\0';
    return GTmpStr;
  }

  hsStrncpy(GTmpStr,source+i-1+strlen(left),sizeof(GTmpStr));
  j=StrPos(GTmpStr,right);
  if (j==0)
    GTmpStr[0]='\0';
  else
    GTmpStr[j-1]='\0';
  return GTmpStr;
}


/***************************************************************************
函数名称:GetToken
函数功能:取字符串。取s1中，在s2子串前的字符串,并返回。s1为剩余部分
输入参数:
  ...
输出参数:取得的子串
返 回 值:取得的子串
***************************************************************************/
char *GetToken(char *s1,char *s2)
{
  char *str1;

  str1=strstr(s1,s2);
  if (str1==NULL)
  {
    hsStrncpy(GTmpStr,s1,sizeof(GTmpStr));
    s1[0]='\0';
  }
  else
  {
    s1[str1-s1]='\0';
    hsStrncpy(GTmpStr,s1,sizeof(GTmpStr));
    strcpy(s1,str1+strlen(s2));
  }
  return GTmpStr;
}

/***************************************************************************
函数名称:Precision
函数功能:精确小数。
输入参数:mode = 0 四舍五入
1 截位
2 进位
输出参数:取精确后的小数
返 回 值:取精确后的小数
***************************************************************************/
double Precision(double f,int p,int mode)
{
	char str[30];
	int i,n;
	double fRtn;
	if(FEQ(f,0.0))
		return 0.0;
	switch(mode){
    case 0: /*四舍五入*/
		/*2010 处理由于double精度引起的进位问题，FCMP、DCMP用作浮点数比较的，除10为了处理后的值，在浮点数比较时返回结果也是相等的*/
		if ( f>0 )
		  f=f+DCMP/10;
		else if(f<0)
		  f=f-DCMP/10;
		for(i=0,n=1;i<p;i++)
			n *= 10;
		fRtn = (floor(f*n+0.5))/n;
		break;
    case 1: /*截位*/
		/*2010 处理由于double精度引起的进位问题，FCMP、DCMP用作浮点数比较的，除10为了处理后的值，在浮点数比较时返回结果也是相等的*/
		if ( f>0 )
			f=(f>10 ? (f+FCMP/10):(f+DCMP/10));
		else
			f=(f<-10 ? (f-FCMP/10):(f-DCMP/10));
		for(i=0,n=1;i<p;i++)
			n *= 10;
		hsSnprintf(str,sizeof(str),"%20.4lf\n",f*n);
		str[16]='\0';
		fRtn = atof(str)/n;
		break;  
	case 2:  /*进位*/
		/*2010 处理由于double精度引起的进位问题，FCMP、DCMP用作浮点数比较的，除10为了处理后的值，在浮点数比较时返回结果也是相等的*/
		if ( f>0 )
			f=(f>10 ? (f-FCMP/10):(f-DCMP/10));
		else
			f=(f<-10 ? (f+FCMP/10):(f+DCMP/10));
		for(i=0,n=1;i<p;i++)
			n *= 10;
		fRtn = (ceil(f*n))/n;
		break;
	default:
		fRtn = f;
		break;
	}
	return fRtn;
}
/*功能基本同DiffTime 返回微妙*/
unsigned long UDiffTime(time_stru dwStart)
{
  unsigned long dd;
  struct timeval dwEnd;
  gettimeofday((time_stru *)&dwEnd,NULL);
  
  dd = 1000000*(dwEnd.tv_sec-dwStart.tv_sec)+(dwEnd.tv_usec-dwStart.tv_usec);  
  
  return dd;
}
/*返回日期型变量，与当前机器时间的间隔，单位为秒，精确到毫秒。
   一般用于性能方面的日志记录
   目前只能适用于开始结束日期都在2038年以前
   若超出2038年需要适用下面的函数*/
double DiffTime(struct timeb t)
{
  double dd;
  struct timeb t1;
  ftime(&t1);
  dd=(t1.time-t.time)+(t1.millitm*1.0-t.millitm*1.0)/1000.0;
  return dd;
}

/*判断是否为闰年
  返回值：1-闰年；0-平年*/
int is_leap_year(int in_year)
{
  if ((in_year % 4 == 0) && (in_year % 100 != 0) || (in_year % 400 == 0))
  	return 1;
 	else
 		return 0;
}

/*把日期转换成天数
  返回值：0-成功；1-失败*/
int encode_date(int in_year, int in_month, int in_day, int *out_datetime)
{
	int is_leap = is_leap_year(in_year);
	int *day_table = day_table_all[is_leap];
	int i;
	if ((in_year >= 1) && (in_year <= 9999) && (in_month >= 1) && (in_month <= 12) &&
    (in_day >= 1) && (in_day <= day_table[in_month - 1]))
	{
      *out_datetime = 0;
  	  for (i = 0; i < in_month - 1; i++)
  	    *out_datetime += day_table[i];
  	
      i = in_year - 1;
      *out_datetime += i * 365 + i / 4 - i / 100 + i / 400 + in_day;
  	  return 0;
	}
 	else
 	  return 1;
}

int split_hsdate(int in_hsdate, int *out_year, int *out_month, int *out_day)
{
	*out_year = in_hsdate / 10000;
	*out_month = in_hsdate / 100 % 100;
	*out_day = in_hsdate % 100;
	return 0;
}

int encode_hsdate(int in_hsdate, int *out_datetime)
{
	int year, month, day;
	split_hsdate(in_hsdate, &year, &month, &day);
	return encode_date(year, month, day, out_datetime);
}

/*计算日期间隔
	返回值：0-成功；1-开始日期错误；2-结束日期错误
	开始或结束日期在2038年以后的需使用该函数
*/
int hsdate_diff(int in_begin_hsdate, int in_end_hsdate, int *out_days)
{
	int begin_days, end_days;
	
	if (encode_hsdate(in_begin_hsdate, &begin_days) == 1) return 1;
	if (encode_hsdate(in_end_hsdate, &end_days) == 1) return 2;

	*out_days = end_days - begin_days;
	return 0;
}


/***************************************************************************
函数名称:GetTime
函数功能:返回当前日期时间的字符串,格式为：yyyy-mm-dd hh:mi:ss
输入参数:
输出参数:
返 回 值:
***************************************************************************/
char *GetTime()
{
  struct tm t;
  time_t now;
  int year;

  time(&now);
  t = *localtime(&now);
  year=t.tm_year;
  if (year<50)
    year+=2000;
  else
    year+=1900;
  hsSnprintf(GTmpStr,sizeof(GTmpStr),"%04d-%02d-%02d %02d:%02d:%02d",year,t.tm_mon+1,t.tm_mday,t.tm_hour,t.tm_min,t.tm_sec);

  return GTmpStr;
}

/***************************************************************************
函数名称:取系统日期
函数功能:返回当前日期的数字,格式为：yyyymmdd
输入参数:
输出参数:
返 回 值:
***************************************************************************/
char * GetDate()
{
  struct tm t;
  time_t now;
  int year;

  time(&now);
  t = *localtime(&now);
  year=t.tm_year;
  if (year<50)
    year+=2000;
  else
    year+=1900;
  hsSnprintf(GTmpStr,sizeof(GTmpStr),"%04d%02d%02d",year,t.tm_mon+1,t.tm_mday);
  return GTmpStr;
}

/*返回isourcedate后第idatediff 天的时间*/
int adddate(const int isourcedate,const int idatediff)
{
  int year;
  struct tm t;
  time_t addt;

  int years,months,days,tempdate ;
  years = isourcedate / 10000;
  tempdate = isourcedate % 10000;
  months = tempdate / 100;
  days = tempdate % 100;

  addt = MakeTime( years, months, days ) + idatediff * 24 * 3600;
  t = *localtime( &addt  );
  year=t.tm_year;
  if (year<50)
    year+=2000;
  else
    year+=1900;

  return  year*10000 + ( t.tm_mon + 1 ) * 100 + t.tm_mday ;
}

/*判断该年是否闰年*/
int isleapyear(const int iyear)
{  	
  if ((iyear % 100) == 0)  
  {
     if ( (iyear % 400) == 0 )
	   return 1;
	 else
	   return 0;
  }
  else
  {
    if ( (iyear % 4) == 0 ) 
	  return 1;
	else
	  return 0;
  }
}

/*判断是否某月的最后一天*/
int ismonthlastday(const int isourcedate)
{
  int years,months,days,tempdate ;
  years = isourcedate / 10000;
  tempdate = isourcedate % 10000;
  months = tempdate / 100;
  days = tempdate % 100;

  if ( (years < 1000)|| (years > 9999) )
  	return -1;

  if ( (months > 12)||(months < 1) )
  	return -1;
  
  if ( (days > 31)||(days < 1) )
    return -1;
  else if ( days <= 27 )
    return 0;
  else if ( days == 28 )
  {
    if (months != 2)
      return 0;
    else
    {
      if (isleapyear(years))
        return 0;
      else
        return 1;
    }
  }
  else if ( days == 29 )
  {
    if (months != 2)
      return 0 ;
    else
    {
      if (isleapyear(years))
        return 1;
      else
        return -1;
    }
  }
  else if ( days == 30 )
  {
    if (months == 2)
	  return -1;
	else if ((months == 4) || (months == 6) || (months == 9) || (months == 11))
	  return 1;
	else
	  return 0;
  }
  else if ( days == 31 )
  {
    if ((months == 2) || (months == 4) || (months == 6) || (months == 9) || (months == 11))
      return -1;
    else
      return 1;
  }
  else
    return -1;
}

/*获取该月的最后一天*/
int getmonthlastday(const int iyear,const int imonth)
{
  if ( (imonth > 12)||(imonth < 1) )
	return -1;

  if (imonth == 2)
  {
    if ( isleapyear(iyear) )
      return 29;
    else
      return 28;
  }
  else if ((imonth == 4) || (imonth== 6) || (imonth == 9) || (imonth == 11))
	return 30;
  else
	return 31;
}

/*返回isourcedate后第imonthdiff 月的时间*/
int addmonths(const int isourcedate,const int imonthdiff)
{
  int years,months,days,tempdate ;
  years = isourcedate / 10000;
  tempdate = isourcedate % 10000;
  months = tempdate / 100;
  days = tempdate % 100;

  months += imonthdiff;
  years = years + months/12;
  months = months % 12;
  if ( months < 1 )
  {
    months += 12;
	years--;
  }
  if ( ismonthlastday(isourcedate) == -1 )
  {
    return -1;
  }
  else if ( ismonthlastday(isourcedate) == 1 )
  {
     days = getmonthlastday( years, months);
  }
  else
  {
     if (days > getmonthlastday(years, months))
       days = getmonthlastday(years, months);
  }
  return  years*10000 + months * 100 + days ;  
}


/*如果Condition为真，返回字符串s1,否则返回s2*/
char *IIF(int Condition,char *s1,char *s2)
{
  if (Condition)
    return s1;
  else
    return s2;
}

/*判断str字符串，是否为空，只有空格也算空*/
int IsNull(char *str)
{
  char *pTmpStr;
  pTmpStr = (char *) malloc(strlen(str));
  if(pTmpStr == NULL)
    return 1;
  hsStrncpy(pTmpStr,str,strlen(str));
  Trim(pTmpStr);
  if (pTmpStr[0] == '\0') 
  {
    free(pTmpStr); 
    /*pTmpStr = NULL;*/
    return 1;
  }
  free(pTmpStr); 
  /*pTmpStr = NULL;*/
  return 0;
}

/*返回一年中，有多少天*/
int GetYearDays(char *sYear)
{
  int nYear,nDays = 365;
  nYear = atoi(sYear);
  if((((nYear % 400) == 0)) ||(((nYear % 4) == 0)&&((nYear % 100) != 0)))
    nDays = 366;
  
  return nDays; 
}

/*根据年iYear、月iMonth、iDay，返回对应的时间类型*/
time_t MakeTime(int iYear,int iMonth,int iDay)
{
  struct tm  timeptr;
  time_t  time_now;

  memset(&timeptr, 0 , sizeof(struct tm));
  timeptr.tm_year = iYear - 1900;
  timeptr.tm_mon = iMonth - 1;
  timeptr.tm_mday = iDay;
  timeptr.tm_hour = 12;
  timeptr.tm_min = 0;
  timeptr.tm_sec = 0;
  
  time_now = mktime(&timeptr);
  return time_now;
}




/*获取文件大小*/
long Getfilesize(char * sFileName )
{
  struct stat f_stat;
  if( stat( sFileName, &f_stat ) == -1 )
    return -1;

  return (long)f_stat.st_size;
}

/*判断文件大小是否达到最大限制，如果达到最大限制，将其改名，名字后缀为系统日期*/
int Changefilename(char *sFileName)
{  
  char sNewFile[200]="";
  int  iRet=0, i=1;  
  if(Getfilesize(sFileName)> (MAX_LOGFILE_SIZE*1024*1024) )/*大于最大大小限制后，改名*/
  {
    hsSnprintf(sNewFile,sizeof(sNewFile),"%s.%s_%d",sFileName,GetDate(), i);
    /*判断新文件是否存在，如果文件存在，则重新生成文件名，并且控制，当天文件名不能超过10000个*/
    #ifdef WIN32
       while(( (_access(sNewFile,0))!= -1 )&&(i<10000))
       {
         i++;
         hsSnprintf(sNewFile,sizeof(sNewFile),"%s.%s_%d",sFileName,GetDate(), i);
       }
    #else
       while(( (access(sNewFile,0))!= -1 )&&(i<10000))
       {
         i++;
         hsSnprintf(sNewFile,sizeof(sNewFile),"%s.%s_%d",sFileName,GetDate(), i);
       }
    #endif
    iRet=rename(sFileName,sNewFile);
    if(iRet!=0)
    {
      perror("Rename File Name Error!\n");
      return -1;
    }
  }
  return 0;
}



/*
  如果是微软windows环境,该函数取得指定文件的最后修改时间
*/
#if defined(_MSC_VER)
int GetFileDate(char *FileName)
{
  HANDLE fh;
  FILETIME createTime, accessTime, writeTime;
  SYSTEMTIME sysTime;
  fh = CreateFile(FileName, GENERIC_READ, FILE_SHARE_READ|FILE_SHARE_WRITE,
               NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
  if ((fh != INVALID_HANDLE_VALUE) && 
    (GetFileTime(fh, &createTime, &accessTime, &writeTime)) &&
    (FileTimeToSystemTime(&createTime, &sysTime)) )
  {
    CloseHandle(fh);
    return sysTime.wYear*10000 + sysTime.wMonth*100 + sysTime.wDay;
  }
  else
  {
    CloseHandle(fh);
    return -1;
  }
}
#endif
/*
  HSSleep函数实现程序暂停指定长度时间功能,参数为微秒级
*/
void HSSleep(int msec)
{
  #if defined(_MSC_VER)
  Sleep((unsigned long)msec);
  #else
  struct timeval timeout;
  timeout.tv_sec=msec/1000;
  timeout.tv_usec = (msec%1000)*1000;
  select(0, NULL, NULL, NULL, &timeout);
  #endif
}

/*
  GetColString: 取得指定字符串中按照指定分隔符分隔得指定部分,按字符串返回
  sSrc: 源串
  sDes: 返回值,目标串
  ch : 分隔字符
  num: 取第几部分
*/
int GetColString(char* sSrc,char* sDes,char ch ,int num)
{
  char *pCurr = sSrc;
  char *pNext;
  int i=0;
  for(i=0; i<num; i++) 
  {
    if ((pCurr = strchr(pCurr,ch))==NULL) 
    {
      break;
    }
    if ( pCurr[0] == ch )
    {
      pCurr++;
    }
  }

  if (!pCurr) 
  {
    *sDes = 0;
  }
  else 
  {
    pNext = strchr(pCurr,ch);
    if (!pNext)
    {
      strcpy(sDes, pCurr);
    }
    else 
    {
      strncpy(sDes, pCurr, (size_t)(pNext - pCurr));
      sDes[pNext - pCurr] = 0;
    }
  }

  if(strlen(sDes)||(i==num && strchr(sSrc,ch)!=NULL))
    return 0;
  else
    return -2;
}

/*
  GetColString: 取得指定字符串中按照指定分隔符分隔得指定部分,按整数返回
  sSrc: 源串
  iDes: 返回值,整型
  ch : 分隔字符
  num: 取第几部分
*/
int GetColInteger(char * sstr, int *iDes, char ch, int num)
{
  char buff[100];
  unsigned int i=0;

  memset(buff, 0, 100);
  if (GetColString(sstr, buff, ch, num)==0)
  {
    for (i=0; i< strlen(buff); i++)
    {
      if ((buff[i] >= '0') && (buff[i] <= '9'))
        continue;
      else if ( (i==0) && ((buff[i] == '-')||(buff[i] == '+')) ) 
        continue;
      else
        return -2;
    }
    *iDes = atoi(buff);
    if (*iDes == INT_MAX || *iDes == INT_MIN)
    {
      return -2;
    }
    return 0;
  }
  else
  {
    return -2;
  }
}

/*
  GetColString: 取得指定字符串中按照指定分隔符分隔得指定部分,按浮点值返回
  sSrc: 源串
  enDes: 返回值,实型
  ch : 分隔字符
  num: 取第几部分
*/
int GetColDouble(char * sstr, double *enDes, char ch, int num)
{
  char buff[100];
  unsigned int i=0;
  int ipointcnt=0;

  memset(buff, 0, 100);
  if (GetColString(sstr, buff, ch, num)==0)
  {
    for (i=0; i< strlen(buff); i++)
    {
      if (buff[i] == '.')
      {
        ipointcnt++;
      }
      else if ((buff[i] >= '0') && (buff[i] <= '9'))
        continue;
      else if ( (i==0) && ((buff[i] == '-') || (buff[i] == '+')))
        continue;
      else
        return -2;    
    }

    if (ipointcnt > 1) 
    {
      return -2;
    }
    *enDes = atof(buff);

    return 0;
  }
  else
  {
    return -2;
  }
}

/*字符串字母小写改大写*/
void strltou(char *s)
{
  unsigned int i;
  for(i=0;i<strlen(s);i++) 
  {
    if ( s[i] >96 && s[i] < 123 ) 
      s[i] = (char)toupper(s[i]); 
  }

  return ;
}

/******************************以下 ini读写类 开始***********************************/
/**
 * @file
 * @brief initialization file read and write API implementation
 * @author Deng Yangjun
 * @date 2007-1-9
 * @version 0.1
 */

static int load_ini_file(const char *file, char *buf,int *file_size)
{
	FILE *in = NULL;
	int i=0;
	*file_size =0;
 
	assert(file !=NULL);
	assert(buf !=NULL);
	
  if (!file)
    return 0;
  if (!buf)
    return 0;
  in = fopen(file,"r");
  if( NULL == in) {
		return 0;
	}
  buf[i]=(char)fgetc(in);
	/*load initialization file*/
	while( (int) buf[i]!= EOF){
		i++;
		assert( i < MAX_FILE_SIZE); 
        if(i < MAX_FILE_SIZE-1){
            buf[i]=(char)fgetc(in);
        }else{
           break;
        }
	}
	buf[i]='\0';
	*file_size = i;

	fclose(in);
	return 1;
}
static int isnewline(char c)
{
	return ('\n' == c ||  '\r' == c )? 1 : 0;
}
static int isend(char c)
{
	return '\0'==c? 1 : 0;
}
static int isleftbarce(char c)
{
	return LEFT_BRACE == c? 1 : 0;
}
static int isrightbrace(char c )
{
	return RIGHT_BRACE == c? 1 : 0;
}
static int parse_file(const char *section, const char *key, const char *buf,int *sec_s,int *sec_e,
					  int *key_s,int *key_e, int *value_s, int *value_e)
{
	const char *p = buf;
	int i=0;
	char sKey[256]="";
  char sSection[256]="";
	assert(buf!=NULL);
	assert(section != NULL);
	assert(key != NULL);

	*sec_e = *sec_s = *key_e = *key_s = *value_s = *value_e = -1;

	while( !isend(p[i]) ) {
		/*find the section*/
		if( ( 0==i ||  isnewline(p[i-1]) ) && isleftbarce(p[i]) )
		{
			int section_start=i+1;

			/*find the ']'*/
			do {
				i++;
			} while( !isrightbrace(p[i]) && !isend(p[i]));
			memset(sSection,0,sizeof(sSection));
      strncpy(sSection,p+section_start,i-section_start);
      Trim(sSection); 
			if(section != NULL && 0 == strcmp(sSection,section)) {
				int newline_start=0;

				i++;

				/*Skip over space char after ']'*/
				while(isspace(p[i])) {
					i++;
				}

				/*find the section*/
				*sec_s = section_start;
				*sec_e = i;

				while( ! (isnewline(p[i-1]) && isleftbarce(p[i])) 
				&& !isend(p[i]) ) {
					int j=0;
					/*get a new line*/
					newline_start = i;

					while( !isnewline(p[i]) &&  !isend(p[i]) ) {
						i++;
					}
					
					/*now i  is equal to end of the line*/
					j = newline_start;

					if(';' != p[j]) 
					{
						while(j < i && p[j]!='=') {
							j++;
							if('=' == p[j]) 
							{ memset(sKey,0,sizeof(sKey));
							  strncpy(sKey,p+newline_start,j-newline_start);
							  Trim(sKey);
								if(key != NULL && 0==strcmp(key,sKey))
								{
									*key_s = newline_start;
									*key_e = j-1;

									*value_s = j+1;
									*value_e = i;

									return 1;
								}
							}
						}
					}

					i++;
				}
			}
		}
		else
		{
			i++;
		}
	}
	return 0;
}

/**
*@brief read string in initialization file\n
* retrieves a string from the specified section in an initialization file
*@param section [in] name of the section containing the key name
*@param key [in] name of the key pairs to value 
*@param value [in] pointer to the buffer that receives the retrieved string
*@param size [in] size of value buffer
*@param default_value [in] defualt value of result
*@param file [in] path of the initialization file
*@return 1 : read success; \n 0 : read fail
*/
int read_profile_string( const char *section, const char *key,char *value, 
		 int size, const char *default_value, const char *file)
{
	char buf[MAX_FILE_SIZE]={0};
	int file_size;
	int sec_s,sec_e,key_s,key_e, value_s, value_e;

	/*check parameters*/
	assert(section != NULL);
	assert(key != NULL);
	assert(value != NULL);
	assert(size > 0);
	assert(file !=NULL);

	if(!load_ini_file(file,buf,&file_size))
	{
		if(default_value!=NULL &&value != NULL )
		{
			strncpy(value,default_value, size);
		}
		return 0;
	}

	if(!parse_file(section,key,buf,&sec_s,&sec_e,&key_s,&key_e,&value_s,&value_e))
	{
		if(default_value!=NULL &&value != NULL)
		{
			strncpy(value,default_value, size);
		}
		return 0; 
	}
	else
	{
		int cpcount = value_e -value_s;

		if( size-1 < cpcount)
		{
			cpcount =  size-1;
		}
	  if(value != NULL) 
	  {
		  memset(value, 0, size);
      memcpy(value,buf+value_s, cpcount );
      value[cpcount] = '\0';
    }
    return 1;
	}
}

/**
*@brief int value in initialization file\n
* retrieves int value from the specified section in an initialization file
*@param section [in] name of the section containing the key name
*@param key [in] name of the key pairs to value 
*@param default_value [in] defualt value of result
*@param file [in] path of the initialization file
*@return profile int value,if read fail, return default value
*/
int read_profile_int( const char *section, const char *key,int default_value, 
				const char *file)
{
	char value[32] = {0};
	if(!read_profile_string(section,key,value, sizeof(value),NULL,file))
	{
		return default_value;
	}
	else
	{
		return atoi(value);
	}
}

/**
 * @brief write a profile string to a ini file
 * @param section [in] name of the section,can't be NULL and empty string
 * @param key [in] name of the key pairs to value, can't be NULL and empty string
 * @param value [in] profile string value
 * @param file [in] path of ini file
 * @return 1 : success\n 0 : failure
 */
int write_profile_string(const char *section, const char *key,const char *value, const char *file)
{
	char buf[MAX_FILE_SIZE]={0};
	char w_buf[MAX_FILE_SIZE]={0};
	int sec_s=0,sec_e=0,key_s=0,key_e=0, value_s=0, value_e=0;
	int value_len = (int)strlen(value);
	int file_size;
	FILE *out;

	/*check parameters*/
	assert(section != NULL);
	assert(key != NULL);
	assert(value != NULL);
	assert(file !=NULL);

	if(!load_ini_file(file,buf,&file_size))
	{
		sec_s = -1;
	}
	else
	{
		parse_file(section,key,buf,&sec_s,&sec_e,&key_s,&key_e,&value_s,&value_e);
	}

	if( -1 == sec_s)
	{
		
		if(0==file_size)
		{
			hsSnprintf(w_buf+file_size,MAX_FILE_SIZE-file_size,"[%s]\n%s=%s\n",section,key,value);
		}
		else
		{
			/*not find the section, then add the new section at end of the file*/
			memcpy(w_buf,buf,file_size);
			hsSnprintf(w_buf+file_size,MAX_FILE_SIZE-file_size,"\n[%s]\n%s=%s\n",section,key,value);
		}
	}
	else if(-1 == key_s && key != NULL && value != NULL)
	{
		/*not find the key, then add the new key & value at end of the section*/
		memcpy(w_buf,buf,sec_e);
		hsSnprintf(w_buf+sec_e,MAX_FILE_SIZE-sec_e,"%s=%s\n",key,value);
		hsSnprintf(w_buf+sec_e+strlen(key)+strlen(value)+2,MAX_FILE_SIZE-sec_e-strlen(key)-strlen(value)-2,buf+sec_e, file_size - sec_e);
	}
	else
	{
		/*update value with new value*/
		memcpy(w_buf,buf,value_s);
		memcpy(w_buf+value_s,value, value_len);
		memcpy(w_buf+value_s+value_len, buf+value_e, file_size - value_e);
	}
  if( file !=NULL )
  {	
	  out = fopen(file,"w");
    if(NULL == out)
	  {
		  return 0;
	  }
    if(-1 == fputs(w_buf,out) )
    {
     fclose(out);
     return 0;
    }
    fclose(out);
  }
  return 1;
}
#ifndef _MSC_VER
double diffTimeVal(const time_stru *tv)
{
  time_stru tm;
  gettimeofday(&tm, NULL);
  return (tm.tv_sec*1000.0 + (int)(tm.tv_usec/1000) - (tv->tv_sec*1000.0 + (int)(tv->tv_usec/1000)));
  
}
#else
double diffTimeVal(const time_stru *tv){
  return 0.0;
}

int gettimeofday(time_stru *tv, void *p){
  return 0;
}
#endif

/*add by kongdl for check memory*/
int hsSnprintf(char * buf, size_t buflen, const char * format, ...)
{
  va_list vaparam;
  int res;
#ifdef _TESTMODE
  char * tmpbuf;
#endif
  va_start(vaparam, format);/*lint !e530*/
#ifdef _TESTMODE
  tmpbuf = (char *) malloc(buflen);
#ifdef WIN32
  buf[buflen - 1] = '\0';
  tmpbuf[buflen - 1] = '\0';
  res = _vsnprintf(tmpbuf, buflen-1, format, vaparam);
  if (res < 0)
   hsWriteLog(0, "[error][hsSnprintf]内存溢出（%d）!", buflen);
#else
  res = vsnprintf(tmpbuf, buflen, format, vaparam);
  if ((size_t)res >= buflen)
    hsWriteLog(0, "[error][hsSnprintf]内存溢出（%d）!", buflen);
#endif
  strcpy(buf, tmpbuf);
  free(tmpbuf);
#else
  res = vsprintf(buf,format,vaparam); 
#endif
  va_end(vaparam);
  
  return res; 

}

char * hsStrncpy(char *dest, const char *src, size_t num)
{
	char * res = NULL;
	
#ifdef _TESTMODE
  res = strncpy(dest, src, num);
  if (strlen(src) >= num)
  {
  	hsWriteLog(0, "[error][hsStrncpy]内存溢出（%d）!", num);
  }
#else
  res = strcpy(dest, src);
#endif
  return res;
}/*lint !e429*/ 


char * hsStrcat(char * dest, const char * src, size_t destlen)
{
#ifdef _TESTMODE
  char * address;
  address = dest;
  while (*dest)
    dest++;

  while (((size_t)(dest - address + 1) < destlen) && *src)
	  *dest++ = *src++;
  *dest = '\0';
  if (*src)
  {
	  hsWriteLog(0, "[error][hsStrcat]内存溢出（%d）!", destlen);
  }
  return address;
#else
  return strcat(dest, src);
#endif
}
/*add by kongd*/

/************************************************************************/
/* @desc 在预定义字符前添加反斜杠										*/
/* @param 待转义字符串													*/
/* @return 转义过的字符串												*/
/************************************************************************/
char *addslashes(const char *str)
{
    char *new_str;
    char *target;
    int new_length;
    int length = strlen(str);
	int i;

    if (length == 0) 
    {
        char *p = (char *) malloc(1);
        if (p == NULL) 
        {
            return p;
        }
        p[0] = 0;
        return p;
    }

    new_str = (char *) malloc(2 * length + 1);
    if (new_str == NULL)
    {
        return new_str;
    }

    target = new_str;

    for (i=0; i<length; i++)
    {
        switch (str[i]) 
        {
        case '\0':
            *target++ = '\\';
            *target++ = '0';
            break;
        case '\'':
        case '\"':
        case '\\':
            *target++ = '\\';
            break;
        default:
            *target++ = str[i];
            break;
        }
    }

    *target = 0;
    new_length = target - new_str;
    new_str = (char *) realloc(new_str, new_length + 1);
    return new_str;
}

/*==========================================================
 * Function   : escape_sql
 * Description: 转义SQL中的特殊字符
 * Input      : const char *src   待转义字符串
 *				char	   *dst
 *				int		   dst_len
 * Output     : 
 * Return     : 0       成功
 *         		1    	转义失败
 * Author     : zhouyx
 * Date       : 2014/11/10
 ==========================================================*/
int escape_sql(const char* src, char* dst, int dst_len)
{
    int i=0;
    int j=0;
    int src_len=0;
    
    // 入参合法性校验
    if ((NULL == src) || (NULL == dst))
       return -1;
	
   // 如果待处理字符串为空，则返回结果串为空
    src_len=strlen(src);
    if(0 == src_len)
    {
        dst[0] = '\0';
        return 0;
    }

    for (i=0,j=0; i<src_len; i++)
    {
        if (('%' == src[i]) || ('&' == src[i]) || ('_' == src[i]))
        {
            if ((j+5) >= dst_len)
                break;
            dst[j++] = '\'';
			dst[j++] = '|';
			dst[j++] = '|';
			dst[j++] = '\'';
			dst[j++] = src[i];
        }
        else if ('\'' == src[i])
        {
            if ((j+2) >= dst_len)
                break;
            dst[j++] = '\'';
			dst[j++] = src[i];
        }
        else
        {
            if ((j+1) >= dst_len)
                break;
            dst[j++] = src[i];
        }
    }
    dst[j] = '\0';
    if (i != src_len)
       return -1;

    return 0;
}

const char* GetOraPwd(const char* szLogicName)
{
    if(NULL == szLogicName || 0 == strcmp(szLogicName, ""))
        return NULL;
    
    const char* oraPasswd = GMapOraPasswd[szLogicName].c_str();
    if(NULL == oraPasswd)
        return NULL;
 
    return oraPasswd;
}

void AddHsdbOraInfo(const char* szLogicName, const char* passwd)
{
    GMapOraPasswd[szLogicName] = passwd;
}

/********************************** ini读写类 结束***********************************/

