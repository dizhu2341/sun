#ifndef _O4_INIT_MANAGER_H_
#define _O4_INIT_MANAGER_H_

#include <Include/pack_interface.h>
#include <Include/esb_message_interface.h>
#include <Include/tag_def.h>
#include <Include/f2core_interface.h>
#include <Include/biz_comp_interface.h>
#include <Include/comm_agent_interface.h>
#include <IncludeFm/s_jc_public.h>

#include <map>
#include <vector>
#include "hshead.h"

#include "threadPool.h"

extern IAS2Context * glb_lpcontext;
extern IF2Packer * glb_lpoutpacker;
extern ICommAgent * glb_lpcommagent;
extern IF2Core * glb_lpCore;

using namespace std;

typedef struct SubSysStatus {
    int jc_subsys_status;
    int hg_subsys_status;
    int qs_subsys_status;

    SubSysStatus() {
        jc_subsys_status = -1;
        hg_subsys_status = -1;
        qs_subsys_status = -1;
    }
} SubSysStatus;

class CO4InitManager {
public:
    CO4InitManager(IAS2Context * lpContext, ICommAgent* lpCommAgent, IF2UnPacker * lpInUnPacker, IF2Packer * lpOutPacker, char* pErrPathInfo);
    ~CO4InitManager();

    bool Init();
    bool Clear();
    bool Sync();
    bool UpgradeSync();

    bool InitDBConnection();
    bool doPreInit();
    bool doInit();
    bool doNextInit();
    bool CancelSubscribeTopics();
    bool SubsribeTopics();
    bool MultiCast();
    bool ExportDataToCsv();
    bool GetAllSubSysStatus();
    int GetErrNo();
    char* GetErrInfo();
    char* GetErrPathInfo();
    int GetInitDate();
    bool ClearMulticastNo();
    int IsOpenUFT();
    int CallService(int FuncNo, IF2Packer* inPack, IF2Packer* outPack, int TimeOut);
    bool ValidUFTData();
    bool GetDockSystem();
    bool DeleteBasedellog();
private:
    bool IsHaveSyncErr();
    bool IsAllFinished();
    bool IsCanInit();
    int GetSysStatus(int sysNo);
    bool GetSyncTaskList();
    void GroupSyncTask();
    void SetErrInfo(int nErrNo, const char* pErrInfo);
    void SetErrPathInfo(const char* pErrPathInfo);
    char* GetRunningTasks();


private:
    IAS2Context * m_lpContext;
    ICommAgent * m_lpCommAgent;
    IF2UnPacker * m_lpInUnPacker;
    IF2Packer * m_lpOutPacker;
    //CThreadPool	 * m_lpThPool;
    IConnection *m_lpDBConn;
    SubSysStatus m_subSysStatus;

    vector<CSyncTask*> m_vecTask;
    vector<vector<CSyncTask*> > m_vecMgrTask;

    int m_nInitMode; //1-日初始化全流程；2-只做数据同步，不包含UFT初始化；3-正式清算流程
    int m_nInitDate;
    int m_nErrNo;
    char m_sErrInfo[1025];
    char m_sErrPathInfo[4001];
    char m_sRunTaskLst[10240];
    char m_sErrorMessage[1024];
    char m_sDockSystem;
};

#endif
