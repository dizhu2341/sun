/* 
 * File:   Subjectstock_redo.h
 * Author: wangzh19004
 *
 * Created on 2016年11月9日, 下午3:30
 */

#ifndef SUBJECTSTOCK_REDO_H
#define	SUBJECTSTOCK_REDO_H

#include "DataSync.h"

// 一批次同步1W行
#define BATCH_ROWS 10000

// 同步处理类

class CSubjectStockRedo : public CDataSync
{
public:
    CSubjectStockRedo(IAS2Context * lpContext);
    ~CSubjectStockRedo();

protected:
    virtual bool ExpO3View2Temp(); // 从O32表导入数据到临时表
    virtual bool ExpTemp2Dst(); // 从临时表导入数据到目标表
};

#endif	/* SUBJECTSTOCK_REDO_H */

