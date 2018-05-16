#ifndef FEESETHS_H
#define FEESETHS_H

#include "DataSync.h"

// 一批次同步1W行
#define BATCH_ROWS 10000

// 同步处理类

class CFeesethsSync : public CDataSync
{
public:
    CFeesethsSync(IAS2Context * lpContext);
    ~CFeesethsSync();

protected:
    virtual bool ExpO3View2Temp(); // 从O32表导入数据到临时表
    virtual bool ExpTemp2Dst(); // 从临时表导入数据到目标表
};


#endif /* FEESETHS_H */
