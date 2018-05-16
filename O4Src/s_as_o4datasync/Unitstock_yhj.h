/* 
 * File:   Unitstock_yhj.h
 * Author: wangzh19004
 *
 * Created on 2016��11��7��, ����4:24
 */

#ifndef UNITSTOCK_YHJ_H
#define	UNITSTOCK_YHJ_H

#include "DataSync.h"

// һ����ͬ��1W��
#define BATCH_ROWS 10000

// ͬ��������

class CUnitStockYhj : public CDataSync
{
public:
    CUnitStockYhj(IAS2Context * lpContext);
    ~CUnitStockYhj();

protected:
    virtual bool ExpO3View2Temp(); // ��O32�������ݵ���ʱ��
    virtual bool ExpTemp2Dst(); // ����ʱ�������ݵ�Ŀ���
};

#endif	/* UNITSTOCK_YHJ_H */

