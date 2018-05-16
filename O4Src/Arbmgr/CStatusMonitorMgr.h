#ifndef _CStatusMonitorMgr_H__
#define _CStatusMonitorMgr_H__

#include "ArbMgrMain.h"

class CArbMgrIOC; //反转控制器类
class CStatusMonitorMgr; //管理器类
class CArbManager; //插件实现类

class CStatusMonitorMgr: public IManager
{
public:
    CStatusMonitorMgr(CArbManager * lpOwner);
    ///IManager接口
    //@{
    unsigned long  FUNCTION_CALL_MODE QueryInterface( HS_SID iid, IKnown **ppv );
    unsigned long  FUNCTION_CALL_MODE AddRef();
    unsigned long  FUNCTION_CALL_MODE Release();

    int  FUNCTION_CALL_MODE ProcMngRequest(IF2UnPacker * lpInput,IF2Packer * lpOutput);
    int  FUNCTION_CALL_MODE ProcMngAnswer(IF2UnPacker * lpInput);
    int  FUNCTION_CALL_MODE ProcSysEvent(unsigned long dwMessageID,
    				  unsigned long dwWParam,
    				  unsigned long dwLParam,
    				  PFOnSetTimeOut pfOnSetTimeOut = NULL);
    //@}
	
private:
    ///管理请求处理函数列表相关类型定义、数据结构、方法
    //@{
    ///定义请求处理函数类型REQ_ACTION
    typedef int (CStatusMonitorMgr::* REQ_ACTION)(IF2UnPacker * lpRequest,IF2Packer * lpAnswer);
    ///定义处理动作列表节点类型
    typedef struct tagAction{
        REQ_ACTION  lpAction;		//处理函数指针
        const char *   sCaption;	//处理函数说明
    }ACTION_INFO,* LPACTION_INFO;
    ///定义管理功能处理函数表类型 ACTION_MAP
    typedef std::map< unsigned long, LPACTION_INFO > ACTION_MAP;

    ///管理功能函数表
    ACTION_MAP m_ProcReqActionList;
    ///将处理函数加入到列表中
    /** 
     *@param unsigned long  dwFuncNo   管理功能号
     *@param ProcReqAction  fpAction   功能号对应的处理函数
     *@param const char *   sCaption   管理功能描述
     */
    int mf_AddToActionList(unsigned long dwFuncNo,REQ_ACTION fpAction,const char * sCaption);
    ///取功能号对应的处理函数
    CStatusMonitorMgr::REQ_ACTION mf_GetAction(unsigned long dwFuncNo);
    //@}
	
    ///管理功能处理函数，所有函数原型均如:int mf_GetFuncList(IF2UnPacker * ,IF2Packer * )
    //@{
    ///查询插件管理功能号列表
    int  mf_GetFuncList(IF2UnPacker * lpRequest,IF2Packer * lpAnswer);
    ///@todo定义各管理功能处理函数
    
    //@}
private:
    CArbManager * m_lpOwner;
};

#endif
