#include <stdio.h>
#include <stdlib.h>
#include "o4InitManager.h"
#include "o4InitLogicImpl.h"

IAS2Context * glb_lpcontext = NULL;
IF2Packer * glb_lpoutpacker = NULL;
ICommAgent * glb_lpcommagent = NULL;
IF2Core * glb_lpCore = NULL;
int glb_nthreadcount = 0;

int PackAnswerPackage(IAS2Context * lpContext, IF2Packer* pack, int nErrorNo, const char* pErrorInfo, char* pErrorPathInfo = "")
{
    pack->AddField("error_no");
    pack->AddField("error_info");
    if (nErrorNo != 0)
    {
        pack->AddField("error_pathinfo");
    }
    pack->AddInt(nErrorNo); /*lint !e539*/
    pack->AddStr(pErrorInfo);
    if (nErrorNo != 0)
    {
        pack->AddStr(pErrorPathInfo);
    }
    DLOGEVENT(lpContext,"服务返回参数:ErrNO[" << nErrorNo << "]ErrInfo[" << pErrorInfo << "]ErrPathInfo[" << pErrorPathInfo << "]"); /*lint !e539*/
    return nErrorNo;
}

int FUNCTION_CALL_MODE F615001(IAS2Context * lpContext, IF2UnPacker * lpInUnPacker, IF2Packer * lpOutPacker)
{
	DLOGEVENT(lpContext,"开始日初始化同步");

    char sErrPathInfo[4096] = {0};
    strcpy(sErrPathInfo, conversion((char *) lpInUnPacker->GetStr("error_pathinfo")));
    strcat(sErrPathInfo, "->F615001()");

    // 申请日初始化管理类
    int nErrNo = 0;
    char sErrInfo[4096] = {0};
    CO4InitManager *pMgr = new CO4InitManager(lpContext, glb_lpcommagent, lpInUnPacker, lpOutPacker, sErrPathInfo);
    if (NULL == pMgr)
    {
        nErrNo = -101;
        strcpy(sErrInfo, "日初管理类创建异常!");
        return PackAnswerPackage(lpContext, lpOutPacker, nErrNo, sErrInfo, sErrPathInfo);
    }

    // 开始初始化
    pMgr->Init();

    nErrNo = pMgr->GetErrNo();
    strcpy(sErrInfo, pMgr->GetErrInfo());
    strcpy(sErrPathInfo, pMgr->GetErrPathInfo());

    //此处不用返回码判断是因为多交易中心情况下，只要有一个交易中心成功，返回的就是0
    if (sErrInfo[0] == '\0')
        strcpy(sErrInfo, "O4日初始化成功");
    delete pMgr;
    return PackAnswerPackage(lpContext, lpOutPacker, nErrNo, sErrInfo, sErrPathInfo);
}

int FUNCTION_CALL_MODE F615002(IAS2Context * lpContext, IF2UnPacker * lpInUnPacker, IF2Packer * lpOutPacker)
{
	DLOGEVENT(lpContext,"开始O4正式清算");
    int nErrNo = 0;
    char sErrInfo[4096] = {0};
    char sErrPathInfo[4096] = {0};
    strcpy(sErrPathInfo, conversion((char *) lpInUnPacker->GetStr("error_pathinfo")));
    strcat(sErrPathInfo, "->F615002()");

    CO4InitManager *pMgr = new CO4InitManager(lpContext, glb_lpcommagent, lpInUnPacker, lpOutPacker, sErrPathInfo);
    if (NULL == pMgr)
    {
        nErrNo = -101;
        strcpy(sErrInfo, "日初管理类创建异常!");
        return PackAnswerPackage(lpContext, lpOutPacker, nErrNo, sErrInfo, sErrPathInfo);
    }

    // 开始正式清算
    pMgr->Clear();

    nErrNo = pMgr->GetErrNo();
    strcpy(sErrInfo, pMgr->GetErrInfo());
    strcpy(sErrPathInfo, pMgr->GetErrPathInfo());
    //此处不用返回码判断是因为多交易中心情况下，只要有一个交易中心成功，返回的就是0
	if (sErrInfo[0] == '\0')
		strcpy(sErrInfo, "正式初始化成功");
    delete pMgr;
    return PackAnswerPackage(lpContext, lpOutPacker, nErrNo, sErrInfo, sErrPathInfo);
}

int FUNCTION_CALL_MODE F615004(IAS2Context * lpContext, IF2UnPacker * lpInUnPacker, IF2Packer * lpOutPacker)
{
	DLOGEVENT(lpContext,"开始O4数据同步");
    int nErrNo = 0;
    char sErrInfo[4096] = {0};
    char sErrPathInfo[4096] = {0};
    strcpy(sErrPathInfo, conversion((char *) lpInUnPacker->GetStr("error_pathinfo")));
    strcat(sErrPathInfo, "->F615004()");

    // 申请日初始化管理类
    CO4InitManager *pMgr = new CO4InitManager(lpContext, glb_lpcommagent, lpInUnPacker, lpOutPacker, sErrPathInfo);
    if (NULL == pMgr)
    {
        nErrNo = -101;
        strcpy(sErrInfo, "日初管理类创建异常!");
        return PackAnswerPackage(lpContext, lpOutPacker, nErrNo, sErrInfo, sErrPathInfo);
    }

    // 开始数据同步
    bool bRet = pMgr->Sync();
    if (false == bRet)
    {
        nErrNo = pMgr->GetErrNo();
        strcpy(sErrInfo, pMgr->GetErrInfo());
        strcpy(sErrPathInfo, pMgr->GetErrPathInfo());
        delete pMgr;
        return PackAnswerPackage(lpContext, lpOutPacker, nErrNo, sErrInfo, sErrPathInfo);
    }

    delete pMgr;
    return PackAnswerPackage(lpContext, lpOutPacker, 0, "O4数据同步成功！");
}

// 夜盘升级同步数据
int FUNCTION_CALL_MODE F615006(IAS2Context * lpContext, IF2UnPacker * lpInUnPacker, IF2Packer * lpOutPacker)
{
	DLOGEVENT(lpContext,"开始夜盘升级数据同步");
    int nErrNo = 0;
    char sErrInfo[4096] = {0};
    char sErrPathInfo[4096] = {0};
    strcpy(sErrPathInfo, conversion((char *) lpInUnPacker->GetStr("error_pathinfo")));
    strcat(sErrPathInfo, "->F615006()");

    // 申请日初始化管理类
    CO4InitManager *pMgr = new CO4InitManager(lpContext, glb_lpcommagent, lpInUnPacker, lpOutPacker, sErrPathInfo);
    if (NULL == pMgr)
    {
        nErrNo = -101;
        strcpy(sErrInfo, "日初管理类创建异常!");
        return PackAnswerPackage(lpContext, lpOutPacker, nErrNo, sErrInfo, sErrPathInfo);
    }

    // 开始数据同步
    bool bRet = pMgr->UpgradeSync();
    if (false == bRet)
    {
        nErrNo = pMgr->GetErrNo();
        strcpy(sErrInfo, pMgr->GetErrInfo());
        strcpy(sErrPathInfo, pMgr->GetErrPathInfo());
        delete pMgr;
        return PackAnswerPackage(lpContext, lpOutPacker, nErrNo, sErrInfo, sErrPathInfo);
    }

    delete pMgr;
    return PackAnswerPackage(lpContext, lpOutPacker, 0, "夜盘升级数据同步成功！");
}

void FUNCTION_CALL_MODE OnLoad(char * argv)
{
    //初始化线程最大数，默认15个
    if (strlen(argv) > 0)
    {
        glb_nthreadcount = atoi(argv);
    } else
    {
        glb_nthreadcount = 15;
    }
}

void FUNCTION_CALL_MODE OnUnload()
{

}

void FUNCTION_CALL_MODE OnStart()
{

}

void FUNCTION_CALL_MODE OnStop()
{
}


//获取组件功能函数信息

int FUNCTION_CALL_MODE GetBizFunctionsInfo(int Index, LPBIZ_FUNC_INFO ppv)
{
    int iRet = ASFC_EXISTS;
    switch (Index)
    {
        case 0:
            if (ppv != NULL)
            {
                ppv->dwFunctionNo = 615001; //功能号
                ppv->iVersion = 20150202; //version信息
                ppv->ReqProc = F615001; //功能函数指针
                ppv->AnsProc = NULL; //应答处理函数入口
                ppv->Caption = "日初始化"; //函数功能描述
            }
            break;
        case 1:
            if (ppv != NULL)
            {
                ppv->dwFunctionNo = 615004; //功能号
                ppv->iVersion = 20150810; //version信息
                ppv->ReqProc = F615004; //功能函数指针
                ppv->AnsProc = NULL; //应答处理函数入口
                ppv->Caption = "数据同步"; //函数功能描述
            }
            break;
        case 2:
            if (ppv != NULL)
            {
                ppv->dwFunctionNo = 615002; //功能号
                ppv->iVersion = 20170111; //version信息
                ppv->ReqProc = F615002; //功能函数指针
                ppv->AnsProc = NULL; //应答处理函数入口
                ppv->Caption = "正式清算"; //函数功能描述
            }
            break;
        case 3:
			if (ppv != NULL)
			{
				ppv->dwFunctionNo = 615006; //功能号
				ppv->iVersion = 20170406; //version信息
				ppv->ReqProc = F615006; //功能函数指针
				ppv->AnsProc = NULL; //应答处理函数入口
				ppv->Caption = "夜盘升级"; //函数功能描述
			}
			break;
        default:
            iRet = ASFC_NONE;
    }
    return iRet;
}


//获取组件信息

char * FUNCTION_CALL_MODE GetLibVersion()
{
    return __DATE__;
}

void FUNCTION_CALL_MODE SetIKnown(IKnown * lp)
{
    glb_lpCore = (IF2Core *) lp;
    IKnown * lpService = NULL;
    if (glb_lpCore)
    {
        //获得glb_lpcommagent指针
        glb_lpCore->QueryInterface("commagent", (IKnown**) & lpService);
        if (lpService)
        {
            lpService->QueryInterface(ICOMM_AGENT, (IKnown**) & glb_lpcommagent);
        } else
        {
            return;
        }
    } else
    {
        return;
    }
}
