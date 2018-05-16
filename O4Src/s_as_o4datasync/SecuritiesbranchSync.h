#ifndef SECURITIESBRANCH_H
#define SECURITIESBRANCH_H

#include "DataSync.h"

// 一批次同步1W行
#define BATCH_ROWS 10000

// 同步处理类

class CSecuritiesbranchSync : public CDataSync
{
public:
    CSecuritiesbranchSync(IAS2Context * lpContext);
    ~CSecuritiesbranchSync();

protected:
    virtual bool ExpO3View2Temp(); // 从O32表导入数据到临时表
    virtual bool ExpTemp2Dst(); // 从临时表导入数据到目标表
private:
    void ConvertEntrustDirList(char (*pEntrustDirArr)[1025], char sEntrustDirSrc[BATCH_ROWS][1025]);
};


#endif /* SECURITIESBRANCH_H */
