#ifndef OPTIONCOMBI_H
#define OPTIONCOMBI_H

#include "DataSync.h"

// 一批次同步1W行
#define BATCH_ROWS 10000

// 同步处理类

class COptioncombiSync : public CDataSync
{
public:
    COptioncombiSync(IAS2Context * lpContext);
    ~COptioncombiSync();

protected:
    virtual bool ExpO3View2Temp(); // 从O32表导入数据到临时表
    virtual bool ExpTemp2Dst(); // 从临时表导入数据到目标表
};


#endif /* OPTIONCOMBI_H */
