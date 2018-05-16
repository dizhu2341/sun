#include <IncludeFm/writedlog.h>

CWriteDLog::CWriteDLog()
{

}
CWriteDLog::~CWriteDLog()
{

}

int CWriteDLog::DlogWrite(IAS2Context * lpContext, int iLogID, int iLogLevel, char *loginfo)
{

	  ICloud_Dlog * lpCloudDlog = NULL;
	  lpContext->QueryInterface(SID_CLOUD_DLOG, (IKnown **)&lpCloudDlog);
	  if (lpCloudDlog == NULL)
	    return -1;

	  ICloud_DLogArgs * lpArgs = lpCloudDlog->GetDLogArgs();
	  if (lpArgs == NULL)
	    return -1;

	  lpArgs->AddBody(loginfo);
	  lpArgs->SetInfoByESBMsg(lpContext->GetOrgRequest());

	  lpCloudDlog->AddLogByArgsEx(iLogID, iLogLevel, lpArgs);
	  lpArgs->Release();
	  return 0;
}
