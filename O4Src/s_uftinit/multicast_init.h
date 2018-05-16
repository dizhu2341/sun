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
#include <Include/tag_def.h>
#include <Include/biz_comp_interface.h>
#include <Include/esb_message_factory_interface.h>

///EXPORTS定义
#ifndef EXPORTS
#define EXPORTS __declspec(dllexport)
#endif

#endif      

