#ifndef FEEHS_H
#define FEEHS_H

#include "DataSync.h"

// һ����ͬ��1W��
#define BATCH_ROWS 10000

// ͬ��������

class CFeehsSync : public CDataSync
{
public:
    CFeehsSync(IAS2Context * lpContext);
    ~CFeehsSync();

protected:
    virtual bool ExpO3View2Temp(); // ��O32�������ݵ���ʱ��
    virtual bool ExpTemp2Dst(); // ����ʱ�������ݵ�Ŀ���
};


#endif /* FEEHS_H */
