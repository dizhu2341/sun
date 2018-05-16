/* 
 * File:   Unitstock_qh_sync.h
 * Author: wangzh19004
 *
 * Created on 2016年11月7日, 下午3:44
 */

#ifndef UNITSTOCK_QH_SYNC_H
#define	UNITSTOCK_QH_SYNC_H

#include "DataSync.h"

// 一批次同步1W行
#define BATCH_ROWS 10000

// 同步处理类

class CUnitStockQhSync : public CDataSync
{
public:
    CUnitStockQhSync(IAS2Context * lpContext);
    ~CUnitStockQhSync();

protected:
    virtual bool ExpO3View2Temp(); // 从O32表导入数据到临时表
    virtual bool ExpTemp2Dst(); // 从临时表导入数据到目标表
};

#endif	/* UNITSTOCK_QH_SYNC_H */

