/*
 * Headfile: s_helper.h
 * Author : 周伟明.
 * Date   : 2008/10/20.
 * Notes  : 工具函数实现
 * Modify : 版本       修改日期   修改人         修改单       修改说明
 *				  V8.0.6.0   20100614   刘元召         内部         经纪业务运营平台V2.0项目2011基线建立
 *          V8.0.5.4   20110415   王仁云         20110415019  增加函数SynCallSubServicePack1和SubServiceCallPack1
 *          V8.0.5.2   20100702   周伟明         20100702016  函数【CheckDbLinkMethod】修改修改iSqlcode <= -25401 && iSqlcode >= -25409判断
 *                                                            函数【GetLibVersion】修改版本为V8.0.5.2
 *          V8.0.5.1   20100630   周伟明         20100630020  函数【CheckDbLinkMethod】修改SQLCODE <= -3100 and SQLCODE > -3133判断
 *                                                            函数【GetLibVersion】修改版本为V8.0.5.1
 *          V8.0.5.0   20100414   周伟明         内部         基线
 *          V8.0.4.2   20091212   周伟明         内部         [SynCallSubService]修改超时时间从原始包中获取,修改li_timeout和li_timeout类型从unsigned int修改为int
 *          V8.0.4.1   20091027   周伟明         内部         调用子服务异常时候Proc插件不做异常数据库记录
 *          V8.0.4.0   20090926   周伟明         内部         基线
 *          V8.0.3.2   20090924   周伟明         内部         增加函数CheckDbLinkMethod
 *          V8.0.3.1   20090727   周伟明         内部         AsynPostMessage函数增加接口sPlugInName
 *          V8.0.3.0   20090626   周伟明         内部         打包
 *          V8.0.2.0   20090420   周伟明         内部         打包
 *          V8.0.1.0   20090120   周伟明         内部         打包
 *          V8.0.0.0   20081014   周伟明         内部         创建
 */

#ifndef s_helper_h
#define s_helper_h

#include "hshead.h"

/*==========================================================
 * Function   : PackResultSet
 * Description: 结果集打包输出
 * Input      : IF2ResultSet * lpInUnPacker	结果集
 * Output     : IF2Packer * lpOutPacker     输出
 * Return     : 0		    成功
 *				      <>0     失败 		
 * Author     : zhouwm
 * Date       : 2008/10/20.
 ==========================================================*/
extern int PackResultSet(IF2ResultSet * lpInUnPacker,IF2Packer * lpOutPacker);


/*==========================================================
 * Function   : MutiResultSetPack
 * Description: 多结果集打包
 * Input      : IUnPacker  lpResultSet  结果集
 * Output     : IPacker    lpOutPacker  输出结果集
 * Return     : 0   成功
 *        <>0     失败
 * Author     : zhouwm
 * Date       : 2006/08/15
 ==========================================================*/
extern int MutiResultSetPack(IF2UnPacker * lpResultSet,IF2Packer * lpOutPacker);

/*==========================================================
 * Function   : SynCallSubService
 * Description: 子服务调用
 * Input      : IASContext *pContext              接口上下文
 *              IF2Packer * lpReqPacker           输入接口包
 *              IESBMessage ** lppAnsMessage      数据包
 *              int iTimeOut                      超时时间
 *              unsigned int dwFuncNo             功能号
 *              unsigned int dwBranchNo           营业部编号
 *              unsigned int dwSystemNo           系统编号
 *              unsigned int dwSubSystemNo        子系统编号
 * Output     : 
 * Return     : 0 成功
 *              -1 失败
 * Author     : zhouwm
 * Date       : 2008/10/20
 ==========================================================*/
extern int SynCallSubService(IAS2Context * lpContext,IF2Packer * lpReqPacker, IESBMessage ** lppAnsMessage,unsigned int iTimeOut,unsigned int dwFuncNo,unsigned int dwBranchNo,unsigned int dwSystemNo,unsigned int dwSubSystemNo,unsigned int dwBusinessNo);

/*==========================================================
 * Function   : SubServiceCall
 * Description: 原子服务调用扩展
 * Input      : IASContext *pContext              接口上下文
 *              IF2Packer * lpReqPacker           输入接口包
 *              IF2Packer * lpOutPacker           数据包
 *              int iTimeOut                      超时时间(默认5000ms)
 *              int iFuncNo                       功能号
 *              int iBranchNo                     营业部编号
 *              int iSystemNo                     系统编号
 *              int iSubSystemNo                  子系统编号
 * Output     : 
 * Return     : 0 成功
 *              -1 失败
 * Author     : zhouwm
 * Date       : 2008/10/20
 ==========================================================*/
extern int SubServiceCall(IAS2Context * lpContext,IF2UnPacker * lpInUnPacker, IF2Packer * lpOutPacker,unsigned int iTimeOut,unsigned int iFuncNo,unsigned int iBranchNo,unsigned int iSystemNo,unsigned int iSubSystemNo);

/*==========================================================
 * Function   : SubServiceCallTrans
 * Description: 事务原子服务调用扩展
 * Input      : IASContext *pContext              接口上下文
 *              IF2Packer * lpReqPacker           输入接口包
 *              IF2Packer * lpOutPacker           数据包
 *              IAS2TM * lpTransMonitor           事务模拟器
 *              int iTimeOut                      超时时间(默认5000ms)
 *              int iFuncNo                       功能号
 *              int iBranchNo                     营业部编号
 *              int iSystemNo                     系统编号
 *              int iSubSystemNo                  子系统编号
 * Output     : 
 * Return     : 0 成功
 *              -1 失败
 * Author     : zhouwm
 * Date       : 2008/10/20
 ==========================================================*/
extern int SubServiceCallTrans(IAS2Context * lpContext,IF2UnPacker * lpInUnPacker, IF2Packer * lpOutPacker,IAS2TM * lpTransMonitor,unsigned int iTimeOut,unsigned int iFuncNo,unsigned int iBranchNo,unsigned int iSystemNo,unsigned int iSubSystemNo);

/*==========================================================
 * Function   : SystemErrorPacker
 * Description: 错误信息打包输出
 * Input      : IF2Packer * lpOutPacker           输出包
 *              char *sError_PathInfo             错误路径信息
 *              int iError_no                     错误号
 *              char *sError_Info                 错误信息
 * Output     : 
 * Return     : 0 成功
 *              -1 失败
 * Author     : zhouwm
 * Date       : 2008/10/20
 ==========================================================*/
extern int SystemErrorPacker(IF2Packer * lpOutPacker,const char * sErrorPathInfo,int iErrorNo,const char * sErrorInfo);

/*==========================================================
 * Function   : WriteSystemLog
 * Description: 记录系统日志
 * Input      : IASContext *pContext              接口上下文
 *              char *sError_PathInfo             错误路径信息
 *              int iError_no                     错误号
 *              char *sError_Info                 错误信息
 *              int iError_id                     系统错误编号
 *              char *sError_SysInfo              系统错误信息
 * Output     : 
 * Return     : 0 成功
 *              -1 失败
 * Author     : zhouwm
 * Date       : 2008/10/20
 ==========================================================*/
extern int WriteSystemLog(IAS2Context * lpContext,char *sError_PathInfo,int iError_no,char *sError_Info,int iError_id,char *sError_SysInfo);

/*==========================================================
 * Function   : WriteTimeStamp
 * Description: 记录时间戳
 * Input      : IASContext *pContext              接口上下文
 *              char *sWriteSysInfo               记录时间戳信息
 * Output     : 
 * Return     : 0 成功
 *              -1 失败
 * Author     : zhouwm
 * Date       : 2008/10/20
 ==========================================================*/
extern int WriteTimeStamp(IAS2Context * lpContext,char *sWriteSysInfo);

/*==========================================================
 * Function   : AsynPostMessage
 * Description: 异步发生消息（2.0包发送）
 * Input      : IASContext *pContext              接口上下文
 *              IF2Packer * lpOutPacker           推送消息包
 *              char * sErrorPathInfo             错误路径信息
 *              char * iErrorNo                   错误代码
 *              char * sErrorInfo                 错误信息
 *              char * sTargetAr                  路由AR
 *              char * sTransName                 推送客户端
 *              int    iFunctionID                推送功能号
 *              char * sPlugInName                插件名
 * Output     : 
 * Return     : 0 成功
 *              -1 失败
 * Author     : zhouwm
 * Date       : 2008/10/20
 ==========================================================*/
extern int AsynPostMessage(IAS2Context * lpContext,IF2UnPacker * lpInUnPacker,char * sErrorPathInfo,char * sErrorInfo,char * sTargetAr,char *sTransName,int iFunctionID,int iIssueType=0,char *sPlugInName=NULL);

/*==========================================================
 * Function   : AsynPostMessagePack1
 * Description: 异步发生消息（2.0包转成1.0包再发送）
 * Input      : IASContext *pContext              接口上下文
 *              IF2Packer * lpOutPacker           推送消息包
 *              char * sErrorPathInfo             错误路径信息
 *              char * iErrorNo                   错误代码
 *              char * sErrorInfo                 错误信息
 *              char * sTargetAr                  路由AR
 *              char * sTransName                 推送客户端
 *              int    iFunctionID                推送功能号
 * Output     : 
 * Return     : 0 成功
 *              -1 失败
 * Author     : zhouwm
 * Date       : 2008/10/20
 ==========================================================*/
extern int AsynPostMessagePack1(IAS2Context * lpContext,IF2UnPacker * lpInUnPacker,char * sErrorPathInfo,char * sErrorInfo,char * sTargetAr,char *sTransName,int iFunctionID,int iIssueType=0);


/*==========================================================
 * Function   : GetCancelSerialNo
 * Description: 取中间件流水号
 * Input      : IASContext *pContext              接口上下文
 *              char *sCancelSerialNo             流水号
 * Output     : 
 * Return     : 0 成功
 *              -1 失败
 * Author     : zhouwm
 * Date       : 2008/10/20
 ==========================================================*/
extern int GetCancelSerialNo(IAS2Context * lpContext,char *sCancelSerialNo);


//校验数据库连接情况
//  int iDbLinkMethod 数据库连接模式
//  int iSqlcode      SQL错误代码
//  如果错误sqlcode为-28或者sqlcode为-1012或者（数据库连接模式为select、sqlcode大于等于3100、sqlcode小于3133）则返回-1，需要进行数据库重连
/*==========================================================
 * Function   : CheckDbLinkMethod
 * Description: 校验数据库连接情况
 * Input      : IConnection * lpConn              数据库连接
 *              int iSqlcode                      SQL错误代码
 * Output     : 
 * Return     : 0 成功
 *              -1 失败
 * Author     : zhouwm
 * Date       : 2009/09/24
 ==========================================================*/
extern int CheckDbLinkMethod(IConnection * lpConn,int iSqlcode);

/*==========================================================
 * Function   : SynCallSubServicePack1
 * Description: 子服务调用输出为pack1
 * Input      : IASContext *pContext              接口上下文
 *              IF2Packer * lpReqPacker           输入接口包
 *              IESBMessage ** lppAnsMessage      数据包
 *              int iTimeOut                      超时时间
 *              unsigned int dwFuncNo             功能号
 *              unsigned int dwBranchNo           营业部编号
 *              unsigned int dwSystemNo           系统编号
 *              unsigned int dwSubSystemNo        子系统编号
 * Output     : 
 * Return     : 0 成功
 *              -1 失败
 * Author     : wangry
 * Date       : 2011/04/15
 ==========================================================*/
extern int SynCallSubServicePack1(IAS2Context * lpContext,IF2Packer * lpReqPacker, IESBMessage ** lppAnsMessage,unsigned int iTimeOut,unsigned int dwFuncNo,unsigned int dwBranchNo,unsigned int dwSystemNo,unsigned int dwSubSystemNo,unsigned int dwBusinessNo);

/*==========================================================
 * Function   : SubServiceCallPack1
 * Description: 原子服务调用扩展，输出为Pack1
 * Input      : IASContext *pContext              接口上下文
 *              IF2Packer * lpReqPacker           输入接口包
 *              IF2Packer * lpOutPacker           数据包
 *              int iTimeOut                      超时时间(默认5000ms)
 *              int iFuncNo                       功能号
 *              int iBranchNo                     营业部编号
 *              int iSystemNo                     系统编号
 *              int iSubSystemNo                  子系统编号
 * Output     : 
 * Return     : 0 成功
 *              -1 失败
 * Author     : wangry
 * Date       : 2011/04/15
 ==========================================================*/
extern int SubServiceCallPack1(IAS2Context * lpContext,IF2UnPacker * lpInUnPacker, IF2Packer * lpOutPacker,unsigned int iTimeOut,unsigned int iFuncNo,unsigned int iBranchNo,unsigned int iSystemNo,unsigned int iSubSystemNo);


#endif

