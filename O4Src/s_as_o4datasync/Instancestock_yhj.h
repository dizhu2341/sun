/* 
 * File:   Instancestock_yhj.h
 * Author: wangzh19004
 *
 * Created on 2016年11月10日, 下午5:32
 */

#ifndef INSTANCESTOCK_YHJ_H
#define	INSTANCESTOCK_YHJ_H

#include "DataSync.h"

// 一批次同步1W行
#define BATCH_ROWS 10000

// 同步处理类

class CInstancestockYhj : public CDataSync
{
public:
    CInstancestockYhj(IAS2Context * lpContext);
    ~CInstancestockYhj();

protected:
    virtual bool ExpO3View2Temp(); // 从O32表导入数据到临时表
    virtual bool ExpTemp2Dst(); // 从临时表导入数据到目标表
};

#endif	/* INSTANCESTOCK_YHJ_H */

