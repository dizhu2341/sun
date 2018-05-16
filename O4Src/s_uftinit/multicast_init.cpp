#include "multicast_init.h"
#include "monitor.h"

int PackAnswerPackage(IAS2Context * lpContext, IF2Packer* pack, int nErrorNo, const char* pErrorInfo)
{
    pack->AddField("error_no");
    pack->AddField("error_info");
    pack->AddInt(nErrorNo);
    pack->AddStr(pErrorInfo);
    DLOGEVENT(lpContext,"服务返回参数:ErrNO[" << nErrorNo << "]ErrInfo[" << pErrorInfo << "]");
    return nErrorNo;
}

int  FUNCTION_CALL_MODE F615011( IAS2Context * lpContext, IF2UnPacker * in, IF2Packer * out)
{
    bool bRet = false;
    char ErrInfo[5000];

    //获取初始化日期
    int nInitDate = in->GetInt("init_date");
    int nCenterId = in->GetInt("branch_no");
    if (nInitDate == 0)
    {
        return PackAnswerPackage(lpContext, out, -100, "传入初始化日期为0!");
    }
    DLOGEVENT(lpContext, "传入参数init_date[" << nInitDate << "]center_id[" << nCenterId << "]");

    CMonitor * lpMonitor = new CMonitor(lpContext);

    //--------------------------------------
    // 获取交易核心服务器信息列表
    DLOGEVENT(lpContext,"开始获取节点列表...");
    bRet = lpMonitor->GetServerListInfo();
    if (! bRet)
    {
        sprintf(ErrInfo, "获取交易核心服务器信息列表失败[%s]!", lpMonitor->GetErrorInfo());
        delete lpMonitor;
        return PackAnswerPackage(lpContext, out, -101, ErrInfo);
    }
    DLOGEVENT(lpContext,"获取服务器列表...【成功】");

    //--------------------------------------
    // 重启各节点
    DLOGEVENT(lpContext,"开始执行各节点重启...");
    bRet = lpMonitor->RebootCresServers();
    if (!bRet)
    {
        sprintf(ErrInfo, "服务器节点重启失败[%s]", lpMonitor->GetErrorInfo());
        delete lpMonitor;
        return PackAnswerPackage(lpContext, out, -102, ErrInfo);
    }
    DLOGEVENT(lpContext,"各节点重启脚本执行...【成功】");

    //----------------------------------------------------------------
    // 判断各个节点是否重启成功
    DLOGEVENT(lpContext,"检测各节点是否重启成功...");
    bRet = lpMonitor->IsRebootNormal();
    if (!bRet)
    {
        sprintf(ErrInfo, "节点重启异常:[%s]!", lpMonitor->GetErrorInfo());
        delete lpMonitor;
        return PackAnswerPackage(lpContext, out, -102, ErrInfo);
    }
    DLOGEVENT(lpContext,"检测节点重启状态...【成功】");

    //切换前置机为非工作模式
    //TODO-没有必要
    //   DLOGEVENT(lpContext,"开始切换前置机为非工作模式...");
    //   bRet = lpMonitor->SetFrontUnWork();
    //   if (! bRet)
    //   {
    //       sprintf(ErrInfo, "切换前置机至非工作模式失败[%s]!", lpMonitor->GetErrorInfo());
    //       delete lpMonitor;
    //       return PackAnswerPackage(out, -102, ErrInfo);
    //   }
    //   DLOGEVENT(lpContext,"切换前置机为非工作模式...【成功】");

    DLOGEVENT(lpContext,"控制DBInit初始化数据...");

    char sName[128] = "init";
    bRet = lpMonitor->InitData(nInitDate, nCenterId, sName);
    if (! bRet)
    {
        sprintf(ErrInfo, "DBInit初始化数据失败[%s]!", lpMonitor->GetErrorInfo());
        delete lpMonitor;
        return PackAnswerPackage(lpContext, out, -102, ErrInfo);
    }
    DLOGEVENT(lpContext,"控制DBInit初始化数据... 【成功】");

    //-------------------------------------------------------------
    // 判断交易核心节点是否初始化成功
    DLOGEVENT(lpContext,"开始检查各节点是否进入交易状态...");
    bRet = lpMonitor->IsBeginTrade();
    if (! bRet)
    {
        sprintf(ErrInfo, "等待交易核心进入交易状态失败[%s]", lpMonitor->GetErrorInfo());
        delete lpMonitor;
        return PackAnswerPackage(lpContext, out, -104, ErrInfo);
    }
    DLOGEVENT(lpContext,"检查各节点是否进入交易状态...【成功】");

    //切换前置机为工作模式
    DLOGEVENT(lpContext,"开始切换前置机为工作模式...");
    bRet = lpMonitor->SetFrontWork();
    if (! bRet)
    {
        sprintf(ErrInfo, "UFT初始化已经成功, 但切换前置机至工作模式失败[%s]，请尝试手工切换前置机至工作模式!", lpMonitor->GetErrorInfo());
        delete lpMonitor;
        return PackAnswerPackage(lpContext, out, 0, ErrInfo);
    }
    DLOGEVENT(lpContext,"切换前置机为工作模式...【成功】");

    delete lpMonitor;
    return PackAnswerPackage(lpContext, out, 0, "UFT初始化成功！");
}


//新增对接UFM的日初始化代码

int  FUNCTION_CALL_MODE F460011( IAS2Context * lpContext, IF2UnPacker * in, IF2Packer * out)
{
    bool bRet = false;
    char ErrInfo[5000] = {0};

    //获取初始化日期
    int nInitDate = in->GetInt("init_date");
    int nCenterId = 35;
    if (nInitDate == 0)
    {
        return PackAnswerPackage(lpContext, out, -101, "传入初始化日期为0!");
    }
    DLOGEVENT(lpContext, "传入参数init_date[" << nInitDate << "]center_id[" << nCenterId << "]");

    CMonitor * lpMonitor = new CMonitor(lpContext);

    //--------------------------------------
    // 获取交易核心服务器信息列表
    DLOGEVENT(lpContext,"开始获取服务器列表...");
    bRet = lpMonitor->GetServerListInfo();
    if (! bRet)
    {
        sprintf(ErrInfo, "获取UFM服务器信息列表失败[%s]!", lpMonitor->GetErrorInfo());
        delete lpMonitor;
        return PackAnswerPackage(lpContext, out, -102, ErrInfo);
    }
    DLOGEVENT(lpContext,"获取服务器列表...【成功】");

    //--------------------------------------
    // 重启各节点
    DLOGEVENT(lpContext,"开始执行各节点重启...");
    bRet = lpMonitor->RebootCresServers();
    if (!bRet)
    {
        sprintf(ErrInfo, "服务器节点重启失败[%s]", lpMonitor->GetErrorInfo());
        delete lpMonitor;
        return PackAnswerPackage(lpContext, out, -103, ErrInfo);
    }
    DLOGEVENT(lpContext,"各节点重启脚本执行...【成功】");

    //----------------------------------------------------------------
    // 判断各个节点是否重启成功
    DLOGEVENT(lpContext,"检测各节点是否重启成功...");
    bRet = lpMonitor->IsRebootNormal();
    if (!bRet)
    {
        sprintf(ErrInfo, "服务器重启异常:[%s]!", lpMonitor->GetErrorInfo());
        delete lpMonitor;
        return PackAnswerPackage(lpContext, out, -104, ErrInfo);
    }
    DLOGEVENT(lpContext,"检测服务器重启状态...【成功】");

    //切换前置机为非工作模式
    DLOGEVENT(lpContext,"开始切换前置机为非工作模式...");
    bRet = lpMonitor->SetFrontUnWork();
    if (! bRet)
    {
        sprintf(ErrInfo, "切换前置机至非工作模式失败[%s]!", lpMonitor->GetErrorInfo());
        delete lpMonitor;
        return PackAnswerPackage(lpContext, out, -102, ErrInfo);
    }
    DLOGEVENT(lpContext,"切换前置机为非工作模式...【成功】");

    DLOGEVENT(lpContext,"控制DBInit初始化数据...");
    char sName[128] = "init";
    bRet = lpMonitor->InitData(nInitDate, nCenterId, sName);
    if (! bRet)
    {
        sprintf(ErrInfo, "DBInit初始化数据失败[%s]!", lpMonitor->GetErrorInfo());
        delete lpMonitor;
        return PackAnswerPackage(lpContext, out, -102, ErrInfo);
    }
    DLOGEVENT(lpContext,"控制DBInit初始化数据...【成功】");

    //-------------------------------------------------------------
    // 判断各节点是否可以开始交易
    DLOGEVENT(lpContext,"开始检查各节点是否进入交易状态...");
    bRet = lpMonitor->IsBeginTrade();
    if (! bRet)
    {
        sprintf(ErrInfo, "等待UFM进入交易状态失败[%s]", lpMonitor->GetErrorInfo());
        delete lpMonitor;
        return PackAnswerPackage(lpContext, out, -110, ErrInfo);
    }
    DLOGEVENT(lpContext,"检查各节点是否进入交易状态...【成功】");

    //切换前置机为工作模式
    DLOGEVENT(lpContext,"开始切换前置机为工作模式...");
    bRet = lpMonitor->SetFrontWork();
    if (! bRet)
    {
        sprintf(ErrInfo, "UFM初始化已经成功, 但切换前置机至工作模式失败，请尝试手工切换前置机至工作模式!");
        delete lpMonitor;
        return PackAnswerPackage(lpContext, out, 0, ErrInfo);
    }
    DLOGEVENT(lpContext,"切换前置机为工作模式...【成功】");

    delete lpMonitor;
    return PackAnswerPackage(lpContext, out, 0, "UFM初始化成功！");
}

int FUNCTION_CALL_MODE F615012( IAS2Context * lpContext, IF2UnPacker * lpInUnPacker, IF2Packer * lpOutPacker)
{
    bool bRet = false;
    char ErrInfo[5000];
    //获取初始化日期
    int nInitDate = lpInUnPacker->GetInt("init_date");
    if (nInitDate == 0)
    {
        return PackAnswerPackage(lpContext, lpOutPacker, -100, "传入初始化日期为0!");
    }
    DLOGEVENT(lpContext, "传入参数init_date[" << nInitDate << "]");

    CMonitor * lpMonitor = new CMonitor(lpContext);

    //--------------------------------------
    //临时清算数据组播到UFT
    DLOGEVENT(lpContext,"开始下载临时清算数据...");

    int nCenterId = 0;
    char sName[128] = "preclear_tmp";
    bRet = lpMonitor->LoadCSV(nInitDate, nCenterId, sName);
    if (!bRet)
    {
        sprintf(ErrInfo, "下载临时清算数据失败[%s]!", lpMonitor->GetErrorInfo());
        delete lpMonitor;
        return PackAnswerPackage(lpContext, lpOutPacker, -101, ErrInfo);
    }
    DLOGEVENT(lpContext,"下载临时清算数据...【成功】");

    // 控制DBInit开始组播临时清算数据
    DLOGEVENT(lpContext,"控制DBInit组播临时清算数据...");
    bRet = lpMonitor->SendData(nInitDate);
    if (!bRet)
    {
        sprintf(ErrInfo, "DBInit组播临时清算数据失败[%s]!", lpMonitor->GetErrorInfo());
        delete lpMonitor;
        return PackAnswerPackage(lpContext, lpOutPacker, -104, ErrInfo);
    }
    DLOGEVENT(lpContext,"DBInit组播临时清算数据...【成功】");

    delete lpMonitor;
    return PackAnswerPackage(lpContext, lpOutPacker, 0, "UFT清算数据（临时）成功！");
}

int FUNCTION_CALL_MODE F615013( IAS2Context * lpContext, IF2UnPacker * lpInUnPacker, IF2Packer * lpOutPacker)
{
    bool bRet = false;
    char ErrInfo[5000];
    //获取初始化日期
    int nInitDate = lpInUnPacker->GetInt("init_date");
    if (nInitDate == 0)
    {
        return PackAnswerPackage(lpContext, lpOutPacker, -100, "传入初始化日期为0!");
    }
    int nBatchNo = lpInUnPacker->GetInt("batch_no");

    DLOGEVENT(lpContext, "传入参数init_date[" << nInitDate << "]batch_no[" << nBatchNo << "]");

    CMonitor * lpMonitor = new CMonitor(lpContext);

    DLOGEVENT(lpContext,"开始下载清算数据到Oplus...");
    char sName[128] = "preclear_h3";
    bRet = lpMonitor->FormalInitData(nInitDate, sName, nBatchNo);
    if (!bRet)
    {
        sprintf(ErrInfo, "下载清算数据到Oplus失败[%s]!", lpMonitor->GetErrorInfo());
        delete lpMonitor;
        return PackAnswerPackage(lpContext, lpOutPacker, -101, ErrInfo);
    }
    DLOGEVENT(lpContext,"下载Oplus清算数据...【成功】");

    //---------------------------------------------------------------
    // 判断交易核心是否成功接收初始化数据
    DLOGEVENT(lpContext,"开始检测各节点是否接收数据结束... ");
    bRet = lpMonitor->IsDataReceived();
    if (!bRet)
    {
        sprintf(ErrInfo, "等待交易核心接收结束异常[%s]!", lpMonitor->GetErrorInfo());
        delete lpMonitor;
        return PackAnswerPackage(lpContext, lpOutPacker, -103, ErrInfo);
    }
    DLOGEVENT(lpContext,"检测各节点接收数据结束...【成功】");

    DLOGEVENT(lpContext,"开始调用UFT清算数据计算服务...");
    bRet = lpMonitor->CalcUFTData();
    if (!bRet)
    {
        sprintf(ErrInfo, "UFT清算数据计算服务调用失败[%s]!", lpMonitor->GetErrorInfo());
        delete lpMonitor;
        return PackAnswerPackage(lpContext, lpOutPacker, -105, ErrInfo);
    }
    DLOGEVENT(lpContext,"调用UFT清算数据计算服务...【成功】");

    delete lpMonitor;
    return PackAnswerPackage(lpContext, lpOutPacker, 0, "UFT清算Oplus数据成功！");
}

int FUNCTION_CALL_MODE F615014( IAS2Context * lpContext, IF2UnPacker * lpInUnPacker, IF2Packer * lpOutPacker)
{
    DLOGEVENT(lpContext,"开始UFT正式清算... ");

    bool bRet = false;
    char ErrInfo[5000];
    //获取初始化日期
    int nInitDate = lpInUnPacker->GetInt("init_date");
    if (nInitDate == 0)
    {
        return PackAnswerPackage(lpContext, lpOutPacker, -100, "传入初始化日期为0!");
    }
    DLOGEVENT(lpContext, "传入参数init_date[" << nInitDate << "]");

    CMonitor * lpMonitor = new CMonitor(lpContext);

    //--------------------------------------
    // 获取交易核心服务器信息列表
    DLOGEVENT(lpContext,"开始获取服务器列表...");
    bRet = lpMonitor->GetServerListInfo();
    if (! bRet)
    {
        sprintf(ErrInfo, "获取交易核心服务器信息列表失败[%s]!", lpMonitor->GetErrorInfo());
        delete lpMonitor;
        return PackAnswerPackage(lpContext, lpOutPacker, -101, ErrInfo);
    }
    DLOGEVENT(lpContext,"获取服务器列表...【成功】");

    //--------------------------------------
    //清算数据组播到UFT
    DLOGEVENT(lpContext,"开始下载正式清算数据... ");
    char sName[128] = "formalclear";
    bRet = lpMonitor->FormalInitData(nInitDate, sName);
    if (!bRet)
    {
        sprintf(ErrInfo, "下载正式清算数据失败[%s]!", lpMonitor->GetErrorInfo());
        delete lpMonitor;
        return PackAnswerPackage(lpContext, lpOutPacker, -101, ErrInfo);
    }
    DLOGEVENT(lpContext,"下载正式清算数据...【成功】");

    //---------------------------------------------------------------
    // 判断交易核心是否成功接收初始化数据
    DLOGEVENT(lpContext,"开始检测各节点是否接收数据结束...");
    bRet = lpMonitor->IsDataReceived();
    if (!bRet)
    {
        sprintf(ErrInfo, "等待交易核心接收结束异常[%s]!", lpMonitor->GetErrorInfo());
        delete lpMonitor;
        return PackAnswerPackage(lpContext, lpOutPacker, -103, ErrInfo);
    }
    DLOGEVENT(lpContext,"检测各节点接收数据结束...【成功】");

    //---------------------------------------------------------------
    DLOGEVENT(lpContext,"开始调用UFT清算数据计算服务...");
    bRet = lpMonitor->CalcUFTData();
    if (!bRet)
    {
        sprintf(ErrInfo, "UFT清算数据计算服务调用失败[%s]!", lpMonitor->GetErrorInfo());
        delete lpMonitor;
        return PackAnswerPackage(lpContext, lpOutPacker, -105, ErrInfo);
    }
    DLOGEVENT(lpContext,"调用UFT清算数据计算服务...【成功】");

    delete lpMonitor;
    DLOGEVENT(lpContext,"UFT正式清算成功！");
    return PackAnswerPackage(lpContext, lpOutPacker, 0, "UFT正式清算成功！");
}

int  FUNCTION_CALL_MODE F615015( IAS2Context * lpContext, IF2UnPacker * in, IF2Packer * out)
{
    bool bRet = false;
    bool bRet1 = false;
    char ErrInfo[5000];

    //获取初始化日期
    int nInitDate = in->GetInt("init_date");
    int nCenterId = in->GetInt("branch_no");
    if (nInitDate == 0)
    {
        return PackAnswerPackage(lpContext, out, -100, "传入初始化日期为0!");
    }
    DLOGEVENT(lpContext, "传入参数init_date[" << nInitDate << "]center_id[" << nCenterId << "]");

    CMonitor * lpMonitor = new CMonitor(lpContext);

    //--------------------------------------
    // 获取交易核心服务器信息列表
    DLOGEVENT(lpContext,"开始获取节点列表...");
    bRet = lpMonitor->GetServerListInfo();
    if (! bRet)
    {
        sprintf(ErrInfo, "获取交易核心服务器信息列表失败[%s]!", lpMonitor->GetErrorInfo());
        delete lpMonitor;
        return PackAnswerPackage(lpContext, out, -101, ErrInfo);
    }
    DLOGEVENT(lpContext,"获取服务器列表...【成功】");

    //--------------------------------------
    // 重启各节点
    DLOGEVENT(lpContext,"开始执行各节点重启...");
    bRet = lpMonitor->RebootCresServers();
    if (!bRet)
    {
        sprintf(ErrInfo, "服务器节点重启失败[%s]", lpMonitor->GetErrorInfo());
        delete lpMonitor;
        return PackAnswerPackage(lpContext, out, -102, ErrInfo);
    }
    DLOGEVENT(lpContext,"各节点重启脚本执行...【成功】");

    //----------------------------------------------------------------
    // 判断各个节点是否重启成功
    DLOGEVENT(lpContext,"检测各节点是否重启成功...");
    bRet = lpMonitor->IsRebootNormal();
    if (!bRet)
    {
        sprintf(ErrInfo, "节点重启异常:[%s]!", lpMonitor->GetErrorInfo());
        delete lpMonitor;
        return PackAnswerPackage(lpContext, out, -102, ErrInfo);
    }
    DLOGEVENT(lpContext,"检测节点重启状态...【成功】");


    DLOGEVENT(lpContext,"控制DBInit初始化数据...");

    char sName[128] = "init";
    bRet = lpMonitor->InitData(nInitDate, nCenterId, sName);
    
    //-------------------------------------------------------------
    // 判断交易核心节点是否初始化成功
    DLOGEVENT(lpContext,"开始检查各节点是否进入交易状态...");
    bRet = lpMonitor->IsBeginTrade();
    if (! bRet)
    {
        sprintf(ErrInfo, "等待交易核心进入交易状态失败[%s]", lpMonitor->GetErrorInfo());
        delete lpMonitor;
        return PackAnswerPackage(lpContext, out, -104, ErrInfo);
    }
    DLOGEVENT(lpContext,"检查各节点是否进入交易状态...【成功】");

// todo
    char sName1[128] = "ypsj";
    bRet1 = lpMonitor->UpgradeInitData(nInitDate, nCenterId, sName1);
    if (! bRet || ! bRet1)
    {
        sprintf(ErrInfo, "DBInit初始化数据失败[%s]!", lpMonitor->GetErrorInfo());
        delete lpMonitor;
        return PackAnswerPackage(lpContext, out, -102, ErrInfo);
    }
    DLOGEVENT(lpContext,"控制DBInit初始化数据... 【成功】");


    //切换前置机为工作模式
    DLOGEVENT(lpContext,"开始切换前置机为工作模式...");
    bRet = lpMonitor->SetFrontWork();
    if (! bRet)
    {
        sprintf(ErrInfo, "UFT初始化已经成功, 但切换前置机至工作模式失败[%s]，请尝试手工切换前置机至工作模式!", lpMonitor->GetErrorInfo());
        delete lpMonitor;
        return PackAnswerPackage(lpContext, out, 0, ErrInfo);
    }
    DLOGEVENT(lpContext,"切换前置机为工作模式...【成功】");
    
    DLOGEVENT(lpContext,"开始覆盖UFT持仓明细数据...");
    bRet = lpMonitor->SyncUFTHoldingdetail();
    if (!bRet)
    {
        sprintf(ErrInfo, "覆盖UFT持仓明细数据失败[%s]!", lpMonitor->GetErrorInfo());
        delete lpMonitor;
        return PackAnswerPackage(lpContext, out, -105, ErrInfo);
    }
    DLOGEVENT(lpContext,"覆盖UFT持仓明细数据...【成功】");

    delete lpMonitor;
    return PackAnswerPackage(lpContext, out, 0, "夜盘升级完成，UFT初始化成功！");
}


//从本地读csv的方式来加载日初始化数据

int  FUNCTION_CALL_MODE F615021( IAS2Context * lpContext, IF2UnPacker * in, IF2Packer * out)
{
    bool bRet = false;
    char ErrInfo[5000];

    //获取初始化日期
    int nInitDate = in->GetInt("init_date");
    int nCenterId = in->GetInt("branch_no");
    if (nInitDate == 0)
    {
        return PackAnswerPackage(lpContext, out, -100, "传入初始化日期为0!");
    }
    DLOGEVENT(lpContext, "传入参数init_date[" << nInitDate << "]center_id[" << nCenterId << "]");

    CMonitor * lpMonitor = new CMonitor(lpContext);

    //--------------------------------------
    // 获取交易核心服务器信息列表
    DLOGEVENT(lpContext,"开始获取服务器列表...");
    bRet = lpMonitor->GetServerListInfo();
    if (! bRet)
    {
        sprintf(ErrInfo, "获取交易核心服务器信息列表失败[%s]!", lpMonitor->GetErrorInfo());
        delete lpMonitor;
        return PackAnswerPackage(lpContext, out, -101, ErrInfo);
    }
    DLOGEVENT(lpContext,"获取服务器列表...【成功】");

    //--------------------------------------
    // 重启各节点
    DLOGEVENT(lpContext,"开始执行各节点重启...");
    bRet = lpMonitor->RebootCresServers();
    if (!bRet)
    {
        sprintf(ErrInfo, "服务器节点重启失败[%s]", lpMonitor->GetErrorInfo());
        delete lpMonitor;
        return PackAnswerPackage(lpContext, out, -102, ErrInfo);
    }
    DLOGEVENT(lpContext,"各节点重启脚本执行...【成功】");

    //----------------------------------------------------------------
    // 判断各个节点是否重启成功
    DLOGEVENT(lpContext,"检测各节点是否重启成功...");
    bRet = lpMonitor->IsRebootNormal();
    if (!bRet)
    {
        sprintf(ErrInfo, "服务器重启异常:[%s]!", lpMonitor->GetErrorInfo());
        delete lpMonitor;
        return PackAnswerPackage(lpContext, out, -102, ErrInfo);
    }
    DLOGEVENT(lpContext,"检测服务器重启状态...【成功】");

    //----------------------------------------------------------------
    // 控制dbinit插件加载csv，并让询问交易核心是否可以接收数据。
    DLOGEVENT(lpContext,"控制DBInit加载csv...");

    char sName[128] = "init";
    bRet = lpMonitor->LoadLocalCSV(nInitDate, nCenterId, sName);
    if (! bRet)
    {
        sprintf(ErrInfo, "DBInit初始化失败[%s]!", lpMonitor->GetErrorInfo());
        delete lpMonitor;
        return PackAnswerPackage(lpContext, out, -102, ErrInfo);
    }
    DLOGEVENT(lpContext,"控制DBInit加载csv...【成功】");

    //-----------------------------------------------------------------
    // 判断交易核心服务器是否准备好。开始接收初始化数据
    DLOGEVENT(lpContext,"检查各节点是否进入数据接收准备状态...");
    bRet = lpMonitor->IsPrepareInit();
    if (! bRet)
    {
        sprintf(ErrInfo, "交易核心无法开始接收初始化数据[%s]!", lpMonitor->GetErrorInfo());
        delete lpMonitor;
        return PackAnswerPackage(lpContext, out, -103, ErrInfo);
    }
    DLOGEVENT(lpContext,"各节点进入准备接收数据状态...");

    //----------------------------------------------------------------
    // 控制DBInit开始组播缓存数据
    DLOGEVENT(lpContext,"控制DBInit组播缓存数据...");
    bRet = lpMonitor->SendData(nInitDate, nCenterId);
    if (!bRet)
    {
        sprintf(ErrInfo, "DBInit组播缓存数据失败[%s]!", lpMonitor->GetErrorInfo());
        delete lpMonitor;
        return PackAnswerPackage(lpContext, out, -104, ErrInfo);
    }
    DLOGEVENT(lpContext,"DBInit组播缓存数据...【成功】");

    //---------------------------------------------------------------
    // 判断交易核心是否成功接收初始化数据
    DLOGEVENT(lpContext,"开始检测各节点是否接收数据结束...");
    bRet = lpMonitor->IsDataReceived();
    if (!bRet)
    {
        sprintf(ErrInfo, "等待交易核心接收结束异常[%s]!", lpMonitor->GetErrorInfo());
        delete lpMonitor;
        return PackAnswerPackage(lpContext, out, -103, ErrInfo);
    }
    DLOGEVENT(lpContext,"检测各节点接收数据结束...【成功】");

    //---------------------------------------------------------------
    // 设置初始化结束,准备交易
    DLOGEVENT(lpContext,"发送初始化结束标记...");
    bRet = lpMonitor->SetInitEnd(nInitDate);
    if (! bRet)
    {
        sprintf(ErrInfo, "设置初始化结束标记异常[%s]!", lpMonitor->GetErrorInfo());
        delete lpMonitor;
        return PackAnswerPackage(lpContext, out, -103, ErrInfo);
    }
    DLOGEVENT(lpContext,"发送初始化结束标记...【成功】");

    //-------------------------------------------------------------
    // 判断各节点是否可以开始交易
    DLOGEVENT(lpContext,"开始检查各节点是否进入交易状态...");
    bRet = lpMonitor->IsBeginTrade();
    if (! bRet)
    {
        sprintf(ErrInfo, "等待交易核心进入交易状态失败[%s]", lpMonitor->GetErrorInfo());
        delete lpMonitor;
        return PackAnswerPackage(lpContext, out, -104, ErrInfo);
    }
    DLOGEVENT(lpContext,"检查各节点是否进入交易状态...【成功】");

    //切换前置机为工作模式
    DLOGEVENT(lpContext,"开始切换前置机为工作模式...");
    bRet = lpMonitor->SetFrontWork();
    if (! bRet)
    {
        sprintf(ErrInfo, "UFT初始化已经成功, 但切换前置机至工作模式失败，请尝试手工切换前置机至工作模式!");
        delete lpMonitor;
        return PackAnswerPackage(lpContext, out, 0, ErrInfo);
    }
    DLOGEVENT(lpContext,"切换前置机为工作模式...【成功】");

    delete lpMonitor;
    return PackAnswerPackage(lpContext, out, 0, "UFT初始化成功！");
}

//UFM本地读csv的方式来加载日初始化数据

int  FUNCTION_CALL_MODE F460021( IAS2Context * lpContext, IF2UnPacker * in, IF2Packer * out)
{
    bool bRet = false;
    char ErrInfo[5000] = {0};

    //获取初始化日期
    int nInitDate = in->GetInt("init_date");
    int nCenterId = 35;
    if (nInitDate == 0)
    {
        return PackAnswerPackage(lpContext, out, -101, "传入初始化日期为0!");
    }
    DLOGEVENT(lpContext, "传入参数init_date[" << nInitDate << "]center_id[" << nCenterId << "]");

    CMonitor * lpMonitor = new CMonitor(lpContext);

    //--------------------------------------
    // 获取交易核心服务器信息列表
    DLOGEVENT(lpContext,"开始获取服务器列表...");
    bRet = lpMonitor->GetServerListInfo();
    if (! bRet)
    {
        sprintf(ErrInfo, "获取UFM服务器信息列表失败[%s]!", lpMonitor->GetErrorInfo());
        delete lpMonitor;
        return PackAnswerPackage(lpContext, out, -102, ErrInfo);
    }
    DLOGEVENT(lpContext,"获取服务器列表...【成功】");

    //--------------------------------------
    // 重启各节点
    DLOGEVENT(lpContext,"开始执行各节点重启...");
    bRet = lpMonitor->RebootCresServers();
    if (!bRet)
    {
        sprintf(ErrInfo, "服务器节点重启失败[%s]", lpMonitor->GetErrorInfo());
        delete lpMonitor;
        return PackAnswerPackage(lpContext, out, -103, ErrInfo);
    }
    DLOGEVENT(lpContext,"各节点重启脚本执行...【成功】");

    //----------------------------------------------------------------
    // 判断各个节点是否重启成功
    DLOGEVENT(lpContext,"检测各节点是否重启成功...");
    bRet = lpMonitor->IsRebootNormal();
    if (!bRet)
    {
        sprintf(ErrInfo, "服务器重启异常:[%s]!", lpMonitor->GetErrorInfo());
        delete lpMonitor;
        return PackAnswerPackage(lpContext, out, -104, ErrInfo);
    }
    DLOGEVENT(lpContext,"检测服务器重启状态...【成功】");

    //----------------------------------------------------------------
    // 控制dbinit插件加载csv，并让询问交易核心是否可以接收数据。
    DLOGEVENT(lpContext,"控制DBInit加载csv...");

    char sName[128] = "init";
    bRet = lpMonitor->LoadLocalCSV(nInitDate, nCenterId, sName);
    if (! bRet)
    {
        sprintf(ErrInfo, "DBInit初始化失败[%s]!", lpMonitor->GetErrorInfo());
        delete lpMonitor;
        return PackAnswerPackage(lpContext, out, -105, ErrInfo);
    }
    DLOGEVENT(lpContext,"控制DBInit加载csv...【成功】");

    //-----------------------------------------------------------------
    // 判断交易核心服务器是否准备好。开始接收初始化数据
    DLOGEVENT(lpContext,"检查各节点是否进入数据接收准备状态...");
    bRet = lpMonitor->IsPrepareInit();
    if (! bRet)
    {
        sprintf(ErrInfo, "UFM无法开始接收初始化数据[%s]!", lpMonitor->GetErrorInfo());
        delete lpMonitor;
        return PackAnswerPackage(lpContext, out, -106, ErrInfo);
    }
    DLOGEVENT(lpContext,"各节点进入准备接收数据状态...");

    //----------------------------------------------------------------
    // 控制DBInit开始组播缓存数据
    DLOGEVENT(lpContext,"控制DBInit组播缓存数据...");
    bRet = lpMonitor->SendData(nInitDate, 35);
    if (!bRet)
    {
        sprintf(ErrInfo, "DBInit组播缓存数据失败[%s]!", lpMonitor->GetErrorInfo());
        delete lpMonitor;
        return PackAnswerPackage(lpContext, out, -107, ErrInfo);
    }
    DLOGEVENT(lpContext,"DBInit组播缓存数据...【成功】");

    //---------------------------------------------------------------
    // 判断交易核心是否成功接收初始化数据
    DLOGEVENT(lpContext,"开始检测各节点是否接收数据结束...");
    bRet = lpMonitor->IsDataReceived();
    if (!bRet)
    {
        sprintf(ErrInfo, "等待UFM接收结束异常[%s]!", lpMonitor->GetErrorInfo());
        delete lpMonitor;
        return PackAnswerPackage(lpContext, out, -108, ErrInfo);
    }
    DLOGEVENT(lpContext,"检测各节点接收数据结束...【成功】");

    //---------------------------------------------------------------
    // 设置初始化结束,准备交易
    DLOGEVENT(lpContext,"发送初始化结束标记...");
    bRet = lpMonitor->SetInitEnd(nInitDate, 35);
    if (! bRet)
    {
        sprintf(ErrInfo, "设置初始化结束标记异常[%s]!", lpMonitor->GetErrorInfo());
        delete lpMonitor;
        return PackAnswerPackage(lpContext, out, -109, ErrInfo);
    }
    DLOGEVENT(lpContext,"发送初始化结束标记...【成功】");

    //-------------------------------------------------------------
    // 判断各节点是否可以开始交易
    DLOGEVENT(lpContext,"开始检查各节点是否进入交易状态...");
    bRet = lpMonitor->IsBeginTrade();
    if (! bRet)
    {
        sprintf(ErrInfo, "等待UFM进入交易状态失败[%s]", lpMonitor->GetErrorInfo());
        delete lpMonitor;
        return PackAnswerPackage(lpContext, out, -110, ErrInfo);
    }
    DLOGEVENT(lpContext,"检查各节点是否进入交易状态...【成功】");

    //切换前置机为工作模式
    DLOGEVENT(lpContext,"开始切换前置机为工作模式...");
    bRet = lpMonitor->SetFrontWork();
    if (! bRet)
    {
        sprintf(ErrInfo, "UFT初始化已经成功, 但切换前置机至工作模式失败，请尝试手工切换前置机至工作模式!");
        delete lpMonitor;
        return PackAnswerPackage(lpContext, out, 0, ErrInfo);
    }
    DLOGEVENT(lpContext,"切换前置机为工作模式...【成功】");

    delete lpMonitor;
    return PackAnswerPackage(lpContext, out, 0, "UFM初始化成功！");
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
            if  (ppv != NULL)
            {
                ppv->dwFunctionNo = 615011;        //功能号
                ppv->iVersion = 20121212;       //version信息
                ppv->ReqProc = F615011;            //功能函数指针
                ppv->AnsProc = NULL;            //应答处理函数入口
                ppv->Caption = "监控交易核心装态";      //函数功能描述
            }
            break;
        case 1:
            if  (ppv != NULL)
            {
                ppv->dwFunctionNo = 615012;        //功能号
                ppv->iVersion = 20121212;       //version信息
                ppv->ReqProc = F615012;            //功能函数指针
                ppv->AnsProc = NULL;            //应答处理函数入口
                ppv->Caption = "清算数据组播到UFT临时";      //函数功能描述
            }
            break;
        case 2:
            if  (ppv != NULL)
            {
                ppv->dwFunctionNo = 615013;        //功能号
                ppv->iVersion = 20121212;       //version信息
                ppv->ReqProc = F615013;            //功能函数指针
                ppv->AnsProc = NULL;            //应答处理函数入口
                ppv->Caption = "清算数据组播到Oplus";      //函数功能描述
            }
            break;
        case 3:
            if  (ppv != NULL)
            {
                ppv->dwFunctionNo = 615014;        //功能号
                ppv->iVersion = 20121212;       //version信息
                ppv->ReqProc = F615014;            //功能函数指针
                ppv->AnsProc = NULL;            //应答处理函数入口
                ppv->Caption = "清算数据组播到UFT";      //函数功能描述
            }
            break;
        case 4:
            if  (ppv != NULL)
            {
                ppv->dwFunctionNo = 615021;        //功能号
                ppv->iVersion = 20121212;       //version信息
                ppv->ReqProc = F615021;            //功能函数指针
                ppv->AnsProc = NULL;            //应答处理函数入口
                ppv->Caption = "加载本地CSV做日初始化";      //函数功能描述
            }
            break;
        case 5:
            if  (ppv != NULL)
            {
                ppv->dwFunctionNo = 460011;        //功能号
                ppv->iVersion = 20160407;       //version信息
                ppv->ReqProc = F460011;            //功能函数指针
                ppv->AnsProc = NULL;            //应答处理函数入口
                ppv->Caption = "UFM初始化";      //函数功能描述
            }
            break;
        case 6:
            if  (ppv != NULL)
            {
                ppv->dwFunctionNo = 460021;        //功能号
                ppv->iVersion = 20160407;       //version信息
                ppv->ReqProc = F460021;            //功能函数指针
                ppv->AnsProc = NULL;            //应答处理函数入口
                ppv->Caption = "加载本地CSV做UFM初始化";      //函数功能描述
            }
            break;
        case 7:
			if  (ppv != NULL)
			{
				ppv->dwFunctionNo = 615015;        //功能号
				ppv->iVersion = 20170408;       //version信息
				ppv->ReqProc = F615015;            //功能函数指针
				ppv->AnsProc = NULL;            //应答处理函数入口
				ppv->Caption = "夜盘升级组播数据到UFT";      //函数功能描述
			}
			break;
        default:
            iRet = ASFC_NONE;
    }
    return iRet;
}


//获取组件信息

char *  FUNCTION_CALL_MODE GetLibVersion( )
{
    return __DATE__;
}

