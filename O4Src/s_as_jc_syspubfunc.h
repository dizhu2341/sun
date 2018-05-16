

#ifndef _S_AS_JC_SYSPUBFUNC_H
#define _S_AS_JC_SYSPUBFUNC_H

#include "hshead.h" 
//AF_公共_内存表获取
int FUNCTION_CALL_MODE F3610015(IAS2Context * lpContext,IF2UnPacker * lpInUnPacker,IF2Packer * lpOutPacker,IConnection * lpParentConn=NULL);

//AF_公共_内存表同步
int FUNCTION_CALL_MODE F3610016(IAS2Context * lpContext,IF2UnPacker * lpInUnPacker,IF2Packer * lpOutPacker,IConnection * lpParentConn=NULL);

//AF_公共_获取市场是否开闭市状态--未开发
int FUNCTION_CALL_MODE F3610025(IAS2Context * lpContext,IF2UnPacker * lpInUnPacker,IF2Packer * lpOutPacker,IConnection * lpParentConn=NULL);

//AF_公共_获取业务配置信息--未开发
int FUNCTION_CALL_MODE F3610060(IAS2Context * lpContext,IF2UnPacker * lpInUnPacker,IF2Packer * lpOutPacker,IConnection * lpParentConn=NULL);

//AF_公共_获取债券信息
int FUNCTION_CALL_MODE F3610106(IAS2Context * lpContext,IF2UnPacker * lpInUnPacker,IF2Packer * lpOutPacker,IConnection * lpParentConn=NULL);

//AF_基础数据_获取缓存配置
int FUNCTION_CALL_MODE F3610602(IAS2Context * lpContext,IF2UnPacker * lpInUnPacker,IF2Packer * lpOutPacker,IConnection * lpParentConn=NULL);

//AF_基础数据_获取缓存加载SQL
int FUNCTION_CALL_MODE F3610601(IAS2Context * lpContext,IF2UnPacker * lpInUnPacker,IF2Packer * lpOutPacker,IConnection * lpParentConn=NULL);

//AF_公共_获取公司参数
int FUNCTION_CALL_MODE F3610011(IAS2Context * lpContext,IF2UnPacker * lpInUnPacker,IF2Packer * lpOutPacker,IConnection * lpParentConn=NULL);

//AF_公共_获取币种信息--未开发
int FUNCTION_CALL_MODE F3610057(IAS2Context * lpContext,IF2UnPacker * lpInUnPacker,IF2Packer * lpOutPacker,IConnection * lpParentConn=NULL);

//AF_公共_获取汇率信息--未开发
int FUNCTION_CALL_MODE F3610058(IAS2Context * lpContext,IF2UnPacker * lpInUnPacker,IF2Packer * lpOutPacker,IConnection * lpParentConn=NULL);

//AF_公共_获取交易日_工作日--未开发
int FUNCTION_CALL_MODE F3610024(IAS2Context * lpContext,IF2UnPacker * lpInUnPacker,IF2Packer * lpOutPacker,IConnection * lpParentConn=NULL);

//AF_公共_获取字典子项名称
int FUNCTION_CALL_MODE F3610105(IAS2Context * lpContext,IF2UnPacker * lpInUnPacker,IF2Packer * lpOutPacker,IConnection * lpParentConn=NULL);

//AF_公共_获取委托方向信息
int FUNCTION_CALL_MODE F3610054(IAS2Context * lpContext,IF2UnPacker * lpInUnPacker,IF2Packer * lpOutPacker,IConnection * lpParentConn=NULL);

//AF_基础数据_获取股指期货信息
int FUNCTION_CALL_MODE F3610804(IAS2Context * lpContext,IF2UnPacker * lpInUnPacker,IF2Packer * lpOutPacker,IConnection * lpParentConn=NULL);

//AF_公共_获取期货品种--未开发
int FUNCTION_CALL_MODE F3610055(IAS2Context * lpContext,IF2UnPacker * lpInUnPacker,IF2Packer * lpOutPacker,IConnection * lpParentConn=NULL);

//AF_公共_获取回购参数--未开发
int FUNCTION_CALL_MODE F3610107(IAS2Context * lpContext,IF2UnPacker * lpInUnPacker,IF2Packer * lpOutPacker,IConnection * lpParentConn=NULL);

//AF_公共_获取持仓席位
int FUNCTION_CALL_MODE F3610067(IAS2Context * lpContext,IF2UnPacker * lpInUnPacker,IF2Packer * lpOutPacker,IConnection * lpParentConn=NULL);

//AF_公共_获取初始化日期
int FUNCTION_CALL_MODE F3610002(IAS2Context * lpContext,IF2UnPacker * lpInUnPacker,IF2Packer * lpOutPacker,IConnection * lpParentConn=NULL);

//AF_公共_获取证券资料_通过风控关联代码--未开发
int FUNCTION_CALL_MODE F3610102(IAS2Context * lpContext,IF2UnPacker * lpInUnPacker,IF2Packer * lpOutPacker,IConnection * lpParentConn=NULL);

//AF_公共_获取前初始化日期
int FUNCTION_CALL_MODE F3610003(IAS2Context * lpContext,IF2UnPacker * lpInUnPacker,IF2Packer * lpOutPacker,IConnection * lpParentConn=NULL);

//AF_公共_获取交易市场信息--未开发
int FUNCTION_CALL_MODE F3610050(IAS2Context * lpContext,IF2UnPacker * lpInUnPacker,IF2Packer * lpOutPacker,IConnection * lpParentConn=NULL);

//AF_公共_获取杂项分类
int FUNCTION_CALL_MODE F3610004(IAS2Context * lpContext,IF2UnPacker * lpInUnPacker,IF2Packer * lpOutPacker,IConnection * lpParentConn=NULL);

//AF_基础数据_获取操作员信息
int FUNCTION_CALL_MODE F3610818(IAS2Context * lpContext,IF2UnPacker * lpInUnPacker,IF2Packer * lpOutPacker,IConnection * lpParentConn=NULL);

//AF_公共_获取最小价差信息--未开发
int FUNCTION_CALL_MODE F3610056(IAS2Context * lpContext,IF2UnPacker * lpInUnPacker,IF2Packer * lpOutPacker,IConnection * lpParentConn=NULL);

//AF_通用查询_获取通用查询过滤串
int FUNCTION_CALL_MODE F3610502(IAS2Context * lpContext,IF2UnPacker * lpInUnPacker,IF2Packer * lpOutPacker,IConnection * lpParentConn=NULL);

//AF_通用查询_获取通用查询SQL模板
int FUNCTION_CALL_MODE F3610501(IAS2Context * lpContext,IF2UnPacker * lpInUnPacker,IF2Packer * lpOutPacker,IConnection * lpParentConn=NULL);

//AF_基础数据_获取营业部信息
int FUNCTION_CALL_MODE F3610806(IAS2Context * lpContext,IF2UnPacker * lpInUnPacker,IF2Packer * lpOutPacker,IConnection * lpParentConn=NULL);

//AF_公共_获取证券的业务日期
int FUNCTION_CALL_MODE F3610022(IAS2Context * lpContext,IF2UnPacker * lpInUnPacker,IF2Packer * lpOutPacker,IConnection * lpParentConn=NULL);

//AF_公共_获取股东信息
int FUNCTION_CALL_MODE F3610065(IAS2Context * lpContext,IF2UnPacker * lpInUnPacker,IF2Packer * lpOutPacker,IConnection * lpParentConn=NULL);

//AF_公共_获取证券资料_通过证券内码
int FUNCTION_CALL_MODE F3610100(IAS2Context * lpContext,IF2UnPacker * lpInUnPacker,IF2Packer * lpOutPacker,IConnection * lpParentConn=NULL);

//AF_公共_获取证券资料_通过申报代码和市场
int FUNCTION_CALL_MODE F3610101(IAS2Context * lpContext,IF2UnPacker * lpInUnPacker,IF2Packer * lpOutPacker,IConnection * lpParentConn=NULL);

//AF_公共_获取证券类别--未开发
int FUNCTION_CALL_MODE F3610053(IAS2Context * lpContext,IF2UnPacker * lpInUnPacker,IF2Packer * lpOutPacker,IConnection * lpParentConn=NULL);

//AF_公共_获取子系统状态
int FUNCTION_CALL_MODE F3610005(IAS2Context * lpContext,IF2UnPacker * lpInUnPacker,IF2Packer * lpOutPacker,IConnection * lpParentConn=NULL);

//AF_公共_获取部门参数
int FUNCTION_CALL_MODE F3610012(IAS2Context * lpContext,IF2UnPacker * lpInUnPacker,IF2Packer * lpOutPacker,IConnection * lpParentConn=NULL);

//AF_公共_获取系统参数
int FUNCTION_CALL_MODE F3610010(IAS2Context * lpContext,IF2UnPacker * lpInUnPacker,IF2Packer * lpOutPacker,IConnection * lpParentConn=NULL);

//AF_公共_获取系统时区
int FUNCTION_CALL_MODE F3610001(IAS2Context * lpContext,IF2UnPacker * lpInUnPacker,IF2Packer * lpOutPacker,IConnection * lpParentConn=NULL);

//AF_公共_获取交易日_自然日--未开发
int FUNCTION_CALL_MODE F3610023(IAS2Context * lpContext,IF2UnPacker * lpInUnPacker,IF2Packer * lpOutPacker,IConnection * lpParentConn=NULL);

//AF_公共_获取市场初始化日期
int FUNCTION_CALL_MODE F3610020(IAS2Context * lpContext,IF2UnPacker * lpInUnPacker,IF2Packer * lpOutPacker,IConnection * lpParentConn=NULL);

//AF_公共_获取交易对手--未开发
int FUNCTION_CALL_MODE F3610070(IAS2Context * lpContext,IF2UnPacker * lpInUnPacker,IF2Packer * lpOutPacker,IConnection * lpParentConn=NULL);

//AF_公共_获取交易席位--未开发
int FUNCTION_CALL_MODE F3610066(IAS2Context * lpContext,IF2UnPacker * lpInUnPacker,IF2Packer * lpOutPacker,IConnection * lpParentConn=NULL);

//AF_基础数据_获取交易员信息
int FUNCTION_CALL_MODE F3610819(IAS2Context * lpContext,IF2UnPacker * lpInUnPacker,IF2Packer * lpOutPacker,IConnection * lpParentConn=NULL);

//AF_公共_判断是否交易日--未开发
int FUNCTION_CALL_MODE F3610021(IAS2Context * lpContext,IF2UnPacker * lpInUnPacker,IF2Packer * lpOutPacker,IConnection * lpParentConn=NULL);

//AF_通用查询_解析通用查询SQL
int FUNCTION_CALL_MODE F3610503(IAS2Context * lpContext,IF2UnPacker * lpInUnPacker,IF2Packer * lpOutPacker,IConnection * lpParentConn=NULL);

//AF_测试_打印包数据
int FUNCTION_CALL_MODE F3610999(IAS2Context * lpContext,IF2UnPacker * lpInUnPacker,IF2Packer * lpOutPacker,IConnection * lpParentConn=NULL);

//AF_公共_反转交易市场
int FUNCTION_CALL_MODE F3610006(IAS2Context * lpContext,IF2UnPacker * lpInUnPacker,IF2Packer * lpOutPacker,IConnection * lpParentConn=NULL);

//AF_公共_获取单元基本信息
int FUNCTION_CALL_MODE F3610044(IAS2Context * lpContext,IF2UnPacker * lpInUnPacker,IF2Packer * lpOutPacker,IConnection * lpParentConn=NULL);

//AF_公共_获取组合基本信息
int FUNCTION_CALL_MODE F3610045(IAS2Context * lpContext,IF2UnPacker * lpInUnPacker,IF2Packer * lpOutPacker,IConnection * lpParentConn=NULL);

//AF_公共_获取公司基本信息--未开发
int FUNCTION_CALL_MODE F3610040(IAS2Context * lpContext,IF2UnPacker * lpInUnPacker,IF2Packer * lpOutPacker,IConnection * lpParentConn=NULL);

//AF_公共_获取部门基本信息--未开发
int FUNCTION_CALL_MODE F3610041(IAS2Context * lpContext,IF2UnPacker * lpInUnPacker,IF2Packer * lpOutPacker,IConnection * lpParentConn=NULL);

//AF_公共_获取账户基本信息
int FUNCTION_CALL_MODE F3610043(IAS2Context * lpContext,IF2UnPacker * lpInUnPacker,IF2Packer * lpOutPacker,IConnection * lpParentConn=NULL);

#endif /* _S_AS_JC_SYSPUBFUNC_H */
