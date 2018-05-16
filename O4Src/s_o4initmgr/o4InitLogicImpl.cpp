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
    DLOGEVENT(lpContext,"���񷵻ز���:ErrNO[" << nErrorNo << "]ErrInfo[" << pErrorInfo << "]ErrPathInfo[" << pErrorPathInfo << "]"); /*lint !e539*/
    return nErrorNo;
}

int FUNCTION_CALL_MODE F615001(IAS2Context * lpContext, IF2UnPacker * lpInUnPacker, IF2Packer * lpOutPacker)
{
	DLOGEVENT(lpContext,"��ʼ�ճ�ʼ��ͬ��");

    char sErrPathInfo[4096] = {0};
    strcpy(sErrPathInfo, conversion((char *) lpInUnPacker->GetStr("error_pathinfo")));
    strcat(sErrPathInfo, "->F615001()");

    // �����ճ�ʼ��������
    int nErrNo = 0;
    char sErrInfo[4096] = {0};
    CO4InitManager *pMgr = new CO4InitManager(lpContext, glb_lpcommagent, lpInUnPacker, lpOutPacker, sErrPathInfo);
    if (NULL == pMgr)
    {
        nErrNo = -101;
        strcpy(sErrInfo, "�ճ������ഴ���쳣!");
        return PackAnswerPackage(lpContext, lpOutPacker, nErrNo, sErrInfo, sErrPathInfo);
    }

    // ��ʼ��ʼ��
    pMgr->Init();

    nErrNo = pMgr->GetErrNo();
    strcpy(sErrInfo, pMgr->GetErrInfo());
    strcpy(sErrPathInfo, pMgr->GetErrPathInfo());

    //�˴����÷������ж�����Ϊ�ཻ����������£�ֻҪ��һ���������ĳɹ������صľ���0
    if (sErrInfo[0] == '\0')
        strcpy(sErrInfo, "O4�ճ�ʼ���ɹ�");
    delete pMgr;
    return PackAnswerPackage(lpContext, lpOutPacker, nErrNo, sErrInfo, sErrPathInfo);
}

int FUNCTION_CALL_MODE F615002(IAS2Context * lpContext, IF2UnPacker * lpInUnPacker, IF2Packer * lpOutPacker)
{
	DLOGEVENT(lpContext,"��ʼO4��ʽ����");
    int nErrNo = 0;
    char sErrInfo[4096] = {0};
    char sErrPathInfo[4096] = {0};
    strcpy(sErrPathInfo, conversion((char *) lpInUnPacker->GetStr("error_pathinfo")));
    strcat(sErrPathInfo, "->F615002()");

    CO4InitManager *pMgr = new CO4InitManager(lpContext, glb_lpcommagent, lpInUnPacker, lpOutPacker, sErrPathInfo);
    if (NULL == pMgr)
    {
        nErrNo = -101;
        strcpy(sErrInfo, "�ճ������ഴ���쳣!");
        return PackAnswerPackage(lpContext, lpOutPacker, nErrNo, sErrInfo, sErrPathInfo);
    }

    // ��ʼ��ʽ����
    pMgr->Clear();

    nErrNo = pMgr->GetErrNo();
    strcpy(sErrInfo, pMgr->GetErrInfo());
    strcpy(sErrPathInfo, pMgr->GetErrPathInfo());
    //�˴����÷������ж�����Ϊ�ཻ����������£�ֻҪ��һ���������ĳɹ������صľ���0
	if (sErrInfo[0] == '\0')
		strcpy(sErrInfo, "��ʽ��ʼ���ɹ�");
    delete pMgr;
    return PackAnswerPackage(lpContext, lpOutPacker, nErrNo, sErrInfo, sErrPathInfo);
}

int FUNCTION_CALL_MODE F615004(IAS2Context * lpContext, IF2UnPacker * lpInUnPacker, IF2Packer * lpOutPacker)
{
	DLOGEVENT(lpContext,"��ʼO4����ͬ��");
    int nErrNo = 0;
    char sErrInfo[4096] = {0};
    char sErrPathInfo[4096] = {0};
    strcpy(sErrPathInfo, conversion((char *) lpInUnPacker->GetStr("error_pathinfo")));
    strcat(sErrPathInfo, "->F615004()");

    // �����ճ�ʼ��������
    CO4InitManager *pMgr = new CO4InitManager(lpContext, glb_lpcommagent, lpInUnPacker, lpOutPacker, sErrPathInfo);
    if (NULL == pMgr)
    {
        nErrNo = -101;
        strcpy(sErrInfo, "�ճ������ഴ���쳣!");
        return PackAnswerPackage(lpContext, lpOutPacker, nErrNo, sErrInfo, sErrPathInfo);
    }

    // ��ʼ����ͬ��
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
    return PackAnswerPackage(lpContext, lpOutPacker, 0, "O4����ͬ���ɹ���");
}

// ҹ������ͬ������
int FUNCTION_CALL_MODE F615006(IAS2Context * lpContext, IF2UnPacker * lpInUnPacker, IF2Packer * lpOutPacker)
{
	DLOGEVENT(lpContext,"��ʼҹ����������ͬ��");
    int nErrNo = 0;
    char sErrInfo[4096] = {0};
    char sErrPathInfo[4096] = {0};
    strcpy(sErrPathInfo, conversion((char *) lpInUnPacker->GetStr("error_pathinfo")));
    strcat(sErrPathInfo, "->F615006()");

    // �����ճ�ʼ��������
    CO4InitManager *pMgr = new CO4InitManager(lpContext, glb_lpcommagent, lpInUnPacker, lpOutPacker, sErrPathInfo);
    if (NULL == pMgr)
    {
        nErrNo = -101;
        strcpy(sErrInfo, "�ճ������ഴ���쳣!");
        return PackAnswerPackage(lpContext, lpOutPacker, nErrNo, sErrInfo, sErrPathInfo);
    }

    // ��ʼ����ͬ��
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
    return PackAnswerPackage(lpContext, lpOutPacker, 0, "ҹ����������ͬ���ɹ���");
}

void FUNCTION_CALL_MODE OnLoad(char * argv)
{
    //��ʼ���߳��������Ĭ��15��
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


//��ȡ������ܺ�����Ϣ

int FUNCTION_CALL_MODE GetBizFunctionsInfo(int Index, LPBIZ_FUNC_INFO ppv)
{
    int iRet = ASFC_EXISTS;
    switch (Index)
    {
        case 0:
            if (ppv != NULL)
            {
                ppv->dwFunctionNo = 615001; //���ܺ�
                ppv->iVersion = 20150202; //version��Ϣ
                ppv->ReqProc = F615001; //���ܺ���ָ��
                ppv->AnsProc = NULL; //Ӧ���������
                ppv->Caption = "�ճ�ʼ��"; //������������
            }
            break;
        case 1:
            if (ppv != NULL)
            {
                ppv->dwFunctionNo = 615004; //���ܺ�
                ppv->iVersion = 20150810; //version��Ϣ
                ppv->ReqProc = F615004; //���ܺ���ָ��
                ppv->AnsProc = NULL; //Ӧ���������
                ppv->Caption = "����ͬ��"; //������������
            }
            break;
        case 2:
            if (ppv != NULL)
            {
                ppv->dwFunctionNo = 615002; //���ܺ�
                ppv->iVersion = 20170111; //version��Ϣ
                ppv->ReqProc = F615002; //���ܺ���ָ��
                ppv->AnsProc = NULL; //Ӧ���������
                ppv->Caption = "��ʽ����"; //������������
            }
            break;
        case 3:
			if (ppv != NULL)
			{
				ppv->dwFunctionNo = 615006; //���ܺ�
				ppv->iVersion = 20170406; //version��Ϣ
				ppv->ReqProc = F615006; //���ܺ���ָ��
				ppv->AnsProc = NULL; //Ӧ���������
				ppv->Caption = "ҹ������"; //������������
			}
			break;
        default:
            iRet = ASFC_NONE;
    }
    return iRet;
}


//��ȡ�����Ϣ

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
        //���glb_lpcommagentָ��
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
