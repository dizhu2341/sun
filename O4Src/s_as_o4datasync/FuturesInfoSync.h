/* 
 * File:   FuturesInfoSync.h
 * Author: sunhm15168
 * Description: 期货信息同步
 * Created on 2016年2月16日, 上午9:45
 */

#ifndef FUTURESINFOSYNC_H
#define	FUTURESINFOSYNC_H
#include "DataSync.h"

// 一批次同步1W行
#define BATCH_ROWS 10000

// 同步处理类

class CFuturesInfoSync : public CDataSync
{
public:
    CFuturesInfoSync(IAS2Context * lpContext);
    ~CFuturesInfoSync();
protected:
    virtual bool ExpO3View2Temp(); // 从O32表导入数据到临时表
    virtual bool ExpTemp2Dst(); // 从临时表导入数据到目标表
};


#endif	/* FUTURESINFOSYNC_H */

