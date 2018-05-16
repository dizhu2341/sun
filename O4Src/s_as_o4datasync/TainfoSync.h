#ifndef TAINFO_H
#define TAINFO_H

#include "DataSync.h"

// 一批次同步1W行
#define BATCH_ROWS 10000

// 同步处理类

class CTainfoSync : public CDataSync
{
public:
    CTainfoSync(IAS2Context * lpContext);
    ~CTainfoSync();

protected:
    virtual bool ExpO3View2Temp(); // 从O32表导入数据到临时表
    virtual bool ExpTemp2Dst(); // 从临时表导入数据到目标表
};


#endif /* TAINFO_H */
