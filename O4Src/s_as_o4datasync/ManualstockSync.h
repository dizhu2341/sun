#ifndef MANUALSTOCK_H
#define MANUALSTOCK_H

#include "DataSync.h"

// һ����ͬ��1W��
#define BATCH_ROWS 10000

// ͬ��������

class CManualstockSync : public CDataSync
{
public:
    CManualstockSync(IAS2Context * lpContext);
    ~CManualstockSync();

protected:
    virtual bool ExpO3View2Temp(); // ��O32�������ݵ���ʱ��
    virtual bool ExpTemp2Dst(); // ����ʱ�������ݵ�Ŀ���
};


#endif /* MANUALSTOCK_H */
