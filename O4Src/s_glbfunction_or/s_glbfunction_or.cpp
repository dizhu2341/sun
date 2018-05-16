/*
 * Program: s_glbfunction_or.cpp
 * Author : zhouwm.
 * Date   : 2008/10/14.
 * Notes  : 提供系统公共函数
 * Modify : 版本       修改日期  申请人  修改人   修改单          修改说明
 *          V8.0.6.1   20110729          刘元召   20110728043     增加一个输出函数GetCaeCodePrice，相比GetSecuCodePrice多增加五档行情价格信息的返回
 *      		V8.0.6.0   20100614          刘元召   内部            经纪业务运营平台V2.0项目2011基线建立
   					V8.0.5.4   20110315  李玲斌  李玲斌  	20110308021			security.a变动后的重新编译
 * 					V8.0.5.3   20110303  王仁云  王仁云  	20110301024			将加密和解密相关的放到license_security动态库中。增加密码加密和解密函数。
 *          V8.0.5.2   20110222  李玲斌  李玲斌  	20101228018  		为中信扩展口令获取与检验
 * 					V8.0.5.1   20110215  王仁云  王仁云  	20110216030			为统一接入增加Blowfish加密和解密，并修改s_glbfunction_or.gcc文件，静态链接libsecurity.a。
 *          V8.0.5.0   20100414  周伟明  周伟明   内部            基线
 *          V8.0.4.1   20100121  陈  飞  周伟明   JJYWYYPT-5421   EtfToStruct()增加字段输出redeem_replace_balance和secu_market_code begin
 *          V8.0.4.0   20090926  周伟明  周伟明   内部            基线
 *          V8.0.3.0   20090626  周伟明  周伟明   内部            打包
 *          V8.0.2.0   20090420  周伟明  周伟明   内部            打包
 *          V8.0.1.0   20090120  周伟明  周伟明   内部            打包
 */

#include "hshead.h"

/*==========================================================
 * Function   : GetLibVersion
 * Description: 获取版本信息
 * Input      : 
 * Output     : 
 * Return     : so版本信息
 * Author     : zhouwm
 * Date       : 2007/12/07
 ==========================================================*/
#ifdef OS_UNIX
#ifndef _NOTEXPORT_VER_
char *  FUNCTION_CALL_MODE GetLibVersion( )
{
    return "V9.0.2.0";
}
#endif
#endif

/*取内存表数据信息*/
int GetMdbData(IAS2Context * lpContext, IF2UnPacker * lpInUnPacker, IF2Packer * lpOutPacker,int * iErrorNo,char * sErrorInfo,char *sErrorPathInfo)
{
   return lib_GetMdbData(lpContext, lpInUnPacker, lpOutPacker, iErrorNo, sErrorInfo, sErrorPathInfo); 
}

/*内存表数据同步*/
int SyncMdbData(IAS2Context * lpContext, IF2UnPacker * lpInUnPacker, IF2Packer * lpOutPacker,int * iErrorNo,char * sErrorInfo,char *sErrorPathInfo)
{
   int iReturnCode = 0;
   int i = 0,j = 0;
   int li_count = 0;
   int  p_error_no = 0;
    
   char * p_table_name = (char *)lpInUnPacker->GetStr("table_name");
   char * p_where_str = (char *)lpInUnPacker->GetStr("where_str");
   
   IMdbService * lpMDB = NULL;
   lpContext->QueryInterface(SID_MDB,(IKnown **)&lpMDB);
   
   if (lpMDB)
   {   
      int iSession = lpContext->GetMDBSession();
      if (iSession >= 0)
      {
         trim(p_where_str);
         iReturnCode = lpMDB->Sync(p_table_name,p_where_str);
         if (iReturnCode != 0)
         {
            p_error_no = ERR_SYNCMDBTABLE_FIAL;
            hs_snprintf(sErrorInfo,500,"同步内存数据库表失败[内存表: %s][条件: %s][%d]",p_table_name,p_where_str,iReturnCode);
            hs_strncat(sErrorPathInfo," -> SyncMdbData()->Sync()",500);
            iReturnCode = p_error_no;
         }
      }
      else
      {
          p_error_no = ERR_SYNCMDBTABLE_FIAL;
          hs_snprintf(sErrorInfo,500,"同步内存数据库表失败[内存表: %s][条件: %s]",p_table_name,p_where_str);
          hs_strncat(sErrorPathInfo," -> SyncMdbData()->GetMDBSession()",500);
          iReturnCode = p_error_no;
          
          goto svr_end;
      }
   }
   else
   {
      p_error_no = ERR_GETMEMORYDATASESSIONFAIL;
      hs_strcpy(sErrorInfo,"取内存数据服务错误");
      hs_strncat(sErrorPathInfo," -> SyncMdbData()->QueryInterface()",500);
      iReturnCode = p_error_no;
      goto svr_end;
   }
   
   goto svr_end;
   
svr_end:
   if (iReturnCode != 0)
   {
      *iErrorNo = p_error_no;
   }

   return iReturnCode;        
}

//取错误信息
char * GetErrorInfo(IAS2Context * pContext,int p_iErrorNo,char * p_sErrorInfo)
{
  int p_curr_time = 0;
  int p_error_no  = p_iErrorNo;
  char p_error_info[501] = {0};
  char p_error_pathinfo[501] = {0};
  char p_sErrorInfo1[501] = {0};
  char p_tmp[2001] = {0};
  int iReturnCode = 0;
  char sWhere[256]={0};
  char p_error_no_str[33]={0};
  IF2PackSvr * lpPackService = pContext->GetF2PackSvr();
  IF2Packer * lpFuncInPacker = lpPackService->GetPacker(2);
  IF2Packer * lpOutput=lpPackService->GetPacker(2);
  IF2UnPacker * lpResultSet = NULL;
  
  //从相关参数取起
  if(!strchr(p_sErrorInfo, '['))
    p_sErrorInfo1[0] = 0;
  else
  {
    hs_snprintf(p_error_no_str,32,"[%d]",p_error_no);
    if (hs_strstr(p_sErrorInfo,p_error_no_str) > 0)
    	goto svr_end;
    
    strcpy(p_sErrorInfo1, strchr(p_sErrorInfo, '['));
  }
  hs_snprintf(sWhere,255, "error_no=%d", p_error_no);
  lpFuncInPacker->BeginPack();
  lpFuncInPacker->AddField("error_pathinfo");
  lpFuncInPacker->AddField("table_name");
  lpFuncInPacker->AddField("column_str");
  lpFuncInPacker->AddField("where_str");
  lpFuncInPacker->AddStr("GetErrorInfo()");
  lpFuncInPacker->AddStr("errormsg");
  lpFuncInPacker->AddStr("error_info");
  lpFuncInPacker->AddStr(sWhere);
  lpFuncInPacker->EndPack();

  lpOutput->BeginPack();
  iReturnCode = GetMdbData(pContext,lpFuncInPacker->UnPack(),lpOutput,&p_error_no,p_error_info,p_error_pathinfo);
  lpOutput->EndPack();
  lpResultSet = lpOutput->UnPack();

  if ( 0 != iReturnCode )
  {
    p_error_no = lpResultSet->GetInt("error_no");
    hs_snprintf(p_error_pathinfo, 500,"%s", lpResultSet->GetStr("error_pathinfo"));
    hs_snprintf(p_error_info, 500,"%s", lpResultSet->GetStr("error_info"));
    goto svr_end;
  }
  else
  {
     if (!lpResultSet->IsEmpty())
     {
        hs_strcpy(p_error_info, lpResultSet->GetStr("error_info"));
     }
  }
  
  if(p_sErrorInfo1[0])
  {
    hs_snprintf(p_tmp,2000, "[%d][%s]\r\n%s\n", p_iErrorNo, (char *)p_error_info, (char *)p_sErrorInfo1);
    hs_strncpy(p_sErrorInfo,p_tmp,500);
  }
  else
  {
    hs_snprintf(p_tmp,2000, "[%d][%s]\n", p_iErrorNo, (char *)p_error_info);
    hs_strncpy(p_sErrorInfo,p_tmp,500);
  }
  goto svr_end;

svr_end:
  if (lpFuncInPacker)
  { 
    free(lpFuncInPacker->GetPackBuf());
    lpFuncInPacker->Release();
  }
  if (lpOutput)
  {
    free(lpOutput->GetPackBuf());
    lpOutput->Release();
  }
  
  return p_sErrorInfo;
}

//取错误信息,将函数报错将原来的错误信息附加在后面
char * GetErrorInfox(IAS2Context * lpContext,int p_iErrorNo,char * p_sErrorInfo)
{
  IF2XmlFIleGetService * lpXmlFileGet = NULL;
  lpContext->QueryInterface(SID_SVR_XMLFILEGET,(IKnown **)&lpXmlFileGet);
    
  char ls_ErrorSort[2] = {0};
  char ls_ErrorSource[9] = {0};
  char ls_ErrorNo[9] = {0};
  int iRet = 0;

  hs_strcpy(ls_ErrorSort,"3");
  hs_strcpy(ls_ErrorSource,"0");
  hs_snprintf(ls_ErrorNo,8,"%d",p_iErrorNo);
  
  if (lpXmlFileGet)
  {
  	  iRet = lpXmlFileGet->pf_GetExternErrorInfo(ls_ErrorSort,ls_ErrorSource,ls_ErrorNo,p_sErrorInfo);
      if (iRet < 0)
		  goto svr_end;
  }
  else
  {
  	  iRet = -1;
	  goto svr_end;
  }
   
svr_end: 
  if (iRet < 0)
     hs_strcpy(p_sErrorInfo,"其它系统错误");

  return p_sErrorInfo;
}

// 生成随机数
int randomx(int iSeed)
{
  //srand( (unsigned)time( NULL ) );// 加上可能会好些
  return (rand() % iSeed);
}

// 加密函数
char* Encode(char *EncodePass, const char* Password, int Key)
{
  return lib_Encode(EncodePass,  Password, Key);
}

char* EncodeBkPwd(char *EncodePass, const char *lPassword)
{
  return lib_EncodeBkPwd(EncodePass, lPassword);
}

char* DecodeBkPwd(char *lPassword, const char *EncodePwd)
{
  return lib_DecodeBkPwd(lPassword, EncodePwd);
}

char * getInFieldName(unsigned lFlag)
{
  switch(lFlag)
  {
  case PMFLAG_ENTRUST_BS:
    return "entrust_bs";
  case PMFLAG_ENTRUST_STATUS:
    return "entrust_status";
  case PMFLAG_EXCHANGE_TYPE:
    return "exchange_type";
  case PMFLAG_BUSINESS_TYPE:
    return "business_type";
  case PMFLAG_REAL_STATUS:
    return "business_status";
  case PMFLAG_REAL_TYPE:
    return "business_type";
  case PMFLAG_BKTRANS_STATUS:
    return "entrust_status";
  case PMFLAG_MONEY_TYPE:
    return "money_type";
  case PMFLAG_TRANS_TYPE:
    return "business_type";
  case PMFLAG_STOCK_CODE:
    return "stock_code";
  case PMFLAG_BUSINESS_FLAG:
    return "business_flag";
  case PMFLAG_BANK_NO:
    return "bank_no";
  case PMFLAG_ERROR_NO:
    return "error_no";
  default:
    return NULL;
  }
}

char * getOutFieldName(unsigned lFlag)
{
  switch(lFlag)
  {
  case PMFLAG_ENTRUST_BS:
    return "bs_name";
  case PMFLAG_ENTRUST_STATUS:
    return "status_name";
  case PMFLAG_EXCHANGE_TYPE:
    return "exchange_name";
  case PMFLAG_BUSINESS_TYPE:
    return "type_name";
  case PMFLAG_REAL_STATUS:
    return "status_name";
  case PMFLAG_REAL_TYPE:
    return "type_name";
  case PMFLAG_BKTRANS_STATUS:
    return "entrust_name";
  case PMFLAG_MONEY_TYPE:
    return "money_name";
  case PMFLAG_TRANS_TYPE:
    return "trans_name";
  case PMFLAG_STOCK_CODE:
    return "stock_name";
  case PMFLAG_BUSINESS_FLAG:
    return "business_name";
  case PMFLAG_BANK_NO:
    return "bank_name";
  case PMFLAG_ERROR_NO:
    return "cancel_info";
  default:
    return "unknow";
  }
}

char * getTableName(unsigned lFlag)
{
  switch(lFlag)
  {
  case PMFLAG_ENTRUST_BS:
    return "dict_bs_flag";
  case PMFLAG_ENTRUST_STATUS:
    return "dict_entrust_status";
  case PMFLAG_EXCHANGE_TYPE:
    return "dict_exchange_type";
  case PMFLAG_BUSINESS_TYPE:
    return "dict_business_type";
  case PMFLAG_REAL_STATUS:
    return "dict_business_status";
  case PMFLAG_REAL_TYPE:
    return "dict_business_kind";
  case PMFLAG_BKTRANS_STATUS:
    return "dict_trans_status";
  case PMFLAG_MONEY_TYPE:
    return "dict_money_type";
  case PMFLAG_TRANS_TYPE:
    return "dict_bank_trans_type";
  case PMFLAG_STOCK_CODE:
    return "stkcode";
  case PMFLAG_BUSINESS_FLAG:
    return "businflag";
  case PMFLAG_BANK_NO:
    return "dict_bank_name";
  default:
    return NULL;
  }
}

int getBankNo(IAS2Context * lpContext,const int action_in,int lBranchNo, const char *lpOutBankNo, char *lpBankNo, int iBufSize)
{
  char psWhere[256];
  int iReturnCode = 0;
  int p_error_no  = 0;
  char p_error_info[501] = {0};
  char p_error_pathinfo[501] = {0};
  IF2PackSvr * lpPackService = lpContext->GetF2PackSvr();
  IF2Packer * lpFuncInPacker = lpPackService->GetPacker(2);
  IF2Packer * lpOutput=lpPackService->GetPacker(2);
  IF2UnPacker * lpResultSet = NULL;

  //若内存数据库异常或取不到相应数据，返回输入的bank_no
  strncpy(lpBankNo, lpOutBankNo, iBufSize);
  lpBankNo[iBufSize] = '\0';
  
  if (action_in == 1) 
  {
    hs_snprintf(psWhere,255,"branch_no=%d and config_value_in='%s'", lBranchNo, lpOutBankNo);
  }
  else
  {
    hs_snprintf(psWhere,255,"branch_no=%d and config_value_out='%s'", lBranchNo, lpOutBankNo);
  }
  lpFuncInPacker->BeginPack();
  lpFuncInPacker->AddField("error_pathinfo");
  lpFuncInPacker->AddField("table_name");
  lpFuncInPacker->AddField("column_str");
  lpFuncInPacker->AddField("where_str");
  lpFuncInPacker->AddStr("getBankNo()");
  lpFuncInPacker->AddStr("errormsg");
  lpFuncInPacker->AddStr("error_info");
  lpFuncInPacker->AddStr(psWhere);
  lpFuncInPacker->EndPack();

  lpOutput->BeginPack();
  iReturnCode = GetMdbData(lpContext,lpFuncInPacker->UnPack(),lpOutput,&p_error_no,p_error_info,p_error_pathinfo);
  lpOutput->EndPack();
  lpResultSet = lpOutput->UnPack();

  if ( 0 != iReturnCode )
  {
    p_error_no = lpResultSet->GetInt("error_no");
    hs_snprintf(p_error_pathinfo,500, "%s", lpResultSet->GetStr("error_pathinfo"));
    hs_snprintf(p_error_info,500, "%s", lpResultSet->GetStr("error_info"));
    //iReturnCode = lpContext->setError(ERR_GETMEMORYDATASESSIONFAIL, p_error_info);
    goto svr_end;
  }
  else
  {
     if (!lpResultSet->IsEmpty())
     {
        if (action_in == 1) 
        {
           strncpy(lpBankNo, lpResultSet->GetStr("config_value_out"), iBufSize);
        }
        else
        {
           strncpy(lpBankNo, lpResultSet->GetStr("config_value_in"), iBufSize);
        }
        lpBankNo[iBufSize] = '\0';
     }
  }
  goto svr_end;
svr_end:  
  
  if (lpFuncInPacker)
  { 
    free(lpFuncInPacker->GetPackBuf());
    lpFuncInPacker->Release();
  }
  if (lpOutput)
  {
    free(lpOutput->GetPackBuf());
    lpOutput->Release();
  }

  return iReturnCode;
}

int getPrompt(unsigned long lFlag,IAS2Context * lpContext,IF2ResultSet * lpInUnPacker,IF2Packer * lpOutPacker)
{
  int i;
  unsigned long tlFlag;
  char *psTableName;
  const char *psInFieldName;
  char psWhere[256];
  char p_error_info[501] = {0};
  int ierror_no;
  //IResultSet * lpInUnPacker = NULL;
  IF2ResultSet * lpMDBResultSet = NULL;

  //取数据库服务    
  IMdbService * lpMDB = NULL;
  lpContext->QueryInterface(SID_MDB,(IKnown **)&lpMDB);
  //取缺省连接
  int iSession = lpContext->GetMDBSession();

  if(!lFlag || (lpMDB == NULL) || (iSession < 0))//没有字段需要解析,或无法访问内存数据库
  {
    PackResultSet(lpInUnPacker,lpOutPacker);
    return 0;
  }

  //增加字段名
  for(i = 0; i < lpInUnPacker->GetColCount(); i++)
    lpOutPacker->AddField(lpInUnPacker->GetColName(i));
  for(tlFlag = 1; tlFlag <= lFlag; tlFlag *= 2)
    if(lFlag & tlFlag)
      lpOutPacker->AddField(getOutFieldName(tlFlag));

  //插入数据
  while(!lpInUnPacker->IsEOF())
  {
    for(i = 0; i < lpInUnPacker->GetColCount(); i++)
    {
      if((lFlag & PMFLAG_BANKNO) && (strcmp(lpInUnPacker->GetColName(i), "bank_no") == 0))
      {
        hs_snprintf(psWhere,255,"branch_no=%d and config_value_out='%s'",lpInUnPacker->GetInt("branch_no"),lpInUnPacker->GetStr("bank_no"));
        lpMDBResultSet = lpMDB->Query(iSession,"outerconfig","*",psWhere);
        if(lpMDBResultSet)
        {
          if(!lpMDBResultSet->IsEmpty())
            lpOutPacker->AddStr(lpMDBResultSet->GetStr("config_value_in"));
          else
            lpOutPacker->AddStr(lpInUnPacker->GetStrByIndex(i));
          lpMDBResultSet->Destroy();
        } 
        else
          lpOutPacker->AddStr(lpInUnPacker->GetStrByIndex(i));
      }
      else
        lpOutPacker->AddStr(lpInUnPacker->GetStrByIndex(i));
    }
    
    for(i = 0; i < lpInUnPacker->GetColCount(); i++)
    {
      if((lFlag & PMFLAG_ERROR_NO) && (strcmp(lpInUnPacker->GetColName(i), "error_no") == 0))
      {
        ierror_no = lpInUnPacker->GetInt("error_no");
        GetErrorInfo(lpContext,ierror_no,p_error_info);
        lpOutPacker->AddStr(p_error_info);
      }
    }
    
    for(tlFlag = 1; tlFlag <= lFlag; tlFlag *= 2)
    {
      if(lFlag & tlFlag)
      {
        psTableName = getTableName(tlFlag);
        psInFieldName = getInFieldName(tlFlag);
        if(psTableName && psInFieldName)
        {
          if(tlFlag == PMFLAG_BUSINESS_FLAG)
            hs_snprintf(psWhere,255,"p_key=%d",lpInUnPacker->GetInt(psInFieldName));
          else if(tlFlag == PMFLAG_STOCK_CODE)
            sprintf(psWhere,"p_key='%c%s'",lpInUnPacker->GetChar("exchange_type"),lpInUnPacker->GetStr("stock_code"));
          else
            hs_snprintf(psWhere,255,"p_key='%s'",lpInUnPacker->GetStr(psInFieldName));
          lpMDBResultSet = lpMDB->Query(iSession,psTableName,"*",psWhere);
          if(lpMDBResultSet)
          {
            if(!lpMDBResultSet->IsEmpty())
              lpOutPacker->AddStr(lpMDBResultSet->GetStr("p_prompt"));
            else if(tlFlag == PMFLAG_STOCK_CODE)
              lpOutPacker->AddStr(lpInUnPacker->GetStr("stock_code"));
            else
              lpOutPacker->AddStr("未知");
            lpMDBResultSet->Destroy();
          }
          else if(tlFlag == PMFLAG_STOCK_CODE)
            lpOutPacker->AddStr(lpInUnPacker->GetStr("stock_code"));
          else
            lpOutPacker->AddStr("未知");
        }
        else
          lpOutPacker->AddStr("");
      }
    }
    lpInUnPacker->Next();
  }

//  lpMDB->freeSession(iSession);
  return 0;
}

///周边取外部错误代码
int getExternErrorXml(IAS2Context * lpContext,const int lFunctionId,const int lErrorId)
{
  IF2XmlFIleGetService * lpXmlFileGet = NULL;
  lpContext->QueryInterface(SID_SVR_XMLFILEGET,(IKnown **)&lpXmlFileGet);
  char ls_ErrorSort[2] = {0};
  char ls_ErrorSource[9] = {0};
  char ls_ErrorNo[9] = {0};
  int iRet = 0;

  hs_strcpy(ls_ErrorSort,"1");
  hs_snprintf(ls_ErrorSource,8,"%d",lFunctionId);
  hs_snprintf(ls_ErrorNo,8,"%d",lErrorId);
  
  //取缺省连接
  int  iErrorNo = 0;
  
  if (lpXmlFileGet)
  {
  	  iRet = lpXmlFileGet->pf_GetExternError(ls_ErrorSort,ls_ErrorSource,ls_ErrorNo,&iErrorNo);
	  if (iRet < 0)
		  goto svr_end;
  }
  else
  {
  	  iRet = -1;
	  goto svr_end;
  }
   
  if (iErrorNo == 0)
  {
      iErrorNo = lErrorId;
  }

svr_end:
  if (iRet < 0)
  {
     if (lFunctionId == 304 || lFunctionId == 303)
  	     iErrorNo = -54;
  	 else
  	  	 iErrorNo = -61;
  }
  
  return iErrorNo;
}

///使用内存数据库对银行的错误号进行转换
int getBankErrorXml(IAS2Context * lpContext,const int lErrorId)
{
  IF2XmlFIleGetService * lpXmlFileGet = NULL;
  lpContext->QueryInterface(SID_SVR_XMLFILEGET,(IKnown **)&lpXmlFileGet);
     
  char ls_ErrorSort[2] = {0};
  char ls_ErrorSource[9] = {0};
  char ls_ErrorNo[9] = {0};
  int iRet = 0;

  hs_strcpy(ls_ErrorSort,"3");
  hs_strcpy(ls_ErrorSource,"0");
  hs_snprintf(ls_ErrorNo,8,"%d",lErrorId);
  
  //取缺省连接
  int iErrorNo = 0;
  
  if (lpXmlFileGet)
  {
  	  iRet = lpXmlFileGet->pf_GetExternError(ls_ErrorSort,ls_ErrorSource,ls_ErrorNo,&iErrorNo);
      if (iRet < 0)
		  goto svr_end;
  }
  else
  {
  	  iRet = -1;
	  goto svr_end;
  }
   
  if (iErrorNo == 0)
  {
      iErrorNo = lErrorId;
  }
  
svr_end: 
  if (iRet < 0)
     iErrorNo = 6000;

  return iErrorNo;
}

//zhangly 20051024 增加 业务复核所用函数-------------------------------------
//检查一条规则是否??
bool CheckRule(char rule_type,char * rule_value,char rule_op,char * check_value)
{
  bool bRet = false;
  switch (rule_op)
  {
    case '0': //大于等于
    {
       if ( rule_type == 'F' )
       {
          if ( fabs(atof(check_value)) >= atof(rule_value) )
          	 bRet = true;
       }
       else if ( rule_type == 'I' )
       {
          if ( abs(atoi(check_value)) >= atoi(rule_value) )
          	 bRet = true;
       }
       break; 
    }
    case '1'://小于等于
    {
       if ( rule_type == 'F' )
       {
          if ( fabs(atof(check_value)) <= atof(rule_value) ) 
          	 bRet = true;
       }
       else if ( rule_type == 'I' )
       {
          if ( abs(atoi(check_value)) <= atoi(rule_value) )
          	 bRet = true;
       }
       break; 
    }
    case '2'://包含于
    {
       if ( rule_type == 'S' )
       {
          if ( strstr(check_value,rule_value) != NULL )
          	 bRet = true;
       }
       break; 
    }
    case '3'://不包含于
    {
       if ( rule_type == 'S' )
       {
          if ( strstr(check_value,rule_value) == NULL )
          	bRet = true;      
       }
       break;           
    }
  }  
  return bRet;
}

//计算二条规则的逻辑值
bool RuleLogic(bool rule1,char rule_logic,bool rule2)
{
  bool bRet = true;
  switch (rule_logic)
  {
    case '1':bRet = rule1 && rule2;break;
    case '2':bRet = rule1 || rule2;break;
  }
  return bRet;
}

//调用复核规则检查函数
bool CheckAuditRule( char * rule1_field,char rule1_type,char * rule1_value,char rule1_op,char * check_value1,char rule1_logic,
                     char * rule2_field,char rule2_type,char * rule2_value,char rule2_op,char * check_value2,char rule2_logic,
                     char * rule3_field,char rule3_type,char * rule3_value,char rule3_op,char * check_value3 )
{
  bool bRet = true;
  //规则1是否要检查    
  if ( strcmp(rule1_field,"*") == 0)
  {
     bRet = true; //规则2不需要检查，无条件触发
  }
  else
  {
    //检查规则1?欠衤?
    bool r1 = CheckRule(rule1_type,rule1_value,rule1_op,check_value1);
    //下个规则是否要检查
    if ( strcmp(rule2_field,"*") == 0)
    {
      bRet = r1; //规则2不需要检查，返回规则1结果
    }
    else
    {
      //检查规则2是否满足
      bool r2 = CheckRule(rule2_type,rule2_value,rule2_op,check_value2);
      //取规则1和规则2进行逻辑运算结果 tmp
      bool tmp = RuleLogic(r1,rule1_logic,r2);
      //下个规则是否要检查
      if ( strcmp(rule3_field,"*") == 0)
      {
        bRet = tmp; //规则3不需要检查，返回（规则1,2）运算结果
      }
      else
      {
        //检查规则3是否满足
        bool r3 = CheckRule(rule3_type,rule3_value,rule3_op,check_value3);
        //取规则3和（规则1,2）进行逻辑运算的结果
        tmp = RuleLogic(tmp,rule2_logic,r3);
        bRet = tmp;
      }
    }   
  }
  return bRet;
}

//取复核检查字段值
char * GetAuditCheckValue(char * sFieldName,IF2UnPacker * lpInUnPacker,IF2UnPacker * lpInUnPackerParent,char * amount_value,char *balance_value)
{
  char * sRet = NULL;
  char sRealName[64] ={0};
  if ( strcmp(sFieldName,"*") == 0) //表示不需要检查
  {
     sRet = ""; 
  }
  else if (sFieldName[0] == '1')  //表示使用汇总字段
  {
     if ( strcmp(sFieldName,"1balance") == 0) //表示取发生额
     {
        sRet = balance_value; 
     }else if ( strcmp(sFieldName,"1amount") == 0 )  //表示取发生量
     {
      	sRet = amount_value; 
     }    
  }
  else if (sFieldName[0] == '2') //表示使用预处理字段
  {
     strcpy(sRealName,&sFieldName[1]); 
     sRet =(char *)lpInUnPacker->GetStr(sRealName);
  }
  else  //表示使用请求中的参数
  {
     sRet = (char *)lpInUnPackerParent->GetStr(sFieldName);
  }
  
  if (sRet)
     return sRet ;
  else
     return "";
}

bool CheckOPRolesStr(char * src,char * RolesStr)
{
  bool bRet = false;
  //从src中分离以逗号分开的角色代码
  int iRolesLen = strlen(RolesStr);
  int iLen = strlen(src);
  int iPos = 0;
  char * lpBegin = src;
  while ( iPos<iLen )
  {
    if ( src[iPos] == ',' )
    {
      //查找当一个角色号对应位在 RolesStr 中是否为'1'
      src[iPos] = '\0';
      int iRoleID = atoi(lpBegin);
      if ( (iRoleID - 1) < iRolesLen)
      {
        if  (RolesStr[iRoleID - 1] == '1')
        {
          bRet = true;
          break;
        }
      } 
      lpBegin = src+iPos+1; //指向下一个      
    }
    iPos++;
  }

  return bRet;
}

//zhangly 20051024 增加 业务复核所用函数  end-------------------------------------

//20060219 wangjz 增加银行密码处理，同注意有公用过程相关函数同步
char* hs_EncodeBkPwd(const char *bk_password, char *password_out)
{
  return lib_hs_EncodeBkPwd(bk_password, password_out);
}

char* hs_DecodeBkPwd(const char *bk_password, char *password_out)
{
  return lib_hs_DecodeBkPwd(bk_password, password_out);
}

//20060331 wangjz 增加
//取字符串第 byPart 部分, byPart >= 1
void GetPart(const char *Buf, char cDelimiter, int byPart, char *pValue)
{
  char s_str[8192]={0};
  char *ptr, *ptr1;
  int i;
  
  pValue[0] = '\0';
  ptr = NULL;
  strncpy(s_str, Buf, length(Buf));

  ptr  = s_str;
  ptr1 = ptr + instr(ptr, cDelimiter)-1;
  
  if ( (byPart > 1) && (isnull(ptr1) != 0) )
  for (i=2; i<=byPart; i++)
  {
    ptr = ptr1 + 1;
    ptr1= ptr + instr(ptr, cDelimiter)-1;
    if (isnull(ptr1) == 0)
      break;
  }

  if (isnull(ptr1) != 0)
    if (ptr1 > ptr)
      strncpy(pValue, ptr, ptr1 - ptr);
      
}


//20060701 wangjz add
//取间隔时间，以秒为单位
int GetIntervalSec(int HsTimePre, int HsTimeNext)
{
  int iIntervalSec = ((HsTimeNext / 10000) * 3600 + (HsTimeNext % 10000 / 100) * 60 + (HsTimeNext % 100)) -
                     ((HsTimePre / 10000) * 3600 + (HsTimePre % 10000 / 100) * 60 + (HsTimePre % 100));

  if (iIntervalSec < 0)
    iIntervalSec += 24 * 3600;      
      
  return iIntervalSec;
}

//20070118 weiye add
//期货代理客户解密
char* DecodeFuPwd(char *lPassword, const char *EncodePwd)
{  
   return lib_DecodeFuPwd(lPassword, EncodePwd);
}

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
char *Decrypt(char *pDecLiscense,const char *pLiscense,unsigned dwKey)
{
  return lib_Decrypt(pDecLiscense, pLiscense, dwKey);
}
/*==========================================================
 * Function   : CheckLiscense
 * Description: 对传入的Liscense有效性及是否过期进行校验
 * Input      : IASContext *pContext 链接数据库使用
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
int CheckLiscense(IAS2Context *lpContext,const char *pLiscense,char *pProductID,char *pOtherCompany,int iTimeMin,char *pErrorMsg)
{
   return lib_CheckLiscense(lpContext, pLiscense, pProductID, pOtherCompany, iTimeMin, pErrorMsg); 
}

/*==========================================================
 * Function   : GetCompanyName
 * Description: 用于取sysarg中的证券公司名称
 * Input      : IASContext *lpContext 链接数据库使用
 *              char *pStkCompany 证券公司名称
 * Output     : 
 * Return     : true 成功
 *              false 失败
 * Author     : wanglb,zhouwm
 * Date       : 2008/09/12
 ==========================================================*/
//把从数据库获取改成从内存数据库获取
bool GetCompanyName(IAS2Context * lpContext,char *pStkCompany)
{
   return lib_GetCompanyName( lpContext, pStkCompany);
}
//20080912 王力波,周伟明 以下为新增用于第三方授权操作解密及校验的函数，周伟明对函数进行调整 end.


/*==========================================================
 * Function   : GetSecuAssetPrice
 * Description: 取证券市值价
 * Input      : IAS2Context  lpContext	上下文
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
double GetSecuAssetPrice(IAS2Context *lpContext,char * szSecuExchType,char * szStockCode,char * szStockType,int iStoreUnit,char cAssetFlag)
{
   IF2UDPRecService * lpUDPRecSvr = NULL;
   if (!lpUDPRecSvr)
      lpContext->QueryInterface(SID_SVR_CAEUDPREC,(IKnown **)&lpUDPRecSvr);
   
   if (lpUDPRecSvr)
   {
   	  return lpUDPRecSvr->pf_GetSecuAssetPrice(szSecuExchType,szStockCode,szStockType,iStoreUnit,cAssetFlag);
   }
   else
   {
   	  return 0.000;
   }
}

/*==========================================================
 * Function   : GetSecuLastPrice
 * Description: 取证券最新价
 * Input      : IAS2Context  lpContext	上下文
 *              char * szSecuExchType   交易类别
 *              char * szStockCode      证券代码
 *              char * szStockType      证券类别
 * Output     : Last_Price             最新价
 * Return     : >=0		    成功
 *				<0          失败 		
 * Author     : zhouwm
 * Date       : 2008/12/03.
 ==========================================================*/
double GetSecuLastPrice(IAS2Context *lpContext,char * szSecuExchType,char * szStockCode,char * szStockType)
{
   IF2UDPRecService * lpUDPRecSvr = NULL;
   if (!lpUDPRecSvr)
      lpContext->QueryInterface(SID_SVR_CAEUDPREC,(IKnown **)&lpUDPRecSvr);
   
   if (lpUDPRecSvr)
   {
   	  return lpUDPRecSvr->pf_GetSecuLastPrice(szSecuExchType,szStockCode,szStockType);
   }
   else
   {
   	  return 0.000;
   }
}


/*==========================================================
 * Function   : GetDebtInterest
 * Description: 取国债利息
 * Input      : IAS2Context  lpContext	上下文
 *              char * szSecuExchType   交易类别
 *              char * szStockCode      证券代码
 *              char * szStockType      证券类别(允许为空)
 * Output     : Debt_Interest           最新价
 * Return     : >=0		    成功
 *				<0          失败 		
 * Author     : zhouwm
 * Date       : 2008/12/03.
 ==========================================================*/
double GetSecuDebtInterest(IAS2Context *lpContext,char * szSecuExchType,char * szStockCode,char * szStockType)
{
   IF2UDPRecService * lpUDPRecSvr = NULL;
   if (!lpUDPRecSvr)
      lpContext->QueryInterface(SID_SVR_CAEUDPREC,(IKnown **)&lpUDPRecSvr);
   
   if (lpUDPRecSvr)
   {
   	  return lpUDPRecSvr->pf_GetSecuDebtInterest(szSecuExchType,szStockCode,szStockType);
   }
   else
   {
   	  return 0.000;
   }
}

/*==========================================================
 * Function   : GetSecuCode
 * Description: 取证券代码信息
 * Input      : IAS2Context*  lpContext        上下文
 *              IF2UnPacker * lpInUnPacker     请求包
 *              IF2Packer *   lpOutPacker      应答包
 * Output     : 
 * Return     : >=0		    成功
 *				<0          失败 		
 * Author     : zhouwm
 * Date       : 2009/05/12.
 ==========================================================*/
int GetSecuCode(IAS2Context* lpContext,IF2UnPacker * lpInUnPacker,IF2Packer * lpOutPacker)
{
   IF2UDPRecService * lpUDPRecSvr = NULL;
   
   lpContext->QueryInterface(SID_SVR_CAEUDPREC,(IKnown **)&lpUDPRecSvr);
   
   if (lpUDPRecSvr)
   {
   	  return lpUDPRecSvr->pf_GetSecuCode(lpContext,lpInUnPacker,lpOutPacker);
   }
   else
   {
   	  return 0;
   }
}

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
int GetSecuCodePrice(IAS2Context* lpContext,IF2UnPacker * lpInUnPacker,IF2Packer * lpOutPacker)
{
   IF2UDPRecService * lpUDPRecSvr = NULL;
   
   lpContext->QueryInterface(SID_SVR_CAEUDPREC,(IKnown **)&lpUDPRecSvr);
   
   if (lpUDPRecSvr)
   {
   	  return lpUDPRecSvr->pf_GetSecuCodePrice(lpContext,lpInUnPacker,lpOutPacker);
   }
   else
   {
   	  return 0;
   }
}

///begin 20110729 刘元召 add, 增加一个输出函数GetCaeCodePrice，相比GetSecuCodePrice多增加五档行情价格信息的返回
/*==========================================================
 * Function   : GetCaeCodePrice
 * Description: 取证券代码信息＋最新价＋市值价+五档行情信息
 * Input      : IAS2Context*  lpContext        上下文
 *              IF2UnPacker * lpInUnPacker     请求包
 *              IF2Packer *   lpOutPacker      应答包
 * Output     : 
 * Return     : >=0		    成功
 *				      <0          失败 		
 * Author     : liuyz
 * Date       : 2010/07/29.
 ==========================================================*/
int GetCaeCodePrice(IAS2Context* lpContext,IF2UnPacker * lpInUnPacker,IF2Packer * lpOutPacker)
{
   IF2UDPRecService * lpUDPRecSvr = NULL;
   
   lpContext->QueryInterface(SID_SVR_CAEUDPREC,(IKnown **)&lpUDPRecSvr);
   
   if (lpUDPRecSvr)
   {
   	  return lpUDPRecSvr->pf_GetCaeCodePrice(lpContext,lpInUnPacker,lpOutPacker);
   }
   else
   {
   	  return 0;
   }
}
///end 20110729 刘元召 add, 增加一个输出函数GetCaeCodePrice，相比GetSecuCodePrice多增加五档行情价格信息的返回

/*==========================================================
 * Function   : GetUserToken
 * Description: 用户令牌获取
 * Input      : IAS2Context  lpContext	    上下文
 *              cosnt int iInitDate         系统初始化日期
 *              const char cCertType        身份类别
 *              const char * sCertAccount   身份帐号
 *              const char cPasswordType    密码类别
 *              const char * sPassword      密码
 *              const char   cPasswordCheck 密码校验
 * Output     : char *sUserToken            令牌
 * Return     : >=0		    成功
 *				<0          失败 		
 * Author     : zhouwm
 * Date       : 2008/12/03.
 ==========================================================*/
int GetUserToken(IAS2Context *lpContext,char *sUserToken, const int iInitDate, const char cCertType,const char * sCertAccount,const char cPasswordType,const char * sPassword,const char cPasswordCheck)
{
   IF2UserAuthService * lpUserAuthSvr = NULL;
   
   lpContext->QueryInterface(SID_SVR_USERAUTH,(IKnown **)&lpUserAuthSvr);
   
   if (lpUserAuthSvr)
   {
   	  return lpUserAuthSvr->pf_GetUserToken(sUserToken,iInitDate,cCertType,sCertAccount,cPasswordType,sPassword,cPasswordCheck);
   }
   else
   {
   	  return -1;
   }
}


/*==========================================================
 * Function   : CheckUserToken
 * Description: 用户令牌校验
 * Input      : IAS2Context  lpContext	    上下文
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
int CheckUserToken(IAS2Context *lpContext,char *sUserToken,const int iInitDate, const char cCertType,const char * sCertAccount,const char cPasswordType,const char * sPassword)
{
   IF2UserAuthService * lpUserAuthSvr = NULL;
   
   lpContext->QueryInterface(SID_SVR_USERAUTH,(IKnown **)&lpUserAuthSvr);
   
   if (lpUserAuthSvr)
   {
   	  return lpUserAuthSvr->pf_CheckUserToken(lpContext,sUserToken,iInitDate,cCertType,sCertAccount,cPasswordType,sPassword);
   }
   else
   {
   	  return -1;
   }
}


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
int GetFileBuffer(IAS2Context *lpContext,IRCfgObj *pCfgObj,char * sBuf,char *sLocation)
{
   ICfgSvr * lpCfgSvr = NULL;
   
   lpContext->QueryInterface(SID_CFGSVR,(IKnown **)&lpCfgSvr);
   
   if (lpCfgSvr)
   {
      ICfgObjMaker * lpCfgObjMaker = lpCfgSvr->GetCfgObjMaker();
      
      if (lpCfgObjMaker)
      {
          pCfgObj = lpCfgObjMaker->LoadFromBuf((void *)sBuf,length(sBuf),sLocation);
          if (!pCfgObj)
             return -1;
      }
      else
      {
         return -1;
      }
   }
   else
   {
      return -1;
   }
   return 0;
}

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
int SaveFileBuffer(IAS2Context *lpContext,IWCfgObj *pWCfgObj,char* sBuf)
{
   void * lpBuf;
   long iBufSize=0;

   ICfgSvr * lpCfgSvr = NULL;
   
   lpContext->QueryInterface(SID_CFGSVR,(IKnown **)&lpCfgSvr);
   
   if (lpCfgSvr)
   {
      ICfgObjMaker * lpCfgObjMaker = lpCfgSvr->GetCfgObjMaker();
      IRCfgObj * lpRCfgObj = NULL;
      pWCfgObj->QueryInterface(SID_RCFGOBJ,(IKnown **)&lpRCfgObj);
      
      if ((lpCfgObjMaker)&&(lpRCfgObj))
      {
          if(lpCfgObjMaker->SaveToBuf(lpRCfgObj,(void **)&lpBuf,&iBufSize)>=0)
          {
            hs_strncpy(sBuf,(char*)lpBuf,iBufSize);
            free(lpBuf);            
            return 0;
          }
          else
          {
            return -1;
          }
      }
      else
      {
         return -1;
      }
   }
   else
   {
      return -1;
   }
   return 0;
}

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
int GetNewWCfgObj(IAS2Context *lpContext,IWCfgObj *pCfgObj,char *sLocation)
{
   ICfgSvr * lpCfgSvr = NULL;
   
   lpContext->QueryInterface(SID_CFGSVR,(IKnown **)&lpCfgSvr);
   
   if (lpCfgSvr)
   {
      ICfgObjMaker * lpCfgObjMaker = lpCfgSvr->GetCfgObjMaker();
      
      if (lpCfgObjMaker)
      {
         pCfgObj=lpCfgObjMaker->MakeObject(sLocation);      
         if (!pCfgObj)
         {
          return -1;
         }
      }
      else
      {
        return -1;
      }
   }
   else
   {
      return -1;
   }
   return 0;
}

/*==========================================================
 * Function   : CheckAccessLicense
 * Description: 接入许可校验
 * Input      : IAS2Context  lpContext          上下文
 * Output     : 
 * Return     : =0          成功
 *              >0          失败 
 * Author     : lilb
 * Date       : 2009/02/13
 ==========================================================*/
int CheckAccessLicense(IAS2Context *lpContext)
{
   CAccessAuthSvr * lpAccessAuthSvr = NULL;
   
   lpContext->QueryInterface(SID_SVR_ACCESSAUTH,(IKnown **)&lpAccessAuthSvr);

   if (lpAccessAuthSvr)
   {
      IESBMessage * lpMessage=lpContext->GetOrgRequest();
      int iLicenseNo=lpMessage->GetItem(TAG_INTERNAL_LICENSE_NO)->GetInt();
      int iFunctionNo=lpMessage->GetItem(TAG_FUNCTION_ID)->GetInt();
      return lpAccessAuthSvr->pf_CheckAccessLicense(lpContext, iLicenseNo, iFunctionNo);
   }
   else
   {
      return ERR_EXT_SYS_LIC_LOAD_FAIL;
   }
   
}


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

int EncodeTwoWord(char *pIn, char *pOut)
{
	return lib_EncodeTwoWord( pIn,  pOut);
}

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
int DecodeTwoWord(char *pIn, char *pOut)
{
	return lib_DecodeTwoWord(pIn, pOut);
}

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
int EtfToStruct(IAS2Context * lpContext,S_ETFCOMPONENT *pEtfComponent,char *sMdbTable,char *sWhere,int * iErrorNo,char * sErrorInfo,char *sErrorPathInfo)
{
   int iReturnCode = 0;
   int i = 0,j = 0;
   int li_count = 0;
   
   char * p_table_name = sMdbTable;
   char * p_where_str = sWhere;
   
   //trim(p_where_str);
   
   IF2ResultSet * lpMDBResultSet = NULL;
   IMdbService * lpMDB = NULL;
   
   lpContext->QueryInterface(SID_MDB,(IKnown **)&lpMDB);

   if (lpMDB)
   {   
      int iSession = lpContext->GetMDBSession();
      if (iSession >= 0)
      {
         
         lpMDBResultSet = lpMDB->Query(iSession, p_table_name, "*", p_where_str);
         
         if (lpMDBResultSet)
         {
            while (!lpMDBResultSet->IsEOF())
            {
               li_count = lpMDBResultSet->GetColCount();
               for (i = 0;i<li_count;i++)
               {
                 //获取记录字段值
                 //ETF成份股代码
                 if (hs_strcmp(lpMDBResultSet->GetColName(i),"component_code") == 0)
                 	hs_strcpy(pEtfComponent[j].p_component_code,lpMDBResultSet->GetStrByIndex(i));
                 //ETF成份股代码名称
                 else if (hs_strcmp(lpMDBResultSet->GetColName(i),"component_name") == 0)
                 {
                    hs_strcpy(pEtfComponent[j].p_component_name,lpMDBResultSet->GetStrByIndex(i));
                    if (isnull(trim(pEtfComponent[j].p_component_name)) == 0)
                       hs_strcpy(pEtfComponent[j].p_component_name,pEtfComponent[j].p_component_code);
                 }
                 //替代标志
                 else if (hs_strcmp(lpMDBResultSet->GetColName(i),"replace_flag") == 0)
                    pEtfComponent[j].p_replace_flag = lpMDBResultSet->GetCharByIndex(i);
                 //溢价比率
                 else if (hs_strcmp(lpMDBResultSet->GetColName(i),"replace_ratio") == 0)
                    pEtfComponent[j].p_replace_ratio = lpMDBResultSet->GetDoubleByIndex(i);
                 //替代金额
                 else if (hs_strcmp(lpMDBResultSet->GetColName(i),"replace_balance") == 0)
                    pEtfComponent[j].p_replace_balance = lpMDBResultSet->GetDoubleByIndex(i);
                 //成份股数量
                 else if (hs_strcmp(lpMDBResultSet->GetColName(i),"component_amount") == 0)
                    pEtfComponent[j].p_component_amount = lpMDBResultSet->GetDoubleByIndex(i);
                 //20100121 zhouwm 增加字段输出redeem_replace_balance和secu_market_code begin 
                 //赎回替代金额
                 else if (hs_strcmp(lpMDBResultSet->GetColName(i),"redeem_replace_balance") == 0)
                    pEtfComponent[j].p_redeem_replace_balance = lpMDBResultSet->GetDoubleByIndex(i);
                 //证券挂牌市场
                 else if (hs_strcmp(lpMDBResultSet->GetColName(i),"secu_market_code") == 0)
                 	hs_strcpy(pEtfComponent[j].p_secu_market_code,lpMDBResultSet->GetStrByIndex(i));
                 //20100121 zhouwm 增加字段输出redeem_replace_balance和secu_market_code end
               }
               
               j = j + 1;
               lpMDBResultSet->Next();
            }
            iReturnCode = j;
         }
         else
         {
 
            *iErrorNo = ERR_QUERYMEMORYTABLE_ERROR;
            hs_snprintf(sErrorInfo,500,"查询内存数据库错误[内存表: '%s'][字段: *][条件: '%s']",p_table_name,p_where_str);
            hs_strncat(sErrorPathInfo," -> EtfToStruct()",500);
            iReturnCode = -1;
            goto svr_end;
         }
         
      }
      else
      {
          *iErrorNo = ERR_GETMEMORYSERVICESESSIONERROR;
          hs_strcpy(sErrorInfo,"取内存服务session错误");
          hs_strncat(sErrorPathInfo," -> EtfToStruct()",500);
          iReturnCode = -1;
          
          goto svr_end;
      }
   }
   else
   {
      *iErrorNo = ERR_GETMEMORYDATASESSIONFAIL;
      hs_strcpy(sErrorInfo,"取内存数据服务错误");
      hs_strncat(sErrorPathInfo," -> EtfToStruct()",500);
      iReturnCode = -1;
      
   }
   
   goto svr_end;
svr_end:
   if (lpMDBResultSet)
      lpMDBResultSet->Destroy();  //释放结果集对象
   
   return iReturnCode; 
}

/*==========================================================
 * Function   : EtfResultUnion
 * Description: 根据数组的成分代码修改ETF成分股信息结构数组中对应的成分代码数量数据
 * Input      :  S_ETFCOMPONENT **pEtfComponent        成份股结构数组
 *            :  const int      iArrayLen              结构长度
 *            :  const int      iListLen              结构长度
 *            :  char           sComponentCode[][7]    成份股代码
 *            :  double         dEnableAmount[]        可用数量
 *            :  double         dIssueAmount[]         可申购赎回数量
 * Return     :  =0          成功
 *               <>0         失败 
 * Author     : zhouwm
 * Date       : 2009/05/06
 ==========================================================*/
int EtfResultUnion(S_ETFCOMPONENT *pEtfComponent,const int iArrayLen,const int iListLen,char sComponentCode[][7],double dEnableAmount[],double dIssueAmount[])
{
   int iPos = 0,i = 0;
   
   while ((isnull(trim(sComponentCode[i])) != 0) && (i < iListLen))
   {
   	  //查找成份股代码，如果找到则修改修改结构数组中的成员数量
   	  iPos = ResultSearch(pEtfComponent,iArrayLen,sComponentCode[i]);
   	  if (iPos >= 0)
   	  {
   	  	 pEtfComponent[iPos].p_enable_amount = dEnableAmount[i];
   	  	 pEtfComponent[iPos].p_issue_amount = dIssueAmount[i];
   	  }
   	  i++;
   }
   return 0;
}

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
int ResultSearch(S_ETFCOMPONENT *pEtfComponent,const int iArrayLen,const char *sComponentCode)
{
   int iLeft = 0, iRight = 0, iMiddle = 0;
   // 二分查找
   for (iLeft = 0, iRight = iArrayLen - 1; iLeft <= iRight;)
   {
      iMiddle = iLeft+(iRight-iLeft) / 2;
      if (isnull(trim(pEtfComponent[iMiddle].p_component_code)) == 0)
      {
         iRight = iMiddle - 1;
      }
      else if (strcmp(pEtfComponent[iMiddle].p_component_code, sComponentCode) < 0)
      {
         iLeft = iMiddle + 1;
      }
      else if (strcmp(pEtfComponent[iMiddle].p_component_code, sComponentCode) > 0)
      {
         iRight = iMiddle - 1;
      }
      else
      {
         return  iMiddle;
      }
   }
   
   return -1;
}

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
char *DecryptHsLicense(char *pDecLiscense,const char *pLiscense,int usKey)
{
  return lib_DecryptHsLicense(pDecLiscense, pLiscense, usKey);
}

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
char * EncryptHsLicense(char *pEncLiscense,const char *pLiscense,unsigned short usKey)
{
 return lib_EncryptHsLicense(pEncLiscense, pLiscense, usKey);
}

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
char * ProfessionCode2Hs6(const char *sz_src,char *sz_dest)
{
  if(isnull(sz_src) == 0)
    return NULL;
    
  memset(sz_dest,'\0',sizeof(sz_dest));
  if (length(sz_src) > 1)
    strcpy(sz_dest,sz_src+1);
  else
  	strcpy(sz_dest,sz_src);
  	
  return sz_dest;
}

/*==========================================================
 * Function   : Nationality2Hs6
 * Description: 用于把08国籍地区代码转换为06版
 * Input      : char *sz_src 源字符串
 * Output     : char 转换后的06版国籍地区代码
 * Return     : char 
 * Author     : yangsb
 * Date       : 2009/06/01
 ==========================================================*/
char Nationality2Hs6(const char *sz_src)
{
  char cNational  = '0';
  
  if(isnull(sz_src) == 0)
    return '0';

  if ( strcmp(sz_src, CNST_NATIONALITY_USA) == 0 )
    cNational = '1';
  else
    cNational = '0';
    
  return cNational;
}

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
int CheckSystemLicense(IAS2Context *lpContext,int & nBranchCnt, int & nClientCnt, int & nValidDate)
{
   CAccessAuthSvr * lpAccessAuthSvr = NULL;
   
   lpContext->QueryInterface(SID_SVR_ACCESSAUTH,(IKnown **)&lpAccessAuthSvr);

   if (lpAccessAuthSvr)
   {
      return lpAccessAuthSvr->pf_CheckSystemLicense(lpContext, nBranchCnt, nClientCnt, nValidDate);
   }
   else
   {
      return ERR_EXT_SYS_LIC_LOAD_FAIL;
   }  
}

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
void BFEncode(void *lpOut, const void *lpIn, int nLength, const void *lpKey)
{
	BlowfishEncode(lpOut, lpIn, nLength, lpKey);
}

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
void BFDecode(void *lpOut, const void *lpIn, int nLength, const void *lpKey)
{
	BlowfishDecode(lpOut, lpIn, nLength, lpKey);
}

/*==========================================================
* Function   : HsPwdEncode
* Description: 加密密码
* Input      : const char *pIn 输入的密码串
*              char *pOut 输出的加密后的密码。
* Return     : 0: 成功，其他失败。
* Author     : wangry
* Date       : 2010/03/03
==========================================================*/
int HsPwdEncode(const char *pIn, char *pOut)
{
	return lib_HsPwdEncode(pIn, pOut);
}

/*==========================================================
* Function   : HsPwdDecode
* Description: 密码解密
* Input      : const char *pIn 输入的加密的密码串
*              char *pOut 输出的解密后的密码。
* Return     : 0: 成功，其他失败。
* Author     : wangry
* Date       : 2010/03/03
==========================================================*/
int HsPwdDecode(const char *pIn, char *pOut)
{
	return lib_HsPwdDecode(pIn, pOut);
}
