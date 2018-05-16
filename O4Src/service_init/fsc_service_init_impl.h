///Service_init 插件实现头文件
/*********************************************************************************************
  源程序名称: fsc_service_init_impl.h
  软件著作权: 恒生电子股份有限公司
  服务名称:  
  模块名称:  fsc_service_init

  插件类型:  可管理可反转普通插件

  功能说明:  

  相关文档:  

  作    者:  研发中心chengjin
  开发日期:  2014-11-17
  备    注:  
  修改记录:  
 *********************************************************************************************/

#ifndef __Service_init_Impl_H__
#define __Service_init_Impl_H__

///系统头文件
#include <string.h>
#include <stdlib.h>
#include <map>
///@todo 添加其他所需头文件
//@{

//@}


///fbase2.0头文件
#include <Include/config_interface.h>
#include <Include/pack_interface.h>
#include <Include/security_interface.h>
///@todo 添加其他所需头文件
//@{

//@}

//#include ""
///插件接口定义头文件
#include <IncludeFm/s_liblogpublic.h>
#include <service_init/service_init_interface.h>

//定义默认日志参数
#define DEFAULT_LOG_LEVEL   5
#define DEFAULT_LOG_LINE    -1
#define DEFAULT_LOG_NAME    "runlog.log"
#define DEFAULT_LOG_PATH    "./log"

class CService_initIoC; //反转控制器类
class CService_initMgr; //管理器类
class CService_initImpl; //插件实现类

///插件实现类

class CService_initImpl : public IService_init
{
    friend class CService_initIoC;
    friend class CService_initMgr;
public:
    ///IKnown接口函数
    //@{
    unsigned long FUNCTION_CALL_MODE QueryInterface(HS_SID iid, IKnown **ppv);
    unsigned long FUNCTION_CALL_MODE AddRef();
    unsigned long FUNCTION_CALL_MODE Release();
    //@}

    ///@todo, IService_init接口
    //@{


    //@}

public:
    CService_initImpl();
    ~CService_initImpl(); /*lint !e1510*/

    ///初始化，被插件库引出函数Service_initInit()调用
    int OnInit(PFOnSetTimeOut pfOnSetTimeOut = NULL);

    ///管理器事件处理函数
    //启动，管理器在处理MSG_START事件时调用
    void OnStart(PFOnSetTimeOut pfOnSetTimeOut = NULL);
    //停止，管理器在处理MSG_STOP事件时调用
    void OnStop(PFOnSetTimeOut pfOnSetTimeOut = NULL);
    //退出，管理器在处理MSG_EXIT事件时调用
    void OnExit(PFOnSetTimeOut pfOnSetTimeOut = NULL);

public:
    ///@todo, 根据需要添加其他函数
    //@{
    int InitLogLevel();
    int InitLogLineCount();
    int InitLogName();
    int InitLogPath();
    int InitHsdbOraInfo();

    //@}

private:
    ///反转控制器
    CService_initIoC * m_lpIoC;
    ///管理器
    CService_initMgr * m_lpMgr;
    ///配置对象<plugins>(收到MSG_START事件之后即释放)
    IRCfgObj * m_lpConfig;
    ///配置对象<pub>(收到MSG_START事件之后即释放)
    IRCfgObj * m_lpCoPub;
    
    ICfgSvr * m_lpCfgSvr;
    
    ISecurity * m_lpSecurity;

private:
    ///@todo, 添加所需变量
    //@{
    
    //@}
};


///反转控制器类

class CService_initIoC : public IIoC
{
public:

    CService_initIoC(CService_initImpl * lpOwner)
    {
        m_lpOwner = lpOwner;
    }
    ///IIoC接口
    //@{
    unsigned long FUNCTION_CALL_MODE QueryInterface(HS_SID iid, IKnown **ppv);
    unsigned long FUNCTION_CALL_MODE AddRef();
    unsigned long FUNCTION_CALL_MODE Release();

    int FUNCTION_CALL_MODE SetConfig(const char * sPath, IRCfgObj * lpConfig);
    int FUNCTION_CALL_MODE SetDependService(HS_SID iid, IKnown * lpService);
    //@}
private:
    CService_initImpl * m_lpOwner;
};


///管理器类

class CService_initMgr : public IManager
{
public:
    CService_initMgr(CService_initImpl * lpOwner);
    ///IManager接口
    //@{
    unsigned long FUNCTION_CALL_MODE QueryInterface(HS_SID iid, IKnown **ppv);
    unsigned long FUNCTION_CALL_MODE AddRef();
    unsigned long FUNCTION_CALL_MODE Release();

    int FUNCTION_CALL_MODE ProcMngRequest(IF2UnPacker * lpInput, IF2Packer * lpOutput);
    int FUNCTION_CALL_MODE ProcMngAnswer(IF2UnPacker * lpInput);
    int FUNCTION_CALL_MODE ProcSysEvent(unsigned long dwMessageID,
                                        unsigned long dwWParam,
                                        unsigned long dwLParam,
                                        PFOnSetTimeOut pfOnSetTimeOut = NULL);
    //@}

private:
    ///管理请求处理函数列表相关类型定义、数据结构、方法
    //@{
    ///定义请求处理函数类型REQ_ACTION
    typedef int (CService_initMgr::* REQ_ACTION)(IF2UnPacker * lpRequest, IF2Packer * lpAnswer);
    ///定义处理动作列表节点类型

    typedef struct tagAction
    {
        REQ_ACTION lpAction; //处理函数指针
        const char * sCaption; //处理函数说明
    } ACTION_INFO, * LPACTION_INFO;
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
    int mf_AddToActionList(unsigned long dwFuncNo, REQ_ACTION fpAction, const char * sCaption);
    ///取功能号对应的处理函数
    CService_initMgr::REQ_ACTION mf_GetAction(unsigned long dwFuncNo);
    //@}

    ///管理功能处理函数，所有函数原型均如:int mf_GetFuncList(IF2UnPacker * ,IF2Packer * )
    //@{
    ///查询插件管理功能号列表
    int mf_GetFuncList(IF2UnPacker * lpRequest, IF2Packer * lpAnswer);
    ///@todo定义各管理功能处理函数

    //@}
private:
    CService_initImpl * m_lpOwner;
}; /*lint !e1510*/


#endif       /*end def __Service_init_Impl_H__*/


