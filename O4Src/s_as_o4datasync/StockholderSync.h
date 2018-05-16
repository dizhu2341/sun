#ifndef STOCKHOLDER_H
#define STOCKHOLDER_H

#include "DataSync.h"

// 一批次同步1W行
#define BATCH_ROWS 10000

// 同步处理类

class CStockholderSync : public CDataSync
{
public:
    CStockholderSync(IAS2Context * lpContext);
    ~CStockholderSync();

protected:
    virtual bool ExpO3View2Temp(); // 从O32表导入数据到临时表
    virtual bool ExpTemp2Dst(); // 从临时表导入数据到目标表

private:
    void ConvertStockTypeList(char (*pStockTypeArr)[1025], char sStockTypeSrc[BATCH_ROWS][1025]);
};


#endif /* STOCKHOLDER_H */
