//20130701 xuxp �����ֶ�֧�ֵ�16��
//20140228 xuxp �����ӿڣ�����������Դ�ڲ�ͬϵͳ������
//20140314 xuxp ���ӻ�ȡ�������충����Ϣ�ӿ�
//20140825 majc ���ӻ�ȡ�������͵Ľӿ�
#ifndef __MCGD_interface__
#define __MCGD_interface__
#include <Include/mc_glbdef.h>
#include <Include/plugin_interface.h>
#include <Include/esb_message_interface.h>
#include <os/inttypes.h>
#include <os/config_env.h>
#include <Include/pack_interface.h>
#include <Include/glbdef.h>
#include <Include/mcmsg_interface.h>
#include <map>


using namespace std;

USING_FBASE2_MC_NAMESPACE
BEGIN_FBASE2_MC_NAMESPACE

///����ӿ�ID����
#define SID_MCGD "com.hundsun.fbase.mcgd"
//20130701 xuxp �����ֶ�֧�ֵ�16��
//#define MAX_FILTER_FIELDS 6
#define MAX_FILTER_FIELDS 16
//#define MAX_ALLFILTER_FIELDS 8
#define MAX_ALLFILTER_FIELDS 18
#define MAX_FILTERFIELD_LEN 63
#define MAX_TOPICNAME_LEN 256
#define MAX_SUBSCRIBENAME_LEN 32
#define MAX_PUBLISHERNAME_LEN 32

#define MAX_MACADDRESS_LEN	18
#define MAX_RAND_LEN	4
//20140328 xuxp �ĳ�һ�µĺ궨��
#define MAX_BIZNAME_LEN IDENTITY_NAME_LENGTH+1+MAX_MACADDRESS_LEN+1+MAX_RAND_LEN+2

enum ReliableLevel{LEVEL_DOBEST =0,//������Ϊ
				   LEVEL_DOBEST_BYSEQ = 1,//��������
				   LEVEL_MEM = 2,//�ڴ�
				   LEVEL_FILE = 3,//�ļ�
				   LEVEL_SYSTEM= 4};//ϵͳ


//�ڵ��ͨ�Ų��·����Ϣ
typedef struct tagrouteinfo
{
	//���������ֶ��Ƿ����ߵķ�������Ϣ
	char m_ospfName[ID_STR_LEN+1] ;
	char m_nbrName[IDENTITY_NAME_LENGTH+1] ;
	char m_svrName[SVRINSTANCE_NAME_LENGTH+1] ;
	char m_pluginId[PLUGIN_NAME_LENGTH+1] ;
	int  m_connectId ;
	int  m_memberNo ;
	//����Ԥ��������
	char m_domainName[ID_STR_LEN+1] ;
	tagrouteinfo()
	{
		memset(this, 0, sizeof(tagrouteinfo));
	}

	int clone(tagrouteinfo* lpRoute)
	{
		strncpy(lpRoute->m_ospfName,m_ospfName,ID_STR_LEN);
		strncpy(lpRoute->m_nbrName,m_nbrName,IDENTITY_NAME_LENGTH);
		strncpy(lpRoute->m_svrName,m_svrName,SVRINSTANCE_NAME_LENGTH);
		strncpy(lpRoute->m_pluginId,m_pluginId,PLUGIN_NAME_LENGTH);
		strncpy(lpRoute->m_domainName,m_domainName,ID_STR_LEN);
		lpRoute->m_connectId = m_connectId;
		lpRoute->m_memberNo = m_memberNo;
		return 0;
	}

	bool equal(tagrouteinfo* lpRoute)
	{
		if(strcmp(m_ospfName, lpRoute->m_ospfName)!=0)
			return false;
		if(strcmp(m_nbrName, lpRoute->m_nbrName)!=0)
			return false;
		if(strcmp(m_svrName, lpRoute->m_svrName)!=0)
			return false;
		if(strcmp(m_pluginId, lpRoute->m_pluginId)!=0)
			return false;
		if(m_connectId!= lpRoute->m_connectId)
			return false;
		if(m_memberNo!= lpRoute->m_memberNo)
			return false;
		return true;
	}

}ROUTE_INFO,*LPROUTE_INFO;

//����������
typedef struct tagsendpath
{
	char m_szName[MAX_BIZNAME_LEN+1];//ҵ����
	
	int clone(tagsendpath* lpSend)
	{
		strncpy(lpSend->m_szName,m_szName,MAX_BIZNAME_LEN);
		return 0;
	}

	inline bool operator== (const tagsendpath& lValue) const
	{
		if(strcmp(m_szName, lValue.m_szName)!=0)
			return false;
		return true;
	}

    inline tagsendpath& operator=(const tagsendpath& one)
    {
        if (this != &one)
        {
            memset(this, 0, sizeof(tagsendpath));
            memcpy(this->m_szName, one.m_szName, strlen(one.m_szName));
        }

        return *this;
    }

    tagsendpath()
	{
		memset(this, 0, sizeof(tagsendpath));
	}
} SENDER_NAME,*LPSENDER_NAME ;


class CFilterName
{
public:
	inline CFilterName(const char* lpName)
	{
		int iSize=sizeof(m_szName);
		memset(m_szName, 0, iSize);
		strncpy(m_szName, lpName, iSize-1);
	};
 	inline CFilterName()
 	{
 		memset(this, 0, sizeof(CFilterName));
 	};
	inline ~CFilterName()
	{
	};
	inline bool operator < (const CFilterName& lValue) const
	{
		if(strcmp(m_szName, lValue.m_szName)<0)
			return true;
		else
			return false;
	};
	inline bool operator == (const CFilterName& lValue) const
	{
		if(strcmp(m_szName, lValue.m_szName)==0)
			return true;
		else
			return false;
	};
	inline const char* GetName() const
	{
		return m_szName;
	}

private:
	char m_szName[MAX_FILTERFIELD_LEN+1];
};

//����������ȡֵ����Ǽ��ϣ���0x02��Ϊ�ָ�����Ȼ����ӵ�����������
typedef struct tagfilter
{
	char	lppFieldName[MAX_ALLFILTER_FIELDS][MAX_FILTERFIELD_LEN+1];//�����ֶ�����
	char	lppFieldlue[MAX_ALLFILTER_FIELDS][MAX_FILTERFIELD_LEN+1];//�����ֶ�ȡֵ
	int		nFilterCount;//������������
	
	bool isEqual(tagfilter* lValue) const
	{
		if (nFilterCount != lValue->nFilterCount)
		{
			return false;
		}
		
		for (int i=0;i<nFilterCount;i++)
		{
			char* strName = lValue->lppFieldName[i];
			if(!strName || strcmp(strName,lppFieldName[i])!=0 )
			{
				return false;
			}

			char* strValue = lValue->lppFieldlue[i];
			if(!strValue || strcmp(strValue,lppFieldlue[i])!=0 )
			{
				return false;
			}
		}
		
		return true;
	}

	tagfilter()
	{
		memset(this,0,sizeof(tagfilter));
	}
	~tagfilter()
	{
	}

	void clone(tagfilter* lValue)
	{
		for (int i=0;i<nFilterCount;i++)
		{
			memcpy(lppFieldName[i],lValue->lppFieldName[i],MAX_FILTERFIELD_LEN);
			memcpy(lppFieldlue[i],lValue->lppFieldlue[i],MAX_FILTERFIELD_LEN);
		}
	}

	int GetCount()
	{
		return nFilterCount;
	}
	
	char* GetFilterNameByIndex(int index)
	{
		if (index >= nFilterCount)
		{
			return NULL;
		}
		return lppFieldName[index];
	}
	
	char* GetFilterValueByIndex(int index)
	{
		if (index >= nFilterCount)
		{
			return NULL;
		}
		return lppFieldlue[index];
	}
	
	char* GetFilterValue(char*  fileName)
	{
		for (int i=0;i<nFilterCount;i++)
		{
			if (strcmp(lppFieldName[i],fileName) == 0 )
			{
				return lppFieldlue[i];
			}
		}
		return NULL;
	}
	void SetFilterValue(char* filterName,char* filterValue)
	{
		if (nFilterCount>MAX_ALLFILTER_FIELDS)
		{
			return;
		}

		//���ж��Ƿ��������ֶΣ����ھ��滻����ֵ
		for (int i=0;i<nFilterCount;i++)
		{
			if (strcmp(lppFieldName[i],filterName) == 0 )
			{
				strncpy(lppFieldlue[i],filterValue,MAX_FILTERFIELD_LEN);
				return ;
			}
		}

		//û�о��¼�
		strncpy(lppFieldName[nFilterCount],filterName,MAX_FILTERFIELD_LEN);
		strncpy(lppFieldlue[nFilterCount],filterValue,MAX_FILTERFIELD_LEN);
		nFilterCount++;
	}

}FILTER,*LP_FILTER;

//���충���ߵĽṹ��
typedef struct tagBornSubcribe
{
	uint16 m_uTopicNo; //������
	LP_FILTER m_lpFilterValue;
	tagBornSubcribe* m_lpNext;
	tagBornSubcribe()
	{
		memset(this, 0, sizeof(tagBornSubcribe));
	}
	~tagBornSubcribe()
	{
		if (m_lpFilterValue)
		{
			delete m_lpFilterValue;
		}
	}

	uint32 GetMem()
	{
		uint32 useMem = sizeof(uint16)+ sizeof(LP_FILTER) + sizeof(tagBornSubcribe*);
		if (m_lpFilterValue)
		{
			useMem += sizeof(FILTER);
		}
		return useMem;
	}
}BORN_SUBSCRIBE,*LPBORN_SUBSCRIBE;


/*
��������Ĳ�������ǣ�
First()
while(!IsEOF())
{
	��ȡ����
	Next();
}                                                               
*/
//�����Ӧ�ķ��������ֺ���ŵı����ӿڣ����ڿ����ָ�
struct IGlobalNoMap: public IKnown
{
	virtual int FUNCTION_CALL_MODE GetPublisherCount() = 0;//��ȡ�����߸���
	virtual uint16 FUNCTION_CALL_MODE GetPublisherNo() = 0;//��ȡ���������
	virtual uint32 FUNCTION_CALL_MODE GetStartNo() = 0;//��ǰ��Ч���ڵ���С���
	virtual uint32 FUNCTION_CALL_MODE GetLastNo() = 0;//��ǰ�����ߵ��������
	virtual void FUNCTION_CALL_MODE SetRecomList(void* lpList) = 0;//���������
	virtual void* FUNCTION_CALL_MODE GetRecommList() = 0;//��ȡ�������ָ��

	virtual int FUNCTION_CALL_MODE IsEOF() = 0;
	virtual int FUNCTION_CALL_MODE Next() = 0;
	virtual int FUNCTION_CALL_MODE First() = 0;
};

//�������Բ����ӿ�
struct ITopicAttribute: public IKnown
{
	//��ȡ�������Խӿ�
	virtual uint16 FUNCTION_CALL_MODE GetTopicNo() = 0;
	virtual char* FUNCTION_CALL_MODE GetTopicName() = 0;//�������֣����ֱ���ֻ������ĸ�����֣��Լ�����"."��ɣ�����"."�Ǹ�������ָ��������ִ�Сд
	virtual uint8 FUNCTION_CALL_MODE GetReliableLevel() = 0;//�ɿ��Եȼ�,0�Ǿ�����Ϊ��1��������2�ڴ漶��3�ļ�����4ϵͳ��
	virtual uint8 FUNCTION_CALL_MODE GetIssuePriority() = 0;//�������ȼ�,����Խ�����ȼ�Խ�ߣ�Ĭ����6��ȡֵ��Χ6-13
	virtual uint32 FUNCTION_CALL_MODE GetMsgLifetime() = 0;//��Ϣ��Ч�ڣ��Է���Ϊ��λ��Ĭ��Ϊ0��ֻ����ļ����Լ����ϵ�������Ч
	virtual uint8 FUNCTION_CALL_MODE GetStutas() = 0;// ����״̬,0�����ã�1�ǽ���
	virtual uint8 FUNCTION_CALL_MODE GetTickStrategy() = 0;// �������˲���,0��ʾ����Ҫ���ˣ�1��ʾ��֮ǰ��½�ģ�2��ʾ�ߺ����½��
	virtual uint8 FUNCTION_CALL_MODE GetBusinessVerify() = 0;//�Ƿ���Ҫҵ��У�飬0����Ҫ��1��Ҫ
	//20121212 xuxp �����������ԣ���ʾ�Ƿ��Ǿֲ������⣬ֻ��ȫ�ֵ����⣬�¼�����Ҫ���Ƹ��ϼ���Ĭ����ȫ������
	virtual uint8 FUNCTION_CALL_MODE GetLocalTopic() = 0;//�Ƿ��Ǿֲ�����
	virtual char* FUNCTION_CALL_MODE GetFilterName(int index=0) = 0;//��ȡ�Ѷ���Ĺ����ֶ����֣�һ������
	virtual int FUNCTION_CALL_MODE GetTopicCrc() = 0;//��ȡ����У����

	virtual char* FUNCTION_CALL_MODE GetSubscribeStr() = 0;//�����߲����б�֧�֡�*������?��
	virtual char* FUNCTION_CALL_MODE GetPublishStr() = 0;//�����߲����б�֧�֡�*������?��

	//�����������Խӿڣ�ֻ��״̬���ԣ������߲������ͷ����߲��������Զ�̬�޸ġ�
	virtual int FUNCTION_CALL_MODE SetStutas(bool bStutas) = 0;//true��ʾ������ã�false��ʾ�������
	virtual int FUNCTION_CALL_MODE SetSubscribeStr(char* strSub) = 0;//���ö����߲�����
	virtual int FUNCTION_CALL_MODE SetPublisherStr(char* strPub) = 0;//���÷����߲�����
	virtual int FUNCTION_CALL_MODE SetTopicCrc(int nTopicCrc) = 0;//����У��ͣ�ֻ�����¼���Ϣ����

	//�ж��Ƿ������������ֶ�
	virtual int FUNCTION_CALL_MODE FindFilterName(char* filedName) = 0;

	//20140825 majc ���ӻ�ȡ�������͵Ľӿ�
	virtual int FUNCTION_CALL_MODE GetIssueType() = 0;
};


///����ӿڶ���
struct IMCGD: public IKnown
{

	/**
	* ��ʼ��ȫ������ģ�飬�ȳ�ʼ������ӿڣ�����ӿڲſ��Ե���
	* @param lpTopicList ������ϸ����
	* @return ����0��ʾ�ɹ��������ʾʧ�ܣ�ͨ������GetErrorMsg���Ի�ȡ��ϸ������Ϣ
	* ������������ֶ������£�
	* TopicName ReliableLevel IssuePriority MsgLifetime Stutas TickStrategy BusinessVerify Local FilterField1 FilterField2 
	*	FilterField3 FilterField4 FilterField5 FilterField6 SubscribeStr PublishStr
	* û�е��ֶξ͸�ֵΪ""
	*/
	virtual int FUNCTION_CALL_MODE InitGD(IF2UnPacker* lpTopicList) = 0;		

	///////////////////////////////////������صĽӿ�///////////////////////////////////////
	/**
	* ��ȡָ����ŵ�������Ϣ
	* @param topicNo ������
	* @param topicName��������
	* @return ���ض�Ӧ��������Ϣ��ʧ�ܷ���NULL
	*/
	virtual ITopicAttribute* FUNCTION_CALL_MODE GetTopicInfoByNo(int topicNo,char* topicName) = 0;

	/**
	* ���ݱ�Ż�ȡ��������
	* @param topicNo ������
	* @return ���ض�Ӧ����������
	*/
	virtual char* FUNCTION_CALL_MODE GetTopicNameByNo(int topicNo) = 0;


	/**
	* ���������źͷ���������,�������ߵ������б�У�鵱ǰ�������Ƿ���Է����������
	* @param topicNo ������
	* @param publishName ����������
	* @return ����true��ʾУ��ͨ����false�Ǽ���ʧ��
	*/
	virtual bool FUNCTION_CALL_MODE CheckPublishList(int topicNo,char* publishName) = 0;

	/**
	* ���������źͶ���������,�������ߵ������б�У�鵱ǰ�������Ƿ���Զ����������
	* @param topicNo ������
	* @param subscribeName ����������
	* @return ����true��ʾУ��ͨ����false�Ǽ���ʧ��
	*/
	virtual bool FUNCTION_CALL_MODE CheckSubscribeList(int topicNo,char* subscribeName) = 0;

	/**
	* ���ݱ�Ż�ȡ����ɿ�����
	* @param topicNo ������
	* @return ���ض�Ӧ������ɿ����𣬾������涨�弸�֣�-1��ʾû�ж�Ӧ��������
	*/
	virtual int FUNCTION_CALL_MODE GetTopicLevelByNo(int topicNo) = 0;

	/**
	* ���ݱ�Ż�ȡ���˲���
	* @param topicNo ������
	* @return ���ض�Ӧ�����˲��ԣ�-1��ʾû�ж�Ӧ��������
	*/
	virtual int FUNCTION_CALL_MODE GetTickStrategyByNo(int topicNo) = 0;

	/**
	* ���ݱ�Ż�ȡ�Ƿ�ҵ��У��
	* @param topicNo ������
	* @return ���ض�Ӧҵ��У�飬-1��ʾû�ж�Ӧ��������
	*/
	virtual int FUNCTION_CALL_MODE GetBusinessVerifyByNo(int topicNo) = 0;

	/**
	* ���ݱ�Ż�ȡ�����Ƿ��Ǿֲ���
	* @param topicNo ������
	* @return ���ض�Ӧ����ľֲ�����,-1��ʾû�ж�Ӧ��������
	*/
	virtual int FUNCTION_CALL_MODE GetTopicLocalByNo(int topicNo)= 0;

	/**
	* �������ֻ�ȡ������
	* @param topicName ��������
	* @return ���ض�Ӧ��������
	*/
	virtual uint16 FUNCTION_CALL_MODE GetTopicNoByName(char*  topicName) = 0;

	//��ȡ������ĸ������������ʱ�����ȡ�������ŵ������С
	/**
	* �����������ȡ
	* @param topicNo ������
	* @return �ɹ����������������0��ʾû��������,������ʾû���������
	*/
	virtual int FUNCTION_CALL_MODE GetTopicChildCount(int topicNo) = 0;

	/**
	* �������б��ȡ
	* @param topicNo ������
	* @param arrayCOunt �����������������������
	* @return �ɹ����ض�Ӧ�����������ָ�룬��������ڴ��������з���
	*/
	virtual uint16* FUNCTION_CALL_MODE GetTopicChild(int topicNo,int* arrayCOunt) = 0;

	/**
	* �����������
	* @return �ɹ��ͷ������������ʧ�ܷ���-1��
	*/
	virtual int FUNCTION_CALL_MODE GetTopicCount() = 0;

	/**
	* �����±귵���������ԣ����ڱ�����ע���±��0��ʼ
	* @param index ������
	* @return �ɹ��ͷ��ض�Ӧ���������ԣ�ʧ�ܷ���NULL��
	*/
	virtual ITopicAttribute* FUNCTION_CALL_MODE GetTopicInfoByindex(int index)=0;

	///////////////////////////////////������صĽӿڵ��˽���///////////////////////////////////////

	///////////////////////////////////���충����صĽӿ�///////////////////////////////////////
	/**
	* ��ʼ���������충���ߣ�����֧����������,������ֻ�ܸ��ݶ�������������ӣ�������������Ե���
	* @param lpUnPacker ���е����충������Ϣ
	* @return �ɹ�����0��ʧ�ܷ��ظ���
	* �����������ֶ��У����������֣�SubscribeName�� �������֣�TopicName�����Լ�
	* ����Ĺ�������FilterField1 FilterField2 FilterField3 FilterField4 FilterField5 FilterField6
	* ��������û�о�ȡ��
	*/
	virtual int FUNCTION_CALL_MODE InitBornTopic(IF2UnPacker* lpUnPacker) = 0;
	

	/**
	* ���충���߻�ȡ
	* @param subName ���Ķ˵�����
	* @return ���ض�Ӧ�����ߵ����충������Ϣ��ʧ�ܷ���NULL����һ��������Ҫ������ȡ�������충���ߣ�������Ϊ0�ڵ�����
	*/
	virtual LPBORN_SUBSCRIBE FUNCTION_CALL_MODE GetBornByName(char* subName) = 0;


	/**
	* ֻ�����һ�������������충����ɾ������
	* @param subName ���Ķ˵�����
	* @param lpUnPacker ���충���߶�Ӧ�Ĺ���������Ϣ���ṹ��ͬ����ķ���ֵ
	* @return �ɹ�����0.ʧ�ܷ��ظ���
	* �����������ֶ��У��������֣�topicName�����Լ�����Ĺ������������������еĹ��ֶ����֣�
	*/
	virtual int FUNCTION_CALL_MODE DeleteBornTopicByName(char* subName,IF2UnPacker* lpUnPacker) = 0;

	/**
	* ֻ�����һ�������������충�������Ӳ���
	* @param subName ���Ķ˵�����
	* @param lpUnPacker ���충���߶�Ӧ�Ĺ���������Ϣ���ṹ��ͬ����ķ���ֵ
	* @return �ɹ�����0.ʧ�ܷ��ظ���
	* �����������ֶ��У��������֣�topicName�����Լ�����Ĺ������������������еĹ��ֶ����֣�
	*/
	virtual int FUNCTION_CALL_MODE AddBornTopicByName(char* subName,IF2UnPacker* lpUnPacker) = 0;
	///////////////////////////////////���충����صĽӿڵ��˽���///////////////////////////////////////

	///////////////////////////////////��������صĽӿ�///////////////////////////////////////

	/**
	* ��ӷ����߱����Ϣ
	* @param lpSenderName�����ߵ�������Ϣ������ҵ�����ֺͷ�������Ϣ
	* @return �ɹ��ͷ��ص�ǰ�����ߵ���ţ�ʧ�ܾͷ��ظ�����
	*/
	virtual int FUNCTION_CALL_MODE AddPublishNo(const char* lpSenderName) = 0;


	/**
	* ��ȡָ�����ֵķ����߱��
	* @param lpSenderName�����ߵ�������Ϣ
	* @return �ɹ��ͷ��ص�ǰ�����ߵ���ţ�ʧ�ܾͷ��ظ�����
	*/
	virtual int FUNCTION_CALL_MODE GetPublishNo(const char* lpSenderName) = 0;
	
	/**
	* ��ȡָ����ŵķ�����������Ϣ
	* @param publishNo �����ߵ����
	* @return �ɹ��ͷ��ض�Ӧ�����֣�ʧ�ܷ���NULL
	*/
	virtual char* FUNCTION_CALL_MODE GetPublishName(int publishNo) = 0;
	///////////////////////////////////��������صĽӿڵ��˽���///////////////////////////////////////

	///////////////////////////////////ȫ�����ӳ��ӿ�///////////////////////////////////////
	/**
	* ����������еĶ���ָ��
	* @param topicNo ������
	* @param publishNo �����߱��
	* @param lpList ������е�ָ��
	* @return �ɹ��ͷ���0���������ر�ʾʧ�ܡ�
	*/
	virtual int FUNCTION_CALL_MODE SetRecomList(int topicNo, int publishNo ,void* lpList) = 0;


	/**
	* �����������Լ������߱�Ż�ȡ��Ӧ���������
	* @param topicNo ������
	* @param publishNo �����߱��
	* @return �ɹ��ͷ����������ָ�룬ʧ�ܷ���NULL��
	*/
	virtual void* FUNCTION_CALL_MODE GetRecomList(int topicNo, int publishNo) = 0;


	/**
	* ���������ȡ��ǰ���еķ����ߺ������Ϣ
	* @return �ɹ��ͷ��ض�Ӧ�ı����ӿڣ�ʧ�ܷ���NULL��
	*/
	virtual IGlobalNoMap* FUNCTION_CALL_MODE GetGlobalNoMap(int topicNo) = 0;
	/**
	* ���������ż�����������в���ʱ��Ҫ
	* @param topicNo ������
	*/
	virtual void FUNCTION_CALL_MODE LockRecomList(int topicNo) = 0;

	/**
	* ���������Ž�����������в���ʱ��Ҫ
	* @param topicNo ������
	*/
	virtual void FUNCTION_CALL_MODE UnLockRecomList(int topicNo) = 0;
	
	/**
	* ���յ�����Ϣ��ӵ�ȫ�����
	* @param topicNo ������
	* @param publishNo �����߱��
	* @param msgNo ��Ϣ���
	* @return �ɹ��ͷ��ص�ǰ��Ϣ���ڲ���ţ�ʧ�ܾͷ���0
	*/
	virtual uint32 FUNCTION_CALL_MODE AddGlobalNo(int topicNo, int publishNo,uint32 msgNo) = 0;


	/**
	* ����ȫ���������ȡ��Ӧ���ڲ����
	* @param topicNo ������
	* @param publishNo �����߱��
	* @param msgNo ��Ϣ���
	* @return �ɹ��ͷ��ص�ǰ��Ϣ���ڲ���ţ�ʧ�ܾͷ���0
	*/
	virtual uint32 FUNCTION_CALL_MODE GetInternalNo(int topicNo, int publishNo,uint32 msgNo) = 0;


	/**
	* ��ȡ��ǰ������������ߣ���Ч��Ϣ����ʼ���
	* @param topicNo ������
	* @param publishNo �����߱��
	* @return �ɹ��ͷ��ص�ǰ��Ч����С��ţ�ʧ�ܾͷ���0
	*/
	virtual uint32 FUNCTION_CALL_MODE GetStartNo(int topicNo, int publishNo) = 0;

	/**
	* ��ȡȫ�����
	* @param topicNo ������
	* @param publishNo �����߱��
	* @return �ɹ��ͷ��ص�ǰ���µ���ŵ���һ����ţ�ʧ�ܾͷ���0
	*/
	virtual uint32 FUNCTION_CALL_MODE GetLastNo(int topicNo, int publishNo) = 0;

	/**
	* ��ȡ�����Ӧ�ķ����߸���
	* @param topicNo ������
	* @return �ɹ��ͷ��ص�ǰ����ķ����߸�����ʧ�ܾͷ���0
	*/
	virtual uint32 FUNCTION_CALL_MODE GetPubilshCount(int topicNo) = 0;


	/**
	* ��ȡ���µ��ڲ����
	* @param topicNo ������
	* @return �ɹ��ͷ��ص�ǰ���µ��ڲ���ţ�ʧ�ܾͷ���0
	*/
	virtual uint32 FUNCTION_CALL_MODE GetLastInternelNo(int topicNo) = 0;
	///////////////////////////////////ȫ�����ӳ��ӿڵ��˽���///////////////////////////////////////

	///////////////////////////////////��Ϣ����Ľӿ�///////////////////////////////////////

	/**
	* �����Ϣ����
	* @param topicNo ������
	* @param InternalNo �ڲ����
	* @param lpMsg �������Ϣ
	* @return �ɹ�����0��ʧ�ܷ��ظ���
	*/
	virtual int FUNCTION_CALL_MODE AddMessage(int topicNo, uint32 InternalNo,IESBMessage* lpMsg, int publishNo=0,uint32 uMsgId=0) = 0;


	/**
	* ������ȱ�������������ڽڵ�ͬ����������Ϣ����Ҫ������Ϣ�����������ѡ��������
	* @param topicNo ������
	* @param InternalNo �ڲ����
	* @param lpMsg �������Ϣ
	* @return �ɹ�����0��ʧ�ܷ��ظ���
	*/
	virtual int FUNCTION_CALL_MODE AddMessageForGroup(int topicNo, uint32 InternalNo,IESBMessage* lpMsg, int publishNo=0,uint32 uMsgId=0) = 0;


	/**
	* �����ڲ���Ż�ȡ��Ϣ�������鲥��ȡ��Ϣ
	* @param topicNo ������
	* @param InternalNo �ڲ����
	* @param publishNo �����߱��
	* @return �ɹ����ؾ�����Ϣָ�룬ʧ�ܷ���NULL
	*/
	virtual IESBMessage* FUNCTION_CALL_MODE GetMessage(int topicNo, uint32 InternalNo) = 0;

	
	/**
	* �����ڲ���Ż�ȡ��Ϣ,���ڻỰ���ȡ��Ϣ
	* @param topicNo ������
	* @param InternalNo �ڲ����
	* @return �ɹ�����һ����װ����Ϣָ�룬���ʹ�õ�ʱ����Ҫ�ٴη�װ
	*/
	virtual IMCMemCachedMsg* FUNCTION_CALL_MODE GetMsgForSession(int topicNo, uint32 InternalNo) = 0;
	
	///////////////////////////////////��Ϣ����Ľӿڵ��˽���///////////////////////////////////////

	///////////////////////////////////���������Ľӿ�///////////////////////////////////////

	/**
	* ��ӹ�������
	* @param topicNo ������
	* @param InternalNo �ڲ����
	* @param lpFilter ���������Ľṹ��ʽ
	* @return �ɹ�����0������ʧ��
	*/
	virtual int FUNCTION_CALL_MODE AddFilterIndex(int topicNo,uint32 InternalNo, LP_FILTER lpFilter) = 0;


	/**
	* �����ڲ������ʼֵ�Լ�����������ȡ��Ϣ���ڲ�����б�
	* @param topicNo ������
	* @param sInternalNo �ڲ����
	* @param eInternalNo �����ڲ���ţ��������0���ͱ�ʾ������ǰ���µġ�
	* @param lpFilter ��������
	* @param InternalList �ڲ�����ռ䣬�������0���ⲿ��Ҫ��������ĺ����ͷſռ�
	* @param nCount ���Ϲ��������ĸ���������ֵ��-2�Լ�-3��ʱ�����ֵ��ʾ��ǰ�ڴ�������Ч�ڵ���С��ţ��ⲿӦ������������Ϊ��ʼ�Ĳ�ȱ���
	* @return �ɹ����ط��������ĸ�����������ʾʧ�ܣ�-1��ʾ�ڲ���ȡ���ԣ�-2��û�й���������-3���Զ���Ĺ�������
	* ����-2��-3�����������Ҫ�Լ���ȡ�����ڲ���ţ������ڲ����һ������ȡ��Ȼ��ȽϹ�������
	*/
	virtual int FUNCTION_CALL_MODE GetInternalList(int topicNo,uint32 sInternalNo, uint32 eInternalNo, LP_FILTER lpFilter,uint32** InternalList,int* nCount) = 0;

	/**
	* �ͷ����溯�����ص�int����ռ�
	* @param InternalList ���溯�����ص�int����
	*/
	virtual void FUNCTION_CALL_MODE ReleaseInternalList(uint32* InternalList) = 0;
	///////////////////////////////////���������Ľӿڵ��˽���///////////////////////////////////////


	///////////////////////////////////�������ݻ���ӿ�///////////////////////////////////////
	/**
	* �����Ϣ���鲥��������
	* @param lpMsg ��Ҫ��ӵ���Ϣ
	* @return �ɹ�����0��������ʾʧ��
	*/
	virtual int FUNCTION_CALL_MODE AddMsgForGroup(IESBMessage* lpMsg) = 0;


	/**
	* ��ȡ�鲥���������Ӧ����Ϣ���������ڲ�ȱ
	* @param uTopicNo ������
	* @param cPublishName ����������
	* @param msgId ��Ϣ���
	* @return �ɹ����ض�Ӧ��Ϣ����������NULL
	*/
	virtual IESBMessage* FUNCTION_CALL_MODE GetMsgForGroup(uint16 uTopicNo,const char* cPublishName,uint32 msgId) = 0;

	///////////////////////////////////�������ݻ���ӿڵ��˽���///////////////////////////////////////

	
	virtual IMCMessagePtr*	FUNCTION_CALL_MODE AllocMCMessagePtr()=0;
	virtual IMCMemCachedMsg* FUNCTION_CALL_MODE AllocMCMemCachedMsg()=0;

	//20140228 xuxp �����ӿڣ�����������Դ�ڲ�ͬϵͳ������
	virtual int FUNCTION_CALL_MODE AddTopic(IF2UnPacker* lpTopicUnpack) = 0;//������⣬�������������ڲ�ͬϵͳ
	//�������ʹ�����������ڶ�ϵͳ��ʱ���������ͨ��AddTopic��ɣ�Ȼ���ٵ������������ʼ������InitGD����ֻ��ѡ��һ����������ʼ��
	virtual int FUNCTION_CALL_MODE InitGDEx() = 0;
	virtual int FUNCTION_CALL_MODE AddBornTopic(IF2UnPacker* lpTopicUnpack) = 0;//������충���ߣ��������충�������ڲ�ͬϵͳ
	virtual int FUNCTION_CALL_MODE GetTopicFromSystem(int topicNo) = 0;//�����������ֻ�ȡ�����������ĸ�ϵͳ
	//20140314 xuxp ���ӻ�ȡ�������충����Ϣ�Ľӿ�
	virtual int FUNCTION_CALL_MODE GetAllBornInfo(IF2Packer* lpBornPack) = 0;
};
END_FBASE2_MC_NAMESPACE
#endif
