#ifndef INTERESTRATE_H
#define INTERESTRATE_H

#include "DataSync.h"

// 一批次同步1W行
#define BATCH_ROWS 10000

// 同步处理类

class CInterestrateSync : public CDataSync
{
public:
    CInterestrateSync(IAS2Context * lpContext);
    ~CInterestrateSync();

protected:
    virtual bool ExpO3View2Temp(); // 从O32表导入数据到临时表
    virtual bool ExpTemp2Dst(); // 从临时表导入数据到目标表
};


#endif /* INTERESTRATE_H */
