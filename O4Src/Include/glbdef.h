///恒生ESB全局常量定义
/**
 *源程序名称:glbdef.h
 *软件著作权:恒生电子股份有限公司
 *系统名称:恒生企业服务总线ESB
 *模块名称:Include
 *功能说明:定义ESB全局常量定义
 *作    者: 项目组
 *开发日期: 2008-7-2 9:49:29
 *备    注: 
 */
#ifndef __FBASE2_GLBDEF_H__
#define __FBASE2_GLBDEF_H__
#include <Include/inttypes.h>
///ESB组名长度，名字为可见字符，不能包含实例分隔符、空格、分号;
#define IDENTITY_NAME_LENGTH	32
///实例编号最大占位长度
#define ID_LENGTH               4   
///实例分隔符，用于ESB节点名，插件实例名，服务进程实例名，这三种对象都会有多个实例，每个实例有唯一数字编号，名字与编号之间采用此分隔符
#define DELAM_FLAG				'#'	
#define DELAM_FLAG_SZ			"#"
///节点名全长,定义时使用char sName[ID_STR_LEN+1]
#define ID_STR_LEN		       (IDENTITY_NAME_LENGTH + ID_LENGTH + 1)


//	插件接口名的最大长度,定义时使用char sName[PLUGINID_LENGTH+1]
#define PLUGINID_LENGTH	256
//	插件实例名的最大长度,定义时使用char sName[PLUGIN_NAME_LENGTH+1]
#define PLUGIN_NAME_LENGTH	(PLUGINID_LENGTH+ID_LENGTH+1)
//	进程名最大长度.定义时使用char sName[SVR_NAME_LENGTH+1]
#define SVR_NAME_LENGTH	256
//	进程实例名最大长度.定义时使用char sName[PLUGINID_NAME_LENGTH+1]
#define SVRINSTANCE_NAME_LENGTH	(SVR_NAME_LENGTH+ID_LENGTH+1)

///正常无错返回码
#define ERR_NONE									0

/*
  修改人员：xuxp
  修改日期：2009.04.10
  修改说明：采用宏定义四种身份

  修改日期：2009.04.20
  修改说明：增加前缀，因为和F1的宏定义冲突
*/
#define ESB_IDENTITY_AR  "ar"
#define ESB_IDENTITY_BAR "bar"
#define ESB_IDENTITY_LS  "ls"
#define ESB_IDENTITY_AS  "as"


/*
  修改人员：xuxp
  修改日期：2009.04.10
  修改说明：增加身份标示定义，采用枚举定义，采用宏定义这四种身份
*/
enum HS_IDENTITY 
{ 
HSSERVER_UNKNOWN=0,
HSSERVER_AR=1, 
HSSERVER_BAR=2, 
HSSERVER_LS=3,
HSSERVER_AS=4
}; 


#endif
