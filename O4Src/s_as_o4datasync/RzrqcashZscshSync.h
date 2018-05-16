#ifndef RZRQCASH_ZSCSH_H
#define RZRQCASH_ZSCSH_H

#include "DataSync.h"

// 一批次同步1W行
#define BATCH_ROWS 10000

// 同步处理类

class CRzrqcashZscshSync : public CDataSync
{
public:
    CRzrqcashZscshSync(IAS2Context * lpContext);
    ~CRzrqcashZscshSync();

protected:
    virtual bool ExpO3View2Temp(); // 从O32表导入数据到临时表
    virtual bool ExpTemp2Dst(); // 从临时表导入数据到目标表
};


#endif /* RZRQCASH_ZSCSH_H */
