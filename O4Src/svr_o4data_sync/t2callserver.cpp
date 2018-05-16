#include "procMain.h"
#include "o4data_convert.h"
#include "t2callserver.h"
#include "global_func.h"

bool bIsSubSucc = false;   // �ж��Ƿ��ĳɹ�
void PrintSubList();       // ��ӡ�Ѷ��������б�
void PrintUnPack(IF2UnPacker* lpUnPack);   // ��ӡUnPacker��

//-------------------------------
// T2sdk�������
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
  // ��ȡ�����ֶ���Ϣ
  unPack = NewUnPacker(lpRecvData->lpFilterData,lpRecvData->iFilterDataLen);
  if(! unPack)
  {
    hsWriteLog(0, "���������ֶ��쳣!");
		return;
	}	
  unPack->AddRef();
  lpTableName = unPack->GetStr("keyword1");
  lpActionType = unPack->GetStr("keyword2");
  unPack->Release();
	
	//-----------------------------
	// ɾ���������򲻴���
	if ('2' == lpActionType[0])
		return;
	
	//----------------------------
	// ȫ��������������ݼ�
	if ('0' == lpActionType[0])
	{
		SingleConvert(lpTableName, lpActionType, NULL);
	}
	else
	{
	  unPack = NewUnPacker((void*)lpData,nLength);
	  if (!unPack)
	  {
		  hsWriteLog(0, "��ȡҵ��ͬ�����ݰ�ʧ��!");
		  return;
		}
    unPack->AddRef();
	
    pData = unPack->GetRaw("data", &nLen);
    if ((NULL == pData) || (nLen<=0))
    {
    	hsWriteLog(0, "��ȡdata���ݼ�����ָ��Ϊ��.");
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
// ���캯��
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
	hsWriteLog(0, "����AR��ַ: %s", m_szServers);
}

//----------------------------------
// ��������
CT2Manager::~CT2Manager()
{	
	//�ͷ�����
	if (NULL != m_lpConfig) 
	{
		try
		{
			m_lpConfig->Release(); 
		}catch(...) {}
	}
		
	//�ͷŶ��Ľӿ�
	if (NULL != m_lpSub)
	{
		try
		{
			m_lpSub->Release();
		}catch(...) {}
	}
	
	//�ͷ�ESB��
	if (NULL != m_lpESBMessage)
	{
		try
		{
			m_lpESBMessage->Release();
		}catch(...) {}
	}	
		
	//�ͷ�t2����
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
// ���ӽ���AR
bool CT2Manager::Connect()
{
	int ret = 0;
	
	// ��������Ѿ����ڣ� �򷵻�true
	if (NULL != m_lpConnection)
		return true;
	
	// ����t2����������Ϣ
	if (NULL == m_lpConfig)
	{	
		if (strcmp(m_szServers, "") == 0)
		{
			GErrorNo = -12;	
			strcpy(GErrorMessage, "��ȡ����AR��ַ������Ϣʧ�ܣ�");
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
	
  // ����CConnection����ָ��
	m_lpConnection = NewConnection(m_lpConfig);
	if (NULL == m_lpConnection)
		return false;
	m_lpConnection->AddRef();
	
	// �������Ӷ���
	ret = m_lpConnection->Create(m_lpCallBack);
	if (0 != ret)
	{
		m_lpConnection->Release();
		m_lpConnection = NULL;
		return false;
	}
	
	// ���ӷ�����
	ret = m_lpConnection->Connect(1000);
	if (ret != 0)  //��ʽ��ʼ���ӣ�����1000Ϊ��ʱ��������λ����
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
// ��������
bool CT2Manager::SubscribeTopic(char* lpSuberName,char* lpTopicName,bool bIsRebuild, bool bIsReplace,char* lpFilterName1, char* lpFilterValue1,char* lpFilterName2, char* lpFilterValue2,char* lpFilterName3, char* lpFilterValue3,char* lpFilterName4, char* lpFilterValue4,char* lpFilterName5, char* lpFilterValue5,char* lpFilterName6, char* lpFilterValue6)
{
	int iRet = 0;
	
	// ���ӷ�����, ����Ѿ����ӣ������л�ֱ�ӷ���
	if (!Connect())
	{
		hsWriteLog(0, "����arʧ�ܣ�");
		return false;
	}
	
	// �������Ľӿ�
	if (!NewSubscriber(lpSuberName))
	{
		hsWriteLog(0, "���ö��Ľӿ�ʧ��");
		return false;
	}
	
	// ���ö��Ĳ���			
	CSubscribeParamInterface* lpSubscribeParam = SetSubscribeParam(lpTopicName, bIsRebuild, bIsReplace,lpFilterName1, lpFilterValue1,lpFilterName2, lpFilterValue2,lpFilterName3, lpFilterValue3,lpFilterName4, lpFilterValue4,lpFilterName5, lpFilterValue5,lpFilterName6, lpFilterValue6);
	if (NULL == lpSubscribeParam)
	{
		hsWriteLog(0, "���ö��Ĳ���ʧ��");
		return false;
	}

	// ��������
	iRet = m_lpSub->SubscribeTopic(lpSubscribeParam,5000,NULL);
	if (iRet <= 0)
	{
		GErrorNo = -105;
		sprintf(GErrorMessage, "��������ʧ��: %s", m_lpConnection->GetErrorMsg(iRet));
		return false;
	}
	
	return true;
}

//------------------------------------------
// ���ö��Ĳ���
CSubscribeParamInterface* CT2Manager::SetSubscribeParam(char* lpTopicName,bool bIsRebuild, bool bIsReplace,char* lpFilterName1, char* lpFilterValue1,char* lpFilterName2, char* lpFilterValue2,char* lpFilterName3, char* lpFilterValue3, char* lpFilterName4, char* lpFilterValue4,char* lpFilterName5, char* lpFilterValue5,char* lpFilterName6, char* lpFilterValue6)
{
	CSubscribeParamInterface* lpSubscribeParam = NewSubscribeParam();
	if (NULL == lpSubscribeParam)
		return NULL;
	
	lpSubscribeParam->AddRef();
	lpSubscribeParam->SetTopicName(lpTopicName);   	//������
	lpSubscribeParam->SetFromNow(bIsRebuild);      	//�Ƿ�ȱ
	lpSubscribeParam->SetReplace(bIsReplace);      	//�Ƿ��滻
	lpSubscribeParam->SetSendInterval(0); 					//����Ƶ�ʼ��                                      
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
	 	sprintf(GErrorMessage, "�����������쳣:%s", m_lpConnection->GetMCLastError());
		return false;
	}
	m_lpSub->AddRef();
	return true;
}

bool CT2Manager::SetESBMessage(int nFuncNo, IF2Packer* packer)
{
	if (NULL == m_lpESBMessage)
	{
		m_lpESBMessage = NewESBMessage();  //����һ����Ϣ����
		if (NULL == m_lpESBMessage)
			return false;
	}
	m_lpESBMessage->AddRef();           //��Ϣ�������+1
	m_lpESBMessage->Prepare(REQUEST_PACKET, nFuncNo); //׼������������ܺ��ɲ�������
	m_lpESBMessage->GetItem(TAG_MESSAGE_BODY)->SetRawData(packer->GetPackBuf(), packer->GetPackLen());
	return true;
}

//------------------------------------------
// ��ӡ�Ѷ��ĵ�����
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
	void *lpData = NULL; //�洢ESB����
	int iLength = 0;
	
	//���ӷ�����
	if (!Connect())
	{
		hsWriteLog(1, "����arʧ�ܣ�");
		return NULL;
	}
	
	//����������ӣ������¶���
	if (!bIsSubSucc)
	{
		::SubscribeTopic();
	}
	

	// ��֯�����
	if (!SetESBMessage(nFuncNo, packer))
	{
		hsWriteLog(1, "����ESB�����쳣��");
		return NULL;
	}

	// ͬ�����������
	lpData = m_lpESBMessage->GetBuffer(&iLength);
	ret = m_lpConnection->Send(lpData, iLength, 0);
	if (ret < 0)
	{
		GErrorNo = ret;
        sprintf(GErrorMessage, "���͹��ܺ�[%d]�����ʧ��: ErrorNo[%d]ErrorMsg[%s]", nFuncNo, ret, m_lpConnection->GetErrorMsg(ret));
		return NULL;
	}
	
	//---------------------
	// ����Ӧ�����Ĭ�ϳ�ʱʱ��Ϊ1��
	ret = m_lpConnection->Receive(ret, &lpData, &iLength, 300000, (int)CConnectionInterface::JustRemoveHandle);
	if (0 != ret)
	{
		GErrorNo = ret;
		sprintf(GErrorMessage, "���չ��ܺ�[%d]Ӧ����쳣: %s", nFuncNo, m_lpConnection->GetErrorMsg(ret));
		return NULL;
	}
	m_lpESBMessage->SetBuffer(lpData, iLength);
	
	//--------------------------------
	// �ж�ESB���Ƿ��쳣
	ret = m_lpESBMessage->GetItem(TAG_ERROR_NO)->GetInt();
	if (0 != ret)
	{
		GErrorNo = ret;
		strcpy(GErrorMessage, m_lpESBMessage->GetItem(TAG_ERROR_INFO)->GetString());
		return NULL;
	}

	//-----------------------------
	// ����Ӧ���
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
// ��ӡUnpacker��
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
// ���÷���
IF2UnPacker* CallSvr(int nFuncNo, IF2Packer* packer)
{
	return CT2Manager::GetSingleInstance().CallSvr(nFuncNo, packer);
}

//---------------------------------------
// ��������
void SubscribeTopic()
{
	if( bIsSubSucc == true)
		return;
	
	if (!CT2Manager::GetSingleInstance().SubscribeTopic("o4converter", "1000", true, false, "keyword1", "", "keyword2", ""))
	{
		hsWriteLog(0, "���ⶩ��ʧ��[%d:%s]���ռ仺�潫�޷�ˢ�£��ɳ���������",  GErrorNo, GErrorMessage);
		bIsSubSucc = false;
		return;
	}
	hsWriteLog(0, "���ⶩ�ĳɹ���");
	bIsSubSucc = true;
}

//��ӡUnpacker
void PrintUnpacker(IF2UnPacker* lpUnPack)
{
	CT2Manager::GetSingleInstance().PrintUnPack(lpUnPack);
}

