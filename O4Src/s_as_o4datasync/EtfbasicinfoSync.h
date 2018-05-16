#ifndef ETFBASICINFO_H
#define ETFBASICINFO_H

#include "DataSync.h"

// һ����ͬ��1W��
#define BATCH_ROWS 10000

// ͬ��������

class CEtfbasicinfoSync : public CDataSync
{
public:
    CEtfbasicinfoSync(IAS2Context * lpContext);
    ~CEtfbasicinfoSync();

protected:
    virtual bool ExpO3View2Temp(); // ��O32�������ݵ���ʱ��
    virtual bool ExpTemp2Dst(); // ����ʱ�������ݵ�Ŀ���
    virtual bool AfterAction();
    bool ModifyStockType();
};


#endif /* ETFBASICINFO_H */
