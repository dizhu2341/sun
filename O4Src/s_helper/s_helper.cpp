/*
 * Program: s_helper.cpp
 * Author : 周伟明.
 * Date   : 2008/10/14.
 * Notes  : 工具函数实现
 * Modify : 版本       修改日期   修改人         修改单       修改说明
 *          V8.0.6.0   20100614   刘元召         内部         经纪业务运营平台V2.0项目2011基线建立
 *          V8.0.5.4   20110415   王仁云         20110415019  增加函数SynCallSubServicePack1和SubServiceCallPack1
 *          V8.0.5.3   20101222   刘元召         20101221012  函数【SynCallSubService】添加44域[TAG_INTERNAL_LICENSE_NO]-- 内部许可证编号,逻辑调用逻辑时许可证检查用
 *                                                            函数【GetLibVersion】修改版本为V8.0.5.3
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

#include "s_helper.h"
#include <Include/log_interface.h>

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
char *  FUNCTION_CALL_MODE GetLibVersion( )
{
	///20110415 王仁云 版本从V8.0.5.3修改为V8.0.5.4
    //20101222 liuyz  版本从V8.0.5.2修改V8.0.5.3
    //20100702 zhouwm 版本从V8.0.5.1修改V8.0.5.2
    //20100630 zhouwm 版本从V8.0.5.0修改V8.0.5.1
    return "V9.0.2.0";
}
#endif


/*==========================================================
 * Function   : PackResultSet
 * Description: 结果集打包输出
 * Input      : IF2ResultSet * lpInUnPacker 结果集
 * Output     : IF2Packer * lpOutPacker     输出
 * Return     : 0       成功
 *              <>0     失败
 * Author     : zhouwm
 * Date       : 2008/10/20.
 ==========================================================*/
int PackResultSet(IF2ResultSet * lpInUnPacker,IF2Packer * lpOutPacker)
{
  int iRet=0;
  const char * pBuff;
  int iCount;
  int iCols =0; //字段数
  char sErrorPathInfo[501]={0};

  if ((lpInUnPacker) && (lpOutPacker))
  {
     hs_strncpy(sErrorPathInfo,conversion((char *)lpInUnPacker->GetStr("error_pathinfo")),500);
     iCols = lpInUnPacker->GetColCount(); //取字段数

     //添加应答包字段信息
     for (iCount=0;iCount<iCols;iCount++)
     {
       lpOutPacker->AddField( lpInUnPacker->GetColName(iCount),
       lpInUnPacker->GetColType(iCount),
       lpInUnPacker->GetColWidth(iCount),
       lpInUnPacker->GetColScale(iCount));
     }

       //将请求包记录和字段，逐个添加到应答包
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
          	pBuff = lpInUnPacker->GetStrByIndex(iCount);//取当前字段
            lpOutPacker->AddStr(pBuff); //添加到应答包
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
    lpOutPacker->AddStr("打包结果集为空");
  }

  return iRet;

}

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



//同步子服务调用
int SynCallSubService(IAS2Context * lpContext,IF2UnPacker * lpInUnPacker, IESBMessage ** lppAnsMessage,unsigned int iTimeOut,unsigned int dwFuncNo,unsigned int dwBranchNo,unsigned int dwSystemNo,unsigned int dwSubSystemNo)
{
   int iRet = -1;
   //获取超时时间
   //20091226 zhouwm 从unsigned int修改为int
   int li_TimeOut = iTimeOut;   
   int li_tmp = 0;
   //20091226 zhouwm 从unsigned int修改为int
   int li_TimeOut1 = 0;  //包头超时时间
   if (li_TimeOut <= 0)
      li_TimeOut = CNST_TIMEOUT_DEFAULT;
   
   //创建一个请求消息
   IESBMessageFactory * lpESBMessageFactory = lpContext->GetESBMsgFactory();
   if (lpESBMessageFactory)
   {
      IESBMessage * lpMsgReq =  lpESBMessageFactory->GetESBMsg();
      
      if (lpMsgReq)
      { 
         lpMsgReq->GetItem(TAG_PACKET_TYPE)->SetInt(REQUEST_PACKET);
         
         if (lpContext->GetOrgRequest()->IsExist(TAG_TIMESTAMP) > 0)
         	lpMsgReq->GetItem(TAG_TIMESTAMP)->SetStringAtTail("begin SynCallSubService");
         
         //包头超时时间，max(包头超时时间,原子服务设置包头时间)
         //20091212 周伟明 [SynCallSubService]修改超时时间从原始包中获取
         //li_TimeOut1 = lpMsgReq->GetItem(TAG_LIVE_TIME)->GetInt(TAG_LIVE_TIME);
         li_TimeOut1 = lpContext->GetOrgRequest()->GetItem(TAG_LIVE_TIME)->GetInt();
         
         //功能号
         if (dwFuncNo > 0)
            lpMsgReq->GetItem(TAG_FUNCTION_ID)->SetInt(dwFuncNo);
         
         //分支代码
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
         
         //系统编号
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
         	 
         //子系统编号
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
         
         ///begin 20101222 刘元召 add, 添加44域-- 内部许可证编号
         //内部许可证编号
         if ( lpContext->GetOrgRequest()->IsExist(TAG_INTERNAL_LICENSE_NO) > 0 )
         {
            li_tmp = lpContext->GetOrgRequest()->GetItem(TAG_INTERNAL_LICENSE_NO)->GetInt();
            lpMsgReq->GetItem(TAG_INTERNAL_LICENSE_NO)->SetInt(li_tmp);
         }
         ///end 20101222 刘元召 add
         
         //取业务体
         void * lpBizBuf = lpInUnPacker->GetPackBuf();
         int iLen = lpInUnPacker->GetPackLen();
         //业务体复制到消息中
         lpMsgReq->GetItem(TAG_MESSAGE_BODY)->SetRawData( lpBizBuf,iLen );
         
         //调用子服务,发送失败时，请求消息已被释放
         //包头超时时间和原子服务设置的超时时间取大值，max(包头超时时间,原子服务设置包头时间)
         if (li_TimeOut1 > li_TimeOut)
         	iRet = lpContext->CallSubService(lpMsgReq,lppAnsMessage ,li_TimeOut1);
         else
         	iRet = lpContext->CallSubService(lpMsgReq,lppAnsMessage ,li_TimeOut);
      }
   }
   
   return  iRet;
}

//原子服务调用扩展
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

   //获取超时时间
   li_TimeOut = iTimeOut;
   if (li_TimeOut <= 0)
      li_TimeOut = CNST_TIMEOUT_DEFAULT;
      
   IF2UnPacker * lpUnPack1 = NULL;
   IESBMessage * lpMsgA1 = NULL;
   iSubRet = SynCallSubService(lpContext,lpInUnPacker,&lpMsgA1,li_TimeOut,iFuncNo,iBranchNo,iSystemNo,iSubSystemNo);

   if ( iSubRet == 0 && lpMsgA1 )
   {
       int iBizRetcode = lpMsgA1->GetItem(TAG_RETURN_CODE)->GetInt(); //返回码
       //1或者-1 通讯失败
       
       //有业务体返回业务体，没业务体则通过消息头中的error_no,error_info,return_code来返回
       if   ( ( iBizRetcode == RT_ERR_PROCESS ) || ( iBizRetcode == RT_ERR_TRANSFER ) )
       {
          //系统错误消息（AR不能转发，AS不能处理）可能没有业务体，说明交易没有提交
          iErrorNo = ERR_SYSERR_AR_NOTRANS_AS_NOPROC;
          iErrorID = iBizRetcode;
          if (iBizRetcode == RT_ERR_TRANSFER)
          {
             hs_snprintf(sErrorInfo,500,"路由不能转发[%s],发送者信息 = [%s] 插件ID = [%s] 节点编号 = [%d] 子系统编号 = [%d]",
                               lpMsgA1->GetItem(TAG_ERROR_INFO)->GetString(),
                               lpMsgA1->GetItem(TAG_SENDER_PATH)->GetString(IDX_OSPF_NAME),
                               lpMsgA1->GetItem(TAG_SENDER_PATH)->GetString(IDX_PLUGIN_ID),iSystemNo,iSubSystemNo);
          
          }   
          else
             hs_strcpy(sErrorInfo,lpMsgA1->GetItem(TAG_ERROR_INFO)->GetString());
          
          hs_snprintf(sErrorSysInfo,500,"SubServiceCall调用[%d]失败(retcode[%d],节点编号[%d],子系统编号[%d])",iFuncNo,iBizRetcode,iSystemNo,iSubSystemNo);
          
          iReturnCode = SystemErrorPacker(lpOutPacker,sErrorPathInfo,iErrorNo,sErrorInfo);
          WriteSystemLog(lpContext,sErrorPathInfo,iErrorNo,sErrorInfo,iErrorID,sErrorSysInfo);
       }
       else
       {
          int iAnsLen = 0;
       
          void * lpAnsBuf =(void *) lpMsgA1->GetItem(TAG_MESSAGE_BODY)->GetRawData( &iAnsLen ); //内存由msg释放
          
          if ( lpAnsBuf && (iAnsLen>0) )
          {
             lpUnPack1 = lpPackService->GetUnPacker(lpAnsBuf,iAnsLen);
             if (lpUnPack1)
             {
                //业务成功或业务错误
                PackResultSet(lpUnPack1,lpOutPacker);
                lpUnPack1->Release();
                
                iReturnCode = iBizRetcode;
             }
             else
             {
             	//系统错误消息（AR不能转发，AS不能处理）可能没有业务体，说明交易没有提交
                iErrorNo = ERR_EXEC_BUSIPACK_ISNULL;
                iErrorID = RT_ERR_PROCESS;
                hs_snprintf(sErrorInfo,500,"业务包为空[功能号[%d] 节点编号[%d] 子系统编号[%d]]",iFuncNo,iSystemNo,iSubSystemNo);
                hs_snprintf(sErrorSysInfo,500,"SubServiceCall调用[%d]失败(retcode[%d],节点编号[%d],子系统编号[%d])",iFuncNo,RT_ERR_PROCESS,iSystemNo,iSubSystemNo);
                
                iReturnCode = SystemErrorPacker(lpOutPacker,sErrorPathInfo,iErrorNo,sErrorInfo);
                WriteSystemLog(lpContext,sErrorPathInfo,iErrorNo,sErrorInfo,iErrorID,sErrorSysInfo);
                iReturnCode = iErrorNo;
             }
          }
          else
          {
          	 //系统错误消息（AR不能转发，AS不能处理）可能没有业务体，说明交易没有提交
             iErrorNo = ERR_EXEC_BUSIPACK_ISNULL;
             iErrorID = RT_ERR_PROCESS;
             hs_snprintf(sErrorInfo,500,"业务包为空[功能号[%d] 节点编号[%d] 子系统编号[%d]]",iFuncNo,iSystemNo,iSubSystemNo);
             hs_snprintf(sErrorSysInfo,500,"SubServiceCall调用[%d]失败(retcode[%d],节点编号[%d],子系统编号[%d])",iFuncNo,RT_ERR_PROCESS,iSystemNo,iSubSystemNo);
             
             iReturnCode = SystemErrorPacker(lpOutPacker,sErrorPathInfo,iErrorNo,sErrorInfo);
             WriteSystemLog(lpContext,sErrorPathInfo,iErrorNo,sErrorInfo,iErrorID,sErrorSysInfo);
             iReturnCode = iErrorNo;
          }
       }
       
	   lpMsgA1->Release();
   }
   else
   {
       //调用失败或没收到应答消息（超时）
   	   if ( iSubRet == -2)
   	   {
   	   	  //超时错误(交易可能成功，可能失败)，要记录
          iErrorNo = ERR_SUBSERVICE_CALL_TIMEOUT;
          iErrorID = iSubRet;
          hs_snprintf(sErrorInfo,500,"业务受理中，请稍后检查是否成功[功能号[%d] 节点编号[%d] 子系统编号[%d]]",iFuncNo,iSystemNo,iSubSystemNo);
          //这种情况下功能可能已被调用到,需要冲正
   	      hs_snprintf(sErrorSysInfo,500,"SubServiceCall调用[%d]失败(超时[%d],节点编号[%d],子系统编号[%d])",iFuncNo,iSubRet,iSystemNo,iSubSystemNo);
   	   }
   	   else
   	   {
   	   	  //系统调用错误(交易肯定没提交),对于事务中的首次交易调用不必记录
   	      iErrorNo = ERR_SUBSERVICE_CALL_FAIL;
          iErrorID = iSubRet;
          hs_snprintf(sErrorInfo,500,"子服务调用失败[功能号[%d] 节点编号[%d] 子系统编号[%d]]",iFuncNo,iSystemNo,iSubSystemNo);
          hs_snprintf(sErrorSysInfo,500,"SubServiceCall调用[%d]失败(发送[%d],节点编号[%d],子系统编号[%d])",iFuncNo,iSubRet,iSystemNo,iSubSystemNo);
   	   }
   	   iReturnCode = SystemErrorPacker(lpOutPacker,sErrorPathInfo,iErrorNo,sErrorInfo);
       WriteSystemLog(lpContext,sErrorPathInfo,iErrorNo,sErrorInfo,iErrorID,sErrorSysInfo);
   }

   return iReturnCode;
}

//事务原子服务调用扩展
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
   
   //获取超时时间
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
           //调用成功，并收到应答消息
           int iBizRetcode = lpMsgA1->GetItem(TAG_RETURN_CODE)->GetInt(); //返回码

           if   ( ( iBizRetcode == RT_ERR_PROCESS ) || ( iBizRetcode == RT_ERR_TRANSFER ) )
           {
               //系统错误消息（AR不能转发，AS不能处理）可能没有业务体，说明交易没有提交
               iErrorNo = ERR_SYSERR_AR_NOTRANS_AS_NOPROC;
               iErrorID = iBizRetcode;
               if (iBizRetcode == RT_ERR_TRANSFER)
               {
                  hs_snprintf(sErrorInfo,500,"路由不能转发[%s],发送者信息 = [%s] 插件ID = [%s] 节点编号 = [%d] 子系统编号 = [%d]",
                                    lpMsgA1->GetItem(TAG_ERROR_INFO)->GetString(),
                                    lpMsgA1->GetItem(TAG_SENDER_PATH)->GetString(IDX_OSPF_NAME),
                                    lpMsgA1->GetItem(TAG_SENDER_PATH)->GetString(IDX_PLUGIN_ID),iSystemNo,iSubSystemNo);
               
               }   
               else
                  hs_strcpy(sErrorInfo,lpMsgA1->GetItem(TAG_ERROR_INFO)->GetString());
                  
               hs_snprintf(sErrorSysInfo,500,"SubServiceCall调用[%d]失败(retcode[%d],节点编号[%d],子系统编号[%d])",iFuncNo,iBizRetcode,iSystemNo,iSubSystemNo);
               //20091027 周伟明 调用子服务异常时候Proc插件不做异常数据库记录
               //if ( lpTransMonitor->GetCommitNum() != 0 )
               //	  lpTransMonitor->Assert();

               iReturnCode = SystemErrorPacker(lpOutPacker,sErrorPathInfo,iErrorNo,sErrorInfo);
               WriteSystemLog(lpContext,sErrorPathInfo,iErrorNo,sErrorInfo,iErrorID,sErrorSysInfo);
           }
           else
           {
               int iAnsLen = 0;
               void * lpAnsBuf =(void *) lpMsgA1->GetItem(TAG_MESSAGE_BODY)->GetRawData( &iAnsLen ); //内存由msg释放
               if ( lpAnsBuf && (iAnsLen>0) )
               {
                   lpUnPack1 = lpPackService->GetUnPacker(lpAnsBuf,iAnsLen);
              
                   if (lpUnPack1)
                   {
                       //业务成功或业务错误
                       if  ( iBizRetcode == RT_ERR_NONE )
                       {
                           //业务处理成功
                           PackResultSet(lpUnPack1,lpOutPacker);
                           lpUnPack1->Release();
                       }
                       else
                       {
                           //20091027 周伟明 调用子服务异常时候Proc插件不做异常数据库记录
                           //业务处理失败,,对于事务中的首次交易调用不必记录
                           //if ( lpTransMonitor->GetCommitNum() != 0 )
                           //	  lpTransMonitor->Assert();
                           
                           PackResultSet(lpUnPack1,lpOutPacker);
                           lpUnPack1->Release();
                       }
                       iReturnCode = iBizRetcode;
                   }
                   else
                   {
                   	   //20091027 周伟明 调用子服务异常时候Proc插件不做异常数据库记录
                   	   //业务处理失败,,对于事务中的首次交易调用不必记录
                       //if ( lpTransMonitor->GetCommitNum() != 0 )
                   	   //   lpTransMonitor->Assert();
                   	   
                   	   //系统错误消息（AR不能转发，AS不能处理）可能没有业务体，说明交易没有提交
                       iErrorNo = ERR_EXEC_BUSIPACK_ISNULL;
                       iErrorID = RT_ERR_PROCESS;
                       hs_snprintf(sErrorInfo,500,"业务包为空[功能号[%d] 节点编号[%d] 子系统编号[%d]]",iFuncNo,iSystemNo,iSubSystemNo);
                       hs_snprintf(sErrorSysInfo,500,"SubServiceCall调用[%d]失败(retcode[%d],节点编号[%d],子系统编号[%d])",iFuncNo,RT_ERR_PROCESS,iSystemNo,iSubSystemNo);
                       iReturnCode = SystemErrorPacker(lpOutPacker,sErrorPathInfo,iErrorNo,sErrorInfo);
                       WriteSystemLog(lpContext,sErrorPathInfo,iErrorNo,sErrorInfo,iErrorID,sErrorSysInfo);
                       iReturnCode = iErrorNo;
                   }
               }
               else
               {
               	   //20091027 周伟明 调用子服务异常时候Proc插件不做异常数据库记录
               	   //业务处理失败,,对于事务中的首次交易调用不必记录
                   //if ( lpTransMonitor->GetCommitNum() != 0 )
                   //	  lpTransMonitor->Assert();
                   
                   //系统错误消息（AR不能转发，AS不能处理）可能没有业务体，说明交易没有提交
                   iErrorNo = ERR_EXEC_BUSIPACK_ISNULL;
                   iErrorID = RT_ERR_PROCESS;
                   hs_snprintf(sErrorInfo,500,"业务包为空[功能号[%d] 节点编号[%d] 子系统编号[%d]]",iFuncNo,iSystemNo,iSubSystemNo);
                   hs_snprintf(sErrorSysInfo,500,"SubServiceCall调用[%d]失败(retcode[%d],节点编号[%d],子系统编号[%d])",iFuncNo,RT_ERR_PROCESS,iSystemNo,iSubSystemNo);
                   iReturnCode = SystemErrorPacker(lpOutPacker,sErrorPathInfo,iErrorNo,sErrorInfo);
                   WriteSystemLog(lpContext,sErrorPathInfo,iErrorNo,sErrorInfo,iErrorID,sErrorSysInfo);
                   iReturnCode = iErrorNo;
               }
               
           }
           
           lpMsgA1->Release();
       }
       else
       {
           //调用失败或没收到应答消息（超时）
           if ( iSubRet == -2)
           {
               //超时错误(交易可能成功，可能失败)，要记录
               iErrorNo = ERR_SUBSERVICE_CALL_TIMEOUT;
               iErrorID = iSubRet;
               hs_snprintf(sErrorInfo,500,"子服务调用超时[功能号[%d] 节点编号[%d] 子系统编号[%d]]",iFuncNo,iSystemNo,iSubSystemNo);
               //这种情况下功能可能已被调用到,需要冲正
   	           hs_snprintf(sErrorSysInfo,500,"SubServiceCall调用[%d]失败(超时[%d],节点编号[%d],子系统编号[%d])",iFuncNo,iSubRet,iSystemNo,iSubSystemNo);
               
               //20091027 周伟明 调用子服务异常时候Proc插件不做异常数据库记录
               //这种情况下功能可能已被调用到,需要冲正
               //lpTransMonitor->Assert();
           }
           else
           {
               //系统调用错误(交易肯定没提交),对于事务中的首s次交易调用不必记录
   	           iErrorNo = ERR_SUBSERVICE_CALL_FAIL;
               iErrorID = iSubRet;
               hs_snprintf(sErrorInfo,500,"子服务调用失败[功能号[%d] 节点编号[%d] 子系统编号[%d]]",iFuncNo,iSystemNo,iSubSystemNo);
   	           hs_snprintf(sErrorSysInfo,500,"SubServiceCall调用[%d]失败(发送[%d],节点编号[%d],子系统编号[%d])",iFuncNo,iSubRet,iSystemNo,iSubSystemNo);
   	           
   	           //20091027 周伟明 调用子服务异常时候Proc插件不做异常数据库记录
               //if ( lpTransMonitor->GetCommitNum() != 0 )
               //	  lpTransMonitor->Assert();

           }
           //返回系统错误信息
           iReturnCode = SystemErrorPacker(lpOutPacker,sErrorPathInfo,iErrorNo,sErrorInfo);
           WriteSystemLog(lpContext,sErrorPathInfo,iErrorNo,sErrorInfo,iErrorID,sErrorSysInfo);
       }
   }
   return iReturnCode;
}

//错误信息打包输出
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

//记录系统日志
//记录到中间件*operation.biz，二进制文件*operation.bin
int WriteSystemLog(IAS2Context * lpContext,char *sError_PathInfo,int iError_no,char *sError_Info,int iError_id,char *sError_SysInfo)
{
   //char sErrorInfo[2001]={0};
   
   //printf("\n执行路径: [%s]\n错误号: [%d]\n错误信息: [%s]\n系统错误号: [%d]\n系统错误信息: [%s]\n",sError_PathInfo,iError_no,sError_Info,iError_id,sError_SysInfo);
   if (iError_id == 0)
   	  return 0;
   
   //记录buffer信息
   static ILogService * lpLog = NULL;
   
   if (!lpLog) lpContext->QueryInterface(SID_BIZLOG,(IKnown **)&lpLog);
   
   if (lpLog)
   {
      IESBMessage * lpESBMessage = lpContext->GetOrgRequest();
      //hs_snprintf(sErrorInfo,2000,"错误号: [%d],错误信息: [%s],系统错误号: [%d],系统错误信息: [%s]",iError_no,sError_Info,iError_id,sError_SysInfo);
      
      lpLog->AddBizLog(lpESBMessage,sError_PathInfo,iError_no,sError_Info,iError_id,sError_SysInfo);
   }
   else
   {
      printf("\n执行路径: [%s]\n错误号: [%d]\n错误信息: [%s]\n系统错误号: [%d]\n系统错误信息: [%s]\n",sError_PathInfo,iError_no,sError_Info,iError_id,sError_SysInfo);
   }
   
   return 0;
}

//记录时间戳
int WriteTimeStamp(IAS2Context * lpContext,char *sWriteSysInfo)
{
   IESBMessage * lpMessage = lpContext->GetOrgRequest();
   
   lpMessage->AddTimeStamp(sWriteSysInfo);

   return 0;
}

//异步发生消息（2.0包发送）
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
   	  
   	  //取业务体
      void * lpBizBuf = lpInUnPacker->GetPackBuf();
      int iLen = lpInUnPacker->GetPackLen();
         
   	  if (iIssueType > 0)
   	  {
   	     lpMsgReq->GetItem(TAG_ISSUE_TYPE)->SetInt(iIssueType);
   	     
         //业务体复制到消息中
         lpMsgReq->GetItem(TAG_KEY_INFO)->SetRawData(lpBizBuf,iLen);
      }
      else
      {
         //业务体复制到消息中
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
   	  //系统错误消息（AR不能转发，AS不能处理）可能没有业务体，说明交易没有提交
      hs_strcpy(sErrorInfo,"系统忙（无法获取系统消息）");
      li_ReturnCode = ERR_SYS_BUSI_GET_MESSAGE_FAIL;
   }
   
   
   
   return li_ReturnCode;
}

//异步发生消息（2.0包转成1.0包再发送）
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
   	  
   	  //取业务体
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
   	     
         //业务体复制到消息中
         lpMsgReq->GetItem(TAG_KEY_INFO)->SetRawData(lpBizBuf,iLen);
      }
      else
      {
         //业务体复制到消息中
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
   	  //系统错误消息（AR不能转发，AS不能处理）可能没有业务体，说明交易没有提交
      hs_strcpy(sErrorInfo,"系统忙（无法获取系统消息）");
      li_ReturnCode = ERR_SYS_BUSI_GET_MESSAGE_FAIL;
   }
   
   return li_ReturnCode;
}


//取中间件冲销流水号
int GetCancelSerialNo(IAS2Context * lpContext,char *sCancelSerialNo)
{
   IAS2TM * lpTransMonitor = NULL;
   
   lpContext->QueryInterface(SID_TM,(IKnown **) &lpTransMonitor); //取当前上下文的事务监视器
   
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

//校验数据库连接情况
int CheckDbLinkMethod(IConnection * lpConn,int iSqlcode)
{
   //SQLCODE = -28 and SQLCODE = -1012
   if ( (iSqlcode == ERR_CUREE_SESSION_IS_KILLED) || (iSqlcode == ERR_DB_NOT_LOGGED_ON) )
   {
     return -1;
   }
   //20100630 zhouwm 修改SQLCODE <= -3100 and SQLCODE > -3133 修改单号:20100630020
   //SQLCODE <= -3100 and SQLCODE > -3133
   else if ((iSqlcode <= ERR_DB_COMMUNICATION_FAIL) && (iSqlcode > ERR_DB_STOP_END_ERR))
   {
   	  //如果RAC连接切换模式不为select模式，则数据库连接需要重连
   	  if (lpConn->QueryInterface("com.hundsun.fbase.iconnection",NULL))
   	     if (lpConn->getServerType() != CNST_RACFAILMETHOD_SELECT)
   	  	   return -1;
   	  
   	  return 0;
   }
   //20100702 zhouwm 修改iSqlcode <= -25401 && iSqlcode >= -25409 修改单号:20100702016
   //RAC模式下，执行过程中，如果连接被强制断开，此时需要rollback
   else if ((iSqlcode <= ERR_DB_NO_CONTINUE_FETCH) && (iSqlcode >= ERR_DB_FAILOVER_NETWORK_OPER_FAIL))
   {
   	  return -1;
   }
   else
   {
   	  return 0;
   }
}

///begin 20110415 王仁云 add, 为账户增加一个新的子服务调用函数，把v1或v2的解包器内容转为v1的打包器内容发送（用于T1通道）。此修改涉及到创业板的登记报送
//同步子服务调用，输出的pack为1.0
int SynCallSubServicePack1(IAS2Context * lpContext,IF2UnPacker * lpInUnPacker, IESBMessage ** lppAnsMessage,unsigned int iTimeOut,unsigned int dwFuncNo,unsigned int dwBranchNo,unsigned int dwSystemNo,unsigned int dwSubSystemNo)
{
   int iRet = -1;
   //获取超时时间
   //20091226 zhouwm 从unsigned int修改为int
   int li_TimeOut = iTimeOut;   
   int li_tmp = 0;
   //20091226 zhouwm 从unsigned int修改为int
   int li_TimeOut1 = 0;  //包头超时时间
   if (li_TimeOut <= 0)
      li_TimeOut = CNST_TIMEOUT_DEFAULT;
   
   //创建一个请求消息
   IESBMessageFactory * lpESBMessageFactory = lpContext->GetESBMsgFactory();
   if (lpESBMessageFactory)
   {
      IESBMessage * lpMsgReq =  lpESBMessageFactory->GetESBMsg();
      
      if (lpMsgReq)
      { 
         lpMsgReq->GetItem(TAG_PACKET_TYPE)->SetInt(REQUEST_PACKET);
         
         if (lpContext->GetOrgRequest()->IsExist(TAG_TIMESTAMP) > 0)
         	lpMsgReq->GetItem(TAG_TIMESTAMP)->SetStringAtTail("begin SynCallSubService");
         
         //包头超时时间，max(包头超时时间,原子服务设置包头时间)
         //20091212 周伟明 [SynCallSubService]修改超时时间从原始包中获取
         //li_TimeOut1 = lpMsgReq->GetItem(TAG_LIVE_TIME)->GetInt(TAG_LIVE_TIME);
         li_TimeOut1 = lpContext->GetOrgRequest()->GetItem(TAG_LIVE_TIME)->GetInt();
         
         //功能号
         if (dwFuncNo > 0)
            lpMsgReq->GetItem(TAG_FUNCTION_ID)->SetInt(dwFuncNo);
         
         //分支代码
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
         
         //系统编号
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
         	 
         //子系统编号
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
         
         ///begin 20101222 刘元召 add, 添加44域-- 内部许可证编号
         //内部许可证编号
         if ( lpContext->GetOrgRequest()->IsExist(TAG_INTERNAL_LICENSE_NO) > 0 )
         {
            li_tmp = lpContext->GetOrgRequest()->GetItem(TAG_INTERNAL_LICENSE_NO)->GetInt();
            lpMsgReq->GetItem(TAG_INTERNAL_LICENSE_NO)->SetInt(li_tmp);
         }
         ///end 20101222 刘元召 add
         
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
			
         //业务体复制到消息中
         lpMsgReq->GetItem(TAG_MESSAGE_BODY)->SetRawData( lpBizBuf,iLen );
         
         ///释放申请的pack内存
         free(lpFuncInPacker->GetPackBuf());
		 lpFuncInPacker->Release();
         
         //调用子服务,发送失败时，请求消息已被释放
         //包头超时时间和原子服务设置的超时时间取大值，max(包头超时时间,原子服务设置包头时间)
         if (li_TimeOut1 > li_TimeOut)
         	iRet = lpContext->CallSubService(lpMsgReq,lppAnsMessage ,li_TimeOut1);
         else
         	iRet = lpContext->CallSubService(lpMsgReq,lppAnsMessage ,li_TimeOut);
      }
   }
   
   return  iRet;
}

//原子服务调用扩展
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

   //获取超时时间
   li_TimeOut = iTimeOut;
   if (li_TimeOut <= 0)
      li_TimeOut = CNST_TIMEOUT_DEFAULT;
      
   IF2UnPacker * lpUnPack1 = NULL;
   IESBMessage * lpMsgA1 = NULL;
   iSubRet = SynCallSubServicePack1(lpContext,lpInUnPacker,&lpMsgA1,li_TimeOut,iFuncNo,iBranchNo,iSystemNo,iSubSystemNo);

   if ( iSubRet == 0 && lpMsgA1 )
   {
       int iBizRetcode = lpMsgA1->GetItem(TAG_RETURN_CODE)->GetInt(); //返回码
       //1或者-1 通讯失败
       
       //有业务体返回业务体，没业务体则通过消息头中的error_no,error_info,return_code来返回
       if   ( ( iBizRetcode == RT_ERR_PROCESS ) || ( iBizRetcode == RT_ERR_TRANSFER ) )
       {
          //系统错误消息（AR不能转发，AS不能处理）可能没有业务体，说明交易没有提交
          iErrorNo = ERR_SYSERR_AR_NOTRANS_AS_NOPROC;
          iErrorID = iBizRetcode;
          if (iBizRetcode == RT_ERR_TRANSFER)
          {
             hs_snprintf(sErrorInfo,500,"路由不能转发[%s],发送者信息 = [%s] 插件ID = [%s] 节点编号 = [%d] 子系统编号 = [%d]",
                               lpMsgA1->GetItem(TAG_ERROR_INFO)->GetString(),
                               lpMsgA1->GetItem(TAG_SENDER_PATH)->GetString(IDX_OSPF_NAME),
                               lpMsgA1->GetItem(TAG_SENDER_PATH)->GetString(IDX_PLUGIN_ID),iSystemNo,iSubSystemNo);
          
          }   
          else
             hs_strcpy(sErrorInfo,lpMsgA1->GetItem(TAG_ERROR_INFO)->GetString());
          
          hs_snprintf(sErrorSysInfo,500,"SubServiceCallPack1调用[%d]失败(retcode[%d],节点编号[%d],子系统编号[%d])",iFuncNo,iBizRetcode,iSystemNo,iSubSystemNo);
          
          iReturnCode = SystemErrorPacker(lpOutPacker,sErrorPathInfo,iErrorNo,sErrorInfo);
          WriteSystemLog(lpContext,sErrorPathInfo,iErrorNo,sErrorInfo,iErrorID,sErrorSysInfo);
       }
       else
       {
          int iAnsLen = 0;
       
          void * lpAnsBuf =(void *) lpMsgA1->GetItem(TAG_MESSAGE_BODY)->GetRawData( &iAnsLen ); //内存由msg释放
          
          if ( lpAnsBuf && (iAnsLen>0) )
          {
             lpUnPack1 = lpPackService->GetUnPacker(lpAnsBuf,iAnsLen);
             if (lpUnPack1)
             {
                //业务成功或业务错误
                PackResultSet(lpUnPack1,lpOutPacker);
                lpUnPack1->Release();
                
                iReturnCode = iBizRetcode;
             }
             else
             {
             	//系统错误消息（AR不能转发，AS不能处理）可能没有业务体，说明交易没有提交
                iErrorNo = ERR_EXEC_BUSIPACK_ISNULL;
                iErrorID = RT_ERR_PROCESS;
                hs_snprintf(sErrorInfo,500,"业务包为空[功能号[%d] 节点编号[%d] 子系统编号[%d]]",iFuncNo,iSystemNo,iSubSystemNo);
                hs_snprintf(sErrorSysInfo,500,"SubServiceCallPack1调用[%d]失败(retcode[%d],节点编号[%d],子系统编号[%d])",iFuncNo,RT_ERR_PROCESS,iSystemNo,iSubSystemNo);
                
                iReturnCode = SystemErrorPacker(lpOutPacker,sErrorPathInfo,iErrorNo,sErrorInfo);
                WriteSystemLog(lpContext,sErrorPathInfo,iErrorNo,sErrorInfo,iErrorID,sErrorSysInfo);
                iReturnCode = iErrorNo;
             }
          }
          else
          {
          	 //系统错误消息（AR不能转发，AS不能处理）可能没有业务体，说明交易没有提交
             iErrorNo = ERR_EXEC_BUSIPACK_ISNULL;
             iErrorID = RT_ERR_PROCESS;
             hs_snprintf(sErrorInfo,500,"业务包为空[功能号[%d] 节点编号[%d] 子系统编号[%d]]",iFuncNo,iSystemNo,iSubSystemNo);
             hs_snprintf(sErrorSysInfo,500,"SubServiceCallPack1调用[%d]失败(retcode[%d],节点编号[%d],子系统编号[%d])",iFuncNo,RT_ERR_PROCESS,iSystemNo,iSubSystemNo);
             
             iReturnCode = SystemErrorPacker(lpOutPacker,sErrorPathInfo,iErrorNo,sErrorInfo);
             WriteSystemLog(lpContext,sErrorPathInfo,iErrorNo,sErrorInfo,iErrorID,sErrorSysInfo);
             iReturnCode = iErrorNo;
          }
       }
       
	   lpMsgA1->Release();
   }
   else
   {
       //调用失败或没收到应答消息（超时）
   	   if ( iSubRet == -2)
   	   {
   	   	  //超时错误(交易可能成功，可能失败)，要记录
          iErrorNo = ERR_SUBSERVICE_CALL_TIMEOUT;
          iErrorID = iSubRet;
          hs_snprintf(sErrorInfo,500,"业务受理中，请稍后检查是否成功[功能号[%d] 节点编号[%d] 子系统编号[%d]]",iFuncNo,iSystemNo,iSubSystemNo);
          //这种情况下功能可能已被调用到,需要冲正
   	      hs_snprintf(sErrorSysInfo,500,"SubServiceCallPack1调用[%d]失败(超时[%d],节点编号[%d],子系统编号[%d])",iFuncNo,iSubRet,iSystemNo,iSubSystemNo);
   	   }
   	   else
   	   {
   	   	  //系统调用错误(交易肯定没提交),对于事务中的首次交易调用不必记录
   	      iErrorNo = ERR_SUBSERVICE_CALL_FAIL;
          iErrorID = iSubRet;
          hs_snprintf(sErrorInfo,500,"子服务调用失败[功能号[%d] 节点编号[%d] 子系统编号[%d]]",iFuncNo,iSystemNo,iSubSystemNo);
          hs_snprintf(sErrorSysInfo,500,"SubServiceCallPack1调用[%d]失败(发送[%d],节点编号[%d],子系统编号[%d])",iFuncNo,iSubRet,iSystemNo,iSubSystemNo);
   	   }
   	   iReturnCode = SystemErrorPacker(lpOutPacker,sErrorPathInfo,iErrorNo,sErrorInfo);
       WriteSystemLog(lpContext,sErrorPathInfo,iErrorNo,sErrorInfo,iErrorID,sErrorSysInfo);
   }

   return iReturnCode;
}
///end 20110415 王仁云 add, 为账户增加一个新的子服务调用函数，把v1或v2的解包器内容转为v1的打包器内容发送（用于T1通道）。此修改涉及到创业板的登记报送
