// Դ�ļ�����namedpipe.h
// �����Ȩ�����ݺ������ӹɷ����޹�˾
// ϵͳ���ƣ�HZHSGS���ڻ�����1.0
// ����˵���������ܵ������壬������ֻ����������ֻд��֧�ֶ�ƽ̨
// ��    �ߣ����پ�
// ��    ע��Tab = 4
// ��    ʷ��
// 20041015 ��һ���汾

#ifndef NAMEDPIPE_H_INCLUDE
#define NAMEDPIPE_H_INCLUDE

#include <os/config_env.h>
#include <os/inttypes.h>

#ifndef _WIN32
#include <sys/ipc.h>
#endif

#define MAX_PIPE_BUF_SIZE	10240

#include <os/config_env.h>

BEGIN_FBASE2_NAMESPACE

#ifdef _WIN32
#  if !defined(MAX_INSTANCE)
#  define MAX_INSTANCE	64
#  endif

#define CONNECTING_STATE 0 
#define READING_STATE 1 
#define READ_STATE 2 
//#define INSTANCES 4 
#define PIPE_TIMEOUT 5000
#define BUFSIZE 4096

typedef struct 
{ 
	OVERLAPPED oOverlap; 
	HANDLE hPipeInst; 
//	TCHAR chRequest[BUFSIZE]; 
//	DWORD cbRead;
//	TCHAR chReply[BUFSIZE];
//	DWORD cbToWrite; 
	DWORD dwState; 
	BOOL fPendingIO; 
} PIPEINST, *LPPIPEINST; 

#endif

class API_EXPORT CNamedPipe
{
private:
	char	m_szName[256];
#ifdef _WIN32
	HANDLE	m_handle;

	PIPEINST	m_Pipes[MAX_INSTANCE]; 
	HANDLE		m_Events[MAX_INSTANCE];

	VOID _DisconnectAndReconnect(DWORD i);
	BOOL _ConnectToNewClient(HANDLE hPipe, LPOVERLAPPED lpo);
#else
	bool	m_bCreated;
	int		m_fd;
	int		m_fdDummy;	// �����ʹ�ã���ʹ��
#endif

public:
	CNamedPipe(const char *szName);
	~CNamedPipe();
	bool Create();
	bool Connect();
	bool Read(void *buf, uint32 size, uint32 &plen, uint32 uMs = (uint32)INFINITE);
	bool Write(const void *buf, uint32 len);
};

END_FBASE2_NAMESPACE

#endif
