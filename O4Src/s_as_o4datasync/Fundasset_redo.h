/* 
 * File:   Fundasset_redo.h
 * Author: wangzh19004
 *
 * Created on 2016年11月8日, 下午7:43
 */

#ifndef FUNDASSET_REDO_H
#define	FUNDASSET_REDO_H

#include "DataSync.h"

// 一批次同步1W行
#define BATCH_ROWS 10000

// 同步处理类

class CFundassetRedo : public CDataSync
{
public:
    CFundassetRedo(IAS2Context * lpContext);
    ~CFundassetRedo();

protected:
    virtual bool ExpO3View2Temp(); // 从O32表导入数据到临时表
    virtual bool ExpTemp2Dst(); // 从临时表导入数据到目标表
};

#endif	/* FUNDASSET_REDO_H */

