/* 
 * File:   Stockbusiness_yhj.h
 * Author: wangzh19004
 *
 * Created on 2016年11月3日, 下午3:10
 */

#ifndef STOCKBUSINESS_YHJ_H
#define	STOCKBUSINESS_YHJ_H

#include "DataSync.h"

// 一批次同步1W行
#define BATCH_ROWS 10000

class CStockBusinessYhj : public CDataSync
{
    public:
        CStockBusinessYhj(IAS2Context * lpContext);
        ~CStockBusinessYhj();
        
    protected:
        virtual bool ExpO3View2Temp(); // 从O32表导入数据到临时表
        virtual bool ExpTemp2Dst(); // 从临时表导入数据到目标表
};

#endif	/* STOCKBUSINESS_YHJ_H */

