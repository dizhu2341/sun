#ifndef INSTANCESTOCK_XH_H
#define INSTANCESTOCK_XH_H

#include "DataSync.h"

// һ����ͬ��1W��
#define BATCH_ROWS 10000

// ͬ��������

class CInstancestockXh : public CDataSync
{
public:
    CInstancestockXh(IAS2Context * lpContext);
    ~CInstancestockXh();

protected:
    virtual bool ExpO3View2Temp(); // ��O32�������ݵ���ʱ��
    virtual bool ExpTemp2Dst(); // ����ʱ�������ݵ�Ŀ���
};


#endif /* INSTANCESTOCK_XH_H */
