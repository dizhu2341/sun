#ifndef CAPITALACCOUNT_H
#define CAPITALACCOUNT_H

#include "DataSync.h"

// һ����ͬ��1W��
#define BATCH_ROWS 10000

// ͬ��������

class CCapitalaccountSync : public CDataSync
{
public:
    CCapitalaccountSync(IAS2Context * lpContext);
    ~CCapitalaccountSync();

protected:
    virtual bool ExpO3View2Temp(); // ��O32�������ݵ���ʱ��
    virtual bool ExpTemp2Dst(); // ����ʱ�������ݵ�Ŀ���
};


#endif /* CAPITALACCOUNT_H */
