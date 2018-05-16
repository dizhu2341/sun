/* 
 * File:   Stockfrozendetail_yhj.h
 * Author: wangzh19004
 *
 * Created on 2016年11月3日, 下午7:43
 */

#ifndef STOCKFROZENDETAIL_YHJ_H
#define	STOCKFROZENDETAIL_YHJ_H

#include "DataSync.h"

// 一批次同步1W行
#define BATCH_ROWS 10000

class CStockFrozenDetailYhj : public CDataSync
{
    public:
        CStockFrozenDetailYhj(IAS2Context * lpContext);
        ~CStockFrozenDetailYhj();
        
    protected:
        virtual bool ExpO3View2Temp(); // 从O32表导入数据到临时表
        virtual bool ExpTemp2Dst(); // 从临时表导入数据到目标表
};

#endif	/* STOCKFROZENDETAIL_YHJ_H */

