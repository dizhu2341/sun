/*
 * writedlog.h
 *  Created on: 2017年3月1日
 *      Author: linan15617
 */

#ifndef _WRITEDLOG_H_
#define _WRITEDLOG_H_

#include <fstream>
#include <pthread.h>
#include <string.h>
#include <sstream>
#include <cstring>
#include <IncludeFm/cloud_dlog_interface.h>
#include <Include/biz_comp_interface.h>
using namespace std;
/*记录错误日志，要传日志编号*/
#define DLOGDEBUG(lpContext,TEXT)					WRITEDLOG2FILE(lpContext, 0, 0, CLOUD_LOG_DEBUG, TEXT)
#define DLOGEVENT(lpContext,TEXT)					WRITEDLOG2FILE(lpContext, 0, 0, CLOUD_LOG_EVENT, TEXT)
#define DLOGWARNING(lpContext,TEXT)					WRITEDLOG2FILE(lpContext, 0, 0, CLOUD_LOG_WARNING, TEXT)
#define DLOGERROR(lpContext, ERROR_CODE, TEXT)		WRITEDLOG2FILE(lpContext, ERROR_CODE, 0, CLOUD_LOG_ERRER, TEXT)
#define DLOGCRUSHED(lpContext, TEXT)				WRITEDLOG2FILE(lpContext, 0, 0, CLOUD_LOG_CRUSHED, TEXT)
#define DLOGIMP(lpContext,TEXT)						WRITEDLOG2FILE(lpContext, 0, 0, CLOUD_LOG_IMPORTANTEVENT, TEXT)
#define DLOGUNKNOWN(lpContext,TEXT)					WRITEDLOG2FILE(lpContext, 0, 0, CLOUD_LOG_UNKNOWN, TEXT)


#define WRITEDLOG2FILE(lpContext, ERROR_CODE, LOGID, DLOGLEVEL, TEXT) \
{ \
	stringstream ss; \
	string getStr; \
	char loginfo[10000] = {0}; \
	ss << "["; \
	ss << __FILE__; \
	ss << "|"; \
	ss << __LINE__; \
	ss << "|"; \
	ss << __func__; \
	ss << "]"; \
	ss << TEXT; \
	getStr = ss.str(); \
	strcpy(loginfo, getStr.c_str()); \
	CWriteDLog::DlogWrite(lpContext, LOGID, (int)DLOGLEVEL,loginfo);\
}


class CWriteDLog
{
public:
	CWriteDLog();
	~CWriteDLog();
public:
	static int DlogWrite(IAS2Context * lpContext,int iLogID, int iLogLevel,char *loginfo);
};

#endif /* _WRITEDLOG_H_ */
