/* 
 * File:   rj_msg.h
 * Author: wangzh19004
 *
 * Created on 2017��3��17��, ����3:13
 */

#ifndef RJ_MSG_H
#define	RJ_MSG_H

#include "hshead.h"
#include "s_as_jc_o4rjfunc.h"

#include <string>

using namespace std;

typedef enum REFRESH_TYPE
{
	REFRESH_TYPE_UPDATE = 0,
	REFRESH_TYPE_DELETE = 3
}RefreshType;

class CRjMsg
{
public:
    CRjMsg(IAS2Context *lpContext,
    			 string TopicName, 
    			 string TableName);
    ~CRjMsg();
	
	bool SyncRj();
	string GetTableName();
	IAS2Context *GetContext();
private:
	string GetProcName();
	string GetCurrUpdateTimeStamp();
	bool CallProcedure(string szProcName, IF2Packer* lpDelRecPack);
	bool PublishTopic(string szTimePrev, string szTimeAft, IF2Packer* lpDelRecPack);
	bool PublishDelMsg(IF2Packer* lpDelRecPack);
	bool PublishUpdateMsg(string szTimePrev, string szTimeAft);
	IConnection* GetO3DBConn();
	bool Publish(IAS2Context* lpContext, IF2Packer* lpPack);
	bool PublishRjMultiDataSetTopic(IF2Packer* lpDelRecPack, IF2Packer* lpDelRecPack1, string tableName);
	
private:
	IAS2Context* m_lpContext;
  string m_szTopicName;   //������
  string m_szTableName;   // ����
};

#endif	/* RJ_MSG_H */

