#ifndef INSTANCESTOCK_QH_REDO_H
#define INSTANCESTOCK_QH_REDO_H

#include "DataSync.h"

// һ����ͬ��1W��
#define BATCH_ROWS 10000

// ͬ��������

class CInstancestockQhRedo : public CDataSync
{
public:
    CInstancestockQhRedo(IAS2Context * lpContext);
    ~CInstancestockQhRedo();

protected:
    virtual bool ExpO3View2Temp(); // ��O32�������ݵ���ʱ��
    virtual bool ExpTemp2Dst(); // ����ʱ�������ݵ�Ŀ���
};


#endif /* INSTANCESTOCK_QH_REDO_H */
