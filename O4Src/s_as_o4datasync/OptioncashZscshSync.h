#ifndef OPTIONCASH_ZSCSH_H
#define OPTIONCASH_ZSCSH_H

#include "DataSync.h"

// һ����ͬ��1W��
#define BATCH_ROWS 10000

// ͬ��������

class COptioncashZscshSync : public CDataSync
{
public:
    COptioncashZscshSync(IAS2Context * lpContext);
    ~COptioncashZscshSync();

protected:
    virtual bool ExpO3View2Temp(); // ��O32�������ݵ���ʱ��
    virtual bool ExpTemp2Dst(); // ����ʱ�������ݵ�Ŀ���
};


#endif /* OPTIONCASH_ZSCSH_H */
