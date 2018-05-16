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
		DLOGERROR(lpContext,-100, "UFT״̬��ع����ഴ���쳣!");
		return PackAnswerPackage(lpOutPacker, -100, "UFT״̬��ع����ഴ���쳣!");
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
		DLOGEVENT(lpContext,"���񷵻ز���:ErrNO["<<nErrNo<<"]ErrInfo["<<sErrInfo<<"]");
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


//��ȡ������ܺ�����Ϣ
int  FUNCTION_CALL_MODE GetBizFunctionsInfo(int Index, LPBIZ_FUNC_INFO  ppv)
{
   int iRet = ASFC_EXISTS;
   switch (Index)
   {
   case 0:
      if  (ppv!=NULL)
      {
         ppv->dwFunctionNo = 615010;        //���ܺ�
         ppv->iVersion = 20121212;       //version��Ϣ
         ppv->ReqProc = F615010;            //���ܺ���ָ��
         ppv->AnsProc = NULL;            //Ӧ���������
         ppv->Caption = "��ؽ��׺���װ̬";      //������������
      }
      break;
   default:
      iRet= ASFC_NONE;
   }
   return iRet;
}


//��ȡ�����Ϣ
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
		//���glb_lpcommagentָ��
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

