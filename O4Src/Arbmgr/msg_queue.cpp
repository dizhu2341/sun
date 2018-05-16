#include "msg_queue.h"

#ifdef _WIN32

CMsgQueue::CMsgQueue()
{
	m_lpQueueName = (char*)malloc(PATH_MAX);
	m_nTotalMsgs = 0;
}

CMsgQueue::~CMsgQueue()
{
	if (m_lpQueueName)
	{
		free(m_lpQueueName);
		m_lpQueueName = NULL;
	}
}

int CMsgQueue::CreateQueueName(const char * queueName)
{
	return -1;
}

int CMsgQueue::Create(const char* queueName, long msg_max, long msg_size)
{
	return -1;
}

int CMsgQueue::Open(const char * queueName)
{
	return -1;
}

int CMsgQueue::Read(char * lpBuf, size_t nLen, long dwMillsSecond)
{
	return -1;
}

int CMsgQueue::Write(const char * lpBuf, size_t nLen, long dwMillsSecond)
{
	return -1;
}

int CMsgQueue::Close()
{
	return -1;
}

int CMsgQueue::Delete()
{
	return -1;
}

long CMsgQueue::GetMaxMsg()
{
	return -1;
}

long CMsgQueue::GetMsgSize()
{
	return -1;
}

long CMsgQueue::GetCurMsgs()
{
	return -1;
}

long CMsgQueue::GetTotalMsgs()
{
	return m_nTotalMsgs;
}

#else

CMsgQueue::CMsgQueue()
{
	m_lpQueueName = (char*)malloc(PATH_MAX);
	m_nTotalMsgs = 0;
}

CMsgQueue::~CMsgQueue()
{
	if (m_lpQueueName)
	{
		free(m_lpQueueName);
		m_lpQueueName = NULL;
	}
}

int CMsgQueue::CreateQueueName(const char * queueName)
{
	const char * dir, * slash;
	if (m_lpQueueName == NULL && (m_lpQueueName = (char*)malloc(PATH_MAX)) == NULL)
		return -1;

#ifdef POSIX_IPC_PREFIX
	dir = "/";
#else
	dir = "/tmp/";
#endif

	slash = (dir[strlen(dir) - 1] == '/') ? "":"/";
	snprintf(m_lpQueueName, PATH_MAX, "%s%s%s", dir, slash, queueName);
	return 0;
}

int CMsgQueue::Create(const char* queueName, long msg_max, long msg_size)
{
	if (CreateQueueName(queueName))
		return-1;

	struct mq_attr attr;
	attr.mq_maxmsg = msg_max;
	attr.mq_msgsize = msg_size;
	m_lpQueue = mq_open(m_lpQueueName, O_RDWR | O_CREAT, QUEUE_MODE, &attr);
	if (m_lpQueue == -1)
		return -1;

	m_nTotalMsgs = GetCurMsgs();
	return 0;
}

int CMsgQueue::Open(const char * queueName)
{
	if (CreateQueueName(queueName))
		return -1;

	m_lpQueue = mq_open(m_lpQueueName, O_RDWR, QUEUE_MODE, NULL);
	if (m_lpQueue == -1)
		return -1;

	m_nTotalMsgs = GetCurMsgs();
	return 0;
}

int CMsgQueue::Read(char * lpBuf, size_t nLen, long dwMillsSecond)
{
	int iRet;
	if (dwMillsSecond == INFINITE)
	{
		while ((iRet = mq_receive(m_lpQueue, lpBuf, nLen, NULL)) == -1)
		{
			if (errno == EINTR)
				continue;
			return -1;
		}
		return iRet;
	}
	else
	{
		struct timespec tm;
		
		ConvertToTimespec(dwMillsSecond, tm);

		while ((iRet = mq_timedreceive(m_lpQueue, lpBuf, nLen, NULL, &tm)) == -1)
		{
			if (errno == EINTR)
				continue;
			else if (errno == ETIMEDOUT)
				return -2;
			else
				return -1;
		}
		return iRet;
	}
}

int CMsgQueue::Write(const char * lpBuf, size_t nLen, long dwMillsSecond)
{
	int iRet;
	if (dwMillsSecond == INFINITE)
	{
		while ((iRet = mq_send(m_lpQueue, lpBuf, nLen, 0)) == -1)
		{
			if (errno == EINTR)
				continue;
			return -1;
		}
		return iRet;
	}
	else
	{
		struct timespec tm;

		ConvertToTimespec(dwMillsSecond, tm);

		while ((iRet = mq_timedsend(m_lpQueue, lpBuf, nLen, 0, &tm)) == -1)
		{
			if (errno == EINTR)
				continue;
			else if (errno == ETIMEDOUT)
				return -2;
			else
				return -1;
		}
		return iRet;
	}
}

int CMsgQueue::Close()
{
	return mq_close(m_lpQueue);
}

int CMsgQueue::Delete()
{
	return mq_unlink(m_lpQueueName);
}

long CMsgQueue::GetMaxMsg()
{
	struct mq_attr  attr;
	if (mq_getattr(m_lpQueue, &attr)) 
		return -1;
	return attr.mq_maxmsg;
}

long CMsgQueue::GetMsgSize()
{
	struct mq_attr  attr;
	if (mq_getattr(m_lpQueue, &attr)) 
		return -1;
	return attr.mq_msgsize;
}

long CMsgQueue::GetCurMsgs()
{
	struct mq_attr  attr;
	if (mq_getattr(m_lpQueue, &attr)) 
		return -1;
	return attr.mq_curmsgs;
}

long CMsgQueue::GetTotalMsgs()
{
	return m_nTotalMsgs;
}

#endif
