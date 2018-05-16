#include "monitor_manager.h"
#include "monitor_thread.h"

CMonitorManager::CMonitorManager(IAS2Context * lpContext, ICommAgent* lpCommAgent, IF2UnPacker * lpInUnPacker, IF2Packer * lpOutPacker)
{
		m_lpContext = lpContext;
		m_lpCommAgent = lpCommAgent;
		m_lpInUnPacker = lpInUnPacker;
		m_lpOutPacker = lpOutPacker;
		strcpy(error_pathinfo, "F615010()");
		m_nErrNo = 0;
		strcpy(m_sErrInfo, "");
}

CMonitorManager::~CMonitorManager()
{
	m_lpContext = NULL;
	m_lpCommAgent = NULL;
	m_lpInUnPacker = NULL;
	m_lpOutPacker = NULL;
}

int CMonitorManager::GetErrNo()
{
	return m_nErrNo;
}

char* CMonitorManager::GetErrInfo()
{
	return m_sErrInfo;						/*lint !e1536*/
}

void CMonitorManager::SetErrInfo(int errNo, const char* pErrInfo)
{
	m_nErrNo = errNo;
	strcpy(m_sErrInfo, pErrInfo);
}

bool CMonitorManager::CallMonitorService()
{
	if (!CheckTradeCenterInit())
	{
		return false;
	}
	
	if (!ResetTradeCenterFlag())
	{
		SetErrInfo(-101, "���ý������ĳ�ʼ��״̬ʧ��");
		return false;
	}
	
	if (!GetTradeCenterList())
	{
		SetErrInfo(-102, "��ȡ����������Ϣʧ��");
		return false;
	}
	
	//----------------------------------------------------------------
	//���߳�ִ�е��÷���
	TRADELIST::iterator tradeIter = m_lstTrd.begin();
	for (; tradeIter != m_lstTrd.end(); tradeIter++)
	{
		CMonitorAgent* lpMntrAgt = new CMonitorAgent();
		lpMntrAgt->Execute((void *)(*tradeIter));
		m_lstMntr.push_back(lpMntrAgt);
	}													/*lint !e429*/
	
	//---------------------------------------------------------------
	//��ȡ�����߳̽���״̬
	unsigned int successCount 				= 0;
	unsigned int failCount 					= 0;
	bool isUfmOk = true;
	int ufmErrNo = -10000000;
	char ufmErrInfo[5000] = {0};
	char tmpErrInfo[5000] = {0};
	char errInfo[5000] = {0};
	for (MNTRLIST::iterator mntrIter = m_lstMntr.begin(); mntrIter != m_lstMntr.end(); mntrIter++)
	{
		CMonitorAgent* lpMntrAgt = (*mntrIter);
		CTradeCenter*  lpTrdCnt = (CTradeCenter*)lpMntrAgt->GetThreadData();
		bool isExecOk = lpMntrAgt->WaitForTid();
		
		// �����ufm(��ϵͳ��Ϊ35),�����⴦��
		if (35 == lpTrdCnt->GetTradeID())
		{
			ufmErrNo = lpMntrAgt->GetErrNo();
			strcpy (ufmErrInfo, lpMntrAgt->GetErrInfo());
			isUfmOk = isExecOk;
		}
		else if (!isExecOk)
		{
			sprintf(tmpErrInfo, "����[%d]�ճ�ʧ��,ErrNo[%d]ErrInfo[%s];", lpTrdCnt->GetTradeID(), lpMntrAgt->GetErrNo(), lpMntrAgt->GetErrInfo());
			DLOGWARNING(m_lpContext, tmpErrInfo);
			strcat(errInfo, tmpErrInfo);
			failCount++;
		}
		else								//�����سɹ��������ó�ʼ�����Ϊ�ѳ�ʼ��
		{
			sprintf(tmpErrInfo, "����[%d]�ճ��ɹ�;", lpTrdCnt->GetTradeID());
			DLOGWARNING(m_lpContext, tmpErrInfo);
			strcat(errInfo, tmpErrInfo);
			successCount++;
			UpdateInitFlag(lpTrdCnt);
		}
		
		delete lpMntrAgt;
	}

	if (successCount > 0 &&  failCount > 0)    // ���ֳɹ�
	{
		if (false == isUfmOk)
		{
			sprintf(tmpErrInfo, "UFT���ֳ�ʼ���ɹ�,UFM��ʼ��ʧ��:%s;UFM�ճ�ʧ��ErrNo[%d]ErrInfo[%s]", errInfo, ufmErrNo, ufmErrInfo);
			SetErrInfo(615011,  tmpErrInfo);
		}
		else if (ufmErrNo == 0)
		{
			sprintf(tmpErrInfo, "UFT���ֳ�ʼ���ɹ�,UFM��ʼ���ɹ�:%s", errInfo);
			//SetErrInfo(0,  tmpErrInfo);
            SetErrInfo(-100,  tmpErrInfo);
		}
		else
		{
			sprintf(tmpErrInfo, "UFT���ֳ�ʼ���ɹ�: %s", errInfo);
			//SetErrInfo(0,  tmpErrInfo);
			SetErrInfo(-100,  tmpErrInfo);
		}	
	}
	else if (successCount > 0 &&  failCount == 0) // ȫ���ɹ�
	{
		if (false == isUfmOk)
		{
			sprintf(tmpErrInfo, "UFT��ʼ���ɹ�,UFM��ʼ��ʧ��:UFM�ճ�ʧ��ErrNo[%d]ErrInfo[%s]", ufmErrNo, ufmErrInfo);
			SetErrInfo(615011,  tmpErrInfo);
		}
		else if (ufmErrNo == 0)
		{
			strcat(tmpErrInfo, "UFT��UFM��ʼ���ɹ�.");
			SetErrInfo(0,  tmpErrInfo);
		}
		else
		{
			strcat(tmpErrInfo, "UFT��ʼ���ɹ�.");
			SetErrInfo(0,  tmpErrInfo);
		}	

		if (false == isUfmOk) 
		{
			sprintf(tmpErrInfo, "UFT��ʼ���ɹ�,����UFM��ʼ��ʧ��,ErrNo[%d]ErrInfo[%s]���뵥�����³�ʼ��UFM��", ufmErrNo, ufmErrInfo);
			SetErrInfo(615011, tmpErrInfo);
		}
		else
			SetErrInfo(0, "UFT��ʼ���ɹ�!");
	}
	else                                          // ȫ��ʧ��
	{
		if (false == isUfmOk)
		{
			sprintf(tmpErrInfo, "UFT��UFMȫ����ʼ��ʧ��:%s;UFM�ճ�ʧ��ErrNo[%d]ErrInfo[%s]", errInfo, ufmErrNo, ufmErrInfo);
			SetErrInfo(-100,  tmpErrInfo);
		}
		else if (ufmErrNo == 0)
		{
			sprintf(tmpErrInfo, "UFT��ʼ��ʧ��,UFM��ʼ���ɹ�:%s",  errInfo);
			SetErrInfo(-100,  tmpErrInfo);
		}
		else
		{
			sprintf(tmpErrInfo, "UFT��ʼ��ʧ��:%s",  errInfo);
			SetErrInfo(-100,  tmpErrInfo);
		}	
	}
	
	return true;
}

bool CMonitorManager::GetUFMStatus()
{	
    int funcId = 2617006;
    int iRet = 0;
    IF2PackSvr * lpPackService = m_lpContext->GetF2PackSvr();
    IF2Packer * lpFuncInPacker = lpPackService->GetPacker(2);
    IF2Packer * lpFuncOutPacker = lpPackService->GetPacker(2);
    IF2UnPacker * lpResultSet = NULL;
    int branch_no = m_lpInUnPacker->GetInt("branch_no");

    //--------------------------------------------------
    //�жϻ�����ϵͳ�Ƿ�����
    // ׼���첽��Ϣ
    int subsys_id = 36;
    int sysnode_id = 0;

    //����2617006��ѯϵͳ����ֵ61263�Ƿ����������������߳����ӹ��ܺ�
    lpFuncInPacker->BeginPack();
    lpFuncInPacker->AddField("sysparam_no",'I');
    lpFuncInPacker->AddField("error_pathinfo",'S',4000);
    lpFuncInPacker->AddInt(61263); 
    lpFuncInPacker->AddStr(error_pathinfo);
    lpFuncInPacker->EndPack();

    //��������תΪ���������������ʹ��
    lpFuncOutPacker->BeginPack();
    iRet = SubServiceCall(m_lpContext,lpFuncInPacker->UnPack(),lpFuncOutPacker,5000,funcId,branch_no,sysnode_id,subsys_id);
    lpFuncOutPacker->EndPack();
    lpResultSet = lpFuncOutPacker->UnPack(); //������

    if (0 != iRet)
    {
        DLOGERROR(m_lpContext,iRet, "���ù��ܺ�"<<funcId<<"ʧ�ܣ�������Ϣ��"<<lpResultSet->GetStr("error_info"));
        SetErrInfo(iRet, lpResultSet->GetStr("error_info"));	
        if (lpResultSet->GetStr("error_pathinfo") == NULL)
            hs_strncat(error_pathinfo,"->2617006",4000);
        else
            hs_strncpy(error_pathinfo, lpResultSet->GetStr("error_pathinfo"), 4000);

        return false;
    }
    int nUFMStatus = atoi(lpResultSet->GetStr("param_value"));

    if (lpResultSet)
    {
        lpResultSet->Release();
    }

    if (lpFuncInPacker)
    {
        free(lpFuncInPacker->GetPackBuf());
        lpFuncInPacker->Release();
    }

    if (lpFuncOutPacker)
    {
        free(lpFuncOutPacker->GetPackBuf());
        lpFuncOutPacker->Release();
    }

    return nUFMStatus;
}

bool CMonitorManager::GetTradeCenterList()
{
	DLOGEVENT(m_lpContext,"��ʼ��ѯ���������б�");
	int iRet = 0;
	int funcId = 2617002;
	int nTradeId = 0;
	int nInitDate = 0;
    IF2PackSvr * lpPackService = m_lpContext->GetF2PackSvr();
    IF2Packer * lpFuncInPacker = lpPackService->GetPacker(2);
	IF2Packer * lpFuncOutPacker = lpPackService->GetPacker(2);
    IF2UnPacker * lpResultSet = NULL;
	int branch_no = m_lpInUnPacker->GetInt("branch_no");
	nInitDate = m_lpInUnPacker->GetInt("init_date");
	
	//--------------------------------------------------
	//�жϻ�����ϵͳ�Ƿ�����
	int subsys_no = 999;
	// ׼���첽��Ϣ
	int subsys_id = 36;
	int sysnode_id = 0;

	//����AS_����_��ϵͳ�Ƿ�����
	lpFuncInPacker->BeginPack();
	lpFuncInPacker->AddField("subsys_no",'I');
	lpFuncInPacker->AddField("error_pathinfo",'S',4000);
	lpFuncInPacker->AddInt(subsys_no); //subsys_no
	lpFuncInPacker->AddStr(error_pathinfo);
	lpFuncInPacker->EndPack();

	//��������תΪ���������������ʹ��
	lpFuncOutPacker->BeginPack();
	iRet = SubServiceCall(m_lpContext,lpFuncInPacker->UnPack(),lpFuncOutPacker,5000,funcId,branch_no,sysnode_id,subsys_id);
	lpFuncOutPacker->EndPack();
	lpResultSet = lpFuncOutPacker->UnPack(); //������
	
	if (0 != iRet)
	{
		DLOGERROR(m_lpContext,iRet, "���ù��ܺ�"<<funcId<<"ʧ�ܣ�������Ϣ��"<<lpResultSet->GetStr("error_info"));
		SetErrInfo(iRet, lpResultSet->GetStr("error_info"));

		if (lpResultSet->GetStr("error_pathinfo") == NULL)
			hs_strncat(error_pathinfo,"->2617002", 4000);
		else
			hs_strncpy(error_pathinfo, lpResultSet->GetStr("error_pathinfo"), 4000);
		
		return false;
	}
	
	while ( !lpResultSet->IsEOF() )
	{
		nTradeId = lpResultSet->GetInt("center_id");
        if (lpResultSet->GetChar("use_flag") == '1')
        {
            m_lstTrd.push_back(new CTradeCenter(m_lpContext, m_lpCommAgent, nTradeId, nInitDate));
        }
		lpResultSet->Next();
	}

	DLOGEVENT(m_lpContext,"��ѯ��"<<m_lstTrd.size()<<"����������");
	
	if (lpResultSet)
	{
		lpResultSet->Release();
	}
	
	if (lpFuncInPacker)
	{
		free(lpFuncInPacker->GetPackBuf());
		lpFuncInPacker->Release();
	}
	
	if (lpFuncOutPacker)
	{
		free(lpFuncOutPacker->GetPackBuf());
		lpFuncOutPacker->Release();
	}
	
	//�ж��Ƿ���Ҫ������ͬ����UFM�ڵ�
	bool UFMStatus =GetUFMStatus();
	if(UFMStatus)
	{
		//UFM��ϵͳ��Ϊ35,��Ӧ��ʼ���Ĺ��ܺ�Ϊ460011
		m_lstTrd.push_back(new CTradeCenter(m_lpContext, m_lpCommAgent, 35, nInitDate,460011));
		DLOGDEBUG(m_lpContext, "UFM�ڵ���뽻�������б�");
        return true;
	}
	
	return true;
}

bool CMonitorManager::ResetTradeCenterFlag()
{
	DLOGEVENT(m_lpContext,"��ʼ���ý������ĳ�ʼ��״̬");
	
	int iRet = 0;
	int funcId = 2617003;
    IF2PackSvr * lpPackService = m_lpContext->GetF2PackSvr();
    IF2Packer * lpFuncInPacker = lpPackService->GetPacker(2);
	IF2Packer * lpFuncOutPacker = lpPackService->GetPacker(2);
    IF2UnPacker * lpResultSet = NULL;
	int branch_no = m_lpInUnPacker->GetInt("branch_no");
	
	//--------------------------------------------------
	//�жϻ�����ϵͳ�Ƿ�����
	int subsys_no = 999;
	// ׼���첽��Ϣ
	int subsys_id = 36;
	int sysnode_id = 0;

	//����AS_����_��ϵͳ�Ƿ�����
	lpFuncInPacker->BeginPack();
	lpFuncInPacker->AddField("subsys_no",'I');
	lpFuncInPacker->AddField("error_pathinfo",'S',4000);
	lpFuncInPacker->AddInt(subsys_no); //subsys_no
	lpFuncInPacker->AddStr(error_pathinfo);
	lpFuncInPacker->EndPack();

	//��������תΪ���������������ʹ��
	lpFuncOutPacker->BeginPack();
	iRet = SubServiceCall(m_lpContext,lpFuncInPacker->UnPack(),lpFuncOutPacker,5000,funcId,branch_no,sysnode_id,subsys_id);
	lpFuncOutPacker->EndPack();
	lpResultSet = lpFuncOutPacker->UnPack(); //������
	
	if (0 != iRet)
	{
		DLOGERROR(m_lpContext,iRet, "���ù��ܺ�"<<funcId<<"ʧ�ܣ�������Ϣ��"<<lpResultSet->GetStr("error_info"));
		SetErrInfo(iRet, lpResultSet->GetStr("error_info"));

		if (lpResultSet->GetStr("error_pathinfo") == NULL)
			hs_strncat(error_pathinfo,"->2617003", 4000);
		else
			hs_strncpy(error_pathinfo, lpResultSet->GetStr("error_pathinfo"), 4000);
		
		return false;
	}
	
	if (lpResultSet)
	{
		lpResultSet->Release();
	}
	
	if (lpFuncInPacker)
	{
		free(lpFuncInPacker->GetPackBuf());
		lpFuncInPacker->Release();
	}
	
	if (lpFuncOutPacker)
	{
		free(lpFuncOutPacker->GetPackBuf());
		lpFuncOutPacker->Release();
	}
	
	DLOGEVENT(m_lpContext,"���ý������ĳ�ʼ��״̬���");
    return true;
}

bool CMonitorManager::UpdateInitFlag(CTradeCenter* lpTrdCnt)
{
	int iRet = 0;
	int funcId = 2617004;
    IF2PackSvr * lpPackService = m_lpContext->GetF2PackSvr();
    IF2Packer * lpFuncInPacker = lpPackService->GetPacker(2);
	IF2Packer * lpFuncOutPacker = lpPackService->GetPacker(2);
    IF2UnPacker * lpResultSet = NULL;
	int branch_no = m_lpInUnPacker->GetInt("branch_no");
	
	int nTradeID = lpTrdCnt->GetTradeID();
	char sInitFlag = lpTrdCnt->GetInitFlag();
	
	DLOGEVENT(m_lpContext,"��ʼ���ý�������["<<nTradeID<<"]�ĳ�ʼ��״̬["<<sInitFlag<<"]");
	
	//--------------------------------------------------
	// ׼���첽��Ϣ
	int subsys_id = 36;
	int sysnode_id = 0;

	//����AS_����_��ϵͳ�Ƿ�����
	lpFuncInPacker->BeginPack();
	lpFuncInPacker->AddField("error_pathinfo",'S',4000);
	lpFuncInPacker->AddField("center_id",'I');
	lpFuncInPacker->AddField("init_flag",'C');
	lpFuncInPacker->AddStr(error_pathinfo);
	lpFuncInPacker->AddInt(nTradeID);
	lpFuncInPacker->AddChar(sInitFlag);
	lpFuncInPacker->EndPack();

	//��������תΪ���������������ʹ��
	lpFuncOutPacker->BeginPack();
	iRet = SubServiceCall(m_lpContext,lpFuncInPacker->UnPack(),lpFuncOutPacker,5000,funcId,branch_no,sysnode_id,subsys_id);
	lpFuncOutPacker->EndPack();
	lpResultSet = lpFuncOutPacker->UnPack(); //������
	
	if (0 != iRet)
	{
		DLOGERROR(m_lpContext,iRet, "���ù��ܺ�"<<funcId<<"ʧ�ܣ�������Ϣ��"<<lpResultSet->GetStr("error_info"));
		SetErrInfo(iRet, lpResultSet->GetStr("error_info"));

		if (lpResultSet->GetStr("error_pathinfo") == NULL)
			hs_strncat(error_pathinfo,"->2617004", 4000);
		else
			hs_strncpy(error_pathinfo, lpResultSet->GetStr("error_pathinfo"), 4000);
		
		return false;
	}
	
	if (lpResultSet)
	{
		lpResultSet->Release();
	}
	
	if (lpFuncInPacker)
	{
		free(lpFuncInPacker->GetPackBuf());
		lpFuncInPacker->Release();
	}
	
	if (lpFuncOutPacker)
	{
		free(lpFuncOutPacker->GetPackBuf());
		lpFuncOutPacker->Release();
	}
	
	DLOGEVENT(m_lpContext,"��������["<<nTradeID<<"]�ĳ�ʼ��״̬�������");
	
    return true;
}

bool CMonitorManager::CheckTradeCenterInit()
{
	DLOGEVENT(m_lpContext,"��ʼ�������ĳ�ʼ��ҵ��У��");
	
	int iRet = 0;
	int funcId = 2616211;
    IF2PackSvr * lpPackService = m_lpContext->GetF2PackSvr();
    IF2Packer * lpFuncInPacker = lpPackService->GetPacker(2);
	IF2Packer * lpFuncOutPacker = lpPackService->GetPacker(2);
    IF2UnPacker * lpResultSet = NULL;
	int branch_no = m_lpInUnPacker->GetInt("branch_no");
	
	//--------------------------------------------------
	// ׼���첽��Ϣ
	int subsys_id = 36;
	int sysnode_id = 0;

	//����AS_����_��ϵͳ�Ƿ�����
	lpFuncInPacker->BeginPack();
	lpFuncInPacker->AddField("error_pathinfo",'S',4000);
	lpFuncInPacker->AddStr(error_pathinfo);
	lpFuncInPacker->EndPack();

	//��������תΪ���������������ʹ��
	lpFuncOutPacker->BeginPack();
	iRet = SubServiceCall(m_lpContext,lpFuncInPacker->UnPack(),lpFuncOutPacker,5000,funcId,branch_no,sysnode_id,subsys_id);
	lpFuncOutPacker->EndPack();
	lpResultSet = lpFuncOutPacker->UnPack(); //������
	
	if (0 != iRet)
	{
		DLOGERROR(m_lpContext,iRet, "���ù��ܺ�"<<funcId<<"����������Ϣ��"<<lpResultSet->GetStr("error_info"));
		SetErrInfo(iRet, lpResultSet->GetStr("error_info"));

		if (lpResultSet->GetStr("error_pathinfo") == NULL)
			hs_strncat(error_pathinfo,"->2615404", 4000);
		else
			hs_strncpy(error_pathinfo, lpResultSet->GetStr("error_pathinfo"), 4000);
		
		return false;
	}
	
	if (lpResultSet)
	{
		lpResultSet->Release();
	}
	
	if (lpFuncInPacker)
	{
		free(lpFuncInPacker->GetPackBuf());
		lpFuncInPacker->Release();
	}
	
	if (lpFuncOutPacker)
	{
		free(lpFuncOutPacker->GetPackBuf());
		lpFuncOutPacker->Release();
	}
	
	DLOGEVENT(m_lpContext,"�������ĳ�ʼ��ҵ��У�����");
	
    return true;
}
