/* 
 * File:   Unitstock_yhj.h
 * Author: wangzh19004
 *
 * Created on 2016年11月7日, 下午4:24
 */

#ifndef UNITSTOCK_YHJ_H
#define	UNITSTOCK_YHJ_H

#include "DataSync.h"

// 一批次同步1W行
#define BATCH_ROWS 10000

// 同步处理类

class CUnitStockYhj : public CDataSync
{
public:
    CUnitStockYhj(IAS2Context * lpContext);
    ~CUnitStockYhj();

protected:
    virtual bool ExpO3View2Temp(); // 从O32表导入数据到临时表
    virtual bool ExpTemp2Dst(); // 从临时表导入数据到目标表
};

#endif	/* UNITSTOCK_YHJ_H */

