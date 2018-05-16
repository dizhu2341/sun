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

#ifndef _S_LIBPUBLIC_H
#define _S_LIBPUBLIC_H

//20071204 ��ΰ�� ������ʱ�ַ�������󳤶�
#define TEMP_STR_MAX_LEN     18960
#ifdef  _WIN32
  #define vsnprintf _vsnprintf
#endif

//20071207 ��ΰ�� ���Ӱ汾��Ϣ�������
#ifdef OS_UNIX
	#define ASFC_CALL_MODE  
#else
	#define ASFC_CALL_MODE  __stdcall 
#endif

/*
#ifdef	__cplusplus
extern "C" {
#endif
*/

/*############################### C ���� ##################################*/
/*
 * The following functions are defined in the libpublic.c soruce code.
 */

/*==========================================================
 * Function   : length
 * Description: ȡ�ַ�������
 * 			    ��Oracle��length������������
 * Input      : char *str 	�����ַ���
 * Output     : 
 * Return     : >0 		�ַ�������
 *				0		�ַ���Ϊ��
 * Author     : zhouwm
 * Date       : 2004/08/16
 ==========================================================*/
extern int	length(const char *str);

/*==========================================================
 * Function   : isnull
 * Description: ��֤�ַ����Ƿ�Ϊ��
 * Input      : const char *d_str 	�����ַ���
 * Output     : 
 * Return     : 0		�ַ���Ϊ��
 *				1 		�ַ�����Ϊ��
 * Author     : zhouwm
 * Date       : 2004/08/16
 ==========================================================*/
extern int	isnull(const char *d_str);

/*==========================================================
 * Function  : trim
 * Description:��ȥ�ַ�����ǰ��ո�,��Oracle��Trim������������
 * Input     : char *str
 * Output    : char *str
 * Return    : char *str
 * Author    : zhouwm
 * Date      : 2004/08/16
 ==========================================================*/
extern char  *trim(char * );

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
extern char  *trimb(char * );

/*==========================================================
 * Function   : replace
 * Description: �ַ����滻,ע������Ŀ���ַ������Ȳ�Ҫ̫�̣������滻��Խ��
 * Input      : char	   *dest   Ŀ�괮
 *				const char *src    Դ�ַ���
 *				const char *s_old  ���ַ���
 *				const char *s_new  ���ַ���
 * Output     : 
 * Return     : 0 		�ɹ�
 *				-1		����Ϊ��
 * Author     : zhouwm
 * Date       : 2004/08/16
 ==========================================================*/
extern int replace(char *dest,const char *src,const char *old_str,const char *new_str);

/*==========================================================
 * Function   : ldelchar
 * Description: ǰɾ�ַ�
 * Input      : char	   *dest     Ŀ�괮
 *				const char *src      Դ�ַ���
 *				const char c_char    ���ַ�
 * Output     : 
 * Return     : 0 		�ɹ�
 *				-1		����Ϊ��
 * Author     : zhouwm
 * Date       : 2004/12/29
 ==========================================================*/
extern int ldelchar(char *dest,const char *src,const char c_char);

/*==========================================================
 * Function   : rdelchar
 * Description: ��ɾ�ַ�
 * Input      : char	   *dest     Ŀ�괮
 *				const char *src      Դ�ַ���
 *				const char c_char    ���ַ�
 * Output     : 
 * Return     : 0 		�ɹ�
 *				-1		����Ϊ��
 * Author     : zhouwm
 * Date       : 2004/12/29
 ==========================================================*/
extern int rdelchar(char *dest,const char *src,const char c_char);

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
extern char  *rpad(char *buf, int len, char c );

/*==========================================================
 * Function   : lpad
 * Description:	���ַ�����Oracle��lpad������������,
 * 			    ����ַ���С��lenֵ�����ַ�c
 * Input      : char *buf �����ַ���
 *              int	 len  ���ַ�����ַ����ĳ���
 *              char c    �������ַ�
 * Output     : 
 * Return     : char *str
 * Author     : zhouwm
 * Date       : 2004/08/16
 ==========================================================*/
extern char	 *lpad( char *buf, int len, char c );

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
extern int   instr(const char * src,const char c);

/*==========================================================
 * Function   : substr
 * Description: ��һ���ִ��е�ĳ����ʼλ�ÿ�ʼ�õ�һ���Ӵ�
 * Input      : const char *s 		Դ�ִ�
 *				int		   pos		���Ӵ���Դ�ִ��е���ʼλ�ã���1��ʼ
 *              int        len 		Ҫ�õ����Ӵ��ĳ���
 *				const char *substr	��õ��Ӵ�
 * Output     : char *char �Ӵ�
 * Return     : 0 		�ɹ�
 *				-1		����Ϊ��
 * Author     : zhouwm
 * Date       : 2004/08/16
 ==========================================================*/
extern int substr(const char *src,int pos,int len,char *sub);

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
extern int subcmp(const char *src,int pos,int len,const char *sub);

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
extern int   hs_strstr(const char * src,const char *substr);


/*==========================================================
 * Function   : hs_strcmp
 * Description: �ַ����Ƚ�
 * Input      : const char *d_str �ַ���
 *				const char *s_str �ַ���
 * Output     : 
 * Return     : 0 		�ɹ�
 *				-1		����Ϊ��
*				<>0		�ַ������
 * Author     : zhouwm
 * Date       : 2004/08/16
 ==========================================================*/
extern int hs_strcmp(const char *d_str, const char *s_str);

/*==========================================================
 * Function   : hs_strcat
 * Description: ��һ���ִ����ӵ���һ���ִ�����
 * Input      : char *s_dest Ŀ���ִ������Ӻ����ִ���ŵĵط�
 *				char *s_src Ҫ���ӵ��ִ�
 * Output     : 
 * Return     : 0 		�ɹ�
 *				-1		����Ϊ��
 * Author     : zhouwm
 * Date       : 2004/08/16
 ==========================================================*/
extern int hs_strcat(char *s_dest,const char *s_src);

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
extern int hs_strcpy(char *d_dest,const char *s_src);

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
extern int hs_strncmp(const char *d_str, int d_len,const char *s_str);

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
extern int hs_strncat(char *s_dest,const char *s_src,size_t count);

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
extern int hs_strncpy(char * s_dest,const char *s_src,size_t count);

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
extern int hs_memcmp(const char* d_desc,const char * s_src,size_t count);

/*==========================================================
 * Function   : hs_strtolower
 * Description: �ַ�ת����Сд
 * Input      : char *str �ִ���
 * Output     : 
 * Return     : 0 		�ɹ�
 *				-1		����Ϊ��
*				<>0		�ַ�����ͬ
 * Author     : zhouwm
 * Date       : 2004/08/16
 ==========================================================*/
extern int hs_strtolower(char *str);

/*==========================================================
 * Function   : hs_strtoupper
 * Description: �ַ�ת���ɴ�д
 * Input      : char *str �ִ���
 * Output     : 
 * Return     : 0 		�ɹ�
 *				-1		����Ϊ��
 * Author     : zhouwm
 * Date       : 2004/08/16
 ==========================================================*/
extern int hs_strtoupper(char *str);

/*==========================================================
 * Function   : hs_strlrcpy
 * Description: �ַ������Ҳ��ַ���
 * Input      : char *str         �ַ���
 *            : const void *rstr  ���ַ���
 *            : const void *rstr  �Ҳ��ַ���
 * Output     : 
 * Return     : 0:  �ɹ�
 *				-1: ʧ��
 * Author     : zhouwm
 * Date       : 2004/10/11
 ==========================================================*/
extern int hs_strlrcpy(char *str,const char *lstr,const char *rstr);

/*==========================================================
 * Function   : hs_datediff
 * Description: ���ڼ������
 * Input      : int ��ʼ����,��������
 *              �ر�� ���ڲ�����С�ڵ���19700101
 * Output     : 
 * Return     : ���ڼ������
 *				-1		�������ڷǷ�
 * Author     : zhouwm��laisha
 * Date       : 2004/08/19
 ==========================================================*/
extern long hs_datediff(const int begin_date,const int end_date);

/*==========================================================
 * Function   : hs_dateadd
 * Description: ���ӻ������Ӧ������
 * Input      : int begin_date ����,n ����,n>0 ��������,n<0, ��������
 *              �ر�� ���ڲ�����С�ڵ���19700101
 * Output     : 
 * Return     : ����
 *				-1		�������ڷǷ�
 * Author     : zhouwm��laisha
 * Date       : 2004/08/19
 ==========================================================*/
int hs_dateadd(int begin_date,int n);

/*==========================================================
 * Function   : hs_round
 * Description: ��ȡ������С�����nλ���������룬ͬoracle�е�round
 * Input      : double f ���븡����,int n��ȡλ��  n>0
 * Output     : 
 * Return     : ��ȡ��ĸ�����
 *				n<0�������븡����
 * Author     : laisha
 * Date       : 2004/08/19
 ==========================================================*/
extern long double hs_round(long double f,const long int n);

/*==========================================================
 * Function   : hs_trunc
 * Description: ��ȡ������С�����nλ��ĩλ��ȥ��ͬoracle�е�trunc
 * Input      : double f ���븡����,int n��ȡλ��  n>0
 * Output     : 
 * Return     : ��ȡ��ĸ�����
 *				n<0�������븡����
 * Author     : laisha
 * Date       : 2004/08/19
 ==========================================================*/
extern long double hs_trunc(long double f,const long int n);


/*==========================================================
 * Function   : ltoc
 * Description: ����ת�����ַ���
 * Input      : char *buf  ת�����ַ���
 *              long data  ��ת������
 * Output     : 
 * Return     : char* �ַ���
 *				
 * Author     : zhouwm
 * Date       : 2004/08/19
 ==========================================================*/
extern char *ltoc( char *buf, long data );

/*==========================================================
 * Function   : dtostr
 * Description: ������ת�����ַ�
 * Input      : char	*buf  ת�����ַ���
 *              double	data  ��ת��������
 * Output     : 
 * Return     : char* �ַ���
 *				
 * Author     : zhouwm
 * Date       : 2004/08/19
 ==========================================================*/
extern char *dtostr( char *buf, double data );

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
 * Date       : 2004/08/19
 ==========================================================*/
extern int right(const char * s_str,const int len,char * d_str);

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
extern int left(const char * s_str,const int len,char * d_str);

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
extern int hs_getdate();

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
extern int hs_getdatetime(int *pi_date,int *pi_time);


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
extern int hs_datediff(const int pi_begdate,const int pi_enddate,char * ps_format);


/*######################### C++���� #####################################*/

/*==========================================================
 * Function   : conversion
 * Description: �ַ�ת��
 * Input      : char	p_var  ��'\0'ת���ɿո�
 * Output     : char  p_var  
 * Return     : char  ת�����ַ�
 *				
 * Author     : zhouwm
 * Date       : 2004/08/19
 ==========================================================*/
extern char conversion(char p_var);

/*==========================================================
 * Function   : conversion
 * Description: �ַ�ת��
 * Input      : char *p_var  ��'\0'ת���ɿո�
 * Output     : char *p_var  
 * Return     : char *  ת�����ַ�
 *				
 * Author     : zhouwm
 * Date       : 2004/08/19
 ==========================================================*/
extern char * conversion(char * p_var);

/*==========================================================
 * Function   : hs_max
 * Description: ȡ�������������ֵ
 * Input      : const int i_data1
 *            : const int i_data2
 * Output     : 
 * Return     : int �������������ֵ
 *				
 * Author     : zhouwm
 * Date       : 2004/08/19
 ==========================================================*/
extern int hs_max(const int i_data1,const int i_data2);

/*==========================================================
 * Function   : hs_max
 * Description: ȡ���������������ֵ
 * Input      : const double d_data1
 *            : const double d_data2
 * Output     : 
 * Return     : double ���������������ֵ
 *				
 * Author     : zhouwm
 * Date       : 2004/08/19
 ==========================================================*/
extern double hs_max(const double i_data1,const double i_data2);

/*==========================================================
 * Function   : hs_min
 * Description: ȡ������������Сֵ
 * Input      : const int i_data1
 *            : const int i_data2
 * Output     : 
 * Return     : int ������������Сֵ
 *				
 * Author     : zhouwm
 * Date       : 2004/08/19
 ==========================================================*/
extern int hs_min(const int i_data1,const int i_data2);

/*==========================================================
 * Function   : hs_min
 * Description: ȡ��������������Сֵ
 * Input      : const double d_data1
 *            : const double d_data2
 * Output     : 
 * Return     : double ��������������Сֵ
 *				
 * Author     : zhouwm
 * Date       : 2004/08/19
 ==========================================================*/
extern double hs_min(const double d_data1,const double d_data2);

/*==========================================================
 * Function   : isnumeric
 * Description: �ж��ַ����Ƿ�Ϊ����
 * Input      : char *str 	�����ַ���
 * Output     : 
 * Return     : 0 	�ַ���Ϊ����
 *				      1		�ַ�����Ϊ����
 * Author     : ��ɳ
 * Date       : 2007/02/28
 ==========================================================*/
extern int isnumeric(const char *str);

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
extern int hs_subinstr(const char *ps_source,const char *ps_subsrc,const char* ps_part);

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
extern int hs_snprintf(char   *string,size_t   count, const   char   *format,...);

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
extern int   hs_strstrsoh(const char * src,const char *substr,const char soh);

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
extern int hs_strncpysoh(const char *src,int sohpos,int maxlen,char *sub,char soh);

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
extern int hs_sohnum(const char *src,char soh);


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
extern int hs_timediff(const int pi_begdate,const int pi_begtime,const int pi_enddate,const int pi_endtime,char * ps_format);

/*==========================================================
 * Function   : hs_validdate
 * Description: ���������Ч��
 * Input      : int   pi_validdate     ���ڣ���ʽΪ��YYYYMMDD��
 * Return     : 0                 �ɹ�
 *              -1                ʧ��          
 * Author     : zhouwm
 * Date       : 2010/07/21
 ==========================================================*/
extern int hs_validdate(const int pi_validdate);

/*==========================================================
 * Function   : hs_validtime
 * Description: ���ʱ����Ч��
 * Input      : int   pi_validtime     ���ڣ���ʽΪ��HH24MISS��
 * Return     : 0                 �ɹ�
 *              -1                ʧ��          
 * Author     : zhouwm
 * Date       : 2010/07/21
 ==========================================================*/
extern int hs_validtime(const int pi_validtime);

/*
#ifdef	__cplusplus
}
#endif
*/

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
extern char * StrToHex(char *sz_dest,const char *sz_src);

/*==========================================================
* Function   : HexToStr
* Description: ���ڰ�16������ת��Ϊ�ַ�
* Input      : const char *s_src ��������
* Output     : char *d_dest      ��������
* Return     : 0 �ɹ� <0 ʧ��
* Author     : wanglb,zhouwm
* Date       : 2008/09/12
==========================================================*/
extern int HexToStr(char *d_dest,const char *s_src);

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
extern int TransChar(char *pCharValue);

#endif /* _S_LIBPUBLIC_H */


