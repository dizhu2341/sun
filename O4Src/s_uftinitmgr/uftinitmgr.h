#ifndef __STATUS_MONITOR_H__
#define __STATUS_MONITOR_H__


///系统头文件
#include <stdio.h>
#include <string.h>
#ifdef _WIN32
//#include <windows.h>
#else
#include <unistd.h>
#endif

///fbase2.0头文件
#include <Include/pack_interface.h>
#include <Include/esb_message_interface.h>
#include <Include/tag_def.h>
#include <Include/f2core_interface.h>
#include <Include/biz_comp_interface.h>
#include <Include/comm_agent_interface.h>
#include <IncludeFm/s_jc_public.h>

///EXPORTS定义
#ifndef EXPORTS
#define EXPORTS __declspec(dllexport)
#endif

int FUNCTION_CALL_MODE F615010(IAS2Context * lpContext,IF2UnPacker * lpInUnPacker,IF2Packer * lpOutPacker);

#endif      

