/*
* Headfile : hsmenu.h
* Author   : 经纪业务运营平台V20开发组
* Date     : 2012-09-04
* Notes    : 系统菜单常量定义
*            常量宏定义规则: CNST_*****_######
*                            *****：宏定义类型
*                            ######：宏定义详细说明
*
*/


#ifndef _HSMENU_H
#define _HSMENU_H


#define   MENU_USER_SYS                                      10                                                 //系统
#define   MENU_USER_SYSARG                                   1010                                               //系统参数
#define   MENU_USER_SYSARG_SYSSTATUS_SET                     101002                                             //系统状态设置
#define   MENU_USER_SYSARG_DIV01                             101003                                             //-
#define   MENU_USER_SYSARG_SYSDICT_SET                       101004                                             //数据字典设置
#define   MENU_USER_SYSARG_SYSCONFIG_SET                     101005                                             //配置参数设置
#define   MENU_USER_SYSARG_ERRMSG_SET                        101006                                             //错误信息设置
#define   MENU_USER_SYSARG_FUNCTION_SET                      101007                                             //系统功能设置
#define   MENU_USER_SYSARG_BUSINFLAG_SET                     101021                                             //业务标志设置
#define   MENU_USER_SYSARG_MENUHINT_SET                      101019                                             //菜单业务提示设置
#define   MENU_USER_SYSARG_QUERYINFO_SET                     101022                                             //通用查询信息设置
#define   MENU_USER_SYSARG_GENREPORT_SET                     101023                                             //通用报表信息设置
#define   MENU_USER_SYSARG_DIV02                             101010                                             //-
#define   MENU_USER_SYSARG_USERARG_SET                       101011                                             //用户参数设置
#define   MENU_USER_SYSARG_PASSWDRESTRICT_SET                101013                                             //密码限制设置
#define   MENU_USER_SYSARG_DIV03                             101014                                             //-
#define   MENU_USER_SYSARG_LICENSE_MAN                       101017                                             //许可证信息管理
#define   MENU_USER_SYSARG_BRANCH                            1011                                               //机构管理
#define   MENU_USER_SYSARG_BRANCH_SET                        101101                                             //机构信息管理
#define   MENU_USER                                          11                                                 //用户
#define   MENU_USER_RIGHT                                    1100                                               //权限管理
#define   MENU_USER_RIGHT_ROLERIGHTS                         110002                                             //角色授权
#define   MENU_USER_RIGHT_USER_RIGHT                         110004                                             //用户授权
#define   MENU_USER_RIGHT_SPEC_RIGHTS                        110005                                             //用户特殊授权
#define   MENU_USER_RIGHT_USERRIGTH_CP                       110006                                             //用户权限复制
#define   MENU_USER_RIGHT_DIV1                               110007                                             //-
#define   MENU_USER_RIGHT_ALLOWCLIENT                        110008                                             //可操作客户设置
#define   MENU_USER_RIGHT_CLIENTALLOWUSER                    110009                                             //客户可被操作用户设置
#define   MENU_USER_RIGHT_ALLOWSTATION                       110010                                             //可操作站点设置
#define   MENU_USER_RIGHT_ALLOWREPORT                        110016                                             //可操作通用报表设置
#define   MENU_USER_RIGHT_DIV2                               110012                                             //-
#define   MENU_USER_RIGHT_USERRIGHT_QRY                      110013                                             //用户权限查询
#define   MENU_USER_RIGHT_ONLINE                             110014                                             //在线用户查询
#define   MENU_USER_RIGHT_CLASS_QUERY                        110015                                             //权限分类查询
#define   MENU_USER_DIV80                                    1151                                               //-
#define   MENU_USER_OPER                                     1101                                               //操作员管理
#define   MENU_USER_OPER_ADD                                 110101                                             //操作员增加
#define   MENU_USER_OPER_MODI                                110102                                             //操作员修改
#define   MENU_USER_OPER_CANCEL                              110103                                             //操作员注销
#define   MENU_USER_OPER_UNCANCEL                            110104                                             //操作员注销取消
#define   MENU_USER_OPER_DIV1                                110105                                             //-
#define   MENU_USER_OPER_FROZEN                              110106                                             //冻结操作员
#define   MENU_USER_OPER_UNFFROZEN                           110107                                             //解冻操作员
#define   MENU_USER_OPER_DIV2                                110108                                             //-
#define   MENU_USER_OPER_CLEARPWD                            110109                                             //操作员清密
#define   MENU_USER_OPER_MODIPWD                             110110                                             //操作员密码修改
#define   MENU_USER_OPER_DIV3                                110111                                             //-
#define   MENU_USER_OPER_LEAVE                               110112                                             //操作员休假
#define   MENU_USER_OPER_UNLEAVE                             110113                                             //操作员收假
#define   MENU_USER_OPER_REDEPLOY                            110114                                             //操作员转移
#define   MENU_USER_OPER_DIV4                                110115                                             //-
#define   MENU_USER_OPER_LOG                                 110116                                             //操作员日志
#define   MENU_USER_OPER_QUERY                               110117                                             //操作员信息查询
#define   MENU_CUST                                          14                                                 //账户
#define   MENU_CUST_ARG                                      1400                                               //账户参数
#define   MENU_CUST_ARG_CLIENTMODEL                          140002                                             //客户模板设置
#define   MENU_FUND                                          20                                                 //资金
#define   MENU_FUND_ARG                                      2001                                               //资金参数
#define   MENU_FUND_ARG_BANK_BASE                            200101                                             //银行参数设置
#define   MENU_FUND_MANAGEMENT_DIV02                         2008                                               //-
#define   MENU_FUND_DEPOISTFECTH                             2003                                               //资金存取
#define   MENU_FUND_XJCQ                                     200301                                             //现金存取
#define   MENU_FUND_DEPOISTFECTH_DIV05                       200316                                             //-
#define   MENU_FUND_QZXJCQ                                   200317                                             //强制现金取
#define   MENU_QURY                                          42                                                 //查询
#define   MENU_QURY_KHCX                                     4200                                               //单客户查询
#define   MENU_QURY_GSCX                                     4201                                               //多客户查询
#define   MENU_QURY_DIV1                                     4203                                               //-
#define   MENU_QURY_OPERATOR_QUERY                           4204                                               //操作员查询
#define   MENU_QURY_DIV6                                     4256                                               //-
#define   MENU_QURY_GENERAL_QUERY                            4215                                               //通用查询
#define   MENU_SETT                                          51                                                 //日终
#define   MENU_SETT_BUSINFLOW                                5199                                               //日终流程查看
#define   MENU_SETT_BUSINFLOW_SET                            5196                                               //日终流程设置
#define   MENU_SETT_DIV01                                    5151                                               //-
#define   MENU_SETT_DATASYNC                                 5198                                               //清算数据准备
#define   MENU_SETT_DIV02                                    5152                                               //-
#define   MENU_SETT_FBACKUP                                  5194                                               //清算前备份
#define   MENU_SETT_BBACKUP                                  5195                                               //清算后备份
#define   MENU_SETT_DIV03                                    5153                                               //-
#define   MENU_SETT_FUND                                     5100                                               //资金日终
#define   MENU_SETT_FUND_INIT                                510001                                             //系统初始化
#define   MENU_SETT_FUND_CLOSE                               510002                                             //资金收市处理
#define   MENU_SETT_BK                                       5101                                               //存管日终
#define   MENU_SETT_BK_FILESET                               510101                                             //存管文件设置
#define   MENU_SETT_BK_OUTFILESET                            510108                                             //存管导出接口文件设置
#define   MENU_SETT_BK_DIV01                                 510151                                             //-
#define   MENU_SETT_BK_TRANSCHECK                            510102                                             //交易对账
#define   MENU_SETT_BK_TRANSCHECKAFTER                       510107                                             //交易对账后处理
#define   MENU_SETT_BK_DIV02                                 510152                                             //-
#define   MENU_SETT_BK_OUTREADY                              510103                                             //导出准备
#define   MENU_SETT_BK_DATAOUT                               510104                                             //数据导出
#define   MENU_SETT_BK_DIV03                                 510153                                             //-
#define   MENU_SETT_BK_SETTCHECK                             510105                                             //清算对账
#define   MENU_SETT_BK_DATATOHIS                             510106                                             //数据归上日
#define   MENU_SETT_ACCOUNT                                  5104                                               //账户日终
#define   MENU_SETT_ACCOUNT_FILES_SET                        510400                                             //账户日终文件设置
#define   MENU_SETT_ACCOUNT_EXTERNFUNC_SET                   510423                                             //账户外挂功能设置
#define   MENU_SETT_ACCOUNT_FLOW_SET                         510424                                             //账户日终流程设置
#define   MENU_SETT_ACCOUNT_FLOW_QRY                         510425                                             //账户日终处理向导
#define   MENU_SETT_ACCOUNT_DIV04                            510454                                             //-
#define   MENU_SETT_ACCOUNT_INIT                             510401                                             //账户系统初始化
#define   MENU_SETT_ACCOUNT_PREPARE                          510402                                             //账户日终准备
#define   MENU_SETT_ACCOUNT_DATA_IN                          510403                                             //待交收数据转入
#define   MENU_SETT_ACCOUNT_DEAL_PRE                         510404                                             //账户交收前处理
#define   MENU_SETT_ACCOUNT_DEAL                             510405                                             //账户交收处理
#define   MENU_SETT_ACCOUNT_HOLDEROPEN_CLEAR                 510414                                             //账户开户费清算
#define   MENU_SETT_ACCOUNT_DATA_TOTAL                       510406                                             //账户数据归历史
#define   MENU_SETT_ACCOUNT_DIV01                            510451                                             //-
#define   MENU_SETT_ACCOUNT_TRADEDATA_IN                     510407                                             //订单系统数据转入
#define   MENU_SETT_ACCOUNT_TRADEDATA_CONTRAST               510408                                             //订单系统数据核对
#define   MENU_SETT_ACCOUNT_CSDCDATA_IN                      510409                                             //中登数据转入
#define   MENU_SETT_ACCOUNT_CSDCDATA_OUT                     510410                                             //中登数据报送
#define   MENU_SETT_ACCOUNT_CSDCDATA_CONTRAST                510411                                             //中登数据核对
#define   MENU_SETT_ACCOUNT_FILES_OUT                        510421                                             //中登文件导出
#define   MENU_SETT_ACCOUNT_DIV02                            510452                                             //-
#define   MENU_SETT_ACCOUNT_ORTHERS_DATAIN                   510412                                             //其他数据导入
#define   MENU_SETT_ACCOUNT_OTHERS_DATAOUT                   510416                                             //其他数据导出
#define   MENU_SETT_ACCOUNT_XYHOLDEROPEN_OUT                 510413                                             //新意开户费导出
#define   MENU_SETT_ACCOUNT_VOUCHER_OUT                      510426                                             //财务开户凭证导出
#define   MENU_SETT_ACCOUNT_HOLDERJOUR_EXP                   510420                                             //代理登记业务流水导出
#define   MENU_SETT_ACCOUNT_DIV03                            510453                                             //-
#define   MENU_SETT_ACCOUNT_BANKPRESETT_DEAL                 510415                                             //银行预约开户日终处理
#define   MENU_SETT_ACCOUNT_FUNDACCT_MARK                    510422                                             //纯资金户日终处理
#define   MENU_SETT_DATA                                     5111                                               //经营管理日终
#define   MENU_SETT_DATA_CHECK                               511101                                             //冗余数据校验
#define   MENU_SETT_DATA_DIV01                               511151                                             //-
#define   MENU_SETT_DATA_TOTAL                               511103                                             //经营数据汇总
#define   MENU_SETT_DATA_TOHIS                               511102                                             //经营数据归历史
#define   MENU_SETT_SDC                                      5116                                               //登记日终
#define   MENU_SETT_SDC_EXCHFILES                            511601                                             //登记日终文件设置
#define   MENU_SETT_SDC_OUTFILESET                           511602                                             //登记文件导出设置
#define   MENU_SETT_SDC_DIV01                                511603                                             //-
#define   MENU_SETT_SDC_READY                                511604                                             //登记清算前处理
#define   MENU_SETT_SDC_BUSINENTER                           511605                                             //登记清算转入
#define   MENU_SETT_SDC_BUSINDEAL                            511606                                             //登记清算处理
#define   MENU_SETT_SDC_BUSINTOACCO                          511607                                             //登记清算入账
#define   MENU_SETT_SDC_SQUAREDEAL                           511608                                             //登记结算处理
#define   MENU_SETT_SDC_SQUARETOACCO                         511609                                             //登记结算入账
#define   MENU_SETT_SDC_BUSINAFTER                           511610                                             //登记清算后处理
#define   MENU_SETT_SDC_FILEOUT                              511611                                             //登记文件导出
#define   MENU_SETT_OTC                                      5117                                               //股权日终
#define   MENU_SETT_OTC_EXCHFILES                            511701                                             //股权日终文件设置
#define   MENU_SETT_OTC_SUPERCHECKSET                        511702                                             //股权结算对账设置
#define   MENU_SETT_OTC_DIV01                                511703                                             //-
#define   MENU_SETT_OTC_READY                                511704                                             //股权清算前处理
#define   MENU_SETT_OTC_BUSINENTER                           511705                                             //股权清算转入
#define   MENU_SETT_OTC_BUSINDEAL                            511706                                             //股权清算处理
#define   MENU_SETT_OTC_BUSINTOACCO                          511707                                             //股权清算入账
#define   MENU_SETT_OTC_SQUAREENTER                          511708                                             //股权结算转入
#define   MENU_SETT_OTC_SQUAREDEAL                           511709                                             //股权结算处理
#define   MENU_SETT_OTC_SQUARETOACCO                         511710                                             //股权结算入账
#define   MENU_SETT_OTC_BUSINAFTER                           511711                                             //股权清算后处理
#define   MENU_SETT_OTC_SUPERCHECK                           511712                                             //股权登记对账
#define   MENU_SETT_ASSISTANT                                5113                                               //辅助日终
#define   MENU_SETT_ASSISTANT_AUDIT                          511301                                             //日终工作复核
#define   MENU_SETT_ASSISTANT_DIV01                          511351                                             //-
#define   MENU_SETT_EXTERNFUNC                               5197                                               //外挂功能设置
#define   MENU_TRANS                                         60                                                 //转换机
#define   MENU_OTHERS_OTCTRAN                                3510                                               //股权报盘机
#define   MENU_OTHERS_OTCTRAN_SETARG                         351001                                             //报盘机参数设置
#define   MENU_OTHERS_OTCTRAN_CLEARJK                        351002                                             //当前接口库清除
#define   MENU_OTHERS_OTCTRAN_DIV02                          351003                                             //-
#define   MENU_OTHERS_OTCTRAN_TRANS                          351004                                             //股权申报回报
#define   MENU_SDC                                           22                                                 //登记
#define   MENU_SDC_SDCARG                                    2200                                               //登记参数
#define   MENU_SDC_SUBRULE                                   220001                                             //账户编码设置
#define   MENU_SDC_DIV01                                     220010                                             //-
#define   MENU_SDC_SDCBFARE1                                 220011                                             //一级费用设置
#define   MENU_SDC_AUTHORITY                                 220012                                             //权益方案设置
#define   MENU_SDC_SDCOCODE                                  220013                                             //股权代码登记
#define   MENU_SDC_STBXXOUTPT                                220014                                             //接口文件导出
#define   MENU_SDC_SDCACCT                                   2201                                               //登记账户
#define   MENU_SDC_SDCACCT_FIRM                              220100                                             //会员信息设置
#define   MENU_SDC_SDCACCT_SDCRESERV                         220101                                             //备付金信息设置
#define   MENU_SDC_SDCACCT_SDCOHOLDER                        220102                                             //股权登记账户管理
#define   MENU_SDC_SDCACCT_SDCOCOMPANY                       220103                                             //股份公司管理
#define   MENU_SDC_SDCASSET                                  2202                                               //登记存管
#define   MENU_SDC_SDCASSET_SDC                              220201                                             //确权登记
#define   MENU_SDC_SDCASSET_TRANSFER                         220202                                             //非交易过户
#define   MENU_SDC_SDCASSET_ROLLIN                           220203                                             //登记股权划转
#define   MENU_SDC_SDCASSET_FROZEN                           220204                                             //登记股权冻结
#define   MENU_SDC_SDCASSET_FROZENCANCEL                     220205                                             //登记股权解冻
#define   MENU_SDC_SDCASSET_ACCESS                           220206                                             //备付金转账
#define   MENU_SDC_SDCQRY                                    2203                                               //登记查询
#define   MENU_OTC                                           35                                                 //股权
#define   MENU_OTC_OTCARG                                    3500                                               //股权参数
#define   MENU_OTC_OTCEXCHARG_SET                            350001                                             //股权交易参数设置
#define   MENU_OTC_OTCARG_DIV01                              350010                                             //-
#define   MENU_OTC_OTCEXCHDATE_SET                           350011                                             //股权交易日期设置
#define   MENU_OTC_OTCEXCHTIME_SET                           350012                                             //股权交易时间期设置
#define   MENU_OTC_OTCARG_DIV02                              350020                                             //-
#define   MENU_OTC_OTCTYPE_SET                               350021                                             //股权类别设置
#define   MENU_OTC_OTCMODEL_SET                              350022                                             //股权模板设置
#define   MENU_OTC_OTCCODE_SET                               350023                                             //股权代码维护
#define   MENU_OTC_OTCARG_DIV03                              350030                                             //-
#define   MENU_OTC_OTCFARE_SET                               350031                                             //股权前台费用设置
#define   MENU_OTC_OTCFARE2_SET                              350032                                             //股权二级费用设置
#define   MENU_OTC_OTCARG_DIV04                              350040                                             //-
#define   MENU_OTC_OTCARG_OTCSEAT_SET                        350041                                             //股权席位参数设置
#define   MENU_OTC_OTCARG_OTCQUOTE_SET                       350042                                             //报价权限设置
#define   MENU_OTC_OTCARG_DIV05                              350050                                             //-
#define   MENU_OTC_OTCARG_OTCTIMECMD_SET                     350051                                             //股权交易指令设置
#define   MENU_OTC_OTCACCT                                   3501                                               //股权账户
#define   MENU_OTC_OTCACCT_OPEN                              350100                                             //股权账户开户
#define   MENU_OTC_OTCACCT_CANCEL                            350101                                             //股权账户销户
#define   MENU_OTC_OTCACCT_MODIFY                            350102                                             //股权账户修改
#define   MENU_OTC_OTCACCT_UNION_EASY_OPEN                   350103                                             //股权联合开户
#define   MENU_OTC_OTCACCT_UNIONCANCEL                       350104                                             //股权联合销户
#define   MENU_OTC_OTCACCT_UNIONMODI                         350105                                             //股权联合修改
#define   MENU_OTC_OTCACCT_APPFORM_REPRINT                   350106                                             //股权联合开户套打
#define   MENU_OTC_OTCACCT_ACCOUNTSYNC_ALL                   350107                                             //股权账户信息全同步
#define   MENU_OTC_OTCHOLD                                   3502                                               //股权持仓
#define   MENU_OTC_OTCHOLD_GQDJ                              350201                                             //股权冻结
#define   MENU_OTC_OTCHOLD_GQDJQX                            350202                                             //股权冻结取消
#define   MENU_OTC_OTCHOLD_GQJD                              350203                                             //股权解冻
#define   MENU_OTC_OTCHOLD_GQJDQX                            350204                                             //股权解冻取消
#define   MENU_OTC_OTCHOLD_GQHC                              350205                                             //股权红冲
#define   MENU_OTC_OTCHOLD_GQLB                              350206                                             //股权蓝补
#define   MENU_OTC_OTCTRADE                                  3503                                               //股权交易
#define   MENU_OTC_OTCTRADE_AGREEMENT_SIGN                   350300                                             //报价协议签署
#define   MENU_OTC_OTCTRADE_AGREEMENT_CANCEL                 350301                                             //报价协议取消
#define   MENU_OTC_OTCTRADE_DIV1                             350302                                             //-
#define   MENU_OTC_OTCTRADE_YXWT                             350303                                             //意向委托
#define   MENU_OTC_OTCTRADE_DJWT                             350304                                             //定价委托
#define   MENU_OTC_OTCTRADE_QRWT                             350305                                             //确认委托
#define   MENU_OTC_OTCTRADE_DIV2                             350306                                             //-
#define   MENU_OTC_OTCTRADE_MARKETMAKER_QUOTE                350307                                             //做市商报价
#define   MENU_OTC_OTCTRADE_INVESTOR_QUOTE                   350308                                             //投资者报价
#define   MENU_OTC_OTCTRADE_DIV3                             350309                                             //-
#define   MENU_OTC_OTCTRADE_QUOTE_MATCH                      350310                                             //点选成交
#define   MENU_OTC_OTCQRY                                    3504                                               //股权查询
#define   TEST_USER                                          70                                                 //用户管理
#define   TEST_USER_QUERY                                    7001                                               //用户管理



#endif /* _HSMENU_H */


