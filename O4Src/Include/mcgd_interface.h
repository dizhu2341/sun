//20130701 xuxp 过滤字段支持到16个
//20140228 xuxp 新增接口，满足主题来源于不同系统的需求
//20140314 xuxp 增加获取所有先天订阅信息接口
//20140825 majc 增加获取发布类型的接口
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

///插件接口ID定义
#define SID_MCGD "com.hundsun.fbase.mcgd"
//20130701 xuxp 过滤字段支持到16个
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
//20140328 xuxp 改成一致的宏定义
#define MAX_BIZNAME_LEN IDENTITY_NAME_LENGTH+1+MAX_MACADDRESS_LEN+1+MAX_RAND_LEN+2

enum ReliableLevel{LEVEL_DOBEST =0,//尽力而为
				   LEVEL_DOBEST_BYSEQ = 1,//尽力有序
				   LEVEL_MEM = 2,//内存
				   LEVEL_FILE = 3,//文件
				   LEVEL_SYSTEM= 4};//系统


//节点的通信层的路径信息
typedef struct tagrouteinfo
{
	//下面六个字段是发布者的发送者信息
	char m_ospfName[ID_STR_LEN+1] ;
	char m_nbrName[IDENTITY_NAME_LENGTH+1] ;
	char m_svrName[SVRINSTANCE_NAME_LENGTH+1] ;
	char m_pluginId[PLUGIN_NAME_LENGTH+1] ;
	int  m_connectId ;
	int  m_memberNo ;
	//下面预留个域名
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

//发布者名字
typedef struct tagsendpath
{
	char m_szName[MAX_BIZNAME_LEN+1];//业务名
	
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

//过滤条件的取值如果是集合，用0x02作为分隔符，然后添加到过滤条件中
typedef struct tagfilter
{
	char	lppFieldName[MAX_ALLFILTER_FIELDS][MAX_FILTERFIELD_LEN+1];//过滤字段名字
	char	lppFieldlue[MAX_ALLFILTER_FIELDS][MAX_FILTERFIELD_LEN+1];//过滤字段取值
	int		nFilterCount;//过滤条件个数
	
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

		//先判断是否存在这个字段，存在就替换成新值
		for (int i=0;i<nFilterCount;i++)
		{
			if (strcmp(lppFieldName[i],filterName) == 0 )
			{
				strncpy(lppFieldlue[i],filterValue,MAX_FILTERFIELD_LEN);
				return ;
			}
		}

		//没有就新加
		strncpy(lppFieldName[nFilterCount],filterName,MAX_FILTERFIELD_LEN);
		strncpy(lppFieldlue[nFilterCount],filterValue,MAX_FILTERFIELD_LEN);
		nFilterCount++;
	}

}FILTER,*LP_FILTER;

//先天订阅者的结构体
typedef struct tagBornSubcribe
{
	uint16 m_uTopicNo; //主题编号
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
外面遍历的步骤必须是：
First()
while(!IsEOF())
{
	获取数据
	Next();
}                                                               
*/
//主题对应的发布者名字和序号的遍历接口，用于开机恢复
struct IGlobalNoMap: public IKnown
{
	virtual int FUNCTION_CALL_MODE GetPublisherCount() = 0;//获取发布者个数
	virtual uint16 FUNCTION_CALL_MODE GetPublisherNo() = 0;//获取发布者序号
	virtual uint32 FUNCTION_CALL_MODE GetStartNo() = 0;//当前有效期内的最小序号
	virtual uint32 FUNCTION_CALL_MODE GetLastNo() = 0;//当前发布者的最新序号
	virtual void FUNCTION_CALL_MODE SetRecomList(void* lpList) = 0;//设置重组队
	virtual void* FUNCTION_CALL_MODE GetRecommList() = 0;//获取重组队列指针

	virtual int FUNCTION_CALL_MODE IsEOF() = 0;
	virtual int FUNCTION_CALL_MODE Next() = 0;
	virtual int FUNCTION_CALL_MODE First() = 0;
};

//主题属性操作接口
struct ITopicAttribute: public IKnown
{
	//获取主题属性接口
	virtual uint16 FUNCTION_CALL_MODE GetTopicNo() = 0;
	virtual char* FUNCTION_CALL_MODE GetTopicName() = 0;//主题名字，名字必须只能由字母和数字，以及符号"."组成，其中"."是父子主题分隔符，区分大小写
	virtual uint8 FUNCTION_CALL_MODE GetReliableLevel() = 0;//可靠性等级,0是尽力而为，1尽力有序，2内存级，3文件级，4系统级
	virtual uint8 FUNCTION_CALL_MODE GetIssuePriority() = 0;//发布优先级,数字越大优先级越高，默认是6，取值范围6-13
	virtual uint32 FUNCTION_CALL_MODE GetMsgLifetime() = 0;//消息有效期，以分钟为单位，默认为0。只针对文件级以及以上的主题有效
	virtual uint8 FUNCTION_CALL_MODE GetStutas() = 0;// 主题状态,0是启用，1是禁用
	virtual uint8 FUNCTION_CALL_MODE GetTickStrategy() = 0;// 重名踢人策略,0表示不需要踢人，1表示踢之前登陆的，2表示踢后面登陆的
	virtual uint8 FUNCTION_CALL_MODE GetBusinessVerify() = 0;//是否需要业务校验，0不需要，1需要
	//20121212 xuxp 增加主题属性，表示是否是局部的主题，只有全局的主题，下级才需要复制给上级，默认是全局主题
	virtual uint8 FUNCTION_CALL_MODE GetLocalTopic() = 0;//是否是局部主题
	virtual char* FUNCTION_CALL_MODE GetFilterName(int index=0) = 0;//获取已定义的过滤字段名字，一共六个
	virtual int FUNCTION_CALL_MODE GetTopicCrc() = 0;//获取主题校验码

	virtual char* FUNCTION_CALL_MODE GetSubscribeStr() = 0;//订阅者操作列表，支持“*”，“?”
	virtual char* FUNCTION_CALL_MODE GetPublishStr() = 0;//发布者操作列表，支持“*”，“?”

	//设置主题属性接口，只有状态属性，订阅者操作串和发布者操作串可以动态修改。
	virtual int FUNCTION_CALL_MODE SetStutas(bool bStutas) = 0;//true表示主题可用，false表示主题禁用
	virtual int FUNCTION_CALL_MODE SetSubscribeStr(char* strSub) = 0;//设置订阅者操作串
	virtual int FUNCTION_CALL_MODE SetPublisherStr(char* strPub) = 0;//设置发布者操作串
	virtual int FUNCTION_CALL_MODE SetTopicCrc(int nTopicCrc) = 0;//设置校验和，只用于下级消息中心

	//判断是否存在这个过滤字段
	virtual int FUNCTION_CALL_MODE FindFilterName(char* filedName) = 0;

	//20140825 majc 增加获取发布类型的接口
	virtual int FUNCTION_CALL_MODE GetIssueType() = 0;
};


///插件接口定义
struct IMCGD: public IKnown
{

	/**
	* 初始化全局数据模块，先初始化这个接口，后面接口才可以调用
	* @param lpTopicList 主题详细属性
	* @return 返回0表示成功，否则表示失败，通过调用GetErrorMsg可以获取详细错误信息
	* 解包器包含的字段名如下：
	* TopicName ReliableLevel IssuePriority MsgLifetime Stutas TickStrategy BusinessVerify Local FilterField1 FilterField2 
	*	FilterField3 FilterField4 FilterField5 FilterField6 SubscribeStr PublishStr
	* 没有的字段就赋值为""
	*/
	virtual int FUNCTION_CALL_MODE InitGD(IF2UnPacker* lpTopicList) = 0;		

	///////////////////////////////////主题相关的接口///////////////////////////////////////
	/**
	* 获取指定编号的主题信息
	* @param topicNo 主题编号
	* @param topicName主题名字
	* @return 返回对应的主题信息，失败返回NULL
	*/
	virtual ITopicAttribute* FUNCTION_CALL_MODE GetTopicInfoByNo(int topicNo,char* topicName) = 0;

	/**
	* 根据编号获取主题名字
	* @param topicNo 主题编号
	* @return 返回对应的主题名字
	*/
	virtual char* FUNCTION_CALL_MODE GetTopicNameByNo(int topicNo) = 0;


	/**
	* 根据主题编号和发布者名字,到发布者的允许列表校验当前发布者是否可以发布这个主题
	* @param topicNo 主题编号
	* @param publishName 发布者名字
	* @return 返回true表示校验通过，false是检验失败
	*/
	virtual bool FUNCTION_CALL_MODE CheckPublishList(int topicNo,char* publishName) = 0;

	/**
	* 根据主题编号和订阅者名字,到订阅者的允许列表校验当前订阅者是否可以订阅这个主题
	* @param topicNo 主题编号
	* @param subscribeName 订阅者名字
	* @return 返回true表示校验通过，false是检验失败
	*/
	virtual bool FUNCTION_CALL_MODE CheckSubscribeList(int topicNo,char* subscribeName) = 0;

	/**
	* 根据编号获取主题可靠级别
	* @param topicNo 主题编号
	* @return 返回对应的主题可靠级别，就是上面定义几种，-1表示没有对应的主题编号
	*/
	virtual int FUNCTION_CALL_MODE GetTopicLevelByNo(int topicNo) = 0;

	/**
	* 根据编号获取踢人策略
	* @param topicNo 主题编号
	* @return 返回对应的踢人策略，-1表示没有对应的主题编号
	*/
	virtual int FUNCTION_CALL_MODE GetTickStrategyByNo(int topicNo) = 0;

	/**
	* 根据编号获取是否业务校验
	* @param topicNo 主题编号
	* @return 返回对应业务校验，-1表示没有对应的主题编号
	*/
	virtual int FUNCTION_CALL_MODE GetBusinessVerifyByNo(int topicNo) = 0;

	/**
	* 根据编号获取主题是否是局部的
	* @param topicNo 主题编号
	* @return 返回对应主题的局部属性,-1表示没有对应的主题编号
	*/
	virtual int FUNCTION_CALL_MODE GetTopicLocalByNo(int topicNo)= 0;

	/**
	* 根据名字获取主题编号
	* @param topicName 主题名字
	* @return 返回对应的主题编号
	*/
	virtual uint16 FUNCTION_CALL_MODE GetTopicNoByName(char*  topicName) = 0;

	//获取子主题的个数，方便调用时申请获取子主题编号的数组大小
	/**
	* 子主题个数获取
	* @param topicNo 主题编号
	* @return 成功返回子主题个数，0表示没有子主题,负数表示没有这个主题
	*/
	virtual int FUNCTION_CALL_MODE GetTopicChildCount(int topicNo) = 0;

	/**
	* 子主题列表获取
	* @param topicNo 主题编号
	* @param arrayCOunt 传出参数，返回子主题个数
	* @return 成功返回对应子主题的数组指针，数组个数在传出参数中返回
	*/
	virtual uint16* FUNCTION_CALL_MODE GetTopicChild(int topicNo,int* arrayCOunt) = 0;

	/**
	* 返回主题个数
	* @return 成功就返回主题个数，失败返回-1。
	*/
	virtual int FUNCTION_CALL_MODE GetTopicCount() = 0;

	/**
	* 根据下标返回主题属性，用于遍历，注意下标从0开始
	* @param index 主题编号
	* @return 成功就返回对应的主题属性，失败返回NULL。
	*/
	virtual ITopicAttribute* FUNCTION_CALL_MODE GetTopicInfoByindex(int index)=0;

	///////////////////////////////////主题相关的接口到此结束///////////////////////////////////////

	///////////////////////////////////先天订阅相关的接口///////////////////////////////////////
	/**
	* 初始化增加先天订阅者，这里支持批量增加,运行期只能根据订阅者名字来添加，这个函数不可以调用
	* @param lpUnPacker 所有的先天订阅者信息
	* @return 成功返回0，失败返回负数
	* 解包器打包器字段有：订阅者名字（SubscribeName） 主题名字（TopicName），以及
	* 主题的过滤条件FilterField1 FilterField2 FilterField3 FilterField4 FilterField5 FilterField6
	* 过滤条件没有就取空
	*/
	virtual int FUNCTION_CALL_MODE InitBornTopic(IF2UnPacker* lpUnPacker) = 0;
	

	/**
	* 先天订阅者获取
	* @param subName 订阅端的名字
	* @return 返回对应订阅者的先天订阅者信息，失败返回NULL，是一个链表，需要遍历获取多有先天订阅者，主题编号为0节点抛弃
	*/
	virtual LPBORN_SUBSCRIBE FUNCTION_CALL_MODE GetBornByName(char* subName) = 0;


	/**
	* 只能针对一个订阅者做先天订阅者删除操作
	* @param subName 订阅端的名字
	* @param lpUnPacker 先天订阅者对应的过滤条件信息，结构如同上面的返回值
	* @return 成功返回0.失败返回负数
	* 解包器打包器字段有：主题名字（topicName），以及主题的过滤条件（主题属性中的过字段名字）
	*/
	virtual int FUNCTION_CALL_MODE DeleteBornTopicByName(char* subName,IF2UnPacker* lpUnPacker) = 0;

	/**
	* 只能针对一个订阅者做先天订阅者增加操作
	* @param subName 订阅端的名字
	* @param lpUnPacker 先天订阅者对应的过滤条件信息，结构如同上面的返回值
	* @return 成功返回0.失败返回负数
	* 解包器打包器字段有：主题名字（topicName），以及主题的过滤条件（主题属性中的过字段名字）
	*/
	virtual int FUNCTION_CALL_MODE AddBornTopicByName(char* subName,IF2UnPacker* lpUnPacker) = 0;
	///////////////////////////////////先天订阅相关的接口到此结束///////////////////////////////////////

	///////////////////////////////////发布者相关的接口///////////////////////////////////////

	/**
	* 添加发布者编号信息
	* @param lpSenderName发布者的名字信息，包含业务名字和发送者信息
	* @return 成功就返回当前发布者的序号，失败就返回负数。
	*/
	virtual int FUNCTION_CALL_MODE AddPublishNo(const char* lpSenderName) = 0;


	/**
	* 获取指定名字的发布者编号
	* @param lpSenderName发布者的名字信息
	* @return 成功就返回当前发布者的序号，失败就返回负数。
	*/
	virtual int FUNCTION_CALL_MODE GetPublishNo(const char* lpSenderName) = 0;
	
	/**
	* 获取指定编号的发布者名字信息
	* @param publishNo 发布者的序号
	* @return 成功就返回对应的名字，失败返回NULL
	*/
	virtual char* FUNCTION_CALL_MODE GetPublishName(int publishNo) = 0;
	///////////////////////////////////发布者相关的接口到此结束///////////////////////////////////////

	///////////////////////////////////全局序号映射接口///////////////////////////////////////
	/**
	* 设置重组队列的队列指针
	* @param topicNo 主题编号
	* @param publishNo 发布者编号
	* @param lpList 重组队列的指针
	* @return 成功就返回0，其他返回表示失败。
	*/
	virtual int FUNCTION_CALL_MODE SetRecomList(int topicNo, int publishNo ,void* lpList) = 0;


	/**
	* 根据主题编号以及发布者编号获取对应的重组队列
	* @param topicNo 主题编号
	* @param publishNo 发布者编号
	* @return 成功就返回重组队列指针，失败返回NULL。
	*/
	virtual void* FUNCTION_CALL_MODE GetRecomList(int topicNo, int publishNo) = 0;


	/**
	* 根据主题获取当前所有的发布者和序号信息
	* @return 成功就返回对应的遍历接口，失败返回NULL。
	*/
	virtual IGlobalNoMap* FUNCTION_CALL_MODE GetGlobalNoMap(int topicNo) = 0;
	/**
	* 根据主题编号加锁，重组队列操作时需要
	* @param topicNo 主题编号
	*/
	virtual void FUNCTION_CALL_MODE LockRecomList(int topicNo) = 0;

	/**
	* 根据主题编号解锁，重组队列操作时需要
	* @param topicNo 主题编号
	*/
	virtual void FUNCTION_CALL_MODE UnLockRecomList(int topicNo) = 0;
	
	/**
	* 接收到的消息添加到全局序号
	* @param topicNo 主题编号
	* @param publishNo 发布者编号
	* @param msgNo 消息编号
	* @return 成功就返回当前消息的内部序号，失败就返回0
	*/
	virtual uint32 FUNCTION_CALL_MODE AddGlobalNo(int topicNo, int publishNo,uint32 msgNo) = 0;


	/**
	* 根据全局序号来获取对应的内部序号
	* @param topicNo 主题编号
	* @param publishNo 发布者编号
	* @param msgNo 消息编号
	* @return 成功就返回当前消息的内部序号，失败就返回0
	*/
	virtual uint32 FUNCTION_CALL_MODE GetInternalNo(int topicNo, int publishNo,uint32 msgNo) = 0;


	/**
	* 获取当前主题这个发布者，有效消息的起始序号
	* @param topicNo 主题编号
	* @param publishNo 发布者编号
	* @return 成功就返回当前有效的最小序号，失败就返回0
	*/
	virtual uint32 FUNCTION_CALL_MODE GetStartNo(int topicNo, int publishNo) = 0;

	/**
	* 获取全局序号
	* @param topicNo 主题编号
	* @param publishNo 发布者编号
	* @return 成功就返回当前最新的序号的下一个序号，失败就返回0
	*/
	virtual uint32 FUNCTION_CALL_MODE GetLastNo(int topicNo, int publishNo) = 0;

	/**
	* 获取主题对应的发布者个数
	* @param topicNo 主题编号
	* @return 成功就返回当前主题的发布者个数，失败就返回0
	*/
	virtual uint32 FUNCTION_CALL_MODE GetPubilshCount(int topicNo) = 0;


	/**
	* 获取最新的内部序号
	* @param topicNo 主题编号
	* @return 成功就返回当前最新的内部序号，失败就返回0
	*/
	virtual uint32 FUNCTION_CALL_MODE GetLastInternelNo(int topicNo) = 0;
	///////////////////////////////////全局序号映射接口到此结束///////////////////////////////////////

	///////////////////////////////////消息缓存的接口///////////////////////////////////////

	/**
	* 添加消息缓存
	* @param topicNo 主题编号
	* @param InternalNo 内部序号
	* @param lpMsg 具体的消息
	* @return 成功返回0，失败返回负数
	*/
	virtual int FUNCTION_CALL_MODE AddMessage(int topicNo, uint32 InternalNo,IESBMessage* lpMsg, int publishNo=0,uint32 uMsgId=0) = 0;


	/**
	* 开机补缺，接收来自组内节点同步过来的消息，需要根据消息的相对年龄来选择年龄箱
	* @param topicNo 主题编号
	* @param InternalNo 内部序号
	* @param lpMsg 具体的消息
	* @return 成功返回0，失败返回负数
	*/
	virtual int FUNCTION_CALL_MODE AddMessageForGroup(int topicNo, uint32 InternalNo,IESBMessage* lpMsg, int publishNo=0,uint32 uMsgId=0) = 0;


	/**
	* 根据内部序号获取消息，用于组播获取消息
	* @param topicNo 主题编号
	* @param InternalNo 内部序号
	* @param publishNo 发布者编号
	* @return 成功返回具体消息指针，失败返回NULL
	*/
	virtual IESBMessage* FUNCTION_CALL_MODE GetMessage(int topicNo, uint32 InternalNo) = 0;

	
	/**
	* 根据内部序号获取消息,用于会话层获取消息
	* @param topicNo 主题编号
	* @param InternalNo 内部序号
	* @return 成功返回一个封装的消息指针，外层使用的时候需要再次封装
	*/
	virtual IMCMemCachedMsg* FUNCTION_CALL_MODE GetMsgForSession(int topicNo, uint32 InternalNo) = 0;
	
	///////////////////////////////////消息缓存的接口到此结束///////////////////////////////////////

	///////////////////////////////////过滤索引的接口///////////////////////////////////////

	/**
	* 添加过滤索引
	* @param topicNo 主题编号
	* @param InternalNo 内部序号
	* @param lpFilter 过滤条件的结构形式
	* @return 成功返回0，其他失败
	*/
	virtual int FUNCTION_CALL_MODE AddFilterIndex(int topicNo,uint32 InternalNo, LP_FILTER lpFilter) = 0;


	/**
	* 根据内部序号起始值以及过滤条件获取消息的内部序号列表
	* @param topicNo 主题编号
	* @param sInternalNo 内部序号
	* @param eInternalNo 结束内部序号，如果传入0，就表示补到当前最新的。
	* @param lpFilter 过滤条件
	* @param InternalList 内部申请空间，如果返回0，外部需要调用下面的函数释放空间
	* @param nCount 符合过滤条件的个数，返回值是-2以及-3的时候，这个值表示当前内存里面有效期的最小序号，外部应该用这个序号作为起始的补缺序号
	* @return 成功返回符合条件的个数，负数表示失败，-1表示内部获取不对，-2是没有过滤条件，-3是自定义的过滤条件
	* 返回-2，-3的情况，都需要自己获取最新内部序号，根据内部序号一个个获取，然后比较过滤条件
	*/
	virtual int FUNCTION_CALL_MODE GetInternalList(int topicNo,uint32 sInternalNo, uint32 eInternalNo, LP_FILTER lpFilter,uint32** InternalList,int* nCount) = 0;

	/**
	* 释放上面函数返回的int数组空间
	* @param InternalList 上面函数返回的int数组
	*/
	virtual void FUNCTION_CALL_MODE ReleaseInternalList(uint32* InternalList) = 0;
	///////////////////////////////////过滤索引的接口到此结束///////////////////////////////////////


	///////////////////////////////////组内数据缓存接口///////////////////////////////////////
	/**
	* 添加消息到组播缓存里面
	* @param lpMsg 需要添加的消息
	* @return 成功返回0，其他表示失败
	*/
	virtual int FUNCTION_CALL_MODE AddMsgForGroup(IESBMessage* lpMsg) = 0;


	/**
	* 获取组播缓存里面对应的消息，用于组内补缺
	* @param uTopicNo 主题编号
	* @param cPublishName 发布者名字
	* @param msgId 消息序号
	* @return 成功返回对应消息，其他返回NULL
	*/
	virtual IESBMessage* FUNCTION_CALL_MODE GetMsgForGroup(uint16 uTopicNo,const char* cPublishName,uint32 msgId) = 0;

	///////////////////////////////////组内数据缓存接口到此结束///////////////////////////////////////

	
	virtual IMCMessagePtr*	FUNCTION_CALL_MODE AllocMCMessagePtr()=0;
	virtual IMCMemCachedMsg* FUNCTION_CALL_MODE AllocMCMemCachedMsg()=0;

	//20140228 xuxp 新增接口，满足主题来源于不同系统的需求
	virtual int FUNCTION_CALL_MODE AddTopic(IF2UnPacker* lpTopicUnpack) = 0;//添加主题，用于主题来自于不同系统
	//这个函数使用主题来自于多系统的时候，主题添加通过AddTopic完成，然后再调用这个函数初始化，和InitGD函数只能选择一个函数做初始化
	virtual int FUNCTION_CALL_MODE InitGDEx() = 0;
	virtual int FUNCTION_CALL_MODE AddBornTopic(IF2UnPacker* lpTopicUnpack) = 0;//添加先天订阅者，用于先天订阅来自于不同系统
	virtual int FUNCTION_CALL_MODE GetTopicFromSystem(int topicNo) = 0;//根据主题名字获取主力来自于哪个系统
	//20140314 xuxp 增加获取所有先天订阅信息的接口
	virtual int FUNCTION_CALL_MODE GetAllBornInfo(IF2Packer* lpBornPack) = 0;
};
END_FBASE2_MC_NAMESPACE
#endif
