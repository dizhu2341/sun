#ifndef HOLDINGDETAIL_H
#define HOLDINGDETAIL_H

#include "DataSync.h"

// һ����ͬ��1W��
#define BATCH_ROWS 10000

// ͬ��������

class CHoldingdetailSync : public CDataSync
{
public:
    CHoldingdetailSync(IAS2Context * lpContext);
    ~CHoldingdetailSync();

protected:
    virtual bool ExpO3View2Temp(); // ��O32�������ݵ���ʱ��
    virtual bool ExpTemp2Dst(); // ����ʱ�������ݵ�Ŀ���
};


#endif /* HOLDINGDETAIL_H */
