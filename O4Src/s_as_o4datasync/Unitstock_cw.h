/* 
 * File:   Unitstock_cw.h
 * Author: wangzh19004
 *
 * Created on 2016年11月7日, 下午3:59
 */

#ifndef UNITSTOCK_CW_H
#define	UNITSTOCK_CW_H

#include "DataSync.h"

// 一批次同步1W行
#define BATCH_ROWS 10000

// 同步处理类

class CUnitStockCw : public CDataSync
{
public:
    CUnitStockCw(IAS2Context * lpContext);
    ~CUnitStockCw();

protected:
    virtual bool ExpO3View2Temp(); // 从O32表导入数据到临时表
    virtual bool ExpTemp2Dst(); // 从临时表导入数据到目标表
};

#endif	/* UNITSTOCK_CW_H */

