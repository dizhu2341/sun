#ifndef ASSETDAY_H
#define ASSETDAY_H

#include "DataSync.h"

// һ����ͬ��1W��
#define BATCH_ROWS 10000

// ͬ��������

class CAssetdaySync : public CDataSync
{
public:
    CAssetdaySync(IAS2Context * lpContext);
    ~CAssetdaySync();

protected:
    virtual bool ExpO3View2Temp(); // ��O32�������ݵ���ʱ��
    virtual bool ExpTemp2Dst(); // ����ʱ�������ݵ�Ŀ���
};


#endif /* ASSETDAY_H */
