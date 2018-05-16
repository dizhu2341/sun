/*
 * Program: s_libpublic.cpp
 * Author : 周伟明.
 * Date   : 2009/01/20.
 * Notes  : 提供系统公共函数
 * Modify : 版本       修改日期   修改人         修改单       修改说明
 *          V8.0.6.0   20100614    刘元召         内部         经纪业务运营平台V2.0项目2011基线建立
 *			    V8.0.5.2   20110228   王仁云         20110301024  将StrToHex、HexToStr和TransChar从s_glbfunction_or移到这里。
 *          V8.0.5.1   20100721   周伟明         内部         新增函数hs_timediff（时间差值计算）
 *                                                                    hs_validdate（日期有效性检查）
 *                                                                    hs_validtime（时间有效性检查）
 *          V8.0.5.0   20100414   周伟明         内部         基线
 *          V8.0.4.0   20090926   周伟明         内部         基线
 *          V8.0.3.1   20090804   周伟明         内部         hs_datadiff(begin_date,end_date)修改if( (begin_day > month_day[end_mon - 1]) )修改为if( (end_day > month_day[end_mon - 1]) )
 *          V8.0.3.0   20090626   周伟明         内部         打包
 *          V8.0.2.0   20090420   周伟明         内部         打包
 *          V8.0.1.0   20090120   周伟明         内部         打包
 */

#include  <math.h>
#include  <string.h>
#include  <time.h>
#include  <stdlib.h> 
#include  <ctype.h> 
#include  <stdio.h>
#include  <stdarg.h>
#include  "IncludeFm/s_libpublic.h"

#ifdef OS_UNIX
  #ifdef __cplusplus
     extern "C" { 
  #endif
  #ifndef _NOTEXPORT_VER_
  const char *  ASFC_CALL_MODE GetLibVersion();
  #endif
  #ifdef __cplusplus
    }
  #endif

#endif

/*==========================================================
 * Function   : GetLibVersion
 * Description: 获取版本信息
 * Input      : 
 * Output     : 
 * Return     : so版本信息
 * Author     : zhouwm
 * Date       : 2007/12/07
 ==========================================================*/
#ifdef OS_UNIX
const char * ASFC_CALL_MODE GetLibVersion()
{
    return "V9.0.2.0";
}
#endif

/*==========================================================
 * Function   : isnull
 * Description: 验证字符串是否为空
 * Input      : const char *d_str   输入字符串
 * Output     : 
 * Return     : 0       字符串为空
 *         1    字符串不为空
 * Author     : zhouwm
 * Date       : 2004/08/16
 ==========================================================*/
int isnull(const char *d_str)
{
    if (d_str == NULL || d_str[0] == '\0')
        return(0);              
    
    return(1);
}

/*==========================================================
 * Function   : length
 * Description: 取字符串长度
 *              与Oracle的length函数功能类似
 * Input      : char *str   输入字符串
 * Output     : 
 * Return     : >0      字符串长度
 *              0       字符串为空
 * Author     : zhouwm
 * Date       : 2004/08/16
 ==========================================================*/
int length(const char *str)
{
    const char    *p;

    if (isnull(str) == 0)
    {
        return(0);
    }

    for(p = str; *p != '\0'; p++);

    return(p - str);
}

/*==========================================================
 * Function  : trim
 * Description:滤去字符串的前后空格,与Oracle的Trim函数功能类似
 * Input     : char *str
 * Output    : char *str
 * Return    : char *str
 * Author    : zhouwm
 * Date      : 2004/08/16
 ==========================================================*/
char *trim(char *str )
{
    int len;
    int i;

    if (isnull(str) == 0)
        return str;
    
    len = strlen(str);

    while((str[len-1] == ' ') && (len >0))
        len--;
    
    str[len] = '\0';
    
    i = 0;
    while(str[i] == ' ')
        i++;
    
    if(i > 0)
    {
        //for( j=0; j<len-i+1 ; j++ )
        //    str[j] = str[j+i];
        memcpy(str,str + i,len - i + 1);
    }

    return str;
}

/*==========================================================
 * Function  : trimb
 * Description:滤去字符串的前后空格,与Oracle的Trim函数功能类似
 *             如果trim后为空则保留一个空格
 * Input     : char *str
 * Output    : char *str
 * Return    : char *str
 * Author    : zhouwm
 * Date      : 2004/08/16
 ==========================================================*/
char *trimb(char *str )
{
    int len;
    int i;

    if (isnull(str) == 0)
        return str;
    
    len = strlen(str);

    while((str[len-1] == ' ') && (len >0))
        len--;
    str[len] = '\0';
    
    i = 0;
    while(str[i] == ' ')
        i++;
    
    if(i > 0)
    {
        //for( j=0; j<len-i+1 ; j++ )
        //    str[j] = str[j+i];
        memcpy(str,str + i,len - i + 1);
    }
    
    if (isnull(str) == 0)
        strcpy(str," ");
    
    return str;
}

/*==========================================================
 * Function   : replace
 * Description: 字符串替换,注意输入目标字符串长度不要太短，以免替换后越界
 * Input      : char       *dest   目标串
 *              const char *src    源字符串
 *              const char *s_old  旧字符串
 *              const char *s_new  新字符串
 * Output     : 
 * Return     : 0       成功
 *              -1      输入为空
 * Author     : zhouwm
 * Date       : 2004/08/16
 ==========================================================*/
int replace(char *dest,const char *src,const char *old_str,const char *new_str)
{
	const char *s_tmp = NULL;
    char s_str[8192]={0};
    //*s_src,*s_old,*s_new,
    //int    len,flag;
    //int    len,flag;
    
    if (isnull(src) == 0)
        return -1;
    
    if ((isnull(old_str) == 0))
        return -1;

    //if (strlen(src) < strlen(old_str)) then 

    dest[0] = '\0';
    s_str[0] = '\0';
    while((s_tmp = strstr(src,old_str)) != NULL)
    {
        strncpy(s_str,src,s_tmp-src);
        s_str[s_tmp-src]='\0';
        strcat(dest,s_str);
        strcat(dest,new_str);
        src = s_tmp + strlen(old_str);
    }
    
    if (length(src) > 0)
        strcat(dest,src);

    return 0;
}

/*==========================================================
 * Function   : ldelchar
 * Description: 删前面所有指定的字符
 * Input      : char       *dest     目标串
 *              const char *src      源字符串
 *              const char c_char    删除字符
 * Output     : 
 * Return     : 0       成功
 *              -1      输入为空
 * Author     : zhouwm
 * Date       : 2004/12/29
 ==========================================================*/
int ldelchar(char *dest,const char *src,const char c_char)
{
    int  i=0,ilen = 0;
    
    dest[0] = '\0';

    if (isnull(src) == 0)
        return -1;

    ilen = strlen(src);
    
    while (i < ilen)
    {
       
       if (src[i] != c_char)
         break;
       
       i++;
    }
    
    memcpy(dest,src + i,ilen - i + 1);

    return 0;
}

/*==========================================================
 * Function   : rdelchar
 * Description: 后删字符所有指定的字符
 * Input      : char       *dest     目标串
 *              const char *src      源字符串
 *              const char c_char    删除字符
 * Output     : 
 * Return     : 0       成功
 *              -1      输入为空
 * Author     : zhouwm
 * Date       : 2004/12/29
 ==========================================================*/
int rdelchar(char *dest,const char *src,const char c_char)
{
    char s_str[8192]={0};
    int  i=0,j=0;
    
    dest[0] = '\0';
    s_str[0] = '\0';

    if (isnull(src) == 0)
        return -1;

   hs_strcpy(s_str,src);

    i = length(src) - 1;
    
    while (i >= 0)
    {
       
       if (src[i] == c_char)
       {
          s_str[i] = '\0';
      }
       else
          break;
       i--;
    }
    
   hs_strcpy(dest,s_str);

    return 0;
}


/*==========================================================
 * Function   : lpad
 * Description: 左补字符，与Oracle的lpad函数功能类似,
 *              如果字符串小于len值则左补字符c
 * Input      : char *buf 输入字符串
 *              int  len  补字符后的字符串的长度
 *              char c    待补的字符
 * Output     : 
 * Return     : char *str
 * Author     : zhouwm
 * Date       : 2004/08/16
 ==========================================================*/
char *lpad( char *buf, int len, char c )
{
    register int i, n;

    if( buf==NULL )
        return NULL;
    
    n = length( buf );
    if( n >= len ) return buf;
    
    i = len - n;
    memmove( buf+i, buf, n+1 );
    
    while( --i>=0 )
        buf[i] = c;

    buf[len] = '\0';
    
    return buf;
}

/*==========================================================
 * Function   : rpad
 * Description: 右补字符，与Oracle的rpad函数功能类似
 *              如果字符串小于len值则右补字符c
 * Input      : char *buf 输入字符串
 *              int  len  补字符后的字符串的长度
 *              char c    待补的字符
 * Output     : 
 * Return     : char *str
 * Author     : zhouwm
 * Date       : 2004/08/16
 ==========================================================*/
char *rpad( char *buf, int len, char c )
{
    register int n;
    
    if (buf == NULL)
        return NULL;
    
    n = strlen(buf);
    if( n >= len )
       return buf;
    
    while( n<len )
        buf[n++] = c;
    
    buf[len] = '\0';
    
    return buf;
}

/*==========================================================
 * Function   : instr
 * Description: 查找字符，与Oracle的instr函数功能类似
 * Input      : const char * src 源字符串
 *              const char  c    待查找字符
 * Output     : 
 * Return     : >0      成功
 *              -1      输入为空
 * Author     : zhouwm
 * Date       : 2004/08/16
 ==========================================================*/
int   instr(const char * src,const  char c)
{
    const char *p;
    int i=0,j=0,ilen=0,ipos=1,inth=1;

    if(isnull(src) == 0)
        return(-1); 
    
    j = 0;
    //ipos = pos;
    //inth = nth;
    p = src;
    if (inth <= 0)
        inth = 1;

    ilen = length(p);
    if (abs(ipos) > ilen)
        return 0;

    if (ipos >= 0 )
    {
        if (ipos > 0)
            ipos = ipos -1;
        
        for (i = ipos;i < ilen;i++)
        {
            if (*(p+i) == '\0')
                return 0;
            if (*(p+i) == c)
            {
                j = j + 1;
                if (j == inth)
                    return (i+1);
            }
        }
    }
    else
    {
        ilen = ilen - abs(ipos);
        for (i = ilen - 1;i >= 0;i--)
        {
            
            if (*(p+i) == c)
            {
                j = j + 1;
                if (j == inth)
                    return (i+1);
            }
        }
    }
    return 0;
}

/*==========================================================
 * Function   : hs_strstr
 * Description: 查找字符串
 * Input      : const char * src    源字符串
 *              const char * substr 待查找字符串
 * Output     : 
 * Return     : >0      成功
 *              -1      输入为空
 * Author     : zhouwm
 * Date       : 2004/08/16
 ==========================================================*/
int   hs_strstr(const char * src,const char *substr)
{
    const char *s_tmp = NULL;

    if ((isnull(src) == 0) || (isnull(substr) == 0))
        return -1;
    
    s_tmp = strstr(src,substr);
    if (isnull(s_tmp) == 0)
        return -1;

    return s_tmp-src+1;
}

/*==========================================================
 * Function   : subcmp
 * Description: 子串比较
 * Input      : const char *s 		源字串
 *				int		   pos		该子串在源字串中的起始位置，从1开始
 *              int        len 		要得到的子串的长度
 *				const char *substr	比较得子串
 * Output     : 
 * Return     : 0 		成功
 *				-1		输入为空
 * Author     : zhouwm
 * Date       : 2004/10/12
 ==========================================================*/
int substr(const char *src,int pos,int len,char *sub)
{
    const char    *p;
    char    *w;
    int     k=0,ipos=0,ilen=0;

    p = src;
    w = sub;
    ipos = pos;

    if (isnull(p) == 0)
        return -1;
    
    ilen = len;
    if( ilen <= 0 )
        ilen = length(p);

    ipos = pos;
    if (abs(ipos) > length(p))
        return -1;
    
    if (length(p) < ilen)
        ilen = length(p);
    
    if (ipos <= 0)
    {
       strcpy(sub,"");
       return 0;
    }
    if (ipos > 0)
        ipos = ipos - 1;

    
    if( ipos >= 0 )
    {
        p = p + abs(ipos);
    }
    else
    {
        return -1;
    }
    
    //strncpy(w,p,ilen);
    
    k = 0;
    while( (*p != '\0') && (k < ilen) )
    {
        *w++ = *p++;
        k++;
    }
    
    *w = '\0';
    
    return 0;
}

/*==========================================================
 * Function   : subcmp
 * Description: 子串比较
 * Input      : const char *s       源字串
 *              int        pos      该子串在源字串中的起始位置，从1开始
 *              int        len      要得到的子串的长度
 *              const char *sub     比较得子串
 * Output     : 
 * Return     : 0       成功
 *              -1      输入为空
 * Author     : zhouwm
 * Date       : 2004/10/12
 ==========================================================*/
int subcmp(const char *src,int pos,int len,const char *sub)
{
    char s_sub[2048]={0};
    int ret=0;
    
    if (len - 1 > 2048)
      return -1;
    
    ret = substr(src,pos,len,s_sub);
    if (ret != 0)
        return ret;
    
    ret = hs_strcmp(s_sub,sub);

    return ret;
}


/*==========================================================
 * Function   : hs_strcmp
 * Description: 字符串比较
 * Input      : char *d_str 字符串
 *              char *s_str 字符串
 * Output     : 
 * Return     : 0       成功
 *              -1      输入为空
*               <>0     字符不相等
 * Author     : zhouwm
 * Date       : 2004/08/16
 ==========================================================*/
int hs_strcmp(const char *d_str, const char *s_str)
{
    register signed char __res;
    
    if ((isnull(d_str) == 0) || (isnull(s_str) == 0))
        return(-1);             
    
    if (strlen(d_str) != strlen(s_str))
        return(1); 
    
    while(1)
    {
        if ( (__res = *d_str - *s_str++) != 0 || !*d_str++)
            break;  
    }
    
    return __res;
}


/*==========================================================
 * Function   : hs_strcat
 * Description: 将一个字串连接到另一个字串后面
 * Input      : char *s_dest 目的字串，连接后结果字串存放的地方
 *              char *s_src  要连接的字串
 * Output     : 
 * Return     : 0       成功
 *              -1      输入为空
 * Author     : zhouwm
 * Date       : 2004/08/16
 ==========================================================*/
int hs_strcat(char *s_dest,const char *s_src)
{
    char    *p;
    const char  *k;
    
    if (isnull(s_src) == 0)
        return(-1); 
    
    if (s_dest == NULL)
    	return(-1);
    
    p = s_dest;
    k = s_src;
    
    if (isnull(p) == 0)
        p[0] = '\0'; 

    for(;*p != '\0';p++);
    
    while( *k != '\0' ){
        *p++ = *k++;
    }
    
    *p = '\0';
    
    return(0);
}

/*==========================================================
 * Function   : hs_strcpy
 * Description: 字符串拷贝
 * Input      : char *d_dest 目的字串
 *              char *s_src  源字符串
 * Output     : 
 * Return     : 0       成功
 *              -1      输入为空
 * Author     : zhouwm
 * Date       : 2004/08/16
 ==========================================================*/
int hs_strcpy(char *d_dest,const  char *s_src)
{
    if (isnull(s_src) == 0)
    {
        d_dest[0] = '\0';
        return(-1);
    }
    
    if (d_dest == NULL)
    	return(-1);

    for(; *d_dest++ = *s_src++; )  /* the same as strcpy. */
        ;

    return(0);
}

/*==========================================================
 * Function   : hs_strncmp
 * Description: 两个字符指定长度比较
 * Input      : const char *d_str 比较字符串
 *              int        d_len  指定比较长度
 *              const char *s_str 要比较得字符串
 * Output     : 
 * Return     : 0       成功
 *              -1      输入为空
 *              <>0     字符不相同
 * Author     : zhouwm
 * Date       : 2004/08/16
 ==========================================================*/
int hs_strncmp(const char *d_str, int d_len,const char *s_str)
{
    int ilen=0,ilen1 = 0;
    
    if ((isnull(d_str) == 0) || (isnull(s_str) == 0) || d_len < 0)
    {
            return(-1);
    }
    
    ilen = strlen(d_str);
    ilen1 = strlen(s_str);
    
    if (((ilen < d_len) || (ilen1 < d_len)) && (ilen != ilen1))
    	return (1);
    
    for (; d_len > 0; d_len--)
    {
       if ( *d_str != *s_str)   /* Can check the '\0' case! */
           return(1);

       //if ( *d_str == '\0' && *s_str == '\0')
       //    break;

       d_str++;
       s_str++;
    }

    return(0);
}

/*==========================================================
 * Function   : hs_strncat
 * Description: 指定长度将一个字串连接到另一个字串后面
 * Input      : char *s_dest       目的字串，连接后结果字串存放的地方
 *              char *s_src        要连接的字串
 *              size_t     count   指定连接长度
 * Output     : 
 * Return     : 0       成功
 *              -1      输入为空
 * Author     : zhouwm
 * Date       : 2004/08/16
 ==========================================================*/
int hs_strncat(char *s_dest,const char *s_src,size_t count)
{
    char    *p;
    const char  *k;
    size_t li_len = 0;
    p = s_dest;
    k = s_src;
    
    if (s_dest == NULL)
       return (-1);
    
    if (isnull(s_src) == 0 || (count <= 0))
        return(-1); 
    
	li_len = length(s_dest);

    if (isnull(p) == 0)
        p[0] = '\0'; 

    for(;*p != '\0';p++);
    
    while( li_len < count-- && *k != '\0' ){
        *p++ = *k++;
    }
    
    *p = '\0';
    
    return(0);
}

/*==========================================================
 * Function   : hs_strncpy
 * Description: 指定长度字符串赋值
 * Input      : const char *s_dest 目的字串
 *              const char *s_src  源字符串
 *              size_t     count   指定复制长度
 * Output     : 
 * Return     : 0       成功
 *              -1      输入为空
 * Author     : zhouwm
 * Date       : 2004/08/16
==========================================================*/
int hs_strncpy(char *s_dest,const char *s_src,size_t count)
{
    if ((isnull(s_src) == 0) || (count <= 0))
    {
        *s_dest = '\0';
        return -1;
    }
    
    while (count-- && (*s_dest++ = *s_src++) != '\0')
        /* nothing */;
    
    *s_dest = '\0';

    return(0);
}

/*==========================================================
 * Function   : hs_memcmp
 * Description: 两个字符比较
 * Input      : const char *d_dest 目的字串
 *              const char *s_src  源字符串
 *              size_t     count   指定比较长度
 * Output     : 
 * Return     : 0       成功
 *              -1      输入为空
*               <>0     字符不相同
 * Author     : zhouwm
 * Date       : 2004/08/16
 ==========================================================*/
int hs_memcmp(const char* d_desc,const char * s_src,size_t count)
{
    const char *su1, *su2;
    signed char res = 0;
    int i = count;

    if( (isnull(d_desc) == 0)||(isnull(s_src) == 0)||(count <= 0)
        || (length(d_desc) < i) || (length(s_src) < i))
        return(-1);

    for( su1 = d_desc, su2 = s_src; 0 < count; ++su1, ++su2, count--)
    {
        if ((res = *su1 - *su2) != 0)
            break;
    }
    
    return res;
}

/*==========================================================
 * Function   : hs_strtolower
 * Description: 字符转换成小写
 * Input      : char *str 字符串
 * Output     : 
 * Return     : 0       成功
 *              
 * Author     : zhouwm
 * Date       : 2004/08/16
 ==========================================================*/
int hs_strtolower(char *str)
{
    if (isnull(str) == 0)
        return(0);

    for(; *str = tolower(*str); str++) ;

    return(0);
}

/*==========================================================
 * Function   : hs_strtoupper
 * Description: 字符转换成大写
 * Input      : char *str 字符串
 * Output     : 
 * Return     : 0       成功
 *              
 * Author     : zhouwm
 * Date       : 2004/08/16
 ==========================================================*/
int hs_strtoupper(char *str)
{
    if (isnull(str) == 0)
        return(0);

    for(; *str = toupper(*str); str++) ;

    return(0);
}


/*==========================================================
 * Function   : hs_strlrcpy
 * Description: 字符串左右补字符串
 * Input      : char *str         字符串
 *            : const void *rstr  左补字符串
 *            : const void *rstr  右补字符串
 * Output     : 
 * Return     : 0:  成功
 *              -1: 失败
 * Author     : zhouwm
 * Date       : 2004/10/11
 ==========================================================*/
int hs_strlrcpy(char *str,const char *lstr,const char *rstr)
{
    const char  *s_lstr;
    const char  *s_rstr;
    int     i=0,len=0;
    
    if (isnull(str) == 0)
        return -1;
        
    s_lstr = lstr;
    s_rstr = rstr;
    len = strlen(s_lstr);
    
    memmove(str+len,str,len+length(str));
    
    for (i=0;i<len;i++)
        str[i] = s_lstr[i];
    
    if (hs_strcat(str,s_rstr) < 0)
        return -1;

    return 0;
}


/*==========================================================
 * Function   : hs_datediff
 * Description: 日期间隔天数
 * Input      : int 起始日期,结束日期 
 *              特别地 日期不可以小于等于19700101
 * Output     : 
 * Return     : 日期间隔天数
 *              -1      输入日期非法
 * Author     : zhouwm，laisha
 * Date       : 2004/08/19
 ==========================================================*/
long hs_datediff(const int begin_date,const int end_date)
{
    struct tm begdate,enddate;
    time_t  t_begdate,t_enddate;
    long l_diff;
    int begin_year=0,begin_mon=0,begin_day=0,beg_flag=0,end_flag=0;
    int end_year=0,end_mon=0,end_day=0;
    int month_day[] = {31,28,31,30,31,30,31,31,30,31,30,31};
  
    begin_year = begin_date/10000;
    begin_mon = (begin_date%10000)/100;
    begin_day = (begin_date%10000)%100;

    end_year = end_date/10000;
    end_mon = (end_date%10000)/100;
    end_day = (end_date%10000)%100;
    
    //zhouwm 修改
    if((begin_year < 0) || (begin_mon <= 0 ) || (begin_mon >12) || (begin_day <= 0) 
        || (begin_day > 31))
        return -1;
        
    if( (begin_day > month_day[begin_mon - 1]) )
    {
        if( ((begin_year%4 == 0)&&(begin_year%100 != 0)) || (begin_year%400 == 0) )
        {
            if( (begin_mon == 2) && (begin_day > 29)  )
                return -1;
        }
        else
            return -1;
    }

    if((end_year < 0) || (end_mon <= 0 ) || (end_mon >12) || (end_day <= 0) 
        || (end_day > 31))
        return -1;
    
    //20090804 zhouwm if( (begin_day > month_day[end_mon - 1]) )修改为if( (end_day > month_day[end_mon - 1]) )
    if( (end_day > month_day[end_mon - 1]) )
    {
        if( ((end_year%4 == 0)&&(end_year%100 != 0)) || (end_year%400 == 0) )
        {
            if( (end_mon == 2) && (end_day > 29)  )
                return -1;
        }
        else
            return -1;
    }
    //zhouwm 修改

    memset(&begdate,0,sizeof(begdate));
    memset(&enddate,0,sizeof(enddate));
   
    begdate.tm_year = begin_year-1900;
    begdate.tm_mon = begin_mon-1;
    begdate.tm_mday = begin_day;
    enddate.tm_year = end_year-1900;
    enddate.tm_mon = end_mon-1;
    enddate.tm_mday = end_day;
    
    t_begdate = mktime(&begdate);

    if (t_begdate == -1)
        return -1;
    t_enddate = mktime(&enddate);
    if (t_enddate == -1)
        return -1;
    l_diff = abs(t_enddate - t_begdate);
        return l_diff/86400;
}

/*==========================================================
 * Function   : hs_dateadd
 * Description: 增加或减少相应的日期
 * Input      : int begin_date 日期,n 天数,n>0 增加天数,n<0, 减少天数
 *              特别地 日期不可以小于等于19700101
 * Output     : 
 * Return     : 日期
 *              -1      输入日期非法
 * Author     : zhouwm，laisha
 * Date       : 2004/08/19
 ==========================================================*/
int hs_dateadd(int begin_date,int n)
{
    struct tm begdate;
    struct tm *enddate;
    time_t  t_begdate;
    int begin_year=0,begin_mon=0,begin_day=0;
    int month_day[] = {31,28,31,30,31,30,31,31,30,31,30,31};
    
    begin_year = begin_date/10000;
    begin_mon = (begin_date%10000)/100;
    begin_day = (begin_date%10000)%100;
    
    //zhouwm 修改
    if((begin_year < 0) || (begin_mon < 0 ) || (begin_mon >12) || (begin_day < 0) 
        || (begin_day > 31))
        return -1;
        
    if( (begin_day > month_day[begin_mon - 1]) )
    {
        if( ((begin_year%4 == 0)&&(begin_year%100 != 0)) || (begin_year%400 == 0) )
        {
            if( (begin_mon == 2) && (begin_day > 29)  )
                return -1;
        }
        else
            return -1;
    }
    //zhouwm 修改

    memset(&begdate,0,sizeof(begdate));
    memset(&enddate,0,sizeof(enddate));

    begdate.tm_year = begin_year-1900;
    begdate.tm_mon = begin_mon-1;
    begdate.tm_mday = begin_day;

    t_begdate = mktime(&begdate);
    if (t_begdate == -1)
        return -1;
    t_begdate = t_begdate + 86400*n;
    enddate = localtime(&t_begdate);
    
    return (enddate->tm_year + 1900)*10000 + (enddate->tm_mon+1)*100 + enddate->tm_mday;
};

/*==========================================================
 * Function   : hs_trunc
 * Description: 截取浮点数小数点后n位，四舍五入，同oracle中的round
 * Input      : double f 输入浮点数,int n截取位数  n>0
 * Output     : 
 * Return     : 截取后的浮点数
 *              n<0返回输入浮点数
 * Author     : laisha
 * Date       : 2004/08/19
 ==========================================================*/
long double hs_round(long double f,const long int n)
{
  long double f1,f2,n1;
  int li=1;
  
  if (n < 0)
     return f;
// zhouwm 20060107 负数时会处理不正常
  if (f < 0)
      li = -1;
  f = fabs(f);

  n1 = pow(10,(double)n);
  f1 = f * n1;
  f2 = fmod(f1,1);
  if ((f2 -0.5 )>=0)
    f1 = f1 + 1.0;
  else if ((f2-0.5) + 1<0)
    f1 = f1 - 1.0;
  if (f < 0)
    f1 = f1 + 1;
  f1 = floor(f1) / n1;
  f = f1*li;
  return f;
}


/*==========================================================
 * Function   : hs_round
 * Description: 截取浮点数小数点后n位，末位舍去，同oracle中的trunc
 * Input      : double f 输入浮点数,int n截取位数  n>0
 * Output     : 
 * Return     : 截取后的浮点数
 *              n<0返回输入浮点数
 * Author     : laisha
 * Date       : 2004/08/19
 ==========================================================*/
long double hs_trunc(long double f,const long int n)
{
  long double f1,n1;
  if (n < 0)
     return f;
  n1 = pow(10,(double)n);
  f1 = f * n1;
  if (f < 0)
     f1 = f1 + 1;
  f1 = floor(f1) / n1;
  f = f1;
  return f;
}

/*==========================================================
 * Function   : ltoc
 * Description: 数字转换成字符串
 * Input      : char *buf  转换后字符
 *              long data  被转换数字
 * Output     : 
 * Return     : char* 字符串
 *              
 * Author     : zhouwm
 * Date       : 2004/08/19
 ==========================================================*/
char *ltoc( char *buf, long data )
{                                    
    register long n, m, iCount, flg=0;
    register char c;
    
    if( buf == NULL )
        return NULL;
    
    if( data==0 )
    {
        buf[0] = '0';
        buf[1] = '\0';
        return buf;
    }
    else if( data<0 )
    {
        flg = 1;
        data *= -1;
    }
    iCount = flg;
    while( data>0 )
    {
        n = data/10;
        m = data - (n<<3) - n - n;
        data = n;
        buf[iCount++] = m + '0';
    }
    buf[iCount--] = '\0';
    n = flg;
    while( iCount>n )
    {
        c = buf[iCount];
        buf[iCount--] = buf[n];
        buf[n++] = c;
    }
    if( flg )
        buf[0] = '-';
    
    return buf;
}


/*==========================================================
 * Function   : dtostr
 * Description: 浮点数转换成字符
 * Input      : char    *buf  转换后字符串
 *              double  data  被转换浮点数
 * Output     : 
 * Return     : char* 字符串
 *              
 * Author     : zhouwm
 * Date       : 2004/08/19
 ==========================================================*/
char *dtostr( char *buf, double data )
{
    register long dotf, intf;
    register short i;
    char tmp[10]={0};
    
    if( buf==NULL )
        return NULL;
    
    intf = (long)data;
    if( intf>=0 )
        dotf = (long)((data-intf+0.0000005)*1000000);
    else if( intf<0 )
        dotf = (long)((intf-data+0.0000005)*1000000);
    
    ltoc(buf, intf);
    tmp[0] = '.';

    if( dotf==0 )
    {
        tmp[3] = '\0';
    }
    else
    {
        ltoc(tmp+1, dotf );
        for( i=strlen(tmp)-1; i>1 && tmp[i]=='0'; i-- )
            tmp[i] = '\0';
    }   
    strcat( buf, tmp );
    
    if (buf[strlen(buf)-1] == '.')
        buf[strlen(buf)-1] = '\0';
    
    return buf;
}

/*==========================================================
 * Function   : right
 * Description: 右取字符串
 * Input      : char *p_source_string  原字符串
 *            : int   p_get_length     取原字符串长度
 * Output     : char *p_dest_string    目标字符串
 * Return     : 0                 成功
 *              -1                失败
 *              
 * Author     : zhouwm
 * Date       : 2004/10/11
 ==========================================================*/
int right(const char * s_str,const int len,char * d_str)
{
    int i_len = 0;
    
    if (isnull(s_str) == 0)
        return -1;
    
    i_len = strlen(s_str);
    
    if (i_len >= len)
        i_len = i_len -len;
    else
        i_len = 0;
    
    strcpy(d_str, s_str+i_len);

 
    return 0;
}

/*==========================================================
 * Function   : left
 * Description: 左取字符串
 * Input      : char *p_source_string  原字符串
 *            : int   p_get_length     取原字符串长度
 * Output     : char *p_dest_string    目标字符串
 * Return     : 0                 成功
 *              -1                失败          
 * Author     : zhouwm
 * Date       : 2004/10/11
 ==========================================================*/
int left(const char * s_str,const int len,char * d_str)
{
    int i_len = 0;
    
    if (isnull(s_str) == 0)
        return -1;
    
    i_len = strlen(s_str);
    if (i_len > len)
        strncpy(d_str, s_str, len);
    else
        strcpy(d_str, s_str);
 
    return 0;
}

/*==========================================================
 * Function   : hs_getdate
 * Description: 取当前日期
 * Input      : 
 * Output     : int               当前日期，格式为YYYYMMDD
 * Return     : 0                 成功
 *              -1                失败          
 * Author     : zhouwm
 * Date       : 2005/10/25
 ==========================================================*/
int hs_getdate()
{
    struct tm *newtime;
    time_t long_time;
    int li_year=0,li_month=0,li_day=0;
    
    time( &long_time );
    newtime = localtime( &long_time ); 

    li_year = newtime->tm_year + 1900;
    li_month = newtime->tm_mon + 1;
    li_day = newtime->tm_mday;
    
    return li_year*10000+li_month*100+li_day;
}

/*==========================================================
 * Function   : hs_getdatetime
 * Description: 取当前日期
 * Input      : int *pi_date      当前日期，格式为YYYYMMDD
 *              int *pi_time      当期实际，格式为HHMMSS
 * Output     : int               
 * Return     : 0                 成功
 *              -1                失败          
 * Author     : zhouwm
 * Date       : 2006/11/17
 ==========================================================*/
int hs_getdatetime(int *pi_date,int *pi_time)
{
    struct tm *newtime;
    time_t long_time;
    int li_year=0,li_month=0,li_day=0,li_hour=0,li_min=0,li_sec=0;
    
    time( &long_time );
    newtime = localtime( &long_time ); 

    li_year = newtime->tm_year + 1900;
    li_month = newtime->tm_mon + 1;
    li_day = newtime->tm_mday;
    li_hour = newtime->tm_hour;
    li_min = newtime->tm_min;
    li_sec = newtime->tm_sec;
    
    *pi_date = li_year*10000+li_month*100+li_day;
    *pi_time = li_hour*10000+li_min*100+li_sec;
    
    return *pi_date;
}

/*==========================================================
 * Function   : hs_datediff
 * Description: 取两个日期的差值
 * Input      : int   pi_begdate     开始日期（格式为：YYYYMMDD）
 *            : int   pi_enddate     结束日期（格式为：YYYYMMDD）
 *            : char *ps_format      比较格式
 *                                   YY: 年
 *                                   QQ: 季度
 *                                   MM: 月
 *                                   WW: 周
 *                                   DD: 日
 * Output     : int                  日期差值
 * Return     : 0                 成功
 *              -1                失败          
 * Author     : zhouwm
 * Date       : 2005/10/25
 ==========================================================*/
int hs_datediff(const int pi_begdate,const int pi_enddate,char * ps_format)
{
    int li_beg_year=0,li_beg_month=0,li_beg_day=0,li_begdate=0;
    int li_end_year=0,li_end_month=0,li_end_day=0,li_enddate=0,li_flag=1,li_ret=0;
    time_t  lt_begdate,lt_enddate;
    struct tm ltm_begdate,ltm_enddate;
    int month_day[] = {31,28,31,30,31,30,31,31,30,31,30,31};
    
    memset(&lt_begdate,0,sizeof(lt_begdate));
    memset(&lt_enddate,0,sizeof(lt_enddate));
    memset(&ltm_begdate,0,sizeof(ltm_begdate));
    memset(&ltm_enddate,0,sizeof(ltm_enddate));

    // 判断输入参数是否有效
    if ((hs_strcmp(ps_format,"YY") == 0
      && hs_strcmp(ps_format,"QQ") == 0
      && hs_strcmp(ps_format,"MM") == 0
      && hs_strcmp(ps_format,"WW") == 0
      && hs_strcmp(ps_format,"DD") == 0) 
      || pi_begdate <= 0 
      || pi_enddate <= 0)
      return -1;
    
    // 判断开始日期和结束日期大小
    if (pi_enddate < pi_begdate)
    {
        li_flag = -1;
        li_begdate = pi_enddate;
        li_enddate = pi_begdate;
    }
    else if (pi_enddate > pi_begdate)
    {
        li_begdate = pi_begdate;
        li_enddate = pi_enddate;
    }
    else
    {
        return 0;
    }
    
    li_beg_year = li_begdate / 10000;
    li_beg_month = li_begdate % 10000 / 100;
    li_beg_day = (li_begdate % 10000) % 100;
    
    li_end_year = li_enddate / 10000;
    li_end_month = li_enddate % 10000 / 100;
    li_end_day = (li_enddate % 10000) % 100;
    
    // 日期合法化判断
    if((li_beg_year < 0) || (li_beg_month <= 0 ) || (li_beg_month >12) 
        || (li_beg_day <= 0) || (li_beg_day > 31) 
        || (li_end_year < 0) || (li_end_month <= 0 ) || (li_end_month >12) 
        || (li_end_day <= 0) || (li_end_day > 31))
        return -1;
    
    // 开始日合法化判断
    if( (li_beg_day > month_day[li_beg_month - 1]) )
    {
        // 闰年2月天数判断
        if( ((li_beg_year%4 == 0)&&(li_beg_year%100 != 0)) || (li_beg_year%400 == 0) )
        {
            if( (li_beg_month == 2) && (li_beg_day > 29)  )
                return -1;
        }
        else
            return -1;
    }
    
    // 结束日合法化判断
    if( (li_end_day > month_day[li_end_month - 1]) )
    {
        // 闰年2月天数判断
        if( ((li_end_year%4 == 0)&&(li_end_year%100 != 0)) || (li_end_year%400 == 0) )
        {
            if( (li_end_month == 2) && (li_end_day > 29)  )
                return -1;
        }
        else
            return -1;
    }
    
    // 日期年差值
    if (hs_strcmp(ps_format,"YY") == 0)
    {
        if (li_end_day >= li_beg_day)
           li_end_month = li_end_month - li_beg_month;
        else
           li_end_month = li_end_month - li_beg_month -1;

        if (li_end_month < 0)
           return (li_end_year - li_beg_year - 1)*li_flag;
        else
           return (li_end_year - li_beg_year)*li_flag;
    }
    
    // 日期季度或者月差值
    if ( hs_strcmp(ps_format,"QQ") == 0
      || hs_strcmp(ps_format,"MM") == 0)
    {
        if (li_end_day >= li_beg_day)
            li_end_month = li_end_month - li_beg_month;
        else
            li_end_month = li_end_month - li_beg_month -1;
                
        if (li_end_month < 0)
        {
            li_end_month = li_end_month + 12;
            li_end_year = li_end_year - li_beg_year - 1;
        }
        else
        {
            li_end_year = li_end_year - li_beg_year;
        }

        if (hs_strcmp(ps_format,"QQ") == 0)
            return (li_end_year * 12 + li_end_month) * li_flag / 3;
        else
            return (li_end_year * 12 + li_end_month) * li_flag;

    }

    ltm_begdate.tm_year = li_beg_year - 1900;
    ltm_begdate.tm_mon = li_beg_month - 1;
    ltm_begdate.tm_mday = li_beg_day;
    ltm_enddate.tm_year = li_end_year - 1900;
    ltm_enddate.tm_mon = li_end_month - 1;
    ltm_enddate.tm_mday = li_end_day;
    
    lt_begdate = mktime(&ltm_begdate);
    if (lt_begdate == -1)
        return -1;
    lt_enddate = mktime(&ltm_enddate);
    if (lt_enddate == -1)
        return -1;

    lt_enddate = lt_enddate - lt_begdate;
    
    li_ret = lt_enddate / 86400;
    
    if (hs_strcmp(ps_format,"WW") == 0) 
       return li_ret * li_flag / 7;
    else
       return li_ret * li_flag;
    
}

/*######################### C++函数 #####################################*/

/*==========================================================
 * Function   : conversion
 * Description: 字符转换
 * Input      : char  p_var  把'\0'转换成空格
 * Output     : char  p_var  
 * Return     : char  转换后字符
 *              
 * Author     : zhouwm
 * Date       : 2004/08/19
 ==========================================================*/
char conversion(char p_var)
{
  return p_var == 0 ? 32 : p_var;
}

/*==========================================================
 * Function   : conversion
 * Description: 字符转换
 * Input      : char *p_var  把'\0'转换成空格
 * Output     : char *p_var  
 * Return     : char *       转换后字符
 *              
 * Author     : zhouwm
 * Date       : 2004/08/19
 ==========================================================*/
char * conversion(char * p_var)
{

  if (p_var == 0)
    return (char *)" ";
  else
    return * p_var == 0 ? (char *)" " : p_var;

}

/*==========================================================
 * Function   : hs_max
 * Description: 取两个整数的最大值
 * Input      : const int i_data1 比较的数字
 *            : const int i_data2 比较的数字
 * Output     : 
 * Return     : int 两个整数的最大值
 *              
 * Author     : zhouwm
 * Date       : 2004/08/19
 ==========================================================*/
int hs_max(const int i_data1,const int i_data2)
{
    if (i_data1 > i_data2)
        return i_data1;
    else
        return i_data2;
}

/*==========================================================
 * Function   : hs_max
 * Description: 取两个浮点数的最大值
 * Input      : const double d_data1  比较的数字
 *            : const double d_data2  比较的数字
 * Output     : 
 * Return     : double 两个浮点数的最大值
 *              
 * Author     : zhouwm
 * Date       : 2004/08/19
 ==========================================================*/
double hs_max(const double d_data1,const double d_data2)
{
    if (d_data1 > d_data2)
        return d_data1;
    else
        return d_data2;
}

/*==========================================================
 * Function   : hs_min
 * Description: 取两个整数的最小值
 * Input      : const int i_data1 比较的数字
 *            : const int i_data2 比较的数字
 * Output     : 
 * Return     : int 两个整数的最小值
 *              
 * Author     : zhouwm
 * Date       : 2004/09/20
 ==========================================================*/
int hs_min(const int i_data1,const int i_data2)
{
    if (i_data1 < i_data2)
        return i_data1;
    else
        return i_data2;
}

/*==========================================================
 * Function   : hs_min
 * Description: 取两个浮点数的最小值
 * Input      : const double d_data1 比较的数字
 *            : const double d_data2 比较的数字
 * Output     : 
 * Return     : double 两个浮点数的最小值
 *              
 * Author     : zhouwm
 * Date       : 2004/09/20
 ==========================================================*/
double hs_min(const double d_data1,const double d_data2)
{
    if (d_data1 < d_data2)
        return d_data1;
    else
        return d_data2;
}



/*==========================================================
 * Function   : isnumeric
 * Description: 判断字符串是否为数字
 * Input      : char *str   输入字符串
 * Output     : 
 * Return     : 0   字符串为数字
 *              1   字符串不为数字
 * Author     : 赖沙
 * Date       : 2007/02/28
 ==========================================================*/
int isnumeric(const char *str)
{
   if (isnull(str) == 0)
   {
      return(1);
   }
   for (int i=0;i<=length(str)-1;i++)
   {
      if (str[i] > 57 || str[i] < 48)   
      {
          return(1);      
      }
   }
   
   return(0);
}

/*==========================================================
 * Function   : hs_subinstr
 * Description: 查找子字符串在源字符串中是否存在，
 *              例如"24"在"1234"中是存在的，或者"2,4"在"1,2,3,4"中也是存在的
 * Input      : char *ps_source   源字符串
 *            : char *ps_subsrc   子字符
 * Output     : char *ps_part     字符串是以什么分割的
 * Return     : > 0               成功
 *              <= 0              失败          
 * Author     : zhouwm
 * Date       : 2007/09/29
 ==========================================================*/
int hs_subinstr(const char *ps_source,const char *ps_subsrc,const char* ps_part)
{
   char ls_source[8192] = {0};
   char ls_subsrc[8192] = {0};
   char ls_part[10] = {0};
   char ls_temp[8192] = {0};
   char lc_temp = ' ';
   int li_len = 0,li_pos = 0;

   hs_strcpy(ls_source,ps_source);
   hs_strcpy(ls_subsrc,ps_subsrc);
   hs_strcpy(ls_part,ps_part);

   if (isnull(trim(ls_source)) == 0)
      return 0;
   if (isnull(trim(ls_subsrc)) == 0)
      return 0;
   trim(ls_part);
   
   if (isnull(ls_part) == 0)
   {
      li_len = length(ls_subsrc);
      while (li_pos < li_len)
      {
         lc_temp = ls_subsrc[li_pos];
         if (instr(ls_source,lc_temp) <= 0)
           return 0;
         li_pos = li_pos + 1;
      }
   }
   else
   {
      hs_strlrcpy(ls_source,ls_part,ls_part);
      li_pos = hs_strstr(ls_subsrc,ls_part);
      if (li_pos <= 0)
      {
         hs_strlrcpy(ls_subsrc,ls_part,ls_part);
         if (hs_strstr(ls_source,ls_subsrc) <= 0)
           return 0;
      }
      
      while (li_pos > 0)
      {
         substr(ls_subsrc,1,li_pos - 1,ls_temp);
         hs_strlrcpy(ls_temp,ls_part,ls_part);
         if (hs_strstr(ls_source,ls_temp) <= 0)
            return 0;
          
         substr(ls_subsrc,li_pos + 1,length(ls_subsrc) - li_pos,ls_temp);
         hs_strcpy(ls_subsrc,ls_temp);
         
         li_pos = hs_strstr(ls_subsrc,ls_part);
         if (li_pos <= 0)
         {
            hs_strlrcpy(ls_subsrc,ls_part,ls_part);
            if (hs_strstr(ls_source,ls_subsrc) <= 0)
               return 0;
         }
      }
   }
   return 1;
}

/*==========================================================
 * Function   : hs_snprintf
 * Description: 替换C++中的snprintf以及详细设计里面的sprintf写法
 *              支持最大堆栈为18960，如果超过就会提示超长后进行截取
 * Input      : char *string      赋值的目标字符串
 *            : size_t   count    字符串长度
 *            : const char *format可选便利
 * Output     : 
 * Return     : >= 0             成功
 *              < 0              失败			
 * Author     : zhouwm
 * Date       : 2007/12/04
 ==========================================================*/
int hs_snprintf(char   *string,size_t   count, const   char   *format,...)
{
	char ls_temp[TEMP_STR_MAX_LEN]={0};
	va_list   arglist;   
         int ret = 0;
         
	if (count > TEMP_STR_MAX_LEN)
	{
       printf("[========== string length %d beyond max length %d =========]\n",count,TEMP_STR_MAX_LEN);
	   count = TEMP_STR_MAX_LEN;
    }

	va_start(arglist,   format);
	
	ret = vsnprintf(ls_temp,count,format,arglist);

	va_end(arglist);
	
	strncpy(string,ls_temp,count - 1);

	return ret;
}

/*==========================================================
 * Function   : hs_strstrsoh
 * Description: 在源字符串中找到子串出现的位置中间有几个间隔符块(,,)
 * Input      : const char *src   输入源字符串
 *				const char *substr	输入子串
 *				const char soh		间隔符
 * Output     : 
 * Return     : -1      源字符串或子串为空。
 *				-2    在源字符串中找不到子串。
 * example    : 源串: 11,22,33,44,55 子串为33, 分隔符为','，那么返回的结果为3
 * Author     : wangly
 * Date       : 2008/11/23
 ==========================================================*/
int   hs_strstrsoh(const char * src,const char *substr,const char soh)
{
    char *s_tmp,*s_cur,*s_bef;
	int i_num = 1;

    if ((isnull(src) == 0) || (isnull(substr) == 0))
        return -1;
    
	s_bef = (char *)src;
	
	while (isnull(s_bef) == 1)
	{
		s_tmp = strstr(s_bef,substr);
		if (isnull(s_tmp) == 0)
			return -2;
		
		if ((s_tmp == src)||(*(s_tmp - 1) == soh))
		{
			if (strlen(s_tmp) == strlen(s_tmp))
				break;
			
			if (*(s_tmp + strlen(substr)) == soh)
				break;
		}
		
		s_bef = s_tmp + strlen(substr);
	}
	
	if (isnull(s_bef) == 0)
		return -2;
	
	if (s_tmp == src)
		return 1;
	
	s_cur = (char *)(src+1);//从第二个开始找。;
	
	while (s_cur != s_tmp)
	{
		if (*s_cur == soh)
			i_num++;
		
		s_cur++;
	}
	
    return i_num;
}

/*==========================================================
 * Function   : hs_strncpysoh
 * Description: 从一个字串中取指定间隔符之前的字符串。
 * Input      : const char *src        源字串
 *              int        sohpos      该子串在源字串中的第几个字串，第一个如果是问隔符则忽略，从1开始
 *              int        maxlen      想要得到子串的最大长度。maxlen需要包括字符串最后一个结束符，即\0。
 *              char *sub  获得的子串
 *				char soh   间隔符。
 * Output     : 
 * Return     : 返回子串长度。
 *				小于0
 *				-1       输入参数为空或是maxlen和sohpos<=0
 *				-2		找不到第sohpos个间隔符
 *              -3      找到的子串长度大于maxlen
 *				-4		用于输出的子串为空。
 *
 *
 * example    : 源串: 11,22,33,44,55 指定位置为2 长度为2 获得的子串为22
 * Author     : wangly
 * Date       : 2008/11/13
 * Modify	
 *
 ==========================================================*/
int hs_strncpysoh(const char *src,int sohpos,int maxlen,char *sub,char soh)
{
	if (sub == NULL)
		return -4;
	
	*sub = '\0';
	
	if(isnull(src) == 0 || maxlen <= 0 || sohpos <= 0)
		return -1;
	
	int i_loop = 0,i_srclen = 0 ,icursoh = 1;
	
	char *pcur = (char *)src;
	if (*pcur == soh)
		pcur++;
	
	i_srclen = strlen(pcur);
	
	if (sohpos > 1)
	{
		for(i_loop = 0;i_loop < i_srclen;i_loop++)
		{
			if (*(pcur + i_loop) == soh)
			{
				icursoh++;
				if (icursoh == sohpos)
				{
					break;
				}
			}
		}
		if (i_loop >= i_srclen)
			return -2;
		
		pcur = pcur + i_loop + 1;
	}
	
	i_srclen = strlen(pcur);
	
	for(i_loop = 0;i_loop < i_srclen && i_loop < maxlen - 1;i_loop++)
	{
		if(*pcur == soh)
			break;
		*(sub++) = *(pcur++);
	}
	
	*sub = '\0';//结束符。
	if (i_loop >= (maxlen-1))
		return -3;
	
	return i_loop;
}

/*==========================================================
 * Function   : hs_sohnum
 * Description: 从指定字符串中找有多少个间隔数据块，最后如果不是问隔符也算一个。
 * Input      : const char *src       源字串
 *				char soh	间隔符。
 * Output     : 
 * Return     : 返回间隔符出现个数。
 *				0		间隔符没有出现。
 *				-1       输入参数为空
 *
 *				
 * example    : 源串: 11,22,33,44,55 分隔符为','，那么返回的结果为5
 * Author     : wangly
 * Date       : 2008/11/13
 * Modify	
 *
 ==========================================================*/
int hs_sohnum(const char *src,char soh)
{
	if(isnull(src) == 0)
		return -1;
	
	int i_sohnum = 0,i_srclen = 0,i_loop=0;
	char *cur = (char *)src;
	
	if(*cur == soh)
		cur++;
	
	i_srclen = length(cur);
	
	for(i_loop = 0 ; i_loop < i_srclen ; i_loop++)
	{
		if(*(cur+i_loop) == soh)
			i_sohnum++;
	}
	if(i_sohnum == 0)
		return 0;
	
	if(*(cur + i_loop - 1) != soh)
		i_sohnum++;
	
	return i_sohnum;
}

/*==========================================================
 * Function   : hs_timediff
 * Description: 取两个时间的差值
 * Input      : int   pi_begdate     开始日期（格式为：YYYYMMDD）
 *            : int   pi_begtime     开始时间（格式为：HH24MISS）
 *            : int   pi_enddate     结束日期（格式为：YYYYMMDD）
 *            : int   pi_endtime     结束时间（格式为：HH24MISS）
 *            : char *ps_format      比较格式
 *                                   HH: 返回值以小时为单位
 *                                   MI: 返回值以分钟为单位
 *                                   SS: 返回值以秒为单位
 * Output     : int                  时间差值
 * Return     : >=0                 成功
 *              -1                失败          
 * Author     : zhouwm
 * Date       : 2010/07/21
 ==========================================================*/
int hs_timediff(const int pi_begdate,const int pi_begtime,const int pi_enddate,const int pi_endtime,char * ps_format)
{
    int li_beg_year=0,li_beg_month=0,li_beg_day=0,li_begdate=0,li_begtime=0,li_beg_hour=0,li_beg_minute=0,li_beg_second=0;
    int li_end_year=0,li_end_month=0,li_end_day=0,li_enddate=0,li_endtime=0,li_end_hour=0,li_end_minute=0,li_end_second=0;
	int li_flag=1,li_ret=0;
    time_t  lt_begdate,lt_enddate;
    struct tm ltm_begdate,ltm_enddate;
    int month_day[] = {31,28,31,30,31,30,31,31,30,31,30,31};
    
    memset(&lt_begdate,0,sizeof(lt_begdate));
    memset(&lt_enddate,0,sizeof(lt_enddate));
    memset(&ltm_begdate,0,sizeof(ltm_begdate));
    memset(&ltm_enddate,0,sizeof(ltm_enddate));

    // 判断输入参数是否有效
    if ((hs_strcmp(ps_format,"HH") == 0
      && hs_strcmp(ps_format,"MI") == 0
      && hs_strcmp(ps_format,"SS") == 0) 
      || pi_begdate <= 0 
      || pi_enddate <= 0
	  || pi_begtime < 0
	  || pi_endtime < 0)
      return -1;

	// 判断开始日期和结束日期大小
    if ((pi_enddate < pi_begdate) || (pi_enddate == pi_begdate && pi_endtime < pi_begtime))
    {
    	/*
        li_flag = -1;
        li_begdate = pi_enddate;
        li_enddate = pi_begdate;
		li_begtime = pi_endtime;
        li_endtime = pi_begtime;
        */
        
        ///当结束时间小于开始时间时，也返回-1，表示出错。
        return -1;
    }
    else if ((pi_enddate > pi_begdate) || (pi_enddate == pi_begdate && pi_endtime > pi_begtime))
    {
        li_begdate = pi_begdate;
        li_enddate = pi_enddate;
		li_begtime = pi_begtime;
		li_endtime = pi_endtime;
    }
    else
    {
        return 0;
    }
  
    li_beg_year = li_begdate / 10000;
    li_beg_month = li_begdate % 10000 / 100;
    li_beg_day = (li_begdate % 10000) % 100;
    li_beg_hour = li_begtime / 10000;
	li_beg_minute = li_begtime % 10000 / 100;
	li_beg_second = (li_begtime % 10000) % 100;

    li_end_year = li_enddate / 10000;
    li_end_month = li_enddate % 10000 / 100;
    li_end_day = (li_enddate % 10000) % 100;
    li_end_hour = li_endtime / 10000;
	li_end_minute = li_endtime % 10000 / 100;
	li_end_second = (li_endtime % 10000) % 100;
    
	// 日期合法化判断
    if    ((li_beg_year < 0) || (li_beg_month <= 0 ) || (li_beg_month >12) 
        || (li_beg_day <= 0) || (li_beg_day > 31)
		|| (li_beg_hour < 0) || (li_beg_hour > 23)
		|| (li_beg_minute < 0) || (li_beg_minute > 59)
		|| (li_beg_second < 0) || (li_beg_second > 59)
        || (li_end_year < 0) || (li_end_month <= 0 ) || (li_end_month >12) 
        || (li_end_day <= 0) || (li_end_day > 31)
		|| (li_end_hour < 0) || (li_end_hour > 23)
		|| (li_end_minute < 0) || (li_end_minute > 59)
		|| (li_end_second < 0) || (li_end_second > 59))
        return -1;
    
    // 开始日合法化判断
    if( (li_beg_day > month_day[li_beg_month - 1]) )
    {
        // 闰年2月天数判断
        if( ((li_beg_year%4 == 0)&&(li_beg_year%100 != 0)) || (li_beg_year%400 == 0) )
        {
            if( (li_beg_month == 2) && (li_beg_day > 29)  )
                return -1;
        }
        else
            return -1;
    }
    
    

    // 结束日合法化判断
    if( (li_end_day > month_day[li_end_month - 1]) )
    {
        // 闰年2月天数判断
        if( ((li_end_year%4 == 0)&&(li_end_year%100 != 0)) || (li_end_year%400 == 0) )
        {
            if( (li_end_month == 2) && (li_end_day > 29)  )
                return -1;
        }
        else
            return -1;
    }

	ltm_begdate.tm_year = li_beg_year - 1900;
    ltm_begdate.tm_mon = li_beg_month - 1;
    ltm_begdate.tm_mday = li_beg_day;
	ltm_begdate.tm_hour = li_beg_hour;
	ltm_begdate.tm_min = li_beg_minute;
	ltm_begdate.tm_sec = li_beg_second;
    ltm_enddate.tm_year = li_end_year - 1900;
    ltm_enddate.tm_mon = li_end_month - 1;
    ltm_enddate.tm_mday = li_end_day;
	ltm_enddate.tm_hour = li_end_hour;
	ltm_enddate.tm_min = li_end_minute;
	ltm_enddate.tm_sec = li_end_second;
    
    lt_begdate = mktime(&ltm_begdate);
    if (lt_begdate == -1)
        return -1;
    lt_enddate = mktime(&ltm_enddate);
    if (lt_enddate == -1)
        return -1;

    lt_enddate = lt_enddate - lt_begdate;
    
    if (hs_strcmp(ps_format,"HH") == 0)
       lt_enddate = lt_enddate / 60 / 60;
    else if (hs_strcmp(ps_format,"MI") == 0)
       lt_enddate = lt_enddate / 60;

	return lt_enddate * li_flag;
}

/*==========================================================
 * Function   : hs_validdate
 * Description: 检查日期有效性
 * Input      : int   pi_validdate     日期（格式为：YYYYMMDD）
 * Return     : 0                 成功
 *              -1                失败          
 * Author     : zhouwm
 * Date       : 2010/07/21
 ==========================================================*/
int hs_validdate(const int pi_validdate)
{
   	int li_date_year=0,li_date_month=0,li_date_day=0,li_validdate=0;
	int li_flag=1,li_ret=0;
    time_t  lt_validdate;
    struct tm ltm_validdate;
    int month_day[] = {31,28,31,30,31,30,31,31,30,31,30,31};
    
    memset(&lt_validdate,0,sizeof(lt_validdate));
    memset(&ltm_validdate,0,sizeof(ltm_validdate));
    
    li_validdate = pi_validdate;

    li_date_year = li_validdate / 10000;
    li_date_month = li_validdate % 10000 / 100;
    li_date_day = (li_validdate % 10000) % 100;
    
	// 日期合法化判断
    if    ((li_date_year < 0) || (li_date_month <= 0 ) || (li_date_month >12) 
        || (li_date_day <= 0) || (li_date_day > 31))
        return -1;
    
    // 开始日合法化判断
    if( (li_date_day > month_day[li_date_month - 1]) )
    {
        // 闰年2月天数判断
        if( ((li_date_year%4 == 0)&&(li_date_year%100 != 0)) || (li_date_year%400 == 0) )
        {
            if( (li_date_month == 2) && (li_date_day > 29)  )
                return -1;
        }
        else
            return -1;
    }
    
	ltm_validdate.tm_year = li_date_year - 1900;
    ltm_validdate.tm_mon = li_date_month - 1;
    ltm_validdate.tm_mday = li_date_day;
    
    lt_validdate = mktime(&ltm_validdate);
    if (lt_validdate == -1)
        return -1;

	return 0;
}

/*==========================================================
 * Function   : hs_validtime
 * Description: 检查时间有效性
 * Input      : int   pi_validtime     日期（格式为：HH24MISS）
 * Return     : 0                 成功
 *              -1                失败          
 * Author     : zhouwm
 * Date       : 2010/07/21
 ==========================================================*/
int hs_validtime(const int pi_validtime)
{
   	int li_date_hour=0,li_date_minute=0,li_date_second=0,li_validtime=0;
	int li_flag=1,li_ret=0;
    time_t  lt_validtime;
    struct tm ltm_validtime;
    //int month_day[] = {31,28,31,30,31,30,31,31,30,31,30,31};
    
    memset(&lt_validtime,0,sizeof(lt_validtime));
    memset(&ltm_validtime,0,sizeof(ltm_validtime));
    
    li_validtime = pi_validtime;

    li_date_hour = li_validtime / 10000;
    li_date_minute = li_validtime % 10000 / 100;
    li_date_second = (li_validtime % 10000) % 100;
    
	// 日期合法化判断
    if    ((li_date_hour < 0) || (li_date_hour > 23)
		|| (li_date_minute < 0) || (li_date_minute > 59)
		|| (li_date_second < 0) || (li_date_second > 59))
        return -1;
    
	ltm_validtime.tm_year = 2000 - 1900;
    ltm_validtime.tm_mon = 1;
    ltm_validtime.tm_mday = 1;

    ltm_validtime.tm_hour = li_date_hour;
	ltm_validtime.tm_min = li_date_minute;
	ltm_validtime.tm_sec = li_date_second;
    
    lt_validtime = mktime(&ltm_validtime);
    if (lt_validtime == -1)
        return -1;

	return 0;
}

/*==========================================================
* Function   : HexToStr
* Description: 用于把16进制数转化为字符
* Input      : const char *s_src 传入密文
* Output     : char *d_dest      解密密码
* Return     : 0 成功 <0 失败
* Author     : wanglb,zhouwm
* Date       : 2008/09/12
==========================================================*/
int HexToStr(char *d_dest,const char *s_src)
{
	unsigned dwCharValue; 
	char szTemp[3] = {0};
	char *pTemp = szTemp;
	
	if(isnull(s_src) == 0)
		return -1;    
	
	for(int i = 1;i <= int(length(s_src)/2);i++)
	{
		*pTemp = s_src[2*i-2];
		pTemp++;
		
		*pTemp = s_src[2*i-1];
		pTemp++;
		
		*pTemp = '\0';
		dwCharValue = TransChar(szTemp);
		
		*(d_dest++) = (char)dwCharValue;
		pTemp = szTemp;
	}
	
	*d_dest = '\0';
	
	return 0;
}

/*==========================================================
* Function   : StrToHex
* Description: 用于把字符串转换为16进制
* Input      : char *sz_src 源字符串
*              char *sz_dest 转换后的16进制字符串
* Output     : char *sz_dest 转换后的16进制字符串
* Return     : char *
* Author     : yangsb
* Date       : 2009/05/23
==========================================================*/
char * StrToHex(char *sz_dest,const char *sz_src)
{
	unsigned char wTemp;
	int iLen,i;
	char szTemp[3] = {0};
	
	if(isnull(sz_src) == 0)
		return NULL;
	
	memset(sz_dest,'\0',sizeof(sz_dest));
	iLen = length(sz_src);
	for(i=0;i<iLen;i++)
	{
		wTemp = (unsigned char)sz_src[i];
		sprintf(szTemp, "%02X", (int)wTemp);
		strcat(sz_dest,szTemp);
	}
	return sz_dest;
}

//20080912 王力波,周伟明 以下为新增用于第三方授权操作解密及校验的函数，周伟明对函数进行调整 begin
/*==========================================================
* Function   : TransChar
* Description: 16进制字符转换成10进制数字
* Input      : char *pCharValue 16进制字符
* Output     : 
* Return     : 返回十进制数字
* Author     : wanglb,zhouwm
* Date       : 2008/09/12
==========================================================*/
int TransChar(char *pCharValue)
{
	char s[3] = {0};
	hs_strcpy(s,pCharValue);
	int n = 0; 
	for(int i = 0;s[i] != '\0';i++) 
	{ 
		if(s[i] >= '0' && s[i] <= '9') 
			n = n * 16 + s[i] - '0'; 
		
		if(s[i] >= 'a' && s[i] <= 'f') 
			n = n * 16 + s[i] - 'a' + 10; 
		
		if(s[i] >= 'A' && s[i] <= 'F') 
			n = n * 16 + s[i] - 'A' + 10; 
	} 
	
	return n;
}

