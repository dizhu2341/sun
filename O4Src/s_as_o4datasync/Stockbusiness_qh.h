/* 
 * File:   Stockbusiness_qh.h
 * Author: wangzh19004
 *
 * Created on 2016年11月3日, 上午10:43
 */

#ifndef STOCKBUSINESS_QH_H
#define	STOCKBUSINESS_QH_H

#include "DataSync.h"

// 一批次同步1W行
#define BATCH_ROWS 10000

class CStockBusinessQh : public CDataSync
{
    public:
        CStockBusinessQh(IAS2Context * lpContext);
        ~CStockBusinessQh();
        
    protected:
        virtual bool ExpO3View2Temp(); // 从O32表导入数据到临时表
        virtual bool ExpTemp2Dst(); // 从临时表导入数据到目标表
};

#endif	/* STOCKBUSINESS_QH_H */

