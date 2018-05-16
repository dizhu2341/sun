/*******************************************************
源程序名称:msg_queue.h
软件著作权:恒生电子股份有限公司
系统名称:  posix消息队列封装
模块名称:  
功能说明:  
作    者:  huxb
开发日期:  20131128
备    注: 
*********************************************************/
#ifndef _ACD_MSG_QUEUE_H_
#define _ACD_MSG_QUEUE_H_

#include <os/config_env.h>
#include <os/inttypes.h>

//消息队列名称的最大长度
#ifndef PATH_MAX
#define PATH_MAX 256
#endif

#ifdef _WIN32
#include <Windows.h>
#define MQD HANDLE
#else

#include <mqueue.h>
#include <sys/stat.h>
#define MQD mqd_t
#define POSIX_IPC_PREFIX "/"
#define QUEUE_MODE (S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH)

#endif

class CMsgQueue{
public:
	CMsgQueue();

	~CMsgQueue();

	/* 创建消息队列 如果消息队列存在，则打开
	* @param queueName 消息队列名字，不能有任何斜杠符
	* @param msg_max 消息队列最大消息数
	* @param msg_size 消息最大长度
	* @return 0 成功
	*		 -1 失败
	*/
	int Create(const char* queueName, long msg_max = 10, long msg_size = 8192);

	/* 打开消息队列 如果消息队列不存在，则失败
	* @param queueName 消息队列名字，不能有任何斜杠符
	* @return 0 成功
	*		 -1 失败
	*/
	int Open(const char* queueName);

	/* 从消息队列中读取数据
	* @param lpBuf 接收缓冲区
	* @param nLen  缓冲区长度
	* @param dwMillsSecond  超时时间，单位为ms
	* @return -2 超时
			  -1 其他错误
				 成功返回消息的长度	  
	*/
	int Read(char* lpBuf, size_t nLen, long dwMillsSecond = INFINITE);

	/* 向消息队列中写数据
	* @param lpBuf 发送数据地址
	* @param nLen  发送数据长度
	* @param dwMillsSecond  超时时间，单位为ms
	* @return -2 超时
			  -1 其他错误
			   0 成功
	*/
	int Write(const char* lpBuf, size_t nLen, long dwMillsSecond = INFINITE);

	/* 关闭消息队列
	* @return -1 失败
	*		   0 成功
	*/
	int Close();

	/* 删除消息队列
	* @return -1 失败
	*		   0 成功
	*/
	int Delete();

	/*
	* @return -1 失败 成功返回消息队列最大消息数
	*/
	long GetMaxMsg();

	/*
	* @return -1 失败 成功返回消息的最大长度
	*/
	long GetMsgSize();

	/*
	* @return -1 失败 成功返回消息队列的当前消息个数
	*/
	long GetCurMsgs();

	/*
	* @return 消息队列的消息总个数(多线程环境下，返回值仅作参考)
	*/
	long GetTotalMsgs();

	/* 返回错误号
	*/
	int GetLastErr()
	{
		return errno;
	}
private:
	int CreateQueueName(const char* queueName);

#ifndef _WIN32
	void ConvertToTimespec(long dwMillsSecond, struct timespec& tm)
	{
		struct timeval tvNow;
		gettimeofday(&tvNow, NULL);

		tm.tv_sec = tvNow.tv_sec + dwMillsSecond / 1000;
		tm.tv_nsec = (tvNow.tv_usec + (dwMillsSecond % 1000) * 1000);	//	这里计算的还只是微秒
		if( tm.tv_nsec/(1000*1000) )	//	秒数已经进位
		{
			tm.tv_sec++;
			tm.tv_nsec = tm.tv_nsec%(1000*1000);
		}
		tm.tv_nsec = tm.tv_nsec*1000;	//	转换成纳秒
	}
#endif

private:
	MQD 			m_lpQueue;
	char *			m_lpQueueName;			//消息队列名称
	long			m_nTotalMsgs;			//所有进入队列的消息总数
};

#endif
