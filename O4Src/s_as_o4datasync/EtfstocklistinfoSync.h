#ifndef ETFSTOCKLISTINFO_H
#define ETFSTOCKLISTINFO_H

#include "DataSync.h"

// һ����ͬ��1W��
#define BATCH_ROWS 10000

// ͬ��������

class CEtfstocklistinfoSync : public CDataSync
{
public:
    CEtfstocklistinfoSync(IAS2Context * lpContext);
    ~CEtfstocklistinfoSync();

protected:
    virtual bool ExpO3View2Temp(); // ��O32�������ݵ���ʱ��
    virtual bool ExpTemp2Dst(); // ����ʱ�������ݵ�Ŀ���
};


#endif /* ETFSTOCKLISTINFO_H */
