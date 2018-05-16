#ifndef OPTIONCASH_H
#define OPTIONCASH_H

#include "DataSync.h"

// 一批次同步1W行
#define BATCH_ROWS 10000

// 同步处理类

class COptioncashSync : public CDataSync
{
public:
    COptioncashSync(IAS2Context * lpContext);
    ~COptioncashSync();

protected:
    virtual bool ExpO3View2Temp(); // 从O32表导入数据到临时表
    virtual bool ExpTemp2Dst(); // 从临时表导入数据到目标表
};


#endif /* OPTIONCASH_H */
