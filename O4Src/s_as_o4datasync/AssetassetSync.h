#ifndef ASSETASSET_H
#define ASSETASSET_H

#include "DataSync.h"

// һ����ͬ��1W��
#define BATCH_ROWS 10000

// ͬ��������

class CAssetassetSync : public CDataSync
{
public:
    CAssetassetSync(IAS2Context * lpContext);
    ~CAssetassetSync();

protected:
    virtual bool ExpO3View2Temp(); // ��O32�������ݵ���ʱ��
    virtual bool ExpTemp2Dst(); // ����ʱ�������ݵ�Ŀ���
};


#endif /* ASSETASSET_H */
