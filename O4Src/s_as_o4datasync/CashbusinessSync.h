#ifndef CASHBUSINESS_H
#define CASHBUSINESS_H

#include "DataSync.h"

// һ����ͬ��1W��
#define BATCH_ROWS 10000

// ͬ��������

class CCashbusinessSync : public CDataSync
{
public:
    CCashbusinessSync(IAS2Context * lpContext);
    ~CCashbusinessSync();

protected:
    virtual bool ExpO3View2Temp(); // ��O32�������ݵ���ʱ��
    virtual bool ExpTemp2Dst(); // ����ʱ�������ݵ�Ŀ���
};


#endif /* CASHBUSINESS_H */
