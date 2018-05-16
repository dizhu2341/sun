#ifndef STOCKBUSINESS_ZSCSH_H
#define STOCKBUSINESS_ZSCSH_H

#include "DataSync.h"

// һ����ͬ��1W��
#define BATCH_ROWS 10000

// ͬ��������

class CStockbusinessZscshSync : public CDataSync
{
public:
    CStockbusinessZscshSync(IAS2Context * lpContext);
    ~CStockbusinessZscshSync();

protected:
    virtual bool ExpO3View2Temp(); // ��O32�������ݵ���ʱ��
    virtual bool ExpTemp2Dst(); // ����ʱ�������ݵ�Ŀ���
};


#endif /* STOCKBUSINESS_ZSCSH_H */
