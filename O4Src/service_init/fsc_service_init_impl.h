///Service_init ���ʵ��ͷ�ļ�
/*********************************************************************************************
  Դ��������: fsc_service_init_impl.h
  �������Ȩ: �������ӹɷ����޹�˾
  ��������:  
  ģ������:  fsc_service_init

  �������:  �ɹ���ɷ�ת��ͨ���

  ����˵��:  

  ����ĵ�:  

  ��    ��:  �з�����chengjin
  ��������:  2014-11-17
  ��    ע:  
  �޸ļ�¼:  
 *********************************************************************************************/

#ifndef __Service_init_Impl_H__
#define __Service_init_Impl_H__

///ϵͳͷ�ļ�
#include <string.h>
#include <stdlib.h>
#include <map>
///@todo �����������ͷ�ļ�
//@{

//@}


///fbase2.0ͷ�ļ�
#include <Include/config_interface.h>
#include <Include/pack_interface.h>
#include <Include/security_interface.h>
///@todo �����������ͷ�ļ�
//@{

//@}

//#include ""
///����ӿڶ���ͷ�ļ�
#include <IncludeFm/s_liblogpublic.h>
#include <service_init/service_init_interface.h>

//����Ĭ����־����
#define DEFAULT_LOG_LEVEL   5
#define DEFAULT_LOG_LINE    -1
#define DEFAULT_LOG_NAME    "runlog.log"
#define DEFAULT_LOG_PATH    "./log"

class CService_initIoC; //��ת��������
class CService_initMgr; //��������
class CService_initImpl; //���ʵ����

///���ʵ����

class CService_initImpl : public IService_init
{
    friend class CService_initIoC;
    friend class CService_initMgr;
public:
    ///IKnown�ӿں���
    //@{
    unsigned long FUNCTION_CALL_MODE QueryInterface(HS_SID iid, IKnown **ppv);
    unsigned long FUNCTION_CALL_MODE AddRef();
    unsigned long FUNCTION_CALL_MODE Release();
    //@}

    ///@todo, IService_init�ӿ�
    //@{


    //@}

public:
    CService_initImpl();
    ~CService_initImpl(); /*lint !e1510*/

    ///��ʼ�������������������Service_initInit()����
    int OnInit(PFOnSetTimeOut pfOnSetTimeOut = NULL);

    ///�������¼�������
    //�������������ڴ���MSG_START�¼�ʱ����
    void OnStart(PFOnSetTimeOut pfOnSetTimeOut = NULL);
    //ֹͣ���������ڴ���MSG_STOP�¼�ʱ����
    void OnStop(PFOnSetTimeOut pfOnSetTimeOut = NULL);
    //�˳����������ڴ���MSG_EXIT�¼�ʱ����
    void OnExit(PFOnSetTimeOut pfOnSetTimeOut = NULL);

public:
    ///@todo, ������Ҫ�����������
    //@{
    int InitLogLevel();
    int InitLogLineCount();
    int InitLogName();
    int InitLogPath();
    int InitHsdbOraInfo();

    //@}

private:
    ///��ת������
    CService_initIoC * m_lpIoC;
    ///������
    CService_initMgr * m_lpMgr;
    ///���ö���<plugins>(�յ�MSG_START�¼�֮���ͷ�)
    IRCfgObj * m_lpConfig;
    ///���ö���<pub>(�յ�MSG_START�¼�֮���ͷ�)
    IRCfgObj * m_lpCoPub;
    
    ICfgSvr * m_lpCfgSvr;
    
    ISecurity * m_lpSecurity;

private:
    ///@todo, ����������
    //@{
    
    //@}
};


///��ת��������

class CService_initIoC : public IIoC
{
public:

    CService_initIoC(CService_initImpl * lpOwner)
    {
        m_lpOwner = lpOwner;
    }
    ///IIoC�ӿ�
    //@{
    unsigned long FUNCTION_CALL_MODE QueryInterface(HS_SID iid, IKnown **ppv);
    unsigned long FUNCTION_CALL_MODE AddRef();
    unsigned long FUNCTION_CALL_MODE Release();

    int FUNCTION_CALL_MODE SetConfig(const char * sPath, IRCfgObj * lpConfig);
    int FUNCTION_CALL_MODE SetDependService(HS_SID iid, IKnown * lpService);
    //@}
private:
    CService_initImpl * m_lpOwner;
};


///��������

class CService_initMgr : public IManager
{
public:
    CService_initMgr(CService_initImpl * lpOwner);
    ///IManager�ӿ�
    //@{
    unsigned long FUNCTION_CALL_MODE QueryInterface(HS_SID iid, IKnown **ppv);
    unsigned long FUNCTION_CALL_MODE AddRef();
    unsigned long FUNCTION_CALL_MODE Release();

    int FUNCTION_CALL_MODE ProcMngRequest(IF2UnPacker * lpInput, IF2Packer * lpOutput);
    int FUNCTION_CALL_MODE ProcMngAnswer(IF2UnPacker * lpInput);
    int FUNCTION_CALL_MODE ProcSysEvent(unsigned long dwMessageID,
                                        unsigned long dwWParam,
                                        unsigned long dwLParam,
                                        PFOnSetTimeOut pfOnSetTimeOut = NULL);
    //@}

private:
    ///�������������б�������Ͷ��塢���ݽṹ������
    //@{
    ///����������������REQ_ACTION
    typedef int (CService_initMgr::* REQ_ACTION)(IF2UnPacker * lpRequest, IF2Packer * lpAnswer);
    ///���崦�����б�ڵ�����

    typedef struct tagAction
    {
        REQ_ACTION lpAction; //������ָ��
        const char * sCaption; //������˵��
    } ACTION_INFO, * LPACTION_INFO;
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
    int mf_AddToActionList(unsigned long dwFuncNo, REQ_ACTION fpAction, const char * sCaption);
    ///ȡ���ܺŶ�Ӧ�Ĵ�����
    CService_initMgr::REQ_ACTION mf_GetAction(unsigned long dwFuncNo);
    //@}

    ///�����ܴ����������к���ԭ�;���:int mf_GetFuncList(IF2UnPacker * ,IF2Packer * )
    //@{
    ///��ѯ��������ܺ��б�
    int mf_GetFuncList(IF2UnPacker * lpRequest, IF2Packer * lpAnswer);
    ///@todo����������ܴ�����

    //@}
private:
    CService_initImpl * m_lpOwner;
}; /*lint !e1510*/


#endif       /*end def __Service_init_Impl_H__*/


