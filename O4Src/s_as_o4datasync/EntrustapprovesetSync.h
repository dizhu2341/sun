#ifndef ENTRUSTAPPROVESET_H
#define ENTRUSTAPPROVESET_H

#include "DataSync.h"

// 一批次同步1W行
#define BATCH_ROWS 10000

// 同步处理类

class CEntrustapprovesetSync : public CDataSync
{
public:
    CEntrustapprovesetSync(IAS2Context * lpContext);
    ~CEntrustapprovesetSync();

protected:
    virtual bool ExpO3View2Temp(); // 从O32表导入数据到临时表
    virtual bool ExpTemp2Dst(); // 从临时表导入数据到目标表
};


#endif /* ENTRUSTAPPROVESET_H */
