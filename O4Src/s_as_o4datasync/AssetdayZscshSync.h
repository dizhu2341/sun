#ifndef ASSETDAY_ZSCSH_H
#define ASSETDAY_ZSCSH_H

#include "DataSync.h"

// һ����ͬ��1W��
#define BATCH_ROWS 10000

// ͬ��������

class CAssetdayZscshSync : public CDataSync
{
public:
    CAssetdayZscshSync(IAS2Context * lpContext);
    ~CAssetdayZscshSync();

protected:
    virtual bool ExpO3View2Temp(); // ��O32�������ݵ���ʱ��
    virtual bool ExpTemp2Dst(); // ����ʱ�������ݵ�Ŀ���
};


#endif /* ASSETDAY_ZSCSH_H */
