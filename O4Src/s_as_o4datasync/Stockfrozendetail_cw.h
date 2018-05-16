/* 
 * File:   Stockfrozendetail_cw.h
 * Author: wangzh19004
 *
 * Created on 2016年11月3日, 下午7:26
 */

#ifndef STOCKFROZENDETAIL_CW_H
#define	STOCKFROZENDETAIL_CW_H

#include "DataSync.h"

// 一批次同步1W行
#define BATCH_ROWS 10000

class CStockFrozenDetailCw : public CDataSync
{
    public:
        CStockFrozenDetailCw(IAS2Context * lpContext);
        ~CStockFrozenDetailCw();
        
    protected:
        virtual bool ExpO3View2Temp(); // 从O32表导入数据到临时表
        virtual bool ExpTemp2Dst(); // 从临时表导入数据到目标表
};

#endif	/* STOCKFROZENDETAIL_CW_H */

