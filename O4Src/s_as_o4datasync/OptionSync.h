/* 
 * File:   OptionSync.h
 * Author: zhouyx11685
 * Description: 期权属性同步类
 * Created on 2015年12月11日, 下午7:44
 */

#ifndef OPTIONSYNC_H
#define	OPTIONSYNC_H

#include "DataSync.h"

// 一批次同步1W行
#define BATCH_ROWS 10000

// 同步处理类

class COptionSync : public CDataSync
{
public:
    COptionSync(IAS2Context * lpContext);
    ~COptionSync();
protected:
    virtual bool ExpO3View2Temp(); // 从O32表导入数据到临时表
    virtual bool ExpTemp2Dst(); // 从临时表导入数据到目标表
};

#endif	/* OPTIONSYNC_H */

