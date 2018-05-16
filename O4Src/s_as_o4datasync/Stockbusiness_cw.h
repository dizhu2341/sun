/* 
 * File:   Stockbusiness_cw.h
 * Author: wangzh19004
 *
 * Created on 2016年11月3日, 上午11:26
 */

#ifndef STOCKBUSINESS_CW_H
#define	STOCKBUSINESS_CW_H

#include "DataSync.h"

// 一批次同步1W行
#define BATCH_ROWS 10000

class CStockBusinessCw : public CDataSync
{
    public:
        CStockBusinessCw(IAS2Context * lpContext);
        ~CStockBusinessCw();
        
    protected:
        virtual bool ExpO3View2Temp(); // 从O32表导入数据到临时表
        virtual bool ExpTemp2Dst(); // 从临时表导入数据到目标表
};

#endif	/* STOCKBUSINESS_CW_H */

