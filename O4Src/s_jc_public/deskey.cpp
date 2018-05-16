#include <stdlib.h>
#include <string.h>
#include "deskey.h"

static char GConstDesKey[48] = {
	13, 16, 10, 23,  30,  4,  2, 27, 14,  5, 20,  9,
	22, 18, 11,  3, 25,  7, 15,  6, 26, 19, 12,  1,
	40, 51, 30, 36, 46, 54, 29, 39, 50, 44, 32, 47,
	43, 48, 38, 55, 35, 52, 45, 41, 49, 35, 28, 31 };

/*这样写,KEY是动态运算出来的，增加一些安全性。*/
int GetDesKey(char * sGUID, char *sDesKey)
{
   if (strcmp(sGUID,"{342BEAE2-1190-4201-9374-B2671C862CEB}") == 0)
   {
      sDesKey[0] = GConstDesKey[3] - 3;
      sDesKey[1] = GConstDesKey[5] + 8;
      sDesKey[2] = GConstDesKey[12] + 10;
      sDesKey[3] = GConstDesKey[18] - 2;
      sDesKey[4] = GConstDesKey[7] + 6;
      sDesKey[5] = GConstDesKey[24] + 3;   
      sDesKey[6] = GConstDesKey[28] + 7;   
      sDesKey[7] = GConstDesKey[25] + 4;   
      sDesKey[8] = GConstDesKey[27] + 5;   
      sDesKey[9] = GConstDesKey[26] + 13;   
      sDesKey[10] = GConstDesKey[28] + 7;   
      sDesKey[11] = GConstDesKey[32] + 2;   
      sDesKey[12] = GConstDesKey[35] - 1;   
      sDesKey[13] = GConstDesKey[13] + 4; 
      sDesKey[14] = 0;
      return 0;
   }
   else
      return -1;
}

