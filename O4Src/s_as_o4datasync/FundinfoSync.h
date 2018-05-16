#ifndef FUNDINFO_H
#define FUNDINFO_H

#include "DataSync.h"

// 一批次同步1W行
#define BATCH_ROWS 10000

// 同步处理类

class CFundinfoSync : public CDataSync
{
public:
    CFundinfoSync(IAS2Context * lpContext);
    ~CFundinfoSync();

protected:
    virtual bool ExpO3View2Temp(); // 从O32表导入数据到临时表
    virtual bool ExpTemp2Dst(); // 从临时表导入数据到目标表

private:
    void ConvertMarketNoList(char (*pMarketNoArr)[257], char sMarketNoSrc[BATCH_ROWS][257]);
};


#endif /* FUNDINFO_H */
