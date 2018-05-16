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

#ifndef _S_LIBPUBLIC_H
#define _S_LIBPUBLIC_H

//20071204 周伟明 增加临时字符变量最大长度
#define TEMP_STR_MAX_LEN     18960
#ifdef  _WIN32
  #define vsnprintf _vsnprintf
#endif

//20071207 周伟明 增加版本信息输出处理
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

/*############################### C 函数 ##################################*/
/*
 * The following functions are defined in the libpublic.c soruce code.
 */

/*==========================================================
 * Function   : length
 * Description: 取字符串长度
 * 			    与Oracle的length函数功能类似
 * Input      : char *str 	输入字符串
 * Output     : 
 * Return     : >0 		字符串长度
 *				0		字符串为空
 * Author     : zhouwm
 * Date       : 2004/08/16
 ==========================================================*/
extern int	length(const char *str);

/*==========================================================
 * Function   : isnull
 * Description: 验证字符串是否为空
 * Input      : const char *d_str 	输入字符串
 * Output     : 
 * Return     : 0		字符串为空
 *				1 		字符串不为空
 * Author     : zhouwm
 * Date       : 2004/08/16
 ==========================================================*/
extern int	isnull(const char *d_str);

/*==========================================================
 * Function  : trim
 * Description:滤去字符串的前后空格,与Oracle的Trim函数功能类似
 * Input     : char *str
 * Output    : char *str
 * Return    : char *str
 * Author    : zhouwm
 * Date      : 2004/08/16
 ==========================================================*/
extern char  *trim(char * );

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
extern char  *trimb(char * );

/*==========================================================
 * Function   : replace
 * Description: 字符串替换,注意输入目标字符串长度不要太短，以免替换后越界
 * Input      : char	   *dest   目标串
 *				const char *src    源字符串
 *				const char *s_old  旧字符串
 *				const char *s_new  新字符串
 * Output     : 
 * Return     : 0 		成功
 *				-1		输入为空
 * Author     : zhouwm
 * Date       : 2004/08/16
 ==========================================================*/
extern int replace(char *dest,const char *src,const char *old_str,const char *new_str);

/*==========================================================
 * Function   : ldelchar
 * Description: 前删字符
 * Input      : char	   *dest     目标串
 *				const char *src      源字符串
 *				const char c_char    旧字符
 * Output     : 
 * Return     : 0 		成功
 *				-1		输入为空
 * Author     : zhouwm
 * Date       : 2004/12/29
 ==========================================================*/
extern int ldelchar(char *dest,const char *src,const char c_char);

/*==========================================================
 * Function   : rdelchar
 * Description: 后删字符
 * Input      : char	   *dest     目标串
 *				const char *src      源字符串
 *				const char c_char    旧字符
 * Output     : 
 * Return     : 0 		成功
 *				-1		输入为空
 * Author     : zhouwm
 * Date       : 2004/12/29
 ==========================================================*/
extern int rdelchar(char *dest,const char *src,const char c_char);

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
extern char  *rpad(char *buf, int len, char c );

/*==========================================================
 * Function   : lpad
 * Description:	左补字符，与Oracle的lpad函数功能类似,
 * 			    如果字符串小于len值则左补字符c
 * Input      : char *buf 输入字符串
 *              int	 len  补字符后的字符串的长度
 *              char c    待补的字符
 * Output     : 
 * Return     : char *str
 * Author     : zhouwm
 * Date       : 2004/08/16
 ==========================================================*/
extern char	 *lpad( char *buf, int len, char c );

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
extern int   instr(const char * src,const char c);

/*==========================================================
 * Function   : substr
 * Description: 从一个字串中的某个起始位置开始得到一个子串
 * Input      : const char *s 		源字串
 *				int		   pos		该子串在源字串中的起始位置，从1开始
 *              int        len 		要得到的子串的长度
 *				const char *substr	获得的子串
 * Output     : char *char 子串
 * Return     : 0 		成功
 *				-1		输入为空
 * Author     : zhouwm
 * Date       : 2004/08/16
 ==========================================================*/
extern int substr(const char *src,int pos,int len,char *sub);

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
extern int subcmp(const char *src,int pos,int len,const char *sub);

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
extern int   hs_strstr(const char * src,const char *substr);


/*==========================================================
 * Function   : hs_strcmp
 * Description: 字符串比较
 * Input      : const char *d_str 字符串
 *				const char *s_str 字符串
 * Output     : 
 * Return     : 0 		成功
 *				-1		输入为空
*				<>0		字符不相等
 * Author     : zhouwm
 * Date       : 2004/08/16
 ==========================================================*/
extern int hs_strcmp(const char *d_str, const char *s_str);

/*==========================================================
 * Function   : hs_strcat
 * Description: 将一个字串连接到另一个字串后面
 * Input      : char *s_dest 目的字串，连接后结果字串存放的地方
 *				char *s_src 要连接的字串
 * Output     : 
 * Return     : 0 		成功
 *				-1		输入为空
 * Author     : zhouwm
 * Date       : 2004/08/16
 ==========================================================*/
extern int hs_strcat(char *s_dest,const char *s_src);

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
extern int hs_strcpy(char *d_dest,const char *s_src);

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
extern int hs_strncmp(const char *d_str, int d_len,const char *s_str);

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
extern int hs_strncat(char *s_dest,const char *s_src,size_t count);

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
extern int hs_strncpy(char * s_dest,const char *s_src,size_t count);

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
extern int hs_memcmp(const char* d_desc,const char * s_src,size_t count);

/*==========================================================
 * Function   : hs_strtolower
 * Description: 字符转换成小写
 * Input      : char *str 字串串
 * Output     : 
 * Return     : 0 		成功
 *				-1		输入为空
*				<>0		字符不相同
 * Author     : zhouwm
 * Date       : 2004/08/16
 ==========================================================*/
extern int hs_strtolower(char *str);

/*==========================================================
 * Function   : hs_strtoupper
 * Description: 字符转换成大写
 * Input      : char *str 字串串
 * Output     : 
 * Return     : 0 		成功
 *				-1		输入为空
 * Author     : zhouwm
 * Date       : 2004/08/16
 ==========================================================*/
extern int hs_strtoupper(char *str);

/*==========================================================
 * Function   : hs_strlrcpy
 * Description: 字符串左右补字符串
 * Input      : char *str         字符串
 *            : const void *rstr  左补字符串
 *            : const void *rstr  右补字符串
 * Output     : 
 * Return     : 0:  成功
 *				-1: 失败
 * Author     : zhouwm
 * Date       : 2004/10/11
 ==========================================================*/
extern int hs_strlrcpy(char *str,const char *lstr,const char *rstr);

/*==========================================================
 * Function   : hs_datediff
 * Description: 日期间隔天数
 * Input      : int 起始日期,结束日期
 *              特别地 日期不可以小于等于19700101
 * Output     : 
 * Return     : 日期间隔天数
 *				-1		输入日期非法
 * Author     : zhouwm，laisha
 * Date       : 2004/08/19
 ==========================================================*/
extern long hs_datediff(const int begin_date,const int end_date);

/*==========================================================
 * Function   : hs_dateadd
 * Description: 增加或减少相应的日期
 * Input      : int begin_date 日期,n 天数,n>0 增加天数,n<0, 减少天数
 *              特别地 日期不可以小于等于19700101
 * Output     : 
 * Return     : 日期
 *				-1		输入日期非法
 * Author     : zhouwm，laisha
 * Date       : 2004/08/19
 ==========================================================*/
int hs_dateadd(int begin_date,int n);

/*==========================================================
 * Function   : hs_round
 * Description: 截取浮点数小数点后n位，四舍五入，同oracle中的round
 * Input      : double f 输入浮点数,int n截取位数  n>0
 * Output     : 
 * Return     : 截取后的浮点数
 *				n<0返回输入浮点数
 * Author     : laisha
 * Date       : 2004/08/19
 ==========================================================*/
extern long double hs_round(long double f,const long int n);

/*==========================================================
 * Function   : hs_trunc
 * Description: 截取浮点数小数点后n位，末位舍去，同oracle中的trunc
 * Input      : double f 输入浮点数,int n截取位数  n>0
 * Output     : 
 * Return     : 截取后的浮点数
 *				n<0返回输入浮点数
 * Author     : laisha
 * Date       : 2004/08/19
 ==========================================================*/
extern long double hs_trunc(long double f,const long int n);


/*==========================================================
 * Function   : ltoc
 * Description: 数字转换成字符串
 * Input      : char *buf  转换后字符串
 *              long data  被转换数字
 * Output     : 
 * Return     : char* 字符串
 *				
 * Author     : zhouwm
 * Date       : 2004/08/19
 ==========================================================*/
extern char *ltoc( char *buf, long data );

/*==========================================================
 * Function   : dtostr
 * Description: 浮点数转换成字符
 * Input      : char	*buf  转换后字符串
 *              double	data  被转换浮点数
 * Output     : 
 * Return     : char* 字符串
 *				
 * Author     : zhouwm
 * Date       : 2004/08/19
 ==========================================================*/
extern char *dtostr( char *buf, double data );

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
 * Date       : 2004/08/19
 ==========================================================*/
extern int right(const char * s_str,const int len,char * d_str);

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
extern int left(const char * s_str,const int len,char * d_str);

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
extern int hs_getdate();

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
extern int hs_getdatetime(int *pi_date,int *pi_time);


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
extern int hs_datediff(const int pi_begdate,const int pi_enddate,char * ps_format);


/*######################### C++函数 #####################################*/

/*==========================================================
 * Function   : conversion
 * Description: 字符转换
 * Input      : char	p_var  把'\0'转换成空格
 * Output     : char  p_var  
 * Return     : char  转换后字符
 *				
 * Author     : zhouwm
 * Date       : 2004/08/19
 ==========================================================*/
extern char conversion(char p_var);

/*==========================================================
 * Function   : conversion
 * Description: 字符转换
 * Input      : char *p_var  把'\0'转换成空格
 * Output     : char *p_var  
 * Return     : char *  转换后字符
 *				
 * Author     : zhouwm
 * Date       : 2004/08/19
 ==========================================================*/
extern char * conversion(char * p_var);

/*==========================================================
 * Function   : hs_max
 * Description: 取两个整数的最大值
 * Input      : const int i_data1
 *            : const int i_data2
 * Output     : 
 * Return     : int 两个整数的最大值
 *				
 * Author     : zhouwm
 * Date       : 2004/08/19
 ==========================================================*/
extern int hs_max(const int i_data1,const int i_data2);

/*==========================================================
 * Function   : hs_max
 * Description: 取两个浮点数的最大值
 * Input      : const double d_data1
 *            : const double d_data2
 * Output     : 
 * Return     : double 两个浮点数的最大值
 *				
 * Author     : zhouwm
 * Date       : 2004/08/19
 ==========================================================*/
extern double hs_max(const double i_data1,const double i_data2);

/*==========================================================
 * Function   : hs_min
 * Description: 取两个整数的最小值
 * Input      : const int i_data1
 *            : const int i_data2
 * Output     : 
 * Return     : int 两个整数的最小值
 *				
 * Author     : zhouwm
 * Date       : 2004/08/19
 ==========================================================*/
extern int hs_min(const int i_data1,const int i_data2);

/*==========================================================
 * Function   : hs_min
 * Description: 取两个浮点数的最小值
 * Input      : const double d_data1
 *            : const double d_data2
 * Output     : 
 * Return     : double 两个浮点数的最小值
 *				
 * Author     : zhouwm
 * Date       : 2004/08/19
 ==========================================================*/
extern double hs_min(const double d_data1,const double d_data2);

/*==========================================================
 * Function   : isnumeric
 * Description: 判断字符串是否为数字
 * Input      : char *str 	输入字符串
 * Output     : 
 * Return     : 0 	字符串为数字
 *				      1		字符串不为数字
 * Author     : 赖沙
 * Date       : 2007/02/28
 ==========================================================*/
extern int isnumeric(const char *str);

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
extern int hs_subinstr(const char *ps_source,const char *ps_subsrc,const char* ps_part);

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
extern int hs_snprintf(char   *string,size_t   count, const   char   *format,...);

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
extern int   hs_strstrsoh(const char * src,const char *substr,const char soh);

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
extern int hs_strncpysoh(const char *src,int sohpos,int maxlen,char *sub,char soh);

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
extern int hs_sohnum(const char *src,char soh);


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
extern int hs_timediff(const int pi_begdate,const int pi_begtime,const int pi_enddate,const int pi_endtime,char * ps_format);

/*==========================================================
 * Function   : hs_validdate
 * Description: 检查日期有效性
 * Input      : int   pi_validdate     日期（格式为：YYYYMMDD）
 * Return     : 0                 成功
 *              -1                失败          
 * Author     : zhouwm
 * Date       : 2010/07/21
 ==========================================================*/
extern int hs_validdate(const int pi_validdate);

/*==========================================================
 * Function   : hs_validtime
 * Description: 检查时间有效性
 * Input      : int   pi_validtime     日期（格式为：HH24MISS）
 * Return     : 0                 成功
 *              -1                失败          
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
* Description: 用于把字符串转换为16进制
* Input      : char *sz_src 源字符串
*              char *sz_dest 转换后的16进制字符串
* Output     : char *sz_dest 转换后的16进制字符串
* Return     : char *
* Author     : yangsb
* Date       : 2009/05/23
==========================================================*/
extern char * StrToHex(char *sz_dest,const char *sz_src);

/*==========================================================
* Function   : HexToStr
* Description: 用于把16进制数转化为字符
* Input      : const char *s_src 传入密文
* Output     : char *d_dest      解密密码
* Return     : 0 成功 <0 失败
* Author     : wanglb,zhouwm
* Date       : 2008/09/12
==========================================================*/
extern int HexToStr(char *d_dest,const char *s_src);

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
extern int TransChar(char *pCharValue);

#endif /* _S_LIBPUBLIC_H */


