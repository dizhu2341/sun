#include "monitor.h"
#include <string.h>
#include <stdlib.h>

//--------------------------------------------
// ˯�ߣ�����Ϊ����

void MSleep(int nCount)
{
#ifdef _WIN32
    Sleep(nCount * 1000);
#else
    sleep(nCount);
#endif
}

CMonitor::CMonitor(IAS2Context* lpContext)
{
    // �����ļ�
    char fileName[30] = { "statcfg.ini" };

    // ��ʼ����Ա����
    m_nErrorNo = 0;
    strcpy(m_szErrorMessage, "");
    m_lpContext = NULL;
    m_nMaxTryTimes = 5;
    m_lpContext = lpContext;

    // ��ȡ������Ϣ
    rebootTryCount = read_profile_int("trycount", "reboot", 60, fileName);
    preInitTryCount = read_profile_int("trycount", "preinit", 60, fileName);
    cacheRecvTryCount = read_profile_int("trycount", "cacherecv", 100, fileName);
    beginTradeTryCount = read_profile_int("trycount", "begintrade", 10, fileName);

    frontstartWait = read_profile_int("sleep", "frontstart", 5, fileName);
    cacheRecvWait = 100;
    m_nRMTimeOut = read_profile_int("timeout", "RMTimeOut", 60000, fileName);
    DLOGDEBUG(m_lpContext, "Reboot[" << rebootTryCount << "]Dbinit[" << preInitTryCount << "]CacheRecv[" << cacheRecvTryCount << "]");

    m_mPluginMap["uftinit"] = 2;
    m_mPluginMap["tradelogsvr"] = 4;
    m_mPluginMap["hsuftfront"] = 4;
    m_mPluginMap["hsuft"] = 22;
    m_mPluginMap["hsuft#1"] = 22;
    m_mPluginMap["com.hundsun.acd.queue"] = 7;
    m_mPluginMap["hundsun.o4.Utodb"] = 12;
    m_mPluginMap["hundsun.o4.Risktodb"] = 12;
    m_mPluginMap["hundsun.o4.PubMessage"] = 12;
}

CMonitor::~CMonitor()
{
    try
    {
        for (vector<CSvrNode*>::iterator itSvr = m_vecSvrNode.begin(); itSvr != m_vecSvrNode.end(); ++itSvr)
        {
            delete (*itSvr);
        }
        m_vecSvrNode.clear();
    }
    catch (...)
    {

    }
}

IF2UnPacker* CMonitor::CallService(int FuncNo, IF2Packer* inPack, int TimeOut, int BranchNo)
{
    m_nErrorNo = 0;
    strcpy(m_szErrorMessage, "");

    if (NULL == m_lpContext)
        return NULL;

    // ����ESB�����
    IESBMessage*  lpRequestESB = NULL;
    lpRequestESB = m_lpContext->GetESBMsgFactory()->GetESBMsg();
    if (NULL == lpRequestESB)
    {
        DLOGERROR(m_lpContext,-100, "ESB���������ʧ��!");
        return NULL;
    }
    lpRequestESB->Prepare(REQUEST_PACKET, FuncNo);
    if (BranchNo > 0)
        lpRequestESB->GetItem(TAG_BRANCH_NO)->SetInt(BranchNo);
    lpRequestESB->GetItem(TAG_MESSAGE_BODY)->SetRawData(inPack->GetPackBuf(), inPack->GetPackLen());   //ҵ���帴�Ƶ���Ϣ��

    //�����ӷ���,����ʧ��ʱ��������Ϣ�ѱ��ͷ�
    IESBMessage* lpAnswerESB = NULL;
    int iRet = m_lpContext->CallSubService(lpRequestESB, &lpAnswerESB, TimeOut);
    if ((iRet != 0) || (NULL == lpAnswerESB))
    {
        m_nErrorNo = iRet;
        switch (iRet)
        {
            case -1:
            {
                sprintf(m_szErrorMessage, "[%d]����ʧ��,������Ϣ�ѱ��ͷ�", FuncNo);
                break;
            }
            case -2:
            {
                sprintf(m_szErrorMessage, "[%d]���ó�ʱ,������������Ҫ�ط�", FuncNo);
                break;
            }
            default:
            {
                m_nErrorNo = -3;
                sprintf(m_szErrorMessage, "[%d]δ֪����", FuncNo);
            }
        };
        DLOGERROR(m_lpContext,-100, "��������쳣:" << m_szErrorMessage);
        return NULL;
    }

    // ����ҵ���
    void *lpData = NULL;
    int nLen = 0;
    iRet = lpAnswerESB->GetItem(TAG_RETURN_CODE)->GetInt();
    lpData = (void*)lpAnswerESB->GetItem(TAG_MESSAGE_BODY)->GetRawData(&nLen);
    if ((NULL == lpData) || (nLen <= 0))
    {
        m_nErrorNo = lpAnswerESB->GetItem(TAG_ERROR_NO)->GetInt();
        strcpy(m_szErrorMessage, lpAnswerESB->GetItem(TAG_ERROR_INFO)->GetString());
        lpAnswerESB->Release();
        DLOGERROR(m_lpContext,-100, "[" << FuncNo << "]��������쳣:" << m_szErrorMessage);
        return NULL;
    }

    //����ҵ�����
    IF2UnPacker* unPacker = m_lpContext->GetF2PackSvr()->GetUnPacker(lpData, nLen);
    if (NULL == unPacker)
    {
        lpAnswerESB->Release();
        DLOGERROR(m_lpContext,-100, "[" << FuncNo << "]���������ʧ��!");
        return NULL;
    }
    unPacker->AddRef();
    unPacker->Open(lpData, nLen);

    if (iRet != 0)
    {
        const char *lpErrNo = unPacker->GetStr("error_no");
        const char *lpErrInfo = unPacker->GetStr("error_info");
        if (NULL != lpErrNo)
        {
            m_nErrorNo = atoi(lpErrNo);
        }
        else
            m_nErrorNo = -99;

        if (NULL != lpErrInfo)
        {
            strcpy(m_szErrorMessage, lpErrInfo);
        }
        else
            strcpy(m_szErrorMessage, "δ֪����");

        unPacker->Release();
        lpAnswerESB->Release();
        DLOGERROR(m_lpContext,-100, "[" << FuncNo << "]��������쳣:" << m_szErrorMessage);
        return NULL;
    }
    lpAnswerESB->Release();
    //lpRequestESB = NULL;
    return unPacker;
}

bool CMonitor::GetServerListInfo()
{
    bool bRet = false;

    char xmlfile[128] = "svrcfginfo.xml";
    TiXmlDocument doc(xmlfile);
    bRet = doc.LoadFile();
    if (!bRet)
    {
        m_nErrorNo = -110;
        sprintf(m_szErrorMessage, "�޷�����XML��svrcfginfo.xml����%s", doc.ErrorDesc());
        DLOGERROR(m_lpContext,m_nErrorNo, m_szErrorMessage);
        return bRet;
    }
    //    TiXmlPrinter printer;//�ṩ�Ĺ�����,Ŀ���ǽ�xml�����ݰ���ʽ���
    //    doc.Accept(&printer);
    //    LOGDEBUG("xml string:" << printer.CStr());
    //ʹ�ñ����ķ�ʽ���д���
    TiXmlNode* pChildNode = NULL;
    TiXmlElement* pElement = NULL;
    TiXmlAttribute *pAttr = NULL;
    char sAttrName[32] = {0};

    while (pChildNode = doc.RootElement()->FirstChild()->IterateChildren(pChildNode))
    {
        if (pChildNode->Type() == TiXmlNode::TINYXML_COMMENT)
        {
            continue;
        }

        pElement = pChildNode->ToElement();
        pAttr = pElement->FirstAttribute();
        CSvrNode *pSvrNode = new CSvrNode();
        while (pAttr)
        {
            strcpy(sAttrName, pAttr->NameTStr().c_str());
            if (strcmp(sAttrName, "user") == 0)
            {
                strcpy(pSvrNode->m_sUser, pAttr->ValueStr().c_str());
            }
            else if (strcmp(sAttrName, "passwd") == 0)
            {
                strcpy(pSvrNode->m_sPasswd, pAttr->ValueStr().c_str());
            }
            else if (strcmp(sAttrName, "name") == 0)
            {
                strcpy(pSvrNode->m_sName, pAttr->ValueStr().c_str());
            }
            else if (strcmp(sAttrName, "server_ip") == 0)
            {
                strcpy(pSvrNode->m_sIP, pAttr->ValueStr().c_str());
            }
            else if (strcmp(sAttrName, "runscript") == 0)
            {
                strcpy(pSvrNode->m_sRunscript, pAttr->ValueStr().c_str());
            }
            else if (strcmp(sAttrName, "stopscript") == 0)
            {
                strcpy(pSvrNode->m_sStopscript, pAttr->ValueStr().c_str());
            }
            pAttr = pAttr->Next();
        }

        TiXmlNode* pPluginNode = NULL;
        TiXmlElement* pPluginElement = NULL;
        TiXmlAttribute *pPluginAttr = NULL;
        CSvrPlugin *pSvrPlugin = NULL;
        while (pPluginNode = pChildNode->IterateChildren(pPluginNode))
        {
            if (pPluginNode->Type() == TiXmlNode::TINYXML_COMMENT)
            {
                continue;
            }
            pPluginElement = pPluginNode->ToElement();
            pPluginAttr = pPluginElement->FirstAttribute();
            pSvrPlugin = new CSvrPlugin();
            while (pPluginAttr)
            {
                strcpy(sAttrName, pPluginAttr->NameTStr().c_str());
                if (strcmp(sAttrName, "name") == 0)
                {
                    strcpy(pSvrPlugin->m_sName, pPluginAttr->ValueStr().c_str());
                }
                else if (strcmp(sAttrName, "type") == 0)
                {
                    strcpy(pSvrPlugin->m_sType, pPluginAttr->ValueStr().c_str());
                }
                pPluginAttr = pPluginAttr->Next();
            }
            pSvrNode->AddSvrPlugin(pSvrPlugin);
        }
        m_vecSvrNode.push_back(pSvrNode);
    }
    //��ӡ��ȡ���Ľڵ���Ϣ
    //    PrintSvrInfo();

    return true;
}

IF2UnPacker* CMonitor::CallServiceEx(int FuncNo, IF2Packer* inPack, int TimeOut, int BranchNo)
{
    IF2UnPacker * unPack = NULL;
    for (int i = 0; i < 3; ++i)
    {
        unPack = CallService(FuncNo, inPack, TimeOut, BranchNo);
        if ((-1 != m_nErrorNo) &&
                (-2 != m_nErrorNo) &&
                (-3 != m_nErrorNo))
            break;
        DLOGWARNING(m_lpContext, "[" << FuncNo << "]��" << i + 1 << "�����Ե���");
    }
    return unPack;
}

//------------------------------------------------------------------
// ���ù��ܺ��������ݵ�����CSV

bool CMonitor::LoadCSV(int nInitDate, int nCenterId, char* sName)
{
    if (!m_lpContext)
        return false;

    IF2Packer *inPack = m_lpContext->GetF2PackSvr()->GetPacker(2);
    inPack->BeginPack();
    inPack->AddField("op_branch_no");
    inPack->AddField("operator_no");
    inPack->AddField("op_password");
    inPack->AddField("date", 'I');
    inPack->AddField("force");
    inPack->AddField("center_id", 'I');
    inPack->AddField("batch");				//ԭ�ȵ�name��ʾ���Σ��ĳ�batch��ʾ
    inPack->AddStr("1");
    inPack->AddStr("23");
    inPack->AddStr("{F#%')+-/");
    inPack->AddInt(nInitDate);
    inPack->AddStr("0");
    inPack->AddInt(nCenterId);
    inPack->AddStr(sName);
    inPack->EndPack();

    IF2UnPacker * unPack = CallServiceEx(514452, inPack, m_nRMTimeOut, nCenterId);

    inPack->FreeMem(inPack->GetPackBuf());
    inPack->Release();

    if (NULL == unPack)
        return false;

    if (atoi(unPack->GetStr("error_no")) != 0)
    {
        m_nErrorNo = atoi(unPack->GetStr("error_no"));
        strcpy(m_szErrorMessage, unPack->GetStr("error_info"));
    }
    unPack->Release();

    return 0 == m_nErrorNo;
}

//------------------------------------------------------------------
// ���ù��ܺţ�dbinit�������csv���ڴ�

bool CMonitor::LoadLocalCSV(int nInitDate, int nCenterId, char* sName)
{
    if (!m_lpContext)
        return false;

    IF2Packer *inPack = m_lpContext->GetF2PackSvr()->GetPacker(2);
    inPack->BeginPack();
    inPack->AddField("op_branch_no");
    inPack->AddField("operator_no");
    inPack->AddField("op_password");
    inPack->AddField("date", 'I');
    inPack->AddField("force");
    inPack->AddField("center_id", 'I');
    inPack->AddField("batch");				//ԭ�ȵ�name��ʾ���Σ��ĳ�batch��ʾ
    inPack->AddStr("1");
    inPack->AddStr("23");
    inPack->AddStr("{F#%')+-/");
    inPack->AddInt(nInitDate);
    inPack->AddStr("1");
    inPack->AddInt(nCenterId);
    inPack->AddStr(sName);
    inPack->EndPack();

    IF2UnPacker * unPack = CallServiceEx(514452, inPack, m_nRMTimeOut, nCenterId);

    inPack->FreeMem(inPack->GetPackBuf());
    inPack->Release();

    if (NULL == unPack)
        return false;

    if (atoi(unPack->GetStr("error_no")) != 0)
    {
        m_nErrorNo = atoi(unPack->GetStr("error_no"));
        strcpy(m_szErrorMessage, unPack->GetStr("error_info"));
    }
    unPack->Release();

    return 0 == m_nErrorNo;
}

bool CMonitor::FormalInitData(int nInitDate, char* sName, int nBatchNo)
{
    if (!m_lpContext)
        return false;

    IF2Packer *inPack = m_lpContext->GetF2PackSvr()->GetPacker(2);
    inPack->BeginPack();
    inPack->AddField("op_branch_no");
    inPack->AddField("operator_no");
    inPack->AddField("op_password");
    inPack->AddField("date", 'I');
    inPack->AddField("force");
    inPack->AddField("function_id");
    inPack->AddField("batch");				//ԭ�ȵ�name��ʾ���Σ��ĳ�batch��ʾ
    inPack->AddField("batch_no", 'I');
    inPack->AddStr("1");
    inPack->AddStr("23");
    inPack->AddStr("{F#%')+-/");
    inPack->AddInt(nInitDate);
    inPack->AddStr("0");
    inPack->AddStr("*");
    inPack->AddStr(sName);
    inPack->AddInt(nBatchNo);
    inPack->EndPack();

    IF2UnPacker * unPack = CallServiceEx(514459, inPack, m_nRMTimeOut);

    inPack->FreeMem(inPack->GetPackBuf());
    inPack->Release();

    if (NULL == unPack)
        return false;

    if (atoi(unPack->GetStr("error_no")) != 0)
    {
        m_nErrorNo = atoi(unPack->GetStr("error_no"));
        strcpy(m_szErrorMessage, unPack->GetStr("error_info"));
    }
    unPack->Release();

    return 0 == m_nErrorNo;
}

bool CMonitor::SendData(int nInitDate, int nCenterID)
{
    if (!m_lpContext)
        return false;
    IF2Packer *inPack = m_lpContext->GetF2PackSvr()->GetPacker(2);
    inPack->BeginPack();
    inPack->AddField("op_branch_no");
    inPack->AddField("operator_no");
    inPack->AddField("op_password");
    inPack->AddField("date", 'I');
    inPack->AddField("force");
    inPack->AddStr("1");
    inPack->AddStr("23");
    inPack->AddStr("{F#%')+-/");
    inPack->AddInt(nInitDate);
    inPack->AddStr("0");
    inPack->EndPack();

    IF2UnPacker* unPack = CallServiceEx(514453, inPack, m_nRMTimeOut, nCenterID);

    inPack->FreeMem(inPack->GetPackBuf());
    inPack->Release();

    if (!unPack)
        return false;

    if (atoi(unPack->GetStr("error_no")) != 0)
    {
        m_nErrorNo = atoi(unPack->GetStr("error_no"));
        strcpy(m_szErrorMessage, unPack->GetStr("error_info"));
    }
    unPack->Release();

    return 0 == m_nErrorNo;
}

bool CMonitor::RebootCresServers()
{
    DLOGDEBUG(m_lpContext, "��ʼ�������з���ڵ�...");
    if ( !RebootNodes() )   return false;
    DLOGDEBUG(m_lpContext, "��������ڵ�ű�ִ��...���ɹ���");

    return true;
}

bool CMonitor::RebootNodes()
{
    if (!CloseNodes())
        return false;
    if (!OpenNodes())
        return false;
    return true;
}

//-----------------------------------
// �л�ǰ�û�״̬Ϊ�ǹ���ģʽ

bool CMonitor::SetFrontUnWork()
{
    int nFuncID = 5;
    bool bIsWorkModel = false;
    for (vector<CSvrNode*>::const_iterator itSvr = m_vecSvrNode.begin(); itSvr != m_vecSvrNode.end(); ++itSvr)
    {
        for (vector<CSvrPlugin*>::const_iterator itPlugin = (*itSvr)->m_vecSvrPlugin.begin(); itPlugin != (*itSvr)->m_vecSvrPlugin.end(); ++itPlugin)
        {
            //ֻ���ǰ�ò��
            if (SVRTYPE_FRONT != (string)(*itPlugin)->m_sType)
                continue;
            IF2UnPacker* unPacker = CallPluginSvr((*itSvr)->m_sName, (*itPlugin)->m_sName, nFuncID, 5000);
            if ((unPacker != NULL) && (unPacker->GetInt("system_status") == SYS_STATUS_PAUSE))
            {
                unPacker->Release();
                bIsWorkModel = true;
            }
            else
            {
                return false;
            }
        }
    }

    return bIsWorkModel;
}

//-----------------------------------
// �л�ǰ�û�״̬Ϊ����ģʽ

bool CMonitor::SetFrontWork()
{
    int nFuncID = 6;
    bool bIsWorkModel = false;
    for (vector<CSvrNode*>::const_iterator itSvr = m_vecSvrNode.begin(); itSvr != m_vecSvrNode.end(); ++itSvr)
    {
        for (vector<CSvrPlugin*>::const_iterator itPlugin = (*itSvr)->m_vecSvrPlugin.begin(); itPlugin != (*itSvr)->m_vecSvrPlugin.end(); ++itPlugin)
        {
            //ֻ���ǰ�ò��
            if (SVRTYPE_FRONT != (string)(*itPlugin)->m_sType)
                continue;
            IF2UnPacker* unPacker = CallPluginSvr((*itSvr)->m_sName, (*itPlugin)->m_sName, nFuncID, 5000);
            if ((unPacker != NULL) && (unPacker->GetInt("system_status") == SYS_STATUS_SUCCESS))
            {
                unPacker->Release();
                bIsWorkModel = true;
            }
            else
            {
                return false;
            }
        }
    }

    return bIsWorkModel;
}

//---------------------------------------------------
// SSH �������нڵ�

bool CMonitor::OpenNodes()
{
    for (vector<CSvrNode*>::const_iterator itSvr = m_vecSvrNode.begin(); itSvr != m_vecSvrNode.end(); ++itSvr)
    {
        DLOGDEBUG(m_lpContext, "��ʼ������" << (*itSvr)->m_sName << "��");
        if (!SshCommand((*itSvr)->m_sIP, (*itSvr)->m_sUser, (*itSvr)->m_sPasswd, (*itSvr)->m_sRunscript, NULL))
        {
        	return false;
        }
        DLOGDEBUG(m_lpContext, "������" << (*itSvr)->m_sName << "���ű�ִ�����");
    }

    return true;
}

//---------------------------------------------------
// SSH �ر�ĳ�ڵ�

bool CMonitor::CloseNodes()
{
    for (vector<CSvrNode*>::const_iterator itSvr = m_vecSvrNode.begin(); itSvr != m_vecSvrNode.end(); ++itSvr)
    {
        DLOGDEBUG(m_lpContext, "��ʼ�رա�" << (*itSvr)->m_sName << "��");
        if(!SshCommand((*itSvr)->m_sIP, (*itSvr)->m_sUser, (*itSvr)->m_sPasswd, NULL, (*itSvr)->m_sStopscript))
        {
        	return false;
        }
        DLOGDEBUG(m_lpContext, "�رա�" << (*itSvr)->m_sName << "���ű�ִ�����");
    }

    return true;
}

//-----------------------------------------------------
// �жϳ�ǰ�û���Ľڵ��Ƿ������ɹ���������ǰ�û�,UFT,UFR,��־������,

bool CMonitor::IsRebootNormal()
{
    for (int i = 0; i < rebootTryCount; ++i)
    {
        MSleep(1);  //���ε���֮����1s

        if (CheckRebootNormal())
            return true;
    }

    return false;
}

//-------------------------------------------------------
// �жϸ���������Ƿ��ʼ���ɹ�

bool CMonitor::CheckRebootNormal()
{
    for (int i = 0, j = 0; i < m_vecSvrNode.size(); ++i)
    {
        CSvrNode* lpSvr = m_vecSvrNode[i];

        //����ڵ��Ѿ������ɹ���������
        if (lpSvr->IsRebootOk)
            continue;

        for (j = 0; j < lpSvr->m_vecSvrPlugin.size(); ++j)
        {
            CSvrPlugin* lpPlugin = (CSvrPlugin*)lpSvr->m_vecSvrPlugin[j];

            //����Ҫ�����ٲû�������״̬
            if (SVRTYPE_ARB == (string)lpPlugin->m_sType)
                continue;

            // �������Ѿ������ɹ���������
            if (lpPlugin-> IsRebootOk)
                continue;

            int nStatus = GetSysStatus(lpSvr->m_sName, lpPlugin->m_sName);
            if (nStatus < 0)
            {
                DLOGWARNING(m_lpContext, "����ڵ�[" << lpSvr->m_sName << "]�Ĳ��[" << lpPlugin->m_sName << "]����������...");
                return false;
            }
            else if ((nStatus == SYS_STATUS_SUCCESS) || (nStatus == SYS_STATUS_PAUSE))
            {
                lpPlugin->m_nStatus = nStatus;
                lpPlugin->IsRebootOk = true;
                DLOGDEBUG(m_lpContext, "����ڵ�[" << lpSvr->m_sName << "]�Ĳ��[" << lpPlugin->m_sName << "]�����ɹ�.");
            }
            else
            {
                m_nErrorNo = -111;
                sprintf(m_szErrorMessage, "����ڵ�[%s]�Ĳ��[%s]����ʧ��.", lpSvr->m_sName, lpPlugin->m_sName);
                DLOGWARNING(m_lpContext, "����ڵ�[" << lpSvr->m_sName << "]�Ĳ��[" << lpPlugin->m_sName << "]״̬Ϊ" << nStatus << ",�˳��˴����.");
                return false;
            }
        }

        // ������в���������ɹ�, ��ڵ������ɹ�
        if (j == lpSvr->m_vecSvrPlugin.size())
        {
            lpSvr->IsRebootOk = true;
            DLOGDEBUG(m_lpContext, "����ڵ�[" << lpSvr->m_sName << "]�����ɹ�.");
        }
    }

    return true;
}

/**
 * ����8�Ź����ܲ�ѯָ�������ָ��������
 * @param sNodeFullName
 * @param sPluginName
 * @param nFuncID
 * @param TimeOut
 * @return ���ؽ����
 */
IF2UnPacker* CMonitor::CallPluginSvr(char* sNodeFullName, char* sPluginName, int nFuncID, int TimeOut)
{
    IF2Packer* lpInPack = m_lpContext->GetF2PackSvr()->GetPacker(2);
    lpInPack->BeginPack();
    lpInPack->AddField("plugin_id", 'S');
    lpInPack->AddField("function_id", 'I');
    lpInPack->AddStr(sPluginName);
    lpInPack->AddInt(nFuncID);
    lpInPack->EndPack();

    IESBMessage* lpAnsESB = NULL;
    IESBMessage*  lpReqMsg = m_lpContext->GetESBMsgFactory()->GetESBMsg();
    lpReqMsg->Prepare(REQUEST_PACKET, 8);
    lpReqMsg->GetItem(TAG_ROUTE_INFO)->SetString(sNodeFullName, IDX_OSPF_NAME);
    lpReqMsg->GetItem(TAG_MESSAGE_BODY)->SetRawData(lpInPack->GetPackBuf(), lpInPack->GetPackLen());

    int iRet = m_lpContext->CallSubService(lpReqMsg, &lpAnsESB, TimeOut);
    if ((iRet != 0) || (NULL == lpAnsESB))
    {
        m_nErrorNo = iRet;
        sprintf(m_szErrorMessage, "���ù����ܺ��쳣���ڵ�����%s��,�������%s���������Ƿ�ʱ��5s��", sNodeFullName, sPluginName);
        return NULL;
    }

    // ���ESB���Ƿ����
    iRet = lpAnsESB->GetItem(TAG_ERROR_NO)->GetInt();
    if (iRet)
    {
        m_nErrorNo = iRet;
        sprintf(m_szErrorMessage, "���ù�����ESB���쳣���ڵ�����%s��,�������%s����������Ϣ��%s��", sNodeFullName, sPluginName, lpAnsESB->GetItem(TAG_ERROR_INFO)->GetString());
        lpAnsESB->Release();
        return NULL;
    }

    // ���ҵ����Ƿ����
    void *lpData = NULL;
    int nLen = 0;
    iRet = lpAnsESB->GetItem(TAG_RETURN_CODE)->GetInt();
    lpData = (void*)lpAnsESB->GetItem(TAG_MESSAGE_BODY)->GetRawData(&nLen);
    if ((NULL == lpData) || (nLen <= 0))
    {
        m_nErrorNo = iRet;
        sprintf(m_szErrorMessage, "���ù�����ESB���쳣���ڵ�����%s��,�������%s����������Ϣ��%s��", sNodeFullName, sPluginName, lpAnsESB->GetItem(TAG_ERROR_INFO)->GetString());
        lpAnsESB->Release();
        return NULL;
    }

    //����ҵ�����
    IF2UnPacker* unPacker = m_lpContext->GetF2PackSvr()->GetUnPacker(lpData, nLen);
    unPacker->AddRef();
    unPacker->Open(lpData, nLen);

    if (iRet != 0)
    {
        m_nErrorNo = atoi(unPacker->GetStr("error_no"));
        sprintf(m_szErrorMessage, "���ù�����ҵ����쳣���ڵ�����%s��,�������%s����������Ϣ��%s��", sNodeFullName, sPluginName, unPacker->GetStr("error_info"));

        unPacker->Release();
        lpAnsESB->Release();
        return NULL;
    }
    lpAnsESB->Release();
    return unPacker;
}

int CMonitor::GetSvrStatus(char* sNodeFullName, char* sPluginName)
{
    int nSvrStatus = SYS_STATUS_FAIL;
    int nFuncID = 8;

    IF2UnPacker* unPacker = CallPluginSvr(sNodeFullName, sPluginName, nFuncID, 5000);
    if (unPacker == NULL)
        return -100;

    nSvrStatus = unPacker->GetInt("custom_status");
    unPacker->Release();

    return nSvrStatus;
}

int CMonitor::GetSysStatus(char* sNodeFullName, char* sPluginName)
{
    int nFuncID = m_mPluginMap[sPluginName];
    if (nFuncID <= 0)
    {
        m_nErrorNo = -100;
        sprintf(m_szErrorMessage, "�޷�ʶ��Ĳ�����ơ�%s��", sPluginName);
        return -100;
    }

    IF2UnPacker* unPacker = CallPluginSvr(sNodeFullName, sPluginName, nFuncID, 5000);
    if (unPacker == NULL)
        return -100;

    int nSysStatus = unPacker->GetInt("system_status");
    unPacker->Release();

    return nSysStatus;
}

/**
 * ��ȡδ�����ɹ��ڵ��б�
 */
string CMonitor::GetUnStartNodes()
{
    string nodes = "";
    for (vector<CSvrNode*>::const_iterator itSvr = m_vecSvrNode.begin(); itSvr != m_vecSvrNode.end(); ++itSvr)
    {
        for (vector<CSvrPlugin*>::const_iterator itPlugin = (*itSvr)->m_vecSvrPlugin.begin(); itPlugin != (*itSvr)->m_vecSvrPlugin.end(); ++itPlugin)
        {
            //����Ҫ����ǰ�û�������״̬
            if (SVRTYPE_FRONT == (string)(*itPlugin)->m_sType)
                continue;
            if (!(*itPlugin)->IsRebootOk)
            {
                nodes += (string)(*itPlugin)->m_sName + ",";
            }
        }
    }
    if (!nodes.empty())
    {
        nodes.erase(nodes.end() - 1);
    }
    return nodes;
}

//-----------------------------------------------------------------
// �жϸ��ڵ��Ƿ�׼���ó�ʼ�������ջ�������

bool CMonitor::IsPrepareInit()
{
    for (int i = 0; i < preInitTryCount; ++i)
    {
        MSleep(1);

        if (CheckPrepareInit())
            return true;
    }
    return false;
}

//---------------------------------------------------------
// �жϸ��ڵ��Ƿ����׼����ʼ��

bool CMonitor::CheckPrepareInit()
{
    int nUFRStatus = 0;
    int nUFTStatus = 0;
    for (vector<CSvrNode*>::const_iterator itSvr = m_vecSvrNode.begin(); itSvr != m_vecSvrNode.end(); ++itSvr)
    {
        for (vector<CSvrPlugin*>::const_iterator itPlugin = (*itSvr)->m_vecSvrPlugin.begin(); itPlugin != (*itSvr)->m_vecSvrPlugin.end(); ++itPlugin)
        {
            //����uft���ġ���У��
            if ((SVRTYPE_UFT != (string)(*itPlugin)->m_sType)&&(SVRTYPE_UFR != (string)(*itPlugin)->m_sType))
                continue;
            if ((*itPlugin)->m_nStatus == STATUS_INIT_START)
                continue;

            int nStatus = GetSvrStatus((*itSvr)->m_sName, (*itPlugin)->m_sName);

            if (SVRTYPE_UFT == (string)(*itPlugin)->m_sType)
            {
                nUFTStatus = nStatus % 10;        //UFT״̬ȡ��λ��
                if ((nUFTStatus == STATUS_INIT_START) && ((*itPlugin)->m_nStatus != STATUS_INIT_START))
                {
                    (*itPlugin)->m_nStatus = nUFTStatus;
                    DLOGDEBUG(m_lpContext, "����ڵ�[" << (*itSvr)->m_sName << "]������[" << (*itPlugin)->m_sName << ".uft]׼����ʼ��ʼ��.");
                }
                else
                {
                    DLOGDEBUG(m_lpContext, "����ڵ�[" << (*itSvr)->m_sName << "]������[" << (*itPlugin)->m_sName << ".uft]״̬Ϊ" << nUFTStatus << ",�˳��˴����.");
                    return false;
                }
            }
            else if (SVRTYPE_UFR == (string)(*itPlugin)->m_sType)
            {
                nUFRStatus = nStatus / 10;        //UFR״̬ȡʮλ��
                if (nUFRStatus == STATUS_INIT_START)
                {
                    (*itPlugin)->m_nStatus = nUFRStatus;
                    DLOGDEBUG(m_lpContext, "����ڵ�[" << (*itSvr)->m_sName << "]������[" << (*itPlugin)->m_sName << ".ufr]׼����ʼ��ʼ��.");
                }
                else
                {
                    DLOGDEBUG(m_lpContext, "����ڵ�[" << (*itSvr)->m_sName << "]������[" << (*itPlugin)->m_sName << ".ufr]״̬Ϊ" << nUFRStatus << ",�˳��˴����.");
                    return false;
                }
            }
        }
    }
    return true;
}

bool CMonitor::IsDataReceived()
{
    for (int i = 0; i < cacheRecvTryCount; ++i)
    {
        MSleep(1);

        if (CheckDataReceived())
            return true;
    }
    return false;
}

//---------------------------------------
// �Ƿ���뽻��״̬

bool CMonitor::IsBeginTrade()
{
    for (int i = 0; i < beginTradeTryCount; ++i)
    {
        if (m_nErrorNo == 0)
            MSleep(1);

        if (CheckBeginTrade())
            return true;
    }
    return false;
}

//---------------------------------------
// �жϸ����׺��Ľڵ��Ƿ�ʼ����

bool CMonitor::CheckBeginTrade()
{
    int nUFRStatus = 0;
    int nUFTStatus = 0;
    for (vector<CSvrNode*>::const_iterator itSvr = m_vecSvrNode.begin(); itSvr != m_vecSvrNode.end(); ++itSvr)
    {
        for (vector<CSvrPlugin*>::const_iterator itPlugin = (*itSvr)->m_vecSvrPlugin.begin(); itPlugin != (*itSvr)->m_vecSvrPlugin.end(); ++itPlugin)
        {
            if ((SVRTYPE_UFT != (string)(*itPlugin)->m_sType)&&(SVRTYPE_UFR != (string)(*itPlugin)->m_sType))
                continue;

            //����Ѿ����ڽ���״̬��������
            if ((*itPlugin)->m_nStatus == STATUS_TRADE)
                continue;
            //����Ѿ�����ʧ��״̬���򷵻�
            if ((*itPlugin)->m_nStatus == STATUS_ERROR)
                return false;

            m_nErrorNo = 0;
            int nStatus = GetSvrStatus((*itSvr)->m_sName, (*itPlugin)->m_sName);
            if (SVRTYPE_UFT == (string)(*itPlugin)->m_sType)
            {
                nUFTStatus = nStatus % 10;        //UFT״̬ȡ��λ��
                if (nUFTStatus == STATUS_TRADE)
                {
                    (*itPlugin)->m_nStatus = STATUS_TRADE;
                    DLOGDEBUG(m_lpContext, "����ڵ�[" << (*itSvr)->m_sName << "]������[" << (*itPlugin)->m_sName << ".uft]���뽻��״̬.");
                }
                else if (nUFTStatus == STATUS_ERROR)
                {
                    (*itPlugin)->m_nStatus = STATUS_ERROR;
                    //���ϴ����
                    m_nErrorNo = -111;
                    sprintf(m_szErrorMessage, "�뵽����ڵ�[%s]������[%s]���ڽڵ��workspace\\logĿ¼�²鿴��ش�����־!",
                            (*itSvr)->m_sName,
                            (*itPlugin)->m_sName);
                    DLOGERROR(m_lpContext,m_nErrorNo, "����ڵ�[" << (*itSvr)->m_sName << "]������[" << (*itPlugin)->m_sName << ".uft]�ճ�ʼ���쳣���޷����뽻��״̬.");
                    return false;
                }
                else
                {
                    DLOGDEBUG(m_lpContext, "����ڵ�[" << (*itSvr)->m_sName << "]������[" << (*itPlugin)->m_sName << ".uft]״̬Ϊ" << nUFTStatus << ",�˳��˴����.");
                    return false;
                }
            }
            else if (SVRTYPE_UFR == (string)(*itPlugin)->m_sType)
            {
                nUFRStatus = nStatus / 10;        //UFR״̬ȡʮλ��
                if (nUFRStatus == STATUS_TRADE)
                {
                    (*itPlugin)->m_nStatus = STATUS_TRADE;
                    DLOGDEBUG(m_lpContext, "����ڵ�[" << (*itSvr)->m_sName << "]������[" << (*itPlugin)->m_sName << ".ufr]���뽻��״̬..");
                }
                else if (nUFRStatus == STATUS_ERROR)
                {
                    (*itPlugin)->m_nStatus = STATUS_ERROR;
                    //���ϴ����
                    m_nErrorNo = -111;
                    sprintf(m_szErrorMessage, "�뵽����ڵ�[%s]������[%s]���ڽڵ��workspace\\logĿ¼�²鿴��ش�����־!",
                            (*itSvr)->m_sName,
                            (*itPlugin)->m_sName);
                    DLOGERROR(m_lpContext,m_nErrorNo, "����ڵ�[" << (*itSvr)->m_sName << "]������[" << (*itPlugin)->m_sName << ".ufr]�ճ�ʼ���쳣���޷����뽻��״̬.");
                    return false;
                }
                else
                {
                    DLOGDEBUG(m_lpContext, "����ڵ�[" << (*itSvr)->m_sName << "]������[" << (*itPlugin)->m_sName << ".ufr]״̬Ϊ" << nUFRStatus << ",�˳��˴����.");
                    return false;
                }
            }
        }
    }

    return true;
}

//-------------------------------------------------------
// �жϸ��ڵ��Ƿ���ջ������ݽ���

bool CMonitor::CheckDataReceived()
{
    int nUFRStatus = 0;
    int nUFTStatus = 0;
    for (vector<CSvrNode*>::const_iterator itSvr = m_vecSvrNode.begin(); itSvr != m_vecSvrNode.end(); ++itSvr)
    {
        for (vector<CSvrPlugin*>::const_iterator itPlugin = (*itSvr)->m_vecSvrPlugin.begin(); itPlugin != (*itSvr)->m_vecSvrPlugin.end(); ++itPlugin)
        {
            //����uft���ġ���У��
            if ((SVRTYPE_UFT != (string)(*itPlugin)->m_sType)&&(SVRTYPE_UFR != (string)(*itPlugin)->m_sType))
                continue;
            if ((*itPlugin)->m_nStatus == STATUS_INIT_END)
                continue;

            int nStatus = GetSvrStatus((*itSvr)->m_sName, (*itPlugin)->m_sName);

            if (SVRTYPE_UFR == (string)(*itPlugin)->m_sType)
            {
                nUFRStatus = nStatus / 10;        //UFR״̬ȡʮλ��
                if (nUFRStatus == STATUS_INIT_END)
                {
                    (*itPlugin)->m_nStatus = STATUS_INIT_END;
                    DLOGDEBUG(m_lpContext, "����ڵ�[" << (*itSvr)->m_sName << "]������[" << (*itPlugin)->m_sName << ".ufr]�������ݽ���.");
                }
                else
                {
                    DLOGDEBUG(m_lpContext, "����ڵ�[" << (*itSvr)->m_sName << "]������[" << (*itPlugin)->m_sName << ".ufr]״̬Ϊ" << nUFRStatus << ",�˳��˴����.");
                    return false;
                }
            }
            else if (SVRTYPE_UFT == (string)(*itPlugin)->m_sType)
            {
                nUFTStatus = nStatus % 10;        //UFT״̬ȡ��λ��
                if (nUFTStatus == STATUS_INIT_END)
                {
                    (*itPlugin)->m_nStatus = STATUS_INIT_END;
                    DLOGDEBUG(m_lpContext, "����ڵ�[" << (*itSvr)->m_sName << "]������[" << (*itPlugin)->m_sName << ".uft]�������ݽ���.");
                }
                else
                {
                    DLOGDEBUG(m_lpContext, "����ڵ�[" << (*itSvr)->m_sName << "]������[" << (*itPlugin)->m_sName << ".uft]״̬Ϊ" << nUFTStatus << ",�˳��˴����.");
                    return false;
                }
            }
        }
    }
    return true;
}

//-----------------------------------------
// ���ó�ʼ�����������뽻��״̬

bool CMonitor::SetInitEnd(int nInitDate, int nCenterID)
{
    if (!m_lpContext)
        return false;

    IF2Packer *inPack = m_lpContext->GetF2PackSvr()->GetPacker(2);
    inPack->BeginPack();
    inPack->AddField("op_branch_no");
    inPack->AddField("operator_no");
    inPack->AddField("op_password");
    inPack->AddField("date", 'I');
    inPack->AddField("force");
    inPack->AddStr("1");
    inPack->AddStr("23");
    inPack->AddStr("{F#%')+-/");
    inPack->AddInt(nInitDate);
    inPack->AddStr("0");
    inPack->EndPack();

    IF2UnPacker* unPack = CallServiceEx(514454, inPack, m_nRMTimeOut, nCenterID);

    inPack->FreeMem(inPack->GetPackBuf());
    inPack->Release();

    if (!unPack)
        return false;
    if (atoi(unPack->GetStr("error_no")) != 0)
    {
        m_nErrorNo = atoi(unPack->GetStr("error_no"));
        strcpy(m_szErrorMessage, unPack->GetStr("error_info"));
    }
    unPack->Release();

    return 0 == m_nErrorNo;
}

const char * CMonitor::GetErrorInfo()
{
    char errInfo[512];
    sprintf(errInfo, "%d:%s", m_nErrorNo, m_szErrorMessage);
    strcpy(m_szErrorMessage, errInfo);
    return m_szErrorMessage;
}

bool CMonitor::SshCommand(char* pIpAddress, char *pUser, char *pPasswd, char* pRunScript, char* pStopScript)
{
    char sSshCmd[1000] = {0};

    if (NULL != pStopScript)
    {
        //0429���Ҫ��˫�Ŷ�����»�������Ŷ���������������ϸ��Ҫ������kill
        if ((strstr(pStopScript, "stopqueue") != NULL) || (strstr(pStopScript, "stopuftcore") != NULL))
        {
            sprintf(sSshCmd, "\"source ~/.bash_profile; ps ux | grep mainsvr | grep hsserver | awk '{print \\$2}' |xargs kill -s 9;\"", pStopScript);
        }
        else
        {
            sprintf(sSshCmd, "'source ~/.bash_profile; cd ~/workspace; sh %s;'", pStopScript);
            //strcpy(sSshCmd, "'source ~/.bash_profile; pkill hsserver;'");
        }
        if (! ExecCommand(sSshCmd, pIpAddress, pUser, pPasswd))
        {
            m_nErrorNo = -108;
            DLOGERROR(m_lpContext, m_nErrorNo, m_szErrorMessage);
            return false;
        }

        if ((strstr(pStopScript, "stopqueue") != NULL) || (strstr(pStopScript, "stopuftcore") != NULL))
        {
            sleep(5);   //�����������˳�̫�죬��������������ԭ���Ĵ�����̻�û�˳�
        }
    }

    if (NULL != pRunScript)
    {
        struct tm current_time;
        time_t now = time(NULL);
        current_time = *localtime(&now);

        sprintf(sSshCmd, "'source ~/.bash_profile; cd ~/workspace; %s > log/%sout_%04d%02d%02d%02d%02d%02d.log 2>&1 &'",
                pRunScript, pRunScript, current_time.tm_year + 1900, current_time.tm_mon + 1, current_time.tm_mday,
                current_time.tm_hour, current_time.tm_min, current_time.tm_sec);
        if (! ExecCommand(sSshCmd, pIpAddress, pUser, pPasswd))
        {
            m_nErrorNo = -108;
            DLOGERROR(m_lpContext, m_nErrorNo, m_szErrorMessage);
            return false;
        }
        MSleep(1);
    }
    return true;
}

bool CMonitor::ExecCommand(char* pCmd, char* pIpAddress, char *pUser, char *pPasswd)
{
	FILE* fstream = NULL;
	char buffer[100] = {0};
    char sExecCmd[1024] = {0};
    DLOGDEBUG(m_lpContext, "Cmd:sshpass -p '***' ssh -o StrictHostKeyChecking=no " << pUser << "@" << pIpAddress << " " << pCmd);
    sprintf(sExecCmd, "sshpass -p '%s' ssh -o StrictHostKeyChecking=no %s@%s %s;echo $?", pPasswd, pUser, pIpAddress, pCmd);
    if(NULL == (fstream = popen(sExecCmd,"r")))
    {
       return -1;
    }
    fgets(buffer,sizeof(buffer),fstream);
    pclose(fstream);
    if(strncmp(buffer,"5",1)==0)
    {
    	sprintf(m_szErrorMessage, "����[%s]�û�[%s]ʧ�ܣ�����o4uftmgr�ڵ�workspaceĿ¼��svrcfginfo.xml�������Ƿ���ȷ", pIpAddress, pUser);
    	return false;
    }
    if(strncmp(buffer,"127",3)==0)
    {
    	sprintf(m_szErrorMessage, "�ű�ִ���쳣������svrcfginfo.xml�����Ƿ���ȷ�����ߵ�%s@%s��ִ��%s���������֤", pUser, pIpAddress, pCmd);
        return false;
    }
    return true;
}

//------------------------------------------
// ��ӡ�����ķ�����Ϣ

void CMonitor::PrintSvrInfo()
{
    DLOGDEBUG(m_lpContext, "��ȡ�����׽ڵ���Ϣ...");
    //TODO
}

bool CMonitor::ExportMemData()
{
    if ( ! ExportUFRMemData())
    {
        return false;
    }

    if ( ! ExportUFTMemData())
    {
        return false;
    }
    return true;
}

bool CMonitor::ExportUFRMemData()
{
    if (!m_lpContext)
        return false;

    IF2Packer *inPack = m_lpContext->GetF2PackSvr()->GetPacker(2);
    inPack->BeginPack();
    inPack->AddField("table_buffer");
    inPack->AddStr("-1");
    inPack->EndPack();
    IF2UnPacker* unPack = CallServiceEx(417101, inPack, 30000);
    inPack->FreeMem(inPack->GetPackBuf());
    inPack->Release();

    if (!unPack)
        return false;
    if (atoi(unPack->GetStr("error_no")) != 0)
    {
        m_nErrorNo = atoi(unPack->GetStr("error_no"));
        strcpy(m_szErrorMessage, unPack->GetStr("error_info"));
    }
    unPack->Release();

    return 0 == m_nErrorNo;
}

bool CMonitor::ExportUFTMemData()
{
    if (!m_lpContext)
        return false;

    IF2Packer *inPack = m_lpContext->GetF2PackSvr()->GetPacker(2);
    inPack->BeginPack();
    inPack->AddField("table_buffer");
    inPack->AddStr("-1");
    inPack->EndPack();
    IF2UnPacker* unPack = CallServiceEx(710506, inPack, 30000);
    inPack->FreeMem(inPack->GetPackBuf());
    inPack->Release();

    if (!unPack)
        return false;
    if (atoi(unPack->GetStr("error_no")) != 0)
    {
        m_nErrorNo = atoi(unPack->GetStr("error_no"));
        strcpy(m_szErrorMessage, unPack->GetStr("error_info"));
    }
    unPack->Release();
    return true;
}

//---------------------------------------
// ����Ŷӻ��Ƿ������ɹ�

bool CMonitor::IsFrontStart()
{
    for (int i = 0; i < rebootTryCount; ++i)
    {
        MSleep(1);  //���ε���֮����1s

        if (CheckFrontStart())
            return true;
    }

    return false;
}

bool CMonitor::CheckFrontStart()
{
    for (vector<CSvrNode*>::const_iterator itSvr = m_vecSvrNode.begin(); itSvr != m_vecSvrNode.end(); ++itSvr)
    {
        for (vector<CSvrPlugin*>::const_iterator itPlugin = (*itSvr)->m_vecSvrPlugin.begin(); itPlugin != (*itSvr)->m_vecSvrPlugin.end(); ++itPlugin)
        {
            if (SVRTYPE_FRONT != (string)(*itPlugin)->m_sType)
                continue;
            // ����Ѿ����������ɹ�״̬��������
            if (SYS_STATUS_SUCCESS == (*itPlugin)->m_nStatus)
                continue;
            int nStatus = GetSysStatus((*itSvr)->m_sName, (*itPlugin)->m_sName);
            if (nStatus == SYS_STATUS_SUCCESS)
            {
                (*itPlugin)->m_nStatus = nStatus;
                DLOGDEBUG(m_lpContext, "����ڵ�[" << (*itSvr)->m_sName << "]������[" << (*itPlugin)->m_sName << "]�����ɹ�.");
            }
            else
            {
                DLOGDEBUG(m_lpContext, "����ڵ�[" << (*itSvr)->m_sName << "]������[" << (*itPlugin)->m_sName << "]״̬Ϊ" << nStatus << ",�˳��˴����.");
                return false;
            }
        }
    }
    return true;
}

//-----------------------------------
// ����ǰ�û�

bool CMonitor::StartFront()
{
    DLOGDEBUG(m_lpContext, "��ʼ����ǰ�û�...");
    DLOGDEBUG(m_lpContext, "����ǰ�û��ű�ִ��...���ɹ���");
    return true;
}

bool CMonitor::CalcUFTData()
{
    if (!m_lpContext)
        return false;
    int nTimeOut = 300000;

    //����UFT�ļ��㹦�ܺ�
    /*  IF2Packer *inPack = m_lpContext->GetF2PackSvr()->GetPacker(2);
      inPack->BeginPack();
       inPack->EndPack();
    
       IF2UnPacker * unPack = CallServiceEx(710299, inPack, nTimeOut);

       inPack->FreeMem(inPack->GetPackBuf());
       inPack->Release();

       if (NULL == unPack)
           return false;
    
       m_nErrorNo = atoi(unPack->GetStr("error_no"));
	
       if (m_nErrorNo != 0)
       {
           strcpy(m_szErrorMessage, unPack->GetStr("error_info"));
           unPack->Release();
           return false;
       }
       unPack->Release();
     */
    //����UFR�ļ��㹦�ܺ�
    IF2Packer *inPack = m_lpContext->GetF2PackSvr()->GetPacker(2);
    inPack->BeginPack();
    inPack->EndPack();

    IF2UnPacker *unPack = CallServiceEx(417215, inPack, nTimeOut);

    inPack->FreeMem(inPack->GetPackBuf());
    inPack->Release();

    if (NULL == unPack)
        return false;

    m_nErrorNo = atoi(unPack->GetStr("error_no"));

    if (m_nErrorNo != 0)
    {
        strcpy(m_szErrorMessage, unPack->GetStr("error_info"));
        unPack->Release();
        return false;
    }
    unPack->Release();

    return true;
}

bool CMonitor::SyncUFTHoldingdetail()
{
    if (!m_lpContext)
        return false;
    int nTimeOut = 300000;
    
    IF2Packer *inPack = m_lpContext->GetF2PackSvr()->GetPacker(2);
    inPack->BeginPack();
    inPack->EndPack();

    IF2UnPacker *unPack = CallServiceEx(417884, inPack, nTimeOut);

    inPack->FreeMem(inPack->GetPackBuf());
    inPack->Release();

    if (NULL == unPack)
        return false;

    m_nErrorNo = atoi(unPack->GetStr("error_no"));

    if (m_nErrorNo != 0)
    {
        strcpy(m_szErrorMessage, unPack->GetStr("error_info"));
        unPack->Release();
        return false;
    }
    unPack->Release();

    return true;
}

bool CMonitor::InitData(int nInitDate, int nCenterId, char* sName)
{
    if (!m_lpContext)
        return false;

    IF2Packer *inPack = m_lpContext->GetF2PackSvr()->GetPacker(2);
    inPack->BeginPack();
    inPack->AddField("op_branch_no");
    inPack->AddField("operator_no");
    inPack->AddField("op_password");
    inPack->AddField("date", 'I');
    inPack->AddField("force");
    inPack->AddField("center_id", 'I');
    inPack->AddField("batch");				//ԭ�ȵ�name��ʾ���Σ��ĳ�batch��ʾ
    inPack->AddStr("1");
    inPack->AddStr("23");
    inPack->AddStr("{F#%')+-/");
    inPack->AddInt(nInitDate);
    inPack->AddStr("0");
    inPack->AddInt(nCenterId);
    inPack->AddStr(sName);
    inPack->EndPack();

    IF2UnPacker * unPack = CallServiceEx(514458, inPack, m_nRMTimeOut, nCenterId);

    inPack->FreeMem(inPack->GetPackBuf());
    inPack->Release();

    if (NULL == unPack)
        return false;

    if (atoi(unPack->GetStr("error_no")) != 0)
    {
        m_nErrorNo = atoi(unPack->GetStr("error_no"));
        strcpy(m_szErrorMessage, unPack->GetStr("error_info"));
    }
    unPack->Release();

    return 0 == m_nErrorNo;
}

bool CMonitor::UpgradeInitData(int nInitDate, int nCenterId, char* sName)
{
    if (!m_lpContext)
        return false;

    IF2Packer *inPack = m_lpContext->GetF2PackSvr()->GetPacker(2);
    inPack->BeginPack();
    inPack->AddField("op_branch_no");
    inPack->AddField("operator_no");
    inPack->AddField("op_password");
    inPack->AddField("date", 'I');
    inPack->AddField("force");
    inPack->AddField("center_id", 'I');
    inPack->AddField("batch");				//ԭ�ȵ�name��ʾ���Σ��ĳ�batch��ʾ
    inPack->AddStr("1");
    inPack->AddStr("23");
    inPack->AddStr("{F#%')+-/");
    inPack->AddInt(nInitDate);
    inPack->AddStr("0");
    inPack->AddInt(nCenterId);
    inPack->AddStr(sName);
    inPack->EndPack();

    IF2UnPacker * unPack = CallServiceEx(514459, inPack, m_nRMTimeOut, nCenterId);

    inPack->FreeMem(inPack->GetPackBuf());
    inPack->Release();

    if (NULL == unPack)
        return false;

    if (atoi(unPack->GetStr("error_no")) != 0)
    {
        m_nErrorNo = atoi(unPack->GetStr("error_no"));
        strcpy(m_szErrorMessage, unPack->GetStr("error_info"));
    }
    unPack->Release();

    return 0 == m_nErrorNo;
}

CSvrNode::CSvrNode()
{
    memset(m_sUser, 0 , sizeof (m_sUser));
    memset(m_sPasswd, 0 , sizeof (m_sPasswd));
    memset(m_sIP, 0 , sizeof (m_sIP));
    memset(m_sRunscript, 0 , sizeof (m_sRunscript));
    memset(m_sStopscript, 0 , sizeof (m_sStopscript));
    IsRebootOk = false;
}

CSvrNode::~CSvrNode()
{
    for (vector<CSvrPlugin*>::iterator itPlugin = m_vecSvrPlugin.begin(); itPlugin != m_vecSvrPlugin.end(); ++itPlugin)
    {
        delete (*itPlugin);
    }
    m_vecSvrPlugin.clear();
}

void CSvrNode::AddSvrPlugin(CSvrPlugin* pSvrPlugin)
{
    m_vecSvrPlugin.push_back(pSvrPlugin);
}

CSvrPlugin::CSvrPlugin()
{
    memset(m_sName, 0 , sizeof (m_sName));
    memset(m_sType, 0 , sizeof (m_sType));
    m_nStatus = -1;
    IsRebootOk = false;
}

CSvrPlugin::~CSvrPlugin()
{
}

