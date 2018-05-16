#ifndef PENDSETTLE_H
#define PENDSETTLE_H

#include "DataSync.h"

// 一批次同步1W行
#define BATCH_ROWS 10000

// 同步处理类

class CPendsettleSync : public CDataSync
{
public:
    CPendsettleSync(IAS2Context * lpContext);
    ~CPendsettleSync();

protected:
    virtual bool ExpO3View2Temp(); // 从O32表导入数据到临时表
    virtual bool ExpTemp2Dst(); // 从临时表导入数据到目标表
};


#endif /* PENDSETTLE_H */
