#ifndef MANUALCASH_H
#define MANUALCASH_H

#include "DataSync.h"

// һ����ͬ��1W��
#define BATCH_ROWS 10000

// ͬ��������

class CManualcashSync : public CDataSync
{
public:
    CManualcashSync(IAS2Context * lpContext);
    ~CManualcashSync();

protected:
    virtual bool ExpO3View2Temp(); // ��O32�������ݵ���ʱ��
    virtual bool ExpTemp2Dst(); // ����ʱ�������ݵ�Ŀ���
};


#endif /* MANUALCASH_H */
