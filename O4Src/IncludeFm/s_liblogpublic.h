#ifndef _S_LIBLOGPUBLIC_H_
#define _S_LIBLOGPUBLIC_H_

#include <fstream>
#include <pthread.h>
#include <string.h>
#include "os/functional.h"

#ifndef ENUM_LOG_RUNNING_STATE
#define ENUM_LOG_RUNNING_STATE
enum LOG_RUNNING_STATE
{
	
	LOG_INIT_COMPLETE = 0,
	LOG_UNINITIALIZED = 1
};
#endif
#ifndef ENUM_LOG_LOG_WARNING_LEVEL
#define ENUM_LOG_LOG_WARNING_LEVEL
enum LOG_LOG_WARNING_LEVEL
{	
	LOG_ESB_LOG_ERROR = 0,
	LOG_ESB_LOG_WARN = 1,
	LOG_ESB_LOG_SYSTEM = 2,
	LOG_ESB_LOG_PARAM = 3,
	LOG_ESB_LOG_DETAIL = 4,
	LOG_ESB_LOG_DEBUG = 5,
	LOG_ESB_LOG_UNKNOWN = 6
};
#endif
#ifndef ENUM_LOG_FILE_NAME_TYPE
#define ENUM_LOG_FILE_NAME_TYPE
enum LOG_FILE_NAME_TYPE
{
	WRITE_LOG_NAME_DEFAULT = 0,
	WRITE_LOG_NAME_NEW = 1,
};
#endif
#ifndef LOG_MAX_PATH
#define LOG_MAX_PATH			256
#endif

USING_FBASE2_NAMESPACE

class CWriteLog;
extern int GLogLevel;
extern int GMaxLineCount;
extern const char *GLogPath;
extern CWriteLog *pGwriteLog;

//20160511  daiyh 增加全局变量设置文件名 默认文件名：runlog.log
extern const char * pGLogName; //若自定义了文件名，则按自定义文件名命名

/*记录错误日志，要传日志编号*/
#define LOGERROR(ERROR_CODE, TEXT)	WRITELOG2FILE(LOG_ESB_LOG_ERROR, ERROR_CODE, TEXT)
#define LOGWARN(TEXT)								WRITELOG2FILE(LOG_ESB_LOG_WARN, 0, TEXT)
#define LOGSYSTEM(TEXT)							WRITELOG2FILE(LOG_ESB_LOG_SYSTEM, 0, TEXT)
#define LOGPARAM(TEXT)							WRITELOG2FILE(LOG_ESB_LOG_PARAM, 0, TEXT)
#define LOGDETAIL(TEXT)							WRITELOG2FILE(LOG_ESB_LOG_DETAIL, 0, TEXT)
#define LOGDEBUG(TEXT)							WRITELOG2FILE(LOG_ESB_LOG_DEBUG, 0, TEXT)

#define LOGERROREX(OBJ, ERROR_CODE, TEXT)	WRITELOG2FILEEX(OBJ, LOG_ESB_LOG_ERROR, ERROR_CODE, TEXT)
#define LOGWARNEX(OBJ, TEXT)							WRITELOG2FILEEX(OBJ, LOG_ESB_LOG_WARN, 0, TEXT)
#define LOGSYSTEMEX(OBJ, TEXT)						WRITELOG2FILEEX(OBJ, LOG_ESB_LOG_SYSTEM, 0, TEXT)
#define LOGPARAMEX(OBJ, TEXT)							WRITELOG2FILEEX(OBJ, LOG_ESB_LOG_PARAM, 0, TEXT)
#define LOGDETAILEX(OBJ, TEXT)						WRITELOG2FILEEX(OBJ, LOG_ESB_LOG_DETAIL, 0, TEXT)
#define LOGDEBUGEX(OBJ, TEXT)							WRITELOG2FILEEX(OBJ, LOG_ESB_LOG_DEBUG, 0, TEXT)


#define WRITELOG2FILE(LOGWARMINGLEVEL, ERRORCODE, TEXT) if (GLogLevel >= (int)LOGWARMINGLEVEL) \
{ \
	CWriteLog::Lock(); \
	std::ofstream ofile; \
	CWriteLog::NewLine(ofile, __FILE__, __LINE__, __func__, (int)LOGWARMINGLEVEL, ERRORCODE) << TEXT; \
	ofile.close(); \
	CWriteLog::UnLock(); \
}

#define WRITELOG2FILEEX(OBJ, LOGWARMINGLEVEL, ERRORCODE, TEXT) if (OBJ != NULL && OBJ->AccessToLog((int)LOGWARMINGLEVEL)) \
{ \
	OBJ->IndepLock(); \
	std::ofstream ofile; \
	OBJ->IndepWriteLogFile(ofile, __FILE__, __LINE__, __func__, (int)LOGWARMINGLEVEL, ERRORCODE) << TEXT; \
	ofile.close(); \
	OBJ->IndepUnLock(); \
}

class CWriteLog
{
public:
	CWriteLog();
	CWriteLog(const char *plogname, const int nlevel = LOG_ESB_LOG_ERROR, const char *path = ".", const int nMaxLineCount = 20000);
	~CWriteLog();
public:
	int GetLogFileNameFormat();
	int GetFallLevel();
	int SetFallLevel(int nlevel);
	bool AccessToLog(const int errorCode);
	std::ofstream& IndepWriteLogFile(std::ofstream& ofile, const char *fileName, const int fileLine, const char *funcName,
		const int logLevel, const int errorCode);
	int GetLogFileName(char *fileName);
	int GetDate();
	int Changefilename(const char *sFileName);
	int ProcessPathName();
	double GetLines(const char *sFileName);
	void IndepLock();
	void IndepUnLock();
	void LogFileDivide(char * pFileName, const char *pLogPath, const char *pLogName, int iMaxLineCount);

    //M201605120442
    const char *ConvertDirectory(char dir_[]);//查找路径串中，在当前平台下不合规的目录分隔符
    bool IsDirectory(char pathname[]); //判断所给的目录路径是否存在
    int CreateDirectory(char dir_[]);//创建多层目录
    
	static void Lock();
	static void UnLock();
	static std::ofstream& NewLine(std::ofstream& ofile, const char *fileName,
		const int fileLine, const char *funcName, const int logLevel, const int errorCode);
private:
	int		m_nMaxLineCount;					//! 一个日志文件最大的条目数(只用于旧版)
	int 	m_nFallLevel;							//! 日志记录等级
	int		m_lineCount;							//! 日志当前行数
	int		m_init;										//! 锁控制
	int		m_nLogFileNameFormat;			//! 控制日志文件名格式
	char	m_szLogName[LOG_MAX_PATH];			//! 文件名，使用时额外添加时间
	char	m_szLogingPath[LOG_MAX_PATH];		//! 日志文件路径
	pthread_mutex_t m_Mutex;
};


#endif /* _S_LIBLOGPUBLIC_H_ */

