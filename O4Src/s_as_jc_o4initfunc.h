

#ifndef _S_AS_JC_O4INITFUNC_H
#define _S_AS_JC_O4INITFUNC_H

#include "s_as_jc_publicfunc.h" 
#include "s_as_jc_syspubfunc.h" 
#include "s_as_jc_wbpubfunc.h" 
#include "hshead.h" 
//AF_日初始化_全表更新
int FUNCTION_CALL_MODE F3615056(IAS2Context * lpContext,IF2UnPacker * lpInUnPacker,IF2Packer * lpOutPacker,IConnection * lpParentConn=NULL);

//AF_日初始化_委托方向转换
int FUNCTION_CALL_MODE F3615010(IAS2Context * lpContext,IF2UnPacker * lpInUnPacker,IF2Packer * lpOutPacker,IConnection * lpParentConn=NULL);

//AF_日初始化_委托方向权限格式转换
int FUNCTION_CALL_MODE F3615020(IAS2Context * lpContext,IF2UnPacker * lpInUnPacker,IF2Packer * lpOutPacker,IConnection * lpParentConn=NULL);

//AF_日初始化_账户状态转换
int FUNCTION_CALL_MODE F3615018(IAS2Context * lpContext,IF2UnPacker * lpInUnPacker,IF2Packer * lpOutPacker,IConnection * lpParentConn=NULL);

//AF_日初始化_交易市场转换
int FUNCTION_CALL_MODE F3615001(IAS2Context * lpContext,IF2UnPacker * lpInUnPacker,IF2Packer * lpOutPacker,IConnection * lpParentConn=NULL);

//AF_日初始化_期权标的类型转换
int FUNCTION_CALL_MODE F3615053(IAS2Context * lpContext,IF2UnPacker * lpInUnPacker,IF2Packer * lpOutPacker,IConnection * lpParentConn=NULL);

//AF_日初始化_投资透支转换
int FUNCTION_CALL_MODE F3615110(IAS2Context * lpContext,IF2UnPacker * lpInUnPacker,IF2Packer * lpOutPacker,IConnection * lpParentConn=NULL);

//AF_日初始化_允许交易的市场列表格式转换
int FUNCTION_CALL_MODE F3615019(IAS2Context * lpContext,IF2UnPacker * lpInUnPacker,IF2Packer * lpOutPacker,IConnection * lpParentConn=NULL);

//AF_日初始化_允许操作证券类别格式转换
int FUNCTION_CALL_MODE F3615011(IAS2Context * lpContext,IF2UnPacker * lpInUnPacker,IF2Packer * lpOutPacker,IConnection * lpParentConn=NULL);

//AF_日初始化_获取交易平台
int FUNCTION_CALL_MODE F3615002(IAS2Context * lpContext,IF2UnPacker * lpInUnPacker,IF2Packer * lpOutPacker,IConnection * lpParentConn=NULL);

//AF_日初始化_获取席位代码
int FUNCTION_CALL_MODE F3615009(IAS2Context * lpContext,IF2UnPacker * lpInUnPacker,IF2Packer * lpOutPacker,IConnection * lpParentConn=NULL);

//AF_日初始化_获取股东代码
int FUNCTION_CALL_MODE F3615008(IAS2Context * lpContext,IF2UnPacker * lpInUnPacker,IF2Packer * lpOutPacker,IConnection * lpParentConn=NULL);

//AF_日初始化_获取股东代码_期权保证金
int FUNCTION_CALL_MODE F3615050(IAS2Context * lpContext,IF2UnPacker * lpInUnPacker,IF2Packer * lpOutPacker,IConnection * lpParentConn=NULL);

//AF_日初始化_证券类别转换
int FUNCTION_CALL_MODE F3615003(IAS2Context * lpContext,IF2UnPacker * lpInUnPacker,IF2Packer * lpOutPacker,IConnection * lpParentConn=NULL);

//AF_日初始化_证券类别列表转换
int FUNCTION_CALL_MODE F3615111(IAS2Context * lpContext,IF2UnPacker * lpInUnPacker,IF2Packer * lpOutPacker,IConnection * lpParentConn=NULL);

//AF_日初始化_证券类别权限格式转换
int FUNCTION_CALL_MODE F3615007(IAS2Context * lpContext,IF2UnPacker * lpInUnPacker,IF2Packer * lpOutPacker,IConnection * lpParentConn=NULL);

//AF_日初始化_交易日类型转换
int FUNCTION_CALL_MODE F3615052(IAS2Context * lpContext,IF2UnPacker * lpInUnPacker,IF2Packer * lpOutPacker,IConnection * lpParentConn=NULL);

//AF_日初始化_交易平台序号转换
int FUNCTION_CALL_MODE F3615045(IAS2Context * lpContext,IF2UnPacker * lpInUnPacker,IF2Packer * lpOutPacker,IConnection * lpParentConn=NULL);

//AF_日初始化_生成BrokerID
int FUNCTION_CALL_MODE F3615054(IAS2Context * lpContext,IF2UnPacker * lpInUnPacker,IF2Packer * lpOutPacker,IConnection * lpParentConn=NULL);

//AF_日初始化_生成证券内码
int FUNCTION_CALL_MODE F3615005(IAS2Context * lpContext,IF2UnPacker * lpInUnPacker,IF2Packer * lpOutPacker,IConnection * lpParentConn=NULL);

//AF_日初始化_获取和生成证券内码
int FUNCTION_CALL_MODE F3615047(IAS2Context * lpContext,IF2UnPacker * lpInUnPacker,IF2Packer * lpOutPacker,IConnection * lpParentConn=NULL);

//AF_日初始化_获取资金类型
int FUNCTION_CALL_MODE F3615112(IAS2Context * lpContext,IF2UnPacker * lpInUnPacker,IF2Packer * lpOutPacker,IConnection * lpParentConn=NULL);

//AF_日初始化_根据券商编号获取券商ID
int FUNCTION_CALL_MODE F3615014(IAS2Context * lpContext,IF2UnPacker * lpInUnPacker,IF2Packer * lpOutPacker,IConnection * lpParentConn=NULL);

//AF_日初始化_根据营业部序号获取券商ID
int FUNCTION_CALL_MODE F3615017(IAS2Context * lpContext,IF2UnPacker * lpInUnPacker,IF2Packer * lpOutPacker,IConnection * lpParentConn=NULL);

//AF_日初始化_根据市场获取业务日期
int FUNCTION_CALL_MODE F3615048(IAS2Context * lpContext,IF2UnPacker * lpInUnPacker,IF2Packer * lpOutPacker,IConnection * lpParentConn=NULL);

//AF_日初始化_获取资金账户ID
int FUNCTION_CALL_MODE F3615016(IAS2Context * lpContext,IF2UnPacker * lpInUnPacker,IF2Packer * lpOutPacker,IConnection * lpParentConn=NULL);

//AF_日初始化_校验EI接口数据是否为空
int FUNCTION_CALL_MODE F3615141(IAS2Context * lpContext,IF2UnPacker * lpInUnPacker,IF2Packer * lpOutPacker,IConnection * lpParentConn=NULL);

//AF_日初始化_获取账户层次
int FUNCTION_CALL_MODE F3615012(IAS2Context * lpContext,IF2UnPacker * lpInUnPacker,IF2Packer * lpOutPacker,IConnection * lpParentConn=NULL);

//AF_日初始化_获取账户操作权限
int FUNCTION_CALL_MODE F3615013(IAS2Context * lpContext,IF2UnPacker * lpInUnPacker,IF2Packer * lpOutPacker,IConnection * lpParentConn=NULL);

//AF_日初始化_获取证券内码
int FUNCTION_CALL_MODE F3615004(IAS2Context * lpContext,IF2UnPacker * lpInUnPacker,IF2Packer * lpOutPacker,IConnection * lpParentConn=NULL);

//AF_日初始化_获取接口启用状态
int FUNCTION_CALL_MODE F3615057(IAS2Context * lpContext,IF2UnPacker * lpInUnPacker,IF2Packer * lpOutPacker,IConnection * lpParentConn=NULL);

//AF_基础_获取系统字典子项编号
int FUNCTION_CALL_MODE F3615051(IAS2Context * lpContext,IF2UnPacker * lpInUnPacker,IF2Packer * lpOutPacker,IConnection * lpParentConn=NULL);

//AF_日初始化_ETF证券类别调整
int FUNCTION_CALL_MODE F3615113(IAS2Context * lpContext,IF2UnPacker * lpInUnPacker,IF2Packer * lpOutPacker,IConnection * lpParentConn=NULL);

//AF_数据同步_禁买权限设置
int FUNCTION_CALL_MODE F3615151(IAS2Context * lpContext,IF2UnPacker * lpInUnPacker,IF2Packer * lpOutPacker,IConnection * lpParentConn=NULL);

//AF_数据同步_资金账户
int FUNCTION_CALL_MODE F3615034(IAS2Context * lpContext,IF2UnPacker * lpInUnPacker,IF2Packer * lpOutPacker,IConnection * lpParentConn=NULL);

//AF_数据同步_沪深费用明细
int FUNCTION_CALL_MODE F3615025(IAS2Context * lpContext,IF2UnPacker * lpInUnPacker,IF2Packer * lpOutPacker,IConnection * lpParentConn=NULL);

//AF_数据同步_期货费用明细
int FUNCTION_CALL_MODE F3615029(IAS2Context * lpContext,IF2UnPacker * lpInUnPacker,IF2Packer * lpOutPacker,IConnection * lpParentConn=NULL);

//AF_数据同步_期货保证金比例
int FUNCTION_CALL_MODE F3615038(IAS2Context * lpContext,IF2UnPacker * lpInUnPacker,IF2Packer * lpOutPacker,IConnection * lpParentConn=NULL);

//AF_数据同步_期货套利代码
int FUNCTION_CALL_MODE F3615065(IAS2Context * lpContext,IF2UnPacker * lpInUnPacker,IF2Packer * lpOutPacker,IConnection * lpParentConn=NULL);

//AF_数据同步_在途回购业务
int FUNCTION_CALL_MODE F3615132(IAS2Context * lpContext,IF2UnPacker * lpInUnPacker,IF2Packer * lpOutPacker,IConnection * lpParentConn=NULL);

//AF_数据同步_资金手工业务流水
int FUNCTION_CALL_MODE F3615134(IAS2Context * lpContext,IF2UnPacker * lpInUnPacker,IF2Packer * lpOutPacker,IConnection * lpParentConn=NULL);

//AF_数据同步_证券手工业务流水
int FUNCTION_CALL_MODE F3615136(IAS2Context * lpContext,IF2UnPacker * lpInUnPacker,IF2Packer * lpOutPacker,IConnection * lpParentConn=NULL);

//AF_数据同步_市场信息
int FUNCTION_CALL_MODE F3615036(IAS2Context * lpContext,IF2UnPacker * lpInUnPacker,IF2Packer * lpOutPacker,IConnection * lpParentConn=NULL);

//AF_数据同步_期权组合持仓
int FUNCTION_CALL_MODE F3615083(IAS2Context * lpContext,IF2UnPacker * lpInUnPacker,IF2Packer * lpOutPacker,IConnection * lpParentConn=NULL);

//AF_数据同步_深圳分级基金盲拆预估
int FUNCTION_CALL_MODE F3615093(IAS2Context * lpContext,IF2UnPacker * lpInUnPacker,IF2Packer * lpOutPacker,IConnection * lpParentConn=NULL);

//AF_数据同步_系统参数值
int FUNCTION_CALL_MODE F3615066(IAS2Context * lpContext,IF2UnPacker * lpInUnPacker,IF2Packer * lpOutPacker,IConnection * lpParentConn=NULL);

//AF_数据同步_操作员
int FUNCTION_CALL_MODE F3615102(IAS2Context * lpContext,IF2UnPacker * lpInUnPacker,IF2Packer * lpOutPacker,IConnection * lpParentConn=NULL);

//AF_数据同步_组合席位关系
int FUNCTION_CALL_MODE F3615104(IAS2Context * lpContext,IF2UnPacker * lpInUnPacker,IF2Packer * lpOutPacker,IConnection * lpParentConn=NULL);

//AF_数据同步_交易对手信息
int FUNCTION_CALL_MODE F3615069(IAS2Context * lpContext,IF2UnPacker * lpInUnPacker,IF2Packer * lpOutPacker,IConnection * lpParentConn=NULL);

#endif /* _S_AS_JC_O4INITFUNC_H */
