#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <stdio.h>

#include "global_func.h"
#include "spub.h"

/*ini文件类定义*/
#define MAX_FILE_SIZE (1024*16)
#define LEFT_BRACE '['
#define RIGHT_BRACE ']'

int GErrorNo = 0;
char GErrorMessage[10240] = {0};
char GConfigFile[260] = {"hstrade.ini"};

//--------------------------------------
// 函数功能：从配置文件读取配置信息
// 返回：1:成功;0:没有配置信息;<0:出错
int hsGetConfig(const char *sKey, const char *sParam, char *sValue)
{
    FILE  *fpFile;
    char  sRow[MAX_LINE_LEN];
    char  stmpKey[256],sTmpParam[256];
    int bSectionFounded = false;
    int iFounded=0;
    char *pDest;

    sTmpParam[0]='\0';
    strcpy(sValue,"");
    if ((fpFile = fopen(GConfigFile, "r")) == NULL)
        return -2;

    memset(sRow, 0, MAX_LINE_LEN);
    sprintf(stmpKey, "[%s]", sKey);
    while (fgets(sRow, MAX_LINE_LEN, fpFile)) 
    {
        sRow[MAX_LINE_LEN - 1] = 0;
        Trim(sRow);
        if (sRow[0] == '#') 
            continue;

        if (! bSectionFounded) 
        {
            if (strcmp(stmpKey, sRow) == 0) 
            {
                bSectionFounded = true;
                continue;
            }
        } else 
        {
            if ((sRow[0] == '[') && (sRow[strlen(sRow)-1] == ']')) 
                break;
            pDest=strchr(sRow, '=');      
            if ( pDest == NULL) 
                continue;
            int length = pDest - sRow;
            char *sKey = (char *)malloc(length + 1);
            if (sKey)
            {
                sKey[length] = '\0';
                memcpy(sKey,sRow,length);
                strcpy(sTmpParam,sParam);
                strltou(sTmpParam);
                strltou(sKey);
                if (strcmp(sKey, sTmpParam) == 0) 
                {
                    strcpy(sValue, pDest+1);
                    iFounded = 1;        
                    free(sKey);
                    break;
                }
                free(sKey);
            }
        }
    }
    fclose(fpFile);
    return iFounded;
}
