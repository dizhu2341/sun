#ifndef OPTIONCASH_H
#define OPTIONCASH_H

#include "DataSync.h"

// һ����ͬ��1W��
#define BATCH_ROWS 10000

// ͬ��������

class COptioncashSync : public CDataSync
{
public:
    COptioncashSync(IAS2Context * lpContext);
    ~COptioncashSync();

protected:
    virtual bool ExpO3View2Temp(); // ��O32�������ݵ���ʱ��
    virtual bool ExpTemp2Dst(); // ����ʱ�������ݵ�Ŀ���
};


#endif /* OPTIONCASH_H */
