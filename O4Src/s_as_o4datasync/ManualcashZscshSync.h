#ifndef MANUALCASH_ZSCSH_H
#define MANUALCASH_ZSCSH_H

#include "DataSync.h"

// һ����ͬ��1W��
#define BATCH_ROWS 10000

// ͬ��������

class CManualcashZscshSync : public CDataSync
{
public:
    CManualcashZscshSync(IAS2Context * lpContext);
    ~CManualcashZscshSync();

protected:
    virtual bool ExpO3View2Temp(); // ��O32�������ݵ���ʱ��
    virtual bool ExpTemp2Dst(); // ����ʱ�������ݵ�Ŀ���
};


#endif /* MANUALCASH_ZSCSH_H */
