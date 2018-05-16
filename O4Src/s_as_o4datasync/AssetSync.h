/* 
 * File:   AssetSync.h
 * Author: sunhm15168
 * Description: 资产单元同步类
 * Created on 2016年3月29日, 下午6:28
 */

#ifndef ASSETSYNC_H
#define	ASSETSYNC_H
#include "DataSync.h"

// 一批次同步1W行

#define BATCH_ROWS 10000

class CAssetSync : public CDataSync

{
public:
    CAssetSync(IAS2Context * lpContext);
    ~CAssetSync();

protected:
    virtual bool ExpO3View2Temp(); // 从O32表导入数据到临时表
    virtual bool ExpTemp2Dst(); // 从临时表导入数据到目标表
};


#endif	/* ASSETSYNC_H */

