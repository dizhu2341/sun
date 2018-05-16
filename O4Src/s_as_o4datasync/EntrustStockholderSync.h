/* 
 * File:   EntrustStockholderSync.h
 * Author: zhouyx11685
 *
 * Created on 2016年4月5日, 下午1:13
 */

#ifndef ENTRUSTSTOCKHOLDERSYNC_H
#define	ENTRUSTSTOCKHOLDERSYNC_H

#include "DataSync.h"

// 一批次同步1W行
#define BATCH_ROWS 10000

// 同步处理类

class CEntrustStockholderSync : public CDataSync
{
public:
    CEntrustStockholderSync(IAS2Context * lpContext);
    ~CEntrustStockholderSync();
protected:
    virtual bool ExpO3View2Temp(); // 从O32表导入数据到临时表
    virtual bool ExpTemp2Dst(); // 从临时表导入数据到目标表
};

#endif	/* ENTRUSTSTOCKHOLDERSYNC_H */

