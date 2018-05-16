#include "o4data_convert.h"
#include "base64/base64.h"  //用于把二进制转换成字符串
#include "sqlinit.h"
#include "global_func.h"

#pragma hdrstop

#ifdef __cplusplus
extern "C" {
#endif

//-------------------------------
// T2sdk输出函数
IF2Packer * FUNCTION_CALL_MODE NewPacker(int iVersion);
IF2UnPacker * FUNCTION_CALL_MODE NewUnPacker(void * lpBuffer, unsigned int iLen);
    
//-------------------------------------
// DBInit: 初始化UFR插件
bool UFTInit(int nDate); 
  
//--------------------------
// 导出合规设置
bool ExportHgConfig(int nInitDate);

//--------------------------
// 导出基础设置
bool ExportJcConfig(int nInitDate);
    
//---------------------------------
// 服务初始化     
int tpsvrinit(int argc, char* argv[])
{   
	if (0 != ServerInitial())
	{
		hsWriteLog(0, "数据转换服务启动失败!");
		return -1 ;
	}
	else
		hsWriteLog(0, "数据转换服务启动成功!");
	
	//订阅主题, 订阅失败也让服务正常运行
	SubscribeTopic(); 

	return 0;
}

void tpsvrdone(void)
{
	hsWriteLog(0, "停止数据转换服务成功!");
}

//-----------------------------------
// 全量转化服务
void svc_multi_sync(TPSVCINFO *rqst)  
{
	//------------------------------
	//函数变量定义初始化
	char *sRet=NULL; 
	int i = 0;
	char ConvertTables[150][TABLE_NAME_LENGTH] = { 0 };
	int ConvertTableCount = 0;
	int nInitDate;
	
	//----------------------------
	// 获取初始化日期
	GPackage=PInit();
	PSetText(GPackage,rqst->data);
	if (-1 == PGetItemInt(GPackage,"l_init_date", &nInitDate))
	{
		GErrorNo = -10;
		strcpy(GErrorMessage, "[svc_multi_sync]传入的数据格式不对");
  }
	else
	{
		// 重置全局错误号和错误信息
		GErrorNo=0;  
		strcpy(GErrorMessage, "");
	
		//------------------------------
		//服务初始化
		ServiceInitial();
		
		//---------------------------------
		// 获取需要转换的表信息
		ConvertTableCount = GetConvertTablesInfo(ConvertTables);
		
		//正式数据转换处理
		
		//------------------------
		// 预处理
		if (ExecuteSQL("begin sp_o4sync_before; end;"))
		{
			for(i = 0; i<ConvertTableCount; ++i)
			{
				// 转化数据
				CDataConvert* lpDataConvert = new CDataConvert(ConvertTables[i], nInitDate);  //日初
				lpDataConvert->Convert();
				delete lpDataConvert;
				
				// 如果发生错误，则返回
				if (GErrorNo != 0 )
					break;
			}
		}
	}
	PFree(GPackage);
	
	//-----------------------------
	// 导出合规设置
	if (GErrorNo == 0)
		ExportHgConfig(nInitDate);
		
	//-----------------------------
	// 导出基础设置
	if (GErrorNo == 0)
		ExportJcConfig(nInitDate); 
		
	//-----------------------------
	// 初始化uft组播平台
	if (GErrorNo == 0)
		UFTInit(nInitDate);

	//-------------------------------------
	// 打包返回参数
	GPackage=PInit();
	PAddItemInt(GPackage,"ErrCode",GErrorNo);  
	PAddItemString(GPackage,"ErrMsg",GErrorMessage);  

	//-------------------------------------
	// 返回服务信息
	sRet = tpalloc("STRING",NULL,10240);  
	memset(sRet,0,10240);  
	PGetText(GPackage,sRet,10240);  
	PFree(GPackage);  
	hsWriteLog(1, "批量转化服务传出参数: %s", sRet);  
	tpreturn(TPSUCCESS,0,sRet,0,0);  
}  

//-----------------------------------
// 单笔转化函数, 
void SingleConvert(const char* lpTableName, const char* lpAction, IF2UnPacker* unPacker)  
{	
	//PrintUnpacker(unPacker);
	//return;
	
	//------------------------------
	//服务初始化
	ServiceInitial();
	
	//------------------------------
	// 初始化全局错误号和错误信息
	GErrorNo=0;  
	strcpy(GErrorMessage, "");
	
	//------------------------------
	// 数据转换
	CDataConvert* lpDataConvert = new CDataConvert(lpTableName, lpAction, unPacker);
	lpDataConvert->Convert();
	delete lpDataConvert;
	
	//-----------------------------
	// 打印转换结果
	if (GErrorNo == 0)
		hsWriteLog(0, "日间表[%s]刷新同步成功！", lpTableName);
	else
		hsWriteLog(0, "日间表[%s]刷新同步失败！ErrorCode[%d]ErrorInfo[%s]", lpTableName, GErrorNo, GErrorMessage);
}  

//-------------------------------------
// UFTInit: 初始化组播平台
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
		hsWriteLog(0, "UFT2.0初始化成功！");
		strcpy(GErrorMessage, "UFT2.0初始化成功!");
		return true;
	}
	return false;
}

//--------------------------
// 导出合规设置
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
		hsWriteLog(0, "导出合规设置成功！");
		return true;
	}
	return false;
}

//--------------------------
// 导出基础设置
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
		hsWriteLog(0, "导出基础设置成功！");
		return true;
	}
	return false;
}

#ifdef __cplusplus
}
#endif 
												

