#ifndef RZRQCASH_H
#define RZRQCASH_H

#include "DataSync.h"

// 一批次同步1W行
#define BATCH_ROWS 10000

// 同步处理类

class CRzrqcashSync : public CDataSync
{
public:
    CRzrqcashSync(IAS2Context * lpContext);
    ~CRzrqcashSync();

protected:
    virtual bool ExpO3View2Temp(); // 从O32表导入数据到临时表
    virtual bool ExpTemp2Dst(); // 从临时表导入数据到目标表
};


#endif /* RZRQCASH_H */
