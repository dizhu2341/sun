/*
 * Headfile: s_glbfunction_or.h
 * Author : ��ΰ��.
 * Date   : 2009/01/20.
 * Notes  : �ṩϵͳ��������
 * Modify : �汾       �޸�����  ������  �޸���  �޸ĵ�         �޸�˵��
 *      V8.0.6.0   	   20100614          ��Ԫ��   �ڲ�            ����ҵ����Ӫƽ̨V2.0��Ŀ2011���߽���
 * 			V8.0.5.3   20110303  ������  ������  20110301024	�����ܺͽ�����صķŵ�license_security��̬���С�����������ܺͽ��ܺ�����
 *          V8.0.5.2   20110222  �����  �����  20101228018    Ϊ������չ�����ȡ�����
 * 			V8.0.5.1   20110215  ������  ������  20110216030	Ϊͳһ��������Blowfish���ܺͽ��ܣ����޸�s_glbfunction_or.gcc�ļ�����̬����libsecurity.a��
 *          V8.0.5.0   20100414  ��ΰ��  ��ΰ��   �ڲ�            ����
 *          V8.0.4.1   20100121  ��  ��  ��ΰ��  JJYWYYPT-5421  S_ETFCOMPONENT�����ֶ�redeem_replace_balance��secu_market_code begin����
 *          V8.0.4.0   20090926  ��ΰ��  ��ΰ��  �ڲ�           ����
 *          V8.0.3.0   20090626  ��ΰ��  ��ΰ��  �ڲ�           ���
 *          V8.0.2.0   20090420  ��ΰ��  ��ΰ��  �ڲ�           ���
 *          V8.0.1.0   20090120  ��ΰ��  ��ΰ��  �ڲ�           ���
 */

#ifndef _S_GLBFUNCTION_OR_H
#define _S_GLBFUNCTION_OR_H

#define DICT_BS_FLAG          1204     //��������
#define DICT_ENTRUST_STATUS   1203     //��������
#define DICT_EXCHANGE_TYPE    1301     //�������
#define DICT_BUSINESS_TYPE    1205     //��������
#define DICT_BUSINESS_STATUS  1213     //�ɽ�״̬
#define DICT_BUSINESS_KIND    1212     //�ɽ�����
#define DICT_TRANS_STATUS     1103     //ת��״̬
#define DICT_MONEY_TYPE       1101     //�������
#define DICT_BANK_TRANS_TYPE  1602     //���н�������
#define DICT_BANK_NO          1601     //���д���


#define PMFLAG_ENTRUST_BS     0x1      //��������
#define PMFLAG_ENTRUST_STATUS 0x2      //��������
#define PMFLAG_EXCHANGE_TYPE  0x4      //�������
#define PMFLAG_BUSINESS_TYPE  0x8      //��������
#define PMFLAG_REAL_STATUS    0x10     //�ɽ�״̬
#define PMFLAG_REAL_TYPE      0x20     //�ɽ�����
#define PMFLAG_BKTRANS_STATUS 0x40     //ת��״̬
#define PMFLAG_MONEY_TYPE     0x80     //�������
#define PMFLAG_TRANS_TYPE     0x100    //���н�������
#define PMFLAG_STOCK_CODE     0x1000   //֤ȯ����
#define PMFLAG_BUSINESS_FLAG  0x2000   //ҵ���־
#define PMFLAG_BANK_NO        0x4000   //���д���
#define PMFLAG_BANKNO         0x10000  //���д���ת��
#define PMFLAG_ERROR_NO       0x20000  //���д���ת��


/* �ɷݹ���Ϣ��Ӧ���ڶ���ETF�ɷݹ�����ѯ�� */
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
	double    p_redeem_replace_balance;   //20100121 zhouwm ����
	char      p_secu_market_code[9];      //20100121 zhouwm ����
}S_ETFCOMPONENT,*LPETFCOMPONENT;


/*ȡ�ڴ��������Ϣ*/
extern int GetMdbData(IAS2Context * lpContext, IF2UnPacker * lpInUnPacker, IF2Packer * lpOutPacker,int * iErrorNo,char * sErrorInfo,char *sErrorPathInfo);

/*�ڴ������ͬ��*/
extern int SyncMdbData(IAS2Context * lpContext, IF2UnPacker * lpInUnPacker, IF2Packer * lpOutPacker,int * iErrorNo,char * sErrorInfo,char *sErrorPathInfo);

/*ȡ������Ϣ*/
extern char * GetErrorInfo(IAS2Context * pContext,int p_iErrorNo,char * p_sErrorInfo);

/*ȡ������Ϣ,����������ԭ���Ĵ�����Ϣ�����ں���*/
extern char * GetErrorInfox(IAS2Context * pContext,int p_iErrorNo,char * p_sErrorInfo);

/*ȡ���ַ���������ֵ*/
extern char GetSysConfig(IAS2Context * pContext,int p_iBranchNo,int p_iConfigNo,char p_char_config);

/*ȡ�����*/
extern int randomx(int iSeed);

/*����*/
extern char* Encode(char *EncodePass, const char* Password, int Key);

/*�����������*/
extern char* DecodeBkPwd(char *lPassword, const char *EncodePwd);

/*�����������*/
extern char* EncodeBkPwd(char *EncodePass, const char *lPassword);

/*����ת�ʴ������ת��*/
extern int getBankErr(const int lErrorNo);

///��Դ��������ض����ֶν������ʽ����������´����������
/**
 *ʹ��ʱ��Ҫ��AS���ڴ����ݿ����ò������ӣ�
		<table name="dict_bs_flag"  logic_name="hsrun" type="1" note="1����0����">
				<statement note="��������">
					<select>subentry p_key,dict_prompt p_prompt</select>
					<from>hsdictionary</from>
					<where>dict_entry=1204</where>
				</statement>
		</table>
		<table name="dict_entrust_status"  logic_name="hsrun" type="1" note="1����0����">
				<statement note="ί��״̬">
					<select>subentry p_key,dict_prompt p_prompt</select>
					<from>hsdictionary</from>
					<where>dict_entry=1203</where>
				</statement>
		</table>
		<table name="dict_exchange_type"  logic_name="hsrun" type="1" note="1����0����">
				<statement note="�������">
					<select>subentry p_key,dict_prompt p_prompt</select>
					<from>hsdictionary</from>
					<where>dict_entry=1301</where>
				</statement>
		</table>
		<table name="dict_business_type"  logic_name="hsrun" type="1" note="1����0����">
				<statement note="��������">
					<select>subentry p_key,dict_prompt p_prompt</select>
					<from>hsdictionary</from>
					<where>dict_entry=1205</where>
				</statement>
		</table>
		<table name="dict_business_status"  logic_name="hsrun" type="1" note="1����0����">
				<statement note="�ɽ�״̬">
					<select>subentry p_key,dict_prompt p_prompt</select>
					<from>hsdictionary</from>
					<where>dict_entry=1213</where>
				</statement>
		</table>
		<table name="dict_business_kind"  logic_name="hsrun" type="1" note="1����0����">
				<statement note="�ɽ�����">
					<select>subentry p_key,dict_prompt p_prompt</select>
					<from>hsdictionary</from>
					<where>dict_entry=1212</where>
				</statement>
		</table>
		<table name="dict_trans_status"  logic_name="hsrun" type="1" note="1����0����">
				<statement note="ת��״̬">
					<select>subentry p_key,dict_prompt p_prompt</select>
					<from>hsdictionary</from>
					<where>dict_entry=1103</where>
				</statement>
		</table>
		<table name="dict_money_type"  logic_name="hsrun" type="1" note="1����0����">
				<statement note="�������">
					<select>subentry p_key,dict_prompt p_prompt</select>
					<from>hsdictionary</from>
					<where>dict_entry=1101</where>
				</statement>
		</table>
		<table name="dict_bank_trans_type"  logic_name="hsrun" type="1" note="1����0����">
				<statement note="���н�������">
					<select>subentry p_key,dict_prompt p_prompt</select>
					<from>hsdictionary</from>
					<where>dict_entry=1602</where>
				</statement>
		</table>
		<table name="stkcode"  logic_name="hsrun" type="1" note="1����0����">
				<statement note="��Ʊ����">
					<select>exchange_type||stock_code p_key,stock_name p_prompt</select>
					<from>stkcode</from>
				</statement>
		</table>
		<table name="businflag"  logic_name="hsrun" type="1" note="1����0����">
				<statement note="ҵ���־">
					<select>business_flag p_key,business_name p_prompt</select>
					<from>businflag</from>
				</statement>
		</table>
		<table name="dict_bank_name"  logic_name="hsrun" type="1" note="1����0����">
				<statement note="��������">
					<select>strsubentry p_key,dict_prompt p_prompt</select>
					<from>stringdictionary</from>
					<where>dict_entry=1601</where>
				</statement>
		</table>
 *@param long Flag ����ָ����Щ�ֶ���Ҫ����ת��
  *0:��������(entrust_bs);1:ί��״̬(entrust_status);2:�������(exchange_type);3:��������(business_type);
  *4:�ɽ�״̬(real_status);5:�ɽ�����(real_type);7:ת��״̬(bktrans_status)8:�������(money_type);
  *8:���н�������(trans_type)
  *12:��Ʊ����(exchange_type,stock_code);13:ҵ���־(business_flag):14:���д���(bank_no)
 *@param IASContext * pContext �����ģ����ڻ�ȡ�ڴ����ݿ�ĵ��ýӿ�
 *@param IResultSet * lpResultSet Դ�����
 *@param IPacker *	lpOutPacker  ���������ӿ�
 *@return �ɹ�0��ʧ��-1
 */
int getPrompt(unsigned long lFlag,IAS2Context * pContext,IF2ResultSet * lpInUnPacker,IF2Packer * lpOutPacker);

///ʹ���ڴ����ݿ⽫������ܱ����к�ת��Ϊ��̨�����к�
/**
 *ʹ��ʱ��Ҫ��AS���ڴ����ݿ����ò������ӣ�
		<table name="outerconfig"  logic_name="hsrun" type="1" note="1����0����">
				<statement note="�����ļ�">
					<select>*</select>
					<from>outerconfig</from>
				</statement>
		</table>
 *@param IASContext * pContext �����ģ����ڻ�ȡ�ڴ����ݿ�ĵ��ýӿ�
 *@param const char *lpOutBankNo �ܱ����к�
 *@param char *lpBankNo �����̨�����к�
 *@param int iBufSize �����̨���кŵ���󳤶�
 *@return �ɹ�0��ʧ��-1
 */
int getBankNo(IAS2Context * pContext,int action_in, int lBranchNo, const char *lpOutBankNo, char *lpBankNo, int iBufSize);


///ʹ�û������ܱߵĴ���Ž���ת��
/**
 *@param IASContext * pContext �����ģ�
 *@param const int lFunctionId ���ܺ�
 *@param const int lErrorId �����
 *@return ת����Ĵ����
 */
extern int getExternErrorXml(IAS2Context * pContext,const int lFunctionId,const int lErrorId);

///ʹ�û��������еĴ���Ž���ת��
/**
 *@param IASContext * pContext �����ģ�
 *@param const int lErrorId �����
 *@return ת����Ĵ����
 */
extern int getBankErrorXml(IAS2Context * pContext,const int lErrorId);

//zhangly 20051213 ���� ҵ�񸴺����ú���-------------------------------------
//���ø��˹����麯��
bool CheckAuditRule( char * rule1_field,char rule1_type,char * rule1_value,char rule1_op,char * check_value1,char rule1_logic,
                     char * rule2_field,char rule2_type,char * rule2_value,char rule2_op,char * check_value2,char rule2_logic,
                     char * rule3_field,char rule3_type,char * rule3_value,char rule3_op,char * check_value3 );
//ȡ���˼���ֶ�ֵ
char * GetAuditCheckValue(char * sFieldName,IF2UnPacker * lpInUnPacker,IF2UnPacker * lpInUnPackerParent,char * amount_value,char * balance_value);

//����Զ��ŷָ��Ľ�ɫ�����Ƿ��ڲ���Ա��ɫ����
bool CheckOPRolesStr(char * src,char * RolesStr);

//zhangly 20051213 ���� ҵ�񸴺����ú��� end-------------------------------------

/* 20060219 wangjz �����������봦��ͬע���й��ù�����غ���ͬ�� */
char* hs_EncodeBkPwd(const char *bk_password, char *password_out);

char* hs_DecodeBkPwd(const char *bk_password, char *password_out);

//20060331 wangjz ����
/*ȡ�ַ����� byPart ����, byPart >= 1*/
void GetPart(const char *Buf, char cDelimiter, int byPart, char *pValue);

//20060701 wangjz add
/*ȡ���ʱ�䣬����Ϊ��λ*/
int GetIntervalSec(int HsTimePre, int HsTimeNext);

//20070118 weiye add
/*�ڻ�����ͻ�����*/
extern char* DecodeFuPwd(char *lPassword, const char *EncodePwd);

//20090912 wanglb,zhouwm ���ڵ�������Ȩ�������ܼ�У��ĺ��� begin


/*==========================================================
 * Function   : Decrypt
 * Description: ����Liscense
 * Input      : char *pDecLiscense ���ܺ��Liscense
 *              const char *pLiscense ����ļ���Liscense
 *              unsigned dwKey ��Կ
 * Output     : 
 * Return     : char *pULiscense��ַ
 * Author     : wanglb,zhouwm
 * Date       : 2008/09/12
 ==========================================================*/
char *Decrypt(char *pDecLiscense,const char *pLiscense,unsigned dwKey);

/*==========================================================
 * Function   : CheckLiscense
 * Description: �Դ����Liscense��Ч�Լ��Ƿ���ڽ���У��
 * Input      : IASContext *lpContext �������ݿ�ʹ��
 *              const char *pLiscense ����ļ���Liscense
 *              unsigned dwKey ��Կ
 *              char *pProductID ��Ʒ���
 *              char *pOtherCompany ����������(Ŀǰû��ʹ��,���Ǳ����ýӿ�,���Ժ����ʹ��)
 *              struct tm *tBeginTime ʱ��ṹ�壬���ڱ����м��AS����ʱ��
 *              char *pErrorMsg ���ڱ����������ش�����Ϣ
 * Output     : 
 * Return     : 0 ��Ч���ڣ�����ʹ��
 *              -1 ���ڴ���
 * Author     : wanglb,zhouwm
 * Date       : 2008/09/12
 ==========================================================*/
extern int CheckLiscense(IAS2Context *lpContext,const char *pLiscense,char *pProductID,char *pOtherCompany,int iTimeMin,char *pErrorMsg);

/*==========================================================
 * Function   : GetCompanyName
 * Description: ����ȡsysarg�е�֤ȯ��˾����
 * Input      : IASContext *pContext �������ݿ�ʹ��
 *              char *pStkCompany ֤ȯ��˾����
 * Output     : 
 * Return     : true �ɹ�
 *              false ʧ��
 * Author     : wanglb,zhouwm
 * Date       : 2008/09/12
 ==========================================================*/
/*�Ѵ����ݿ��ȡ�ĳɴ��ڴ����ݿ��ȡ*/
bool GetCompanyName(IAS2Context * pContext,char *pStkCompany);

//20090912 wanglb,zhouwm ���ڵ�������Ȩ�������ܼ�У��ĺ��� end.

/*==========================================================
 * Function   : GetSecuAssetPrice
 * Description: ȡ֤ȯ��ֵ��
 * Input      : IUnPacker  lpContext	������
 *              char * szSecuExchType   �������
 *              char * szStockCode      ֤ȯ����
 *              char * szStockType      ֤ȯ���
 *              int iStoreUnit          ��ŵ�λ
 *              char cAssetFlag         ������ֵ��־
 * Output     : Asset_Price             ��ֵ��
 * Return     : >=0		    �ɹ�
 *				<0          ʧ�� 		
 * Author     : zhouwm
 * Date       : 2008/12/03.
 ==========================================================*/
extern double GetSecuAssetPrice(IAS2Context *lpContext,char * szSecuExchType,char * szStockCode,char * szStockType,int iStoreUnit,char cAssetFlag);


/*==========================================================
 * Function   : GetSecuLastPrice
 * Description: ȡ֤ȯ���¼�
 * Input      : IUnPacker  lpContext	������
 *              char * szSecuExchType   �������
 *              char * szStockCode      ֤ȯ����
 *              char * szStockType      ֤ȯ���
 * Output     : Last_Price             ���¼�
 * Return     : >=0		    �ɹ�
 *				<0          ʧ�� 		
 * Author     : zhouwm
 * Date       : 2008/12/03.
 ==========================================================*/
extern double GetSecuLastPrice(IAS2Context *lpContext,char * szSecuExchType,char * szStockCode,char * szStockType);


/*==========================================================
 * Function   : GetDebtInterest
 * Description: ȡ��ծ��Ϣ
 * Input      : IUnPacker  lpContext	������
 *              char * szSecuExchType   �������
 *              char * szStockCode      ֤ȯ����
 *              char * szStockType      ֤ȯ���(����Ϊ��)
 * Output     : Last_Price             ���¼�
 * Return     : >=0		    �ɹ�
 *				<0          ʧ�� 		
 * Author     : zhouwm
 * Date       : 2008/12/03.
 ==========================================================*/
extern double GetSecuDebtInterest(IAS2Context *lpContext,char * szSecuExchType,char * szStockCode,char * szStockType);

/*==========================================================
 * Function   : GetSecuCode
 * Description: ȡ֤ȯ����
 * Input      : IAS2Context*  lpContext        ������
 *              IF2UnPacker * lpInUnPacker     �����
 *              IF2Packer *   lpOutPacker      Ӧ���
 * Output     : 
 * Return     : >=0		    �ɹ�
 *				<0          ʧ�� 		
 * Author     : zhouwm
 * Date       : 2009/05/12.
 ==========================================================*/
extern int GetSecuCode(IAS2Context* lpContext,IF2UnPacker * lpInUnPacker,IF2Packer * lpOutPacker);

/*==========================================================
 * Function   : GetSecuCodePrice
 * Description: ȡ֤ȯ������Ϣ�����¼ۣ���ֵ��
 * Input      : IAS2Context*  lpContext        ������
 *              IF2UnPacker * lpInUnPacker     �����
 *              IF2Packer *   lpOutPacker      Ӧ���
 * Output     : 
 * Return     : >=0		    �ɹ�
 *				<0          ʧ�� 		
 * Author     : zhouwm
 * Date       : 2009/05/12.
 ==========================================================*/
extern int GetSecuCodePrice(IAS2Context* lpContext,IF2UnPacker * lpInUnPacker,IF2Packer * lpOutPacker);

///begin 20110729 ��Ԫ�� add, ����һ���������GetCaeCodePrice�����GetSecuCodePrice�������嵵����۸���Ϣ�ķ���
/*==========================================================
 * Function   : GetCaeCodePrice
 * Description: ȡ֤ȯ������Ϣ�����¼ۣ���ֵ��+�嵵������Ϣ
 * Input      : IAS2Context*  lpContext        ������
 *              IF2UnPacker * lpInUnPacker     �����
 *              IF2Packer *   lpOutPacker      Ӧ���
 * Output     : 
 * Return     : >=0		    �ɹ�
 *				<0          ʧ�� 		
 * Author     : zhouwm
 * Date       : 2009/05/12.
 ==========================================================*/
extern int GetCaeCodePrice(IAS2Context* lpContext,IF2UnPacker * lpInUnPacker,IF2Packer * lpOutPacker);
///end 20110729 ��Ԫ�� add, ����һ���������GetCaeCodePrice�����GetSecuCodePrice�������嵵����۸���Ϣ�ķ���

/*==========================================================
 * Function   : GetUserToken
 * Description: �û����ƻ�ȡ
 * Input      : IUnPacker  lpContext	    ������
 *              cosnt int iInitDate         ϵͳ��ʼ������
 *              const char cCertType        ������
 *              const char * sCertAccount   ����ʺ�
 *              const char cPasswordType    �������
 *              const char * sPassword      ����
 *              const char   cPasswordCheck ����У��
 * Output     : char *sUserToken            ����
 * Return     : >=0		    �ɹ�
 *				<0          ʧ�� 		
 * Author     : zhouwm,lilb
 * Date       : 2008/12/03.
 ==========================================================*/
extern int GetUserToken(IAS2Context *lpContext,char *sUserToken,const int iInitDate, const char cCertType,const char * sCertAccount,const char cPasswordType,const char * sPassword,const char cPasswordCheck);

/*==========================================================
 * Function   : CheckUserToken
 * Description: �û�����У��
 * Input      : IUnPacker  lpContext	    ������
 *              char *sUserToken            ����
 *              cosnt int iInitDate         ϵͳ��ʼ������
 *              const char cCertType        ������
 *              const char * sCertAccount   ����ʺ�
 *              const char cPasswordType    �������
 *              const char * sPassword      ����
 * Output     : 
 * Return     : >=0		    �ɹ�
 *				<0          ʧ�� 		
 * Author     : zhouwm
 * Date       : 2008/12/03.
 ==========================================================*/
extern int CheckUserToken(IAS2Context *lpContext,char *sUserToken,const int iInitDate, const char cCertType,const char * sCertAccount,const char cPasswordType,const char * sPassword);

/*==========================================================
 * Function   : GetFileBuffer
 * Description: ȡ���ö�����Ϣ
 * Input      : IAS2Context  lpContext      ������
 *              void * lpBuf                ��������ַ
 *              int iBufSize                ��������С
 *              char *sLocation             ���ö���λ��
 *              IRCfgObj *pCfgObj           �����ļ�����
 * Output     : 
 * Return     : >=0         �ɹ�
 *              <0          ʧ��        
 * Author     : zhouwm
 * Date       : 2009/01/17.
 ==========================================================*/
extern int GetFileBuffer(IAS2Context *lpContext,IRCfgObj *pCfgObj,char * sBuf,char *sLocation);

/*==========================================================
 * Function   : SaveFileBuffer
 * Description: �������ö�����Ϣ
 * Input      : IAS2Context  lpContext      ������
 *              void * lpBuf                ��������ַ
 *              long * iBufSize             ��������С
 *              IWCfgObj *pWCfgObj          �����ļ�����
 * Output     : 
 * Return     : >=0         �ɹ�
 *              <0          ʧ��        
 * Author     : zhouwm
 * Date       : 2009/01/17.
 ==========================================================*/
extern int SaveFileBuffer(IAS2Context *lpContext,IWCfgObj *pWCfgObj,char* sBuf);

/*==========================================================
 * Function   : GetNewWCfgObj
 * Description: ��ȡ��д���ö���
 * Input      : IAS2Context  lpContext     ������
 *              IWCfgObj *pCfgObj           ��д���ö���
 *              char *sLocation             ���ö���λ��
 * Output     : 
 * Return     : >=0     �ɹ�
 * <0          ʧ��  
 * Author     : zhouwm
 * Date       : 2009/01/17.
 ==========================================================*/
extern int GetNewWCfgObj(IAS2Context *lpContext,IWCfgObj *pCfgObj,char *sLocation);

/*==========================================================
 * Function   : CheckAccessLicense
 * Description: �������У��
 * Input      : IAS2Context  lpContext          ������
 * Output     : 
 * Return     : =0                       �ɹ�
 *                                 >0          ʧ�� 
 * Author     : lilb
 * Date       : 2009/02/13
 ==========================================================*/
extern int CheckAccessLicense(IAS2Context *lpContext);

/*==========================================================
 * Function   : EncodeTwoWord
 * Description: ���ּ����㷨
 * Input      :  char *pIn  ��Ҫ���ܵ�Դ
 * Output     :  char *pOut ���ܽ��
 * Return     : =0          �ɹ�
 *              <>0         ʧ�� 
 * Author     : wangry
 * Date       : 2009/04/16
 ==========================================================*/
extern int EncodeTwoWord(char *pIn, char *pOut);

/*==========================================================
 * Function   : DecodeTwoWord
 * Description: ���ֽ����㷨
 * Input      :  char *pIn  �����ܵ�Դ
 * Output     :  char *pOut ���ܽ��
 * Return     : =0          �ɹ�
 *              <>0         ʧ�� 
 * Author     : wangry
 * Date       : 2009/04/16
 ==========================================================*/
extern int DecodeTwoWord(char *pIn, char *pOut);

/*==========================================================
 * Function   : EtfToStruct
 * Description: ETF�ɷֹ���Ϣ���浽�ṹ������
 * Input      :  IAS2Context * lpContext        ������
 *            :  S_ETFCOMPONENT **pEtfComponent �ɷݹɽṹ����
 *            :  const char     *sMdbTable      �ڴ����
 *            :  const char     *sWhere         ��ѯ����
 * Return     : =0          �ɹ�
 *              <>0         ʧ�� 
 * Author     : zhouwm
 * Date       : 2009/05/06
 ==========================================================*/
extern int EtfToStruct(IAS2Context * lpContext,S_ETFCOMPONENT *pEtfComponent,char *sMdbTable,char *sWhere,int * iErrorNo,char * sErrorInfo,char *sErrorPathInfo);

/*==========================================================
 * Function   : EtfResultUnion
 * Description: ��������ĳɷִ����޸�ETF�ɷֹ���Ϣ�ṹ�����ж�Ӧ�ĳɷִ�����������
 * Input      :  S_ETFCOMPONENT **pEtfComponent        �ɷݹɽṹ����
 *            :  const int      iArrayLen              �ṹ����
 *            :  const int      iListLen               ���鳤��
 *            :  char           sComponentCode[][7]    �ɷݹɴ���
 *            :  double         dEnableAmount[]        ��������
 *            :  double         dIssueAmount[]         ���깺�������
 * Return     :  =0          �ɹ�
 *               <>0         ʧ�� 
 * Author     : zhouwm
 * Date       : 2009/05/06
 ==========================================================*/
extern int EtfResultUnion(S_ETFCOMPONENT *pEtfComponent,const int iArrayLen,const int iListLen,char sComponentCode[][7],double dEnableAmount[],double dIssueAmount[]);

/*==========================================================
 * Function   : ResultSearch
 * Description: ETF�ɷֹ���Ϣ�������
 * Input      :  S_ETFCOMPONENT **pEtfComponent     �ɷݹɽṹ
 *            :  const int      *sComponentCode     ���鳤��
 *            :  const char     *sComponentCode     �ɷֹ�Ʊ����
 * Return     :  >=0            �ɹ�
 *               <0             ʧ�� 
 * Author     : zhouwm
 * Date       : 2009/05/06
 ==========================================================*/
extern int ResultSearch(S_ETFCOMPONENT *pEtfComponent,const int iArrayLen,const char *sComponentCode);

/*==========================================================
 * Function   : DecryptHsLicense
 * Description: ����Liscense
 * Input      : char *pDecLiscense ���ܺ��Liscense
 *              const char *pLiscense ����ļ���Liscense
 *              unsigned short dwKey  ��Կ
 * Output     :
 * Return     : pDecLiscense
 * Author     : chengjh
 * Date       : 2009/04/24
 ==========================================================*/
extern char *DecryptHsLicense(char *pDecLiscense,const char *pLiscense,int usKey);
/*==========================================================
 * Function   : EncryptHsLicense
 * Description: ����Liscense
 * Input      : char *pEncLiscense ���ܺ��Liscense
 *              const char *pLiscense ����ļ���Liscense
 *              unsigned short dwKey  ��Կ
 * Output     : char *pEncLiscense ���ܺ��Liscense
 * Return     : pEncLiscense
 * Author     : yangsb
 * Date       : 2009/05/23
 ==========================================================*/
extern char * EncryptHsLicense(char *pEncLiscense,const char *pLiscense,unsigned short usKey);

/*==========================================================
 * Function   : ProfessionCode2Hs6
 * Description: ���ڰ�08ְҵ����ת��Ϊ06��
 * Input      : char *sz_src Դ�ַ���
 *              char *sz_dest ת�����06��ְҵ����
 * Output     : char *sz_dest ת�����06��ְҵ����
 * Return     : char *
 * Author     : yangsb
 * Date       : 2009/06/01
 ==========================================================*/
extern char * ProfessionCode2Hs6(const char *sz_src,char *sz_dest);

/*==========================================================
 * Function   : Nationality2Hs6
 * Description: ���ڰ�08������������ת��Ϊ06��
 * Input      : char *sz_src Դ�ַ���
 * Output     : char ת�����06�������������
 * Return     : char 
 * Author     : yangsb
 * Date       : 2009/06/01
 ==========================================================*/
extern char Nationality2Hs6(const char *sz_src);

/*==========================================================
 * Function   : CheckSystemLicense
 * Description: ϵͳ���У��
 * Input      : IAS2Context  lpContext         ������
 *              int & nBranchCnt               Ӫҵ������ 
 *              int & nClientCnt               �ͻ�����
 *              int & nValidDate               ��Ч����
 * Output     : 
 * Return     : =0                             �ɹ�
 *                                 >0          ʧ�� 
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
	// Blowfish�㷨��������ԿԼ����16�ֽڡ�����������������ͬһ��
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
 * Description: Blowfish����
 * Input      : const void *lpIn         		���������
 *              int nLength               		���ĳ��� 
 *              const void *lpKey               ������Կ
 * Output     : lpOut 							���������
 * Return     : void
 * Author     : wangry
 * Date       : 2011/02/15
 ==========================================================*/
extern void BFEncode(void *lpOut, const void *lpIn, int nLength, const void *lpKey);

/*==========================================================
 * Function   : BFDecode
 * Description: Blowfish����
 * Input      : const void *lpIn         		���������
 *              int nLength               		���ĳ��� 
 *              const void *lpKey               ������Կ
 * Output     : lpOut 							���������
 * Return     : void
 * Author     : wangry
 * Date       : 2011/02/15
 ==========================================================*/
extern void BFDecode(void *lpOut, const void *lpIn, int nLength, const void *lpKey);


/*==========================================================
* Function   : HsPwdEncode
* Description: ��������
* Input      : const char *pIn ��������봮
*              char *pOut ����ļ��ܺ�����롣
* Return     : 0: �ɹ�������ʧ�ܡ�
* Author     : wangry
* Date       : 2010/03/03
==========================================================*/
extern int HsPwdEncode(const char *pIn, char *pOut);

/*==========================================================
* Function   : HsPwdDecode
* Description: �������
* Input      : const char *pIn ����ļ��ܵ����봮
*              char *pOut ����Ľ��ܺ�����롣
* Return     : 0: �ɹ�������ʧ�ܡ�
* Author     : wangry
* Date       : 2010/03/03
==========================================================*/
extern int HsPwdDecode(const char *pIn, char *pOut);

#endif /* _S_GLBFUNCTION_OR_H */

