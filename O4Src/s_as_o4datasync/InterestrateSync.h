#ifndef INTERESTRATE_H
#define INTERESTRATE_H

#include "DataSync.h"

// һ����ͬ��1W��
#define BATCH_ROWS 10000

// ͬ��������

class CInterestrateSync : public CDataSync
{
public:
    CInterestrateSync(IAS2Context * lpContext);
    ~CInterestrateSync();

protected:
    virtual bool ExpO3View2Temp(); // ��O32�������ݵ���ʱ��
    virtual bool ExpTemp2Dst(); // ����ʱ�������ݵ�Ŀ���
};


#endif /* INTERESTRATE_H */
