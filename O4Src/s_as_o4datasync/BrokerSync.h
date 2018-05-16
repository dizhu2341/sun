#ifndef BROKER_H
#define BROKER_H

#include "DataSync.h"

// 一批次同步1W行
#define BATCH_ROWS 10000

// 同步处理类

class CBrokerSync : public CDataSync
{
public:
    CBrokerSync(IAS2Context * lpContext);
    ~CBrokerSync();

protected:
    virtual bool ExpO3View2Temp(); // 从O32表导入数据到临时表
    virtual bool ExpTemp2Dst(); // 从临时表导入数据到目标表
};


#endif /* BROKER_H */
