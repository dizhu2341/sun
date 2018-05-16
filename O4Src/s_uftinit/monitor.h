#ifndef _MONITOR_H_
#define _MONITOR_H_

#include <Include/pack_interface.h>
#include <Include/esb_message_interface.h>
#include <Include/tag_def.h>
#include <Include/biz_comp_interface.h>
#include <IncludeFm/s_jc_public.h>
#include <IncludeFm/s_liblogpublic.h>
#include "IncludeFm/writedlog.h"
#include <string>
#include <vector>
#include <iostream>
#include <map>

#include "tinyxml.h"
#include "tinystr.h"

using namespace std;

//------------------------------------
// ����Ϊ��������𣬹̶��ġ�����е�������ϵ��Ӿ��
#define SVRTYPE_UFT      "UFT"
#define SVRTYPE_UFR      "UFR"
#define SVRTYPE_QUERY    "QUERY"
#define SVRTYPE_UFTCORE  "UFTCORE"
#define SVRTYPE_DBINIT   "DBINIT"
#define SVRTYPE_QUEUE    "QUEUE"
#define SVRTYPE_FRONT    "FRONT"
#define SVRTYPE_LOGSVR   "LOGSVR"
#define SVRTYPE_U2DB     "U2DB"
#define SVRTYPE_ARB      "ARB"

//-----------------------------------
// sleep����
void MSleep(int nCount);

//-------------------------------------
// ������״̬
typedef enum __SVRSTATUS {
    STATUS_UFT_BOOT = 1,
    STATUS_INIT_START = 1,
    STATUS_INIT_END = 3,
    STATUS_TRADE = 4,
    STATUS_ERROR = 5
}SVRSTATUS;

typedef enum __SYSSTATUS
{
	SYS_STATUS_INIT    = 0,
	SYS_STATUS_FAIL    = 1,
	SYS_STATUS_SUCCESS = 2,
	SYS_STATUS_PAUSE   = 3,	
}SYSSTATUS;


//--------------------------------------
//��������
class CSvrPlugin
{
public:
    CSvrPlugin();
    ~CSvrPlugin();
public:
    char m_sName[128];
    char m_sType[128];
    int m_nStatus;
    bool IsRebootOk;
};

//--------------------------------------
//����ڵ���
class CSvrNode 
{
public:
    CSvrNode();
    ~CSvrNode();
    void AddSvrPlugin(CSvrPlugin* pSvrPlugin);
public:
    char m_sName[128];
    char m_sUser[128];
    char m_sPasswd[128];
    char m_sIP[128];
    char m_sRunscript[128];
    char m_sStopscript[128];
    bool IsRebootOk;
    vector<CSvrPlugin*>  m_vecSvrPlugin;
};

class CMonitor  
{
public:
	CMonitor(IAS2Context* lpContext);
	virtual ~CMonitor();
	
	const char * GetErrorInfo();

	bool GetServerListInfo();
    bool IsRebootNormal();
    bool LoadCSV(int nInitDate, int nCenterId, char* sName);
    bool LoadLocalCSV(int nInitDate,int nCenterId, char* sName);
    bool InitData(int nInitDate, int nCenterId, char* sName);
    bool FormalInitData(int nInitDate, char* sName, int nBatchNo = 0);
    bool UpgradeInitData(int nInitDate, int nCenterId, char* sName);
	bool IsPrepareInit();
    bool SendData(int nInitDate, int nCenterID =-1);
	bool IsDataReceived();
    bool SetInitEnd(int nInitDate, int nCenterID =-1);
    bool IsBeginTrade();
    bool RebootCresServers();
    bool StartFront();
	bool IsFrontStart();
    bool SetFrontWork();
    bool SetFrontUnWork();
    bool ExportMemData();
	bool LoadOplusDataToCSV(int nInitDate, int nBatchNo);
	bool CalcUFTData();
	bool SyncUFTHoldingdetail();

    void GetInitErrInfo(string machine, string svrID);

public:
    int rebootTryCount;      // �ж��Ƿ������ɹ����Դ���
    int preInitTryCount;     // �ж��Ƿ�׼����ʼ�����Դ���
    int cacheRecvTryCount;   // �ж��Ƿ����ݽ�����ɳ��Դ���
    int beginTradeTryCount;  // �жϽ��׺����Ƿ������״̬���Դ���

    int cacheRecvWait;  //�ȴ�������ս�����ʱ��
    int frontstartWait; //�ȴ�ǰ�û���������

protected:
    bool CheckRebootNormal();
    bool CheckPrepareInit();
    bool CheckDataReceived();
    bool CheckBeginTrade();
	bool CheckFrontStart();

    //-------------------------------------- 
    bool OpenNodes();
    bool CloseNodes();
    bool RebootNodes();

	IF2UnPacker* CallService(int FuncNo, IF2Packer* inPack, int TimeOut, int BranchNo = -1);
	IF2UnPacker* CallServiceEx(int FuncNo, IF2Packer* inPack, int TimeOut, int BranchNo = -1);
    IF2UnPacker* CallPluginSvr(char* sNodeFullName, char* sPluginName, int nFuncID, int TimeOut);
	bool SshCommand(char* pIpAddress, char *pUser, char *pPasswd, char* pRunScript, char* pStopScript);
    bool ExecCommand(char* pCmd, char* pIpAddress, char *pUser, char *pPasswd);
    void PrintSvrInfo();

    bool ExportUFRMemData();
    bool ExportUFTMemData();
    
    int GetSvrStatus(char* sNodeFullName, char* sPluginName);
    int GetSysStatus(char* sNodeFullName, char* sPluginName);
    string GetUnStartNodes();
    int PrintUnPack(IF2UnPacker * unpack);

private:
	IAS2Context*         m_lpContext;
    
    int                  m_nMaxTryTimes;     //��ೢ�Դ���

    vector<CSvrNode*>    m_vecSvrNode;

	// ��¼������Ϣ
	int                  m_nErrorNo;
	char                 m_szErrorMessage[512];
    
	int					 m_nRMTimeOut;
    typedef map<string, int>  PLUGIN_MAP;
    PLUGIN_MAP          m_mPluginMap;
};

#endif


