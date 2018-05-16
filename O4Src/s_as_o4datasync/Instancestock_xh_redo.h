#ifndef INSTANCESTOCK_XH_REDO_H
#define INSTANCESTOCK_XH_REDO_H

#include "DataSync.h"

// 一批次同步1W行
#define BATCH_ROWS 10000

// 同步处理类

class CInstancestockXhRedo : public CDataSync
{
public:
    CInstancestockXhRedo(IAS2Context * lpContext);
    ~CInstancestockXhRedo();

protected:
    virtual bool ExpO3View2Temp(); // 从O32表导入数据到临时表
    virtual bool ExpTemp2Dst(); // 从临时表导入数据到目标表
};


#endif /* INSTANCESTOCK_XH_REDO_H */
