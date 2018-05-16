/* 
 * File:   StockInfoModifySync.h
 * Author: sunhm15168
 * Description: 证券信息增量同步类
 * Created on 2016年3月14日, 上午9:29
 */

#ifndef STOCKINFOMODIFYSYNC_H
#define	STOCKINFOMODIFYSYNC_H

#include "DataSync.h"

// 一批次同步1W行
#define BATCH_ROWS 10000

// 同步处理类

class CStockInfoModifySync : public CDataSync
{
public:
    CStockInfoModifySync(IAS2Context * lpContext);
    ~CStockInfoModifySync();

protected:
    virtual bool ExpO3View2Temp(); // 从O32表导入数据到临时表
    virtual bool ExpTemp2Dst(); // 从临时表导入数据到目标表
    virtual bool AfterAction();

    bool SyncInterCodeToMDB();
    bool ModifyStockType();
};
#endif	/* STOCKINFOMODIFYSYNC_H */

