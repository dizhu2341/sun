/* 
 * File:   HisRealDealSync.h
 * Author: zhouyx11685
 *
 * Created on 2016年11月3日, 下午7:26
 */

#ifndef HISREALDEALSYNC_H
#define	HISREALDEALSYNC_H


#include "DataSync.h"

// 一批次同步1W行
#define BATCH_ROWS 10000

// 同步处理类

class CHisRealDealSync : public CDataSync
{
public:
    CHisRealDealSync(IAS2Context * lpContext);
    ~CHisRealDealSync();

protected:
    virtual bool ExpO3View2Temp(); // 从O32表导入数据到临时表
    virtual bool ExpTemp2Dst(); // 从临时表导入数据到目标表
};

#endif	/* HISREALDEALSYNC_H */

