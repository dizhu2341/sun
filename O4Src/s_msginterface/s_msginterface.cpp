#include "IncludeFm/s_msginterface.h"
#include "IncludeFm/s_liblogpublic.h"
#include <Include/mcapi_plugin_interface.h>
#include "IncludeFm/writedlog.h"

/************************************************************************/
/* 功能: 订阅主题， 返回值小于0，则表示订阅失败.                        */
/************************************************************************/
int FUNCTION_CALL_MODE SubscribeTopic(IAS2Context * lpContext, IF2UnPacker * lpInUnPacker)
{
	int ret = 0;
	char subInfo[4000] = {"订阅:"};
    const char* topicName = NULL;
    int isFromNow = 0;
    int isReplace = 0;
    const char* filterField1 = NULL;
    const char* filterValue1 = NULL;
    const char* filterField2 = NULL;
    const char* filterValue2 = NULL;
    const char* filterField3 = NULL;
    const char* filterValue3 = NULL;
    const char* filterValue4 = NULL;
    const char* filterField4 = NULL;
    const char* filterValue5 = NULL;
    const char* filterField5 = NULL;
    const char* filterValue6 = NULL;
    const char* filterField6 = NULL;
    const char* filterValue7 = NULL;
    const char* filterField7 = NULL;
    const char* filterValue8 = NULL;
    const char* filterField8 = NULL;
    const char* filterValue9 = NULL;
    const char* filterField9 = NULL;
    const char* filterValue10 = NULL;
    const char* filterField10 = NULL;
    const char* filterField11 = NULL;
    const char* filterValue11 = NULL;
    const char* filterField12 = NULL;
    const char* filterValue12 = NULL;
    const char* filterField13 = NULL;
    const char* filterValue13 = NULL;
    const char* filterField14 = NULL;
    const char* filterValue14 = NULL;
    const char* filterField15 = NULL;
    const char* filterValue15 = NULL;
    const char* filterField16 = NULL;
    const char* filterValue16 = NULL;

    if (NULL == lpContext)
    {
        DLOGERROR(lpContext,-1, "发布主题失败:传入上下文为空.");
        return -1;
	}
    
    //--------------------------------------
    // 获取主题和各个过滤字段信息
    if (-1 == lpInUnPacker->FindColIndex("topic_name"))
    {
        DLOGERROR(lpContext,-1, "订阅主题失败:未传入主题名.");
        return -1;
    }
    topicName = lpInUnPacker->GetStr("topic_name");
    isFromNow = lpInUnPacker->GetChar("is_from_now");
	isReplace = lpInUnPacker->GetChar("is_sub_replace");
    if (lpInUnPacker->FindColIndex("filter_field1") != -1)
    {
        filterField1 = lpInUnPacker->GetStr("filter_field1");
        filterValue1 = lpInUnPacker->GetStr("filter_value1");
    }
    if (lpInUnPacker->FindColIndex("filter_field2") != -1)
    {
        filterField2 = lpInUnPacker->GetStr("filter_field2");
        filterValue2 = lpInUnPacker->GetStr("filter_value2");
    }
    if (lpInUnPacker->FindColIndex("filter_field3") != -1)
    {
        filterField3 = lpInUnPacker->GetStr("filter_field3");
        filterValue3 = lpInUnPacker->GetStr("filter_value3");
    }
    if (lpInUnPacker->FindColIndex("filter_field4") != -1)
    {
        filterField4 = lpInUnPacker->GetStr("filter_field4");
        filterValue4 = lpInUnPacker->GetStr("filter_value4");
    }
    if (lpInUnPacker->FindColIndex("filter_field5") != -1)
    {
        filterField5 = lpInUnPacker->GetStr("filter_field5");
        filterValue5 = lpInUnPacker->GetStr("filter_value5");
    }
    if (lpInUnPacker->FindColIndex("filter_field6") != -1)
    {
        filterField6 = lpInUnPacker->GetStr("filter_field6");
        filterValue6 = lpInUnPacker->GetStr("filter_value6");
    }
    if (lpInUnPacker->FindColIndex("filter_field7") != -1)
    {
        filterField7 = lpInUnPacker->GetStr("filter_field7");
        filterValue7 = lpInUnPacker->GetStr("filter_value7");
    }
    if (lpInUnPacker->FindColIndex("filter_field8") != -1)
    {
        filterField8 = lpInUnPacker->GetStr("filter_field8");
        filterValue8 = lpInUnPacker->GetStr("filter_value8");
    }
    if (lpInUnPacker->FindColIndex("filter_field9") != -1)
    {
        filterField9 = lpInUnPacker->GetStr("filter_field9");
        filterValue9 = lpInUnPacker->GetStr("filter_value9");
    }
    if (lpInUnPacker->FindColIndex("filter_field10") != -1)
    {
        filterField10 = lpInUnPacker->GetStr("filter_field10");
        filterValue10 = lpInUnPacker->GetStr("filter_value10");
    }
    if (lpInUnPacker->FindColIndex("filter_field11") != -1)
    {
        filterField11 = lpInUnPacker->GetStr("filter_field11");
        filterValue11 = lpInUnPacker->GetStr("filter_value11");
    }
    if (lpInUnPacker->FindColIndex("filter_field12") != -1)
    {
        filterField12 = lpInUnPacker->GetStr("filter_field12");
        filterValue12 = lpInUnPacker->GetStr("filter_value12");
    }
    
    if (lpInUnPacker->FindColIndex("filter_field13") != -1)
    {
        filterField13 = lpInUnPacker->GetStr("filter_field13");
        filterValue13 = lpInUnPacker->GetStr("filter_value13");
    }
    
    if (lpInUnPacker->FindColIndex("filter_field14") != -1)
    {
        filterField14 = lpInUnPacker->GetStr("filter_field14");
        filterValue14 = lpInUnPacker->GetStr("filter_value14");
    }
    
    if (lpInUnPacker->FindColIndex("filter_field15") != -1)
    {
        filterField15 = lpInUnPacker->GetStr("filter_field15");
        filterValue15 = lpInUnPacker->GetStr("filter_value15");
    }
    if (lpInUnPacker->FindColIndex("filter_field16") != -1)
    {
        filterField16 = lpInUnPacker->GetStr("filter_field16");
        filterValue16 = lpInUnPacker->GetStr("filter_value16");
    }

	//设置订阅参数.
    IPluginSubscribeParamInterface* lpSubscribeParam = lpContext->NewSubscribeParam();
	lpSubscribeParam->SetTopicNamePlugin(topicName);
	sprintf(subInfo, "%s主题名[%s]", subInfo, topicName);
	lpSubscribeParam->SetFromNowPlugin(isFromNow == '1');
	sprintf(subInfo, "%s是否补缺[%c]", subInfo, isFromNow);
	lpSubscribeParam->SetReplacePlugin(isReplace == '1');
	sprintf(subInfo, "%s是否覆盖订阅[%c]", subInfo, isReplace);
	if (NULL != filterField1)
	{
		lpSubscribeParam->SetFilterPlugin(filterField1, filterValue1);
		sprintf(subInfo, "%sFilterField1[%s]FilterValue1[%s]", subInfo, filterField1, filterValue1);
	}
	if (NULL != filterField2)
	{
		lpSubscribeParam->SetFilterPlugin(filterField2, filterValue2);
		sprintf(subInfo, "%sFilterField2[%s]FilterValue2[%s]", subInfo, filterField2, filterValue2);
	}
	if (NULL != filterField3)
	{
		lpSubscribeParam->SetFilterPlugin(filterField3, filterValue3);
		sprintf(subInfo, "%sFilterField3[%s]FilterValue3[%s]", subInfo, filterField3, filterValue3);
	}
	if (NULL != filterField4)
	{
		lpSubscribeParam->SetFilterPlugin(filterField4, filterValue4);
		sprintf(subInfo, "%sFilterField4[%s]FilterValue4[%s]", subInfo, filterField4, filterValue4);
	}
	if (NULL != filterField5)
	{
		lpSubscribeParam->SetFilterPlugin(filterField5, filterValue5);
		sprintf(subInfo, "%sFilterField5[%s]FilterValue5[%s]", subInfo, filterField5, filterValue5);
	}
	if (NULL != filterField6)
	{
		lpSubscribeParam->SetFilterPlugin(filterField6, filterValue6);
		sprintf(subInfo, "%sFilterField6[%s]FilterValue6[%s]", subInfo, filterField6, filterValue6);
	}
	if (NULL != filterField7)
	{
		lpSubscribeParam->SetFilterPlugin(filterField7, filterValue7);
		sprintf(subInfo, "%sFilterField7[%s]FilterValue7[%s]", subInfo, filterField7, filterValue7);
	}
	if (NULL != filterField8)
	{
		lpSubscribeParam->SetFilterPlugin(filterField8, filterValue8);
		sprintf(subInfo, "%sFilterField8[%s]FilterValue8[%s]", subInfo, filterField8, filterValue8);
	}
	if (NULL != filterField9)
	{
		lpSubscribeParam->SetFilterPlugin(filterField9, filterValue9);
		sprintf(subInfo, "%sFilterField9[%s]FilterValue9[%s]", subInfo, filterField9, filterValue9);
	}
	if (NULL != filterField10)
	{
		lpSubscribeParam->SetFilterPlugin(filterField10, filterValue10);
		sprintf(subInfo, "%sFilterField10[%s]FilterValue10[%s]", subInfo, filterField10, filterValue10);
	}
	if (NULL != filterField11)
	{
		lpSubscribeParam->SetFilterPlugin(filterField11, filterValue11);
		sprintf(subInfo, "%sFilterField11[%s]FilterValue11[%s]", subInfo, filterField11, filterValue11);
	}
	if (NULL != filterField12)
	{
		lpSubscribeParam->SetFilterPlugin(filterField12, filterValue12);
		sprintf(subInfo, "%sFilterField12[%s]FilterValue12[%s]", subInfo, filterField12, filterValue12);
	}
	if (NULL != filterField13)
	{
		lpSubscribeParam->SetFilterPlugin(filterField13, filterValue13);
		sprintf(subInfo, "%sFilterField13[%s]FilterValue13[%s]", subInfo, filterField13, filterValue13);
	}
	if (NULL != filterField14)
	{
		lpSubscribeParam->SetFilterPlugin(filterField14, filterValue14);
		sprintf(subInfo, "%sFilterField14[%s]FilterValue14[%s]", subInfo, filterField14, filterValue14);
	}
	if (NULL != filterField15)
	{
		lpSubscribeParam->SetFilterPlugin(filterField15, filterValue15);
		sprintf(subInfo, "%sFilterField15[%s]FilterValue15[%s]", subInfo, filterField15, filterValue15);
	}
	if (NULL != filterField16)
	{
		lpSubscribeParam->SetFilterPlugin(filterField16, filterValue16);
		sprintf(subInfo, "%sFilterField16[%s]FilterValue16[%s]", subInfo, filterField16, filterValue16);
	}

	//订阅.
	int subIndex = lpContext->SubscribeTopic(lpSubscribeParam, 5000, NULL);
	if (subIndex > 0)
	{
		sprintf(subInfo, "%s订阅成功!", subInfo);
        DLOGEVENT(lpContext,subInfo<<"订阅成功!");
		ret = 0;
	}
	else
	{
        sprintf(subInfo, "%s订阅异常,错误号[%d]错误信息[%s]", subInfo, subIndex, lpContext->GetErrorMsg(subIndex));
        DLOGERROR(lpContext,-1, subInfo<<"订阅异常,错误号["<<subIndex<<"]错误信息["<<lpContext->GetErrorMsg(subIndex)<<"]");
		ret = -1;
	}
	
	if (lpSubscribeParam)
	{
		lpSubscribeParam->Release();
	}
	
	return ret; 
}


int FUNCTION_CALL_MODE PublishTopic(IAS2Context * lpContext, IF2UnPacker * lpInUnPacker)
{
    int ret = 0;
    char pubInfo[4000] = {"发布:"};
    int msgbodyLen = 0;
    void *p_msgbody = NULL;
    const char* topicName = NULL;
    const char* filterField1 = NULL;
    const char* filterValue1 = NULL;
    const char* filterField2 = NULL;
    const char* filterValue2 = NULL;
    const char* filterField3 = NULL;
    const char* filterValue3 = NULL;
    const char* filterValue4 = NULL;
    const char* filterField4 = NULL;
    const char* filterValue5 = NULL;
    const char* filterField5 = NULL;
    const char* filterValue6 = NULL;
    const char* filterField6 = NULL;
    const char* filterValue7 = NULL;
    const char* filterField7 = NULL;
    const char* filterValue8 = NULL;
    const char* filterField8 = NULL;
    const char* filterValue9 = NULL;
    const char* filterField9 = NULL;
    const char* filterValue10 = NULL;
    const char* filterField10 = NULL;
    const char* filterField11 = NULL;
    const char* filterValue11 = NULL;
    const char* filterField12 = NULL;
    const char* filterValue12 = NULL;
    const char* filterField13 = NULL;
    const char* filterValue13 = NULL;
    const char* filterField14 = NULL;
    const char* filterValue14 = NULL;
    const char* filterField15 = NULL;
    const char* filterValue15 = NULL;
    const char* filterField16 = NULL;
    const char* filterValue16 = NULL;

    //---------------------------------------
    // 申请打包器
    if (NULL == lpContext)
	{
        DLOGERROR(lpContext,-1, "发布主题失败:传入上下文为空.");
        return -1;
	}
	else
	{
	}

    //--------------------------------------
    // 获取主题和各个过滤字段信息
    if (-1 == lpInUnPacker->FindColIndex("topic_name"))
    {
        DLOGERROR(lpContext,-1, "发布主题失败:未传入主题名.");
        return -1;
    }
	else
	{
	}

    topicName = lpInUnPacker->GetStr("topic_name");

    if (lpInUnPacker->FindColIndex("filter_field1") != -1)
    {
        filterField1 = lpInUnPacker->GetStr("filter_field1");
        filterValue1 = lpInUnPacker->GetStr("filter_value1");
    }
	else
	{
	}

    if (lpInUnPacker->FindColIndex("filter_field2") != -1)
    {
        filterField2 = lpInUnPacker->GetStr("filter_field2");
        filterValue2 = lpInUnPacker->GetStr("filter_value2");
    }
	else
	{
	}

    if (lpInUnPacker->FindColIndex("filter_field3") != -1)
    {
        filterField3 = lpInUnPacker->GetStr("filter_field3");
        filterValue3 = lpInUnPacker->GetStr("filter_value3");
    }
	else
	{
	}

    if (lpInUnPacker->FindColIndex("filter_field4") != -1)
    {
        filterField4 = lpInUnPacker->GetStr("filter_field4");
        filterValue4 = lpInUnPacker->GetStr("filter_value4");
    }
	else
	{
	}

    if (lpInUnPacker->FindColIndex("filter_field5") != -1)
    {
        filterField5 = lpInUnPacker->GetStr("filter_field5");
        filterValue5 = lpInUnPacker->GetStr("filter_value5");
    }
	else
	{
	}

    if (lpInUnPacker->FindColIndex("filter_field6") != -1)
    {
        filterField6 = lpInUnPacker->GetStr("filter_field6");
        filterValue6 = lpInUnPacker->GetStr("filter_value6");
    }
	else
	{
	}

    if (lpInUnPacker->FindColIndex("filter_field7") != -1)
    {
        filterField7 = lpInUnPacker->GetStr("filter_field7");
        filterValue7 = lpInUnPacker->GetStr("filter_value7");
    }
	else
	{
	}

    if (lpInUnPacker->FindColIndex("filter_field8") != -1)
    {
        filterField8 = lpInUnPacker->GetStr("filter_field8");
        filterValue8 = lpInUnPacker->GetStr("filter_value8");
    }
	else
	{
	}

    if (lpInUnPacker->FindColIndex("filter_field9") != -1)
    {
        filterField9 = lpInUnPacker->GetStr("filter_field9");
        filterValue9 = lpInUnPacker->GetStr("filter_value9");
    }
	else
	{
	}

    if (lpInUnPacker->FindColIndex("filter_field10") != -1)
    {
        filterField10 = lpInUnPacker->GetStr("filter_field10");
        filterValue10 = lpInUnPacker->GetStr("filter_value10");
    }
	else
	{
	}

    if (lpInUnPacker->FindColIndex("filter_field11") != -1)
    {
        filterField11 = lpInUnPacker->GetStr("filter_field11");
        filterValue11 = lpInUnPacker->GetStr("filter_value11");
    }
	else
	{
	}

    if (lpInUnPacker->FindColIndex("filter_field12") != -1)
    {
        filterField12 = lpInUnPacker->GetStr("filter_field12");
        filterValue12 = lpInUnPacker->GetStr("filter_value12");
    }
	else
	{
	}

    if (lpInUnPacker->FindColIndex("filter_field13") != -1)
    {
        filterField13 = lpInUnPacker->GetStr("filter_field13");
        filterValue13 = lpInUnPacker->GetStr("filter_value13");
    }
	else
	{
	}

    if (lpInUnPacker->FindColIndex("filter_field14") != -1)
    {
        filterField14 = lpInUnPacker->GetStr("filter_field14");
        filterValue14 = lpInUnPacker->GetStr("filter_value14");
    }
	else
	{
	}

    if (lpInUnPacker->FindColIndex("filter_field15") != -1)
    {
        filterField15 = lpInUnPacker->GetStr("filter_field15");
        filterValue15 = lpInUnPacker->GetStr("filter_value15");
    }
	else
	{
	}

    if (lpInUnPacker->FindColIndex("filter_field16") != -1)
    {
        filterField16 = lpInUnPacker->GetStr("filter_field16");
        filterValue16 = lpInUnPacker->GetStr("filter_value16");
    }
	else
	{
	}
	
    p_msgbody = lpInUnPacker->GetRaw("msg_body", &msgbodyLen);
	sprintf(pubInfo, "发布:topicName[%s]", topicName);
	IPluginFilterInterface* lpFilterInter = lpContext->NewFilter();
	if (NULL != filterField1)
    {
        lpFilterInter->SetFilterPlugin(filterField1, filterValue1);
        sprintf(pubInfo, "%sfield1[%s]value1[%s]",pubInfo,filterField1, filterValue1);
    }
	else
	{
	}
	
    if (NULL != filterField2)
    {
        lpFilterInter->SetFilterPlugin(filterField2, filterValue2);
        sprintf(pubInfo, "%sfield2[%s]value2[%s]",pubInfo,filterField2, filterValue2);
    }
	else
	{
	}
	
    if (NULL != filterField3)
    {
        lpFilterInter->SetFilterPlugin(filterField3, filterValue3);
        sprintf(pubInfo, "%sfield3[%s]value3[%s]",pubInfo,filterField3, filterValue3);
    }
	else
	{
	}
	
    if (NULL != filterField4)
    {
        lpFilterInter->SetFilterPlugin(filterField4, filterValue4);
        sprintf(pubInfo, "%sfield4[%s]value4[%s]",pubInfo,filterField4, filterValue4);
    }
	else
	{
	}
	
    if (NULL != filterField5)
    {
        lpFilterInter->SetFilterPlugin(filterField5, filterValue5);
        sprintf(pubInfo, "%sfield5[%s]value5[%s]",pubInfo,filterField5, filterValue5);
    }
	else
	{
	}
	
    if (NULL != filterField6)
    {
        lpFilterInter->SetFilterPlugin(filterField6, filterValue6);
        sprintf(pubInfo, "%sfield6[%s]value6[%s]",pubInfo,filterField6, filterValue6);
    }
	else
	{
	}
	
    if (NULL != filterField7)
    {
        lpFilterInter->SetFilterPlugin(filterField7, filterValue7);
        sprintf(pubInfo, "%sfield7[%s]value7[%s]",pubInfo,filterField7, filterValue7);
    }
	else
	{
	}
	
    if (NULL != filterField8)
    {
        lpFilterInter->SetFilterPlugin(filterField8, filterValue8);
        sprintf(pubInfo, "%sfield8[%s]value8[%s]",pubInfo,filterField8, filterValue8);
    }
	else
	{
	}
	
    if (NULL != filterField9)
    {
        lpFilterInter->SetFilterPlugin(filterField9, filterValue9);
        sprintf(pubInfo, "%sfield9[%s]value9[%s]",pubInfo,filterField9, filterValue9);
    }
	else
	{
	}
	
    if (NULL != filterField10)
    {
        lpFilterInter->SetFilterPlugin(filterField10, filterValue10);
        sprintf(pubInfo, "%sfield10[%s]value10[%s]",pubInfo,filterField10, filterValue10);
    }
	else
	{
	}
	
    if (NULL != filterField11)
    {
        lpFilterInter->SetFilterPlugin(filterField11, filterValue11);
        sprintf(pubInfo, "%sfield11[%s]value11[%s]",pubInfo,filterField11, filterValue11);
    }
	else
	{
	}
	
    if (NULL != filterField12)
    {
        lpFilterInter->SetFilterPlugin(filterField12, filterValue12);
        sprintf(pubInfo, "%sfield12[%s]value12[%s]",pubInfo,filterField12, filterValue12);
    }
	else
	{
	}
	
    if (NULL != filterField13)
    {
        lpFilterInter->SetFilterPlugin(filterField13, filterValue13);
        sprintf(pubInfo, "%sfield13[%s]value13[%s]",pubInfo,filterField13, filterValue13);
    }
	else
	{
	}
	
    if (NULL != filterField14)
    {
        lpFilterInter->SetFilterPlugin(filterField14, filterValue14);
        sprintf(pubInfo, "%sfield14[%s]value14[%s]",pubInfo,filterField14, filterValue14);
    }
	else
	{
	}
	
    if (NULL != filterField15)
    {
        lpFilterInter->SetFilterPlugin(filterField15, filterValue15);
        sprintf(pubInfo, "%sfield15[%s]value15[%s]",pubInfo,filterField15, filterValue15);
    }
	else
	{
	}
	
    if (NULL != filterField16)
    {
        lpFilterInter->SetFilterPlugin(filterField16, filterValue16);
        sprintf(pubInfo, "%sfield16[%s]value16[%s]",pubInfo,filterField16, filterValue16);
    }
	else
	{
	}
	
    DLOGEVENT(lpContext,pubInfo<<"开始发布.");
	ret = lpContext->PubMsg((char *)topicName, lpFilterInter, p_msgbody, msgbodyLen, 5000);
	
    if (ret == 0)
    {
       DLOGEVENT(lpContext,pubInfo<<"发布成功.");
    }
    else
    {
       DLOGERROR(lpContext,ret, pubInfo<<"发布异常,错误号["<<ret<<"]错误信息["<<lpContext->GetErrorMsg(ret)<<"]");
    }
	
	if (lpFilterInter)		/*lint !e539*/
	{
		lpFilterInter->Release();
	}
    return ret;
}

int FUNCTION_CALL_MODE CancelSubscribe(IAS2Context *lpContext, IF2UnPacker * lpInUnPacker)
{
	int ret = 0;
    char cancelInfo[4000] = {"取消订阅:"};
    const char* topicName = NULL;
    const char* filterField1 = NULL;
    const char* filterValue1 = NULL;
    const char* filterField2 = NULL;
    const char* filterValue2 = NULL;
    const char* filterField3 = NULL;
    const char* filterValue3 = NULL;
    const char* filterValue4 = NULL;
    const char* filterField4 = NULL;
    const char* filterValue5 = NULL;
    const char* filterField5 = NULL;
    const char* filterValue6 = NULL;
    const char* filterField6 = NULL;
    const char* filterValue7 = NULL;
    const char* filterField7 = NULL;
    const char* filterValue8 = NULL;
    const char* filterField8 = NULL;
    const char* filterValue9 = NULL;
    const char* filterField9 = NULL;
    const char* filterValue10 = NULL;
    const char* filterField10 = NULL;
    const char* filterField11 = NULL;
    const char* filterValue11 = NULL;
    const char* filterField12 = NULL;
    const char* filterValue12 = NULL;
    const char* filterField13 = NULL;
    const char* filterValue13 = NULL;
    const char* filterField14 = NULL;
    const char* filterValue14 = NULL;
    const char* filterField15 = NULL;
    const char* filterValue15 = NULL;
    const char* filterField16 = NULL;
    const char* filterValue16 = NULL;
    
    if (NULL == lpContext)
    {
        DLOGERROR(lpContext,-1, "发布主题失败:传入上下文为空.");
        return -1;
	}
	else
	{
	}

    //--------------------------------------
    // 获取主题和各个过滤字段信息
    if (-1 == lpInUnPacker->FindColIndex("topic_name"))
    {
        DLOGERROR(lpContext,-1, "发布主题失败:未传入主题名.");
        return -1;
    }
	else
	{
	}

    topicName = lpInUnPacker->GetStr("topic_name");
    sprintf(cancelInfo, "退订:topicName[%s]", topicName);
    
    if (lpInUnPacker->FindColIndex("filter_field1") != -1)
    {
        filterField1 = lpInUnPacker->GetStr("filter_field1");
        filterValue1 = lpInUnPacker->GetStr("filter_value1");
    }
	else
	{
	}

    if (lpInUnPacker->FindColIndex("filter_field2") != -1)
    {
        filterField2 = lpInUnPacker->GetStr("filter_field2");
        filterValue2 = lpInUnPacker->GetStr("filter_value2");
    }
	else
	{
	}

    if (lpInUnPacker->FindColIndex("filter_field3") != -1)
    {
        filterField3 = lpInUnPacker->GetStr("filter_field3");
        filterValue3 = lpInUnPacker->GetStr("filter_value3");
    }
	else
	{
	}

    if (lpInUnPacker->FindColIndex("filter_field4") != -1)
    {
        filterField4 = lpInUnPacker->GetStr("filter_field4");
        filterValue4 = lpInUnPacker->GetStr("filter_value4");
    }
	else
	{
	}

    if (lpInUnPacker->FindColIndex("filter_field5") != -1)
    {
        filterField5 = lpInUnPacker->GetStr("filter_field5");
        filterValue5 = lpInUnPacker->GetStr("filter_value5");
    }
	else
	{
	}

    if (lpInUnPacker->FindColIndex("filter_field6") != -1)
    {
        filterField6 = lpInUnPacker->GetStr("filter_field6");
        filterValue6 = lpInUnPacker->GetStr("filter_value6");
    }
	else
	{
	}

    if (lpInUnPacker->FindColIndex("filter_field7") != -1)
    {
        filterField7 = lpInUnPacker->GetStr("filter_field7");
        filterValue7 = lpInUnPacker->GetStr("filter_value7");
    }
	else
	{
	}

    if (lpInUnPacker->FindColIndex("filter_field8") != -1)
    {
        filterField8 = lpInUnPacker->GetStr("filter_field8");
        filterValue8 = lpInUnPacker->GetStr("filter_value8");
    }
	else
	{
	}

    if (lpInUnPacker->FindColIndex("filter_field9") != -1)
    {
        filterField9 = lpInUnPacker->GetStr("filter_field9");
        filterValue9 = lpInUnPacker->GetStr("filter_value9");
    }
	else
	{
	}

    if (lpInUnPacker->FindColIndex("filter_field10") != -1)
    {
        filterField10 = lpInUnPacker->GetStr("filter_field10");
        filterValue10 = lpInUnPacker->GetStr("filter_value10");
    }
	else
	{
	}

    if (lpInUnPacker->FindColIndex("filter_field11") != -1)
    {
        filterField11 = lpInUnPacker->GetStr("filter_field11");
        filterValue11 = lpInUnPacker->GetStr("filter_value11");
    }
	else
	{
	}

    if (lpInUnPacker->FindColIndex("filter_field12") != -1)
    {
        filterField12 = lpInUnPacker->GetStr("filter_field12");
        filterValue12 = lpInUnPacker->GetStr("filter_value12");
    }
	else
	{
	}

    
    if (lpInUnPacker->FindColIndex("filter_field13") != -1)
    {
        filterField13 = lpInUnPacker->GetStr("filter_field13");
        filterValue13 = lpInUnPacker->GetStr("filter_value13");
    }
	else
	{
	}

    
    if (lpInUnPacker->FindColIndex("filter_field14") != -1)
    {
        filterField14 = lpInUnPacker->GetStr("filter_field14");
        filterValue14 = lpInUnPacker->GetStr("filter_value14");
    }
	else
	{
	}

    
    if (lpInUnPacker->FindColIndex("filter_field15") != -1)
    {
        filterField15 = lpInUnPacker->GetStr("filter_field15");
        filterValue15 = lpInUnPacker->GetStr("filter_value15");
    }
	else
	{
	}

    
    if (lpInUnPacker->FindColIndex("filter_field16") != -1)
    {
        filterField16 = lpInUnPacker->GetStr("filter_field16");
        filterValue16 = lpInUnPacker->GetStr("filter_value16");
    }
	else
	{
	}

	
    IPluginFilterInterface *lpFilter = lpContext->NewFilter();
	if (NULL != filterField1)
	{
		lpFilter->SetFilterPlugin(filterField1, filterValue1);
		sprintf(cancelInfo, "%sFilterField1[%s]FilterValue1[%s]", cancelInfo, filterField1, filterValue1);
	}
	else
	{
	}

	if (NULL != filterField2)
	{
		lpFilter->SetFilterPlugin(filterField2, filterValue2);
		sprintf(cancelInfo, "%sFilterField2[%s]FilterValue2[%s]", cancelInfo, filterField2, filterValue2);
	}
	else
	{
	}

	if (NULL != filterField3)
	{
		lpFilter->SetFilterPlugin(filterField3, filterValue3);
		sprintf(cancelInfo, "%sFilterField3[%s]FilterValue3[%s]", cancelInfo, filterField3, filterValue3);
	}
	else
	{
	}

	if (NULL != filterField4)
	{
		lpFilter->SetFilterPlugin(filterField4, filterValue4);
		sprintf(cancelInfo, "%sFilterField4[%s]FilterValue4[%s]", cancelInfo, filterField4, filterValue4);
	}
	else
	{
	}

	if (NULL != filterField5)
	{
		lpFilter->SetFilterPlugin(filterField5, filterValue5);
		sprintf(cancelInfo, "%sFilterField5[%s]FilterValue5[%s]", cancelInfo, filterField5, filterValue5);
	}
	else
	{
	}

	if (NULL != filterField6)
	{
		lpFilter->SetFilterPlugin(filterField6, filterValue6);
		sprintf(cancelInfo, "%sFilterField6[%s]FilterValue6[%s]", cancelInfo, filterField6, filterValue6);
	}
	else
	{
	}

	if (NULL != filterField7)
	{
		lpFilter->SetFilterPlugin(filterField7, filterValue7);
		sprintf(cancelInfo, "%sFilterField7[%s]FilterValue7[%s]", cancelInfo, filterField7, filterValue7);
	}
	else
	{
	}
	
	if (NULL != filterField8)
	{
		lpFilter->SetFilterPlugin(filterField8, filterValue8);
		sprintf(cancelInfo, "%sFilterField8[%s]FilterValue8[%s]", cancelInfo, filterField8, filterValue8);
	}
	else
	{
	}

	if (NULL != filterField9)
	{
		lpFilter->SetFilterPlugin(filterField9, filterValue9);
		sprintf(cancelInfo, "%sFilterField9[%s]FilterValue9[%s]", cancelInfo, filterField9, filterValue9);
	}
	else
	{
	}

	if (NULL != filterField10)
	{
		lpFilter->SetFilterPlugin(filterField10, filterValue10);
		sprintf(cancelInfo, "%sFilterField10[%s]FilterValue10[%s]", cancelInfo, filterField10, filterValue10);
	}
	else
	{
	}

	if (NULL != filterField11)
	{
		lpFilter->SetFilterPlugin(filterField11, filterValue11);
		sprintf(cancelInfo, "%sFilterField11[%s]FilterValue11[%s]", cancelInfo, filterField11, filterValue11);
	}
	else
	{
	}

	if (NULL != filterField12)
	{
		lpFilter->SetFilterPlugin(filterField12, filterValue12);
		sprintf(cancelInfo, "%sFilterField12[%s]FilterValue12[%s]", cancelInfo, filterField12, filterValue12);
	}
	else
	{
	}

	if (NULL != filterField13)
	{
		lpFilter->SetFilterPlugin(filterField13, filterValue13);
		sprintf(cancelInfo, "%sFilterField13[%s]FilterValue13[%s]", cancelInfo, filterField13, filterValue13);
	}
	else
	{
	}

	if (NULL != filterField14)
	{
		lpFilter->SetFilterPlugin(filterField14, filterValue14);
		sprintf(cancelInfo, "%sFilterField14[%s]FilterValue14[%s]", cancelInfo, filterField14, filterValue14);
	}
	else
	{
	}

	if (NULL != filterField15)
	{
		lpFilter->SetFilterPlugin(filterField15, filterValue15);
		sprintf(cancelInfo, "%sFilterField15[%s]FilterValue15[%s]", cancelInfo, filterField15, filterValue15);
	}
	else
	{
	}

	if (NULL != filterField16)
	{
		lpFilter->SetFilterPlugin(filterField16, filterValue16);
		sprintf(cancelInfo, "%sFilterField16[%s]FilterValue16[%s]", cancelInfo, filterField16, filterValue16);
	}
	else
	{
	}

	ret = lpContext->CancelSubscribeTopicEx((char *)topicName, lpFilter);

	if (0 == ret)
	{
        DLOGEVENT(lpContext,cancelInfo<<"退订成功");
	}
	else
	{
        DLOGERROR(lpContext,ret, cancelInfo<<"退订异常,错误号["<<ret<<"]错误信息["<<lpContext->GetErrorMsg(ret)<<"]");
	}
	
	if (lpFilter)
	{
		lpFilter->Release();
	}
	return ret;
}


