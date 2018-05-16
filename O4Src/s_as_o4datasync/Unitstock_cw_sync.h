/* 
 * File:   Unitstock_cw_sync.h
 * Author: wangzh19004
 *
 * Created on 2016��11��7��, ����4:17
 */

#ifndef UNITSTOCK_CW_SYNC_H
#define	UNITSTOCK_CW_SYNC_H

#include "DataSync.h"

// һ����ͬ��1W��
#define BATCH_ROWS 10000

// ͬ��������

class CUnitStockCwSync : public CDataSync
{
public:
    CUnitStockCwSync(IAS2Context * lpContext);
    ~CUnitStockCwSync();

protected:
    virtual bool ExpO3View2Temp(); // ��O32�������ݵ���ʱ��
    virtual bool ExpTemp2Dst(); // ����ʱ�������ݵ�Ŀ���
};

#endif	/* UNITSTOCK_CW_SYNC_H */

