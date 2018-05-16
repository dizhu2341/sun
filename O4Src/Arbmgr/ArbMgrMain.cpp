#include "ArbMgrMain.h"
#include "CArbManager.h"

///-------------------------- 插件库引出函数实现 --------------------------///
//@{
int FUNCTION_CALL_MODE ArbmgrInit(void * lpInstance, PFOnSetTimeOut pfOnSetTimeOut)
{
    int iRet = I_NONE;
    if (lpInstance)  
        iRet = ((CArbManager *)lpInstance )->OnInit(pfOnSetTimeOut);
    
    return iRet;
}

char * FUNCTION_CALL_MODE GetArbmgrDependSvr(void * lpInstance)
{
    char * sRet = SID_F2_CORE\
                  "\0\0";
    return sRet;
}

IKnown * FUNCTION_CALL_MODE GetArbmgrInstance()
{
    return new CArbManager();
}

int FUNCTION_CALL_MODE GetArbmgrInfo(int iIndex, tagBaseServiceInfo * ppv)
{
    int iRet = I_OK;
    switch (iIndex)
    {
        case 0:
            if  (ppv!=NULL)
            {
                ppv ->ServiceID = SID_ARBMGR;
                ppv ->iVersion = 20160729;
                ppv ->Init = ArbmgrInit;
                ppv ->getInstance = GetArbmgrInstance;
                ppv ->getDependServices = GetArbmgrDependSvr;
                ppv ->Caption = __DATE__;
            }
            break;
        default:
           iRet = I_NONE ;
    }
    return iRet;
}

