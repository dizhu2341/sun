#ifndef PRICEINTERVAL_H
#define PRICEINTERVAL_H

#include "DataSync.h"

// һ����ͬ��1W��
#define BATCH_ROWS 10000

// ͬ��������

class CPriceintervalSync : public CDataSync
{
public:
    CPriceintervalSync(IAS2Context * lpContext);
    ~CPriceintervalSync();

protected:
    virtual bool ExpO3View2Temp(); // ��O32�������ݵ���ʱ��
    virtual bool ExpTemp2Dst(); // ����ʱ�������ݵ�Ŀ���
};


#endif /* PRICEINTERVAL_H */
