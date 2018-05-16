/* 
 * File:   Unitstock_cw_sync.h
 * Author: wangzh19004
 *
 * Created on 2016年11月7日, 下午4:17
 */

#ifndef UNITSTOCK_CW_SYNC_H
#define	UNITSTOCK_CW_SYNC_H

#include "DataSync.h"

// 一批次同步1W行
#define BATCH_ROWS 10000

// 同步处理类

class CUnitStockCwSync : public CDataSync
{
public:
    CUnitStockCwSync(IAS2Context * lpContext);
    ~CUnitStockCwSync();

protected:
    virtual bool ExpO3View2Temp(); // 从O32表导入数据到临时表
    virtual bool ExpTemp2Dst(); // 从临时表导入数据到目标表
};

#endif	/* UNITSTOCK_CW_SYNC_H */

