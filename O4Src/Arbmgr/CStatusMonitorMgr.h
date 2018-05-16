#ifndef _CStatusMonitorMgr_H__
#define _CStatusMonitorMgr_H__

#include "ArbMgrMain.h"

class CArbMgrIOC; //��ת��������
class CStatusMonitorMgr; //��������
class CArbManager; //���ʵ����

class CStatusMonitorMgr: public IManager
{
public:
    CStatusMonitorMgr(CArbManager * lpOwner);
    ///IManager�ӿ�
    //@{
    unsigned long  FUNCTION_CALL_MODE QueryInterface( HS_SID iid, IKnown **ppv );
    unsigned long  FUNCTION_CALL_MODE AddRef();
    unsigned long  FUNCTION_CALL_MODE Release();

    int  FUNCTION_CALL_MODE ProcMngRequest(IF2UnPacker * lpInput,IF2Packer * lpOutput);
    int  FUNCTION_CALL_MODE ProcMngAnswer(IF2UnPacker * lpInput);
    int  FUNCTION_CALL_MODE ProcSysEvent(unsigned long dwMessageID,
    				  unsigned long dwWParam,
    				  unsigned long dwLParam,
    				  PFOnSetTimeOut pfOnSetTimeOut = NULL);
    //@}
	
private:
    ///�������������б�������Ͷ��塢���ݽṹ������
    //@{
    ///����������������REQ_ACTION
    typedef int (CStatusMonitorMgr::* REQ_ACTION)(IF2UnPacker * lpRequest,IF2Packer * lpAnswer);
    ///���崦�����б�ڵ�����
    typedef struct tagAction{
        REQ_ACTION  lpAction;		//������ָ��
        const char *   sCaption;	//������˵��
    }ACTION_INFO,* LPACTION_INFO;
    ///��������ܴ����������� ACTION_MAP
    typedef std::map< unsigned long, LPACTION_INFO > ACTION_MAP;

    ///�����ܺ�����
    ACTION_MAP m_ProcReqActionList;
    ///�����������뵽�б���
    /** 
     *@param unsigned long  dwFuncNo   �����ܺ�
     *@param ProcReqAction  fpAction   ���ܺŶ�Ӧ�Ĵ�����
     *@param const char *   sCaption   ����������
     */
    int mf_AddToActionList(unsigned long dwFuncNo,REQ_ACTION fpAction,const char * sCaption);
    ///ȡ���ܺŶ�Ӧ�Ĵ�����
    CStatusMonitorMgr::REQ_ACTION mf_GetAction(unsigned long dwFuncNo);
    //@}
	
    ///�����ܴ����������к���ԭ�;���:int mf_GetFuncList(IF2UnPacker * ,IF2Packer * )
    //@{
    ///��ѯ��������ܺ��б�
    int  mf_GetFuncList(IF2UnPacker * lpRequest,IF2Packer * lpAnswer);
    ///@todo����������ܴ�����
    
    //@}
private:
    CArbManager * m_lpOwner;
};

#endif
