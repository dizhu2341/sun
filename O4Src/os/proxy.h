/******************************************************************************
Դ�ļ�����proxy.h
�����Ȩ���������ӹɷ����޹�˾
ϵͳ���ƣ�
����˵��������ӿ�
��    �ߣ�feisi@hundsun.com
����ʱ�䣺20080102
��    ע��
�� �� �ߣ�
�޸�ʱ�䣺
�޸ļ�飺
******************************************************************************/

#ifndef _PROXY_H_
#define _PROXY_H_



/******************************************************************************
*
*	ͷ�ļ�
*
******************************************************************************/
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <assert.h>

#if defined _WIN32
	#include <Winsock2.h>
	#include <Windows.h>
#else
	#include <unistd.h>
	#include <sys/types.h>
	#include <sys/socket.h>
	#include <netinet/in.h>
	#include <netdb.h>
	#include <arpa/inet.h>
#endif

#if defined _WIN32
	typedef int socklen_t;
#endif



/******************************************************************************
*
*	��������
*
******************************************************************************/
// �����ɹ�����
const int SUCCESS = 1;
// select������ʱʱ��
const long SELECT_TIME = 5L;
// SOCKS5��ʹ�õĽ��ջ���UDP���ĵ����ݻ�������С
const unsigned long SOCKS5_UDP_BUFSIZE = 65535UL;

const unsigned char SOCKS5_CMD_TCP  = 0x01;   // SOCKS5����TCP��������
const unsigned char SOCKS5_CMD_UDP  = 0x03;   // SOCKS5����UDP��������

const int ERR_SELECT_ERROR          = -101;   // select��������
const int ERR_SELECT_TIMEOUT        = -102;   // select������ʱ
const int ERR_SOCKET_SEND_ERROR     = -103;   // ϵͳsocket send��������
const int ERR_SOCKET_READ_ERROR     = -104;   // ϵͳsocket recv��������
const int ERR_SOCKET_READ_EOF       = -105;   // �����Է��ر��׽��ֱ�־
const int ERR_CONNECT_PROXY_SERVER  = -106;   // �޷����ӵ����������

/* HTTP error */
const int ERR_HTTP_PACK_CONNECT_REQUEST            = -301;   // ��֯���������
const int ERR_HTTP_SEND_CONNECT_REQUEST            = -302;   // �������������
const int ERR_HTTP_RECV_CONNECT_REPLY              = -303;   // ���շ�����Ӧ�������
const int ERR_HTTP_VERIFY_CONNECT_REPLY            = -304;   // ��֤������Ӧ�������

/* SOCKS4 error */
const int ERR_SOCKS4_PACK_CONNECT_REQUEST          = -401;   // ��֯���������
const int ERR_SOCKS4_SEND_CONNECT_REQUEST          = -402;   // �������������
const int ERR_SOCKS4_RECV_CONNECT_REPLY            = -403;   // ���շ�����Ӧ�������
const int ERR_SOCKS4_VERIFY_CONNECT_REPLY          = -404;   // ��֤������Ӧ�������

/* SOCKS5 error */
const int ERR_SOCKS5_SEND_METHOD_SELECTION_REQUEST = -501;   // "��¼��ʽ"�����ķ���ʧ��
const int ERR_SOCKS5_RECV_METHOD_SELECTION_REPLY   = -502;   // "��¼��ʽ"Ӧ���Ľ���ʧ��
const int ERR_SOCKS5_VERIFY_METHOD_SELECTION_REPLY = -503;   // "��¼��ʽ"���������ܾ�
const int ERR_SOCKS5_PACK_USR_PSWD_REQUEST         = -504;   // "�û���+����"�����������
const int ERR_SOCKS5_SEND_USR_PSWD_REQUEST         = -505;   // "�û���+����"���ķ���ʧ��
const int ERR_SOCKS5_RECV_USR_PSWD_REPLY           = -506;   // "�û���+����"Ӧ���Ľ���ʧ��
const int ERR_SOCKS5_VERIFY_USR_PSWD_REPLY         = -507;   // "�û���+����"��֤���������ܾ�
const int ERR_SOCKS5_PACK_CONNECT_REQUEST          = -508;   // "��������"�������ʧ��
const int ERR_SOCKS5_SEND_CONNECT_REQUEST          = -509;   // "��������"���ķ���ʧ��
const int ERR_SOCKS5_RECV_CONNECT_REPLY            = -510;   // "��������Ӧ��"���Ľ���ʧ��
const int ERR_SOCKS5_VERIFY_CONNECT_REPLY          = -511;   // "��������Ӧ��"������֤ʧ��
const int ERR_SOCKS5_UDP_INIT                      = -512;   // SOCKS5 UDP���ӳ�ʼ��ʧ��
const int ERR_SOCKS5_UDP_FRAGMENTATION             = -513;   // UDP��֧�ֱ��ķ�Ƭ
const int ERR_SOCKS5_UDP_SEND                      = -514;   // UDP���ķ���ʧ��
const int ERR_SOCKS5_UDP_RECV                      = -515;   // UDP���Ľ���ʧ��
const int ERR_SOCKS5_UDP_VERIFY_PACKET             = -516;   // SOCKS5 UDP����ͷ��֤ʧ��
const int ERR_SOCKS5_UDP_INBUF_INSUFFICIENT        = -517;   // �û����ջ��治��
const int ERR_SOCKS5_UDP_NOT_IPv4                  = -518;   // ���ַ�IPv4��ַ

#if defined(_WIN32) && !defined(SEPARATE_COMPILE)
	#ifdef DLL_API_EXPORT
		#define API_EXPORT __declspec(dllexport)
	#else
		#define API_EXPORT __declspec(dllimport)
	#endif
#else
	#define API_EXPORT 
#endif

/******************************************************************************
*
*	����TCP��ؽӿ�
*
******************************************************************************/
/// ����SOCKS4����Э�����TCP�����׽���
/** @param serv_addr: �����������ַ
  * @param serv_port: ����������˿�
  * @param dest_addr: Ŀ��������ַ
  * @param dest_port: Ŀ�������˿�
  *
  * @return int:      �ɹ� > 0, �����׽���
  *                   ʧ�� < 0, �����
  */
extern "C" int API_EXPORT socks4_connect(const char *serv_addr, unsigned short serv_port,
							  const char *dest_addr, unsigned short dest_port);



/// ����HTTP����Э�����TCP�����׽���
/** @param serv_addr: �����������ַ
  * @param serv_port: ����������˿�
  * @param dest_addr: Ŀ��������ַ
  * @param dest_port: Ŀ�������˿�
  * @param user_name: �����¼�û�(������¼ʱ��ΪNULL)
  * @param password:  �����¼����(������¼ʱ��ΪNULL)
  *
  * @return int:      �ɹ� > 0, �����׽���
  *                   ʧ�� < 0, �����
  */
extern "C" int API_EXPORT http_connect(const char *serv_addr, unsigned short serv_port,
							const char *dest_addr, unsigned short dest_port,
							const char *user_name, const char *password);



/// ����SOCKS5����Э�����TCP�����׽���
/** @param serv_addr: �����������ַ
  * @param serv_port: ����������˿�
  * @param dest_addr: Ŀ��������ַ
  * @param dest_port: Ŀ�������˿�
  * @param user_name: �����¼�û�(������¼ʱ��ΪNULL)
  * @param password:  �����¼����(������¼ʱ��ΪNULL)
  *
  * @return int:      �ɹ� > 0, �����׽���
  *                   ʧ�� < 0, �����
  */
extern "C" int API_EXPORT socks5_tcp_connect(const char *serv_addr, unsigned short serv_port,
								  const char *dest_addr, unsigned short dest_port,
								  const char *user_name, const char *password);



/******************************************************************************
*
*	����UDP��ؽӿ�
*
******************************************************************************/
/*

ע: ͨ��SOCKS5����Э�����UDP���ĵ�ת��ʱ, ��"�ͻ���"��"�����������"�䷢��UDP
����ʱ, ����һ������ı���ͷ��, ������ʾ:

      +----+------+------+----------+----------+----------+
      |RSV | FRAG | ATYP | DST.ADDR | DST.PORT |   DATA   |
      +----+------+------+----------+----------+----------+
      | 2  |  1   |  1   | Variable |    2     | Variable |
      +----+------+------+----------+----------+----------+

����:	RSV  - ����λ, ����ȫ0
		FRAG - ��Ƭ��־λ, Ŀǰʵ���в�֧�ַ�Ƭ, ��ֵҲΪ0
		ATYP - ��ַ����, Ŀǰʵ��ֻ֧��ipv4��ַ

		DST.ADDR - ����ʱ, ��������Ŀ�ĵ�ַ(���Ǵ�������ַ)
		           ����ʱ, ��ʾ������Դ��ַ(���Ǵ�������ַ)
		DST.PORT - �˿�, ����ͬ��

		DATA - �û�������Ӧ������

��ʵ����: Socks5Udp::SendTo, Socks5Udp::RecvFrom - �Ѿ��ں����ڲ�������ͷ����Ϣ
                                                   �û�ֻ��Ҫ�����Լ������ݼ���

!!!��ʹ������ϵͳsocket�����е�sendto, recvfrom�÷�һ��!!!

*/

class API_EXPORT Socks5Udp
{
	public:
		/// ����SOCKS5�����UDP������ʼ��
		/** @param serv_addr: �����������ַ
		  * @param serv_port: ����������˿�
		  * @param user_name: �����¼�û�(������¼ʱ��ΪNULL)
		  * @param password:  �����¼����(������¼ʱ��ΪNULL)
		  *
		  * @return int:      �ɹ� == SUCCESS
		  *                   ʧ�� < 0, �����
		  */
		int UdpInit(const char *serv_addr, unsigned short serv_port, const char *user_name, const char *password);

		/// ����SOCKS5�����UDP���ݱ����ͺ���(Ŀǰʵ��ֻ֧��IPv4��ַ)
		/** @param buf:		���������ݻ������׵�ַ
		  * @param len:		���������ݳ���
		  * @param flags:	����ѡ��(�京����ϵͳsocket��sendto��������һ��), һ��ɴ���0
		  * @param to:		����Ҫ������Ŀ�ĵ�ַ�ṹ��(�京����ϵͳsocket��sendto��������һ��)
		  * @param tolen:	����Ҫ������Ŀ�ĵ�ַ�ṹ��ĳ���(�京����ϵͳsocket��sendto��������һ��)
		  *
		  * @return int:      �ɹ�����ʵ�ʷ��͵��ֽ���
		  *                   ʧ�� < 0, �����
		  */
		int SendTo(const char *buf, int len, int flags, const struct sockaddr *to, int tolen);

		/// ����SOCKS5�����UDP���ݱ����պ���(Ŀǰʵ��ֻ֧��IPv4��ַ)
		/** @param buf:		�������ݻ������׵�ַ
		  * @param len:		�������ݻ���������
		  * @param flags:	����ѡ��(�京����ϵͳsocket��recvfrom��������һ��), һ��ɴ���0
		  * @param to:		����������Դ��ַ�ṹ��(�京����ϵͳsocket��recvfrom��������һ��)
		  * @param tolen:	����������Դ��ַ�ṹ��ĳ���(�京����ϵͳsocket��recvfrom��������һ��)
		  *
		  * @return int:      �ɹ�����ʵ�ʽ��յ��ֽ���
		  *                   ʧ�� < 0, �����
		  *                   ע: �����Ϊ"ERR_SOCKS5_UDP_INBUF_INSUFFICIENT"ʱ, �����û��ṩ����
		  *                       ���治��, �����󻺴���ȡ������
		  */
		int RecvFrom(char *buf, int len, int flags, struct sockaddr *from, int *fromlen);

		/// �ر��ڲ�ά����2���׽���(1.TCP - ������ 2.UDP - ת��������)
		/**
		  * @return int: SUCCESS, Ŀǰ���Ƿ��سɹ�
		  *
		  */
		int CloseSocket(void);

		/// ����ڲ�ά����UDP�׽���
		/**
		  * @return int: UDP�׽���
		  *
		  */
		int GetUdpHandle(void) const;

		/// Ĭ�Ϲ��캯��
		Socks5Udp();

		/// ��������
		~Socks5Udp();

	private:
		Socks5Udp(const Socks5Udp &);   // ��ֹ�������캯��
		Socks5Udp & operator=(const Socks5Udp &);   // ��ֹ"="�Ÿ�ֵ

	private:
		int tcp_fd;                    // TCP�׽���, ���ڵ�Э��, ����, Ӧ�� ...; ������
		int udp_fd;                    // UDP�׽���, ����UDP������
		struct sockaddr_in udp_serv;   // SOCKS5�������������ת��UDP����ʹ�õĵ�ַ��Ϣ
		bool m_bAlreadyReaded;                  // ���ڿ����Ƿ���Ҫ�ӵײ��ȡ����
		char m_szRecvBuf[SOCKS5_UDP_BUFSIZE];   // ����UDP�����ڲ�����
		int m_iPackSize;                        // ���յ����Ĵ�С
};



#endif   // _PROXY_H_
