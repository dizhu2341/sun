/* 
 * File:   FundRightSync.h
 * Author: zhouyx11685
 * Description: 账户权限同步类
 * Created on 2015年12月16日, 下午3:10
 */

#ifndef FUNDRIGHTSYNC_H
#define	FUNDRIGHTSYNC_H

#include "DataSync.h"

// 一批次同步1W行
#define BATCH_ROWS 50000

// 同步处理类

class CFundRightSync : public CDataSync
{
public:
    CFundRightSync(IAS2Context * lpContext);
    ~CFundRightSync();
protected:
    virtual bool ExpO3View2Temp(); // 从O32表导入数据到临时表
    virtual bool ExpTemp2Dst(); // 从临时表导入数据到目标表
};

#endif	/* FUNDRIGHTSYNC_H */

