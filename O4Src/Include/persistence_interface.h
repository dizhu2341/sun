/***********************************************************************
版权所有: 恒生电子股份有限公司
项目名称: MC2.0项目
版    本: V1.0
操作系统: Windows/Linux/HP-UX
文 件 名: persistence_interface.h
文件描述: 
项 目 组: CRES
程 序 员: 05909
发布日期: 2012-6-12   17:03:00
修    订:
修改日期:
***********************************************************************/
#ifndef PERSISTENCE_INTERFACE_H
#define PERSISTENCE_INTERFACE_H

#include <Include/plugin_interface.h>
#include <Include/esb_message_interface.h>
#include <Include/mcgd_interface.h>


/* 插件接口ID定义 */
#define SID_PERSISTENCE "persistence"


/* 插件接口定义 */
struct IPersistencePlugin: public IKnown
{
    ///持久化消息接口
    /**
     *@param const IESBMessage* msg: 写入的消息，不能为空
     *@return int: 返回操作结果，0表示成功，-1表示失败
     */
    virtual int FUNCTION_CALL_MODE writeMsg(const IESBMessage* msg) = 0;

    ///根据“主题”获取当前有效消息的发布者列表
    /**
     *@param const char* topicName: 主题名，不能为空
     *@param LPSENDER_NAME publisher: 用于向外部返回发布者列表，不能为空
     *@param unsigned int uiPublisher: 表示上面发布者列表最大可以存放发布者的数量
     *@return int: 失败返回-1，成功返回列表中实际发布者数量，建议外部使用SENDER_NAME[2000]传入，再判断返回值，如果大于2000，需重新来获取
     */
    virtual int FUNCTION_CALL_MODE getPublisher(const char* topicName, LPSENDER_NAME publisher, unsigned int uiPublisher) = 0;

    ///根据“主题、发布者”获取有效消息的最大、最小外部序号接口
    /**
     *@param const char* topicName: 主题名，不能为空
     *@param LPSENDER_NAME publisher: 发布者名，不能为空
     *@param unsigned int* maxExtMsgId: 返回最大有效消息的外部序号
     *@param unsigned int* minExtMsgId: 返回最小有效消息的外部序号
     *@return int: 返回操作结果，0表示成功，-1表示失败
     */
    virtual int FUNCTION_CALL_MODE getRange(const char* topicName, const LPSENDER_NAME publisher, unsigned int* maxExtMsgId, unsigned int* minExtMsgId) = 0;

    ///根据“主题、发布者”获取历史最大外部序号
    /**
     *@param const char* topicName: 主题名，不能为空
     *@param LPSENDER_NAME publisher: 发布者名，不能为空
     *@param unsigned int* maxExtMsgId: 返回历史最大消息的外部序号
     *@return int: 返回操作结果，0表示成功，-1表示失败
     */
    virtual int FUNCTION_CALL_MODE getMaxExtMsgId(const char* topicName, const LPSENDER_NAME publisher, unsigned int* maxExtMsgId) = 0;

    ///根据“主题、发布者、消息外部序号”读取消息接口
    /**
     *@param const char* topicName: 主题名，不能为空
     *@param LPSENDER_NAME publisher: 发布者名，不能为空
     *@param unsigned int ExtMsgId: 消息的外部序号
     *@param IESBMessage* msg: 返回的消息
     *@return int: 返回操作结果，0表示成功，-1表示失败
     */
    virtual int FUNCTION_CALL_MODE readMsg(const char* topicName, const LPSENDER_NAME publisher, unsigned int ExtMsgId, IESBMessage* msg) = 0;

    ///根据“主题、消息内部序号”读取消息接口
    /**
     *@param const char* topicName: 主题名，不能为空
     *@param unsigned int IntMsgId: 消息的内部序号
     *@param IESBMessage* msg: 返回的消息
     *@return int: 返回操作结果，0表示成功，-1表示失败
     */
    virtual int FUNCTION_CALL_MODE readMsg(const char* topicName, unsigned int IntMsgId, IESBMessage* msg) = 0;

    ///触发持久化插件数据整理：数据整理的过程中持久化插件的其他接口不对外提供服务
    /**
     *@param
     *@return int: 返回操作结果，0表示成功，-1表示失败
     */
    virtual int FUNCTION_CALL_MODE triggerDump() = 0;
};

/* 定义插件库标准引出函数，功能及参数说明参见"Include/plugin_interface.h" */
#ifdef __cplusplus
extern "C" {
#endif
    /* 查询插件库中的插件信息 */
    int FUNCTION_CALL_MODE GetPersistenceInfo(int iIndex, tagBaseServiceInfo* ppv );

    /* 取插件实例 */
    IKnown* FUNCTION_CALL_MODE GetPersistenceInstance();

    /* 取插件依赖的其他插件ID串 */
    char*  FUNCTION_CALL_MODE GetPersistenceDependSvr(void* lpInstance);

    /* 插件初始化 */
    int FUNCTION_CALL_MODE PersistenceInit(void* lpInstance, PFOnSetTimeOut pfOnSetTimeOut);
#ifdef __cplusplus
}
#endif

#endif
