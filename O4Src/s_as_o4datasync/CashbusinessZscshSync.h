#ifndef CASHBUSINESS_ZSCSH_H
#define CASHBUSINESS_ZSCSH_H

#include "DataSync.h"

// һ����ͬ��1W��
#define BATCH_ROWS 10000

// ͬ��������

class CCashbusinessZscshSync : public CDataSync
{
public:
    CCashbusinessZscshSync(IAS2Context * lpContext);
    ~CCashbusinessZscshSync();

protected:
    virtual bool ExpO3View2Temp(); // ��O32�������ݵ���ʱ��
    virtual bool ExpTemp2Dst(); // ����ʱ�������ݵ�Ŀ���
};


#endif /* CASHBUSINESS_ZSCSH_H */
