#include "o4data_convert.h"
#include "base64/base64.h"  //���ڰѶ�����ת�����ַ���
#include "sqlinit.h"
#include "global_func.h"

#pragma hdrstop

#ifdef __cplusplus
extern "C" {
#endif

//-------------------------------
// T2sdk�������
IF2Packer * FUNCTION_CALL_MODE NewPacker(int iVersion);
IF2UnPacker * FUNCTION_CALL_MODE NewUnPacker(void * lpBuffer, unsigned int iLen);
    
//-------------------------------------
// DBInit: ��ʼ��UFR���
bool UFTInit(int nDate); 
  
//--------------------------
// �����Ϲ�����
bool ExportHgConfig(int nInitDate);

//--------------------------
// ������������
bool ExportJcConfig(int nInitDate);
    
//---------------------------------
// �����ʼ��     
int tpsvrinit(int argc, char* argv[])
{   
	if (0 != ServerInitial())
	{
		hsWriteLog(0, "����ת����������ʧ��!");
		return -1 ;
	}
	else
		hsWriteLog(0, "����ת�����������ɹ�!");
	
	//��������, ����ʧ��Ҳ�÷�����������
	SubscribeTopic(); 

	return 0;
}

void tpsvrdone(void)
{
	hsWriteLog(0, "ֹͣ����ת������ɹ�!");
}

//-----------------------------------
// ȫ��ת������
void svc_multi_sync(TPSVCINFO *rqst)  
{
	//------------------------------
	//�������������ʼ��
	char *sRet=NULL; 
	int i = 0;
	char ConvertTables[150][TABLE_NAME_LENGTH] = { 0 };
	int ConvertTableCount = 0;
	int nInitDate;
	
	//----------------------------
	// ��ȡ��ʼ������
	GPackage=PInit();
	PSetText(GPackage,rqst->data);
	if (-1 == PGetItemInt(GPackage,"l_init_date", &nInitDate))
	{
		GErrorNo = -10;
		strcpy(GErrorMessage, "[svc_multi_sync]��������ݸ�ʽ����");
  }
	else
	{
		// ����ȫ�ִ���źʹ�����Ϣ
		GErrorNo=0;  
		strcpy(GErrorMessage, "");
	
		//------------------------------
		//�����ʼ��
		ServiceInitial();
		
		//---------------------------------
		// ��ȡ��Ҫת���ı���Ϣ
		ConvertTableCount = GetConvertTablesInfo(ConvertTables);
		
		//��ʽ����ת������
		
		//------------------------
		// Ԥ����
		if (ExecuteSQL("begin sp_o4sync_before; end;"))
		{
			for(i = 0; i<ConvertTableCount; ++i)
			{
				// ת������
				CDataConvert* lpDataConvert = new CDataConvert(ConvertTables[i], nInitDate);  //�ճ�
				lpDataConvert->Convert();
				delete lpDataConvert;
				
				// ������������򷵻�
				if (GErrorNo != 0 )
					break;
			}
		}
	}
	PFree(GPackage);
	
	//-----------------------------
	// �����Ϲ�����
	if (GErrorNo == 0)
		ExportHgConfig(nInitDate);
		
	//-----------------------------
	// ������������
	if (GErrorNo == 0)
		ExportJcConfig(nInitDate); 
		
	//-----------------------------
	// ��ʼ��uft�鲥ƽ̨
	if (GErrorNo == 0)
		UFTInit(nInitDate);

	//-------------------------------------
	// ������ز���
	GPackage=PInit();
	PAddItemInt(GPackage,"ErrCode",GErrorNo);  
	PAddItemString(GPackage,"ErrMsg",GErrorMessage);  

	//-------------------------------------
	// ���ط�����Ϣ
	sRet = tpalloc("STRING",NULL,10240);  
	memset(sRet,0,10240);  
	PGetText(GPackage,sRet,10240);  
	PFree(GPackage);  
	hsWriteLog(1, "����ת�����񴫳�����: %s", sRet);  
	tpreturn(TPSUCCESS,0,sRet,0,0);  
}  

//-----------------------------------
// ����ת������, 
void SingleConvert(const char* lpTableName, const char* lpAction, IF2UnPacker* unPacker)  
{	
	//PrintUnpacker(unPacker);
	//return;
	
	//------------------------------
	//�����ʼ��
	ServiceInitial();
	
	//------------------------------
	// ��ʼ��ȫ�ִ���źʹ�����Ϣ
	GErrorNo=0;  
	strcpy(GErrorMessage, "");
	
	//------------------------------
	// ����ת��
	CDataConvert* lpDataConvert = new CDataConvert(lpTableName, lpAction, unPacker);
	lpDataConvert->Convert();
	delete lpDataConvert;
	
	//-----------------------------
	// ��ӡת�����
	if (GErrorNo == 0)
		hsWriteLog(0, "�ռ��[%s]ˢ��ͬ���ɹ���", lpTableName);
	else
		hsWriteLog(0, "�ռ��[%s]ˢ��ͬ��ʧ�ܣ�ErrorCode[%d]ErrorInfo[%s]", lpTableName, GErrorNo, GErrorMessage);
}  

//-------------------------------------
// UFTInit: ��ʼ���鲥ƽ̨
bool UFTInit(int nDate)
{
	IF2Packer* packer = NewPacker(2);
	packer->BeginPack();
	packer->AddField("l_init_date");
	packer->AddInt(nDate);
	packer->EndPack();
	
	IF2UnPacker* unPacker = CallSvr(615011, packer);
	packer->FreeMem(packer->GetPackBuf());
	packer->Release();
	
	if (!unPacker)
		return false;
	
	unPacker->Release();
	
	if (GErrorNo == 0)
	{
		hsWriteLog(0, "UFT2.0��ʼ���ɹ���");
		strcpy(GErrorMessage, "UFT2.0��ʼ���ɹ�!");
		return true;
	}
	return false;
}

//--------------------------
// �����Ϲ�����
bool ExportHgConfig(int nInitDate)
{
	IF2Packer* packer = NewPacker(2);
	packer->BeginPack();
	packer->AddField("init_date", 'I');
	packer->AddField("file_path");
	packer->AddInt(nInitDate);
	packer->AddStr("InitData");
	packer->EndPack();
	
	IF2UnPacker* unPacker = CallSvr(410017, packer);
	
	packer->FreeMem(packer->GetPackBuf());
	packer->Release();
	
	if (!unPacker)
		return false;
	
	unPacker->Release();
	
	if (GErrorNo == 0)
	{
		hsWriteLog(0, "�����Ϲ����óɹ���");
		return true;
	}
	return false;
}

//--------------------------
// ������������
bool ExportJcConfig(int nInitDate)
{
	IF2Packer* packer = NewPacker(2);
	packer->BeginPack();
	packer->AddField("init_date", 'I');
	packer->AddInt(nInitDate);
	packer->EndPack();
	
	IF2UnPacker* unPacker = CallSvr(615002, packer);
	
	packer->FreeMem(packer->GetPackBuf());
	packer->Release();
	
	if (!unPacker)
		return false;
	
	unPacker->Release();
	
	if (GErrorNo == 0)
	{
		hsWriteLog(0, "�����������óɹ���");
		return true;
	}
	return false;
}

#ifdef __cplusplus
}
#endif 
												

