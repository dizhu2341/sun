#ifndef TRADESEAT_H
#define TRADESEAT_H

#include "DataSync.h"

// һ����ͬ��1W��
#define BATCH_ROWS 10000

// ͬ��������

class CTradeseatSync : public CDataSync
{
public:
    CTradeseatSync(IAS2Context * lpContext);
    ~CTradeseatSync();

protected:
    virtual bool ExpO3View2Temp(); // ��O32�������ݵ���ʱ��
    virtual bool ExpTemp2Dst(); // ����ʱ�������ݵ�Ŀ���
};


#endif /* TRADESEAT_H */
