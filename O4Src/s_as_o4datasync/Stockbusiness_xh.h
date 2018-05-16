/* 
 * File:   stockbusiness_xh.h
 * Author: wangzh19004
 * 
 * Created on 2016年11月2日, 下午4:13
 */

#ifndef STOCKBUSINESS_XH_H
#define	STOCKBUSINESS_XH_H

#include "DataSync.h"

// 一批次同步1W行
#define BATCH_ROWS 10000

class CStockBusinessXh : public CDataSync
{
    public:
        CStockBusinessXh(IAS2Context * lpContext);
        ~CStockBusinessXh();
        
    protected:
        virtual bool ExpO3View2Temp(); // 从O32表导入数据到临时表
        virtual bool ExpTemp2Dst(); // 从临时表导入数据到目标表
};

#endif	/* STOCKBUSINESS_XH_H */

