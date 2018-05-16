#include "CArbManager.h"
#include "CArbMgrIOC.h"
#include "CStatusMonitorMgr.h"

unsigned long  CArbMgrIOC::QueryInterface( HS_SID iid, IKnown **ppv )
{
    if ( strcmp(iid,SID_ARBMGR) == 0 )
    {
        *ppv =  m_lpOwner;
    }
    else if ( strcmp(iid,SID_IOC) == 0 )
    {
        *ppv =  this;
    }
    else
    {
        *ppv = (IKnown *)NULL;
        return I_NONE;
    }
    return I_OK;
}

unsigned long  CArbMgrIOC::AddRef()
{
    return I_OK;
}

unsigned long  CArbMgrIOC::Release()
{
    return I_OK;
}

int FUNCTION_CALL_MODE CArbMgrIOC::SetConfig(const char * sPath,IRCfgObj * lpConfig)
{
    int iRet = I_OK;
    //增加引用计数，传递给容器，由容器在用完之后释放(处理MSG_START事件时释放)
    if ( lpConfig )
    {
        if ( strcmp(sPath,CO_PLUGIN)==0 )
        {
            lpConfig->AddRef();
            m_lpOwner->m_lpConfig = lpConfig;
        }
        else if ( strcmp(sPath,CO_PUB)==0 )
        {
            lpConfig->AddRef();
            m_lpOwner->m_lpCoPub = lpConfig;
        }
    }

    return iRet;
}

int FUNCTION_CALL_MODE CArbMgrIOC::SetDependService(HS_SID iid,IKnown * lpService)
{
    int iRet = I_OK;
   
    if (strcmp(iid, SID_F2_CORE) == 0)
        m_lpF2Core = (IF2Core*)lpService;
	//	m_lpOwner->m_lpCfgSvr = (ICfgSvr*)lpService;
/*	else if (strcmp(iid, SID_ESB_MESSAGEFACTORY) == 0)
		m_lpOwner->m_lpESBFactory = (IESBMessageFactory*)lpService;
	else if(strcmp(iid, SID_F2PACKSVR) == 0)
		m_lpOwner->m_lpPackSvr = (IF2PackSvr*)lpService;
	else if(strcmp(iid, SID_RM3SVR) == 0)
		m_lpOwner->m_lpRMSvr = (IRM3Svr*)lpService;
	else if(strcmp(iid, SID_MCAPI) == 0)
	{
		lpService->QueryInterface(SID_MCCLIENTAPI, (IKnown**)&m_lpOwner->m_lpMcClient);
		//m_lpOwner->m_lpMcClient=(IMCClient*)lpService;
	} */

    
    return iRet;
}

 IArbmgrInterface* CArbMgrIOC::GetPluginArbMgrInterface(HS_SID iid)
 {
     if(NULL == m_lpF2Core)
     {
         // TODO
         return NULL;
     }

     IKnown * lpPlugin = NULL;
     m_lpF2Core->QueryInterface(iid, &lpPlugin);
     if (NULL == lpPlugin)
     {
         // TODO
         return NULL;
     }
     
     IKnown * argMgrInterface = NULL;
     lpPlugin->QueryInterface(SID_ARBMGR, &argMgrInterface);
     if (NULL == argMgrInterface)
     {
         // TODO
         return NULL;
     }
     return (IArbmgrInterface*)argMgrInterface;
 }
