#ifndef SEAT_H
#define SEAT_H

#include "DataSync.h"

// һ����ͬ��1W��
#define BATCH_ROWS 10000

// ͬ��������

class CSeatSync : public CDataSync
{
public:
    CSeatSync(IAS2Context * lpContext);
    ~CSeatSync();

protected:
    virtual bool ExpO3View2Temp(); // ��O32�������ݵ���ʱ��
    virtual bool ExpTemp2Dst(); // ����ʱ�������ݵ�Ŀ���
};


#endif /* SEAT_H */
