/* 
 * File:   StockInfoModifySync.h
 * Author: sunhm15168
 * Description: ֤ȯ��Ϣ����ͬ����
 * Created on 2016��3��14��, ����9:29
 */

#ifndef STOCKINFOMODIFYSYNC_H
#define	STOCKINFOMODIFYSYNC_H

#include "DataSync.h"

// һ����ͬ��1W��
#define BATCH_ROWS 10000

// ͬ��������

class CStockInfoModifySync : public CDataSync
{
public:
    CStockInfoModifySync(IAS2Context * lpContext);
    ~CStockInfoModifySync();

protected:
    virtual bool ExpO3View2Temp(); // ��O32�������ݵ���ʱ��
    virtual bool ExpTemp2Dst(); // ����ʱ�������ݵ�Ŀ���
    virtual bool AfterAction();

    bool SyncInterCodeToMDB();
    bool ModifyStockType();
};
#endif	/* STOCKINFOMODIFYSYNC_H */

