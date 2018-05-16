/*
 * Headfile: Hshead.h
 * Author : 周伟明
 * Date   : 2006/08/16.
 * Notes  : 头文件集合
 *          
 */

#ifndef _S_HSHEAD_H
#define _S_HSHEAD_H

/* operating system header file */
#include  <string.h>
#include  <stdio.h>
#include  <stdlib.h>
#include  <ctype.h>
#include  <sys/types.h>
#include  <time.h>
#include  <memory.h>
#include  <malloc.h>
#include  <fcntl.h>
#include  <limits.h>
#include  <stddef.h>
#include  <stdarg.h>
#include  <math.h>
#include  <errno.h>
#ifdef _WIN32
  #include <windows.h>
  #include <winbase.h>
  #include <io.h>  
#endif

#ifdef  OS_UNIX
	#include  <sys/time.h>	
	#include  <sys/stat.h>	
	#include  <sys/wait.h>
	#include  <unistd.h>
  #include  <dirent.h>
#endif

/* 2007-05-30 zhouwm 关闭系统中printf操作 begin. */
/*
#ifdef _HSDEBUG
  #define printf (void)
#endif
*/
/* 2007-05-30 zhouwm 关闭系统中printf操作 end. */

/* middleware header file */
//#include <Include/as_func_comp.h>
//#include <Include/as_context.h>
//#include <Include/as_tempmdb.h>
//#include <Include/as_ResultSet.h>
#include <Include/tag_def.h>
#include <Include/esb_message_factory_interface.h>
#include <Include/esb_message_interface.h>
#include <Include/biz_comp_interface.h>
#include <Include/resultset.h>
#include <Include/mdb_interface.h>

/* business system header file */
#include "IncludeFm/hscommon.h"
#include "IncludeFm/deskey.h"
#include "IncludeFm/hserror.h"
#include "IncludeFm/hsmenu.h"
#include "IncludeFm/hsfunction.h"
#include "IncludeFm/hsconst.h"
#include "IncludeFm/s_libpublic.h"
#include "IncludeFm/s_liblogpublic.h"
#include "IncludeFm/s_glbfunction_or.h"
#include "IncludeFm/s_helper.h"
#include "IncludeFm/s_jc_public.h"
#include "IncludeFm/s_msginterface.h"
#include "IncludeFm/basepub.h"
#include "IncludeFm/jc_finger.h"
#include "IncludeFm/SyncLock.h"
#include "IncludeFm/writedlog.h"
#include "IncludeFm/desc.h"
#endif /* _HSHEAD_H */

