
/// ��˵��
/*******************************************************
Դ��������:
�������Ȩ:�������ӹɷ����޹�˾
ϵͳ����:  �������������ӿ�
ģ������:  Log
����˵��:  ʵ�ֺ�Log�ӿ���ص��ܱ���(�ṹ)
��    ��:  kongxy@hundsun.com
��������:  20071110 - 10071120
��    ע:  

  �޸���Ա��xuxp
  �޸����ڣ�20110221
  �޸�˵��������ILogService�ӿں�������ֹԭ�еĲ��������Լ���������Ӧ��ɳ��������bug

  �޸���Ա��yinghh
  �޸����ڣ�20110427
  �޸�˵��������ͷ�ļ�����stdlib.h�������������������ϵı������
*********************************************************/


#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_SLOGBEHAVIORPARA_4736C1D80021_INCLUDED
#define _INC_SLOGBEHAVIORPARA_4736C1D80021_INCLUDED
#include <string.h>
#include <stdlib.h>
#include <Include/plugin_interface.h>


#define SID_LOG				    	    "com.hundsun.fbase.log"
#define SID_BIZLOG                      "com.hundsun.fbase.bizlog"
#ifndef WRITE_LOG
#define WRITE_LOG if (m_lpLogService) m_lpLogService->AddLocalLog 
#endif

//##ModelId=49702F9801F6
typedef long HRESULT;
struct IESBMessage;

//20111221 dongpf ����������־����
enum LOG_WARNING_LEVEL 
{

	//##ModelId=49701C4100B4
    ESB_LOG_DEBUG = 0,

	//##ModelId=49701C4100B5
    ESB_LOG_EVENT = 1,

	//##ModelId=49701C4100B6
    ESB_LOG_WARNING = 2,
 
	//##ModelId=49701C4100B7
    ESB_LOG_ERRER = 3,

	//##ModelId=49701C4100B8
    ESB_LOG_CRUSHED = 4,

	ESB_LOG_IMPORTANTEVENT = 5,

	ESB_LOG_UNKNOWN = 6
};


//##ModelId=49702F980271
enum FILTER_MODE 
{
    ///@{

    /// ��������������ȼ�
    /**
      * ���ȼ��ߵĽ���Ȩ��ȡ��Ҫ���˵���־�����水�͵�������
      */
	//##ModelId=49702F980281
    FM_PRIORITY_LOWEST = (1<<0),

	//##ModelId=49702F980282
    FM_PRIORITY_LOW = (1<<1),

	//##ModelId=49702F980283
    FM_PRIORITY_BELOW_NORMAL = (1<<2),

	//##ModelId=49702F980290
    FM_PRIORITY_NORMAL = (1<<3),

	//##ModelId=49702F980291
    FM_PRIORITY_ABOVE_NORMAL = (1<<4),

	//##ModelId=49702F980292
    FM_PRIORITY_HIGH = (1<<5),

	//##ModelId=49702F980293
    FM_PRIORITY_VERY_HIGH = (1<<6),

	//##ModelId=49702F980294
    FM_PRIORITY_HIGHT = (1<<7),

    ///@}

    ///ָ�����������޸���־��Ϣ��Ȩ��
    /** ��־�������־��������������������԰���־�����Լ��Ĺ����޸�Դ��־����Ӱ��
      * �����Ĺ�����������������ʣ����龡������������ԣ����Ҫ��Ҫ������Ĺ�������
      * ����Э�̡�
      */
	//##ModelId=49702F9802A0
    FM_PURVIEW_MODIFY = (1<<16),

    ///��ֹͣ��־���̹�����������־���µ���Ϣ��Ȩ��(����!)
	//##ModelId=49702F9802A1
    FM_PURVIEW_STOP_FILTER = (1<<17),

    //�ռǲ�����
	//##ModelId=49702F9802A2
    FM_DISABLE = (1<<18)
};

/// һ����־���ܵ���
/** ����iLogID,szSrcModule,szDesc�Ǳ���ġ������Ҫ��¼һ����־ʱ��������
  * ICompLog::AddLocalLog���Ѳ���ָ��Ϊ�����iLogID��
  */
//##ModelId=49701C4100F1
struct SLog 
{
public:
    /// ��־ȫ��Ψһ��ʶ����־���������ֵ������
	//##ModelId=49701C410102
    int iLogID;

    /// ��Ҫ��¼��־��Դģ��
	//##ModelId=49701C410103
    char* szSrcModule;

    /// ��־��˵�������ı���
	//##ModelId=49701C410104
    char* szDesc;


    /// ������־��Դλ�ã����ǽ�szSrcModule����ϸ�Ķ�λ
	//##ModelId=49701C410105
    char* szSrcLocate;

    /// ˵�����ܻ�Ӱ�쵽������ģ�顢����
	//##ModelId=49701C410106
    char* szEffect;

    /// ����������Ч�Ĵ�����������Ǵ���
	//##ModelId=49701C410107
    char* szStrategy;

    /// ��־�Ľ����̶�
	//##ModelId=49701C410112
    LOG_WARNING_LEVEL iWarningLevel;

    /// ��־��˵������һ����̬�ı�������ı�ָ����̬�ı�����֯��ʽ
    ///�����׼C���printf�ĵ�һ��������
    /** �����ʽ��ȫ����printf�ĸ�ʽ��������֧������ʽ��ָ������ǰ�����ã�
      */
	//##ModelId=49701C410116
    char* szMsgFormat;
};


//##ModelId=49702F9802BF
struct ILogFilter : public IKnown
{
public:
    /// ����������ں���
    /// ������Ѿ�����־����ע���һ��������ʵ������ô��־�������־���ͣ����ã�������ӿ�
    /**
      *@ const SLog* lpLog:     �µ���־�������־ȫ��ά����������������ô���һ��Ҫ�޸����
      *                         ����־������ʹ�����������������������ѹ�����ģʽ����
      *                         FM_PURVIEW_MODIFYȨ�ޣ���ʹ�þ����ܵ͵����ȼ�����
      *                         FM_PRIORITY_LOWEST����ICompLog::AssignFilter
      *@ return:                I_OK�� S_STOP_LATER_FILTER��Log�����������ֵ������������Ϊ��
      *      I_OK��                 Log��������
      *      S_STOP_LATER_FILTER��  Log����֪ͨ�����Ĺ�����������־�����������Ⱥ���
      *                             FILTER_MODE::FM_PRIORITY_?������ͬ������ע����Ⱥ�
      *                             ���������ȼ��ߣ���ҪʹS_STOP_LATER_FILTER��Ч�����Ĺ�����
      *                             Ȩ�ޱ���Ҫ��FM_PURVIEW_STOP_FILTER������������ֵ��������
      *                             ��������û��Ȩ�ޣ���־������¼һ��ûȨ�޵���־��Ϣ������
      *                             ��־������κι�������ǿ�ҽ�����ʹ��FM_PRIORITY_NORMAL
      */
	//##ModelId=49702F9802D1
    virtual HRESULT Entry(const SLog* LpLog, va_list lpPara) = 0;
};

//20110221 xuxp Ϊ�����ӿڶ����ӵ��࣬���ڲ������ݣ���������ת��Ϊchar*
//�Զ����������
class CLogType
{
private:
	char* m_TypeValue;

public:
	CLogType(int iValue)
	{
		m_TypeValue = (char*)malloc(100);
		memset(m_TypeValue,0,100);
		sprintf(m_TypeValue,"%d",iValue);
	}

	CLogType(double iValue)
	{
		m_TypeValue = (char*)malloc(100);
		memset(m_TypeValue,0,100);
		sprintf(m_TypeValue,"%lf",iValue);
	}

	CLogType(float iValue)
	{
		m_TypeValue = (char*)malloc(100);
		memset(m_TypeValue,0,100);
		sprintf(m_TypeValue,"%lf",iValue);
	}

	CLogType(char* iValue)
	{
        // 20140805 ȥ��win64���뾯��
		int iLen = (int)strlen(iValue);
		m_TypeValue = (char*)malloc(iLen+1);
		memset(m_TypeValue,0,iLen+1);
		memcpy(m_TypeValue,iValue,iLen);
	}

	CLogType(char iValue)
	{
		m_TypeValue = (char*)malloc(100);
		memset(m_TypeValue,0,100);
		m_TypeValue[0] = iValue;
	}

	char* GetValue()
	{
		return m_TypeValue;
	}

	~CLogType()
	{
		free(m_TypeValue); 
	}
};

//20110221 xuxp �궨�壬�������
#define LOGTYPE(x) (new CLogType(x))

//##ModelId=49701C410126
struct ILogService : public IKnown
{
public:
   
    /// ����һ����־
    /// �ڱ�����־��¼�ļ��м���һ��ָ��������־��¼��
    /**
      *@ Param const char* szLocation:  ��־������λ��
      *@ Param int iLogID:      ָ��Ҫ���ӵ���־����־����������ʶ����־���
      *@ Param void* lpany(...):     Ϊ��չ���½ӿڣ����ں������ֵ
      *@ return I_OK:           �ɹ�д����־��������ʾ������־���¼������Ϣ��ע�����
      *                         ���������յ���������Ϊ��־��������������־��
      */
	//##ModelId=49701C410132
    virtual HRESULT AddLocalLog( const char* szLocation, int iLogID, ...   ) = 0;

    /// ����־����ע��һ��������
    /// Ŀ�����ڽ�ס������־���Ա����Ĵ�����ע�⿴iAttachMode����˵����
    /**
      *@ Param  HS_SID  lpFilter:       ��������GUID
      *@ return:                        I_OK�ɹ�ע�ᣬ������ʾ������־���¼�����Ϣ��
      *                                 ע����Ĺ��������յ���
      */
	//##ModelId=49701C410137
    virtual HRESULT AddFilter( ILogFilter *lpFilter, HS_SID FilterSID ) = 0;

    virtual HRESULT AddBizLog(  IESBMessage* lpReq,char *sError_PathInfo,int iError_no,char *sError_Info,int iError_id,char *sError_SysInfo ) = 0;
	
	//20110221 xuxp ���������AddLocalLog�ӿڣ��ѿɱ�������ʮ���̶���������ֹ�������
	/// ����һ����־
    /// �ڱ�����־��¼�ļ��м���һ��ָ��������־��¼��
    /**
      *@ Param const char* szLocation:  ��־������λ��
      *@ Param int iLogID:      ָ��Ҫ���ӵ���־����־����������ʶ����־���
      *@ Param CLogType* arg1:     д����־������ʵ��
	  *��������������������
      *@ return I_OK:           �ɹ�д����־��������ʾ������־���¼������Ϣ��ע�����
      *                         ���������յ���������Ϊ��־��������������־��
      */
	virtual HRESULT AddLocalLogEx( const char* szLocation, int iLogID, CLogType* arg1=NULL,CLogType* arg2=NULL,
		CLogType* arg3=NULL,CLogType* arg4=NULL,CLogType* arg5=NULL,CLogType* arg6=NULL,CLogType* arg7=NULL,
		CLogType* arg8=NULL,CLogType* arg9=NULL,CLogType* arg10=NULL) = 0;

	/// ��¼ҵ����־
	/**
      *@ Param int iLevel             ��ǰ��־����
	  *@ Param char *sError_PathInfo  ����·����Ϣ
	  *@ Param int iError_no          �����
	  *@ Param char *sError_Info      ������Ϣ
	  *@ Param int iError_id          ϵͳ������
	  *@ Param char *sError_SysInfo   ϵͳ������Ϣ
	  *@ Param int iFunctionNo        ���ܺ�
	  *@ return  I_OK   :   0 �ɹ� -1 ʧ��
	*/
	virtual HRESULT AddBizLogEx(int iLevel, const char *sError_PathInfo,int iError_no, const char *sError_Info,int iError_id, const char *sError_SysInfo, int iFunctionNo) = 0;

};

#ifdef __cplusplus
extern "C" {
#endif

    int FUNCTION_CALL_MODE GetLogServiceInfo( int, tagBaseServiceInfo* );

#ifdef __cplusplus
}
#endif


#endif /* _INC_ICOMPLOG_4734086E0225_INCLUDED */
