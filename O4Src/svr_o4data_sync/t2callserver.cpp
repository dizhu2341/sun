#include "procMain.h"
#include "o4data_convert.h"
#include "t2callserver.h"
#include "global_func.h"

bool bIsSubSucc = false;   // 判断是否订阅成功
void PrintSubList();       // 打印已订阅主题列表
void PrintUnPack(IF2UnPacker* lpUnPack);   // 打印UnPacker包

//-------------------------------
// T2sdk输出函数
#ifdef __cplusplus
extern "C"
{
#endif
CConfigInterface * FUNCTION_CALL_MODE NewConfig();
CConnectionInterface * FUNCTION_CALL_MODE NewConnection(CConfigInterface *lpConfig);
IESBMessage *  FUNCTION_CALL_MODE NewESBMessage(int nCompressID = 1);
int FUNCTION_CALL_MODE GetVersionInfo();
IF2Packer * FUNCTION_CALL_MODE NewPacker(int iVersion);
IF2UnPacker * FUNCTION_CALL_MODE NewUnPacker(void * lpBuffer, unsigned int iLen);
CFilterInterface* FUNCTION_CALL_MODE NewFilter();
CSubscribeParamInterface* FUNCTION_CALL_MODE NewSubscribeParam();
#ifdef __cplusplus
};
#endif

void CSubCallback::OnReceived(CSubscribeInterface *lpSub,int subscribeIndex, const void *lpData, int nLength, LPSUBSCRIBE_RECVDATA lpRecvData)
{
  IF2UnPacker* unPack = NULL;
  IF2UnPacker* unPack1 = NULL;
  const char * lpTableName = NULL;
  const char * lpActionType = NULL;
  void * pData = NULL;
  int nLen = 0;

  //--------------------------------------
  // 获取过滤字段信息
  unPack = NewUnPacker(lpRecvData->lpFilterData,lpRecvData->iFilterDataLen);
  if(! unPack)
  {
    hsWriteLog(0, "解析过滤字段异常!");
		return;
	}	
  unPack->AddRef();
  lpTableName = unPack->GetStr("keyword1");
  lpActionType = unPack->GetStr("keyword2");
  unPack->Release();
	
	//-----------------------------
	// 删除操作，则不处理
	if ('2' == lpActionType[0])
		return;
	
	//----------------------------
	// 全表操作，则无数据集
	if ('0' == lpActionType[0])
	{
		SingleConvert(lpTableName, lpActionType, NULL);
	}
	else
	{
	  unPack = NewUnPacker((void*)lpData,nLength);
	  if (!unPack)
	  {
		  hsWriteLog(0, "获取业务同步数据包失败!");
		  return;
		}
    unPack->AddRef();
	
    pData = unPack->GetRaw("data", &nLen);
    if ((NULL == pData) || (nLen<=0))
    {
    	hsWriteLog(0, "获取data数据集错误，指针为空.");
    	return;
    }
    unPack1 = NewUnPacker((void*)pData, nLen);
    unPack1->AddRef();
    SingleConvert(lpTableName, lpActionType, unPack1);
    unPack1->Release();
    
    unPack->Release();
  }	
}

//--------------------------------------
// 构造函数
CT2Manager::CT2Manager()
{
	m_lpConfig = NULL;    
	m_lpConnection = NULL;
	m_lpSub = NULL;       
	m_lpESBMessage = NULL;
	m_lpCallBack = new CCallback(); 
	m_lpSubScriberCallback = new CSubCallback();
	strcpy(m_szServers, "");
	hsGetConfig("uftserver", "uft_t2_ip_port", m_szServers);
	hsWriteLog(0, "接入AR地址: %s", m_szServers);
}

//----------------------------------
// 析构函数
CT2Manager::~CT2Manager()
{	
	//释放配置
	if (NULL != m_lpConfig) 
	{
		try
		{
			m_lpConfig->Release(); 
		}catch(...) {}
	}
		
	//释放订阅接口
	if (NULL != m_lpSub)
	{
		try
		{
			m_lpSub->Release();
		}catch(...) {}
	}
	
	//释放ESB包
	if (NULL != m_lpESBMessage)
	{
		try
		{
			m_lpESBMessage->Release();
		}catch(...) {}
	}	
		
	//释放t2连接
	if (NULL != m_lpConnection)
	{
		try
		{
			m_lpConnection->Close();	
			m_lpConnection->Release();
		}catch(...) {}
	}
	
	if (m_lpCallBack)
		delete m_lpCallBack;
	
	if (m_lpSubScriberCallback)
		delete m_lpSubScriberCallback;
}

//-------------------------------------
// 连接接入AR
bool CT2Manager::Connect()
{
	int ret = 0;
	
	// 如果连接已经存在， 则返回true
	if (NULL != m_lpConnection)
		return true;
	
	// 设置t2连接配置信息
	if (NULL == m_lpConfig)
	{	
		if (strcmp(m_szServers, "") == 0)
		{
			GErrorNo = -12;	
			strcpy(GErrorMessage, "获取接入AR地址配置信息失败！");
			return false;
		}
		m_lpConfig = NewConfig();
	  m_lpConfig->AddRef();
	  m_lpConfig->SetString("t2sdk", "servers", m_szServers);
  	m_lpConfig->SetString("t2sdk", "license_no", "HS-HUNDSUN001-FBASE2-0000-4ePWxzscBVtY9ZKdgDKhSyk2");
  	m_lpConfig->SetString("t2sdk", "notify_port", "12345");
  	m_lpConfig->SetString("t2sdk", "send_queue_size", "10000");
  	m_lpConfig->SetString("t2sdk", "init_recv_buf_size", "102400");
  	m_lpConfig->SetString("t2sdk", "init_send_buf_size", "102400");
  	m_lpConfig->SetString("t2sdk", "sendcount", "10");
  	m_lpConfig->SetString("safe", "safe_level", "none");
  	m_lpConfig->SetString("safe", "cert_file", "");
  	m_lpConfig->SetString("safe", "cert_pwd", "");
	}
	
  // 创建CConnection对象指针
	m_lpConnection = NewConnection(m_lpConfig);
	if (NULL == m_lpConnection)
		return false;
	m_lpConnection->AddRef();
	
	// 创建连接对象
	ret = m_lpConnection->Create(m_lpCallBack);
	if (0 != ret)
	{
		m_lpConnection->Release();
		m_lpConnection = NULL;
		return false;
	}
	
	// 连接服务器
	ret = m_lpConnection->Connect(1000);
	if (ret != 0)  //正式开始连接，参数1000为超时参数，单位毫秒
	{
		GErrorNo = ret;
		strcpy(GErrorMessage, m_lpConnection->GetErrorMsg(ret));
		m_lpConnection->Release();
		m_lpConnection = NULL;
		return false;
	}
	return true;
}

//--------------------------------------
// 订阅主题
bool CT2Manager::SubscribeTopic(char* lpSuberName,char* lpTopicName,bool bIsRebuild, bool bIsReplace,char* lpFilterName1, char* lpFilterValue1,char* lpFilterName2, char* lpFilterValue2,char* lpFilterName3, char* lpFilterValue3,char* lpFilterName4, char* lpFilterValue4,char* lpFilterName5, char* lpFilterValue5,char* lpFilterName6, char* lpFilterValue6)
{
	int iRet = 0;
	
	// 连接服务器, 如果已经连接，函数中会直接返回
	if (!Connect())
	{
		hsWriteLog(0, "连接ar失败！");
		return false;
	}
	
	// 创建订阅接口
	if (!NewSubscriber(lpSuberName))
	{
		hsWriteLog(0, "设置订阅接口失败");
		return false;
	}
	
	// 设置订阅参数			
	CSubscribeParamInterface* lpSubscribeParam = SetSubscribeParam(lpTopicName, bIsRebuild, bIsReplace,lpFilterName1, lpFilterValue1,lpFilterName2, lpFilterValue2,lpFilterName3, lpFilterValue3,lpFilterName4, lpFilterValue4,lpFilterName5, lpFilterValue5,lpFilterName6, lpFilterValue6);
	if (NULL == lpSubscribeParam)
	{
		hsWriteLog(0, "设置订阅参数失败");
		return false;
	}

	// 订阅主题
	iRet = m_lpSub->SubscribeTopic(lpSubscribeParam,5000,NULL);
	if (iRet <= 0)
	{
		GErrorNo = -105;
		sprintf(GErrorMessage, "订阅主题失败: %s", m_lpConnection->GetErrorMsg(iRet));
		return false;
	}
	
	return true;
}

//------------------------------------------
// 设置订阅参数
CSubscribeParamInterface* CT2Manager::SetSubscribeParam(char* lpTopicName,bool bIsRebuild, bool bIsReplace,char* lpFilterName1, char* lpFilterValue1,char* lpFilterName2, char* lpFilterValue2,char* lpFilterName3, char* lpFilterValue3, char* lpFilterName4, char* lpFilterValue4,char* lpFilterName5, char* lpFilterValue5,char* lpFilterName6, char* lpFilterValue6)
{
	CSubscribeParamInterface* lpSubscribeParam = NewSubscribeParam();
	if (NULL == lpSubscribeParam)
		return NULL;
	
	lpSubscribeParam->AddRef();
	lpSubscribeParam->SetTopicName(lpTopicName);   	//主题名
	lpSubscribeParam->SetFromNow(bIsRebuild);      	//是否补缺
	lpSubscribeParam->SetReplace(bIsReplace);      	//是否替换
	lpSubscribeParam->SetSendInterval(0); 					//发送频率间隔                                      
  if (NULL != lpFilterName1)
  {
  	hsWriteLog(5, "FilterName1[%s]FilterValue1[%s]", lpFilterName1, lpFilterValue1);
  	lpSubscribeParam->SetFilter(lpFilterName1, lpFilterValue1);
  }
  if (NULL != lpFilterName2)
  {
  	hsWriteLog(5, "FilterName2[%s]FilterValue2[%s]", lpFilterName2, lpFilterValue2);
  	lpSubscribeParam->SetFilter(lpFilterName2, lpFilterValue2);
  }
  if (NULL != lpFilterName3)
  {
  	hsWriteLog(5, "FilterName3[%s]FilterValue3[%s]", lpFilterName3, lpFilterValue3);
  	lpSubscribeParam->SetFilter(lpFilterName3, lpFilterValue3);
  }
  if (NULL != lpFilterName4)
  {
  	hsWriteLog(5, "FilterName4[%s]FilterValue4[%s]", lpFilterName4, lpFilterValue4);
  	lpSubscribeParam->SetFilter(lpFilterName4, lpFilterValue4);
  }
  if (NULL != lpFilterName5)
  {
  	hsWriteLog(5, "FilterName5[%s]FilterValue5[%s]", lpFilterName5, lpFilterValue5);
  	lpSubscribeParam->SetFilter(lpFilterName5, lpFilterValue5);
  }
  if (NULL != lpFilterName6)
  {
  	hsWriteLog(5, "FilterName6[%s]FilterValue6[%s]", lpFilterName6, lpFilterValue6);
  	lpSubscribeParam->SetFilter(lpFilterName6, lpFilterValue6);
  }
  
  return lpSubscribeParam;
}

bool CT2Manager::NewSubscriber(const char* lpSuberName)
{
	if (NULL != m_lpSub)
		return true;
		
	if (m_lpConnection == NULL)
		return false;
		
	m_lpSub = m_lpConnection->NewSubscriber(m_lpSubScriberCallback,(char*)lpSuberName,5000);
	if (NULL == m_lpSub)
	{
		GErrorNo = -104;
	 	sprintf(GErrorMessage, "创建订阅者异常:%s", m_lpConnection->GetMCLastError());
		return false;
	}
	m_lpSub->AddRef();
	return true;
}

bool CT2Manager::SetESBMessage(int nFuncNo, IF2Packer* packer)
{
	if (NULL == m_lpESBMessage)
	{
		m_lpESBMessage = NewESBMessage();  //产生一个消息对象
		if (NULL == m_lpESBMessage)
			return false;
	}
	m_lpESBMessage->AddRef();           //消息对象个数+1
	m_lpESBMessage->Prepare(REQUEST_PACKET, nFuncNo); //准备请求包，功能号由参数传入
	m_lpESBMessage->GetItem(TAG_MESSAGE_BODY)->SetRawData(packer->GetPackBuf(), packer->GetPackLen());
	return true;
}

//------------------------------------------
// 打印已订阅的主题
void CT2Manager::PrintSubTopicInfo()
{	
	IF2Packer* lpPack = NewPacker(2);
	lpPack->AddRef();
	
	if((m_lpSub == NULL) || (lpPack == NULL))
		return;
		
	m_lpSub->GetSubcribeTopic(lpPack);
	PrintUnPack(lpPack->UnPack());
	lpPack->FreeMem(lpPack->GetPackBuf());
	lpPack->Release();
}

IF2UnPacker* CT2Manager::CallSvr(int nFuncNo, IF2Packer* packer)
{
	//hsWriteLog(0, "In CallSvr");
	
	int ret = 0;
	void *lpData = NULL; //存储ESB报文
	int iLength = 0;
	
	//连接服务器
	if (!Connect())
	{
		hsWriteLog(1, "连接ar失败！");
		return NULL;
	}
	
	//如果重新连接，则重新订阅
	if (!bIsSubSucc)
	{
		::SubscribeTopic();
	}
	

	// 组织请求包
	if (!SetESBMessage(nFuncNo, packer))
	{
		hsWriteLog(1, "设置ESB包体异常！");
		return NULL;
	}

	// 同步发送请求包
	lpData = m_lpESBMessage->GetBuffer(&iLength);
	ret = m_lpConnection->Send(lpData, iLength, 0);
	if (ret < 0)
	{
		GErrorNo = ret;
        sprintf(GErrorMessage, "发送功能号[%d]请求包失败: ErrorNo[%d]ErrorMsg[%s]", nFuncNo, ret, m_lpConnection->GetErrorMsg(ret));
		return NULL;
	}
	
	//---------------------
	// 接受应答包，默认超时时间为1秒
	ret = m_lpConnection->Receive(ret, &lpData, &iLength, 300000, (int)CConnectionInterface::JustRemoveHandle);
	if (0 != ret)
	{
		GErrorNo = ret;
		sprintf(GErrorMessage, "接收功能号[%d]应答包异常: %s", nFuncNo, m_lpConnection->GetErrorMsg(ret));
		return NULL;
	}
	m_lpESBMessage->SetBuffer(lpData, iLength);
	
	//--------------------------------
	// 判断ESB层是否异常
	ret = m_lpESBMessage->GetItem(TAG_ERROR_NO)->GetInt();
	if (0 != ret)
	{
		GErrorNo = ret;
		strcpy(GErrorMessage, m_lpESBMessage->GetItem(TAG_ERROR_INFO)->GetString());
		return NULL;
	}

	//-----------------------------
	// 解析应答包
	ret = m_lpESBMessage->GetItem(TAG_RETURN_CODE)->GetInt();
	lpData = (void*)m_lpESBMessage->GetItem(TAG_MESSAGE_BODY)->GetRawData(&iLength);
	IF2UnPacker* unPacker = NewUnPacker(lpData,iLength);
	if (NULL == unPacker)
		 return NULL;
	unPacker->AddRef();
	unPacker->Open(lpData, iLength);
	
	if (ret != 0)
	{
		//hsWriteLog(0, "Start Error Deal");
		//PrintUnPack(unPacker);
		GErrorNo = atoi(unPacker->GetStr("error_no"));
		strcpy(GErrorMessage, unPacker->GetStr("error_info"));
		unPacker->Release();
		//hsWriteLog(0, "End Error Deal");
		return NULL;
	}
	//hsWriteLog(0, "Out CallSvr");
	return unPacker;
}

//---------------------------------------------
// 打印Unpacker包
void CT2Manager::PrintUnPack(IF2UnPacker* lpUnPack)
{
	int i=0, row = 1;
	int nCount = lpUnPack->GetColCount();
	while (!lpUnPack->IsEOF())
	{
		for(i=0; i<nCount; ++i)
		{
			const char* lpName = lpUnPack->GetColName(i);
			char cType = lpUnPack->GetColType(i);
			const char* lpValue = lpUnPack->GetStrByIndex(i);
			hsWriteLog(0, "[%d]Name[%s]Type[%c]Value[%s]", row, lpName, cType, lpValue);
		}
		lpUnPack->Next();
		row++;
	}
}

//-----------------------------------
// 调用服务
IF2UnPacker* CallSvr(int nFuncNo, IF2Packer* packer)
{
	return CT2Manager::GetSingleInstance().CallSvr(nFuncNo, packer);
}

//---------------------------------------
// 发布主题
void SubscribeTopic()
{
	if( bIsSubSucc == true)
		return;
	
	if (!CT2Manager::GetSingleInstance().SubscribeTopic("o4converter", "1000", true, false, "keyword1", "", "keyword2", ""))
	{
		hsWriteLog(0, "主题订阅失败[%d:%s]，日间缓存将无法刷新，可尝试重启！",  GErrorNo, GErrorMessage);
		bIsSubSucc = false;
		return;
	}
	hsWriteLog(0, "主题订阅成功！");
	bIsSubSucc = true;
}

//打印Unpacker
void PrintUnpacker(IF2UnPacker* lpUnPack)
{
	CT2Manager::GetSingleInstance().PrintUnPack(lpUnPack);
}

