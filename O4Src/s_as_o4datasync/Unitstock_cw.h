/* 
 * File:   Unitstock_cw.h
 * Author: wangzh19004
 *
 * Created on 2016��11��7��, ����3:59
 */

#ifndef UNITSTOCK_CW_H
#define	UNITSTOCK_CW_H

#include "DataSync.h"

// һ����ͬ��1W��
#define BATCH_ROWS 10000

// ͬ��������

class CUnitStockCw : public CDataSync
{
public:
    CUnitStockCw(IAS2Context * lpContext);
    ~CUnitStockCw();

protected:
    virtual bool ExpO3View2Temp(); // ��O32�������ݵ���ʱ��
    virtual bool ExpTemp2Dst(); // ����ʱ�������ݵ�Ŀ���
};

#endif	/* UNITSTOCK_CW_H */

