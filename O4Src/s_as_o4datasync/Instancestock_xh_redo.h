#ifndef INSTANCESTOCK_XH_REDO_H
#define INSTANCESTOCK_XH_REDO_H

#include "DataSync.h"

// һ����ͬ��1W��
#define BATCH_ROWS 10000

// ͬ��������

class CInstancestockXhRedo : public CDataSync
{
public:
    CInstancestockXhRedo(IAS2Context * lpContext);
    ~CInstancestockXhRedo();

protected:
    virtual bool ExpO3View2Temp(); // ��O32�������ݵ���ʱ��
    virtual bool ExpTemp2Dst(); // ����ʱ�������ݵ�Ŀ���
};


#endif /* INSTANCESTOCK_XH_REDO_H */
