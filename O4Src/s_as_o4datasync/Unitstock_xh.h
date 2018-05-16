/* 
 * File:   Unitstock_xh.h
 * Author: wangzh19004
 *
 * Created on 2016年11月7日, 上午10:20
 */

#ifndef UNITSTOCK_XH_H
#define	UNITSTOCK_XH_H

#include "DataSync.h"

// 一批次同步1W行
#define BATCH_ROWS 10000

// 同步处理类

class CUnitStockXh : public CDataSync
{
public:
    CUnitStockXh(IAS2Context * lpContext);
    ~CUnitStockXh();

protected:
    virtual bool ExpO3View2Temp(); // 从O32表导入数据到临时表
    virtual bool ExpTemp2Dst(); // 从临时表导入数据到目标表
};

#endif	/* UNITSTOCK_XH_H */

