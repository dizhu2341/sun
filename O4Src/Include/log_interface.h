
/// 总说明
/*******************************************************
源程序名称:
软件著作权:恒生电子股份有限公司
系统名称:  恒生插件容器库接口
模块名称:  Log
功能说明:  实现和Log接口相关的周边类(结构)
作    者:  kongxy@hundsun.com
开发日期:  20071110 - 10071120
备    注:  

  修改人员：xuxp
  修改日期：20110221
  修改说明：增加ILogService接口函数，防止原有的参数类型以及个数不对应造成程序崩溃的bug

  修改人员：yinghh
  修改日期：20110427
  修改说明：增加头文件包含stdlib.h，避免在其他编译器上的编译错误
*********************************************************/


#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_SLOGBEHAVIORPARA_4736C1D80021_INCLUDED
#define _INC_SLOGBEHAVIORPARA_4736C1D80021_INCLUDED
#include <string.h>
#include <stdlib.h>
#include <Include/plugin_interface.h>


#define SID_LOG				    	    "com.hundsun.fbase.log"
#define SID_BIZLOG                      "com.hundsun.fbase.bizlog"
#ifndef WRITE_LOG
#define WRITE_LOG if (m_lpLogService) m_lpLogService->AddLocalLog 
#endif

//##ModelId=49702F9801F6
typedef long HRESULT;
struct IESBMessage;

//20111221 dongpf 增加两个日志级别
enum LOG_WARNING_LEVEL 
{

	//##ModelId=49701C4100B4
    ESB_LOG_DEBUG = 0,

	//##ModelId=49701C4100B5
    ESB_LOG_EVENT = 1,

	//##ModelId=49701C4100B6
    ESB_LOG_WARNING = 2,
 
	//##ModelId=49701C4100B7
    ESB_LOG_ERRER = 3,

	//##ModelId=49701C4100B8
    ESB_LOG_CRUSHED = 4,

	ESB_LOG_IMPORTANTEVENT = 5,

	ESB_LOG_UNKNOWN = 6
};


//##ModelId=49702F980271
enum FILTER_MODE 
{
    ///@{

    /// 定义过滤器的优先级
    /**
      * 优先级高的将有权先取得要过滤的日志，下面按低到高排列
      */
	//##ModelId=49702F980281
    FM_PRIORITY_LOWEST = (1<<0),

	//##ModelId=49702F980282
    FM_PRIORITY_LOW = (1<<1),

	//##ModelId=49702F980283
    FM_PRIORITY_BELOW_NORMAL = (1<<2),

	//##ModelId=49702F980290
    FM_PRIORITY_NORMAL = (1<<3),

	//##ModelId=49702F980291
    FM_PRIORITY_ABOVE_NORMAL = (1<<4),

	//##ModelId=49702F980292
    FM_PRIORITY_HIGH = (1<<5),

	//##ModelId=49702F980293
    FM_PRIORITY_VERY_HIGH = (1<<6),

	//##ModelId=49702F980294
    FM_PRIORITY_HIGHT = (1<<7),

    ///@}

    ///指定过滤器有修改日志信息的权限
    /** 日志服务把日志发给这个过滤器，它可以把日志根据自己的功能修改源日志，以影响
      * 后续的过滤器。由于这个性质，建议尽量不用这个属性；如果要用要与后续的过滤器开
      * 发者协商。
      */
	//##ModelId=49702F9802A0
    FM_PURVIEW_MODIFY = (1<<16),

    ///有停止日志向后继过滤器发送日志更新的消息的权限(慎用!)
	//##ModelId=49702F9802A1
    FM_PURVIEW_STOP_FILTER = (1<<17),

    //日记不可用
	//##ModelId=49702F9802A2
    FM_DISABLE = (1<<18)
};

/// 一条日志可能的项
/** 其中iLogID,szSrcModule,szDesc是必须的。如果您要记录一条日志时，可以用
  * ICompLog::AddLocalLog，把参数指定为这里的iLogID。
  */
//##ModelId=49701C4100F1
struct SLog 
{
public:
    /// 日志全局唯一标识，日志服务将用这个值作索引
	//##ModelId=49701C410102
    int iLogID;

    /// 想要记录日志的源模块
	//##ModelId=49701C410103
    char* szSrcModule;

    /// 日志的说明（纯文本）
	//##ModelId=49701C410104
    char* szDesc;


    /// 产生日志的源位置，它是较szSrcModule更详细的定位
	//##ModelId=49701C410105
    char* szSrcLocate;

    /// 说明可能会影响到的其它模块、功能
	//##ModelId=49701C410106
    char* szEffect;

    /// 描述可能有效的处理方法（如果是错误）
	//##ModelId=49701C410107
    char* szStrategy;

    /// 日志的紧急程度
	//##ModelId=49701C410112
    LOG_WARNING_LEVEL iWarningLevel;

    /// 日志的说明，是一个动态文本，这个文本指明动态文本的组织格式
    ///（像标准C里的printf的第一参数）。
    /** 这个格式完全兼容printf的格式、（建议支持正则式的指定，当前不能用）
      */
	//##ModelId=49701C410116
    char* szMsgFormat;
};


//##ModelId=49702F9802BF
struct ILogFilter : public IKnown
{
public:
    /// 过滤器的入口函数
    /// 如果您已经向日志服务注册过一个过滤器实例，那么日志会把新日志发送（调用）给这个接口
    /**
      *@ const SLog* lpLog:     新的日志，这个日志全局维护，如果你有特殊用处，一定要修改这个
      *                         新日志（可能使其它过滤器出错），那你必须把过滤器模式加上
      *                         FM_PURVIEW_MODIFY权限，并使用尽可能低的优先级，如
      *                         FM_PRIORITY_LOWEST，见ICompLog::AssignFilter
      *@ return:                I_OK或 S_STOP_LATER_FILTER。Log服务会根据这个值决定后续的行为：
      *      I_OK：                 Log正常运作
      *      S_STOP_LATER_FILTER：  Log不再通知后续的过滤器有新日志，过滤器的先后由
      *                             FILTER_MODE::FM_PRIORITY_?决定，同级根据注册的先后
      *                             （先来优先级高）。要使S_STOP_LATER_FILTER生效，您的过滤器
      *                             权限必须要有FM_PURVIEW_STOP_FILTER。如果返回这个值，而您的
      *                             过滤器又没有权限，日志服务会记录一个没权限的日志信息；这条
      *                             日志不会给任何过滤器！强烈建议您使用FM_PRIORITY_NORMAL
      */
	//##ModelId=49702F9802D1
    virtual HRESULT Entry(const SLog* LpLog, va_list lpPara) = 0;
};

//20110221 xuxp 为新增接口而增加的类，用于参数传递，所有类型转换为char*
//自定义的类型类
class CLogType
{
private:
	char* m_TypeValue;

public:
	CLogType(int iValue)
	{
		m_TypeValue = (char*)malloc(100);
		memset(m_TypeValue,0,100);
		sprintf(m_TypeValue,"%d",iValue);
	}

	CLogType(double iValue)
	{
		m_TypeValue = (char*)malloc(100);
		memset(m_TypeValue,0,100);
		sprintf(m_TypeValue,"%lf",iValue);
	}

	CLogType(float iValue)
	{
		m_TypeValue = (char*)malloc(100);
		memset(m_TypeValue,0,100);
		sprintf(m_TypeValue,"%lf",iValue);
	}

	CLogType(char* iValue)
	{
        // 20140805 去除win64编译警告
		int iLen = (int)strlen(iValue);
		m_TypeValue = (char*)malloc(iLen+1);
		memset(m_TypeValue,0,iLen+1);
		memcpy(m_TypeValue,iValue,iLen);
	}

	CLogType(char iValue)
	{
		m_TypeValue = (char*)malloc(100);
		memset(m_TypeValue,0,100);
		m_TypeValue[0] = iValue;
	}

	char* GetValue()
	{
		return m_TypeValue;
	}

	~CLogType()
	{
		free(m_TypeValue); 
	}
};

//20110221 xuxp 宏定义，方便调用
#define LOGTYPE(x) (new CLogType(x))

//##ModelId=49701C410126
struct ILogService : public IKnown
{
public:
   
    /// 增加一条日志
    /// 在本地日志记录文件中加入一条指定的新日志记录。
    /**
      *@ Param const char* szLocation:  日志发生的位置
      *@ Param int iLogID:      指定要增加的日志的日志常量，用以识别日志类别
      *@ Param void* lpany(...):     为扩展留下接口，现在忽视这个值
      *@ return I_OK:           成功写入日志，其它表示出错，日志会记录出错信息，注册过的
      *                         过滤器能收到除了是因为日志过滤器产生的日志。
      */
	//##ModelId=49701C410132
    virtual HRESULT AddLocalLog( const char* szLocation, int iLogID, ...   ) = 0;

    /// 向日志服务注册一个过滤器
    /// 目的在于截住过新日志，以便您的处理。请注意看iAttachMode参数说明！
    /**
      *@ Param  HS_SID  lpFilter:       过滤器的GUID
      *@ return:                        I_OK成功注册，其它表示出错，日志会记录这个信息，
      *                                 注册过的过滤器能收到。
      */
	//##ModelId=49701C410137
    virtual HRESULT AddFilter( ILogFilter *lpFilter, HS_SID FilterSID ) = 0;

    virtual HRESULT AddBizLog(  IESBMessage* lpReq,char *sError_PathInfo,int iError_no,char *sError_Info,int iError_id,char *sError_SysInfo ) = 0;
	
	//20110221 xuxp 类似上面的AddLocalLog接口，把可变参数变成十个固定参数，防止程序崩溃
	/// 增加一条日志
    /// 在本地日志记录文件中加入一条指定的新日志记录。
    /**
      *@ Param const char* szLocation:  日志发生的位置
      *@ Param int iLogID:      指定要增加的日志的日志常量，用以识别日志类别
      *@ Param CLogType* arg1:     写入日志的类型实例
	  *。。。。。。。。。。
      *@ return I_OK:           成功写入日志，其它表示出错，日志会记录出错信息，注册过的
      *                         过滤器能收到除了是因为日志过滤器产生的日志。
      */
	virtual HRESULT AddLocalLogEx( const char* szLocation, int iLogID, CLogType* arg1=NULL,CLogType* arg2=NULL,
		CLogType* arg3=NULL,CLogType* arg4=NULL,CLogType* arg5=NULL,CLogType* arg6=NULL,CLogType* arg7=NULL,
		CLogType* arg8=NULL,CLogType* arg9=NULL,CLogType* arg10=NULL) = 0;

	/// 记录业务日志
	/**
      *@ Param int iLevel             当前日志级别
	  *@ Param char *sError_PathInfo  错误路径信息
	  *@ Param int iError_no          错误号
	  *@ Param char *sError_Info      错误信息
	  *@ Param int iError_id          系统错误编号
	  *@ Param char *sError_SysInfo   系统错误信息
	  *@ Param int iFunctionNo        功能号
	  *@ return  I_OK   :   0 成功 -1 失败
	*/
	virtual HRESULT AddBizLogEx(int iLevel, const char *sError_PathInfo,int iError_no, const char *sError_Info,int iError_id, const char *sError_SysInfo, int iFunctionNo) = 0;

};

#ifdef __cplusplus
extern "C" {
#endif

    int FUNCTION_CALL_MODE GetLogServiceInfo( int, tagBaseServiceInfo* );

#ifdef __cplusplus
}
#endif


#endif /* _INC_ICOMPLOG_4734086E0225_INCLUDED */
