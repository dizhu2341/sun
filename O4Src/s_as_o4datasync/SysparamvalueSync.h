#ifndef SYSPARAMVALUE_H
#define SYSPARAMVALUE_H

#include "DataSync.h"

// 一批次同步1W行
#define BATCH_ROWS 10000

// 同步处理类

class CSysparamvalueSync : public CDataSync
{
public:
    CSysparamvalueSync(IAS2Context * lpContext);
    ~CSysparamvalueSync();

protected:
    virtual bool ExpO3View2Temp(); // 从O32表导入数据到临时表
    virtual bool ExpTemp2Dst(); // 从临时表导入数据到目标表
private:
    void ConvertStockTypeList(char StockTypeArr[4001], char StockTypeSrc[4001]);
    
};


#endif /* SYSPARAMVALUE_H */
