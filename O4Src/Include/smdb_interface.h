#ifndef __smdb_interface__
#define __smdb_interface__
#include <Include/plugin_interface.h>
#include <Include/biz_comp_interface.h>
#include <Include/pack_interface.h>
///插件接口ID定义
#define SID_SMDB "com.hundsun.fbase.smdb"


///定义插件库标准引出函数，功能及参数说明参见Include/plugin_interface.h
#ifdef __cplusplus
extern "C" {
#endif
  ///取插件实例
  IKnown * FUNCTION_CALL_MODE GetsmdbInstance();
  ///插件初始化
  int FUNCTION_CALL_MODE smdbInit(void * lpInstance);
  ///取插件依赖的其他插件ID串
  char *  FUNCTION_CALL_MODE GetsmdbDependSvr(void * lpInstance);
  ///查询插件库中的插件信息
  int FUNCTION_CALL_MODE GetsmdbInfo(int iIndex, tagBaseServiceInfo * ppv );
#ifdef __cplusplus
}
#endif

///此结构用于表示所有的key与value值
typedef struct  tagDataNode 
{
	void * lpData;           //数据指针
	unsigned int  iDataLen;  //数据长度
}DATA, * LPDATA;

#define INTDATA(var,data)   DATA var ={&data,sizeof(int)}

#define STRDATA(var,data)   DATA var ={(void *)data, strlen(data)} 

#define INT_KEY  'I'
#define STR_KEY  'S'

///内存表接口
/**维护多条内存记录（key-value对），所有记录key值唯一.
* 写数据时，记录不能删除，key值不能修改
* 
*/

///插件接口定义
struct ISMDBTable: public IKnown
{
	///释放自己
	virtual void FUNCTION_CALL_MODE Destroy(void)=0;

	///按主键取一条记录(脏读，本方法返回时，数据区已不加锁)
	/**
	*@param  unsigned int  iKeyValue            主键值
	*@return DBt               记录值 
	*/   
	virtual LPDATA  FUNCTION_CALL_MODE Get(LPDATA key )=0;

	///设置一条记录
	/**注：当key为字符串型时，要求key直接引用value中的字符串地址。
	*@param  DBt key             主键值key
	*@param  DBt value            数据value
	*@return int   
	*/   
	virtual int  FUNCTION_CALL_MODE Put(LPDATA key, LPDATA value )=0;

	///按主键取一条记录(加写锁读，本方法返回时，数据区加写锁。调updateEnd()释放 )
	/**
	*@param  char *  sKeyValue          主键值
	*@return DBt *                        记录值 
	*/   
	virtual LPDATA  FUNCTION_CALL_MODE GetForUpdate(LPDATA key)=0;

	///设置一条记录
	/**
	*@param  char *        sKeyValue            主键值key
	*@param  DBt           lpData               数据value
	*@return int   
	*/   
	virtual int  FUNCTION_CALL_MODE UpdateEnd(LPDATA key )=0;

	///取记录数
	/**返回的记录数为最大的RowID-1
	*@return unsigned int   
	*/   
	virtual unsigned int  FUNCTION_CALL_MODE GetCount()=0;

	///按记录号取数据
	/**内存表从0开始为每增加的一条记录分配一个RowID，通过RowID可以快速获取数据
	*@param unsigned int dwRowID
	*@return int   
	*/   
	virtual LPDATA  FUNCTION_CALL_MODE GetByID(unsigned int dwRowID)=0;

	///对指定记录加读锁
	virtual void  FUNCTION_CALL_MODE ReadLock(LPDATA key )=0;

	///释放指定记录的读锁
	virtual void  FUNCTION_CALL_MODE ReadUnLock(LPDATA key )=0;
};

///高级数据库访问服务
struct ISMDBService:IKnown
{
	///创建一个内存表
	/**创建一个内存表，指定表名
	*
	*@param const char * sName  内存表名字
	*@param int   iHashNodeNum    主键hash索引结点数(每个结点一个读写锁)
	*@param char  cKeyType        主键数据类型 I 整型 S字符串
	*@param int   iFlag           1 数据空间由用户分配
	*@return ISMDB *              返回一个内存表实例接口 
	*/   
	virtual ISMDBTable * FUNCTION_CALL_MODE CreateTable(  const char * sName,
		int   iHashNodeNum,
		char  cKeyType,
		int   iFlag)=0;
	///设置本服务所依赖的其他服务实例
	/**本服务希望调用者设置 SID_LOG 日志服务 
	*
	*@param  iSID               基础服务唯一标识
	*@param  void * lpService   基础服务接口
	*@return int 0成功，其他失败 
	*/   
	virtual int FUNCTION_CALL_MODE SetService(  char * iSID,
		void * lpService)=0;

};
#endif

