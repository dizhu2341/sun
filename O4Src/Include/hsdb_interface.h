/*******************************************************
  源程序名称:hsdb_interface.h
  软件著作权:恒生电子股份有限公司
  系统名称:  HZHSGS金融基础件V2.0
  模块名称:  统一数据库访问引擎接口
  功能说明: 
             
           
  相关文档:  概要设计接口部分
             
  作    者:  zhangly
  开发日期:  20080826
  备    注:  平台无关，支持对多种数据库的访问

*********************************************************/
#ifndef HSDB_INTERFACE_H
#define HSDB_INTERFACE_H

#include <stdio.h>
#include <stdlib.h>
#include <Include/plugin_interface.h>
#include <Include/resultset.h>

#ifndef PLATFORM_EXPORT
#define PLATFORM_EXPORT
#endif

#define SID_F2HSDBSVR					"com.hundsun.fbase.hsdb"

struct IConnection;              //数据库连接接口
struct IStatement;               //SQL语句操作接口
struct ICallableStatement;       //存储过程操作接口

///数据库统一访问服务。
struct IHSDBService:IKnown
{
    ///根据数据源名，获取数据库连接
    /**获得的连接在用完之后,必须调用 IConnection 的toFree()方法归还，供其他使用者复用;
     *
     *当数据源的连接池中所有连接都被占用时，本方法将配置设定的超时时间内重试;
     *@param const char *  datasource_name  数据源逻辑名
     *@return IConnection * 当数据源存在并且有空闲连接时返回连接句柄，否则返回NULL.
     */   
    virtual IConnection * FUNCTION_CALL_MODE getConnection(const char * datasource_name)=0;

    ///根据数据源名字,数据源连接并永久独占使用(排他),直到系统退出
    /**使用本方法取得的连接，在调用toFree()时并不将连接归还给连接池；
     *
     * 比如:AS处理线程提供的缺省连接，即是使用此方法获取的，直到AS关闭时才释放；
     *@param const char *  datasource_name  数据源逻辑名
     *@return 连接对象句柄
     */
    virtual  IConnection * FUNCTION_CALL_MODE getExclusiveConnection(const char * datasource_name) = 0;

};

const int HSDB_CONNECTION_STATUS_DISCONN                    = 0;//连接为断开状态
const int HSDB_CONNECTION_STATUS_FREE                       = 1;//连接为空闲状态
const int HSDB_CONNECTION_STATUS_BUSY                       = 2;//连接为忙状态
const int HSDB_CONNECTION_STATUS_BUSY_AND_DISCONN           = 3;//连接为忙并且断开状态。

const int IAMSTATEMENTIMPL = 0;     //普通语句句柄常量
const int IAMCALLABLESTATEMENTIMPL = 1;//存储过程语句句柄常量



///数据库连接接口 
struct IConnection:IKnown
{

  ///取数据库连接状态
  /*
  *@return HSDB_CONNECTION_STATUS_DISCONN 
  *        HSDB_CONNECTION_STATUS_FREE
  * 	   HSDB_CONNECTION_STATUS_BUSY
  *		   HSDB_CONNECTION_STATUS_BUSY_AND_DISCONN
  */  
  virtual int  FUNCTION_CALL_MODE getConnStatus(void) = 0; 

  ///执行一条update,insert,delete,truncate的sql语句
  /**语句执行结束后，语句句柄即被释放
    *@param  sql: 一条update,insert,delete,truncate的sql语句
    *@return 0成功，1失败
    */
  virtual int FUNCTION_CALL_MODE executeUpdate(char * sql) = 0;

  ///执行一条select语句
  /**语句执行结束后，会打开并占用一个游标资源
   *@param   sql: 一个结果集返回的sql语句
   *@return  :结果集指针
   */
  virtual IF2ResultSet *  FUNCTION_CALL_MODE executeQuery(char * sql)=0;
 
  ///申请普通语句句柄
  /**@return 普通语句接口句柄，用完后调用句柄的destroy()方法释放资源（归还当前连接也会自动释放);
  */ 
  virtual IStatement * FUNCTION_CALL_MODE createStatement(void) = 0;  

  ///申请存储过程语句句柄
  /**@return 存储过程语句接口句柄，用完后调用句柄的destroy()方法释放资源（归还当前连接也会自动释放)
  */  
  virtual ICallableStatement * FUNCTION_CALL_MODE createCallableStatement(void) = 0;
  
  ///归还占用的连接
  /**归还后的连接会被其他调用者复用，归还时会释放此连接上的语句句柄；
   *@return :返回NULL指针. 建议使用FREE_CONNECTION()宏来归还，使当前调用者的连接指针被置为NULL; 
   */
  virtual void * FUNCTION_CALL_MODE toFree() = 0;

  ///获得错误号
  /*@return 错误号:
  */
  virtual int FUNCTION_CALL_MODE getErrNo() = 0;

  ///获得错误信息
  /*@return 错误信息.
  */
  virtual char * FUNCTION_CALL_MODE getErrInfo() = 0;

  ///获得当前连接对象的嵌入SQL所需连接上下文 sql_context
  /*@return void * 上下文句柄
  */
  virtual void * FUNCTION_CALL_MODE getSQLContext() = 0;  

  ///错误设置接口setErrMessage，用于pro*c等嵌入式SQL组件将捕获的SQL错误通知hsdb
  /*调用本接口后，错误信息将被记入到AS日志，对于hsErrNo=HSDB_CONNECT_DISCONN的错误
   *将触发hsdb在下次使用连接时重建连接,如oracle pro*C中的SQLCODE=-28(session中止)或 -1012 (没有登录)
   *@param int hsErrNo            HS错误号，如果当前错误需要重连，则hsErrNo设为 HSDB_CONNECT_DISCONN ，否则设为0
   *@param int errNo              SQL错误号，如pro*C中的sqlca.sqlcode
   *@param const char * errInfo   SQL错误信息，如pro*C中的sqlca.sqlerrm.sqlerrmc
   */
  virtual void FUNCTION_CALL_MODE setErrMessage(int hsErrNo,int errNo,const char * errInfo) = 0;  

  ///获得当前连接对象的服务类型
  /*@return int 服务类型
  */
  virtual int FUNCTION_CALL_MODE getServerType() = 0;
  
};

///数据库语句接口
/**各类调用序列：
 * 1、无结果集
 *
 *   (1)准备             prepare("delete tab"); 
 *
 *   (2)执行             exec();
 *
 *   (3)如有错误(执行返回有错)，可通过当前连接取错误信息;
 *
 *   (4)释放本接口       destroy();
 *
 * 2、有结果集
 *
 *   (1)准备             prepare("select * from tab");
 *
 *   (2)执行并返回结果集 open();
 *
 *   (3)结果集操作(@see IResultSet),操作完之后释放结果集对象;
 *
 *   (4)如有错误(结果集返回NULL)，可通过当前连接取错误信息;
 *
 *   (5)释放本接口       destroy();
 */
struct IStatement:IKnown
{
  ///准备要调用的sql语句或存储过程语句
  /**@param  char *sql  标准SQL语句或存储过程语句(参见扩展的ICallableStatement接口)
	*@return 0成功，1失败
	*/
  virtual int  FUNCTION_CALL_MODE prepare(char * sql) = 0;
	
  ///执行一条update,insert,delete,truncate的sql语句
  /**@param  sql: 一条update,insert,delete,truncate的sql语句
    *@return 0成功，1失败
    */
  virtual int FUNCTION_CALL_MODE exec(void) = 0;

   ///执行一条select语句
  /**@param   sql: 一个结果集返回的sql语句
   *@return  :结果集指针
   */
  virtual IF2ResultSet *  FUNCTION_CALL_MODE open(void) = 0;

  ///语句影响的记录数。
  /**@return  int 记录数.
   */
  virtual int  FUNCTION_CALL_MODE getAffectedCount(void) = 0;

  //取消操作
  /*@return : 0 成功，1失败
  */
  virtual int FUNCTION_CALL_MODE cancel() = 0;

  ///摧毁
  /**@return :返回NULL指针. 建议使用 方法statObj = statObj->destroy();
  */
  virtual void * FUNCTION_CALL_MODE destroy() = 0;

  ///按位置绑定SQL语句中的占位符(扩展用) 
  /**
   *@param int iIndex     要绑定的SQL语句中占位符序数(从左到右以0为基数)
   *@param void * pData   绑定的变量数据区
   *@param int iDataLen   绑定的变量数据区长度
   *@param char cDataType 绑定的变量类型,参见as_hsdb_const.h
   *@return  int 成功为0 
   */
  //virtual int FUNCTION_CALL_MODE bindByPos(int iIndex,void * pData,int iDataLen,char cDataType) =0;
  
};


///存储过程访问接口
/**说明
 *1、该类方法的parameterIndex参数基数均为1.
 *
 *2、prepare()方法中的sql参数的形式，有如下规定 :  
 *             
 *		所调存储过程没有return值的为: "call storeProName(?,?,?.....)"  
 *   
 *		所调存储过程有return值的为  : " ? = call storeProName(?,?,?.....)"
 *
 *      每个问号即为一个参数占位符,对于oracle下返回结果集的游标参数，不必占位，约定为最后一个参数；
 *
 *      编写存储过程时建议将同类型的参数放在一起，并遵守如下顺序：输入，输入输出，输出，结果集;
 *
 *3、调用序列
 *   (1)准备             prepare("call storeProName(?,?,?.....)" );
 *
 *   (2)设置输入参数值   setXXXX();
 *
 *   (3)注册输出参数     registerOutParameter;
 *
 *   (4)执行             有结果集返回用open()，否则用exec();
 *
 *   (5)如果有结果集,即以open()执行，则先读取结果集(@see IResultSet),操作完之后释放结果集对象;
 *
 *   (6)取输出参数及return 返回值,(如果有结果集返回，必须在读完结果集之后再取输出参数);
 *
 *   (7)如有错误(结果集返回NULL)，可通过当前连接取错误信息;
 *
 *   (8)释放本接口       destroy();
 *
 */
struct ICallableStatement:public IStatement
{
  
	/**@name 以下方法在调用前设置各类输入参数*/
	//@{
	    ///添加数据参数: 类型  char * ； c  的字符串类型
		/**@param int parameterIndex:   该参数在输入参数列表中的的位置,
		  *@param char * parameterValue:  参数值
		  *@return HSDB_SUCESS or  HSDB_FAILURE
		  */
		virtual int  FUNCTION_CALL_MODE setString(int parameterIndex,char * parameterValue)=0;

		///添加数据参数: 类型  char
		/** 
		*@param parameterIndex: 该参数在输入参数列表中的的位置,
		*@param parameterValue: 参数值
		*@return HSDB_SUCESS or  HSDB_FAILURE
		*/
  		virtual int  FUNCTION_CALL_MODE setChar(int parameterIndex,char  parameterValue)=0;

		///添加数据参数: 类型    Long
		/**
		*@param parameterIndex:   该参数在输入参数列表中的的位置,
		*@param parameterValue:   参数值
		*@return HSDB_SUCESS or  HSDB_FAILURE
		*/
		virtual int FUNCTION_CALL_MODE setInt(int parameterIndex,int parameterValue) = 0;

		///添加数据参数: 类型    double
		/**
		*@param parameterIndex:   该参数在输入参数列表中的的位置,
		*@param parameterValue:   参数值
		*@return HSDB_SUCESS or  HSDB_FAILURE
		*/
		virtual int FUNCTION_CALL_MODE setDouble(int parameterIndex,double parameterValue) = 0;


		/// 注册输出参数
		/** 
		*@param parameterIndex:int 输出参数位置
		*@param sqlType :  输出参数数据类型HSQL_DATATYPE_STRING or HSQL_DATATYPE_CHAR or HSQL_DATATYPE_LONG or HSQL_DATATYPE_DOUBLE 
		*@param scale   :  精度
		*@return HSDB_SUCESS or  HSDB_FAILURE
		*说明: 函数的返回值(return)也是通过此方法注册的
		*      当注册了return以后,在取输出参数时 getXXX(1) 取到的便是return 值
		*/
  		virtual int  FUNCTION_CALL_MODE registerOutParameter(int parameterIndex,
				                          int sqlType,
					                      int scale) = 0;
	//@}


    //@name 下面方法取输出参数,如果有结果集返回，则应先取完结果集(参见IResultSet)，再取输出参数
	//@{
		///根据参数位置获取返回参数值 类型  char * ； c  的字符串类型
		/** 
		*@param parameterIndex:int 输出参数位置
		*@return :对应值，注意：失败时返回空串""，而非NULL
		*/
		virtual  char *  FUNCTION_CALL_MODE getString(int parameterIndex) = 0;

		///根据参数位置获取返回参数值 char.
		/** 
		* @param parameterIndex:int 输出参数位置
		* @return :对应值 ，失败时，返回0
		*/
		virtual char   FUNCTION_CALL_MODE getChar(int parameterIndex) = 0;
  
		///根据参数位置获取返回参数值 long.
		/** 
		*@param parameterIndex:int 输出参数位置
		*@return :对应值
		*/
		virtual int  FUNCTION_CALL_MODE getInt(int parameterIndex) = 0;
  
		///根据参数位置获取返回参数值 double.
        /** 
		*@param parameterIndex:int 输出参数位置
		*@return : 对应值
		*/
		virtual double FUNCTION_CALL_MODE getDouble(int parameterIndex) = 0;
	//@}

		/// 设置参数为NULL, 目前只支持部分数据库，比如（sql server）
		/** 
		*@param parameterIndex:int 参数位置
		*@return HSDB_SUCESS or  HSDB_FAILURE
		*/
		virtual int  FUNCTION_CALL_MODE setNULL(int parameterIndex) = 0;
    
};

//----------作为可动态加载的基础服务组件，必须定义以下引出函数---------

#ifdef __cplusplus
extern "C" { 
#endif

	///组件初始化xxxxInit()
	/**
	 *@return int 版本号 yyyymmdd形式
	 */
	int  FUNCTION_CALL_MODE HSDBSvrInit(void *lpInst, PFOnSetTimeOut lpFunc= NULL);
	
	///取服务接口句柄 getxxxxInstance()
	/**
	 *@return void * 基础服务句柄 
	 */
	IKnown * FUNCTION_CALL_MODE GetHSDBSvrInstance(void);

	///取服务接口依赖服务
	/**
	 *@param iIndex 
	 *@return IKnown * 依赖服务标识 
	 */
	char * FUNCTION_CALL_MODE GetHSDBSvrDependService(void *);
	
	///返回统一的AS基础服务组件查询接口 getxxxInfo()
	/**当基础服务组件动态加载时，通过本接口或以获取服务信息(包括xxxxInit(),getxxxxInterface()函数指针)
	 *@param void ** ppv    基础服务组件信息(输出参数)，
	 *@return 返回0表示查到所要的接口，否则返回负数
	 */
	int FUNCTION_CALL_MODE GetHSDBSvrInfo(int iIndex, tagBaseServiceInfo * ppv );

#ifdef __cplusplus
  }
#endif
 
#endif
