/* 
 * File:   Subjectbusiness.h
 * Author: wangzh19004
 *
 * Created on 2016年11月9日, 上午9:04
 */

#ifndef SUBJECTBUSINESS_H
#define	SUBJECTBUSINESS_H

#include "DataSync.h"

// 一批次同步1W行
#define BATCH_ROWS 10000

// 同步处理类
class CSubjectBusiness : public CDataSync
{
public:
    CSubjectBusiness(IAS2Context * lpContext);
    ~CSubjectBusiness();

protected:
    virtual bool ExpO3View2Temp(); // 从O32表导入数据到临时表
    virtual bool ExpTemp2Dst(); // 从临时表导入数据到目标表
};

#endif	/* SUBJECTBUSINESS_H */

