#ifndef MANUALSTOCK_ZSCSH_H
#define MANUALSTOCK_ZSCSH_H

#include "DataSync.h"

// һ����ͬ��1W��
#define BATCH_ROWS 10000

// ͬ��������

class CManualstockZscshSync : public CDataSync
{
public:
    CManualstockZscshSync(IAS2Context * lpContext);
    ~CManualstockZscshSync();

protected:
    virtual bool ExpO3View2Temp(); // ��O32�������ݵ���ʱ��
    virtual bool ExpTemp2Dst(); // ����ʱ�������ݵ�Ŀ���
};


#endif /* MANUALSTOCK_ZSCSH_H */
