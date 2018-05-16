/// 配置服务接口
/*******************************************************
  源程序名称:config.h
  软件著作权:恒生电子股份有限公司
  系统名称:  HS ESB
  模块名称:  config
  功能说明: 
  作    者:  研发中心
  开发日期:  20071108
  备    注:  

  修改人员：
  修改日期：
  修改说明：
  20140613 majc 添加取最后错误信息接口
*********************************************************/
#ifndef CONFIG_H
#define CONFIG_H
#include <Include/plugin_interface.h>

#define SID_RCFGOBJ			"com.hundsun.fbase.rcfgobj"
#define SID_WCFGOBJ			"com.hundsun.fbase.wcfgobj"
#define SID_CFGOBJMAKER		"com.hundsun.fbase.cfgobjmaker"
#define SID_CFGSVR			"com.hundsun.fbase.config"

struct IWCfgObj;

/// 只读配置对象接口
struct IRCfgObj : public IKnown
{
	/// 查找指定对象名的配置对象
	/**
	 *@param szLocation: 配置对象在配置信息中的位置
	 * 不同类型的文件此参数表述的含义略有差异,差异如下:
	 * XML: 子对象名/孙对象名/.../第n级对象签名
	 * INI: 子对象名
	 *@return : 符合条件的配置对象指针;失败返回NULL
	 */
	virtual IRCfgObj* FUNCTION_CALL_MODE GetChild(const char * szLocation) = 0;
        
	/// 根据序号获得属性名
	/**
	 *@param iIndex:属性的序号(第几个属性)基数为0
	 *@return :属性名;越界返回NULL
	 */
	virtual const char * FUNCTION_CALL_MODE GetAttrName(int iIndex) = 0;
		
	///根据属性名获得属性值
	/**
	 *@param szName:属性名
	 *@return 属性值;未找到目标返回NULL
	 */
	virtual const char * FUNCTION_CALL_MODE GetAttrValue(const char * szName) = 0;
		
	/// 获取本配置对象的文本内容。当文本值之中仅有空格字符时,则为NULL,即认为没有文本值;
	virtual const char * FUNCTION_CALL_MODE GetText(void) = 0;
		
	/// 获得对象名
	virtual const char * FUNCTION_CALL_MODE GetName(void) = 0;

	/// 获得第一个子配置对象,无子配置对象则失败返回NULL
	virtual IRCfgObj * FUNCTION_CALL_MODE GetFirstChild(void) = 0;
		
	/// 获取当前对象的下一兄弟配置对象,无下一兄弟配置对象返回NULL
	virtual IRCfgObj * FUNCTION_CALL_MODE GetSibling(void) = 0;
	
	virtual IWCfgObj * FUNCTION_CALL_MODE GetWritable(void) = 0;
	
//	/// 销毁自身(包括其子对象)
//	virtual void FUNCTION_CALL_MODE Free(void) = 0;
};

/// 可写配置对象接口
struct IWCfgObj : public IKnown
{      
	/// 添加属性：如果有重名的则覆盖
	/**
	 *@param szName: 属性名
	 *@param szValue: 属性值
	 *@return: 成功返回0; 失败返回-1
	 */
	virtual int FUNCTION_CALL_MODE SetAttr(const char * szName, const char * szValue) = 0;
		
	/// 设置文本信息;
	/**
	 *@param szText: 文本信息
	 *@return: 成功返回0; 失败返回-1
	 */
	virtual int FUNCTION_CALL_MODE SetText(const char * szText, int iLen = 0) = 0;
		
	/// 创建指定对象名的配置对象并添加为当前对象的子对象
	/**
	 *@param szName:	要添加的子对象名
	 *@return:成功返回0; 失败返回-1
	 */
	virtual IWCfgObj * FUNCTION_CALL_MODE CreateChild(const char * szName) = 0;

	/// 删除子配置对象
	/**
	 *@param lpCo: 子对象指针
	 *@return: 成功返回0; 该对象不是此配置对象的孩子返回1。失败返回-1;
	 */
	virtual int FUNCTION_CALL_MODE OffChild(IRCfgObj * lpCo) = 0;
	
	///
	/**
	 *@
	 *@return: 成功返回0; 不存在该属性返回1; 失败返回-1;
	 */
	virtual int FUNCTION_CALL_MODE RemoveAttr(const char* szName) = 0;
};

/// 配置对象序列化、反序列化接口
struct ICfgObjMaker : public IKnown
{
	/// 创建指定对象名的空配置对象
	/** 
	 *@param szName:标签名
	 *@return:新配置对象指针
	 */
	virtual IWCfgObj * FUNCTION_CALL_MODE MakeObject(const char * szName) = 0;
	///从配置文件读取配置对象
	/**
	 *@param szFileUrl:		文件的Url及文件名.
	 *@param szLocation:	配置对象位置。不同类型的文件此参数表述的含义略有差异,差异如下:
	 * XML: /根标签名/次层标签名/.../第n级标签名；如果等于缺省值,则返回根标签项.
	 * INI: /第一维名; 如果等于缺少值，则返回以文件名为第一维名称的配置项
	 *@return: 配置对象指针.如果参数非法或者目标配置对象不存在则返回NULL
	 */
	virtual IRCfgObj * FUNCTION_CALL_MODE LoadFromFile(const char * szFileUrl, const char * szLocation = "") = 0;

	///根据配置对象回写文件.有重名文件存在，覆盖之；无则创建新文件。
	/**
	 *@param lpCo:		配置对象
     *@param szFileUrl:	文件名
	 *@return: 成功返回0; 失败返回-1
	 */
	virtual int FUNCTION_CALL_MODE SaveToFile(IRCfgObj * lpCo, const char * szFileUrl) = 0;

	///从缓冲区读取配置对象
	/**
	 *@param lpBuf:			缓冲区地址
	 *@param iBufSize:		缓冲区大小
	 *@param szLocation:	配置对象位置
	 *@return: 配置对象指针.如果参数非法或者目标配置对象不存在则返回NULL
	 */
	virtual IRCfgObj * FUNCTION_CALL_MODE LoadFromBuf(void * lpBuf, int iBufSize, const char * szLocation = "") = 0;
    
	///将配置对象转换成xml格式写到buf中
	/**
	 入参：
	 *@param lpCo:		配置对象指针
	 出参：
	 *@param lpBuf:		缓冲区地址
	 *@param iBufSize:	数据大小
	 *@return: 成功返回0; 失败返回-1
	 */
	virtual int  FUNCTION_CALL_MODE SaveToBuf(IRCfgObj * lpCo, void ** lpBuf, long * iBufSize) = 0;

	///释放由SavaToBuf生成的lpBuf
	/**
	 *@param lpBuf:		缓冲区地址
	*/
	virtual void FUNCTION_CALL_MODE FreeMem(void* lpBuf) = 0;
	
	//20140613 majc 添加获取最后一条错误信息
	/**LoadFromFile或LoadFromBuf发生错误的时候调用
	 * 线程不安全接口
	 *@return: 如果有错误信息则返回
	 */
	virtual char * FUNCTION_CALL_MODE GetLastErr() = 0;
};

/// 配置服务接口
struct ICfgSvr : public IKnown
{
	/// 获取配置对象制造器实例
	virtual ICfgObjMaker *  FUNCTION_CALL_MODE GetCfgObjMaker(void) = 0;
};

#ifdef __cplusplus
extern "C" { 
#endif

	///配置服务句柄初始化方法, 通过GetCfgSvrInstance获取服务句柄后, 务必使用该方法进行初始化
	///然后再使用, 否则中文处理会无法进行
	int  FUNCTION_CALL_MODE CfgSvrInit(void*, PFOnSetTimeOut);

	///取服务接口句柄
	IKnown * FUNCTION_CALL_MODE GetCfgSvrInstance(void);

	///取服务接口的服务依赖串
	char* FUNCTION_CALL_MODE GetCfgSvrDependService(void*);

	///返回统一的基础服务组件查询接口
	/**当基础服务组件动态加载时，通过本接口或以获取服务信息(包括xxxxInit(),getxxxxInterface()函数指针)
	 *@param iIndex  包含的组件序号(基数为0)
	 *@param lpSvrInfo    基础服务组件信息(输出参数)，
	 *@return 返回0表示查到所要的接口，否则返回负数
	 */
	int FUNCTION_CALL_MODE GetCfgSvrInfo(int iIndex, tagBaseServiceInfo * lpSvrInfo);

#ifdef __cplusplus
  }
#endif

#endif
