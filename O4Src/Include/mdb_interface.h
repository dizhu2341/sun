/*******************************************************
  源程序名称:mdb_interface.h
  软件著作权:恒生电子股份有限公司
  系统名称:  HZHSGS金融业务基础件V1.0
  模块名称:  AS内存数据库模块
  功能说明:  内存数据库操作接口
	         内存数据库操作接口，包括：
				 专用查询接口(不包括内存数据库结果集查询部分)；
				 更新后台和自动同步接口；
				 手工同步接口；

  相关文档:  概要设计接口部分  
  
  作    者:  xiasj
  开发日期:  20040211创建
  备    注:  
          1  where 语句中,参数和运算符号之间不能有空格.比如 where stock_code='600600' 而不能where stock_code = '600600' 
  修改人员：
  修改日期： 
  修改说明：
*********************************************************/

#ifndef AS_MDB_H
#define AS_MDB_H

#include <Include/plugin_interface.h>
#include <Include/resultset.h>

#define SID_MDB "com.hundsun.fbase.mdb"

/// 自定义函数

extern bool contains(char* arg1, char* arg2);

///内存数据库服务接口
struct IMdbService:IKnown
{
	///普通查询
	/**
	 * 如果该表没有配置，则返回NULL
	 * 如果该表不可用，则根据配置和输入条件从后台获取结果
	 * 如果该表配置为部分缓存，则根据配置和输入条件从后台获取结果
	 * 如果该表配置为整表缓存，则根据输入条件从缓存获取结果
	 * 如果 szWhere="" 或 szWhere=NULL ，则相当于无查询条件
	 * @param int session 查询会话，必须从上下文接口 getMDBSession 或 接口函数 getSession 获取
	 * @param const char * szTableName 表名
	 * @param const char * szSelect 相当于SQL语句中的SELECT子句，不带SELECT关键字，比如“(PriKey, Description)"
     * @param const char * szWhere 查询条件，相当于SQL语句中的where子句，不带where关键字，比如"id<100"
     * @return IResultSet * 成功 返回结果集指针，失败 返回NULL
     */
	virtual IF2ResultSet * FUNCTION_CALL_MODE Query(int session, const char * szTableName, const char * szSelect="*", const char * szWhere="")=0; 
	///按主键值查询
	/**
	 * 如果该表没有配置，则返回NULL
	 * 如果该表不可用，则根据配置和输入条件从后台获取结果
	 * 如果该表配置为部分缓存，则先从缓存获取结果；如果没有，则再根据配置和输入条件从后台获取结果，并缓存结果
	 * 如果该表配置为整表缓存，则从缓存获取
	 * @param int session 查询会话，必须从上下文接口 getMDBSession 或 接口函数 getSession 获取
	 * @param const char * szTableName 表名
	 * @param const char * szSelect 相当于SQL语句中的SELECT子句，不带SELECT关键字，比如“(PriKey, Description)"
     * @param const char * szPrimeKey 主键值（字段值组合）描述，比如"PriKey=100"（"index=1 name='xiasj'")
     * @return IResultSet * 成功 返回结果集指针（一条记录），失败 返回NULL
     */
	virtual IF2ResultSet * FUNCTION_CALL_MODE QueryByKey(int session, const char * szTableName, const char * szSelect, const char * szPrimeKey)=0; 
	///更新数据库中的记录，如果该表缓存，则自动同步缓存
	/**
	 * @param const char * szTableName 表名
	 * @param const char * szSet 相当于UPDATE语句中的SET子句，不带SET关键字，比如“id=100, age=15”
	 * @param const char * szWhere 相当于SQL语句中的where条件子句，不带where关键字，比如“id<100 AND id>50 OR ...”
	 * @return int 成功返回 0，失败返回 -1
	 */
	virtual int FUNCTION_CALL_MODE Update(const char * szTableName, const char * szSet, const char * szWhere)=0;
	///删除数据库中的记录，如果该表缓存，则自动同步缓存
	/**
	 * @param const char * szTableName 表名
	 * @param const char * szWhere 相当于SQL语句中的where条件子句，不带where关键字，比如“id<100 AND id>50 OR ...”
	 * @return int 成功返回 0，失败返回 -1
	 */
	virtual int FUNCTION_CALL_MODE DeleteFrom(const char * szTableName, const char * szWhere)=0;
	///插入记录到数据库中，如果该表缓存，则自动同步缓存
	/**
	 * 字段名和字段值必须一一对应
	 * szWhere 缺省值为""，缓存同步方式为整表更新，效率低；如果给 szWhere 赋主键值字符串，则缓存同步方式为部分更新，效率高
	 * @param const char * szTableName 表名
	 * @param const char * szColList 字段名列表，如"PriKey, Description"
	 * @param const char * szValueList 字段名对应的字段值列表，如"123, 'A description of part 123.'"
	 * @param const char * szWhere 该条记录的主键值字符串，不带where关键字，比如“id=100”，id为主键
	 * @return int 成功返回 0，失败返回 -1
	 */
	virtual int FUNCTION_CALL_MODE Insert(const char * szTableName, const char * szColList, const char * szValueList, const char * szWhere="")=0;
	///同步更新内存数据库中的表
	/**
	 * 用于存储过程结束手工同步缓存的表
	 * @param const char * szTableName 表名
	 * @param const char * szWhere 相当于SQL语句中的where条件子句，不带where关键字，比如“id<100 AND id>50 OR ...”
	 * @return int 成功返回 0，失败返回 -1
	 */
	virtual int FUNCTION_CALL_MODE Sync(const char * szTableName, const char * szWhere)=0;
	///获取查询会话
	/**
	 * @return int 成功返回 >=0，失败返回 -1
     */
	virtual int FUNCTION_CALL_MODE GetSession()=0; 
	///释放查询会话
	/**
	 * @param int session 查询会话
	 * @return int 成功返回 0，失败返回 -1
     */
	virtual int FUNCTION_CALL_MODE FreeSession(int session)=0;
};

///定义插件库标准引出函数，功能及参数说明参见Include/plugin_interface.h
#ifdef __cplusplus
extern "C" {
#endif
  ///取插件实例
  IKnown * FUNCTION_CALL_MODE GetMDBInstance();
  ///插件初始化
  int FUNCTION_CALL_MODE MDBInit(void * lpInstance);
  ///取插件依赖的其他插件ID串
  char *  FUNCTION_CALL_MODE GetMDBDependSvr(void * lpInstance);
  ///查询插件库中的插件信息
  int FUNCTION_CALL_MODE GetMDBInfo(int iIndex, tagBaseServiceInfo * ppv );
#ifdef __cplusplus
}
#endif

#endif

