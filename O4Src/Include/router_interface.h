#include <Include/esb_message_factory_interface.h>
#include <Include/pack_interface.h>
#include <Include/tag_def.h>
/// ������Ϣ�����·��Ŀ�ĵ�,
/**
	����:
		0: 		�ɹ����·��
		����:	���ܻ��·��
**/
/*
  GetRouteInfo��Ҫ���������������͵�ֵ
  //����0��ʾ�ҵ�·�������1��ʾû���ҵ�·����, -1��ʾû���ҵ�ͬʱӦ�ýضϣ���Ҫ���¼�·����
*/
int	FUNCTION_CALL_MODE	GetRouteInfo(IESBMessage* lpMessage, ITagItem* lpITem,  int *RouterIndex, bool* isNeedOspf);
int	FUNCTION_CALL_MODE	InitRoute(IRCfgObj* lpCfgObj, IF2PackSvr* lpF2PackSvr);

