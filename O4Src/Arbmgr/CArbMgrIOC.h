#ifndef __CArbMgrIOC_H__
#define __CArbMgrIOC_H__

#include "ArbMgrMain.h"
#include "arbmgr_interface.h"
#include <Include/f2core_interface.h>

class CArbMgrIOC; //��ת��������
class CStatusMonitorMgr; //��������
class CArbManager; //���ʵ����

///��ת��������
class CArbMgrIOC: public IIoC
{
public:
    CArbMgrIOC(CArbManager * lpOwner)
    { 
        m_lpOwner = lpOwner; 
        m_lpF2Core = NULL;
    }
    ///IIoC�ӿ�
    //@{
    unsigned long  FUNCTION_CALL_MODE QueryInterface( HS_SID iid, IKnown **ppv );
    unsigned long  FUNCTION_CALL_MODE AddRef();
    unsigned long  FUNCTION_CALL_MODE Release();

    int  FUNCTION_CALL_MODE SetConfig(const char * sPath,IRCfgObj * lpConfig);
    int  FUNCTION_CALL_MODE SetDependService(HS_SID iid,IKnown * lpService);
    //@}

public:
    IArbmgrInterface* GetPluginArbMgrInterface(HS_SID iid);
 
private:
    CArbManager * m_lpOwner;
    IF2Core* m_lpF2Core;
};

#endif