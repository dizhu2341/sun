#ifndef UNITSTOCK_H
#define UNITSTOCK_H

#include "DataSync.h"

// һ����ͬ��1W��
#define BATCH_ROWS 10000

// ͬ��������

class CUnitstockSync : public CDataSync
{
public:
    CUnitstockSync(IAS2Context * lpContext);
    ~CUnitstockSync();

protected:
    virtual bool ExpO3View2Temp(); // ��O32�������ݵ���ʱ��
    virtual bool ExpTemp2Dst(); // ����ʱ�������ݵ�Ŀ���
};


#endif /* UNITSTOCK_H */
