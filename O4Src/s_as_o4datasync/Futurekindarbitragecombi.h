/* 
 * File:   Futurekindarbitragecombi.h
 * Author: zhouyx11685
 *
 * Created on 2016年5月24日, 上午10:56
 */

#ifndef FUTUREKINDARBITRAGECOMBI_H
#define	FUTUREKINDARBITRAGECOMBI_H

#include "DataSync.h"

// 一批次同步1W行
#define BATCH_ROWS 10000

// 同步处理类

class CFutureKindArbitrageCombiSync : public CDataSync
{
public:
    CFutureKindArbitrageCombiSync(IAS2Context * lpContext);
    ~CFutureKindArbitrageCombiSync();

protected:
    virtual bool ExpO3View2Temp(); // 从O32表导入数据到临时表
    virtual bool ExpTemp2Dst(); // 从临时表导入数据到目标表
};

#endif	/* FUTUREKINDARBITRAGECOMBI_H */

