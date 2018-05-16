#ifndef MC2_TOPIC_H_
#define MC2_TOPIC_H_

#include <Include/biz_check_interface.h>
#include <IncludeFm/hsconst.h>
#include <unistd.h>

extern "C" {
    // 主题获取
    int FUNCTION_CALL_MODE GetTopicList(IAppContext* lpCont, IF2Packer * lpAnswer, int iTimeout);

    // 先天订阅者
    int FUNCTION_CALL_MODE GetDualSub(IAppContext* lpCont, IF2Packer * lpAnswer, int iTimeOut);
    
    // 发布权限校验
    int FUNCTION_CALL_MODE CheckPub(IAppContext* lpCont, char* lpTopic, char* lpPublisher, IF2Packer * lpAnswer);
    
    // 订阅权限校验
    int FUNCTION_CALL_MODE CheckSub(IAppContext* lpCont, char* lpTopic, IF2UnPacker * lpSubReq, char* lpSub, IF2Packer * lpAnswer);
};

#endif // MC2_TOPIC_H_
