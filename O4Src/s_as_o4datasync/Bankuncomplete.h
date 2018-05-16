/* 
 * File:   Bankuncomplete.h
 * Author: wangzh19004
 *
 * Created on 2016年11月8日, 下午8:27
 */

#ifndef BANKUNCOMPLETE_H
#define	BANKUNCOMPLETE_H

#include "DataSync.h"

// 一批次同步1W行
#define BATCH_ROWS 10000

// 同步处理类

class CBankUncomplete : public CDataSync
{
public:
    CBankUncomplete(IAS2Context * lpContext);
    ~CBankUncomplete();

protected:
    virtual bool ExpO3View2Temp(); // 从O32表导入数据到临时表
    virtual bool ExpTemp2Dst(); // 从临时表导入数据到目标表
};

#endif	/* BANKUNCOMPLETE_H */

