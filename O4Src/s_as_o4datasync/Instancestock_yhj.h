/* 
 * File:   Instancestock_yhj.h
 * Author: wangzh19004
 *
 * Created on 2016��11��10��, ����5:32
 */

#ifndef INSTANCESTOCK_YHJ_H
#define	INSTANCESTOCK_YHJ_H

#include "DataSync.h"

// һ����ͬ��1W��
#define BATCH_ROWS 10000

// ͬ��������

class CInstancestockYhj : public CDataSync
{
public:
    CInstancestockYhj(IAS2Context * lpContext);
    ~CInstancestockYhj();

protected:
    virtual bool ExpO3View2Temp(); // ��O32�������ݵ���ʱ��
    virtual bool ExpTemp2Dst(); // ����ʱ�������ݵ�Ŀ���
};

#endif	/* INSTANCESTOCK_YHJ_H */

