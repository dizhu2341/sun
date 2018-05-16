#ifndef UNITSTOCK_ZSCSH_H
#define UNITSTOCK_ZSCSH_H

#include "DataSync.h"

// һ����ͬ��1W��
#define BATCH_ROWS 10000

// ͬ��������

class CUnitstockZscshSync : public CDataSync
{
public:
    CUnitstockZscshSync(IAS2Context * lpContext);
    ~CUnitstockZscshSync();

protected:
    virtual bool ExpO3View2Temp(); // ��O32�������ݵ���ʱ��
    virtual bool ExpTemp2Dst(); // ����ʱ�������ݵ�Ŀ���
};


#endif /* UNITSTOCK_ZSCSH_H */
