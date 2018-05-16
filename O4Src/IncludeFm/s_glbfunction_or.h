/*
 * Headfile: s_glbfunction_or.h
 * Author : 周伟明.
 * Date   : 2009/01/20.
 * Notes  : 提供系统公共函数
 * Modify : 版本       修改日期  申请人  修改人  修改单         修改说明
 *      V8.0.6.0   	   20100614          刘元召   内部            经纪业务运营平台V2.0项目2011基线建立
 * 			V8.0.5.3   20110303  王仁云  王仁云  20110301024	将加密和解密相关的放到license_security动态库中。增加密码加密和解密函数。
 *          V8.0.5.2   20110222  李玲斌  李玲斌  20101228018    为中信扩展口令获取与检验
 * 			V8.0.5.1   20110215  王仁云  王仁云  20110216030	为统一接入增加Blowfish加密和解密，并修改s_glbfunction_or.gcc文件，静态链接libsecurity.a。
 *          V8.0.5.0   20100414  周伟明  周伟明   内部            基线
 *          V8.0.4.1   20100121  陈  飞  周伟明  JJYWYYPT-5421  S_ETFCOMPONENT增加字段redeem_replace_balance和secu_market_code begin定义
 *          V8.0.4.0   20090926  周伟明  周伟明  内部           基线
 *          V8.0.3.0   20090626  周伟明  周伟明  内部           打包
 *          V8.0.2.0   20090420  周伟明  周伟明  内部           打包
 *          V8.0.1.0   20090120  周伟明  周伟明  内部           打包
 */

#ifndef _S_GLBFUNCTION_OR_H
#define _S_GLBFUNCTION_OR_H

#define DICT_BS_FLAG          1204     //买卖方向
#define DICT_ENTRUST_STATUS   1203     //交易属性
#define DICT_EXCHANGE_TYPE    1301     //交易类别
#define DICT_BUSINESS_TYPE    1205     //交易属性
#define DICT_BUSINESS_STATUS  1213     //成交状态
#define DICT_BUSINESS_KIND    1212     //成交类型
#define DICT_TRANS_STATUS     1103     //转帐状态
#define DICT_MONEY_TYPE       1101     //结算币种
#define DICT_BANK_TRANS_TYPE  1602     //银行交易类型
#define DICT_BANK_NO          1601     //银行代码


#define PMFLAG_ENTRUST_BS     0x1      //买卖方向
#define PMFLAG_ENTRUST_STATUS 0x2      //交易属性
#define PMFLAG_EXCHANGE_TYPE  0x4      //交易类别
#define PMFLAG_BUSINESS_TYPE  0x8      //交易属性
#define PMFLAG_REAL_STATUS    0x10     //成交状态
#define PMFLAG_REAL_TYPE      0x20     //成交类型
#define PMFLAG_BKTRANS_STATUS 0x40     //转帐状态
#define PMFLAG_MONEY_TYPE     0x80     //结算币种
#define PMFLAG_TRANS_TYPE     0x100    //银行交易类型
#define PMFLAG_STOCK_CODE     0x1000   //证券代码
#define PMFLAG_BUSINESS_FLAG  0x2000   //业务标志
#define PMFLAG_BANK_NO        0x4000   //银行代码
#define PMFLAG_BANKNO         0x10000  //银行代码转换
#define PMFLAG_ERROR_NO       0x20000  //银行代码转换


/* 成份股信息（应用于订单ETF成份股余额查询） */
typedef struct tagEtfComponent
{
	char      p_component_code[7];
	char      p_component_name[33];
	char      p_replace_flag;
	double    p_replace_ratio;
	double    p_replace_balance;
	double    p_component_amount;
	double    p_enable_amount;
	double    p_issue_amount;
	double    p_redeem_replace_balance;   //20100121 zhouwm 新增
	char      p_secu_market_code[9];      //20100121 zhouwm 新增
}S_ETFCOMPONENT,*LPETFCOMPONENT;


/*取内存表数据信息*/
extern int GetMdbData(IAS2Context * lpContext, IF2UnPacker * lpInUnPacker, IF2Packer * lpOutPacker,int * iErrorNo,char * sErrorInfo,char *sErrorPathInfo);

/*内存表数据同步*/
extern int SyncMdbData(IAS2Context * lpContext, IF2UnPacker * lpInUnPacker, IF2Packer * lpOutPacker,int * iErrorNo,char * sErrorInfo,char *sErrorPathInfo);

/*取错误信息*/
extern char * GetErrorInfo(IAS2Context * pContext,int p_iErrorNo,char * p_sErrorInfo);

/*取错误信息,将函数报错将原来的错误信息附加在后面*/
extern char * GetErrorInfox(IAS2Context * pContext,int p_iErrorNo,char * p_sErrorInfo);

/*取单字符杂项配置值*/
extern char GetSysConfig(IAS2Context * pContext,int p_iBranchNo,int p_iConfigNo,char p_char_config);

/*取随机数*/
extern int randomx(int iSeed);

/*加密*/
extern char* Encode(char *EncodePass, const char* Password, int Key);

/*银行密码解密*/
extern char* DecodeBkPwd(char *lPassword, const char *EncodePwd);

/*银行密码加密*/
extern char* EncodeBkPwd(char *EncodePass, const char *lPassword);

/*银行转帐错误代码转换*/
extern int getBankErr(const int lErrorNo);

///对源结果集中特定的字段进行名词解析，并重新打包输出结果集
/**
 *使用时需要在AS的内存数据库配置部分增加：
		<table name="dict_bs_flag"  logic_name="hsrun" type="1" note="1整表，0部分">
				<statement note="买卖方向">
					<select>subentry p_key,dict_prompt p_prompt</select>
					<from>hsdictionary</from>
					<where>dict_entry=1204</where>
				</statement>
		</table>
		<table name="dict_entrust_status"  logic_name="hsrun" type="1" note="1整表，0部分">
				<statement note="委托状态">
					<select>subentry p_key,dict_prompt p_prompt</select>
					<from>hsdictionary</from>
					<where>dict_entry=1203</where>
				</statement>
		</table>
		<table name="dict_exchange_type"  logic_name="hsrun" type="1" note="1整表，0部分">
				<statement note="交易类别">
					<select>subentry p_key,dict_prompt p_prompt</select>
					<from>hsdictionary</from>
					<where>dict_entry=1301</where>
				</statement>
		</table>
		<table name="dict_business_type"  logic_name="hsrun" type="1" note="1整表，0部分">
				<statement note="交易属性">
					<select>subentry p_key,dict_prompt p_prompt</select>
					<from>hsdictionary</from>
					<where>dict_entry=1205</where>
				</statement>
		</table>
		<table name="dict_business_status"  logic_name="hsrun" type="1" note="1整表，0部分">
				<statement note="成交状态">
					<select>subentry p_key,dict_prompt p_prompt</select>
					<from>hsdictionary</from>
					<where>dict_entry=1213</where>
				</statement>
		</table>
		<table name="dict_business_kind"  logic_name="hsrun" type="1" note="1整表，0部分">
				<statement note="成交类型">
					<select>subentry p_key,dict_prompt p_prompt</select>
					<from>hsdictionary</from>
					<where>dict_entry=1212</where>
				</statement>
		</table>
		<table name="dict_trans_status"  logic_name="hsrun" type="1" note="1整表，0部分">
				<statement note="转帐状态">
					<select>subentry p_key,dict_prompt p_prompt</select>
					<from>hsdictionary</from>
					<where>dict_entry=1103</where>
				</statement>
		</table>
		<table name="dict_money_type"  logic_name="hsrun" type="1" note="1整表，0部分">
				<statement note="结算币种">
					<select>subentry p_key,dict_prompt p_prompt</select>
					<from>hsdictionary</from>
					<where>dict_entry=1101</where>
				</statement>
		</table>
		<table name="dict_bank_trans_type"  logic_name="hsrun" type="1" note="1整表，0部分">
				<statement note="银行交易类型">
					<select>subentry p_key,dict_prompt p_prompt</select>
					<from>hsdictionary</from>
					<where>dict_entry=1602</where>
				</statement>
		</table>
		<table name="stkcode"  logic_name="hsrun" type="1" note="1整表，0部分">
				<statement note="股票名称">
					<select>exchange_type||stock_code p_key,stock_name p_prompt</select>
					<from>stkcode</from>
				</statement>
		</table>
		<table name="businflag"  logic_name="hsrun" type="1" note="1整表，0部分">
				<statement note="业务标志">
					<select>business_flag p_key,business_name p_prompt</select>
					<from>businflag</from>
				</statement>
		</table>
		<table name="dict_bank_name"  logic_name="hsrun" type="1" note="1整表，0部分">
				<statement note="银行名称">
					<select>strsubentry p_key,dict_prompt p_prompt</select>
					<from>stringdictionary</from>
					<where>dict_entry=1601</where>
				</statement>
		</table>
 *@param long Flag 用于指定哪些字段需要进行转换
  *0:买卖方向(entrust_bs);1:委托状态(entrust_status);2:交易类别(exchange_type);3:交易属性(business_type);
  *4:成交状态(real_status);5:成交类型(real_type);7:转帐状态(bktrans_status)8:结算币种(money_type);
  *8:银行交易类型(trans_type)
  *12:股票名称(exchange_type,stock_code);13:业务标志(business_flag):14:银行代码(bank_no)
 *@param IASContext * pContext 上下文，用于获取内存数据库的调用接口
 *@param IResultSet * lpResultSet 源结果集
 *@param IPacker *	lpOutPacker  输出打包器接口
 *@return 成功0，失败-1
 */
int getPrompt(unsigned long lFlag,IAS2Context * pContext,IF2ResultSet * lpInUnPacker,IF2Packer * lpOutPacker);

///使用内存数据库将输入的周边银行号转换为后台的银行号
/**
 *使用时需要在AS的内存数据库配置部分增加：
		<table name="outerconfig"  logic_name="hsrun" type="1" note="1整表，0部分">
				<statement note="配置文件">
					<select>*</select>
					<from>outerconfig</from>
				</statement>
		</table>
 *@param IASContext * pContext 上下文，用于获取内存数据库的调用接口
 *@param const char *lpOutBankNo 周边银行号
 *@param char *lpBankNo 输出后台的银行号
 *@param int iBufSize 输出后台银行号的最大长度
 *@return 成功0，失败-1
 */
int getBankNo(IAS2Context * pContext,int action_in, int lBranchNo, const char *lpOutBankNo, char *lpBankNo, int iBufSize);


///使用缓存表对周边的错误号进行转换
/**
 *@param IASContext * pContext 上下文，
 *@param const int lFunctionId 功能号
 *@param const int lErrorId 错误号
 *@return 转换后的错误号
 */
extern int getExternErrorXml(IAS2Context * pContext,const int lFunctionId,const int lErrorId);

///使用缓存表对银行的错误号进行转换
/**
 *@param IASContext * pContext 上下文，
 *@param const int lErrorId 错误号
 *@return 转换后的错误号
 */
extern int getBankErrorXml(IAS2Context * pContext,const int lErrorId);

//zhangly 20051213 增加 业务复核所用函数-------------------------------------
//调用复核规则检查函数
bool CheckAuditRule( char * rule1_field,char rule1_type,char * rule1_value,char rule1_op,char * check_value1,char rule1_logic,
                     char * rule2_field,char rule2_type,char * rule2_value,char rule2_op,char * check_value2,char rule2_logic,
                     char * rule3_field,char rule3_type,char * rule3_value,char rule3_op,char * check_value3 );
//取复核检查字段值
char * GetAuditCheckValue(char * sFieldName,IF2UnPacker * lpInUnPacker,IF2UnPacker * lpInUnPackerParent,char * amount_value,char * balance_value);

//查检以逗号分隔的角色串，是否在操作员角色集中
bool CheckOPRolesStr(char * src,char * RolesStr);

//zhangly 20051213 增加 业务复核所用函数 end-------------------------------------

/* 20060219 wangjz 增加银行密码处理，同注意有公用过程相关函数同步 */
char* hs_EncodeBkPwd(const char *bk_password, char *password_out);

char* hs_DecodeBkPwd(const char *bk_password, char *password_out);

//20060331 wangjz 增加
/*取字符串第 byPart 部分, byPart >= 1*/
void GetPart(const char *Buf, char cDelimiter, int byPart, char *pValue);

//20060701 wangjz add
/*取间隔时间，以秒为单位*/
int GetIntervalSec(int HsTimePre, int HsTimeNext);

//20070118 weiye add
/*期货代理客户解密*/
extern char* DecodeFuPwd(char *lPassword, const char *EncodePwd);

//20090912 wanglb,zhouwm 用于第三方授权操作解密及校验的函数 begin


/*==========================================================
 * Function   : Decrypt
 * Description: 解密Liscense
 * Input      : char *pDecLiscense 解密后的Liscense
 *              const char *pLiscense 传入的加密Liscense
 *              unsigned dwKey 密钥
 * Output     : 
 * Return     : char *pULiscense地址
 * Author     : wanglb,zhouwm
 * Date       : 2008/09/12
 ==========================================================*/
char *Decrypt(char *pDecLiscense,const char *pLiscense,unsigned dwKey);

/*==========================================================
 * Function   : CheckLiscense
 * Description: 对传入的Liscense有效性及是否过期进行校验
 * Input      : IASContext *lpContext 链接数据库使用
 *              const char *pLiscense 传入的加密Liscense
 *              unsigned dwKey 密钥
 *              char *pProductID 产品编号
 *              char *pOtherCompany 第三方厂商(目前没有使用,但是保留该接口,供以后可能使用)
 *              struct tm *tBeginTime 时间结构体，用于保存中间件AS启动时间
 *              char *pErrorMsg 用于保存产生的相关错误信息
 * Output     : 
 * Return     : 0 有效期内，正常使用
 *              -1 存在错误
 * Author     : wanglb,zhouwm
 * Date       : 2008/09/12
 ==========================================================*/
extern int CheckLiscense(IAS2Context *lpContext,const char *pLiscense,char *pProductID,char *pOtherCompany,int iTimeMin,char *pErrorMsg);

/*==========================================================
 * Function   : GetCompanyName
 * Description: 用于取sysarg中的证券公司名称
 * Input      : IASContext *pContext 链接数据库使用
 *              char *pStkCompany 证券公司名称
 * Output     : 
 * Return     : true 成功
 *              false 失败
 * Author     : wanglb,zhouwm
 * Date       : 2008/09/12
 ==========================================================*/
/*把从数据库获取改成从内存数据库获取*/
bool GetCompanyName(IAS2Context * pContext,char *pStkCompany);

//20090912 wanglb,zhouwm 用于第三方授权操作解密及校验的函数 end.

/*==========================================================
 * Function   : GetSecuAssetPrice
 * Description: 取证券市值价
 * Input      : IUnPacker  lpContext	上下文
 *              char * szSecuExchType   交易类别
 *              char * szStockCode      证券代码
 *              char * szStockType      证券类别
 *              int iStoreUnit          存放单位
 *              char cAssetFlag         计算市值标志
 * Output     : Asset_Price             市值价
 * Return     : >=0		    成功
 *				<0          失败 		
 * Author     : zhouwm
 * Date       : 2008/12/03.
 ==========================================================*/
extern double GetSecuAssetPrice(IAS2Context *lpContext,char * szSecuExchType,char * szStockCode,char * szStockType,int iStoreUnit,char cAssetFlag);


/*==========================================================
 * Function   : GetSecuLastPrice
 * Description: 取证券最新价
 * Input      : IUnPacker  lpContext	上下文
 *              char * szSecuExchType   交易类别
 *              char * szStockCode      证券代码
 *              char * szStockType      证券类别
 * Output     : Last_Price             最新价
 * Return     : >=0		    成功
 *				<0          失败 		
 * Author     : zhouwm
 * Date       : 2008/12/03.
 ==========================================================*/
extern double GetSecuLastPrice(IAS2Context *lpContext,char * szSecuExchType,char * szStockCode,char * szStockType);


/*==========================================================
 * Function   : GetDebtInterest
 * Description: 取国债利息
 * Input      : IUnPacker  lpContext	上下文
 *              char * szSecuExchType   交易类别
 *              char * szStockCode      证券代码
 *              char * szStockType      证券类别(允许为空)
 * Output     : Last_Price             最新价
 * Return     : >=0		    成功
 *				<0          失败 		
 * Author     : zhouwm
 * Date       : 2008/12/03.
 ==========================================================*/
extern double GetSecuDebtInterest(IAS2Context *lpContext,char * szSecuExchType,char * szStockCode,char * szStockType);

/*==========================================================
 * Function   : GetSecuCode
 * Description: 取证券代码
 * Input      : IAS2Context*  lpContext        上下文
 *              IF2UnPacker * lpInUnPacker     请求包
 *              IF2Packer *   lpOutPacker      应答包
 * Output     : 
 * Return     : >=0		    成功
 *				<0          失败 		
 * Author     : zhouwm
 * Date       : 2009/05/12.
 ==========================================================*/
extern int GetSecuCode(IAS2Context* lpContext,IF2UnPacker * lpInUnPacker,IF2Packer * lpOutPacker);

/*==========================================================
 * Function   : GetSecuCodePrice
 * Description: 取证券代码信息＋最新价＋市值价
 * Input      : IAS2Context*  lpContext        上下文
 *              IF2UnPacker * lpInUnPacker     请求包
 *              IF2Packer *   lpOutPacker      应答包
 * Output     : 
 * Return     : >=0		    成功
 *				<0          失败 		
 * Author     : zhouwm
 * Date       : 2009/05/12.
 ==========================================================*/
extern int GetSecuCodePrice(IAS2Context* lpContext,IF2UnPacker * lpInUnPacker,IF2Packer * lpOutPacker);

///begin 20110729 刘元召 add, 增加一个输出函数GetCaeCodePrice，相比GetSecuCodePrice多增加五档行情价格信息的返回
/*==========================================================
 * Function   : GetCaeCodePrice
 * Description: 取证券代码信息＋最新价＋市值价+五档行情信息
 * Input      : IAS2Context*  lpContext        上下文
 *              IF2UnPacker * lpInUnPacker     请求包
 *              IF2Packer *   lpOutPacker      应答包
 * Output     : 
 * Return     : >=0		    成功
 *				<0          失败 		
 * Author     : zhouwm
 * Date       : 2009/05/12.
 ==========================================================*/
extern int GetCaeCodePrice(IAS2Context* lpContext,IF2UnPacker * lpInUnPacker,IF2Packer * lpOutPacker);
///end 20110729 刘元召 add, 增加一个输出函数GetCaeCodePrice，相比GetSecuCodePrice多增加五档行情价格信息的返回

/*==========================================================
 * Function   : GetUserToken
 * Description: 用户令牌获取
 * Input      : IUnPacker  lpContext	    上下文
 *              cosnt int iInitDate         系统初始化日期
 *              const char cCertType        身份类别
 *              const char * sCertAccount   身份帐号
 *              const char cPasswordType    密码类别
 *              const char * sPassword      密码
 *              const char   cPasswordCheck 密码校验
 * Output     : char *sUserToken            令牌
 * Return     : >=0		    成功
 *				<0          失败 		
 * Author     : zhouwm,lilb
 * Date       : 2008/12/03.
 ==========================================================*/
extern int GetUserToken(IAS2Context *lpContext,char *sUserToken,const int iInitDate, const char cCertType,const char * sCertAccount,const char cPasswordType,const char * sPassword,const char cPasswordCheck);

/*==========================================================
 * Function   : CheckUserToken
 * Description: 用户令牌校验
 * Input      : IUnPacker  lpContext	    上下文
 *              char *sUserToken            令牌
 *              cosnt int iInitDate         系统初始化日期
 *              const char cCertType        身份类别
 *              const char * sCertAccount   身份帐号
 *              const char cPasswordType    密码类别
 *              const char * sPassword      密码
 * Output     : 
 * Return     : >=0		    成功
 *				<0          失败 		
 * Author     : zhouwm
 * Date       : 2008/12/03.
 ==========================================================*/
extern int CheckUserToken(IAS2Context *lpContext,char *sUserToken,const int iInitDate, const char cCertType,const char * sCertAccount,const char cPasswordType,const char * sPassword);

/*==========================================================
 * Function   : GetFileBuffer
 * Description: 取配置对象信息
 * Input      : IAS2Context  lpContext      上下文
 *              void * lpBuf                缓冲区地址
 *              int iBufSize                缓冲区大小
 *              char *sLocation             配置对象位置
 *              IRCfgObj *pCfgObj           配置文件对象
 * Output     : 
 * Return     : >=0         成功
 *              <0          失败        
 * Author     : zhouwm
 * Date       : 2009/01/17.
 ==========================================================*/
extern int GetFileBuffer(IAS2Context *lpContext,IRCfgObj *pCfgObj,char * sBuf,char *sLocation);

/*==========================================================
 * Function   : SaveFileBuffer
 * Description: 保存配置对象信息
 * Input      : IAS2Context  lpContext      上下文
 *              void * lpBuf                缓冲区地址
 *              long * iBufSize             缓冲区大小
 *              IWCfgObj *pWCfgObj          配置文件对象
 * Output     : 
 * Return     : >=0         成功
 *              <0          失败        
 * Author     : zhouwm
 * Date       : 2009/01/17.
 ==========================================================*/
extern int SaveFileBuffer(IAS2Context *lpContext,IWCfgObj *pWCfgObj,char* sBuf);

/*==========================================================
 * Function   : GetNewWCfgObj
 * Description: 获取可写配置对象
 * Input      : IAS2Context  lpContext     上下文
 *              IWCfgObj *pCfgObj           可写配置对象
 *              char *sLocation             配置对象位置
 * Output     : 
 * Return     : >=0     成功
 * <0          失败  
 * Author     : zhouwm
 * Date       : 2009/01/17.
 ==========================================================*/
extern int GetNewWCfgObj(IAS2Context *lpContext,IWCfgObj *pCfgObj,char *sLocation);

/*==========================================================
 * Function   : CheckAccessLicense
 * Description: 接入许可校验
 * Input      : IAS2Context  lpContext          上下文
 * Output     : 
 * Return     : =0                       成功
 *                                 >0          失败 
 * Author     : lilb
 * Date       : 2009/02/13
 ==========================================================*/
extern int CheckAccessLicense(IAS2Context *lpContext);

/*==========================================================
 * Function   : EncodeTwoWord
 * Description: 二字加密算法
 * Input      :  char *pIn  需要加密的源
 * Output     :  char *pOut 加密结果
 * Return     : =0          成功
 *              <>0         失败 
 * Author     : wangry
 * Date       : 2009/04/16
 ==========================================================*/
extern int EncodeTwoWord(char *pIn, char *pOut);

/*==========================================================
 * Function   : DecodeTwoWord
 * Description: 二字解密算法
 * Input      :  char *pIn  被加密的源
 * Output     :  char *pOut 解密结果
 * Return     : =0          成功
 *              <>0         失败 
 * Author     : wangry
 * Date       : 2009/04/16
 ==========================================================*/
extern int DecodeTwoWord(char *pIn, char *pOut);

/*==========================================================
 * Function   : EtfToStruct
 * Description: ETF成分股信息保存到结构数组中
 * Input      :  IAS2Context * lpContext        上下文
 *            :  S_ETFCOMPONENT **pEtfComponent 成份股结构数组
 *            :  const char     *sMdbTable      内存表名
 *            :  const char     *sWhere         查询条件
 * Return     : =0          成功
 *              <>0         失败 
 * Author     : zhouwm
 * Date       : 2009/05/06
 ==========================================================*/
extern int EtfToStruct(IAS2Context * lpContext,S_ETFCOMPONENT *pEtfComponent,char *sMdbTable,char *sWhere,int * iErrorNo,char * sErrorInfo,char *sErrorPathInfo);

/*==========================================================
 * Function   : EtfResultUnion
 * Description: 根据数组的成分代码修改ETF成分股信息结构数组中对应的成分代码数量数据
 * Input      :  S_ETFCOMPONENT **pEtfComponent        成份股结构数组
 *            :  const int      iArrayLen              结构长度
 *            :  const int      iListLen               数组长度
 *            :  char           sComponentCode[][7]    成份股代码
 *            :  double         dEnableAmount[]        可用数量
 *            :  double         dIssueAmount[]         可申购赎回数量
 * Return     :  =0          成功
 *               <>0         失败 
 * Author     : zhouwm
 * Date       : 2009/05/06
 ==========================================================*/
extern int EtfResultUnion(S_ETFCOMPONENT *pEtfComponent,const int iArrayLen,const int iListLen,char sComponentCode[][7],double dEnableAmount[],double dIssueAmount[]);

/*==========================================================
 * Function   : ResultSearch
 * Description: ETF成分股信息代码查找
 * Input      :  S_ETFCOMPONENT **pEtfComponent     成份股结构
 *            :  const int      *sComponentCode     数组长度
 *            :  const char     *sComponentCode     成分股票代码
 * Return     :  >=0            成功
 *               <0             失败 
 * Author     : zhouwm
 * Date       : 2009/05/06
 ==========================================================*/
extern int ResultSearch(S_ETFCOMPONENT *pEtfComponent,const int iArrayLen,const char *sComponentCode);

/*==========================================================
 * Function   : DecryptHsLicense
 * Description: 解密Liscense
 * Input      : char *pDecLiscense 解密后的Liscense
 *              const char *pLiscense 传入的加密Liscense
 *              unsigned short dwKey  密钥
 * Output     :
 * Return     : pDecLiscense
 * Author     : chengjh
 * Date       : 2009/04/24
 ==========================================================*/
extern char *DecryptHsLicense(char *pDecLiscense,const char *pLiscense,int usKey);
/*==========================================================
 * Function   : EncryptHsLicense
 * Description: 加密Liscense
 * Input      : char *pEncLiscense 加密后的Liscense
 *              const char *pLiscense 传入的加密Liscense
 *              unsigned short dwKey  密钥
 * Output     : char *pEncLiscense 加密后的Liscense
 * Return     : pEncLiscense
 * Author     : yangsb
 * Date       : 2009/05/23
 ==========================================================*/
extern char * EncryptHsLicense(char *pEncLiscense,const char *pLiscense,unsigned short usKey);

/*==========================================================
 * Function   : ProfessionCode2Hs6
 * Description: 用于把08职业代码转换为06版
 * Input      : char *sz_src 源字符串
 *              char *sz_dest 转换后的06版职业代码
 * Output     : char *sz_dest 转换后的06版职业代码
 * Return     : char *
 * Author     : yangsb
 * Date       : 2009/06/01
 ==========================================================*/
extern char * ProfessionCode2Hs6(const char *sz_src,char *sz_dest);

/*==========================================================
 * Function   : Nationality2Hs6
 * Description: 用于把08国籍地区代码转换为06版
 * Input      : char *sz_src 源字符串
 * Output     : char 转换后的06版国籍地区代码
 * Return     : char 
 * Author     : yangsb
 * Date       : 2009/06/01
 ==========================================================*/
extern char Nationality2Hs6(const char *sz_src);

/*==========================================================
 * Function   : CheckSystemLicense
 * Description: 系统许可校验
 * Input      : IAS2Context  lpContext         上下文
 *              int & nBranchCnt               营业部数量 
 *              int & nClientCnt               客户数量
 *              int & nValidDate               有效日期
 * Output     : 
 * Return     : =0                             成功
 *                                 >0          失败 
 * Author     : lilb
 * Date       : 2009/02/13
 ==========================================================*/
extern int CheckSystemLicense(IAS2Context *lpContext,int & nBranchCnt, int & nClientCnt, int & nValidDate);

#ifndef WIN32
#define __stdcall
#endif

#ifdef __cplusplus
extern "C"
{
#endif
	// Blowfish算法，这里密钥约定是16字节。输入输出缓存可以是同一个
	void __stdcall BlowfishEncode(void *lpOut, const void *lpIn, int nLength, const void *lpKey);
	void __stdcall BlowfishDecode(void *lpOut, const void *lpIn, int nLength, const void *lpKey);
	char* lib_Encode(char *EncodePass, const char* Password, int Key);
	char* lib_DecodeBkPwd(char *lPassword, const char *EncodePwd);
	char* lib_EncodeBkPwd(char *EncodePass, const char *lPassword);
	char* lib_hs_EncodeBkPwd(const char *bk_password, char *password_out);
	char* lib_hs_DecodeBkPwd(const char *bk_password, char *password_out);
	char* lib_DecodeFuPwd(char *lPassword, const char *EncodePwd);
	char *lib_Decrypt(char *pDecLiscense,const char *pLiscense,unsigned dwKey);
	int lib_CheckLiscense(IAS2Context *lpContext,const char *pLiscense,char *pProductID,char *pOtherCompany,int iTimeMin,char *pErrorMsg);
	int lib_EncodeTwoWord(char *pIn, char *pOut);
	int lib_DecodeTwoWord(char *pIn, char *pOut);
	char *lib_DecryptHsLicense(char *pDecLiscense,const char *pLiscense,int usKey);
	char * lib_EncryptHsLicense(char *pEncLiscense,const char *pLiscense,unsigned short usKey);
	int lib_GetMdbData(IAS2Context * lpContext, IF2UnPacker * lpInUnPacker, IF2Packer * lpOutPacker,int * iErrorNo,char * sErrorInfo,char *sErrorPathInfo);
	bool lib_GetCompanyName(IAS2Context * lpContext,char *pStkCompany);
	int lib_HsPwdEncode(const char *pIn, char *pOut);
	int lib_HsPwdDecode(const char *pIn, char *pOut);
#ifdef __cplusplus
}
#endif

/*==========================================================
 * Function   : BFEncode
 * Description: Blowfish加密
 * Input      : const void *lpIn         		输入的明文
 *              int nLength               		明文长度 
 *              const void *lpKey               加密密钥
 * Output     : lpOut 							输出的密文
 * Return     : void
 * Author     : wangry
 * Date       : 2011/02/15
 ==========================================================*/
extern void BFEncode(void *lpOut, const void *lpIn, int nLength, const void *lpKey);

/*==========================================================
 * Function   : BFDecode
 * Description: Blowfish解密
 * Input      : const void *lpIn         		输入的密文
 *              int nLength               		密文长度 
 *              const void *lpKey               加密密钥
 * Output     : lpOut 							输出的明文
 * Return     : void
 * Author     : wangry
 * Date       : 2011/02/15
 ==========================================================*/
extern void BFDecode(void *lpOut, const void *lpIn, int nLength, const void *lpKey);


/*==========================================================
* Function   : HsPwdEncode
* Description: 加密密码
* Input      : const char *pIn 输入的密码串
*              char *pOut 输出的加密后的密码。
* Return     : 0: 成功，其他失败。
* Author     : wangry
* Date       : 2010/03/03
==========================================================*/
extern int HsPwdEncode(const char *pIn, char *pOut);

/*==========================================================
* Function   : HsPwdDecode
* Description: 密码解密
* Input      : const char *pIn 输入的加密的密码串
*              char *pOut 输出的解密后的密码。
* Return     : 0: 成功，其他失败。
* Author     : wangry
* Date       : 2010/03/03
==========================================================*/
extern int HsPwdDecode(const char *pIn, char *pOut);

#endif /* _S_GLBFUNCTION_OR_H */

