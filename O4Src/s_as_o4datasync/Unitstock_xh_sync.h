/* 
 * File:   UnitStock_xh_sync.h
 * Author: wangzh19004
 *
 * Created on 2016年11月7日, 下午2:34
 */

#ifndef UNITSTOCK_XH_SYNC_H
#define	UNITSTOCK_XH_SYNC_H

#include "DataSync.h"

// 一批次同步1W行
#define BATCH_ROWS 10000

// 同步处理类

class CUnitStockXhSync : public CDataSync
{
public:
    CUnitStockXhSync(IAS2Context * lpContext);
    ~CUnitStockXhSync();

protected:
    virtual bool ExpO3View2Temp(); // 从O32表导入数据到临时表
    virtual bool ExpTemp2Dst(); // 从临时表导入数据到目标表
};

#endif	/* UNITSTOCK_XH_SYNC_H */

