/* 
 * File:   Stockfrozendetail_qh.h
 * Author: wangzh19004
 *
 * Created on 2016年11月3日, 下午5:37
 */

#ifndef STOCKFROZENDETAIL_QH_H
#define	STOCKFROZENDETAIL_QH_H

#include "DataSync.h"

// 一批次同步1W行
#define BATCH_ROWS 10000

class CStockFrozenDetailQh : public CDataSync
{
    public:
        CStockFrozenDetailQh(IAS2Context * lpContext);
        ~CStockFrozenDetailQh();
        
    protected:
        virtual bool ExpO3View2Temp(); // 从O32表导入数据到临时表
        virtual bool ExpTemp2Dst(); // 从临时表导入数据到目标表
};

#endif	/* STOCKFROZENDETAIL_QH_H */

