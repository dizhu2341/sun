#ifndef UNFINISHEDBUSIN_H
#define UNFINISHEDBUSIN_H

#include "DataSync.h"

// һ����ͬ��1W��
#define BATCH_ROWS 10000

// ͬ��������

class CUnfinishedbusinSync : public CDataSync
{
public:
    CUnfinishedbusinSync(IAS2Context * lpContext);
    ~CUnfinishedbusinSync();

protected:
    virtual bool ExpO3View2Temp(); // ��O32�������ݵ���ʱ��
    virtual bool ExpTemp2Dst(); // ����ʱ�������ݵ�Ŀ���
};


#endif /* UNFINISHEDBUSIN_H */
