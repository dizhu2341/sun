#ifndef FEESETHS_H
#define FEESETHS_H

#include "DataSync.h"

// һ����ͬ��1W��
#define BATCH_ROWS 10000

// ͬ��������

class CFeesethsSync : public CDataSync
{
public:
    CFeesethsSync(IAS2Context * lpContext);
    ~CFeesethsSync();

protected:
    virtual bool ExpO3View2Temp(); // ��O32�������ݵ���ʱ��
    virtual bool ExpTemp2Dst(); // ����ʱ�������ݵ�Ŀ���
};


#endif /* FEESETHS_H */
