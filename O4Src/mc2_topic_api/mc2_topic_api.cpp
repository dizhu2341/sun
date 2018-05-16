#include "mc2_topic_api.h"

int StrToIntSafe(const char *str, int defalut_value) {
	if (str)    
		return atoi(str);
	return defalut_value;
}

/* 错误信息打包输出 */
int SystemErrorPacker(IF2Packer * lpOutPacker,const char * sErrorPathInfo,int iErrorNo,const char * sErrorInfo)
{
	lpOutPacker->BeginPack();
	lpOutPacker->AddField("error_pathinfo",'S',500);
	lpOutPacker->AddField("error_no");
	lpOutPacker->AddField("error_info",'S',500);
	lpOutPacker->AddStr(sErrorPathInfo);
	lpOutPacker->AddInt(iErrorNo);
	lpOutPacker->AddStr(sErrorInfo);
	lpOutPacker->EndPack();
	return iErrorNo;
}

void PrintUnPacker(IF2UnPacker * lpUnpack)
{
	int i=0;
	int j=0;
	while ( !lpUnpack->IsEOF() )
	{
		for ( i=0; i<lpUnpack->GetColCount(); ++i)
		++j;
		lpUnpack->Next();
	}
}

void  AddNaturalTopicField(IF2Packer * lpPacker)
{
	lpPacker->AddField("TopicNo");
	lpPacker->AddField("SubscribeName");
	lpPacker->AddField("FilterField1");
	lpPacker->AddField("FilterField2");
	lpPacker->AddField("FilterField3");
	lpPacker->AddField("FilterField4");
	lpPacker->AddField("FilterField5");
	lpPacker->AddField("FilterField6");
	lpPacker->AddField("FilterField7");
	lpPacker->AddField("FilterField8");
	lpPacker->AddField("FilterField9");
	lpPacker->AddField("FilterField10");
	lpPacker->AddField("FilterField11");
	lpPacker->AddField("FilterField12");
	lpPacker->AddField("FilterField13");
	lpPacker->AddField("FilterField14");
	lpPacker->AddField("FilterField15");
	lpPacker->AddField("FilterField16");
}

void AddTopicPackField(IF2Packer *lpPacker)
{
	lpPacker->AddField("TopicName");
	lpPacker->AddField("ReliableLevel", 'I');
	lpPacker->AddField("IssuePriority", 'I');
	lpPacker->AddField("MsgLifetime", 'I');
	lpPacker->AddField("Stutas", 'I');
	lpPacker->AddField("TickStrategy", 'I');
	lpPacker->AddField("BusinessVerify", 'I');
	lpPacker->AddField("Local", 'I');
	lpPacker->AddField("FilterField1");
	lpPacker->AddField("FilterField2");
	lpPacker->AddField("FilterField3");
	lpPacker->AddField("FilterField4");
	lpPacker->AddField("FilterField5");
	lpPacker->AddField("FilterField6");
	lpPacker->AddField("FilterField7");
	lpPacker->AddField("FilterField8");
	lpPacker->AddField("FilterField9");
	lpPacker->AddField("FilterField10");
	lpPacker->AddField("FilterField11");
	lpPacker->AddField("FilterField12");
	lpPacker->AddField("FilterField13");
	lpPacker->AddField("FilterField14");
	lpPacker->AddField("FilterField15");
	lpPacker->AddField("FilterField16");
	lpPacker->AddField("SubscribeStr");
	lpPacker->AddField("PublishStr");
}


int FUNCTION_CALL_MODE GetTopicList(IAppContext* lpContext, IF2Packer * lpAnswer, int iTimeOut) 
{
	if ((!lpContext) || (!lpAnswer))  
		return -1;
		
	int funcid = 615501;
	int nTryCount=10;
	int nRet =0;
	
	IF2Packer* lpInPack = lpContext->GetF2PackSvr()->GetPacker(2);
	lpInPack->BeginPack();
	lpInPack->EndPack();
	
    IF2Packer* lpOutPack = lpContext->GetF2PackSvr()->GetPacker(2);
	IF2UnPacker* lpOutUnPack = NULL;
	
	if ((!lpInPack) || (!lpOutPack))  
		return -1;
	
	while (nTryCount-- >0)
	{
        lpOutPack->BeginPack();
        nRet = lpContext->CallSubService(funcid, lpInPack->UnPack(), lpOutPack, 10000);
        lpOutPack->EndPack();

        if (0 == nRet)
            break;
        sleep(2);	
	}
	lpOutUnPack = lpOutPack->UnPack();
		
	// 如果调用服务异常则返回
	if (0 != nRet)
	{
		printf("Call service[%d] error, please ensure jc_ar/bus_ar is alive, and check their routing between them is normal. %s\n", funcid, lpOutUnPack->GetStr("error_info"));
		lpInPack->FreeMem(lpInPack->GetPackBuf());
        lpInPack->Release();
        lpOutPack->FreeMem(lpOutPack->GetPackBuf());
        lpOutPack->Release();
		return -1;
	}
	
	// 打包主题列表给消息中心
	AddTopicPackField(lpAnswer);
	while (!lpOutUnPack->IsEOF())
	{
		lpAnswer->AddStr(lpOutUnPack->GetStr("topic_name"));
		lpAnswer->AddInt(StrToIntSafe(lpOutUnPack->GetStr("rely_level"), 0));
		lpAnswer->AddInt(StrToIntSafe(lpOutUnPack->GetStr("issue_priority"), 6));
		lpAnswer->AddInt(StrToIntSafe(lpOutUnPack->GetStr("life_time"), 24*60));
		lpAnswer->AddInt(StrToIntSafe(lpOutUnPack->GetStr("use_flag"), 24*60));
		lpAnswer->AddInt(StrToIntSafe(lpOutUnPack->GetStr("kick_strategy"), 0));
		lpAnswer->AddInt(StrToIntSafe(lpOutUnPack->GetStr("business_verify"), 1));
		lpAnswer->AddInt(StrToIntSafe(lpOutUnPack->GetStr("available_range"), 0));
		lpAnswer->AddStr(lpOutUnPack->GetStr("filter_field1"));
		lpAnswer->AddStr(lpOutUnPack->GetStr("filter_field2"));
		lpAnswer->AddStr(lpOutUnPack->GetStr("filter_field3"));
		lpAnswer->AddStr(lpOutUnPack->GetStr("filter_field4"));
		lpAnswer->AddStr(lpOutUnPack->GetStr("filter_field5"));
		lpAnswer->AddStr(lpOutUnPack->GetStr("filter_field6"));
		lpAnswer->AddStr(lpOutUnPack->GetStr("filter_field7"));
		lpAnswer->AddStr(lpOutUnPack->GetStr("filter_field8"));
		lpAnswer->AddStr(lpOutUnPack->GetStr("filter_field9"));
		lpAnswer->AddStr(lpOutUnPack->GetStr("filter_field10"));
		lpAnswer->AddStr(lpOutUnPack->GetStr("filter_field11"));
		lpAnswer->AddStr(lpOutUnPack->GetStr("filter_field12"));
		lpAnswer->AddStr(lpOutUnPack->GetStr("filter_field13"));
		lpAnswer->AddStr(lpOutUnPack->GetStr("filter_field14"));
		lpAnswer->AddStr(lpOutUnPack->GetStr("filter_field15"));
		lpAnswer->AddStr(lpOutUnPack->GetStr("filter_field16"));
		lpAnswer->AddStr(lpOutUnPack->GetStr("subscribe_str"));
		lpAnswer->AddStr(lpOutUnPack->GetStr("publish_str"));
		
		lpOutUnPack->Next();
	}
	
	printf("Get %d O4 Topics\n", lpOutUnPack->GetRowCount());
	
	lpInPack->FreeMem(lpInPack->GetPackBuf());
  lpInPack->Release();
  lpOutPack->FreeMem(lpOutPack->GetPackBuf());
  lpOutPack->Release();
	
	return 0;
}

// 先天订阅者
int FUNCTION_CALL_MODE GetDualSub(IAppContext* lpContext, IF2Packer * lpAnswer, int iTimeOut)
{
	IF2Packer* lpInPack = lpContext->GetF2PackSvr()->GetPacker(2);
  	IF2Packer* lpOutPack = lpContext->GetF2PackSvr()->GetPacker(2);
	int funcid = 615502;
	
	if ((!lpInPack) || (!lpOutPack))  
		return -1;
	
	lpInPack->BeginPack();
	lpInPack->EndPack();
	
	lpOutPack->BeginPack();
	int iRet = lpContext->CallSubService(funcid, lpInPack->UnPack(), lpOutPack, 10000);
	lpOutPack->EndPack();
		
	IF2UnPacker* lpOutUnPack = lpOutPack->UnPack();
	
	if (0 != iRet)
	{
		printf("Call Service[%d] Error: %s\n", funcid, lpOutUnPack->GetStr("error_info"));
		return -1;
	}
	
	AddNaturalTopicField(lpAnswer);
	while (!lpOutUnPack->IsEOF())
	{
		lpAnswer->AddStr(lpOutUnPack->GetStr("topic_no"));
		lpAnswer->AddStr(lpOutUnPack->GetStr("subscriber"));
		lpAnswer->AddStr(lpOutUnPack->GetStr("filter_value1"));
		lpAnswer->AddStr(lpOutUnPack->GetStr("filter_value2"));
		lpAnswer->AddStr(lpOutUnPack->GetStr("filter_value3"));
		lpAnswer->AddStr(lpOutUnPack->GetStr("filter_value4"));
		lpAnswer->AddStr(lpOutUnPack->GetStr("filter_value5"));
		lpAnswer->AddStr(lpOutUnPack->GetStr("filter_value6"));
		lpAnswer->AddStr(lpOutUnPack->GetStr("filter_value7"));
		lpAnswer->AddStr(lpOutUnPack->GetStr("filter_value8"));
		lpAnswer->AddStr(lpOutUnPack->GetStr("filter_value9"));
		lpAnswer->AddStr(lpOutUnPack->GetStr("filter_value9"));
		lpAnswer->AddStr(lpOutUnPack->GetStr("filter_value10"));
		lpAnswer->AddStr(lpOutUnPack->GetStr("filter_value11"));
		lpAnswer->AddStr(lpOutUnPack->GetStr("filter_value12"));
		lpAnswer->AddStr(lpOutUnPack->GetStr("filter_value13"));
		lpAnswer->AddStr(lpOutUnPack->GetStr("filter_value14"));
		lpAnswer->AddStr(lpOutUnPack->GetStr("filter_value15"));
		lpAnswer->AddStr(lpOutUnPack->GetStr("filter_value16"));
		
	          
		lpOutUnPack->Next();
	}
	printf("The Number of the O4 NaturalTopic is: %d\n", lpOutUnPack->GetRowCount());
	lpInPack->FreeMem(lpInPack->GetPackBuf());
	lpInPack->Release();
	lpOutPack->FreeMem(lpOutPack->GetPackBuf());
	lpOutPack->Release();
	return 0;
}

// 发布权限校验
int FUNCTION_CALL_MODE CheckPub(IAppContext* lpContext, char* lpTopic, char* lpPublisher, IF2Packer * lpAnswer) 
{
    if (!lpContext || !lpAnswer || !lpTopic || !lpPublisher)  return -1;

    IF2Packer *packer = lpContext->GetF2PackSvr()->GetPacker(0x21);
    if (!packer)    return -1;

    packer->BeginPack();
    packer->AddField("topic_name");
    packer->AddField("publisher");

    packer->AddStr(lpTopic);
    packer->AddStr(lpPublisher);
    packer->EndPack();
	
	//int iRet = lpContext->CallSubService(2002, packer->UnPack(), lpAnswer, 10000);
	lpAnswer = lpContext->GetF2PackSvr()->GetPacker(0x21);
	lpAnswer->BeginPack();
	int iRet = lpContext->CallSubService(615503, packer->UnPack(), lpAnswer, 10000);
	lpAnswer->EndPack();
	
    packer->FreeMem(packer->GetPackBuf());
    packer->Release();

    return iRet;
}

// 订阅权限校验
int FUNCTION_CALL_MODE CheckSub(IAppContext* lpContext, char* lpTopic, IF2UnPacker * lpSubReq, char* lpSub, IF2Packer * lpAnswer) {
    if (!lpContext || !lpAnswer || !lpTopic || !lpSubReq || !lpSub)  return -1;

    IF2Packer *packer = lpContext->GetF2PackSvr()->GetPacker(0x21);
    if (!packer)    return -1;

    packer->BeginPack();
    packer->AddField("topic_name");
    packer->AddField("subscriber");
    
    packer->AddStr(lpTopic);
    packer->AddStr(lpSub);
    packer->EndPack();

    //int iRet = lpContext->CallSubService(2003, packer->UnPack(), lpAnswer, 10000);
	lpAnswer = lpContext->GetF2PackSvr()->GetPacker(0x21);
	lpAnswer->BeginPack();
	int iRet = lpContext->CallSubService(615504, packer->UnPack(), lpAnswer, 10000);
	lpAnswer->EndPack();

    packer->FreeMem(packer->GetPackBuf());
    packer->Release();

    return iRet;
}
