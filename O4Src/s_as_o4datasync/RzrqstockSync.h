#ifndef RZRQSTOCK_H
#define RZRQSTOCK_H

#include "DataSync.h"

// һ����ͬ��1W��
#define BATCH_ROWS 10000

// ͬ��������

class CRzrqstockSync : public CDataSync
{
public:
    CRzrqstockSync(IAS2Context * lpContext);
    ~CRzrqstockSync();

protected:
    virtual bool ExpO3View2Temp(); // ��O32�������ݵ���ʱ��
    virtual bool ExpTemp2Dst(); // ����ʱ�������ݵ�Ŀ���
};


#endif /* RZRQSTOCK_H */
