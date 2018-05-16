/* 
 * File:   Organization.h
 * Author: zhouyx11685
 *
 * Created on 2016年10月31日, 上午9:43
 */

#ifndef ORGANIZATION_H
#define	ORGANIZATION_H

#include "DataSync.h"

// 一批次同步1W行
#define BATCH_ROWS 10000

// 同步处理类

class COrganizationSync : public CDataSync
{
public:
    COrganizationSync(IAS2Context * lpContext);
    ~COrganizationSync();

protected:
    virtual bool ExpO3View2Temp(); // 从O32表导入数据到临时表
    virtual bool ExpTemp2Dst(); // 从临时表导入数据到目标表
};

#endif	/* ORGANIZATION_H */

