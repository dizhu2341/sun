#include <stdlib.h>
#include <string.h>
#include <memory.h>
#include <time.h>

#ifdef __cplusplus
extern "C"
{
#endif 
  #include "procMain.h"
  #include "t2callserver.h"
  
  void svc_multi_sync(TPSVCINFO *rqst);  
  void SingleConvert(const char* lpTableName, const char* lpAction, IF2UnPacker* unPacker);
 
#ifdef __cplusplus
}
#endif




