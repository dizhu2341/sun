#ifndef STOCKBUSINESS_H
#define STOCKBUSINESS_H

#include "DataSync.h"

// һ����ͬ��1W��
#define BATCH_ROWS 10000

// ͬ��������

class CStockbusinessSync : public CDataSync
{
public:
    CStockbusinessSync(IAS2Context * lpContext);
    ~CStockbusinessSync();

protected:
    virtual bool ExpO3View2Temp(); // ��O32�������ݵ���ʱ��
    virtual bool ExpTemp2Dst(); // ����ʱ�������ݵ�Ŀ���
};


#endif /* STOCKBUSINESS_H */
