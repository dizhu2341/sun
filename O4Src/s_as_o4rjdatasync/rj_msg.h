/* 
 * File:   rj_msg.h
 * Author: wangzh19004
 *
 * Created on 2017年3月17日, 下午3:13
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
  string m_szTopicName;   //主题名
  string m_szTableName;   // 表名
};

#endif	/* RJ_MSG_H */

