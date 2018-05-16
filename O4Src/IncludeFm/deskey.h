/************************************************************
 ***文件名: deskey.h
 ***编  写: 翁建平
 ***日  期: 2014-07-15
 ***说  明: 后台加密的KEY文件。
 ************************************************************/
//  修改版本    修改日期    修改单         申请人    负责人    修改内容     修改原因    备注 

#ifndef _HSDESKEY_H
#define _HSDESKEY_H

static char GDesKeyGUID[] = "{342BEAE2-1190-4201-9374-B2671C862CEB}";

/********************************************************
函数功能：获取后台密码加密使用的Key。
参数传入：sGUID: 获取Key的密码，调用函数时传入，写死，值为：{342BEAE2-1190-4201-9374-B2671C862CEB},
                 目的是为了不让这个函数被随便调用。
参数传出：sDesKey: 获取到的加密KEY，长度为15位的字符串。
函数返回：0-成功, -1 失败。
********************************************************/

extern "C"
{
    int GetDesKey(char * sGUID, char * sDesKey);
}

#endif
