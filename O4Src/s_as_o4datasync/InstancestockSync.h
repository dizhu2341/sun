#ifndef INSTANCESTOCK_H
#define INSTANCESTOCK_H

#include "DataSync.h"

// һ����ͬ��1W��
#define BATCH_ROWS 10000

// ͬ��������

class CInstancestockSync : public CDataSync
{
public:
    CInstancestockSync(IAS2Context * lpContext);
    ~CInstancestockSync();

protected:
    virtual bool ExpO3View2Temp(); // ��O32�������ݵ���ʱ��
    virtual bool ExpTemp2Dst(); // ����ʱ�������ݵ�Ŀ���
};


#endif /* INSTANCESTOCK_H */
