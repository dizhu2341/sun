#ifndef INSTANCESTOCK_QH_H
#define INSTANCESTOCK_QH_H

#include "DataSync.h"

// һ����ͬ��1W��
#define BATCH_ROWS 10000

// ͬ��������

class CInstancestockQh : public CDataSync
{
public:
    CInstancestockQh(IAS2Context * lpContext);
    ~CInstancestockQh();

protected:
    virtual bool ExpO3View2Temp(); // ��O32�������ݵ���ʱ��
    virtual bool ExpTemp2Dst(); // ����ʱ�������ݵ�Ŀ���
};


#endif /* INSTANCESTOCK_QH_H */
