#ifndef TRADERIVAL_H
#define TRADERIVAL_H

#include "DataSync.h"

// һ����ͬ��1W��
#define BATCH_ROWS 10000

// ͬ��������

class CTraderivalSync : public CDataSync
{
public:
    CTraderivalSync(IAS2Context * lpContext);
    ~CTraderivalSync();

protected:
    virtual bool ExpO3View2Temp(); // ��O32�������ݵ���ʱ��
    virtual bool ExpTemp2Dst(); // ����ʱ�������ݵ�Ŀ���
};


#endif /* TRADERIVAL_H */
