/* 
 * File:   Unitstock_xh.h
 * Author: wangzh19004
 *
 * Created on 2016��11��7��, ����10:20
 */

#ifndef UNITSTOCK_XH_H
#define	UNITSTOCK_XH_H

#include "DataSync.h"

// һ����ͬ��1W��
#define BATCH_ROWS 10000

// ͬ��������

class CUnitStockXh : public CDataSync
{
public:
    CUnitStockXh(IAS2Context * lpContext);
    ~CUnitStockXh();

protected:
    virtual bool ExpO3View2Temp(); // ��O32�������ݵ���ʱ��
    virtual bool ExpTemp2Dst(); // ����ʱ�������ݵ�Ŀ���
};

#endif	/* UNITSTOCK_XH_H */

