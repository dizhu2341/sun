/* 
 * File:   Unitsotck_qh.h
 * Author: wangzh19004
 *
 * Created on 2016��11��7��, ����3:18
 */

#ifndef UNITSOTCK_QH_H
#define	UNITSOTCK_QH_H

#include "DataSync.h"

// һ����ͬ��1W��
#define BATCH_ROWS 10000

// ͬ��������

class CUnitStockQh : public CDataSync
{
public:
    CUnitStockQh(IAS2Context * lpContext);
    ~CUnitStockQh();

protected:
    virtual bool ExpO3View2Temp(); // ��O32�������ݵ���ʱ��
    virtual bool ExpTemp2Dst(); // ����ʱ�������ݵ�Ŀ���
};

#endif	/* UNITSOTCK_QH_H */

