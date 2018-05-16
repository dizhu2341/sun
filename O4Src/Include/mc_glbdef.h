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
#ifndef __MC_GLBDEF_H__
#define __MC_GLBDEF_H__

#include <Include/plugin_interface.h>
#include <Include/esb_message_interface.h>
#include <Include/esb_message_factory_interface.h>
#include <Include/pack_interface.h>
#include <Include/tag_def.h>
#include <Include/log_interface.h>


#define FUNC_SUBCRIBE 620701 
#define FUNC_CANCELSUBCRIBE 620702
#define FUNC_HEARTBEAT 620703
#define FUNC_PUBLISH 620704
#define FUNC_SESSION_CONNECT 620705
#define FUNC_SESSION_PUB 620706
#define FUNC_GETTOPICINFO 620707
#define FUNC_NOTIFY 620708
#define FUNC_NOTIFY_BORN 620709
#define FUNC_VERTIFY 620710
#define FUNC_REBULID 620711
#define FUNC_REGISTER 620712
#define FUNC_CANCELREGISTER 620713
#define FUNC_GETREGISTERLIST 620714
#define FUNC_TICKSUBSCRIBE 620715
#define FUNC_PUBLISH_HEART 620716

//下级消息中心向上级发起的功能号定义
#define FUNC_MC_PUBLISH 620804
#define FUNC_MC_SESSION_CONNECT 620805
#define FUNC_MC_GETTOPICINFO 620807 
//下级消息中心向上级定时获取主题信息的功能号
#define FUNC_MC2MC_GETTOPICINFO 620817
#define FUNC_MC2MC_GETDUALSUB 620818

/* 文件更新插件功能号定义 */
#define FUNC_MC_UPDATE_FILELIST_OLD     620005  /* 兼容1.0版本：文件列表消息 */
#define FUNC_MC_UPDATE_ONEFILE_OLD      620006  /* 兼容1.0版本：单个文件消息 */
#define FUNC_MC_UPDATE_ONEFILEBLOCK_OLD 620007  /* 兼容1.0版本：文件块消息 */
#define FUNC_MC_UPDATE_FILELIST_CS      620901  /* 客户端与营业部（或总部）之间：文件列表消息 */
#define FUNC_MC_UPDATE_ONEFILE_CS       620902  /* 客户端与营业部（或总部）之间：单个文件消息 */
#define FUNC_MC_UPDATE_ONEFILEBLOCK_CS  620903  /* 客户端与营业部（或总部）之间：文件块消息 */
#define FUNC_MC_UPDATE_FILELIST_SS      620911  /* 营业部与总部之间：文件列表消息 */
#define FUNC_MC_UPDATE_ONEFILE_SS       620912  /* 营业部与总部之间：单个文件消息 */
#define FUNC_MC_UPDATE_ONEFILEBLOCK_SS  620913  /* 营业部与总部之间：文件块消息 */

//////////////////////////////////////////////////////////////////////////
/* 即时聊天插件功能号定义 */
#define FUNC_IM_USER_LOGIN              620921  /* 用户登录消息 */
#define FUNC_IM_USER_GET_LIST           620922  /* 用户列表获取消息 */
#define FUNC_IM_USER_LOGOUT             620923  /* 用户注销消息 */
#define FUNC_IM_USER_STATE_NOTIFY       620924  /* 用户状态定时更新通知消息 */

#define FUNC_IM_GROUP_CREATE            620925  /* 讨论组创建消息 */
#define FUNC_IM_GROUP_ADD_USERS         620926  /* 讨论组增加成员消息 */
#define FUNC_IM_GROUP_QUIT              620927  /* 讨论组成员退出消息 */
#define FUNC_IM_GROUP_DELETE            620928  /* 讨论组删除消息 */
#define FUNC_IM_GROUP_ADD_USERS_NOTIFY  620929  /* 讨论组增加成员通知消息 */
#define FUNC_IM_GROUP_JOIN_NOTIFY       620930  /* 讨论组成员加入通知消息 */
#define FUNC_IM_GROUP_QUIT_NOTIFY       620931  /* 讨论组成员退出通知消息 */
#define FUNC_IM_GROUP_DELETE_NOTIFY     620932  /* 讨论组删除通知消息 */

#define FUNC_IM_CHAT_SINGLE_MSG         620933  /* 聊天消息：点对点 */
#define FUNC_IM_CHAT_GROUP_MSG          620934  /* 聊天消息：讨论组 */
#define FUNC_IM_CHAT_SINGLE_MSG_NOTIFY  620935  /* 聊天通知消息：点对点 */
#define FUNC_IM_CHAT_GROUP_MSG_NOTIFY   620936  /* 聊天通知消息：讨论组 */

#define FUNC_IM_FILE_SEND               620937  /* 文件发送消息 */
#define FUNC_IM_FILE_RECV               620938  /* 文件接收消息 */
#define FUNC_IM_FILE_SEND_NOTIFY        620939  /* 文件发送通知消息 */
#define FUNC_IM_FILE_RECV_NOTIFY        620940  /* 文件接收通知消息 */
#define FUNC_IM_FILE_SEND_BLOCK         620941  /* 文件片发送消息 */

#define FUNC_IM_HEART_BEAT              620942  /* 心跳消息 */
//////////////////////////////////////////////////////////////////////////


///本项目命名空间定义
#define FBASE2_MC_NAMESPACE			FBASE2_MC
///define the namesapce
#define NAMESPACE_BEGIN(x)		namespace x {
#define NAMESPACE_END			}
#define USING_NAMESPACE(x)		using namespace x;

#define BEGIN_FBASE2_MC_NAMESPACE	NAMESPACE_BEGIN(FBASE2_MC_NAMESPACE)
#define END_FBASE2_MC_NAMESPACE		NAMESPACE_END
#define USING_FBASE2_MC_NAMESPACE	USING_NAMESPACE(FBASE2_MC_NAMESPACE)

BEGIN_FBASE2_MC_NAMESPACE
END_FBASE2_MC_NAMESPACE


#endif
