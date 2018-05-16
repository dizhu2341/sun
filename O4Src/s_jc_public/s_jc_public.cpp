/******************************************************************************
 *
 *              ����Ͷ�ʹ���ϵͳ O3.0 
 *
 *       Copyright (C) 2004, ���ݺ������ӹɷ����޹�˾ ������ҵ��
 *
 *               All Rights Reserved.
 *
 * ===========================================================================
 *
 * �� �� ����spub.c
 * ģ�����ƣ�����c����
 * ����˵����
 * ��  �ߣ���־ΰ
 * �������ڣ�2005.08
 * �� �� �ţ�
 * �޸���ʷ��
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

/*ini�ļ��ඨ��*/
#define MAX_FILE_SIZE (1024*16)
#define LEFT_BRACE '['
#define RIGHT_BRACE ']'
#define IS_SPACE(c)  (c == ' '|| c == '\t'||c=='\n'|| c=='\r' )
/**************/

char GTmpStr[10240];            /*������һЩ�����У���Ҫ�����ַ�����ͨ���˱�������������еľ�̬����*/
char GLogFile[MAX_FILENAME_LEN]="";     /*��־����ļ�����������޸ĳɷ����Լ�����־�ļ�*/
int GLogPid;                  /*���̺�*/
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
    /*ʹ�ú����м�����ܵ�GetTime����������������������*/
    fprintf(fh, "%s %s%s",sTmpStr, sbuff,sEnter); 
    fclose(fh);
  }
  return 0;
}

/*************************************************
��ȡ��ǰtick����ȷ�����뼶
**************************************************/
double GetTickCount()
{
  struct timeb t;
  ftime(&t);
  return (double)(1000.0*t.time + t.millitm);
}

/***************************************************************************
��������: CreateDir
��������: �����༶Ŀ¼. �紴��"a/b/c"Ŀ¼��
�������: dir Ŀ¼������Ϊ"a/b/c" ��"a/b/c/"��"/a/b/c" ��"/a/b/c/"
����ֵ��-1 ����ʧ�� 0 �����ɹ�
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
��������:StrSplit
��������: ��src�п���ǰsplitLen���ַ���dst��,����պ������ģ����ȡsplitLen�� ֧�ִ����ĵ��ַ���
		src�б����Ϊʣ�µ��ַ���
�������: src Դ�ַ����� dstĿ��������, splitLen �ָ�ĳ���.
����ֵ�ޣ�
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
��������:StrPos
��������:����s2��s1�е�λ�ã���1��ʼ
�������:
  ...
�������:��
�� �� ֵ:�ڼ�λ
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
��������:Trim
��������:�����߿ո�
�������:
  ...
�������:�������ַ���
�� �� ֵ:�������ַ���
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
�ַ������������Դ�ַ���ΪNULL����""��Ŀ���ַ�����Ĭ��ֵ
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
��������:GetString
��������:�����ַ���source�У���left��right֮��Ĵ�
�������:
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
��������:GetToken
��������:ȡ�ַ�����ȡs1�У���s2�Ӵ�ǰ���ַ���,�����ء�s1Ϊʣ�ಿ��
�������:
  ...
�������:ȡ�õ��Ӵ�
�� �� ֵ:ȡ�õ��Ӵ�
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
��������:Precision
��������:��ȷС����
�������:mode = 0 ��������
1 ��λ
2 ��λ
�������:ȡ��ȷ���С��
�� �� ֵ:ȡ��ȷ���С��
***************************************************************************/
double Precision(double f,int p,int mode)
{
	char str[30];
	int i,n;
	double fRtn;
	if(FEQ(f,0.0))
		return 0.0;
	switch(mode){
    case 0: /*��������*/
		/*2010 ��������double��������Ľ�λ���⣬FCMP��DCMP�����������Ƚϵģ���10Ϊ�˴�����ֵ���ڸ������Ƚ�ʱ���ؽ��Ҳ����ȵ�*/
		if ( f>0 )
		  f=f+DCMP/10;
		else if(f<0)
		  f=f-DCMP/10;
		for(i=0,n=1;i<p;i++)
			n *= 10;
		fRtn = (floor(f*n+0.5))/n;
		break;
    case 1: /*��λ*/
		/*2010 ��������double��������Ľ�λ���⣬FCMP��DCMP�����������Ƚϵģ���10Ϊ�˴�����ֵ���ڸ������Ƚ�ʱ���ؽ��Ҳ����ȵ�*/
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
	case 2:  /*��λ*/
		/*2010 ��������double��������Ľ�λ���⣬FCMP��DCMP�����������Ƚϵģ���10Ϊ�˴�����ֵ���ڸ������Ƚ�ʱ���ؽ��Ҳ����ȵ�*/
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
/*���ܻ���ͬDiffTime ����΢��*/
unsigned long UDiffTime(time_stru dwStart)
{
  unsigned long dd;
  struct timeval dwEnd;
  gettimeofday((time_stru *)&dwEnd,NULL);
  
  dd = 1000000*(dwEnd.tv_sec-dwStart.tv_sec)+(dwEnd.tv_usec-dwStart.tv_usec);  
  
  return dd;
}
/*���������ͱ������뵱ǰ����ʱ��ļ������λΪ�룬��ȷ�����롣
   һ���������ܷ������־��¼
   Ŀǰֻ�������ڿ�ʼ�������ڶ���2038����ǰ
   ������2038����Ҫ��������ĺ���*/
double DiffTime(struct timeb t)
{
  double dd;
  struct timeb t1;
  ftime(&t1);
  dd=(t1.time-t.time)+(t1.millitm*1.0-t.millitm*1.0)/1000.0;
  return dd;
}

/*�ж��Ƿ�Ϊ����
  ����ֵ��1-���ꣻ0-ƽ��*/
int is_leap_year(int in_year)
{
  if ((in_year % 4 == 0) && (in_year % 100 != 0) || (in_year % 400 == 0))
  	return 1;
 	else
 		return 0;
}

/*������ת��������
  ����ֵ��0-�ɹ���1-ʧ��*/
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

/*�������ڼ��
	����ֵ��0-�ɹ���1-��ʼ���ڴ���2-�������ڴ���
	��ʼ�����������2038���Ժ����ʹ�øú���
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
��������:GetTime
��������:���ص�ǰ����ʱ����ַ���,��ʽΪ��yyyy-mm-dd hh:mi:ss
�������:
�������:
�� �� ֵ:
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
��������:ȡϵͳ����
��������:���ص�ǰ���ڵ�����,��ʽΪ��yyyymmdd
�������:
�������:
�� �� ֵ:
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

/*����isourcedate���idatediff ���ʱ��*/
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

/*�жϸ����Ƿ�����*/
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

/*�ж��Ƿ�ĳ�µ����һ��*/
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

/*��ȡ���µ����һ��*/
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

/*����isourcedate���imonthdiff �µ�ʱ��*/
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


/*���ConditionΪ�棬�����ַ���s1,���򷵻�s2*/
char *IIF(int Condition,char *s1,char *s2)
{
  if (Condition)
    return s1;
  else
    return s2;
}

/*�ж�str�ַ������Ƿ�Ϊ�գ�ֻ�пո�Ҳ���*/
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

/*����һ���У��ж�����*/
int GetYearDays(char *sYear)
{
  int nYear,nDays = 365;
  nYear = atoi(sYear);
  if((((nYear % 400) == 0)) ||(((nYear % 4) == 0)&&((nYear % 100) != 0)))
    nDays = 366;
  
  return nDays; 
}

/*������iYear����iMonth��iDay�����ض�Ӧ��ʱ������*/
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




/*��ȡ�ļ���С*/
long Getfilesize(char * sFileName )
{
  struct stat f_stat;
  if( stat( sFileName, &f_stat ) == -1 )
    return -1;

  return (long)f_stat.st_size;
}

/*�ж��ļ���С�Ƿ�ﵽ������ƣ�����ﵽ������ƣ�������������ֺ�׺Ϊϵͳ����*/
int Changefilename(char *sFileName)
{  
  char sNewFile[200]="";
  int  iRet=0, i=1;  
  if(Getfilesize(sFileName)> (MAX_LOGFILE_SIZE*1024*1024) )/*��������С���ƺ󣬸���*/
  {
    hsSnprintf(sNewFile,sizeof(sNewFile),"%s.%s_%d",sFileName,GetDate(), i);
    /*�ж����ļ��Ƿ���ڣ�����ļ����ڣ������������ļ��������ҿ��ƣ������ļ������ܳ���10000��*/
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
  �����΢��windows����,�ú���ȡ��ָ���ļ�������޸�ʱ��
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
  HSSleep����ʵ�ֳ�����ָͣ������ʱ�书��,����Ϊ΢�뼶
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
  GetColString: ȡ��ָ���ַ����а���ָ���ָ����ָ���ָ������,���ַ�������
  sSrc: Դ��
  sDes: ����ֵ,Ŀ�괮
  ch : �ָ��ַ�
  num: ȡ�ڼ�����
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
  GetColString: ȡ��ָ���ַ����а���ָ���ָ����ָ���ָ������,����������
  sSrc: Դ��
  iDes: ����ֵ,����
  ch : �ָ��ַ�
  num: ȡ�ڼ�����
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
  GetColString: ȡ��ָ���ַ����а���ָ���ָ����ָ���ָ������,������ֵ����
  sSrc: Դ��
  enDes: ����ֵ,ʵ��
  ch : �ָ��ַ�
  num: ȡ�ڼ�����
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

/*�ַ�����ĸСд�Ĵ�д*/
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

/******************************���� ini��д�� ��ʼ***********************************/
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
   hsWriteLog(0, "[error][hsSnprintf]�ڴ������%d��!", buflen);
#else
  res = vsnprintf(tmpbuf, buflen, format, vaparam);
  if ((size_t)res >= buflen)
    hsWriteLog(0, "[error][hsSnprintf]�ڴ������%d��!", buflen);
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
  	hsWriteLog(0, "[error][hsStrncpy]�ڴ������%d��!", num);
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
	  hsWriteLog(0, "[error][hsStrcat]�ڴ������%d��!", destlen);
  }
  return address;
#else
  return strcat(dest, src);
#endif
}
/*add by kongd*/

/************************************************************************/
/* @desc ��Ԥ�����ַ�ǰ��ӷ�б��										*/
/* @param ��ת���ַ���													*/
/* @return ת������ַ���												*/
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
 * Description: ת��SQL�е������ַ�
 * Input      : const char *src   ��ת���ַ���
 *				char	   *dst
 *				int		   dst_len
 * Output     : 
 * Return     : 0       �ɹ�
 *         		1    	ת��ʧ��
 * Author     : zhouyx
 * Date       : 2014/11/10
 ==========================================================*/
int escape_sql(const char* src, char* dst, int dst_len)
{
    int i=0;
    int j=0;
    int src_len=0;
    
    // ��κϷ���У��
    if ((NULL == src) || (NULL == dst))
       return -1;
	
   // ����������ַ���Ϊ�գ��򷵻ؽ����Ϊ��
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

/********************************** ini��д�� ����***********************************/

