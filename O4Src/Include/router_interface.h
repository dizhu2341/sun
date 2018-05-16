#include <Include/esb_message_factory_interface.h>
#include <Include/pack_interface.h>
#include <Include/tag_def.h>
/// 根据消息体决定路由目的地,
/**
	返回:
		0: 		成功获得路由
		其他:	不能获得路由
**/
/*
  GetRouteInfo需要返回下面三种类型的值
  //返回0表示找到路由项，返回1表示没有找到路由项, -1表示没有找到同时应该截断，不要往下级路由找
*/
int	FUNCTION_CALL_MODE	GetRouteInfo(IESBMessage* lpMessage, ITagItem* lpITem,  int *RouterIndex, bool* isNeedOspf);
int	FUNCTION_CALL_MODE	InitRoute(IRCfgObj* lpCfgObj, IF2PackSvr* lpF2PackSvr);

