///���ڻ�����2.0OSPFģ��ӿڶ��� 
/*******************************************************
  Դ������:	ospf_interface.h
  �����Ȩ: �������ӹɷ����޹�˾
  ϵͳ����: ���ڻ�����2.0
  ģ������: OSPFģ��
  ����˵��: ����һ��OSPF��
            1���ṩ����·�ɼ���
            2���ռ��ṩ����ͼ��Ϣ
  ��    ��: �з�����
  ��������: 20080103
  ��    ע: 

  �޸���Ա��
  �޸����ڣ�
  �޸�˵����
*********************************************************/

#ifndef __OSPF_INTERFACE_H__
#define __OSPF_INTERFACE_H__

#include <Include/service_interface.h>
#include <Include/glbdef.h>

/// ����ӿڶ���
//@{
/// OSPFģ�������Ϣ(���ò��ֿ�����Ҫͳһ����)
#define GET_FUNCTION_ID			0
#define GET_TOPO				1				// ��ȡ����ͼ
#define GET_ARID				3				// ����AR����
#define PRINT_AVL_TREE			4				// ���ļ������AVL��

/// ��ȡ�ڲ�����״̬
#define GET_NBR_NUM				5				// �ھӶ��г���
#define GET_LSA_DB_NUM			6				// LSA���ݿ�ά����Ŀ
#define GET_RETRANS_NUM			7				// �ط����еĳ���(����LSA��LSR)
#define GET_FLOOD_TIMES			8				// ��ȡ�������
#define REV_PACKETS				9				// ���յ��İ��ĸ���
#define SEND_PACKETS			10				// �ѷ��Ͱ��ĸ���
#define GET_AGING_LSA_NUM		11				// ��ȡ���ϻ���LSA����
#define GET_PROXY_NAME			12				// ��ȡOSPF����Ŀͻ��������Լ��Ѿ������Ŀͻ���
#define GET_NBR					14				// ��ȡ�ھ����Լ�����
#define GET_AGE_BINS			15				// ��ȡ���������Ϣ
#define GET_HISTORY_INFO		16				// ��ȡ��ʷ������Ϣ, ֻ������history=1����Ч
#define GET_MSG_LIST_INFO		17
//@}


typedef struct tagDestAR
{
	char			szARName[IDENTITY_NAME_LENGTH + 1];		// AR����
	unsigned char	byFlag;									// Server/Client�ı�־��1��Client 2��Server
} DestAR;

/// OSPF���ýӿڣ������̹߳���ǰ�������ͬ����
/// ��Router֮��Ľ�����Ҫ��IService�ṩ�Ľӿ�
struct IOspf : IMessageService
{
	/// ��ȡ��һ��·��, lpDest��һ����ŵĵ�ַΪ���ؾ�����ѵ�ַ, ֮�������еȼ�·��
	/** ����:	@char*			lpARName			Ŀ���ַ
	 *			@DestAR*		lpDest				������������ַ
	 *			@uint16			*wPath				(in)lpDest�ṩ��DestAR�ṹ����, (out)ָ�����ȼ۵����е�ַ
	 *	����:	
	 */
	virtual void GetRoute(char *szName, DestAR *lpDest, uint16 *wPath) = 0;

};


#ifdef __cplusplus
extern "C" { 
#endif

	///�����ʼ��
	/**
	 *@return int �汾�� yyyymmdd��ʽ
	 */
	int  FUNCTION_CALL_MODE OSPFInit(void *lp, PFOnSetTimeOut);
	
	///ȡ����ӿھ��
	/**
	 *@return void * ����ģʽ
	 */
	IKnown * FUNCTION_CALL_MODE GetOSPFInstance(void);

	///ȡ����ӿ���������
	/**
	 *@param iIndex 
	 *@return IKnown * ���������ʶ 
	 */
	char * FUNCTION_CALL_MODE GetOSPFDependService(void *lp);
	
	///����ͳһ��AS�������������ѯ�ӿ� getxxxInfo()
	/**���������������̬����ʱ��ͨ�����ӿڻ��Ի�ȡ������Ϣ(����xxxxInit(),getxxxxInterface()����ָ��)
	 *@param void ** ppv    �������������Ϣ(�������)��
	 *@return ����0��ʾ�鵽��Ҫ�Ľӿڣ����򷵻ظ���
	 */
	int FUNCTION_CALL_MODE GetOSPFInfo(int iIndex, tagBaseServiceInfo * ppv);

#ifdef __cplusplus
}
#endif


#endif


