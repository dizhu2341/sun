#ifndef HGMORTAGAGE_H
#define HGMORTAGAGE_H

#include "DataSync.h"

// 一批次同步1W行
#define BATCH_ROWS 10000

// 同步处理类

class CHgmortagageSync : public CDataSync
{
public:
    CHgmortagageSync(IAS2Context * lpContext);
    ~CHgmortagageSync();

protected:
    virtual bool ExpO3View2Temp(); // 从O32表导入数据到临时表
    virtual bool ExpTemp2Dst(); // 从临时表导入数据到目标表
};


#endif /* HGMORTAGAGE_H */
