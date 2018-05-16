///�������������ʾ�����ʵ���� CDemoServiceImpl ����
/*******************************************************
  Դ��������:DemoServiceImpl.h
  �������Ȩ:���ݺ������ӹɷ����޹�˾
  ϵͳ����:  HZHSGS֤ȯ����Ӧ�÷�����V2.0
  ģ������:  ������ģ��
  ����˵��:  
  
  ����ĵ�:  ��Ҫ��ƽӿڲ���
             
  ��    ��:  zhangly
  ��������:  20050718
  //20140919 dongpf �������÷���/���մ��ڴ�С����
*********************************************************/
#ifndef UDP_BROADCAST_H
#define UDP_BROADCAST_H

#include "os/config_env.h"
#include "os/thread.h"

BEGIN_FBASE2_NAMESPACE

///UDP���ջص�����ָ��
#ifdef _WIN32
	typedef int (__stdcall * FOnUDPReceive ) (void * owner,void * lpData,int iDataLen);
#else
	typedef int (* FOnUDPReceive ) (void * owner,void * lpData,int iDataLen);
#endif

//20110524 dongpf Ӧ������Ҫ�󣬻ص�����udp�ķ����ߵ�ip�Ͷ˿�
///UDP���ջص�����ָ��
#ifdef _WIN32
	typedef int (__stdcall * FOnUDPReceiveEx ) (void * owner,void * lpData,int iDataLen, const char * szSenderIP, int iPort);
#else
	typedef int (* FOnUDPReceiveEx ) (void * owner,void * lpData,int iDataLen, const char * szSenderIP, int iPort);
#endif


//20110524 dongpf Ӧ������Ҫ�󣬻ص�����udp�ķ����ߵ�ip�Ͷ˿�(�ĳ�ȫ�ֺ���ָ��)
static FOnUDPReceiveEx g_pReceiveFunctionEx = NULL;   //���ջص�����

///UDP�㲥ʵ����
class API_EXPORT CUDPBroadcast: public CThread
{
public:
	CUDPBroadcast();
	~CUDPBroadcast();

	/**@ udp �㲥�ӿ� */
	//@{
		void Destroy(void);
		///
		/**
		 *
		 *
		 *
		 *@return: 0 �ɹ�  -1ʧ��, �׽��ֳ�ʼ��ʧ��
		 */
		int Init( unsigned int iPort,FOnUDPReceive pFunction,void * lpOwner=NULL);
		
		void Start(void);
		int Broadcast(char * lpData,int iLen);
		
		//20140919 dongpf �������÷��ʹ��ڴ�С����
		/**
		 *@int iSendBufLen: ���ڴ�С����λ���ֽ�
		 *@return: ����ʵ�ʴ��ڴ�С��-1�����÷��ʹ��ڴ�Сʧ��
		 */
		int SetSendBufLen(int iSendBufLen);
		
		//20140919 dongpf �������ý��մ��ڴ�С����
		/**
		 *@int iRecvBufLen: ���ڴ�С����λ���ֽ�
		 *@return: ����ʵ�ʴ��ڴ�С��-1�����ý��մ��ڴ�Сʧ��
		 */
		int SetRecvBufLen(int iRecvBufLen);
	//@}
	
	/**@  */
	//@{
	   long Run();
	//@}
	
	//20110524 dongpf Ӧ������Ҫ�󣬻ص�����udp�ķ����ߵ�ip�Ͷ˿�
	int InitEx( unsigned int iPort,FOnUDPReceiveEx pFunction,void * lpOwner=NULL);
	
private:
	///��������sock
	int CreateSock();
private:
	
	unsigned int  m_iPort;             //�˿ں�
	FOnUDPReceive m_pReceiveFunction;   //���ջص�����

	void *        m_lpOwner;            //�ص�������
	
	int m_iSock;         //sock
};

END_FBASE2_NAMESPACE

#endif
