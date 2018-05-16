/* 
 * File:   Common.h
 * Author: zhouyx11685
 * Description: 通用函数、常量
 * Created on 2015年11月9日, 下午4:10
 */

#ifndef COMMON_H
#define	COMMON_H

#include <pthread.h>
#include "hshead.h"

/*通用错误常量定义*/

//业务同步错误
#define     SYNC_ERR_OTHER                                                      1000        //其他情况错误信息
#define     SYNC_ERR_GET_TABLE_COUNT                                            1001        //获取记录条数失败
#define     SYNC_ERR_CLEAR_TEMP_TABLE                                           1002        //清除中间转换表失败
#define     SYNC_ERR_QUERY_SRC_TABLE                                            1003        //查询来源表数据失败
#define     SYNC_ERR_EXPORT_DATA_TEMP                                           1004        //导出数据到中间表失败
#define     SYNC_ERR_IMPORT_DATA_DST                                            1005        //导入数据到目标表失败
#define     SYNC_ERR_MALLOC_MEMORY                                              1006        //申请分配内存失败
#define     SYNC_ERR_VALIDATE_FIELD                                             1007        //字段兼容性校验失败
#define     SYNC_ERR_LOCK_MUTEX                                                 1008        //同步互斥锁上锁失败
#define     SYNC_ERR_UNLOCK_MUTEX                                               1009        //同步互斥锁解锁失败
#define     SYNC_ERR_DROP_TEMP_TABLE                                            1010        //删除中间转换表结构失败
#define     SYNC_ERR_CREATE_TEMP_TABLE                                          1011        //创建中间转换表失败
#define     SYNC_ERR_GET_SYNC_INFO                                              1012        //获取同步字段配置信息失败
#define     SYNC_ERR_VIOLATED                                                   1013        //重复数据错误信息


//DB操作错误
#define     DB_ERR_OTHER                                                        2000        //其他数据库错误
#define     DB_ERR_CONNECTION                                                   2001        //数据库连接失败
#define     DB_ERR_CURSOR                                                       2002        //数据库游标操作失败
#define     DB_ERR_QUERY                                                        2003        //数据库查询操作失败
#define     DB_ERR_INSERT                                                       2004        //数据库插入操作失败
#define     DB_ERR_UPDATE                                                       2005        //数据库更新操作失败
#define     DB_ERR_DELETE                                                       2006        //数据库更新操作失败
#define     DB_ERR_DROP_INDEX                                                   2007        //删除主键/索引失败
#define     DB_ERR_RECOVER_INDEX                                                2008        //恢复主键/索引失败

#ifdef __cplusplus
extern "C"
{
#endif
    //int ConnectToDB();
    int PackAnswerPackage(IF2Packer* lpOutPacker, int nErrorNo, char* sErrorInfo, char* sErrorPathInfo);
    //TODO

#ifdef __cplusplus
}
#endif

#endif	/* COMMON_H */

