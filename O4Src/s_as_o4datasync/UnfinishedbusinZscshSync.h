#ifndef UNFINISHEDBUSIN_ZSCSH_H
#define UNFINISHEDBUSIN_ZSCSH_H

#include "DataSync.h"

// һ����ͬ��1W��
#define BATCH_ROWS 10000

// ͬ��������

class CUnfinishedbusinZscshSync : public CDataSync
{
public:
    CUnfinishedbusinZscshSync(IAS2Context * lpContext);
    ~CUnfinishedbusinZscshSync();

protected:
    virtual bool ExpO3View2Temp(); // ��O32�������ݵ���ʱ��
    virtual bool ExpTemp2Dst(); // ����ʱ�������ݵ�Ŀ���
};


#endif /* UNFINISHEDBUSIN_ZSCSH_H */
