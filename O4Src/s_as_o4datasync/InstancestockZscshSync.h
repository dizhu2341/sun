#ifndef INSTANCESTOCK_ZSCSH_H
#define INSTANCESTOCK_ZSCSH_H

#include "DataSync.h"

// һ����ͬ��1W��
#define BATCH_ROWS 10000

// ͬ��������

class CInstancestockZscshSync : public CDataSync
{
public:
    CInstancestockZscshSync(IAS2Context * lpContext);
    ~CInstancestockZscshSync();

protected:
    virtual bool ExpO3View2Temp(); // ��O32�������ݵ���ʱ��
    virtual bool ExpTemp2Dst(); // ����ʱ�������ݵ�Ŀ���
};


#endif /* INSTANCESTOCK_ZSCSH_H */
