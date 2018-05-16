#ifndef HOLDINGDETAIL_ZSCSH_H
#define HOLDINGDETAIL_ZSCSH_H

#include "DataSync.h"

// 一批次同步1W行
#define BATCH_ROWS 10000

// 同步处理类

class CHoldingdetailZscshSync : public CDataSync
{
public:
    CHoldingdetailZscshSync(IAS2Context * lpContext);
    ~CHoldingdetailZscshSync();

protected:
    virtual bool ExpO3View2Temp(); // 从O32表导入数据到临时表
    virtual bool ExpTemp2Dst(); // 从临时表导入数据到目标表
};


#endif /* HOLDINGDETAIL_ZSCSH_H */
