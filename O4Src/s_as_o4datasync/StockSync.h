/* 
 * File:   StockSync.h
 * Author: zhouyx11685
 * Description: 证券信息同步类
 * Created on 2015年11月9日, 下午4:10
 */

#ifndef STOCKSYNC_H
#define STOCKSYNC_H

#include "DataSync.h"

// 一批次同步1W行
#define BATCH_ROWS 10000

// 同步处理类

class CStockSync : public CDataSync
{
public:
    CStockSync(IAS2Context * lpContext);
    ~CStockSync();

protected:
    virtual bool ExpO3View2Temp(); // 从O32表导入数据到临时表
    virtual bool ExpTemp2Dst(); // 从临时表导入数据到目标表
    virtual bool AfterAction();

    bool SyncInterCodeToMDB();
    bool ModifyStockType();
    bool SyncStock2His();
};

#endif
