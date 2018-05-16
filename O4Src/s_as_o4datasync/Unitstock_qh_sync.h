/* 
 * File:   Unitstock_qh_sync.h
 * Author: wangzh19004
 *
 * Created on 2016��11��7��, ����3:44
 */

#ifndef UNITSTOCK_QH_SYNC_H
#define	UNITSTOCK_QH_SYNC_H

#include "DataSync.h"

// һ����ͬ��1W��
#define BATCH_ROWS 10000

// ͬ��������

class CUnitStockQhSync : public CDataSync
{
public:
    CUnitStockQhSync(IAS2Context * lpContext);
    ~CUnitStockQhSync();

protected:
    virtual bool ExpO3View2Temp(); // ��O32�������ݵ���ʱ��
    virtual bool ExpTemp2Dst(); // ����ʱ�������ݵ�Ŀ���
};

#endif	/* UNITSTOCK_QH_SYNC_H */

