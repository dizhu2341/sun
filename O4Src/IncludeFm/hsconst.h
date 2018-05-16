/************************************************************
 *** Headfile   : hsconst.h
 *** Author   : zhouyx11685
 *** Date     : 2016-06-27
 *** Notes    : 常量C头文件
 ************************************************************/
// 修改版本    修改日期    修改单         申请人    负责人    修改内容     修改原因    备注 
// V1.0.0.0    20141210                                                                     

#ifndef _HSCONST_H
#define _HSCONST_H
#define   O4DB                                              "o4db"              //O4系统数据库
#define   CNST_ERRORINFO_LEN                                500                 //错误信息长度
#define   ZDJY                                              11                  //指定交易
#define   NORMAL                                            '1'                 //正常
#define   CANCEL                                            '2'                 //注销
#define   CXZD                                              12                  //撤销指定
#define   BUY                                               1                   //买入
#define   SALE                                              2                   //卖出
#define   NOT_ASSIGN                                        '1'                 //未指定
#define   IS_ASSIGN                                         '2'                 //已指定
#define   CAN_OVERSALE                                      '3'                 //当日可卖空
#define   SH                                                1                   //上海
#define   SZ                                                2                   //深圳
#define   DEFAULT_STR_NULL                                  " "                 //默认空字符串
#define   DEFAULT_FILTER_FIELD_NULL                         " "                 //
#define   CONST_FLAG_NO                                     '0'                 //
#define   CONST_FLAG_FALSE                                  '0'                 //
#define   CONST_FLAG_YES                                    '1'                 //
#define   CONST_FLAG_TRUE                                   '1'                 //
#define   O3DB                                              "o3db"              //O32数据库（同步数据用）
#define   CNST_CHAR_DEFAULTVALUE                            ' '                 //单字符默认值
#define   CNST_DOUBLE_ZERO                                  0.00000001          //浮点0值判断
#define   CNST_SQLSTR_LEN                                   16000               //SQL字符串长度
#define   INVALID_BROKER_ID                                 -9999               //无效的券商ID
#define   INVALID_MARKET_NO                                 -9999               //无效的市场编号
#define   INVALID_CAPITAL_ACCOUNT_ID                        -9999               //无效的资金账户ID
#define   INVALID_STOCK_TYPE                                -9999               //无效的证券类别
#define   INVALID_ENTRUST_DIRECTION                         -9999               //无效的委托方向
#define   INVALID_FEE_TYPE                                  -9999               //无效的费用类型
#define   INVALID_TRADE_PLATFORM_ID                         -9999               //无效的交易平台ID
#define   CNST_LOGERROR                                     1                   //错误日志,必定输出(1)无论是数据库错误，还是程序执行错误，入参校验出错等
#define   CNST_LOGPARAM                                     2                   //服务的入参出参信息(1)LS,LF,AS,AF的入参和出参
#define   CNST_LOGWARN                                      3                   //警告(1)对于数据有疑惑,但是也是能执行的这种情况
#define   CNST_LOGDETAIL                                    4                   //输出服务处理各步骤的日志(1)可以记录程序执行到某步骤等更容易分析程序执行状况的日志
#define   CNST_LOGDEBUG                                     5                   //输出最明细的调试日志:(1)可以精确到每步骤之后的关键数据(2)关键临时变量的实时值
#define   INVALID_INTER_CODE                                -9999               //无效的证券内码
#define   INVALID_FUND_TYPE                                 -9999               //无效的账户类别
#define   EI_FUNC_TIMEOUT                                   300000              //EI节点服务的调用超时时间
#define   INVALID_OPTION_TYPE                               -9999               //无效的期权标的类型
#endif
