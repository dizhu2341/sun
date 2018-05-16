/* 
 * File:   Stockfrozendetail_xh.h
 * Author: wangzh19004
 *
 * Created on 2016年11月3日, 下午3:52
 */

#ifndef STOCKFROZENDETAIL_XH_H
#define	STOCKFROZENDETAIL_XH_H

#include "DataSync.h"

// 一批次同步1W行
#define BATCH_ROWS 10000

class CStockFrozenDetailXh : public CDataSync
{
    public:
        CStockFrozenDetailXh(IAS2Context * lpContext);
        ~CStockFrozenDetailXh();
        
    protected:
        virtual bool ExpO3View2Temp(); // 从O32表导入数据到临时表
        virtual bool ExpTemp2Dst(); // 从临时表导入数据到目标表
};

#endif	/* STOCKFROZENDETAIL_XH_H */

