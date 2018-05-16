/* 
 * File:   UnitStock_xh_sync.h
 * Author: wangzh19004
 *
 * Created on 2016��11��7��, ����2:34
 */

#ifndef UNITSTOCK_XH_SYNC_H
#define	UNITSTOCK_XH_SYNC_H

#include "DataSync.h"

// һ����ͬ��1W��
#define BATCH_ROWS 10000

// ͬ��������

class CUnitStockXhSync : public CDataSync
{
public:
    CUnitStockXhSync(IAS2Context * lpContext);
    ~CUnitStockXhSync();

protected:
    virtual bool ExpO3View2Temp(); // ��O32�������ݵ���ʱ��
    virtual bool ExpTemp2Dst(); // ����ʱ�������ݵ�Ŀ���
};

#endif	/* UNITSTOCK_XH_SYNC_H */

