#ifndef HOLDINGDETAIL_ZSCSH_H
#define HOLDINGDETAIL_ZSCSH_H

#include "DataSync.h"

// һ����ͬ��1W��
#define BATCH_ROWS 10000

// ͬ��������

class CHoldingdetailZscshSync : public CDataSync
{
public:
    CHoldingdetailZscshSync(IAS2Context * lpContext);
    ~CHoldingdetailZscshSync();

protected:
    virtual bool ExpO3View2Temp(); // ��O32�������ݵ���ʱ��
    virtual bool ExpTemp2Dst(); // ����ʱ�������ݵ�Ŀ���
};


#endif /* HOLDINGDETAIL_ZSCSH_H */
