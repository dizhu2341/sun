/* 
 * File:   Mortgageinfo_redo.h
 * Author: wangzh19004
 *
 * Created on 2016年11月9日, 上午10:02
 */

#ifndef MORTGAGEINFO_REDO_H
#define	MORTGAGEINFO_REDO_H

#include "DataSync.h"

// 一批次同步1W行
#define BATCH_ROWS 10000

// 同步处理类

class CMortGageInfoRedo : public CDataSync
{
public:
    CMortGageInfoRedo(IAS2Context * lpContext);
    ~CMortGageInfoRedo();

protected:
    virtual bool ExpO3View2Temp(); // 从O32表导入数据到临时表
    virtual bool ExpTemp2Dst(); // 从临时表导入数据到目标表
};

#endif	/* MORTGAGEINFO_REDO_H */

