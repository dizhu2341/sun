#ifndef HSDESC_H
#define HSDESC_H

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "IncludeFm/hsencrypt.h"


extern "C" 
{

/*********************************
函数名称：hsEncryptExNew2
函数功能：加密
传入参数：
   1. keytype: 加密类型,0.自定义加密,直接按sInitKey进行加密,1.Tuxedo加密,2.数据库加密,3.操作员加密,4.其他加密
   2. Key: 密钥，支持0-15位长度。根据加密类型不同,传入值不同,加密类型:0.加密的key,1.空,2.空,3.
   3. s1: 密码，支持0-16位长度
传出参数：
   1. s2: 加密后的密文,长度32
返回值：
 0:  正常
 -1: 密钥或密码的长度越界
 -2: 其他错误
**************************************/
int hsEncryptExNew2(int keytype, const char *key, const char *s1, char *s2);

/*************************************
函数名称：hsDecryptExNew2
函数功能：加密
传入参数：
   1. keytype: 加密类型,0.自定义加密,直接按sInitKey进行加密,1.Tuxedo加密,2.数据库加密,3.操作员加密,4.其他加密
   2. Key: 密钥，支持0-15位长度。 根据加密类型不同,传入值不同,加密类型:0.加密的key,1.空,2.空,3.
   3. s1: 密文，32位长度
传出参数：
   1. s2: 解密后的明文，支持0-16位长度
返回值：
 0: 正常
 -1: 密钥或密码的长度越界
 -2: 其他错误
**************************************/
int hsDecryptExNew2(int keytype, const char *key, const char *s1, char *s2);


}

#endif
