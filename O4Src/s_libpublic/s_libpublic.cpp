/*
 * Program: s_libpublic.cpp
 * Author : ��ΰ��.
 * Date   : 2009/01/20.
 * Notes  : �ṩϵͳ��������
 * Modify : �汾       �޸�����   �޸���         �޸ĵ�       �޸�˵��
 *          V8.0.6.0   20100614    ��Ԫ��         �ڲ�         ����ҵ����Ӫƽ̨V2.0��Ŀ2011���߽���
 *			    V8.0.5.2   20110228   ������         20110301024  ��StrToHex��HexToStr��TransChar��s_glbfunction_or�Ƶ����
 *          V8.0.5.1   20100721   ��ΰ��         �ڲ�         ��������hs_timediff��ʱ���ֵ���㣩
 *                                                                    hs_validdate��������Ч�Լ�飩
 *                                                                    hs_validtime��ʱ����Ч�Լ�飩
 *          V8.0.5.0   20100414   ��ΰ��         �ڲ�         ����
 *          V8.0.4.0   20090926   ��ΰ��         �ڲ�         ����
 *          V8.0.3.1   20090804   ��ΰ��         �ڲ�         hs_datadiff(begin_date,end_date)�޸�if( (begin_day > month_day[end_mon - 1]) )�޸�Ϊif( (end_day > month_day[end_mon - 1]) )
 *          V8.0.3.0   20090626   ��ΰ��         �ڲ�         ���
 *          V8.0.2.0   20090420   ��ΰ��         �ڲ�         ���
 *          V8.0.1.0   20090120   ��ΰ��         �ڲ�         ���
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
 * Description: ��ȡ�汾��Ϣ
 * Input      : 
 * Output     : 
 * Return     : so�汾��Ϣ
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
 * Description: ��֤�ַ����Ƿ�Ϊ��
 * Input      : const char *d_str   �����ַ���
 * Output     : 
 * Return     : 0       �ַ���Ϊ��
 *         1    �ַ�����Ϊ��
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
 * Description: ȡ�ַ�������
 *              ��Oracle��length������������
 * Input      : char *str   �����ַ���
 * Output     : 
 * Return     : >0      �ַ�������
 *              0       �ַ���Ϊ��
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
 * Description:��ȥ�ַ�����ǰ��ո�,��Oracle��Trim������������
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
 * Description:��ȥ�ַ�����ǰ��ո�,��Oracle��Trim������������
 *             ���trim��Ϊ������һ���ո�
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
 * Description: �ַ����滻,ע������Ŀ���ַ������Ȳ�Ҫ̫�̣������滻��Խ��
 * Input      : char       *dest   Ŀ�괮
 *              const char *src    Դ�ַ���
 *              const char *s_old  ���ַ���
 *              const char *s_new  ���ַ���
 * Output     : 
 * Return     : 0       �ɹ�
 *              -1      ����Ϊ��
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
 * Description: ɾǰ������ָ�����ַ�
 * Input      : char       *dest     Ŀ�괮
 *              const char *src      Դ�ַ���
 *              const char c_char    ɾ���ַ�
 * Output     : 
 * Return     : 0       �ɹ�
 *              -1      ����Ϊ��
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
 * Description: ��ɾ�ַ�����ָ�����ַ�
 * Input      : char       *dest     Ŀ�괮
 *              const char *src      Դ�ַ���
 *              const char c_char    ɾ���ַ�
 * Output     : 
 * Return     : 0       �ɹ�
 *              -1      ����Ϊ��
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
 * Description: ���ַ�����Oracle��lpad������������,
 *              ����ַ���С��lenֵ�����ַ�c
 * Input      : char *buf �����ַ���
 *              int  len  ���ַ�����ַ����ĳ���
 *              char c    �������ַ�
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
 * Description: �Ҳ��ַ�����Oracle��rpad������������
 *              ����ַ���С��lenֵ���Ҳ��ַ�c
 * Input      : char *buf �����ַ���
 *              int  len  ���ַ�����ַ����ĳ���
 *              char c    �������ַ�
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
 * Description: �����ַ�����Oracle��instr������������
 * Input      : const char * src Դ�ַ���
 *              const char  c    �������ַ�
 * Output     : 
 * Return     : >0      �ɹ�
 *              -1      ����Ϊ��
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
 * Description: �����ַ���
 * Input      : const char * src    Դ�ַ���
 *              const char * substr �������ַ���
 * Output     : 
 * Return     : >0      �ɹ�
 *              -1      ����Ϊ��
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
 * Description: �Ӵ��Ƚ�
 * Input      : const char *s 		Դ�ִ�
 *				int		   pos		���Ӵ���Դ�ִ��е���ʼλ�ã���1��ʼ
 *              int        len 		Ҫ�õ����Ӵ��ĳ���
 *				const char *substr	�Ƚϵ��Ӵ�
 * Output     : 
 * Return     : 0 		�ɹ�
 *				-1		����Ϊ��
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
 * Description: �Ӵ��Ƚ�
 * Input      : const char *s       Դ�ִ�
 *              int        pos      ���Ӵ���Դ�ִ��е���ʼλ�ã���1��ʼ
 *              int        len      Ҫ�õ����Ӵ��ĳ���
 *              const char *sub     �Ƚϵ��Ӵ�
 * Output     : 
 * Return     : 0       �ɹ�
 *              -1      ����Ϊ��
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
 * Description: �ַ����Ƚ�
 * Input      : char *d_str �ַ���
 *              char *s_str �ַ���
 * Output     : 
 * Return     : 0       �ɹ�
 *              -1      ����Ϊ��
*               <>0     �ַ������
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
 * Description: ��һ���ִ����ӵ���һ���ִ�����
 * Input      : char *s_dest Ŀ���ִ������Ӻ����ִ���ŵĵط�
 *              char *s_src  Ҫ���ӵ��ִ�
 * Output     : 
 * Return     : 0       �ɹ�
 *              -1      ����Ϊ��
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
 * Description: �ַ�������
 * Input      : char *d_dest Ŀ���ִ�
 *              char *s_src  Դ�ַ���
 * Output     : 
 * Return     : 0       �ɹ�
 *              -1      ����Ϊ��
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
 * Description: �����ַ�ָ�����ȱȽ�
 * Input      : const char *d_str �Ƚ��ַ���
 *              int        d_len  ָ���Ƚϳ���
 *              const char *s_str Ҫ�Ƚϵ��ַ���
 * Output     : 
 * Return     : 0       �ɹ�
 *              -1      ����Ϊ��
 *              <>0     �ַ�����ͬ
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
 * Description: ָ�����Ƚ�һ���ִ����ӵ���һ���ִ�����
 * Input      : char *s_dest       Ŀ���ִ������Ӻ����ִ���ŵĵط�
 *              char *s_src        Ҫ���ӵ��ִ�
 *              size_t     count   ָ�����ӳ���
 * Output     : 
 * Return     : 0       �ɹ�
 *              -1      ����Ϊ��
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
 * Description: ָ�������ַ�����ֵ
 * Input      : const char *s_dest Ŀ���ִ�
 *              const char *s_src  Դ�ַ���
 *              size_t     count   ָ�����Ƴ���
 * Output     : 
 * Return     : 0       �ɹ�
 *              -1      ����Ϊ��
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
 * Description: �����ַ��Ƚ�
 * Input      : const char *d_dest Ŀ���ִ�
 *              const char *s_src  Դ�ַ���
 *              size_t     count   ָ���Ƚϳ���
 * Output     : 
 * Return     : 0       �ɹ�
 *              -1      ����Ϊ��
*               <>0     �ַ�����ͬ
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
 * Description: �ַ�ת����Сд
 * Input      : char *str �ַ���
 * Output     : 
 * Return     : 0       �ɹ�
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
 * Description: �ַ�ת���ɴ�д
 * Input      : char *str �ַ���
 * Output     : 
 * Return     : 0       �ɹ�
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
 * Description: �ַ������Ҳ��ַ���
 * Input      : char *str         �ַ���
 *            : const void *rstr  ���ַ���
 *            : const void *rstr  �Ҳ��ַ���
 * Output     : 
 * Return     : 0:  �ɹ�
 *              -1: ʧ��
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
 * Description: ���ڼ������
 * Input      : int ��ʼ����,�������� 
 *              �ر�� ���ڲ�����С�ڵ���19700101
 * Output     : 
 * Return     : ���ڼ������
 *              -1      �������ڷǷ�
 * Author     : zhouwm��laisha
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
    
    //zhouwm �޸�
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
    
    //20090804 zhouwm if( (begin_day > month_day[end_mon - 1]) )�޸�Ϊif( (end_day > month_day[end_mon - 1]) )
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
    //zhouwm �޸�

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
 * Description: ���ӻ������Ӧ������
 * Input      : int begin_date ����,n ����,n>0 ��������,n<0, ��������
 *              �ر�� ���ڲ�����С�ڵ���19700101
 * Output     : 
 * Return     : ����
 *              -1      �������ڷǷ�
 * Author     : zhouwm��laisha
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
    
    //zhouwm �޸�
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
    //zhouwm �޸�

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
 * Description: ��ȡ������С�����nλ���������룬ͬoracle�е�round
 * Input      : double f ���븡����,int n��ȡλ��  n>0
 * Output     : 
 * Return     : ��ȡ��ĸ�����
 *              n<0�������븡����
 * Author     : laisha
 * Date       : 2004/08/19
 ==========================================================*/
long double hs_round(long double f,const long int n)
{
  long double f1,f2,n1;
  int li=1;
  
  if (n < 0)
     return f;
// zhouwm 20060107 ����ʱ�ᴦ������
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
 * Description: ��ȡ������С�����nλ��ĩλ��ȥ��ͬoracle�е�trunc
 * Input      : double f ���븡����,int n��ȡλ��  n>0
 * Output     : 
 * Return     : ��ȡ��ĸ�����
 *              n<0�������븡����
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
 * Description: ����ת�����ַ���
 * Input      : char *buf  ת�����ַ�
 *              long data  ��ת������
 * Output     : 
 * Return     : char* �ַ���
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
 * Description: ������ת�����ַ�
 * Input      : char    *buf  ת�����ַ���
 *              double  data  ��ת��������
 * Output     : 
 * Return     : char* �ַ���
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
 * Description: ��ȡ�ַ���
 * Input      : char *p_source_string  ԭ�ַ���
 *            : int   p_get_length     ȡԭ�ַ�������
 * Output     : char *p_dest_string    Ŀ���ַ���
 * Return     : 0                 �ɹ�
 *              -1                ʧ��
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
 * Description: ��ȡ�ַ���
 * Input      : char *p_source_string  ԭ�ַ���
 *            : int   p_get_length     ȡԭ�ַ�������
 * Output     : char *p_dest_string    Ŀ���ַ���
 * Return     : 0                 �ɹ�
 *              -1                ʧ��          
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
 * Description: ȡ��ǰ����
 * Input      : 
 * Output     : int               ��ǰ���ڣ���ʽΪYYYYMMDD
 * Return     : 0                 �ɹ�
 *              -1                ʧ��          
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
 * Description: ȡ��ǰ����
 * Input      : int *pi_date      ��ǰ���ڣ���ʽΪYYYYMMDD
 *              int *pi_time      ����ʵ�ʣ���ʽΪHHMMSS
 * Output     : int               
 * Return     : 0                 �ɹ�
 *              -1                ʧ��          
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
 * Description: ȡ�������ڵĲ�ֵ
 * Input      : int   pi_begdate     ��ʼ���ڣ���ʽΪ��YYYYMMDD��
 *            : int   pi_enddate     �������ڣ���ʽΪ��YYYYMMDD��
 *            : char *ps_format      �Ƚϸ�ʽ
 *                                   YY: ��
 *                                   QQ: ����
 *                                   MM: ��
 *                                   WW: ��
 *                                   DD: ��
 * Output     : int                  ���ڲ�ֵ
 * Return     : 0                 �ɹ�
 *              -1                ʧ��          
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

    // �ж���������Ƿ���Ч
    if ((hs_strcmp(ps_format,"YY") == 0
      && hs_strcmp(ps_format,"QQ") == 0
      && hs_strcmp(ps_format,"MM") == 0
      && hs_strcmp(ps_format,"WW") == 0
      && hs_strcmp(ps_format,"DD") == 0) 
      || pi_begdate <= 0 
      || pi_enddate <= 0)
      return -1;
    
    // �жϿ�ʼ���ںͽ������ڴ�С
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
    
    // ���ںϷ����ж�
    if((li_beg_year < 0) || (li_beg_month <= 0 ) || (li_beg_month >12) 
        || (li_beg_day <= 0) || (li_beg_day > 31) 
        || (li_end_year < 0) || (li_end_month <= 0 ) || (li_end_month >12) 
        || (li_end_day <= 0) || (li_end_day > 31))
        return -1;
    
    // ��ʼ�պϷ����ж�
    if( (li_beg_day > month_day[li_beg_month - 1]) )
    {
        // ����2�������ж�
        if( ((li_beg_year%4 == 0)&&(li_beg_year%100 != 0)) || (li_beg_year%400 == 0) )
        {
            if( (li_beg_month == 2) && (li_beg_day > 29)  )
                return -1;
        }
        else
            return -1;
    }
    
    // �����պϷ����ж�
    if( (li_end_day > month_day[li_end_month - 1]) )
    {
        // ����2�������ж�
        if( ((li_end_year%4 == 0)&&(li_end_year%100 != 0)) || (li_end_year%400 == 0) )
        {
            if( (li_end_month == 2) && (li_end_day > 29)  )
                return -1;
        }
        else
            return -1;
    }
    
    // �������ֵ
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
    
    // ���ڼ��Ȼ����²�ֵ
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

/*######################### C++���� #####################################*/

/*==========================================================
 * Function   : conversion
 * Description: �ַ�ת��
 * Input      : char  p_var  ��'\0'ת���ɿո�
 * Output     : char  p_var  
 * Return     : char  ת�����ַ�
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
 * Description: �ַ�ת��
 * Input      : char *p_var  ��'\0'ת���ɿո�
 * Output     : char *p_var  
 * Return     : char *       ת�����ַ�
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
 * Description: ȡ�������������ֵ
 * Input      : const int i_data1 �Ƚϵ�����
 *            : const int i_data2 �Ƚϵ�����
 * Output     : 
 * Return     : int �������������ֵ
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
 * Description: ȡ���������������ֵ
 * Input      : const double d_data1  �Ƚϵ�����
 *            : const double d_data2  �Ƚϵ�����
 * Output     : 
 * Return     : double ���������������ֵ
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
 * Description: ȡ������������Сֵ
 * Input      : const int i_data1 �Ƚϵ�����
 *            : const int i_data2 �Ƚϵ�����
 * Output     : 
 * Return     : int ������������Сֵ
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
 * Description: ȡ��������������Сֵ
 * Input      : const double d_data1 �Ƚϵ�����
 *            : const double d_data2 �Ƚϵ�����
 * Output     : 
 * Return     : double ��������������Сֵ
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
 * Description: �ж��ַ����Ƿ�Ϊ����
 * Input      : char *str   �����ַ���
 * Output     : 
 * Return     : 0   �ַ���Ϊ����
 *              1   �ַ�����Ϊ����
 * Author     : ��ɳ
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
 * Description: �������ַ�����Դ�ַ������Ƿ���ڣ�
 *              ����"24"��"1234"���Ǵ��ڵģ�����"2,4"��"1,2,3,4"��Ҳ�Ǵ��ڵ�
 * Input      : char *ps_source   Դ�ַ���
 *            : char *ps_subsrc   ���ַ�
 * Output     : char *ps_part     �ַ�������ʲô�ָ��
 * Return     : > 0               �ɹ�
 *              <= 0              ʧ��          
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
 * Description: �滻C++�е�snprintf�Լ���ϸ��������sprintfд��
 *              ֧������ջΪ18960����������ͻ���ʾ��������н�ȡ
 * Input      : char *string      ��ֵ��Ŀ���ַ���
 *            : size_t   count    �ַ�������
 *            : const char *format��ѡ����
 * Output     : 
 * Return     : >= 0             �ɹ�
 *              < 0              ʧ��			
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
 * Description: ��Դ�ַ������ҵ��Ӵ����ֵ�λ���м��м����������(,,)
 * Input      : const char *src   ����Դ�ַ���
 *				const char *substr	�����Ӵ�
 *				const char soh		�����
 * Output     : 
 * Return     : -1      Դ�ַ������Ӵ�Ϊ�ա�
 *				-2    ��Դ�ַ������Ҳ����Ӵ���
 * example    : Դ��: 11,22,33,44,55 �Ӵ�Ϊ33, �ָ���Ϊ','����ô���صĽ��Ϊ3
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
	
	s_cur = (char *)(src+1);//�ӵڶ�����ʼ�ҡ�;
	
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
 * Description: ��һ���ִ���ȡָ�������֮ǰ���ַ�����
 * Input      : const char *src        Դ�ִ�
 *              int        sohpos      ���Ӵ���Դ�ִ��еĵڼ����ִ�����һ��������ʸ�������ԣ���1��ʼ
 *              int        maxlen      ��Ҫ�õ��Ӵ�����󳤶ȡ�maxlen��Ҫ�����ַ������һ������������\0��
 *              char *sub  ��õ��Ӵ�
 *				char soh   �������
 * Output     : 
 * Return     : �����Ӵ����ȡ�
 *				С��0
 *				-1       �������Ϊ�ջ���maxlen��sohpos<=0
 *				-2		�Ҳ�����sohpos�������
 *              -3      �ҵ����Ӵ����ȴ���maxlen
 *				-4		����������Ӵ�Ϊ�ա�
 *
 *
 * example    : Դ��: 11,22,33,44,55 ָ��λ��Ϊ2 ����Ϊ2 ��õ��Ӵ�Ϊ22
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
	
	*sub = '\0';//��������
	if (i_loop >= (maxlen-1))
		return -3;
	
	return i_loop;
}

/*==========================================================
 * Function   : hs_sohnum
 * Description: ��ָ���ַ��������ж��ٸ�������ݿ飬�����������ʸ���Ҳ��һ����
 * Input      : const char *src       Դ�ִ�
 *				char soh	�������
 * Output     : 
 * Return     : ���ؼ�������ָ�����
 *				0		�����û�г��֡�
 *				-1       �������Ϊ��
 *
 *				
 * example    : Դ��: 11,22,33,44,55 �ָ���Ϊ','����ô���صĽ��Ϊ5
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
 * Description: ȡ����ʱ��Ĳ�ֵ
 * Input      : int   pi_begdate     ��ʼ���ڣ���ʽΪ��YYYYMMDD��
 *            : int   pi_begtime     ��ʼʱ�䣨��ʽΪ��HH24MISS��
 *            : int   pi_enddate     �������ڣ���ʽΪ��YYYYMMDD��
 *            : int   pi_endtime     ����ʱ�䣨��ʽΪ��HH24MISS��
 *            : char *ps_format      �Ƚϸ�ʽ
 *                                   HH: ����ֵ��СʱΪ��λ
 *                                   MI: ����ֵ�Է���Ϊ��λ
 *                                   SS: ����ֵ����Ϊ��λ
 * Output     : int                  ʱ���ֵ
 * Return     : >=0                 �ɹ�
 *              -1                ʧ��          
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

    // �ж���������Ƿ���Ч
    if ((hs_strcmp(ps_format,"HH") == 0
      && hs_strcmp(ps_format,"MI") == 0
      && hs_strcmp(ps_format,"SS") == 0) 
      || pi_begdate <= 0 
      || pi_enddate <= 0
	  || pi_begtime < 0
	  || pi_endtime < 0)
      return -1;

	// �жϿ�ʼ���ںͽ������ڴ�С
    if ((pi_enddate < pi_begdate) || (pi_enddate == pi_begdate && pi_endtime < pi_begtime))
    {
    	/*
        li_flag = -1;
        li_begdate = pi_enddate;
        li_enddate = pi_begdate;
		li_begtime = pi_endtime;
        li_endtime = pi_begtime;
        */
        
        ///������ʱ��С�ڿ�ʼʱ��ʱ��Ҳ����-1����ʾ����
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
    
	// ���ںϷ����ж�
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
    
    // ��ʼ�պϷ����ж�
    if( (li_beg_day > month_day[li_beg_month - 1]) )
    {
        // ����2�������ж�
        if( ((li_beg_year%4 == 0)&&(li_beg_year%100 != 0)) || (li_beg_year%400 == 0) )
        {
            if( (li_beg_month == 2) && (li_beg_day > 29)  )
                return -1;
        }
        else
            return -1;
    }
    
    

    // �����պϷ����ж�
    if( (li_end_day > month_day[li_end_month - 1]) )
    {
        // ����2�������ж�
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
 * Description: ���������Ч��
 * Input      : int   pi_validdate     ���ڣ���ʽΪ��YYYYMMDD��
 * Return     : 0                 �ɹ�
 *              -1                ʧ��          
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
    
	// ���ںϷ����ж�
    if    ((li_date_year < 0) || (li_date_month <= 0 ) || (li_date_month >12) 
        || (li_date_day <= 0) || (li_date_day > 31))
        return -1;
    
    // ��ʼ�պϷ����ж�
    if( (li_date_day > month_day[li_date_month - 1]) )
    {
        // ����2�������ж�
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
 * Description: ���ʱ����Ч��
 * Input      : int   pi_validtime     ���ڣ���ʽΪ��HH24MISS��
 * Return     : 0                 �ɹ�
 *              -1                ʧ��          
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
    
	// ���ںϷ����ж�
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
* Description: ���ڰ�16������ת��Ϊ�ַ�
* Input      : const char *s_src ��������
* Output     : char *d_dest      ��������
* Return     : 0 �ɹ� <0 ʧ��
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
* Description: ���ڰ��ַ���ת��Ϊ16����
* Input      : char *sz_src Դ�ַ���
*              char *sz_dest ת�����16�����ַ���
* Output     : char *sz_dest ת�����16�����ַ���
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

//20080912 ������,��ΰ�� ����Ϊ�������ڵ�������Ȩ�������ܼ�У��ĺ�������ΰ���Ժ������е��� begin
/*==========================================================
* Function   : TransChar
* Description: 16�����ַ�ת����10��������
* Input      : char *pCharValue 16�����ַ�
* Output     : 
* Return     : ����ʮ��������
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

