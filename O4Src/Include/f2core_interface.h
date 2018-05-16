///恒生插件容器接口定义 
/*******************************************************
  源程序名称:f2core_interface.h
  软件著作权:恒生电子股份有限公司
  系统名称:  恒生插件容器库接口
  模块名称:  公共模块
  功能说明: 定义一个反转控制的插件容器库
            1、插件容器本身的实现也封装成动态库（共享库），并且其接口标准也遵守插件库接口标准
            2、反转控制特性：应用主程序 --依赖注入--> 插件容器 --依赖注入--> 插件
  作    者:  研发中心
  开发日期:  20071229
  备    注:  在windows下注意函数调用方式：__stdcall
  
  修改日期：20080310
  修改人员：zhangly
  修改说明：根据20080305评审结果，在一些同步处理函数接口上，增加传入设置下一步处理超时的回调函数, PFOnSetTimeOut

  修改日期：20080111
  修改人员：zhangly
  修改说明：根据20080110评审结果，IF2Core接口
*********************************************************/

#ifndef F2CoreInterface_h
#define F2CoreInterface_h

#include <Include/plugin_interface.h>


///基础件2.0插件容器接口定义，容器本身也以插件形式封装，并同时实现IIoC接口，IManger 接口
/** 
 * 容器的功能:<br>
 * 1)根据配置动态加载插件库，并为每个插件设置需要的依赖项，容器维护一个已加载插件的列表；容器支持分批加载插件；<br>
 * 2)为应用提供一个全局数据容器，容器维护一个全局数据列表；<br>
 * 3)向所维护的插件分发管理请求与系统事件；<br>
 * 4)根据内部插件fsc_msg_pipe的配置，组装消息流水线;<br>
 *
 * 容器的使用序列:<br>
 * 1)应用主程序通过调用态动库引出函数GetIF2CoreInstance()，获得容器接口实例IF2Core；<br>
 *
 *  通过本容器的QueryInterface()方法可以获得容器的依赖注入接口IIoC，向容器传递配置对象等依赖项；
 *
 *  应用主程序通过容器接口中的Load()方法,根据配置分批动态加载各插件库，获取插件中的各类服务实例接口，并将向各服务实例传递相应的配置对象及依赖接口；
 *
 *  各服务实例如果需要用到容器，可以把容器接口IF2Core设为自已的依赖项； 但为了保持反转控制特性，服务实例不应该通过IF2Core的QueryInterface来获得本身依赖的服务；
 *
 *  通过容器接口 SetGlbData() ,GetGlbData()方法,可以存取应用级全局数据；
 *
 *  插件配置格式（物理存放格式由应用程序决定，读取并生成IRCfgObj接口对象）: plugins标签下为每个插件配置一个 plugin 子标签。
 *
 * 2) 应用主程序通过容器接口提供ProcMngRequest()、ProcMngAnswer()、ProcSysEvent()方法，向容器内的所有插件分发管理请求与系统事件（比如启动、停止）
 *
 * 3) 应用主程序通过容器接口的QueryInterface()方法，获得容器的管理器接口IManager，通过管理接口查询容器内部状态
 *
 */
struct IF2Core:IKnown
{
	///加载指定级别的插件，并按一定依赖关系对各插件进行初始化
    /**配置插件时通过指定加载级别，可以使插件能区分加载顺序
     *@param int iLoadLevel    插件加载级别，每个配置的插件可以指明加载级别(缺省为1，合法取值0、1、2)，容器的使用者可以分级分批加载插件
     *@param PFOnSetTimeOut pfOnSetTimeOut   设置超时的回调函数,缺省为NULL,用于通知调用者本次操作估计还需要多少时间才能完成对该事件的处理或在指定时间后再次回调该函数
     *@return int 成功返回I_OK，出错返回I_NONE
     */
    virtual int  FUNCTION_CALL_MODE Load(int iLoadLevel, 
		                                 PFOnSetTimeOut pfOnSetTimeOut = NULL ) = 0;

	///根据全局数据ID，返回指定全局数据指针
    /**
     *@param const char  * sGlbDataID  应用级全局数据ID，由应用开发者自已定义
     *@return void * 成功返回相应的数据区指针，出错返回NULL
     */
    virtual void *  FUNCTION_CALL_MODE GetGlbData(const char * sGlbDataID)=0;

	///根据全局数据ID，保存指定全局数据指针
    /**
     *@param char * sGlbDataID  应用级全局数据ID，由应用开发者自已定义
     *@param const void * pData      数据指针(不能为NULL)
     *@return int 成功返回I_OK，出错返回I_NONE
     */
    virtual int  FUNCTION_CALL_MODE SetGlbData(const char * sGlbDataID,void * pData)=0;


	///通过容器提供的这个方法，向容器内指定插件传递管理请求
	/**指定插件的管理器接口中的ProcMngRequest()方法会被调用到。
	 *@param  HS_SID iid  插件ID
	 *@param IF2UnPacker * lpInput  输入请求包解包器接口
     *@param IF2Packer * lpOutput   输出应答包打包器接口[输出参数]
	 *@return RET_PM_OK 成功，RET_PM_NONE 无数据，RET_PM_ERR 系统错误，其他正整数表示业务性错误
	 */
	virtual  int  FUNCTION_CALL_MODE ProcMngRequest(HS_SID iid,IF2UnPacker * lpInput,IF2Packer * lpOutput)=0;

	///通过容器提供的这个方法，向容器内指定插件传递管理应答
    /**指定插件的管理器接口中的ProcMngAnswer()方法会被调用到。
	 *@param  HS_SID iid  插件ID
 	 *@param IF2UnPacker * lpInput  输入应答包解包器接口
	 *@return int 成功返回I_OK，出错返回I_NONE
     */
	virtual  int  FUNCTION_CALL_MODE ProcMngAnswer(HS_SID iid,IF2UnPacker * lpInput)=0;

	///通过容器提供的这个方法，按指定插件顺序广播系统事件
    /**所有插件的管理器接口中的ProcSysEvent()方法都会被调用到。
	 *@param char * lpIDs 有顺序要求的插件列表，列表最后一项的为空字符串,例如： "xxxxx\0yyyyy\0\0"，表示顺序为xxxxx,yyyyy二个服务
                                若传入NULL，表示顺序无关;
	 *@param unsigned long dwMessageID 系统事件编号(参见MSG_XXXX定义)
	 *@param unsigned long dwWParam  消息参数1(由不同的dwMessageID来具体定义)
     *@param unsigned long dwLParam  消息参数2(由不同的dwMessageID来具体定义)
     *@param PFOnSetTimeOut pfOnSetTimeOut   设置超时的回调函数,缺省为NULL,用于通知调用者本次操作估计还需要多少时间才能完成对该事件的处理或在指定时间后再次回调该函数
	 *@return int 成功返回I_OK，出错返回I_NONE
     */
	virtual  int  FUNCTION_CALL_MODE ProcSysEvent( char * lpIDs,unsigned long dwMessageID,unsigned long dwWParam,unsigned long dwLParam,
		                                           PFOnSetTimeOut pfOnSetTimeOut = NULL ) = 0;

};

//容器库接口---------------------------
#ifdef __cplusplus
extern "C" { 
#endif

///容器库引出函数
IF2Core * FUNCTION_CALL_MODE GetIF2CoreInstance();

#ifdef __cplusplus
}
#endif

#endif
