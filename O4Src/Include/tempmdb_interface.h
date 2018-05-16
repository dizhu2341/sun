#ifndef __tempmdb_interface__
#define __tempmdb_interface__
#include <Include/plugin_interface.h>
///插件接口ID定义
#define SID_TEMPMDB "com.hundsun.fbase.tempmdb"


/**@name 内存临时表相关常量 */
//@{
///字段名最大长度
const int FIELD_NAME_LENGTH	 = 256; 
///字段值最大长度
const int FIELD_VALUE_LENGTH     = 256;  
//@}

/**@name 内存临时表相关数据结构 */
//@{

///描述结果集字段的所有属性
typedef struct tagField
{
	///字段名
    char szName[FIELD_NAME_LENGTH+1];
	///字段类型
    char cType; 
    ///字段长度
    int iLength;  
	///字段小数位数
	int iScale;
	
} FIELD, * LPFIELD;

///带字段序号的字段值结构
typedef struct tagFieldValueNo
{
	///字段号(从0开始)
	unsigned int iNo;
	///字段值
	char szValue[FIELD_VALUE_LENGTH+1];
	
} FVNO, * LPFVNO;

///带字段名的字段值结构
typedef struct tagFieldValueName
{
	///字段名
	char szName[FIELD_NAME_LENGTH+1];
	///字段值
	char szValue[FIELD_VALUE_LENGTH+1];
	
} FVNAME, * LPFVNAME;

///临时表头尾标识
enum POSITION 
{
	///头部
	HEAD = 0,
		///尾部
		TAIL = 1
};

///返回值
enum result_code 
{ 
	///执行成功
    ok						= 0,
		///表不存在
		table_not_found			= -1,
		///元数据格式不一致
		incompatible_metadata	= -2,
		///插入记录失败
		insert_fail				= -3,
		///超出范围
		out_of_range			= -4,
		///输入参数不合法
		illegal_input_para		= -5,
		///没找到
		not_found				= -6,
		///创建表失败
		create_table_fail		= -7,
		///内存分配失败
		alloc_memory_fail		= -8,
		///汇总表失败
		summarize_fail			= -9
};
//@}

///内存临时表服务操作接口
/**
* 组件开发人员通过本接口创建内存临时表、操作内存临时表(不包含扫描结果集)
 */
struct IF2TMdbService: public IKnown
{
	///查询内存临时表
	/**
	* 为了统一结果集的查询
	*
	* 如果 lRecordNo = 0 或 lRecordNo = 1 并且 *lpRecordNum = 0，则返回包含该临时表所有记录的结果集
	*
	* 否则返回包含 lRecordNo 记录号开始的 lRecordNum 条记录的结果集
	*
	* lRecordNo 越界，则查询失败；lRecordNum 超出实际条数，则返回包含实际条数的结果集
	* @param unsigned long lHandle 内存临时表句柄 
	* @param unsigned long lRecordNo 开始记录号，缺省值为1
	* @param unsigned long * lpRecordNum 实际返回的记录总条数，缺省值为0, 输入输出参数
    * @return IF2ResultSet * 成功 结果集指针，失败 NULL; 该结果集不需要释放
    */
	virtual IF2ResultSet * FUNCTION_CALL_MODE query(unsigned long lHandle, unsigned long lRecordNo = 1, unsigned long * lpRecordNum = 0) = 0;
	
	///追加结果集到指定临时表头部或尾部
	/**
	* 追加前必须先创建表
	* @param unsigned long lHandle 临时表句柄
	* @param IF2ResultSet * pSet 结构集指针
	* @param POSITION pos=TAIL 结果集追加位置，缺省值为尾部
	* @return int 成功 追加的记录条数 >=0，失败 -1
	 */
	virtual int FUNCTION_CALL_MODE appendResultSet(unsigned long lHandle, IF2ResultSet * pSet, POSITION pos=TAIL) = 0;
	
	///根据结果集各个字段描述信息，创建内存临时表
	/**
	* 创建完成后，将数据导入临时表
	* @param IResultSet * pSet 结构集指针
	* @param const char * szCreater 创建者描述，缺省值为空
	* @return unsigned long  成功 临时表句柄 >=0，失败 <0
	 */
	virtual long FUNCTION_CALL_MODE createByResultSet(IF2ResultSet * pSet, const char * szCreater="") = 0;

	///聚合汇总结果集
	/**
	* 聚合汇总前必须先创建表，如果汇总的字段是字符串或字符，则用新结果集中的内容替换
	*
	* 扫描结果集，按指定的聚合字段，累加所有汇总字段的值
	* @param unsigned long lHandle 内存临时表句柄 
	* @param unsigned int iComNum 聚合字段个数
	* @param char * * pComFieldName 聚合字段名指针数组首地址
	* @param unsigned int iSumNum 汇总字段个数
	* @param char * * pSumFieldName 汇总字段名指针数组首地址
	* @param IF2ResultSet * pSet 结构集指针
	* @param unsigned int iTag 汇总标记，0 不汇总，>=1 汇总(在结果集最后添加一条汇总数据)；缺省汇总
	* @return int 成功 0，失败 -1
	 */
	virtual int FUNCTION_CALL_MODE comAndSumResultSet(unsigned long	lHandle, 
													unsigned int	iComNum, 
													char **		szComFieldName,
													unsigned int	iSumNum, 
													char **		szSumFieldName, 
													IF2ResultSet *	pSet,
													unsigned int	iTag=1) = 0;

	///删除内存临时表，释放内存空间
	/**
	* @param unsigned long lHandle  临时表句柄
	* @return int  成功返回 0，失败返回 -1
	 */
	virtual int FUNCTION_CALL_MODE drop(unsigned long lHandle) = 0;

	///删除所有临时表
	/** 
	* @return void
	 */
	virtual void FUNCTION_CALL_MODE dropAll(void) = 0;
};


///定义插件库标准引出函数，功能及参数说明参见Include/plugin_interface.h
#ifdef __cplusplus
extern "C" {
#endif
  ///取插件实例
  IKnown * FUNCTION_CALL_MODE GetTempMdbInstance();
  ///插件初始化
  int FUNCTION_CALL_MODE TempMdbInit(void * lpInstance);
  ///取插件依赖的其他插件ID串
  char *  FUNCTION_CALL_MODE GetTempMdbDependSvr(void * lpInstance);
  ///查询插件库中的插件信息
  int FUNCTION_CALL_MODE GetTempMdbInfo(int iIndex, tagBaseServiceInfo * ppv );
#ifdef __cplusplus
}
#endif

#endif

