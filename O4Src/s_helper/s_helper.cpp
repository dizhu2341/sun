/*
 * Program: s_helper.cpp
 * Author : ��ΰ��.
 * Date   : 2008/10/14.
 * Notes  : ���ߺ���ʵ��
 * Modify : �汾       �޸�����   �޸���         �޸ĵ�       �޸�˵��
 *          V8.0.6.0   20100614   ��Ԫ��         �ڲ�         ����ҵ����Ӫƽ̨V2.0��Ŀ2011���߽���
 *          V8.0.5.4   20110415   ������         20110415019  ���Ӻ���SynCallSubServicePack1��SubServiceCallPack1
 *          V8.0.5.3   20101222   ��Ԫ��         20101221012  ������SynCallSubService�����44��[TAG_INTERNAL_LICENSE_NO]-- �ڲ����֤���,�߼������߼�ʱ���֤�����
 *                                                            ������GetLibVersion���޸İ汾ΪV8.0.5.3
 *          V8.0.5.2   20100702   ��ΰ��         20100702016  ������CheckDbLinkMethod���޸��޸�iSqlcode <= -25401 && iSqlcode >= -25409�ж�
 *                                                            ������GetLibVersion���޸İ汾ΪV8.0.5.2
 *          V8.0.5.1   20100630   ��ΰ��         20100630020  ������CheckDbLinkMethod���޸�SQLCODE <= -3100 and SQLCODE > -3133�ж�
 *                                                            ������GetLibVersion���޸İ汾ΪV8.0.5.1
 *          V8.0.5.0   20100414   ��ΰ��         �ڲ�         ����
 *          V8.0.4.2   20091212   ��ΰ��         �ڲ�         [SynCallSubService]�޸ĳ�ʱʱ���ԭʼ���л�ȡ,�޸�li_timeout��li_timeout���ʹ�unsigned int�޸�Ϊint
 *          V8.0.4.1   20091027   ��ΰ��         �ڲ�         �����ӷ����쳣ʱ��Proc��������쳣���ݿ��¼
 *          V8.0.4.0   20090926   ��ΰ��         �ڲ�         ����
 *          V8.0.3.2   20090924   ��ΰ��         �ڲ�         ���Ӻ���CheckDbLinkMethod
 *          V8.0.3.1   20090727   ��ΰ��         �ڲ�         AsynPostMessage�������ӽӿ�sPlugInName
 *          V8.0.3.0   20090626   ��ΰ��         �ڲ�         ���
 *          V8.0.2.0   20090420   ��ΰ��         �ڲ�         ���
 *          V8.0.1.0   20090120   ��ΰ��         �ڲ�         ���
 *          V8.0.0.0   20081014   ��ΰ��         �ڲ�         ����
 */

#include "s_helper.h"
#include <Include/log_interface.h>

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
char *  FUNCTION_CALL_MODE GetLibVersion( )
{
	///20110415 ������ �汾��V8.0.5.3�޸�ΪV8.0.5.4
    //20101222 liuyz  �汾��V8.0.5.2�޸�V8.0.5.3
    //20100702 zhouwm �汾��V8.0.5.1�޸�V8.0.5.2
    //20100630 zhouwm �汾��V8.0.5.0�޸�V8.0.5.1
    return "V9.0.2.0";
}
#endif


/*==========================================================
 * Function   : PackResultSet
 * Description: �����������
 * Input      : IF2ResultSet * lpInUnPacker �����
 * Output     : IF2Packer * lpOutPacker     ���
 * Return     : 0       �ɹ�
 *              <>0     ʧ��
 * Author     : zhouwm
 * Date       : 2008/10/20.
 ==========================================================*/
int PackResultSet(IF2ResultSet * lpInUnPacker,IF2Packer * lpOutPacker)
{
  int iRet=0;
  const char * pBuff;
  int iCount;
  int iCols =0; //�ֶ���
  char sErrorPathInfo[501]={0};

  if ((lpInUnPacker) && (lpOutPacker))
  {
     hs_strncpy(sErrorPathInfo,conversion((char *)lpInUnPacker->GetStr("error_pathinfo")),500);
     iCols = lpInUnPacker->GetColCount(); //ȡ�ֶ���

     //���Ӧ����ֶ���Ϣ
     for (iCount=0;iCount<iCols;iCount++)
     {
       lpOutPacker->AddField( lpInUnPacker->GetColName(iCount),
       lpInUnPacker->GetColType(iCount),
       lpInUnPacker->GetColWidth(iCount),
       lpInUnPacker->GetColScale(iCount));
     }

       //���������¼���ֶΣ������ӵ�Ӧ���
     while ( !lpInUnPacker->IsEOF())
     {
        for (iCount=0;iCount<iCols;iCount++)
        {
          char lc_ColType = ' ';
          lc_ColType = lpInUnPacker->GetColType(iCount);

          if (lc_ColType == 'R')
          {
            int pi_len = 0;
            void *pr_data = NULL;
            pr_data = lpInUnPacker->GetRawByIndex(iCount,&pi_len);
            lpOutPacker->AddRaw(pr_data,pi_len);
          }
          else
          {
          	pBuff = lpInUnPacker->GetStrByIndex(iCount);//ȡ��ǰ�ֶ�
            lpOutPacker->AddStr(pBuff); //��ӵ�Ӧ���
          }
        }

        lpInUnPacker->Next();
     }
  }
  else if (lpOutPacker)
  {
    hs_strcat(sErrorPathInfo,"->PackResultSet()");
    lpOutPacker->AddField("error_pathinfo");
    lpOutPacker->AddField("error_no");
    lpOutPacker->AddField("error_info");
    lpOutPacker->AddStr(sErrorPathInfo);
    lpOutPacker->AddInt(ERR_PACKRESULE_ISNULL);
    lpOutPacker->AddStr("��������Ϊ��");
  }

  return iRet;

}

/*==========================================================
 * Function   : MutiResultSetPack
 * Description: ���������
 * Input      : IUnPacker  lpResultSet  �����
 * Output     : IPacker    lpOutPacker  ��������
 * Return     : 0   �ɹ�
 *        <>0     ʧ��
 * Author     : zhouwm
 * Date       : 2006/08/15
 ==========================================================*/
int MutiResultSetPack(IF2UnPacker * lpResultSet,IF2Packer * lpOutPacker)
{
   int iRet=0;
   int iCount;
   int i;
   char sResultName[20];

   iCount = lpResultSet->GetDatasetCount();

   for (i=0;i < iCount;i++)
   {
      lpResultSet->SetCurrentDatasetByIndex(i);

      if (i != 0)
      {
         sprintf(sResultName,"%d",i);
         lpOutPacker->NewDataset(sResultName,0);
      }
      PackResultSet(lpResultSet,lpOutPacker);
   }

   return iRet;
}



//ͬ���ӷ������
int SynCallSubService(IAS2Context * lpContext,IF2UnPacker * lpInUnPacker, IESBMessage ** lppAnsMessage,unsigned int iTimeOut,unsigned int dwFuncNo,unsigned int dwBranchNo,unsigned int dwSystemNo,unsigned int dwSubSystemNo)
{
   int iRet = -1;
   //��ȡ��ʱʱ��
   //20091226 zhouwm ��unsigned int�޸�Ϊint
   int li_TimeOut = iTimeOut;   
   int li_tmp = 0;
   //20091226 zhouwm ��unsigned int�޸�Ϊint
   int li_TimeOut1 = 0;  //��ͷ��ʱʱ��
   if (li_TimeOut <= 0)
      li_TimeOut = CNST_TIMEOUT_DEFAULT;
   
   //����һ��������Ϣ
   IESBMessageFactory * lpESBMessageFactory = lpContext->GetESBMsgFactory();
   if (lpESBMessageFactory)
   {
      IESBMessage * lpMsgReq =  lpESBMessageFactory->GetESBMsg();
      
      if (lpMsgReq)
      { 
         lpMsgReq->GetItem(TAG_PACKET_TYPE)->SetInt(REQUEST_PACKET);
         
         if (lpContext->GetOrgRequest()->IsExist(TAG_TIMESTAMP) > 0)
         	lpMsgReq->GetItem(TAG_TIMESTAMP)->SetStringAtTail("begin SynCallSubService");
         
         //��ͷ��ʱʱ�䣬max(��ͷ��ʱʱ��,ԭ�ӷ������ð�ͷʱ��)
         //20091212 ��ΰ�� [SynCallSubService]�޸ĳ�ʱʱ���ԭʼ���л�ȡ
         //li_TimeOut1 = lpMsgReq->GetItem(TAG_LIVE_TIME)->GetInt(TAG_LIVE_TIME);
         li_TimeOut1 = lpContext->GetOrgRequest()->GetItem(TAG_LIVE_TIME)->GetInt();
         
         //���ܺ�
         if (dwFuncNo > 0)
            lpMsgReq->GetItem(TAG_FUNCTION_ID)->SetInt(dwFuncNo);
         
         //��֧����
         if (dwBranchNo > 0)
            lpMsgReq->GetItem(TAG_BRANCH_NO)->SetInt(dwBranchNo);
         else
         {
         	 if ( lpContext->GetOrgRequest()->IsExist(TAG_BRANCH_NO) > 0 )
         	 {
         	    li_tmp = lpContext->GetOrgRequest()->GetItem(TAG_BRANCH_NO)->GetInt();
         	    lpMsgReq->GetItem(TAG_BRANCH_NO)->SetInt(li_tmp);
         	 }
         }
         
         //ϵͳ���
         if (dwSystemNo > 0)
            lpMsgReq->GetItem(TAG_SYSTEM_NO)->SetInt(dwSystemNo);
         else
         {
         	 if ( lpContext->GetOrgRequest()->IsExist(TAG_SYSTEM_NO) > 0 )
         	 {
         	    li_tmp = lpContext->GetOrgRequest()->GetItem(TAG_SYSTEM_NO)->GetInt();
         	    lpMsgReq->GetItem(TAG_SYSTEM_NO)->SetInt(li_tmp);
         	 }
         }
         	 
         //��ϵͳ���
         if (dwSubSystemNo > 0)
            lpMsgReq->GetItem(TAG_SUB_SYSTEM_NO)->SetInt(dwSubSystemNo);
         else
         {
         	 if ( lpContext->GetOrgRequest()->IsExist(TAG_SUB_SYSTEM_NO) > 0 )
         	 {
         	    li_tmp = lpContext->GetOrgRequest()->GetItem(TAG_SUB_SYSTEM_NO)->GetInt();
         	    lpMsgReq->GetItem(TAG_SUB_SYSTEM_NO)->SetInt(li_tmp);
         	 }
         }
         
         ///begin 20101222 ��Ԫ�� add, ���44��-- �ڲ����֤���
         //�ڲ����֤���
         if ( lpContext->GetOrgRequest()->IsExist(TAG_INTERNAL_LICENSE_NO) > 0 )
         {
            li_tmp = lpContext->GetOrgRequest()->GetItem(TAG_INTERNAL_LICENSE_NO)->GetInt();
            lpMsgReq->GetItem(TAG_INTERNAL_LICENSE_NO)->SetInt(li_tmp);
         }
         ///end 20101222 ��Ԫ�� add
         
         //ȡҵ����
         void * lpBizBuf = lpInUnPacker->GetPackBuf();
         int iLen = lpInUnPacker->GetPackLen();
         //ҵ���帴�Ƶ���Ϣ��
         lpMsgReq->GetItem(TAG_MESSAGE_BODY)->SetRawData( lpBizBuf,iLen );
         
         //�����ӷ���,����ʧ��ʱ��������Ϣ�ѱ��ͷ�
         //��ͷ��ʱʱ���ԭ�ӷ������õĳ�ʱʱ��ȡ��ֵ��max(��ͷ��ʱʱ��,ԭ�ӷ������ð�ͷʱ��)
         if (li_TimeOut1 > li_TimeOut)
         	iRet = lpContext->CallSubService(lpMsgReq,lppAnsMessage ,li_TimeOut1);
         else
         	iRet = lpContext->CallSubService(lpMsgReq,lppAnsMessage ,li_TimeOut);
      }
   }
   
   return  iRet;
}

//ԭ�ӷ��������չ
int SubServiceCall(IAS2Context * lpContext,IF2UnPacker * lpInUnPacker, IF2Packer * lpOutPacker,unsigned int iTimeOut,unsigned int iFuncNo,unsigned int iBranchNo,unsigned int iSystemNo,unsigned int iSubSystemNo)
{
   int iReturnCode = 0;
   int iErrorNo = 0;
   int iErrorID = 0;
   int li_TimeOut = 0;
   char sErrorInfo[501]={0};
   char sErrorSysInfo[501]={0};
   char sErrorPathInfo[501]={0};
   
   hs_strncpy(sErrorPathInfo,conversion((char *)lpInUnPacker->GetStr("error_pathinfo")),500);
   hs_snprintf(sErrorPathInfo,500,"%s -> SubServiceCall(%d)",sErrorPathInfo,iFuncNo);
   
   IESBMessageFactory * lpESBMessageFactory = lpContext->GetESBMsgFactory();
   IF2PackSvr * lpPackService = lpContext->GetF2PackSvr();
   int iSubRet = 0;

   //��ȡ��ʱʱ��
   li_TimeOut = iTimeOut;
   if (li_TimeOut <= 0)
      li_TimeOut = CNST_TIMEOUT_DEFAULT;
      
   IF2UnPacker * lpUnPack1 = NULL;
   IESBMessage * lpMsgA1 = NULL;
   iSubRet = SynCallSubService(lpContext,lpInUnPacker,&lpMsgA1,li_TimeOut,iFuncNo,iBranchNo,iSystemNo,iSubSystemNo);

   if ( iSubRet == 0 && lpMsgA1 )
   {
       int iBizRetcode = lpMsgA1->GetItem(TAG_RETURN_CODE)->GetInt(); //������
       //1����-1 ͨѶʧ��
       
       //��ҵ���巵��ҵ���壬ûҵ������ͨ����Ϣͷ�е�error_no,error_info,return_code������
       if   ( ( iBizRetcode == RT_ERR_PROCESS ) || ( iBizRetcode == RT_ERR_TRANSFER ) )
       {
          //ϵͳ������Ϣ��AR����ת����AS���ܴ�������û��ҵ���壬˵������û���ύ
          iErrorNo = ERR_SYSERR_AR_NOTRANS_AS_NOPROC;
          iErrorID = iBizRetcode;
          if (iBizRetcode == RT_ERR_TRANSFER)
          {
             hs_snprintf(sErrorInfo,500,"·�ɲ���ת��[%s],��������Ϣ = [%s] ���ID = [%s] �ڵ��� = [%d] ��ϵͳ��� = [%d]",
                               lpMsgA1->GetItem(TAG_ERROR_INFO)->GetString(),
                               lpMsgA1->GetItem(TAG_SENDER_PATH)->GetString(IDX_OSPF_NAME),
                               lpMsgA1->GetItem(TAG_SENDER_PATH)->GetString(IDX_PLUGIN_ID),iSystemNo,iSubSystemNo);
          
          }   
          else
             hs_strcpy(sErrorInfo,lpMsgA1->GetItem(TAG_ERROR_INFO)->GetString());
          
          hs_snprintf(sErrorSysInfo,500,"SubServiceCall����[%d]ʧ��(retcode[%d],�ڵ���[%d],��ϵͳ���[%d])",iFuncNo,iBizRetcode,iSystemNo,iSubSystemNo);
          
          iReturnCode = SystemErrorPacker(lpOutPacker,sErrorPathInfo,iErrorNo,sErrorInfo);
          WriteSystemLog(lpContext,sErrorPathInfo,iErrorNo,sErrorInfo,iErrorID,sErrorSysInfo);
       }
       else
       {
          int iAnsLen = 0;
       
          void * lpAnsBuf =(void *) lpMsgA1->GetItem(TAG_MESSAGE_BODY)->GetRawData( &iAnsLen ); //�ڴ���msg�ͷ�
          
          if ( lpAnsBuf && (iAnsLen>0) )
          {
             lpUnPack1 = lpPackService->GetUnPacker(lpAnsBuf,iAnsLen);
             if (lpUnPack1)
             {
                //ҵ��ɹ���ҵ�����
                PackResultSet(lpUnPack1,lpOutPacker);
                lpUnPack1->Release();
                
                iReturnCode = iBizRetcode;
             }
             else
             {
             	//ϵͳ������Ϣ��AR����ת����AS���ܴ�������û��ҵ���壬˵������û���ύ
                iErrorNo = ERR_EXEC_BUSIPACK_ISNULL;
                iErrorID = RT_ERR_PROCESS;
                hs_snprintf(sErrorInfo,500,"ҵ���Ϊ��[���ܺ�[%d] �ڵ���[%d] ��ϵͳ���[%d]]",iFuncNo,iSystemNo,iSubSystemNo);
                hs_snprintf(sErrorSysInfo,500,"SubServiceCall����[%d]ʧ��(retcode[%d],�ڵ���[%d],��ϵͳ���[%d])",iFuncNo,RT_ERR_PROCESS,iSystemNo,iSubSystemNo);
                
                iReturnCode = SystemErrorPacker(lpOutPacker,sErrorPathInfo,iErrorNo,sErrorInfo);
                WriteSystemLog(lpContext,sErrorPathInfo,iErrorNo,sErrorInfo,iErrorID,sErrorSysInfo);
                iReturnCode = iErrorNo;
             }
          }
          else
          {
          	 //ϵͳ������Ϣ��AR����ת����AS���ܴ�������û��ҵ���壬˵������û���ύ
             iErrorNo = ERR_EXEC_BUSIPACK_ISNULL;
             iErrorID = RT_ERR_PROCESS;
             hs_snprintf(sErrorInfo,500,"ҵ���Ϊ��[���ܺ�[%d] �ڵ���[%d] ��ϵͳ���[%d]]",iFuncNo,iSystemNo,iSubSystemNo);
             hs_snprintf(sErrorSysInfo,500,"SubServiceCall����[%d]ʧ��(retcode[%d],�ڵ���[%d],��ϵͳ���[%d])",iFuncNo,RT_ERR_PROCESS,iSystemNo,iSubSystemNo);
             
             iReturnCode = SystemErrorPacker(lpOutPacker,sErrorPathInfo,iErrorNo,sErrorInfo);
             WriteSystemLog(lpContext,sErrorPathInfo,iErrorNo,sErrorInfo,iErrorID,sErrorSysInfo);
             iReturnCode = iErrorNo;
          }
       }
       
	   lpMsgA1->Release();
   }
   else
   {
       //����ʧ�ܻ�û�յ�Ӧ����Ϣ����ʱ��
   	   if ( iSubRet == -2)
   	   {
   	   	  //��ʱ����(���׿��ܳɹ�������ʧ��)��Ҫ��¼
          iErrorNo = ERR_SUBSERVICE_CALL_TIMEOUT;
          iErrorID = iSubRet;
          hs_snprintf(sErrorInfo,500,"ҵ�������У����Ժ����Ƿ�ɹ�[���ܺ�[%d] �ڵ���[%d] ��ϵͳ���[%d]]",iFuncNo,iSystemNo,iSubSystemNo);
          //��������¹��ܿ����ѱ����õ�,��Ҫ����
   	      hs_snprintf(sErrorSysInfo,500,"SubServiceCall����[%d]ʧ��(��ʱ[%d],�ڵ���[%d],��ϵͳ���[%d])",iFuncNo,iSubRet,iSystemNo,iSubSystemNo);
   	   }
   	   else
   	   {
   	   	  //ϵͳ���ô���(���׿϶�û�ύ),���������е��״ν��׵��ò��ؼ�¼
   	      iErrorNo = ERR_SUBSERVICE_CALL_FAIL;
          iErrorID = iSubRet;
          hs_snprintf(sErrorInfo,500,"�ӷ������ʧ��[���ܺ�[%d] �ڵ���[%d] ��ϵͳ���[%d]]",iFuncNo,iSystemNo,iSubSystemNo);
          hs_snprintf(sErrorSysInfo,500,"SubServiceCall����[%d]ʧ��(����[%d],�ڵ���[%d],��ϵͳ���[%d])",iFuncNo,iSubRet,iSystemNo,iSubSystemNo);
   	   }
   	   iReturnCode = SystemErrorPacker(lpOutPacker,sErrorPathInfo,iErrorNo,sErrorInfo);
       WriteSystemLog(lpContext,sErrorPathInfo,iErrorNo,sErrorInfo,iErrorID,sErrorSysInfo);
   }

   return iReturnCode;
}

//����ԭ�ӷ��������չ
int SubServiceCallTrans(IAS2Context * lpContext,IF2UnPacker * lpInUnPacker, IF2Packer * lpOutPacker,IAS2TM * lpTransMonitor,unsigned int iTimeOut,unsigned int iFuncNo,unsigned int iBranchNo,unsigned int iSystemNo,unsigned int iSubSystemNo)
{
   int iReturnCode = 0;
   int iErrorNo = 0;
   int iErrorID = 0;
   int li_TimeOut = iTimeOut;
   char sErrorInfo[501]={0};
   char sErrorSysInfo[501]={0};
   char sErrorPathInfo[501]={0};
   
   hs_strncpy(sErrorPathInfo,conversion((char *)lpInUnPacker->GetStr("error_pathinfo")),500);
   hs_snprintf(sErrorPathInfo,500,"%s -> SubServiceCall(%d)",sErrorPathInfo,iFuncNo);
   
   //��ȡ��ʱʱ��
   li_TimeOut = iTimeOut;
   if (li_TimeOut <= 0)
      li_TimeOut = CNST_TIMEOUT_DEFAULT;
   
   if (lpTransMonitor)
   {
       IESBMessageFactory * lpESBMessageFactory = lpContext->GetESBMsgFactory();
       IF2PackSvr * lpPackService = lpContext->GetF2PackSvr();
       
       int iSubRet = 0;
       
       IF2UnPacker * lpUnPack1 = NULL;
       IESBMessage * lpMsgA1 = NULL;
       iSubRet = SynCallSubService(lpContext,lpInUnPacker,&lpMsgA1,li_TimeOut,iFuncNo,iBranchNo,iSystemNo,iSubSystemNo); 
       if ( iSubRet == 0 && lpMsgA1 )
       {
           //���óɹ������յ�Ӧ����Ϣ
           int iBizRetcode = lpMsgA1->GetItem(TAG_RETURN_CODE)->GetInt(); //������

           if   ( ( iBizRetcode == RT_ERR_PROCESS ) || ( iBizRetcode == RT_ERR_TRANSFER ) )
           {
               //ϵͳ������Ϣ��AR����ת����AS���ܴ�������û��ҵ���壬˵������û���ύ
               iErrorNo = ERR_SYSERR_AR_NOTRANS_AS_NOPROC;
               iErrorID = iBizRetcode;
               if (iBizRetcode == RT_ERR_TRANSFER)
               {
                  hs_snprintf(sErrorInfo,500,"·�ɲ���ת��[%s],��������Ϣ = [%s] ���ID = [%s] �ڵ��� = [%d] ��ϵͳ��� = [%d]",
                                    lpMsgA1->GetItem(TAG_ERROR_INFO)->GetString(),
                                    lpMsgA1->GetItem(TAG_SENDER_PATH)->GetString(IDX_OSPF_NAME),
                                    lpMsgA1->GetItem(TAG_SENDER_PATH)->GetString(IDX_PLUGIN_ID),iSystemNo,iSubSystemNo);
               
               }   
               else
                  hs_strcpy(sErrorInfo,lpMsgA1->GetItem(TAG_ERROR_INFO)->GetString());
                  
               hs_snprintf(sErrorSysInfo,500,"SubServiceCall����[%d]ʧ��(retcode[%d],�ڵ���[%d],��ϵͳ���[%d])",iFuncNo,iBizRetcode,iSystemNo,iSubSystemNo);
               //20091027 ��ΰ�� �����ӷ����쳣ʱ��Proc��������쳣���ݿ��¼
               //if ( lpTransMonitor->GetCommitNum() != 0 )
               //	  lpTransMonitor->Assert();

               iReturnCode = SystemErrorPacker(lpOutPacker,sErrorPathInfo,iErrorNo,sErrorInfo);
               WriteSystemLog(lpContext,sErrorPathInfo,iErrorNo,sErrorInfo,iErrorID,sErrorSysInfo);
           }
           else
           {
               int iAnsLen = 0;
               void * lpAnsBuf =(void *) lpMsgA1->GetItem(TAG_MESSAGE_BODY)->GetRawData( &iAnsLen ); //�ڴ���msg�ͷ�
               if ( lpAnsBuf && (iAnsLen>0) )
               {
                   lpUnPack1 = lpPackService->GetUnPacker(lpAnsBuf,iAnsLen);
              
                   if (lpUnPack1)
                   {
                       //ҵ��ɹ���ҵ�����
                       if  ( iBizRetcode == RT_ERR_NONE )
                       {
                           //ҵ����ɹ�
                           PackResultSet(lpUnPack1,lpOutPacker);
                           lpUnPack1->Release();
                       }
                       else
                       {
                           //20091027 ��ΰ�� �����ӷ����쳣ʱ��Proc��������쳣���ݿ��¼
                           //ҵ����ʧ��,,���������е��״ν��׵��ò��ؼ�¼
                           //if ( lpTransMonitor->GetCommitNum() != 0 )
                           //	  lpTransMonitor->Assert();
                           
                           PackResultSet(lpUnPack1,lpOutPacker);
                           lpUnPack1->Release();
                       }
                       iReturnCode = iBizRetcode;
                   }
                   else
                   {
                   	   //20091027 ��ΰ�� �����ӷ����쳣ʱ��Proc��������쳣���ݿ��¼
                   	   //ҵ����ʧ��,,���������е��״ν��׵��ò��ؼ�¼
                       //if ( lpTransMonitor->GetCommitNum() != 0 )
                   	   //   lpTransMonitor->Assert();
                   	   
                   	   //ϵͳ������Ϣ��AR����ת����AS���ܴ�������û��ҵ���壬˵������û���ύ
                       iErrorNo = ERR_EXEC_BUSIPACK_ISNULL;
                       iErrorID = RT_ERR_PROCESS;
                       hs_snprintf(sErrorInfo,500,"ҵ���Ϊ��[���ܺ�[%d] �ڵ���[%d] ��ϵͳ���[%d]]",iFuncNo,iSystemNo,iSubSystemNo);
                       hs_snprintf(sErrorSysInfo,500,"SubServiceCall����[%d]ʧ��(retcode[%d],�ڵ���[%d],��ϵͳ���[%d])",iFuncNo,RT_ERR_PROCESS,iSystemNo,iSubSystemNo);
                       iReturnCode = SystemErrorPacker(lpOutPacker,sErrorPathInfo,iErrorNo,sErrorInfo);
                       WriteSystemLog(lpContext,sErrorPathInfo,iErrorNo,sErrorInfo,iErrorID,sErrorSysInfo);
                       iReturnCode = iErrorNo;
                   }
               }
               else
               {
               	   //20091027 ��ΰ�� �����ӷ����쳣ʱ��Proc��������쳣���ݿ��¼
               	   //ҵ����ʧ��,,���������е��״ν��׵��ò��ؼ�¼
                   //if ( lpTransMonitor->GetCommitNum() != 0 )
                   //	  lpTransMonitor->Assert();
                   
                   //ϵͳ������Ϣ��AR����ת����AS���ܴ�������û��ҵ���壬˵������û���ύ
                   iErrorNo = ERR_EXEC_BUSIPACK_ISNULL;
                   iErrorID = RT_ERR_PROCESS;
                   hs_snprintf(sErrorInfo,500,"ҵ���Ϊ��[���ܺ�[%d] �ڵ���[%d] ��ϵͳ���[%d]]",iFuncNo,iSystemNo,iSubSystemNo);
                   hs_snprintf(sErrorSysInfo,500,"SubServiceCall����[%d]ʧ��(retcode[%d],�ڵ���[%d],��ϵͳ���[%d])",iFuncNo,RT_ERR_PROCESS,iSystemNo,iSubSystemNo);
                   iReturnCode = SystemErrorPacker(lpOutPacker,sErrorPathInfo,iErrorNo,sErrorInfo);
                   WriteSystemLog(lpContext,sErrorPathInfo,iErrorNo,sErrorInfo,iErrorID,sErrorSysInfo);
                   iReturnCode = iErrorNo;
               }
               
           }
           
           lpMsgA1->Release();
       }
       else
       {
           //����ʧ�ܻ�û�յ�Ӧ����Ϣ����ʱ��
           if ( iSubRet == -2)
           {
               //��ʱ����(���׿��ܳɹ�������ʧ��)��Ҫ��¼
               iErrorNo = ERR_SUBSERVICE_CALL_TIMEOUT;
               iErrorID = iSubRet;
               hs_snprintf(sErrorInfo,500,"�ӷ�����ó�ʱ[���ܺ�[%d] �ڵ���[%d] ��ϵͳ���[%d]]",iFuncNo,iSystemNo,iSubSystemNo);
               //��������¹��ܿ����ѱ����õ�,��Ҫ����
   	           hs_snprintf(sErrorSysInfo,500,"SubServiceCall����[%d]ʧ��(��ʱ[%d],�ڵ���[%d],��ϵͳ���[%d])",iFuncNo,iSubRet,iSystemNo,iSubSystemNo);
               
               //20091027 ��ΰ�� �����ӷ����쳣ʱ��Proc��������쳣���ݿ��¼
               //��������¹��ܿ����ѱ����õ�,��Ҫ����
               //lpTransMonitor->Assert();
           }
           else
           {
               //ϵͳ���ô���(���׿϶�û�ύ),���������е���s�ν��׵��ò��ؼ�¼
   	           iErrorNo = ERR_SUBSERVICE_CALL_FAIL;
               iErrorID = iSubRet;
               hs_snprintf(sErrorInfo,500,"�ӷ������ʧ��[���ܺ�[%d] �ڵ���[%d] ��ϵͳ���[%d]]",iFuncNo,iSystemNo,iSubSystemNo);
   	           hs_snprintf(sErrorSysInfo,500,"SubServiceCall����[%d]ʧ��(����[%d],�ڵ���[%d],��ϵͳ���[%d])",iFuncNo,iSubRet,iSystemNo,iSubSystemNo);
   	           
   	           //20091027 ��ΰ�� �����ӷ����쳣ʱ��Proc��������쳣���ݿ��¼
               //if ( lpTransMonitor->GetCommitNum() != 0 )
               //	  lpTransMonitor->Assert();

           }
           //����ϵͳ������Ϣ
           iReturnCode = SystemErrorPacker(lpOutPacker,sErrorPathInfo,iErrorNo,sErrorInfo);
           WriteSystemLog(lpContext,sErrorPathInfo,iErrorNo,sErrorInfo,iErrorID,sErrorSysInfo);
       }
   }
   return iReturnCode;
}

//������Ϣ������
int SystemErrorPacker(IF2Packer * lpOutPacker,const char * sErrorPathInfo,int iErrorNo,const char * sErrorInfo)
{
   lpOutPacker->BeginPack();
   lpOutPacker->AddField("error_pathinfo",'S',500);
   lpOutPacker->AddField("error_no");
   lpOutPacker->AddField("error_info",'S',500);
   lpOutPacker->AddStr(sErrorPathInfo);
   lpOutPacker->AddInt(iErrorNo);
   lpOutPacker->AddStr(sErrorInfo);
   return iErrorNo;
}

//��¼ϵͳ��־
//��¼���м��*operation.biz���������ļ�*operation.bin
int WriteSystemLog(IAS2Context * lpContext,char *sError_PathInfo,int iError_no,char *sError_Info,int iError_id,char *sError_SysInfo)
{
   //char sErrorInfo[2001]={0};
   
   //printf("\nִ��·��: [%s]\n�����: [%d]\n������Ϣ: [%s]\nϵͳ�����: [%d]\nϵͳ������Ϣ: [%s]\n",sError_PathInfo,iError_no,sError_Info,iError_id,sError_SysInfo);
   if (iError_id == 0)
   	  return 0;
   
   //��¼buffer��Ϣ
   static ILogService * lpLog = NULL;
   
   if (!lpLog) lpContext->QueryInterface(SID_BIZLOG,(IKnown **)&lpLog);
   
   if (lpLog)
   {
      IESBMessage * lpESBMessage = lpContext->GetOrgRequest();
      //hs_snprintf(sErrorInfo,2000,"�����: [%d],������Ϣ: [%s],ϵͳ�����: [%d],ϵͳ������Ϣ: [%s]",iError_no,sError_Info,iError_id,sError_SysInfo);
      
      lpLog->AddBizLog(lpESBMessage,sError_PathInfo,iError_no,sError_Info,iError_id,sError_SysInfo);
   }
   else
   {
      printf("\nִ��·��: [%s]\n�����: [%d]\n������Ϣ: [%s]\nϵͳ�����: [%d]\nϵͳ������Ϣ: [%s]\n",sError_PathInfo,iError_no,sError_Info,iError_id,sError_SysInfo);
   }
   
   return 0;
}

//��¼ʱ���
int WriteTimeStamp(IAS2Context * lpContext,char *sWriteSysInfo)
{
   IESBMessage * lpMessage = lpContext->GetOrgRequest();
   
   lpMessage->AddTimeStamp(sWriteSysInfo);

   return 0;
}

//�첽������Ϣ��2.0�����ͣ�
int AsynPostMessage(IAS2Context * lpContext,IF2UnPacker * lpInUnPacker,char * sErrorPathInfo,char * sErrorInfo,char * sTargetAr,char *sTransName,int iFunctionID,int iIssueType,char *sPlugInName)
{
   int li_ReturnCode = 0;
   char p_error_pathinfo[501] = {0};
   hs_snprintf(sErrorPathInfo,500,"%s -> AsynPostMessage()",sErrorPathInfo);
   int li_Flag = 0; 
   IESBMessageFactory * lpESBMessageFactory = lpContext->GetESBMsgFactory();
   IESBMessage * lpMsgReq =  lpESBMessageFactory->GetESBMsg();
   
   if (lpMsgReq)
   {
   	  lpMsgReq->GetItem(TAG_PACKET_TYPE)->SetInt(REQUEST_PACKET);
   	     	  
   	  lpMsgReq->GetItem(TAG_FUNCTION_ID)->SetInt(iFunctionID);
   	  
   	  //ȡҵ����
      void * lpBizBuf = lpInUnPacker->GetPackBuf();
      int iLen = lpInUnPacker->GetPackLen();
         
   	  if (iIssueType > 0)
   	  {
   	     lpMsgReq->GetItem(TAG_ISSUE_TYPE)->SetInt(iIssueType);
   	     
         //ҵ���帴�Ƶ���Ϣ��
         lpMsgReq->GetItem(TAG_KEY_INFO)->SetRawData(lpBizBuf,iLen);
      }
      else
      {
         //ҵ���帴�Ƶ���Ϣ��
         lpMsgReq->GetItem(TAG_MESSAGE_BODY)->SetRawData(lpBizBuf,iLen);
      }
      
   	  if (isnull(trim(sTargetAr)) != 0)
   	     lpMsgReq->GetItem(TAG_ROUTE_INFO)->SetString(sTargetAr, IDX_OSPF_NAME);
   	  if (isnull(trim(sTransName)) != 0)
         lpMsgReq->GetItem(TAG_ROUTE_INFO)->SetString(sTransName, IDX_NBR_NAME);
      if (isnull(trim(sPlugInName)) != 0)
         lpMsgReq->GetItem(TAG_ROUTE_INFO)->SetString(sPlugInName, IDX_PLUGIN_ID);
      
      li_ReturnCode = lpContext->PostMsg(lpMsgReq);
      if (li_ReturnCode != 0)
      	 lpMsgReq->Release();
      
   }
   else
   {
   	  //ϵͳ������Ϣ��AR����ת����AS���ܴ�������û��ҵ���壬˵������û���ύ
      hs_strcpy(sErrorInfo,"ϵͳæ���޷���ȡϵͳ��Ϣ��");
      li_ReturnCode = ERR_SYS_BUSI_GET_MESSAGE_FAIL;
   }
   
   
   
   return li_ReturnCode;
}

//�첽������Ϣ��2.0��ת��1.0���ٷ��ͣ�
int AsynPostMessagePack1(IAS2Context * lpContext,IF2UnPacker * lpInUnPacker,char * sErrorPathInfo,char * sErrorInfo,char * sTargetAr,char *sTransName,int iFunctionID,int iIssueType)
{
   int li_ReturnCode = 0;
   char p_error_pathinfo[501] = {0};
   hs_snprintf(sErrorPathInfo,500,"%s -> AsynPostMessage()",sErrorPathInfo);
   int li_Flag = 0; 
   IESBMessageFactory * lpESBMessageFactory = lpContext->GetESBMsgFactory();
   IESBMessage * lpMsgReq =  lpESBMessageFactory->GetESBMsg();
   
   if (lpMsgReq)
   {
   	  lpMsgReq->GetItem(TAG_PACKET_TYPE)->SetInt(REQUEST_PACKET);
   	     	  
   	  lpMsgReq->GetItem(TAG_FUNCTION_ID)->SetInt(iFunctionID);
   	  
   	  //ȡҵ����
   	  IF2PackSvr * lpPackService = lpContext->GetF2PackSvr();
   	  IF2Packer * lpOutPack1 = lpPackService->GetPacker(1);
   	  lpOutPack1->BeginPack();
   	  PackResultSet(lpInUnPacker,lpOutPack1);
   	  lpOutPack1->EndPack();
      void * lpBizBuf = lpOutPack1->GetPackBuf();
      int iLen = lpOutPack1->GetPackLen();
         
   	  if (iIssueType > 0)
   	  {
   	     lpMsgReq->GetItem(TAG_ISSUE_TYPE)->SetInt(iIssueType);
   	     
         //ҵ���帴�Ƶ���Ϣ��
         lpMsgReq->GetItem(TAG_KEY_INFO)->SetRawData(lpBizBuf,iLen);
      }
      else
      {
         //ҵ���帴�Ƶ���Ϣ��
         lpMsgReq->GetItem(TAG_MESSAGE_BODY)->SetRawData(lpBizBuf,iLen);
      }
      
   	  if (isnull(trim(sTargetAr)) != 0)
   	     lpMsgReq->GetItem(TAG_ROUTE_INFO)->SetString(sTargetAr, IDX_OSPF_NAME);
   	  if (isnull(trim(sTransName)) != 0)
         lpMsgReq->GetItem(TAG_ROUTE_INFO)->SetString(sTransName, IDX_NBR_NAME);
      
      li_ReturnCode = lpContext->PostMsg(lpMsgReq);
      if (li_ReturnCode != 0)
      	 lpMsgReq->Release();
      
      if (lpOutPack1)
	  {
	  	free(lpOutPack1->GetPackBuf());
	  	lpOutPack1->Release();
	  }
      
   }
   else
   {
   	  //ϵͳ������Ϣ��AR����ת����AS���ܴ�������û��ҵ���壬˵������û���ύ
      hs_strcpy(sErrorInfo,"ϵͳæ���޷���ȡϵͳ��Ϣ��");
      li_ReturnCode = ERR_SYS_BUSI_GET_MESSAGE_FAIL;
   }
   
   return li_ReturnCode;
}


//ȡ�м��������ˮ��
int GetCancelSerialNo(IAS2Context * lpContext,char *sCancelSerialNo)
{
   IAS2TM * lpTransMonitor = NULL;
   
   lpContext->QueryInterface(SID_TM,(IKnown **) &lpTransMonitor); //ȡ��ǰ�����ĵ����������
   
   if(lpTransMonitor)
   {
      hs_strcpy(sCancelSerialNo, lpTransMonitor->BeginTrans());
      lpTransMonitor->EndTrans();
   }
   else
   {
   	  return -1;
   }
   
   return 0;
}

//У�����ݿ��������
int CheckDbLinkMethod(IConnection * lpConn,int iSqlcode)
{
   //SQLCODE = -28 and SQLCODE = -1012
   if ( (iSqlcode == ERR_CUREE_SESSION_IS_KILLED) || (iSqlcode == ERR_DB_NOT_LOGGED_ON) )
   {
     return -1;
   }
   //20100630 zhouwm �޸�SQLCODE <= -3100 and SQLCODE > -3133 �޸ĵ���:20100630020
   //SQLCODE <= -3100 and SQLCODE > -3133
   else if ((iSqlcode <= ERR_DB_COMMUNICATION_FAIL) && (iSqlcode > ERR_DB_STOP_END_ERR))
   {
   	  //���RAC�����л�ģʽ��Ϊselectģʽ�������ݿ�������Ҫ����
   	  if (lpConn->QueryInterface("com.hundsun.fbase.iconnection",NULL))
   	     if (lpConn->getServerType() != CNST_RACFAILMETHOD_SELECT)
   	  	   return -1;
   	  
   	  return 0;
   }
   //20100702 zhouwm �޸�iSqlcode <= -25401 && iSqlcode >= -25409 �޸ĵ���:20100702016
   //RACģʽ�£�ִ�й����У�������ӱ�ǿ�ƶϿ�����ʱ��Ҫrollback
   else if ((iSqlcode <= ERR_DB_NO_CONTINUE_FETCH) && (iSqlcode >= ERR_DB_FAILOVER_NETWORK_OPER_FAIL))
   {
   	  return -1;
   }
   else
   {
   	  return 0;
   }
}

///begin 20110415 ������ add, Ϊ�˻�����һ���µ��ӷ�����ú�������v1��v2�Ľ��������תΪv1�Ĵ�������ݷ��ͣ�����T1ͨ���������޸��漰����ҵ��ĵǼǱ���
//ͬ���ӷ�����ã������packΪ1.0
int SynCallSubServicePack1(IAS2Context * lpContext,IF2UnPacker * lpInUnPacker, IESBMessage ** lppAnsMessage,unsigned int iTimeOut,unsigned int dwFuncNo,unsigned int dwBranchNo,unsigned int dwSystemNo,unsigned int dwSubSystemNo)
{
   int iRet = -1;
   //��ȡ��ʱʱ��
   //20091226 zhouwm ��unsigned int�޸�Ϊint
   int li_TimeOut = iTimeOut;   
   int li_tmp = 0;
   //20091226 zhouwm ��unsigned int�޸�Ϊint
   int li_TimeOut1 = 0;  //��ͷ��ʱʱ��
   if (li_TimeOut <= 0)
      li_TimeOut = CNST_TIMEOUT_DEFAULT;
   
   //����һ��������Ϣ
   IESBMessageFactory * lpESBMessageFactory = lpContext->GetESBMsgFactory();
   if (lpESBMessageFactory)
   {
      IESBMessage * lpMsgReq =  lpESBMessageFactory->GetESBMsg();
      
      if (lpMsgReq)
      { 
         lpMsgReq->GetItem(TAG_PACKET_TYPE)->SetInt(REQUEST_PACKET);
         
         if (lpContext->GetOrgRequest()->IsExist(TAG_TIMESTAMP) > 0)
         	lpMsgReq->GetItem(TAG_TIMESTAMP)->SetStringAtTail("begin SynCallSubService");
         
         //��ͷ��ʱʱ�䣬max(��ͷ��ʱʱ��,ԭ�ӷ������ð�ͷʱ��)
         //20091212 ��ΰ�� [SynCallSubService]�޸ĳ�ʱʱ���ԭʼ���л�ȡ
         //li_TimeOut1 = lpMsgReq->GetItem(TAG_LIVE_TIME)->GetInt(TAG_LIVE_TIME);
         li_TimeOut1 = lpContext->GetOrgRequest()->GetItem(TAG_LIVE_TIME)->GetInt();
         
         //���ܺ�
         if (dwFuncNo > 0)
            lpMsgReq->GetItem(TAG_FUNCTION_ID)->SetInt(dwFuncNo);
         
         //��֧����
         if (dwBranchNo > 0)
            lpMsgReq->GetItem(TAG_BRANCH_NO)->SetInt(dwBranchNo);
         else
         {
         	 if ( lpContext->GetOrgRequest()->IsExist(TAG_BRANCH_NO) > 0 )
         	 {
         	    li_tmp = lpContext->GetOrgRequest()->GetItem(TAG_BRANCH_NO)->GetInt();
         	    lpMsgReq->GetItem(TAG_BRANCH_NO)->SetInt(li_tmp);
         	 }
         }
         
         //ϵͳ���
         if (dwSystemNo > 0)
            lpMsgReq->GetItem(TAG_SYSTEM_NO)->SetInt(dwSystemNo);
         else
         {
         	 if ( lpContext->GetOrgRequest()->IsExist(TAG_SYSTEM_NO) > 0 )
         	 {
         	    li_tmp = lpContext->GetOrgRequest()->GetItem(TAG_SYSTEM_NO)->GetInt();
         	    lpMsgReq->GetItem(TAG_SYSTEM_NO)->SetInt(li_tmp);
         	 }
         }
         	 
         //��ϵͳ���
         if (dwSubSystemNo > 0)
            lpMsgReq->GetItem(TAG_SUB_SYSTEM_NO)->SetInt(dwSubSystemNo);
         else
         {
         	 if ( lpContext->GetOrgRequest()->IsExist(TAG_SUB_SYSTEM_NO) > 0 )
         	 {
         	    li_tmp = lpContext->GetOrgRequest()->GetItem(TAG_SUB_SYSTEM_NO)->GetInt();
         	    lpMsgReq->GetItem(TAG_SUB_SYSTEM_NO)->SetInt(li_tmp);
         	 }
         }
         
         ///begin 20101222 ��Ԫ�� add, ���44��-- �ڲ����֤���
         //�ڲ����֤���
         if ( lpContext->GetOrgRequest()->IsExist(TAG_INTERNAL_LICENSE_NO) > 0 )
         {
            li_tmp = lpContext->GetOrgRequest()->GetItem(TAG_INTERNAL_LICENSE_NO)->GetInt();
            lpMsgReq->GetItem(TAG_INTERNAL_LICENSE_NO)->SetInt(li_tmp);
         }
         ///end 20101222 ��Ԫ�� add
         
         IF2PackSvr * lpPackService = lpContext->GetF2PackSvr();
         if(!lpPackService)
         	return -1;
     	 IF2Packer * lpFuncInPacker = lpPackService->GetPacker(1);
     	 if(!lpFuncInPacker)
     	 	return -1;
     	 lpFuncInPacker->BeginPack();
     	 PackResultSet(lpInUnPacker,lpFuncInPacker);
     	 lpFuncInPacker->EndPack();
     	 void * lpBizBuf = lpFuncInPacker->GetPackBuf();
     	 int iLen = lpFuncInPacker->GetPackLen();
			
         //ҵ���帴�Ƶ���Ϣ��
         lpMsgReq->GetItem(TAG_MESSAGE_BODY)->SetRawData( lpBizBuf,iLen );
         
         ///�ͷ������pack�ڴ�
         free(lpFuncInPacker->GetPackBuf());
		 lpFuncInPacker->Release();
         
         //�����ӷ���,����ʧ��ʱ��������Ϣ�ѱ��ͷ�
         //��ͷ��ʱʱ���ԭ�ӷ������õĳ�ʱʱ��ȡ��ֵ��max(��ͷ��ʱʱ��,ԭ�ӷ������ð�ͷʱ��)
         if (li_TimeOut1 > li_TimeOut)
         	iRet = lpContext->CallSubService(lpMsgReq,lppAnsMessage ,li_TimeOut1);
         else
         	iRet = lpContext->CallSubService(lpMsgReq,lppAnsMessage ,li_TimeOut);
      }
   }
   
   return  iRet;
}

//ԭ�ӷ��������չ
int SubServiceCallPack1(IAS2Context * lpContext,IF2UnPacker * lpInUnPacker, IF2Packer * lpOutPacker,unsigned int iTimeOut,unsigned int iFuncNo,unsigned int iBranchNo,unsigned int iSystemNo,unsigned int iSubSystemNo)
{
   int iReturnCode = 0;
   int iErrorNo = 0;
   int iErrorID = 0;
   int li_TimeOut = 0;
   char sErrorInfo[501]={0};
   char sErrorSysInfo[501]={0};
   char sErrorPathInfo[501]={0};
   
   hs_strncpy(sErrorPathInfo,conversion((char *)lpInUnPacker->GetStr("error_pathinfo")),500);
   hs_snprintf(sErrorPathInfo,500,"%s -> SubServiceCallPack1(%d)",sErrorPathInfo,iFuncNo);
   
   IESBMessageFactory * lpESBMessageFactory = lpContext->GetESBMsgFactory();
   IF2PackSvr * lpPackService = lpContext->GetF2PackSvr();
   int iSubRet = 0;

   //��ȡ��ʱʱ��
   li_TimeOut = iTimeOut;
   if (li_TimeOut <= 0)
      li_TimeOut = CNST_TIMEOUT_DEFAULT;
      
   IF2UnPacker * lpUnPack1 = NULL;
   IESBMessage * lpMsgA1 = NULL;
   iSubRet = SynCallSubServicePack1(lpContext,lpInUnPacker,&lpMsgA1,li_TimeOut,iFuncNo,iBranchNo,iSystemNo,iSubSystemNo);

   if ( iSubRet == 0 && lpMsgA1 )
   {
       int iBizRetcode = lpMsgA1->GetItem(TAG_RETURN_CODE)->GetInt(); //������
       //1����-1 ͨѶʧ��
       
       //��ҵ���巵��ҵ���壬ûҵ������ͨ����Ϣͷ�е�error_no,error_info,return_code������
       if   ( ( iBizRetcode == RT_ERR_PROCESS ) || ( iBizRetcode == RT_ERR_TRANSFER ) )
       {
          //ϵͳ������Ϣ��AR����ת����AS���ܴ�������û��ҵ���壬˵������û���ύ
          iErrorNo = ERR_SYSERR_AR_NOTRANS_AS_NOPROC;
          iErrorID = iBizRetcode;
          if (iBizRetcode == RT_ERR_TRANSFER)
          {
             hs_snprintf(sErrorInfo,500,"·�ɲ���ת��[%s],��������Ϣ = [%s] ���ID = [%s] �ڵ��� = [%d] ��ϵͳ��� = [%d]",
                               lpMsgA1->GetItem(TAG_ERROR_INFO)->GetString(),
                               lpMsgA1->GetItem(TAG_SENDER_PATH)->GetString(IDX_OSPF_NAME),
                               lpMsgA1->GetItem(TAG_SENDER_PATH)->GetString(IDX_PLUGIN_ID),iSystemNo,iSubSystemNo);
          
          }   
          else
             hs_strcpy(sErrorInfo,lpMsgA1->GetItem(TAG_ERROR_INFO)->GetString());
          
          hs_snprintf(sErrorSysInfo,500,"SubServiceCallPack1����[%d]ʧ��(retcode[%d],�ڵ���[%d],��ϵͳ���[%d])",iFuncNo,iBizRetcode,iSystemNo,iSubSystemNo);
          
          iReturnCode = SystemErrorPacker(lpOutPacker,sErrorPathInfo,iErrorNo,sErrorInfo);
          WriteSystemLog(lpContext,sErrorPathInfo,iErrorNo,sErrorInfo,iErrorID,sErrorSysInfo);
       }
       else
       {
          int iAnsLen = 0;
       
          void * lpAnsBuf =(void *) lpMsgA1->GetItem(TAG_MESSAGE_BODY)->GetRawData( &iAnsLen ); //�ڴ���msg�ͷ�
          
          if ( lpAnsBuf && (iAnsLen>0) )
          {
             lpUnPack1 = lpPackService->GetUnPacker(lpAnsBuf,iAnsLen);
             if (lpUnPack1)
             {
                //ҵ��ɹ���ҵ�����
                PackResultSet(lpUnPack1,lpOutPacker);
                lpUnPack1->Release();
                
                iReturnCode = iBizRetcode;
             }
             else
             {
             	//ϵͳ������Ϣ��AR����ת����AS���ܴ�������û��ҵ���壬˵������û���ύ
                iErrorNo = ERR_EXEC_BUSIPACK_ISNULL;
                iErrorID = RT_ERR_PROCESS;
                hs_snprintf(sErrorInfo,500,"ҵ���Ϊ��[���ܺ�[%d] �ڵ���[%d] ��ϵͳ���[%d]]",iFuncNo,iSystemNo,iSubSystemNo);
                hs_snprintf(sErrorSysInfo,500,"SubServiceCallPack1����[%d]ʧ��(retcode[%d],�ڵ���[%d],��ϵͳ���[%d])",iFuncNo,RT_ERR_PROCESS,iSystemNo,iSubSystemNo);
                
                iReturnCode = SystemErrorPacker(lpOutPacker,sErrorPathInfo,iErrorNo,sErrorInfo);
                WriteSystemLog(lpContext,sErrorPathInfo,iErrorNo,sErrorInfo,iErrorID,sErrorSysInfo);
                iReturnCode = iErrorNo;
             }
          }
          else
          {
          	 //ϵͳ������Ϣ��AR����ת����AS���ܴ�������û��ҵ���壬˵������û���ύ
             iErrorNo = ERR_EXEC_BUSIPACK_ISNULL;
             iErrorID = RT_ERR_PROCESS;
             hs_snprintf(sErrorInfo,500,"ҵ���Ϊ��[���ܺ�[%d] �ڵ���[%d] ��ϵͳ���[%d]]",iFuncNo,iSystemNo,iSubSystemNo);
             hs_snprintf(sErrorSysInfo,500,"SubServiceCallPack1����[%d]ʧ��(retcode[%d],�ڵ���[%d],��ϵͳ���[%d])",iFuncNo,RT_ERR_PROCESS,iSystemNo,iSubSystemNo);
             
             iReturnCode = SystemErrorPacker(lpOutPacker,sErrorPathInfo,iErrorNo,sErrorInfo);
             WriteSystemLog(lpContext,sErrorPathInfo,iErrorNo,sErrorInfo,iErrorID,sErrorSysInfo);
             iReturnCode = iErrorNo;
          }
       }
       
	   lpMsgA1->Release();
   }
   else
   {
       //����ʧ�ܻ�û�յ�Ӧ����Ϣ����ʱ��
   	   if ( iSubRet == -2)
   	   {
   	   	  //��ʱ����(���׿��ܳɹ�������ʧ��)��Ҫ��¼
          iErrorNo = ERR_SUBSERVICE_CALL_TIMEOUT;
          iErrorID = iSubRet;
          hs_snprintf(sErrorInfo,500,"ҵ�������У����Ժ����Ƿ�ɹ�[���ܺ�[%d] �ڵ���[%d] ��ϵͳ���[%d]]",iFuncNo,iSystemNo,iSubSystemNo);
          //��������¹��ܿ����ѱ����õ�,��Ҫ����
   	      hs_snprintf(sErrorSysInfo,500,"SubServiceCallPack1����[%d]ʧ��(��ʱ[%d],�ڵ���[%d],��ϵͳ���[%d])",iFuncNo,iSubRet,iSystemNo,iSubSystemNo);
   	   }
   	   else
   	   {
   	   	  //ϵͳ���ô���(���׿϶�û�ύ),���������е��״ν��׵��ò��ؼ�¼
   	      iErrorNo = ERR_SUBSERVICE_CALL_FAIL;
          iErrorID = iSubRet;
          hs_snprintf(sErrorInfo,500,"�ӷ������ʧ��[���ܺ�[%d] �ڵ���[%d] ��ϵͳ���[%d]]",iFuncNo,iSystemNo,iSubSystemNo);
          hs_snprintf(sErrorSysInfo,500,"SubServiceCallPack1����[%d]ʧ��(����[%d],�ڵ���[%d],��ϵͳ���[%d])",iFuncNo,iSubRet,iSystemNo,iSubSystemNo);
   	   }
   	   iReturnCode = SystemErrorPacker(lpOutPacker,sErrorPathInfo,iErrorNo,sErrorInfo);
       WriteSystemLog(lpContext,sErrorPathInfo,iErrorNo,sErrorInfo,iErrorID,sErrorSysInfo);
   }

   return iReturnCode;
}
///end 20110415 ������ add, Ϊ�˻�����һ���µ��ӷ�����ú�������v1��v2�Ľ��������תΪv1�Ĵ�������ݷ��ͣ�����T1ͨ���������޸��漰����ҵ��ĵǼǱ���
