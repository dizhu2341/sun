#ifndef __STATUS_MONITOR_H__
#define __STATUS_MONITOR_H__


///ϵͳͷ�ļ�
#include <stdio.h>
#include <string.h>
#ifdef _WIN32
//#include <windows.h>
#else
#include <unistd.h>
#endif

///fbase2.0ͷ�ļ�
#include <Include/tag_def.h>
#include <Include/biz_comp_interface.h>
#include <Include/esb_message_factory_interface.h>

///EXPORTS����
#ifndef EXPORTS
#define EXPORTS __declspec(dllexport)
#endif

#endif      

