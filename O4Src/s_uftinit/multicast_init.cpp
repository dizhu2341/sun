#include "multicast_init.h"
#include "monitor.h"

int PackAnswerPackage(IAS2Context * lpContext, IF2Packer* pack, int nErrorNo, const char* pErrorInfo)
{
    pack->AddField("error_no");
    pack->AddField("error_info");
    pack->AddInt(nErrorNo);
    pack->AddStr(pErrorInfo);
    DLOGEVENT(lpContext,"���񷵻ز���:ErrNO[" << nErrorNo << "]ErrInfo[" << pErrorInfo << "]");
    return nErrorNo;
}

int  FUNCTION_CALL_MODE F615011( IAS2Context * lpContext, IF2UnPacker * in, IF2Packer * out)
{
    bool bRet = false;
    char ErrInfo[5000];

    //��ȡ��ʼ������
    int nInitDate = in->GetInt("init_date");
    int nCenterId = in->GetInt("branch_no");
    if (nInitDate == 0)
    {
        return PackAnswerPackage(lpContext, out, -100, "�����ʼ������Ϊ0!");
    }
    DLOGEVENT(lpContext, "�������init_date[" << nInitDate << "]center_id[" << nCenterId << "]");

    CMonitor * lpMonitor = new CMonitor(lpContext);

    //--------------------------------------
    // ��ȡ���׺��ķ�������Ϣ�б�
    DLOGEVENT(lpContext,"��ʼ��ȡ�ڵ��б�...");
    bRet = lpMonitor->GetServerListInfo();
    if (! bRet)
    {
        sprintf(ErrInfo, "��ȡ���׺��ķ�������Ϣ�б�ʧ��[%s]!", lpMonitor->GetErrorInfo());
        delete lpMonitor;
        return PackAnswerPackage(lpContext, out, -101, ErrInfo);
    }
    DLOGEVENT(lpContext,"��ȡ�������б�...���ɹ���");

    //--------------------------------------
    // �������ڵ�
    DLOGEVENT(lpContext,"��ʼִ�и��ڵ�����...");
    bRet = lpMonitor->RebootCresServers();
    if (!bRet)
    {
        sprintf(ErrInfo, "�������ڵ�����ʧ��[%s]", lpMonitor->GetErrorInfo());
        delete lpMonitor;
        return PackAnswerPackage(lpContext, out, -102, ErrInfo);
    }
    DLOGEVENT(lpContext,"���ڵ������ű�ִ��...���ɹ���");

    //----------------------------------------------------------------
    // �жϸ����ڵ��Ƿ������ɹ�
    DLOGEVENT(lpContext,"�����ڵ��Ƿ������ɹ�...");
    bRet = lpMonitor->IsRebootNormal();
    if (!bRet)
    {
        sprintf(ErrInfo, "�ڵ������쳣:[%s]!", lpMonitor->GetErrorInfo());
        delete lpMonitor;
        return PackAnswerPackage(lpContext, out, -102, ErrInfo);
    }
    DLOGEVENT(lpContext,"���ڵ�����״̬...���ɹ���");

    //�л�ǰ�û�Ϊ�ǹ���ģʽ
    //TODO-û�б�Ҫ
    //   DLOGEVENT(lpContext,"��ʼ�л�ǰ�û�Ϊ�ǹ���ģʽ...");
    //   bRet = lpMonitor->SetFrontUnWork();
    //   if (! bRet)
    //   {
    //       sprintf(ErrInfo, "�л�ǰ�û����ǹ���ģʽʧ��[%s]!", lpMonitor->GetErrorInfo());
    //       delete lpMonitor;
    //       return PackAnswerPackage(out, -102, ErrInfo);
    //   }
    //   DLOGEVENT(lpContext,"�л�ǰ�û�Ϊ�ǹ���ģʽ...���ɹ���");

    DLOGEVENT(lpContext,"����DBInit��ʼ������...");

    char sName[128] = "init";
    bRet = lpMonitor->InitData(nInitDate, nCenterId, sName);
    if (! bRet)
    {
        sprintf(ErrInfo, "DBInit��ʼ������ʧ��[%s]!", lpMonitor->GetErrorInfo());
        delete lpMonitor;
        return PackAnswerPackage(lpContext, out, -102, ErrInfo);
    }
    DLOGEVENT(lpContext,"����DBInit��ʼ������... ���ɹ���");

    //-------------------------------------------------------------
    // �жϽ��׺��Ľڵ��Ƿ��ʼ���ɹ�
    DLOGEVENT(lpContext,"��ʼ�����ڵ��Ƿ���뽻��״̬...");
    bRet = lpMonitor->IsBeginTrade();
    if (! bRet)
    {
        sprintf(ErrInfo, "�ȴ����׺��Ľ��뽻��״̬ʧ��[%s]", lpMonitor->GetErrorInfo());
        delete lpMonitor;
        return PackAnswerPackage(lpContext, out, -104, ErrInfo);
    }
    DLOGEVENT(lpContext,"�����ڵ��Ƿ���뽻��״̬...���ɹ���");

    //�л�ǰ�û�Ϊ����ģʽ
    DLOGEVENT(lpContext,"��ʼ�л�ǰ�û�Ϊ����ģʽ...");
    bRet = lpMonitor->SetFrontWork();
    if (! bRet)
    {
        sprintf(ErrInfo, "UFT��ʼ���Ѿ��ɹ�, ���л�ǰ�û�������ģʽʧ��[%s]���볢���ֹ��л�ǰ�û�������ģʽ!", lpMonitor->GetErrorInfo());
        delete lpMonitor;
        return PackAnswerPackage(lpContext, out, 0, ErrInfo);
    }
    DLOGEVENT(lpContext,"�л�ǰ�û�Ϊ����ģʽ...���ɹ���");

    delete lpMonitor;
    return PackAnswerPackage(lpContext, out, 0, "UFT��ʼ���ɹ���");
}


//�����Խ�UFM���ճ�ʼ������

int  FUNCTION_CALL_MODE F460011( IAS2Context * lpContext, IF2UnPacker * in, IF2Packer * out)
{
    bool bRet = false;
    char ErrInfo[5000] = {0};

    //��ȡ��ʼ������
    int nInitDate = in->GetInt("init_date");
    int nCenterId = 35;
    if (nInitDate == 0)
    {
        return PackAnswerPackage(lpContext, out, -101, "�����ʼ������Ϊ0!");
    }
    DLOGEVENT(lpContext, "�������init_date[" << nInitDate << "]center_id[" << nCenterId << "]");

    CMonitor * lpMonitor = new CMonitor(lpContext);

    //--------------------------------------
    // ��ȡ���׺��ķ�������Ϣ�б�
    DLOGEVENT(lpContext,"��ʼ��ȡ�������б�...");
    bRet = lpMonitor->GetServerListInfo();
    if (! bRet)
    {
        sprintf(ErrInfo, "��ȡUFM��������Ϣ�б�ʧ��[%s]!", lpMonitor->GetErrorInfo());
        delete lpMonitor;
        return PackAnswerPackage(lpContext, out, -102, ErrInfo);
    }
    DLOGEVENT(lpContext,"��ȡ�������б�...���ɹ���");

    //--------------------------------------
    // �������ڵ�
    DLOGEVENT(lpContext,"��ʼִ�и��ڵ�����...");
    bRet = lpMonitor->RebootCresServers();
    if (!bRet)
    {
        sprintf(ErrInfo, "�������ڵ�����ʧ��[%s]", lpMonitor->GetErrorInfo());
        delete lpMonitor;
        return PackAnswerPackage(lpContext, out, -103, ErrInfo);
    }
    DLOGEVENT(lpContext,"���ڵ������ű�ִ��...���ɹ���");

    //----------------------------------------------------------------
    // �жϸ����ڵ��Ƿ������ɹ�
    DLOGEVENT(lpContext,"�����ڵ��Ƿ������ɹ�...");
    bRet = lpMonitor->IsRebootNormal();
    if (!bRet)
    {
        sprintf(ErrInfo, "�����������쳣:[%s]!", lpMonitor->GetErrorInfo());
        delete lpMonitor;
        return PackAnswerPackage(lpContext, out, -104, ErrInfo);
    }
    DLOGEVENT(lpContext,"������������״̬...���ɹ���");

    //�л�ǰ�û�Ϊ�ǹ���ģʽ
    DLOGEVENT(lpContext,"��ʼ�л�ǰ�û�Ϊ�ǹ���ģʽ...");
    bRet = lpMonitor->SetFrontUnWork();
    if (! bRet)
    {
        sprintf(ErrInfo, "�л�ǰ�û����ǹ���ģʽʧ��[%s]!", lpMonitor->GetErrorInfo());
        delete lpMonitor;
        return PackAnswerPackage(lpContext, out, -102, ErrInfo);
    }
    DLOGEVENT(lpContext,"�л�ǰ�û�Ϊ�ǹ���ģʽ...���ɹ���");

    DLOGEVENT(lpContext,"����DBInit��ʼ������...");
    char sName[128] = "init";
    bRet = lpMonitor->InitData(nInitDate, nCenterId, sName);
    if (! bRet)
    {
        sprintf(ErrInfo, "DBInit��ʼ������ʧ��[%s]!", lpMonitor->GetErrorInfo());
        delete lpMonitor;
        return PackAnswerPackage(lpContext, out, -102, ErrInfo);
    }
    DLOGEVENT(lpContext,"����DBInit��ʼ������...���ɹ���");

    //-------------------------------------------------------------
    // �жϸ��ڵ��Ƿ���Կ�ʼ����
    DLOGEVENT(lpContext,"��ʼ�����ڵ��Ƿ���뽻��״̬...");
    bRet = lpMonitor->IsBeginTrade();
    if (! bRet)
    {
        sprintf(ErrInfo, "�ȴ�UFM���뽻��״̬ʧ��[%s]", lpMonitor->GetErrorInfo());
        delete lpMonitor;
        return PackAnswerPackage(lpContext, out, -110, ErrInfo);
    }
    DLOGEVENT(lpContext,"�����ڵ��Ƿ���뽻��״̬...���ɹ���");

    //�л�ǰ�û�Ϊ����ģʽ
    DLOGEVENT(lpContext,"��ʼ�л�ǰ�û�Ϊ����ģʽ...");
    bRet = lpMonitor->SetFrontWork();
    if (! bRet)
    {
        sprintf(ErrInfo, "UFM��ʼ���Ѿ��ɹ�, ���л�ǰ�û�������ģʽʧ�ܣ��볢���ֹ��л�ǰ�û�������ģʽ!");
        delete lpMonitor;
        return PackAnswerPackage(lpContext, out, 0, ErrInfo);
    }
    DLOGEVENT(lpContext,"�л�ǰ�û�Ϊ����ģʽ...���ɹ���");

    delete lpMonitor;
    return PackAnswerPackage(lpContext, out, 0, "UFM��ʼ���ɹ���");
}

int FUNCTION_CALL_MODE F615012( IAS2Context * lpContext, IF2UnPacker * lpInUnPacker, IF2Packer * lpOutPacker)
{
    bool bRet = false;
    char ErrInfo[5000];
    //��ȡ��ʼ������
    int nInitDate = lpInUnPacker->GetInt("init_date");
    if (nInitDate == 0)
    {
        return PackAnswerPackage(lpContext, lpOutPacker, -100, "�����ʼ������Ϊ0!");
    }
    DLOGEVENT(lpContext, "�������init_date[" << nInitDate << "]");

    CMonitor * lpMonitor = new CMonitor(lpContext);

    //--------------------------------------
    //��ʱ���������鲥��UFT
    DLOGEVENT(lpContext,"��ʼ������ʱ��������...");

    int nCenterId = 0;
    char sName[128] = "preclear_tmp";
    bRet = lpMonitor->LoadCSV(nInitDate, nCenterId, sName);
    if (!bRet)
    {
        sprintf(ErrInfo, "������ʱ��������ʧ��[%s]!", lpMonitor->GetErrorInfo());
        delete lpMonitor;
        return PackAnswerPackage(lpContext, lpOutPacker, -101, ErrInfo);
    }
    DLOGEVENT(lpContext,"������ʱ��������...���ɹ���");

    // ����DBInit��ʼ�鲥��ʱ��������
    DLOGEVENT(lpContext,"����DBInit�鲥��ʱ��������...");
    bRet = lpMonitor->SendData(nInitDate);
    if (!bRet)
    {
        sprintf(ErrInfo, "DBInit�鲥��ʱ��������ʧ��[%s]!", lpMonitor->GetErrorInfo());
        delete lpMonitor;
        return PackAnswerPackage(lpContext, lpOutPacker, -104, ErrInfo);
    }
    DLOGEVENT(lpContext,"DBInit�鲥��ʱ��������...���ɹ���");

    delete lpMonitor;
    return PackAnswerPackage(lpContext, lpOutPacker, 0, "UFT�������ݣ���ʱ���ɹ���");
}

int FUNCTION_CALL_MODE F615013( IAS2Context * lpContext, IF2UnPacker * lpInUnPacker, IF2Packer * lpOutPacker)
{
    bool bRet = false;
    char ErrInfo[5000];
    //��ȡ��ʼ������
    int nInitDate = lpInUnPacker->GetInt("init_date");
    if (nInitDate == 0)
    {
        return PackAnswerPackage(lpContext, lpOutPacker, -100, "�����ʼ������Ϊ0!");
    }
    int nBatchNo = lpInUnPacker->GetInt("batch_no");

    DLOGEVENT(lpContext, "�������init_date[" << nInitDate << "]batch_no[" << nBatchNo << "]");

    CMonitor * lpMonitor = new CMonitor(lpContext);

    DLOGEVENT(lpContext,"��ʼ�����������ݵ�Oplus...");
    char sName[128] = "preclear_h3";
    bRet = lpMonitor->FormalInitData(nInitDate, sName, nBatchNo);
    if (!bRet)
    {
        sprintf(ErrInfo, "�����������ݵ�Oplusʧ��[%s]!", lpMonitor->GetErrorInfo());
        delete lpMonitor;
        return PackAnswerPackage(lpContext, lpOutPacker, -101, ErrInfo);
    }
    DLOGEVENT(lpContext,"����Oplus��������...���ɹ���");

    //---------------------------------------------------------------
    // �жϽ��׺����Ƿ�ɹ����ճ�ʼ������
    DLOGEVENT(lpContext,"��ʼ�����ڵ��Ƿ�������ݽ���... ");
    bRet = lpMonitor->IsDataReceived();
    if (!bRet)
    {
        sprintf(ErrInfo, "�ȴ����׺��Ľ��ս����쳣[%s]!", lpMonitor->GetErrorInfo());
        delete lpMonitor;
        return PackAnswerPackage(lpContext, lpOutPacker, -103, ErrInfo);
    }
    DLOGEVENT(lpContext,"�����ڵ�������ݽ���...���ɹ���");

    DLOGEVENT(lpContext,"��ʼ����UFT�������ݼ������...");
    bRet = lpMonitor->CalcUFTData();
    if (!bRet)
    {
        sprintf(ErrInfo, "UFT�������ݼ���������ʧ��[%s]!", lpMonitor->GetErrorInfo());
        delete lpMonitor;
        return PackAnswerPackage(lpContext, lpOutPacker, -105, ErrInfo);
    }
    DLOGEVENT(lpContext,"����UFT�������ݼ������...���ɹ���");

    delete lpMonitor;
    return PackAnswerPackage(lpContext, lpOutPacker, 0, "UFT����Oplus���ݳɹ���");
}

int FUNCTION_CALL_MODE F615014( IAS2Context * lpContext, IF2UnPacker * lpInUnPacker, IF2Packer * lpOutPacker)
{
    DLOGEVENT(lpContext,"��ʼUFT��ʽ����... ");

    bool bRet = false;
    char ErrInfo[5000];
    //��ȡ��ʼ������
    int nInitDate = lpInUnPacker->GetInt("init_date");
    if (nInitDate == 0)
    {
        return PackAnswerPackage(lpContext, lpOutPacker, -100, "�����ʼ������Ϊ0!");
    }
    DLOGEVENT(lpContext, "�������init_date[" << nInitDate << "]");

    CMonitor * lpMonitor = new CMonitor(lpContext);

    //--------------------------------------
    // ��ȡ���׺��ķ�������Ϣ�б�
    DLOGEVENT(lpContext,"��ʼ��ȡ�������б�...");
    bRet = lpMonitor->GetServerListInfo();
    if (! bRet)
    {
        sprintf(ErrInfo, "��ȡ���׺��ķ�������Ϣ�б�ʧ��[%s]!", lpMonitor->GetErrorInfo());
        delete lpMonitor;
        return PackAnswerPackage(lpContext, lpOutPacker, -101, ErrInfo);
    }
    DLOGEVENT(lpContext,"��ȡ�������б�...���ɹ���");

    //--------------------------------------
    //���������鲥��UFT
    DLOGEVENT(lpContext,"��ʼ������ʽ��������... ");
    char sName[128] = "formalclear";
    bRet = lpMonitor->FormalInitData(nInitDate, sName);
    if (!bRet)
    {
        sprintf(ErrInfo, "������ʽ��������ʧ��[%s]!", lpMonitor->GetErrorInfo());
        delete lpMonitor;
        return PackAnswerPackage(lpContext, lpOutPacker, -101, ErrInfo);
    }
    DLOGEVENT(lpContext,"������ʽ��������...���ɹ���");

    //---------------------------------------------------------------
    // �жϽ��׺����Ƿ�ɹ����ճ�ʼ������
    DLOGEVENT(lpContext,"��ʼ�����ڵ��Ƿ�������ݽ���...");
    bRet = lpMonitor->IsDataReceived();
    if (!bRet)
    {
        sprintf(ErrInfo, "�ȴ����׺��Ľ��ս����쳣[%s]!", lpMonitor->GetErrorInfo());
        delete lpMonitor;
        return PackAnswerPackage(lpContext, lpOutPacker, -103, ErrInfo);
    }
    DLOGEVENT(lpContext,"�����ڵ�������ݽ���...���ɹ���");

    //---------------------------------------------------------------
    DLOGEVENT(lpContext,"��ʼ����UFT�������ݼ������...");
    bRet = lpMonitor->CalcUFTData();
    if (!bRet)
    {
        sprintf(ErrInfo, "UFT�������ݼ���������ʧ��[%s]!", lpMonitor->GetErrorInfo());
        delete lpMonitor;
        return PackAnswerPackage(lpContext, lpOutPacker, -105, ErrInfo);
    }
    DLOGEVENT(lpContext,"����UFT�������ݼ������...���ɹ���");

    delete lpMonitor;
    DLOGEVENT(lpContext,"UFT��ʽ����ɹ���");
    return PackAnswerPackage(lpContext, lpOutPacker, 0, "UFT��ʽ����ɹ���");
}

int  FUNCTION_CALL_MODE F615015( IAS2Context * lpContext, IF2UnPacker * in, IF2Packer * out)
{
    bool bRet = false;
    bool bRet1 = false;
    char ErrInfo[5000];

    //��ȡ��ʼ������
    int nInitDate = in->GetInt("init_date");
    int nCenterId = in->GetInt("branch_no");
    if (nInitDate == 0)
    {
        return PackAnswerPackage(lpContext, out, -100, "�����ʼ������Ϊ0!");
    }
    DLOGEVENT(lpContext, "�������init_date[" << nInitDate << "]center_id[" << nCenterId << "]");

    CMonitor * lpMonitor = new CMonitor(lpContext);

    //--------------------------------------
    // ��ȡ���׺��ķ�������Ϣ�б�
    DLOGEVENT(lpContext,"��ʼ��ȡ�ڵ��б�...");
    bRet = lpMonitor->GetServerListInfo();
    if (! bRet)
    {
        sprintf(ErrInfo, "��ȡ���׺��ķ�������Ϣ�б�ʧ��[%s]!", lpMonitor->GetErrorInfo());
        delete lpMonitor;
        return PackAnswerPackage(lpContext, out, -101, ErrInfo);
    }
    DLOGEVENT(lpContext,"��ȡ�������б�...���ɹ���");

    //--------------------------------------
    // �������ڵ�
    DLOGEVENT(lpContext,"��ʼִ�и��ڵ�����...");
    bRet = lpMonitor->RebootCresServers();
    if (!bRet)
    {
        sprintf(ErrInfo, "�������ڵ�����ʧ��[%s]", lpMonitor->GetErrorInfo());
        delete lpMonitor;
        return PackAnswerPackage(lpContext, out, -102, ErrInfo);
    }
    DLOGEVENT(lpContext,"���ڵ������ű�ִ��...���ɹ���");

    //----------------------------------------------------------------
    // �жϸ����ڵ��Ƿ������ɹ�
    DLOGEVENT(lpContext,"�����ڵ��Ƿ������ɹ�...");
    bRet = lpMonitor->IsRebootNormal();
    if (!bRet)
    {
        sprintf(ErrInfo, "�ڵ������쳣:[%s]!", lpMonitor->GetErrorInfo());
        delete lpMonitor;
        return PackAnswerPackage(lpContext, out, -102, ErrInfo);
    }
    DLOGEVENT(lpContext,"���ڵ�����״̬...���ɹ���");


    DLOGEVENT(lpContext,"����DBInit��ʼ������...");

    char sName[128] = "init";
    bRet = lpMonitor->InitData(nInitDate, nCenterId, sName);
    
    //-------------------------------------------------------------
    // �жϽ��׺��Ľڵ��Ƿ��ʼ���ɹ�
    DLOGEVENT(lpContext,"��ʼ�����ڵ��Ƿ���뽻��״̬...");
    bRet = lpMonitor->IsBeginTrade();
    if (! bRet)
    {
        sprintf(ErrInfo, "�ȴ����׺��Ľ��뽻��״̬ʧ��[%s]", lpMonitor->GetErrorInfo());
        delete lpMonitor;
        return PackAnswerPackage(lpContext, out, -104, ErrInfo);
    }
    DLOGEVENT(lpContext,"�����ڵ��Ƿ���뽻��״̬...���ɹ���");

// todo
    char sName1[128] = "ypsj";
    bRet1 = lpMonitor->UpgradeInitData(nInitDate, nCenterId, sName1);
    if (! bRet || ! bRet1)
    {
        sprintf(ErrInfo, "DBInit��ʼ������ʧ��[%s]!", lpMonitor->GetErrorInfo());
        delete lpMonitor;
        return PackAnswerPackage(lpContext, out, -102, ErrInfo);
    }
    DLOGEVENT(lpContext,"����DBInit��ʼ������... ���ɹ���");


    //�л�ǰ�û�Ϊ����ģʽ
    DLOGEVENT(lpContext,"��ʼ�л�ǰ�û�Ϊ����ģʽ...");
    bRet = lpMonitor->SetFrontWork();
    if (! bRet)
    {
        sprintf(ErrInfo, "UFT��ʼ���Ѿ��ɹ�, ���л�ǰ�û�������ģʽʧ��[%s]���볢���ֹ��л�ǰ�û�������ģʽ!", lpMonitor->GetErrorInfo());
        delete lpMonitor;
        return PackAnswerPackage(lpContext, out, 0, ErrInfo);
    }
    DLOGEVENT(lpContext,"�л�ǰ�û�Ϊ����ģʽ...���ɹ���");
    
    DLOGEVENT(lpContext,"��ʼ����UFT�ֲ���ϸ����...");
    bRet = lpMonitor->SyncUFTHoldingdetail();
    if (!bRet)
    {
        sprintf(ErrInfo, "����UFT�ֲ���ϸ����ʧ��[%s]!", lpMonitor->GetErrorInfo());
        delete lpMonitor;
        return PackAnswerPackage(lpContext, out, -105, ErrInfo);
    }
    DLOGEVENT(lpContext,"����UFT�ֲ���ϸ����...���ɹ���");

    delete lpMonitor;
    return PackAnswerPackage(lpContext, out, 0, "ҹ��������ɣ�UFT��ʼ���ɹ���");
}


//�ӱ��ض�csv�ķ�ʽ�������ճ�ʼ������

int  FUNCTION_CALL_MODE F615021( IAS2Context * lpContext, IF2UnPacker * in, IF2Packer * out)
{
    bool bRet = false;
    char ErrInfo[5000];

    //��ȡ��ʼ������
    int nInitDate = in->GetInt("init_date");
    int nCenterId = in->GetInt("branch_no");
    if (nInitDate == 0)
    {
        return PackAnswerPackage(lpContext, out, -100, "�����ʼ������Ϊ0!");
    }
    DLOGEVENT(lpContext, "�������init_date[" << nInitDate << "]center_id[" << nCenterId << "]");

    CMonitor * lpMonitor = new CMonitor(lpContext);

    //--------------------------------------
    // ��ȡ���׺��ķ�������Ϣ�б�
    DLOGEVENT(lpContext,"��ʼ��ȡ�������б�...");
    bRet = lpMonitor->GetServerListInfo();
    if (! bRet)
    {
        sprintf(ErrInfo, "��ȡ���׺��ķ�������Ϣ�б�ʧ��[%s]!", lpMonitor->GetErrorInfo());
        delete lpMonitor;
        return PackAnswerPackage(lpContext, out, -101, ErrInfo);
    }
    DLOGEVENT(lpContext,"��ȡ�������б�...���ɹ���");

    //--------------------------------------
    // �������ڵ�
    DLOGEVENT(lpContext,"��ʼִ�и��ڵ�����...");
    bRet = lpMonitor->RebootCresServers();
    if (!bRet)
    {
        sprintf(ErrInfo, "�������ڵ�����ʧ��[%s]", lpMonitor->GetErrorInfo());
        delete lpMonitor;
        return PackAnswerPackage(lpContext, out, -102, ErrInfo);
    }
    DLOGEVENT(lpContext,"���ڵ������ű�ִ��...���ɹ���");

    //----------------------------------------------------------------
    // �жϸ����ڵ��Ƿ������ɹ�
    DLOGEVENT(lpContext,"�����ڵ��Ƿ������ɹ�...");
    bRet = lpMonitor->IsRebootNormal();
    if (!bRet)
    {
        sprintf(ErrInfo, "�����������쳣:[%s]!", lpMonitor->GetErrorInfo());
        delete lpMonitor;
        return PackAnswerPackage(lpContext, out, -102, ErrInfo);
    }
    DLOGEVENT(lpContext,"������������״̬...���ɹ���");

    //----------------------------------------------------------------
    // ����dbinit�������csv������ѯ�ʽ��׺����Ƿ���Խ������ݡ�
    DLOGEVENT(lpContext,"����DBInit����csv...");

    char sName[128] = "init";
    bRet = lpMonitor->LoadLocalCSV(nInitDate, nCenterId, sName);
    if (! bRet)
    {
        sprintf(ErrInfo, "DBInit��ʼ��ʧ��[%s]!", lpMonitor->GetErrorInfo());
        delete lpMonitor;
        return PackAnswerPackage(lpContext, out, -102, ErrInfo);
    }
    DLOGEVENT(lpContext,"����DBInit����csv...���ɹ���");

    //-----------------------------------------------------------------
    // �жϽ��׺��ķ������Ƿ�׼���á���ʼ���ճ�ʼ������
    DLOGEVENT(lpContext,"�����ڵ��Ƿ�������ݽ���׼��״̬...");
    bRet = lpMonitor->IsPrepareInit();
    if (! bRet)
    {
        sprintf(ErrInfo, "���׺����޷���ʼ���ճ�ʼ������[%s]!", lpMonitor->GetErrorInfo());
        delete lpMonitor;
        return PackAnswerPackage(lpContext, out, -103, ErrInfo);
    }
    DLOGEVENT(lpContext,"���ڵ����׼����������״̬...");

    //----------------------------------------------------------------
    // ����DBInit��ʼ�鲥��������
    DLOGEVENT(lpContext,"����DBInit�鲥��������...");
    bRet = lpMonitor->SendData(nInitDate, nCenterId);
    if (!bRet)
    {
        sprintf(ErrInfo, "DBInit�鲥��������ʧ��[%s]!", lpMonitor->GetErrorInfo());
        delete lpMonitor;
        return PackAnswerPackage(lpContext, out, -104, ErrInfo);
    }
    DLOGEVENT(lpContext,"DBInit�鲥��������...���ɹ���");

    //---------------------------------------------------------------
    // �жϽ��׺����Ƿ�ɹ����ճ�ʼ������
    DLOGEVENT(lpContext,"��ʼ�����ڵ��Ƿ�������ݽ���...");
    bRet = lpMonitor->IsDataReceived();
    if (!bRet)
    {
        sprintf(ErrInfo, "�ȴ����׺��Ľ��ս����쳣[%s]!", lpMonitor->GetErrorInfo());
        delete lpMonitor;
        return PackAnswerPackage(lpContext, out, -103, ErrInfo);
    }
    DLOGEVENT(lpContext,"�����ڵ�������ݽ���...���ɹ���");

    //---------------------------------------------------------------
    // ���ó�ʼ������,׼������
    DLOGEVENT(lpContext,"���ͳ�ʼ���������...");
    bRet = lpMonitor->SetInitEnd(nInitDate);
    if (! bRet)
    {
        sprintf(ErrInfo, "���ó�ʼ����������쳣[%s]!", lpMonitor->GetErrorInfo());
        delete lpMonitor;
        return PackAnswerPackage(lpContext, out, -103, ErrInfo);
    }
    DLOGEVENT(lpContext,"���ͳ�ʼ���������...���ɹ���");

    //-------------------------------------------------------------
    // �жϸ��ڵ��Ƿ���Կ�ʼ����
    DLOGEVENT(lpContext,"��ʼ�����ڵ��Ƿ���뽻��״̬...");
    bRet = lpMonitor->IsBeginTrade();
    if (! bRet)
    {
        sprintf(ErrInfo, "�ȴ����׺��Ľ��뽻��״̬ʧ��[%s]", lpMonitor->GetErrorInfo());
        delete lpMonitor;
        return PackAnswerPackage(lpContext, out, -104, ErrInfo);
    }
    DLOGEVENT(lpContext,"�����ڵ��Ƿ���뽻��״̬...���ɹ���");

    //�л�ǰ�û�Ϊ����ģʽ
    DLOGEVENT(lpContext,"��ʼ�л�ǰ�û�Ϊ����ģʽ...");
    bRet = lpMonitor->SetFrontWork();
    if (! bRet)
    {
        sprintf(ErrInfo, "UFT��ʼ���Ѿ��ɹ�, ���л�ǰ�û�������ģʽʧ�ܣ��볢���ֹ��л�ǰ�û�������ģʽ!");
        delete lpMonitor;
        return PackAnswerPackage(lpContext, out, 0, ErrInfo);
    }
    DLOGEVENT(lpContext,"�л�ǰ�û�Ϊ����ģʽ...���ɹ���");

    delete lpMonitor;
    return PackAnswerPackage(lpContext, out, 0, "UFT��ʼ���ɹ���");
}

//UFM���ض�csv�ķ�ʽ�������ճ�ʼ������

int  FUNCTION_CALL_MODE F460021( IAS2Context * lpContext, IF2UnPacker * in, IF2Packer * out)
{
    bool bRet = false;
    char ErrInfo[5000] = {0};

    //��ȡ��ʼ������
    int nInitDate = in->GetInt("init_date");
    int nCenterId = 35;
    if (nInitDate == 0)
    {
        return PackAnswerPackage(lpContext, out, -101, "�����ʼ������Ϊ0!");
    }
    DLOGEVENT(lpContext, "�������init_date[" << nInitDate << "]center_id[" << nCenterId << "]");

    CMonitor * lpMonitor = new CMonitor(lpContext);

    //--------------------------------------
    // ��ȡ���׺��ķ�������Ϣ�б�
    DLOGEVENT(lpContext,"��ʼ��ȡ�������б�...");
    bRet = lpMonitor->GetServerListInfo();
    if (! bRet)
    {
        sprintf(ErrInfo, "��ȡUFM��������Ϣ�б�ʧ��[%s]!", lpMonitor->GetErrorInfo());
        delete lpMonitor;
        return PackAnswerPackage(lpContext, out, -102, ErrInfo);
    }
    DLOGEVENT(lpContext,"��ȡ�������б�...���ɹ���");

    //--------------------------------------
    // �������ڵ�
    DLOGEVENT(lpContext,"��ʼִ�и��ڵ�����...");
    bRet = lpMonitor->RebootCresServers();
    if (!bRet)
    {
        sprintf(ErrInfo, "�������ڵ�����ʧ��[%s]", lpMonitor->GetErrorInfo());
        delete lpMonitor;
        return PackAnswerPackage(lpContext, out, -103, ErrInfo);
    }
    DLOGEVENT(lpContext,"���ڵ������ű�ִ��...���ɹ���");

    //----------------------------------------------------------------
    // �жϸ����ڵ��Ƿ������ɹ�
    DLOGEVENT(lpContext,"�����ڵ��Ƿ������ɹ�...");
    bRet = lpMonitor->IsRebootNormal();
    if (!bRet)
    {
        sprintf(ErrInfo, "�����������쳣:[%s]!", lpMonitor->GetErrorInfo());
        delete lpMonitor;
        return PackAnswerPackage(lpContext, out, -104, ErrInfo);
    }
    DLOGEVENT(lpContext,"������������״̬...���ɹ���");

    //----------------------------------------------------------------
    // ����dbinit�������csv������ѯ�ʽ��׺����Ƿ���Խ������ݡ�
    DLOGEVENT(lpContext,"����DBInit����csv...");

    char sName[128] = "init";
    bRet = lpMonitor->LoadLocalCSV(nInitDate, nCenterId, sName);
    if (! bRet)
    {
        sprintf(ErrInfo, "DBInit��ʼ��ʧ��[%s]!", lpMonitor->GetErrorInfo());
        delete lpMonitor;
        return PackAnswerPackage(lpContext, out, -105, ErrInfo);
    }
    DLOGEVENT(lpContext,"����DBInit����csv...���ɹ���");

    //-----------------------------------------------------------------
    // �жϽ��׺��ķ������Ƿ�׼���á���ʼ���ճ�ʼ������
    DLOGEVENT(lpContext,"�����ڵ��Ƿ�������ݽ���׼��״̬...");
    bRet = lpMonitor->IsPrepareInit();
    if (! bRet)
    {
        sprintf(ErrInfo, "UFM�޷���ʼ���ճ�ʼ������[%s]!", lpMonitor->GetErrorInfo());
        delete lpMonitor;
        return PackAnswerPackage(lpContext, out, -106, ErrInfo);
    }
    DLOGEVENT(lpContext,"���ڵ����׼����������״̬...");

    //----------------------------------------------------------------
    // ����DBInit��ʼ�鲥��������
    DLOGEVENT(lpContext,"����DBInit�鲥��������...");
    bRet = lpMonitor->SendData(nInitDate, 35);
    if (!bRet)
    {
        sprintf(ErrInfo, "DBInit�鲥��������ʧ��[%s]!", lpMonitor->GetErrorInfo());
        delete lpMonitor;
        return PackAnswerPackage(lpContext, out, -107, ErrInfo);
    }
    DLOGEVENT(lpContext,"DBInit�鲥��������...���ɹ���");

    //---------------------------------------------------------------
    // �жϽ��׺����Ƿ�ɹ����ճ�ʼ������
    DLOGEVENT(lpContext,"��ʼ�����ڵ��Ƿ�������ݽ���...");
    bRet = lpMonitor->IsDataReceived();
    if (!bRet)
    {
        sprintf(ErrInfo, "�ȴ�UFM���ս����쳣[%s]!", lpMonitor->GetErrorInfo());
        delete lpMonitor;
        return PackAnswerPackage(lpContext, out, -108, ErrInfo);
    }
    DLOGEVENT(lpContext,"�����ڵ�������ݽ���...���ɹ���");

    //---------------------------------------------------------------
    // ���ó�ʼ������,׼������
    DLOGEVENT(lpContext,"���ͳ�ʼ���������...");
    bRet = lpMonitor->SetInitEnd(nInitDate, 35);
    if (! bRet)
    {
        sprintf(ErrInfo, "���ó�ʼ����������쳣[%s]!", lpMonitor->GetErrorInfo());
        delete lpMonitor;
        return PackAnswerPackage(lpContext, out, -109, ErrInfo);
    }
    DLOGEVENT(lpContext,"���ͳ�ʼ���������...���ɹ���");

    //-------------------------------------------------------------
    // �жϸ��ڵ��Ƿ���Կ�ʼ����
    DLOGEVENT(lpContext,"��ʼ�����ڵ��Ƿ���뽻��״̬...");
    bRet = lpMonitor->IsBeginTrade();
    if (! bRet)
    {
        sprintf(ErrInfo, "�ȴ�UFM���뽻��״̬ʧ��[%s]", lpMonitor->GetErrorInfo());
        delete lpMonitor;
        return PackAnswerPackage(lpContext, out, -110, ErrInfo);
    }
    DLOGEVENT(lpContext,"�����ڵ��Ƿ���뽻��״̬...���ɹ���");

    //�л�ǰ�û�Ϊ����ģʽ
    DLOGEVENT(lpContext,"��ʼ�л�ǰ�û�Ϊ����ģʽ...");
    bRet = lpMonitor->SetFrontWork();
    if (! bRet)
    {
        sprintf(ErrInfo, "UFT��ʼ���Ѿ��ɹ�, ���л�ǰ�û�������ģʽʧ�ܣ��볢���ֹ��л�ǰ�û�������ģʽ!");
        delete lpMonitor;
        return PackAnswerPackage(lpContext, out, 0, ErrInfo);
    }
    DLOGEVENT(lpContext,"�л�ǰ�û�Ϊ����ģʽ...���ɹ���");

    delete lpMonitor;
    return PackAnswerPackage(lpContext, out, 0, "UFM��ʼ���ɹ���");
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
            if  (ppv != NULL)
            {
                ppv->dwFunctionNo = 615011;        //���ܺ�
                ppv->iVersion = 20121212;       //version��Ϣ
                ppv->ReqProc = F615011;            //���ܺ���ָ��
                ppv->AnsProc = NULL;            //Ӧ���������
                ppv->Caption = "��ؽ��׺���װ̬";      //������������
            }
            break;
        case 1:
            if  (ppv != NULL)
            {
                ppv->dwFunctionNo = 615012;        //���ܺ�
                ppv->iVersion = 20121212;       //version��Ϣ
                ppv->ReqProc = F615012;            //���ܺ���ָ��
                ppv->AnsProc = NULL;            //Ӧ���������
                ppv->Caption = "���������鲥��UFT��ʱ";      //������������
            }
            break;
        case 2:
            if  (ppv != NULL)
            {
                ppv->dwFunctionNo = 615013;        //���ܺ�
                ppv->iVersion = 20121212;       //version��Ϣ
                ppv->ReqProc = F615013;            //���ܺ���ָ��
                ppv->AnsProc = NULL;            //Ӧ���������
                ppv->Caption = "���������鲥��Oplus";      //������������
            }
            break;
        case 3:
            if  (ppv != NULL)
            {
                ppv->dwFunctionNo = 615014;        //���ܺ�
                ppv->iVersion = 20121212;       //version��Ϣ
                ppv->ReqProc = F615014;            //���ܺ���ָ��
                ppv->AnsProc = NULL;            //Ӧ���������
                ppv->Caption = "���������鲥��UFT";      //������������
            }
            break;
        case 4:
            if  (ppv != NULL)
            {
                ppv->dwFunctionNo = 615021;        //���ܺ�
                ppv->iVersion = 20121212;       //version��Ϣ
                ppv->ReqProc = F615021;            //���ܺ���ָ��
                ppv->AnsProc = NULL;            //Ӧ���������
                ppv->Caption = "���ر���CSV���ճ�ʼ��";      //������������
            }
            break;
        case 5:
            if  (ppv != NULL)
            {
                ppv->dwFunctionNo = 460011;        //���ܺ�
                ppv->iVersion = 20160407;       //version��Ϣ
                ppv->ReqProc = F460011;            //���ܺ���ָ��
                ppv->AnsProc = NULL;            //Ӧ���������
                ppv->Caption = "UFM��ʼ��";      //������������
            }
            break;
        case 6:
            if  (ppv != NULL)
            {
                ppv->dwFunctionNo = 460021;        //���ܺ�
                ppv->iVersion = 20160407;       //version��Ϣ
                ppv->ReqProc = F460021;            //���ܺ���ָ��
                ppv->AnsProc = NULL;            //Ӧ���������
                ppv->Caption = "���ر���CSV��UFM��ʼ��";      //������������
            }
            break;
        case 7:
			if  (ppv != NULL)
			{
				ppv->dwFunctionNo = 615015;        //���ܺ�
				ppv->iVersion = 20170408;       //version��Ϣ
				ppv->ReqProc = F615015;            //���ܺ���ָ��
				ppv->AnsProc = NULL;            //Ӧ���������
				ppv->Caption = "ҹ�������鲥���ݵ�UFT";      //������������
			}
			break;
        default:
            iRet = ASFC_NONE;
    }
    return iRet;
}


//��ȡ�����Ϣ

char *  FUNCTION_CALL_MODE GetLibVersion( )
{
    return __DATE__;
}

