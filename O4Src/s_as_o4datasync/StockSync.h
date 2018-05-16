/* 
 * File:   StockSync.h
 * Author: zhouyx11685
 * Description: ֤ȯ��Ϣͬ����
 * Created on 2015��11��9��, ����4:10
 */

#ifndef STOCKSYNC_H
#define STOCKSYNC_H

#include "DataSync.h"

// һ����ͬ��1W��
#define BATCH_ROWS 10000

// ͬ��������

class CStockSync : public CDataSync
{
public:
    CStockSync(IAS2Context * lpContext);
    ~CStockSync();

protected:
    virtual bool ExpO3View2Temp(); // ��O32�������ݵ���ʱ��
    virtual bool ExpTemp2Dst(); // ����ʱ�������ݵ�Ŀ���
    virtual bool AfterAction();

    bool SyncInterCodeToMDB();
    bool ModifyStockType();
    bool SyncStock2His();
};

#endif
