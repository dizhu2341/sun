#include "uftinitmgr.h"
#include "monitor_manager.h"

IAS2Context * glb_lpcontext = NULL;
IF2Packer * glb_lpoutpacker = NULL;
ICommAgent * glb_lpcommagent = NULL;
IF2Core * glb_lpCore = NULL;

int PackAnswerPackage(IF2Packer* pack, int nErrorNo, const char* pErrorInfo)
{
	pack->AddField("error_no");
	pack->AddField("error_info");
	pack->AddInt(nErrorNo);
	pack->AddStr(pErrorInfo);
	return nErrorNo;
}

int  FUNCTION_CALL_MODE F615010( IAS2Context * lpContext, IF2UnPacker * lpInUnPacker, IF2Packer * lpOutPacker)
{
	CMonitorManager* lpMntrMgr = new CMonitorManager(lpContext, glb_lpcommagent, lpInUnPacker, lpOutPacker);
	if (NULL == lpMntrMgr)
	{
		DLOGERROR(lpContext,-100, "UFT状态监控管理类创建异常!");
		return PackAnswerPackage(lpOutPacker, -100, "UFT状态监控管理类创建异常!");
	}

	bool bRet = lpMntrMgr->CallMonitorService();
	int nErrNo = 0;
	char sErrInfo[1024] = {0};

	if (false == bRet)
	{
		nErrNo = lpMntrMgr->GetErrNo();
		strcpy(sErrInfo, lpMntrMgr->GetErrInfo());
		DLOGERROR(lpContext,nErrNo, sErrInfo);
	}
	else
	{
		nErrNo = lpMntrMgr->GetErrNo();
		strcpy(sErrInfo, lpMntrMgr->GetErrInfo());
		DLOGEVENT(lpContext,"服务返回参数:ErrNO["<<nErrNo<<"]ErrInfo["<<sErrInfo<<"]");
	}
	
	delete lpMntrMgr;
	return PackAnswerPackage(lpOutPacker, nErrNo, sErrInfo);
}

void  FUNCTION_CALL_MODE OnLoad(char * arg)
{
}

void  FUNCTION_CALL_MODE OnUnload()
{

}

void  FUNCTION_CALL_MODE OnStart()
{
	
}

void  FUNCTION_CALL_MODE OnStop()
{
}


//获取组件功能函数信息
int  FUNCTION_CALL_MODE GetBizFunctionsInfo(int Index, LPBIZ_FUNC_INFO  ppv)
{
   int iRet = ASFC_EXISTS;
   switch (Index)
   {
   case 0:
      if  (ppv!=NULL)
      {
         ppv->dwFunctionNo = 615010;        //功能号
         ppv->iVersion = 20121212;       //version信息
         ppv->ReqProc = F615010;            //功能函数指针
         ppv->AnsProc = NULL;            //应答处理函数入口
         ppv->Caption = "监控交易核心装态";      //函数功能描述
      }
      break;
   default:
      iRet= ASFC_NONE;
   }
   return iRet;
}


//获取组件信息
char *  FUNCTION_CALL_MODE GetLibVersion( )
{
    return __DATE__;
}

void FUNCTION_CALL_MODE  SetIKnown( IKnown * lp )
{
	glb_lpCore = (IF2Core *)lp;
	IKnown * lpService = NULL;
	if(glb_lpCore)
	{
		//获得glb_lpcommagent指针
		glb_lpCore->QueryInterface("commagent", (IKnown**)&lpService);
		if(lpService)
		{
			lpService->QueryInterface(ICOMM_AGENT, (IKnown**)&glb_lpcommagent);
		}
		else
		{
			return;
		}
	}
	else
	{
		return;
	}
}

