/* 
 * File:   Otcdealsettuncomp_redo.h
 * Author: wangzh19004
 *
 * Created on 2016年11月10日, 下午4:28
 */

#ifndef OTCDEALSETTUNCOMP_REDO_H
#define	OTCDEALSETTUNCOMP_REDO_H

#include "DataSync.h"

// 一批次同步1W行
#define BATCH_ROWS 10000

// 同步处理类

class COtcdealsettuncompRedo : public CDataSync
{
public:
    COtcdealsettuncompRedo(IAS2Context * lpContext);
    ~COtcdealsettuncompRedo();

protected:
    virtual bool ExpO3View2Temp(); // 从O32表导入数据到临时表
    virtual bool ExpTemp2Dst(); // 从临时表导入数据到目标表
};

#endif	/* OTCDEALSETTUNCOMP_REDO_H */

