/* 
 * File:   Financedebit_redo.h
 * Author: wangzh19004
 *
 * Created on 2016年11月8日, 下午4:32
 */

#ifndef FINANCEDEBIT_REDO_H
#define	FINANCEDEBIT_REDO_H

#include "DataSync.h"

// 一批次同步1W行
#define BATCH_ROWS 10000

// 同步处理类

class CFinancedebitRedo : public CDataSync
{
public:
    CFinancedebitRedo(IAS2Context * lpContext);
    ~CFinancedebitRedo();

protected:
    virtual bool ExpO3View2Temp(); // 从O32表导入数据到临时表
    virtual bool ExpTemp2Dst(); // 从临时表导入数据到目标表
};

#endif	/* FINANCEDEBIT_REDO_H */

