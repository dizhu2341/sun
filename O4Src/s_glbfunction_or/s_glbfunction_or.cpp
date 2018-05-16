/*
 * Program: s_glbfunction_or.cpp
 * Author : zhouwm.
 * Date   : 2008/10/14.
 * Notes  : �ṩϵͳ��������
 * Modify : �汾       �޸�����  ������  �޸���   �޸ĵ�          �޸�˵��
 *          V8.0.6.1   20110729          ��Ԫ��   20110728043     ����һ���������GetCaeCodePrice�����GetSecuCodePrice�������嵵����۸���Ϣ�ķ���
 *      		V8.0.6.0   20100614          ��Ԫ��   �ڲ�            ����ҵ����Ӫƽ̨V2.0��Ŀ2011���߽���
   					V8.0.5.4   20110315  �����  �����  	20110308021			security.a�䶯������±���
 * 					V8.0.5.3   20110303  ������  ������  	20110301024			�����ܺͽ�����صķŵ�license_security��̬���С�����������ܺͽ��ܺ�����
 *          V8.0.5.2   20110222  �����  �����  	20101228018  		Ϊ������չ�����ȡ�����
 * 					V8.0.5.1   20110215  ������  ������  	20110216030			Ϊͳһ��������Blowfish���ܺͽ��ܣ����޸�s_glbfunction_or.gcc�ļ�����̬����libsecurity.a��
 *          V8.0.5.0   20100414  ��ΰ��  ��ΰ��   �ڲ�            ����
 *          V8.0.4.1   20100121  ��  ��  ��ΰ��   JJYWYYPT-5421   EtfToStruct()�����ֶ����redeem_replace_balance��secu_market_code begin
 *          V8.0.4.0   20090926  ��ΰ��  ��ΰ��   �ڲ�            ����
 *          V8.0.3.0   20090626  ��ΰ��  ��ΰ��   �ڲ�            ���
 *          V8.0.2.0   20090420  ��ΰ��  ��ΰ��   �ڲ�            ���
 *          V8.0.1.0   20090120  ��ΰ��  ��ΰ��   �ڲ�            ���
 */

#include "hshead.h"

/*==========================================================
 * Function   : GetLibVersion
 * Description: ��ȡ�汾��Ϣ
 * Input      : 
 * Output     : 
 * Return     : so�汾��Ϣ
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

/*ȡ�ڴ��������Ϣ*/
int GetMdbData(IAS2Context * lpContext, IF2UnPacker * lpInUnPacker, IF2Packer * lpOutPacker,int * iErrorNo,char * sErrorInfo,char *sErrorPathInfo)
{
   return lib_GetMdbData(lpContext, lpInUnPacker, lpOutPacker, iErrorNo, sErrorInfo, sErrorPathInfo); 
}

/*�ڴ������ͬ��*/
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
            hs_snprintf(sErrorInfo,500,"ͬ���ڴ����ݿ��ʧ��[�ڴ��: %s][����: %s][%d]",p_table_name,p_where_str,iReturnCode);
            hs_strncat(sErrorPathInfo," -> SyncMdbData()->Sync()",500);
            iReturnCode = p_error_no;
         }
      }
      else
      {
          p_error_no = ERR_SYNCMDBTABLE_FIAL;
          hs_snprintf(sErrorInfo,500,"ͬ���ڴ����ݿ��ʧ��[�ڴ��: %s][����: %s]",p_table_name,p_where_str);
          hs_strncat(sErrorPathInfo," -> SyncMdbData()->GetMDBSession()",500);
          iReturnCode = p_error_no;
          
          goto svr_end;
      }
   }
   else
   {
      p_error_no = ERR_GETMEMORYDATASESSIONFAIL;
      hs_strcpy(sErrorInfo,"ȡ�ڴ����ݷ������");
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

//ȡ������Ϣ
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
  
  //����ز���ȡ��
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

//ȡ������Ϣ,����������ԭ���Ĵ�����Ϣ�����ں���
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
     hs_strcpy(p_sErrorInfo,"����ϵͳ����");

  return p_sErrorInfo;
}

// ���������
int randomx(int iSeed)
{
  //srand( (unsigned)time( NULL ) );// ���Ͽ��ܻ��Щ
  return (rand() % iSeed);
}

// ���ܺ���
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

  //���ڴ����ݿ��쳣��ȡ������Ӧ���ݣ����������bank_no
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

  //ȡ���ݿ����    
  IMdbService * lpMDB = NULL;
  lpContext->QueryInterface(SID_MDB,(IKnown **)&lpMDB);
  //ȡȱʡ����
  int iSession = lpContext->GetMDBSession();

  if(!lFlag || (lpMDB == NULL) || (iSession < 0))//û���ֶ���Ҫ����,���޷������ڴ����ݿ�
  {
    PackResultSet(lpInUnPacker,lpOutPacker);
    return 0;
  }

  //�����ֶ���
  for(i = 0; i < lpInUnPacker->GetColCount(); i++)
    lpOutPacker->AddField(lpInUnPacker->GetColName(i));
  for(tlFlag = 1; tlFlag <= lFlag; tlFlag *= 2)
    if(lFlag & tlFlag)
      lpOutPacker->AddField(getOutFieldName(tlFlag));

  //��������
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
              lpOutPacker->AddStr("δ֪");
            lpMDBResultSet->Destroy();
          }
          else if(tlFlag == PMFLAG_STOCK_CODE)
            lpOutPacker->AddStr(lpInUnPacker->GetStr("stock_code"));
          else
            lpOutPacker->AddStr("δ֪");
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

///�ܱ�ȡ�ⲿ�������
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
  
  //ȡȱʡ����
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

///ʹ���ڴ����ݿ�����еĴ���Ž���ת��
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
  
  //ȡȱʡ����
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

//zhangly 20051024 ���� ҵ�񸴺����ú���-------------------------------------
//���һ�������Ƿ�?��?
bool CheckRule(char rule_type,char * rule_value,char rule_op,char * check_value)
{
  bool bRet = false;
  switch (rule_op)
  {
    case '0': //���ڵ���
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
    case '1'://С�ڵ���
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
    case '2'://������
    {
       if ( rule_type == 'S' )
       {
          if ( strstr(check_value,rule_value) != NULL )
          	 bRet = true;
       }
       break; 
    }
    case '3'://��������
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

//�������������߼�ֵ
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

//���ø��˹����麯��
bool CheckAuditRule( char * rule1_field,char rule1_type,char * rule1_value,char rule1_op,char * check_value1,char rule1_logic,
                     char * rule2_field,char rule2_type,char * rule2_value,char rule2_op,char * check_value2,char rule2_logic,
                     char * rule3_field,char rule3_type,char * rule3_value,char rule3_op,char * check_value3 )
{
  bool bRet = true;
  //����1�Ƿ�Ҫ���    
  if ( strcmp(rule1_field,"*") == 0)
  {
     bRet = true; //����2����Ҫ��飬����������
  }
  else
  {
    //������1?Ƿ����?
    bool r1 = CheckRule(rule1_type,rule1_value,rule1_op,check_value1);
    //�¸������Ƿ�Ҫ���
    if ( strcmp(rule2_field,"*") == 0)
    {
      bRet = r1; //����2����Ҫ��飬���ع���1���
    }
    else
    {
      //������2�Ƿ�����
      bool r2 = CheckRule(rule2_type,rule2_value,rule2_op,check_value2);
      //ȡ����1�͹���2�����߼������� tmp
      bool tmp = RuleLogic(r1,rule1_logic,r2);
      //�¸������Ƿ�Ҫ���
      if ( strcmp(rule3_field,"*") == 0)
      {
        bRet = tmp; //����3����Ҫ��飬���أ�����1,2��������
      }
      else
      {
        //������3�Ƿ�����
        bool r3 = CheckRule(rule3_type,rule3_value,rule3_op,check_value3);
        //ȡ����3�ͣ�����1,2�������߼�����Ľ��
        tmp = RuleLogic(tmp,rule2_logic,r3);
        bRet = tmp;
      }
    }   
  }
  return bRet;
}

//ȡ���˼���ֶ�ֵ
char * GetAuditCheckValue(char * sFieldName,IF2UnPacker * lpInUnPacker,IF2UnPacker * lpInUnPackerParent,char * amount_value,char *balance_value)
{
  char * sRet = NULL;
  char sRealName[64] ={0};
  if ( strcmp(sFieldName,"*") == 0) //��ʾ����Ҫ���
  {
     sRet = ""; 
  }
  else if (sFieldName[0] == '1')  //��ʾʹ�û����ֶ�
  {
     if ( strcmp(sFieldName,"1balance") == 0) //��ʾȡ������
     {
        sRet = balance_value; 
     }else if ( strcmp(sFieldName,"1amount") == 0 )  //��ʾȡ������
     {
      	sRet = amount_value; 
     }    
  }
  else if (sFieldName[0] == '2') //��ʾʹ��Ԥ�����ֶ�
  {
     strcpy(sRealName,&sFieldName[1]); 
     sRet =(char *)lpInUnPacker->GetStr(sRealName);
  }
  else  //��ʾʹ�������еĲ���
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
  //��src�з����Զ��ŷֿ��Ľ�ɫ����
  int iRolesLen = strlen(RolesStr);
  int iLen = strlen(src);
  int iPos = 0;
  char * lpBegin = src;
  while ( iPos<iLen )
  {
    if ( src[iPos] == ',' )
    {
      //���ҵ�һ����ɫ�Ŷ�Ӧλ�� RolesStr ���Ƿ�Ϊ'1'
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
      lpBegin = src+iPos+1; //ָ����һ��      
    }
    iPos++;
  }

  return bRet;
}

//zhangly 20051024 ���� ҵ�񸴺����ú���  end-------------------------------------

//20060219 wangjz �����������봦��ͬע���й��ù�����غ���ͬ��
char* hs_EncodeBkPwd(const char *bk_password, char *password_out)
{
  return lib_hs_EncodeBkPwd(bk_password, password_out);
}

char* hs_DecodeBkPwd(const char *bk_password, char *password_out)
{
  return lib_hs_DecodeBkPwd(bk_password, password_out);
}

//20060331 wangjz ����
//ȡ�ַ����� byPart ����, byPart >= 1
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
//ȡ���ʱ�䣬����Ϊ��λ
int GetIntervalSec(int HsTimePre, int HsTimeNext)
{
  int iIntervalSec = ((HsTimeNext / 10000) * 3600 + (HsTimeNext % 10000 / 100) * 60 + (HsTimeNext % 100)) -
                     ((HsTimePre / 10000) * 3600 + (HsTimePre % 10000 / 100) * 60 + (HsTimePre % 100));

  if (iIntervalSec < 0)
    iIntervalSec += 24 * 3600;      
      
  return iIntervalSec;
}

//20070118 weiye add
//�ڻ�����ͻ�����
char* DecodeFuPwd(char *lPassword, const char *EncodePwd)
{  
   return lib_DecodeFuPwd(lPassword, EncodePwd);
}

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
char *Decrypt(char *pDecLiscense,const char *pLiscense,unsigned dwKey)
{
  return lib_Decrypt(pDecLiscense, pLiscense, dwKey);
}
/*==========================================================
 * Function   : CheckLiscense
 * Description: �Դ����Liscense��Ч�Լ��Ƿ���ڽ���У��
 * Input      : IASContext *pContext �������ݿ�ʹ��
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
int CheckLiscense(IAS2Context *lpContext,const char *pLiscense,char *pProductID,char *pOtherCompany,int iTimeMin,char *pErrorMsg)
{
   return lib_CheckLiscense(lpContext, pLiscense, pProductID, pOtherCompany, iTimeMin, pErrorMsg); 
}

/*==========================================================
 * Function   : GetCompanyName
 * Description: ����ȡsysarg�е�֤ȯ��˾����
 * Input      : IASContext *lpContext �������ݿ�ʹ��
 *              char *pStkCompany ֤ȯ��˾����
 * Output     : 
 * Return     : true �ɹ�
 *              false ʧ��
 * Author     : wanglb,zhouwm
 * Date       : 2008/09/12
 ==========================================================*/
//�Ѵ����ݿ��ȡ�ĳɴ��ڴ����ݿ��ȡ
bool GetCompanyName(IAS2Context * lpContext,char *pStkCompany)
{
   return lib_GetCompanyName( lpContext, pStkCompany);
}
//20080912 ������,��ΰ�� ����Ϊ�������ڵ�������Ȩ�������ܼ�У��ĺ�������ΰ���Ժ������е��� end.


/*==========================================================
 * Function   : GetSecuAssetPrice
 * Description: ȡ֤ȯ��ֵ��
 * Input      : IAS2Context  lpContext	������
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
 * Description: ȡ֤ȯ���¼�
 * Input      : IAS2Context  lpContext	������
 *              char * szSecuExchType   �������
 *              char * szStockCode      ֤ȯ����
 *              char * szStockType      ֤ȯ���
 * Output     : Last_Price             ���¼�
 * Return     : >=0		    �ɹ�
 *				<0          ʧ�� 		
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
 * Description: ȡ��ծ��Ϣ
 * Input      : IAS2Context  lpContext	������
 *              char * szSecuExchType   �������
 *              char * szStockCode      ֤ȯ����
 *              char * szStockType      ֤ȯ���(����Ϊ��)
 * Output     : Debt_Interest           ���¼�
 * Return     : >=0		    �ɹ�
 *				<0          ʧ�� 		
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
 * Description: ȡ֤ȯ������Ϣ
 * Input      : IAS2Context*  lpContext        ������
 *              IF2UnPacker * lpInUnPacker     �����
 *              IF2Packer *   lpOutPacker      Ӧ���
 * Output     : 
 * Return     : >=0		    �ɹ�
 *				<0          ʧ�� 		
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

///begin 20110729 ��Ԫ�� add, ����һ���������GetCaeCodePrice�����GetSecuCodePrice�������嵵����۸���Ϣ�ķ���
/*==========================================================
 * Function   : GetCaeCodePrice
 * Description: ȡ֤ȯ������Ϣ�����¼ۣ���ֵ��+�嵵������Ϣ
 * Input      : IAS2Context*  lpContext        ������
 *              IF2UnPacker * lpInUnPacker     �����
 *              IF2Packer *   lpOutPacker      Ӧ���
 * Output     : 
 * Return     : >=0		    �ɹ�
 *				      <0          ʧ�� 		
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
///end 20110729 ��Ԫ�� add, ����һ���������GetCaeCodePrice�����GetSecuCodePrice�������嵵����۸���Ϣ�ķ���

/*==========================================================
 * Function   : GetUserToken
 * Description: �û����ƻ�ȡ
 * Input      : IAS2Context  lpContext	    ������
 *              cosnt int iInitDate         ϵͳ��ʼ������
 *              const char cCertType        ������
 *              const char * sCertAccount   ����ʺ�
 *              const char cPasswordType    �������
 *              const char * sPassword      ����
 *              const char   cPasswordCheck ����У��
 * Output     : char *sUserToken            ����
 * Return     : >=0		    �ɹ�
 *				<0          ʧ�� 		
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
 * Description: �û�����У��
 * Input      : IAS2Context  lpContext	    ������
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
 * Description: �������У��
 * Input      : IAS2Context  lpContext          ������
 * Output     : 
 * Return     : =0          �ɹ�
 *              >0          ʧ�� 
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
 * Description: ���ּ����㷨
 * Input      :  char *pIn  ��Ҫ���ܵ�Դ
 * Output     :  char *pOut ���ܽ��
 * Return     : =0          �ɹ�
 *              <>0         ʧ�� 
 * Author     : wangry
 * Date       : 2009/04/16
 ==========================================================*/

int EncodeTwoWord(char *pIn, char *pOut)
{
	return lib_EncodeTwoWord( pIn,  pOut);
}

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
int DecodeTwoWord(char *pIn, char *pOut)
{
	return lib_DecodeTwoWord(pIn, pOut);
}

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
                 //��ȡ��¼�ֶ�ֵ
                 //ETF�ɷݹɴ���
                 if (hs_strcmp(lpMDBResultSet->GetColName(i),"component_code") == 0)
                 	hs_strcpy(pEtfComponent[j].p_component_code,lpMDBResultSet->GetStrByIndex(i));
                 //ETF�ɷݹɴ�������
                 else if (hs_strcmp(lpMDBResultSet->GetColName(i),"component_name") == 0)
                 {
                    hs_strcpy(pEtfComponent[j].p_component_name,lpMDBResultSet->GetStrByIndex(i));
                    if (isnull(trim(pEtfComponent[j].p_component_name)) == 0)
                       hs_strcpy(pEtfComponent[j].p_component_name,pEtfComponent[j].p_component_code);
                 }
                 //�����־
                 else if (hs_strcmp(lpMDBResultSet->GetColName(i),"replace_flag") == 0)
                    pEtfComponent[j].p_replace_flag = lpMDBResultSet->GetCharByIndex(i);
                 //��۱���
                 else if (hs_strcmp(lpMDBResultSet->GetColName(i),"replace_ratio") == 0)
                    pEtfComponent[j].p_replace_ratio = lpMDBResultSet->GetDoubleByIndex(i);
                 //������
                 else if (hs_strcmp(lpMDBResultSet->GetColName(i),"replace_balance") == 0)
                    pEtfComponent[j].p_replace_balance = lpMDBResultSet->GetDoubleByIndex(i);
                 //�ɷݹ�����
                 else if (hs_strcmp(lpMDBResultSet->GetColName(i),"component_amount") == 0)
                    pEtfComponent[j].p_component_amount = lpMDBResultSet->GetDoubleByIndex(i);
                 //20100121 zhouwm �����ֶ����redeem_replace_balance��secu_market_code begin 
                 //���������
                 else if (hs_strcmp(lpMDBResultSet->GetColName(i),"redeem_replace_balance") == 0)
                    pEtfComponent[j].p_redeem_replace_balance = lpMDBResultSet->GetDoubleByIndex(i);
                 //֤ȯ�����г�
                 else if (hs_strcmp(lpMDBResultSet->GetColName(i),"secu_market_code") == 0)
                 	hs_strcpy(pEtfComponent[j].p_secu_market_code,lpMDBResultSet->GetStrByIndex(i));
                 //20100121 zhouwm �����ֶ����redeem_replace_balance��secu_market_code end
               }
               
               j = j + 1;
               lpMDBResultSet->Next();
            }
            iReturnCode = j;
         }
         else
         {
 
            *iErrorNo = ERR_QUERYMEMORYTABLE_ERROR;
            hs_snprintf(sErrorInfo,500,"��ѯ�ڴ����ݿ����[�ڴ��: '%s'][�ֶ�: *][����: '%s']",p_table_name,p_where_str);
            hs_strncat(sErrorPathInfo," -> EtfToStruct()",500);
            iReturnCode = -1;
            goto svr_end;
         }
         
      }
      else
      {
          *iErrorNo = ERR_GETMEMORYSERVICESESSIONERROR;
          hs_strcpy(sErrorInfo,"ȡ�ڴ����session����");
          hs_strncat(sErrorPathInfo," -> EtfToStruct()",500);
          iReturnCode = -1;
          
          goto svr_end;
      }
   }
   else
   {
      *iErrorNo = ERR_GETMEMORYDATASESSIONFAIL;
      hs_strcpy(sErrorInfo,"ȡ�ڴ����ݷ������");
      hs_strncat(sErrorPathInfo," -> EtfToStruct()",500);
      iReturnCode = -1;
      
   }
   
   goto svr_end;
svr_end:
   if (lpMDBResultSet)
      lpMDBResultSet->Destroy();  //�ͷŽ��������
   
   return iReturnCode; 
}

/*==========================================================
 * Function   : EtfResultUnion
 * Description: ��������ĳɷִ����޸�ETF�ɷֹ���Ϣ�ṹ�����ж�Ӧ�ĳɷִ�����������
 * Input      :  S_ETFCOMPONENT **pEtfComponent        �ɷݹɽṹ����
 *            :  const int      iArrayLen              �ṹ����
 *            :  const int      iListLen              �ṹ����
 *            :  char           sComponentCode[][7]    �ɷݹɴ���
 *            :  double         dEnableAmount[]        ��������
 *            :  double         dIssueAmount[]         ���깺�������
 * Return     :  =0          �ɹ�
 *               <>0         ʧ�� 
 * Author     : zhouwm
 * Date       : 2009/05/06
 ==========================================================*/
int EtfResultUnion(S_ETFCOMPONENT *pEtfComponent,const int iArrayLen,const int iListLen,char sComponentCode[][7],double dEnableAmount[],double dIssueAmount[])
{
   int iPos = 0,i = 0;
   
   while ((isnull(trim(sComponentCode[i])) != 0) && (i < iListLen))
   {
   	  //���ҳɷݹɴ��룬����ҵ����޸��޸Ľṹ�����еĳ�Ա����
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
 * Description: ETF�ɷֹ���Ϣ�������
 * Input      :  S_ETFCOMPONENT **pEtfComponent     �ɷݹɽṹ
 *            :  const int      *sComponentCode     ���鳤��
 *            :  const char     *sComponentCode     �ɷֹ�Ʊ����
 * Return     :  >=0            �ɹ�
 *               <0             ʧ�� 
 * Author     : zhouwm
 * Date       : 2009/05/06
 ==========================================================*/
int ResultSearch(S_ETFCOMPONENT *pEtfComponent,const int iArrayLen,const char *sComponentCode)
{
   int iLeft = 0, iRight = 0, iMiddle = 0;
   // ���ֲ���
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
 * Description: ����Liscense
 * Input      : char *pDecLiscense ���ܺ��Liscense
 *              const char *pLiscense ����ļ���Liscense
 *              unsigned short dwKey  ��Կ
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
 * Description: ����Liscense
 * Input      : char *pEncLiscense ���ܺ��Liscense
 *              const char *pLiscense ����ļ���Liscense
 *              unsigned short dwKey  ��Կ
 * Output     : char *pEncLiscense ���ܺ��Liscense
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
 * Description: ���ڰ�08ְҵ����ת��Ϊ06��
 * Input      : char *sz_src Դ�ַ���
 *              char *sz_dest ת�����06��ְҵ����
 * Output     : char *sz_dest ת�����06��ְҵ����
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
 * Description: ���ڰ�08������������ת��Ϊ06��
 * Input      : char *sz_src Դ�ַ���
 * Output     : char ת�����06�������������
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
 * Description: Blowfish����
 * Input      : const void *lpIn         		���������
 *              int nLength               		���ĳ��� 
 *              const void *lpKey               ������Կ
 * Output     : lpOut 							���������
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
 * Description: Blowfish����
 * Input      : const void *lpIn         		���������
 *              int nLength               		���ĳ��� 
 *              const void *lpKey               ������Կ
 * Output     : lpOut 							���������
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
* Description: ��������
* Input      : const char *pIn ��������봮
*              char *pOut ����ļ��ܺ�����롣
* Return     : 0: �ɹ�������ʧ�ܡ�
* Author     : wangry
* Date       : 2010/03/03
==========================================================*/
int HsPwdEncode(const char *pIn, char *pOut)
{
	return lib_HsPwdEncode(pIn, pOut);
}

/*==========================================================
* Function   : HsPwdDecode
* Description: �������
* Input      : const char *pIn ����ļ��ܵ����봮
*              char *pOut ����Ľ��ܺ�����롣
* Return     : 0: �ɹ�������ʧ�ܡ�
* Author     : wangry
* Date       : 2010/03/03
==========================================================*/
int HsPwdDecode(const char *pIn, char *pOut)
{
	return lib_HsPwdDecode(pIn, pOut);
}
