#ifndef FINANCEDEBIT_H
#define FINANCEDEBIT_H

#include "DataSync.h"

// һ����ͬ��1W��
#define BATCH_ROWS 10000

// ͬ��������

class CFinancedebitSync : public CDataSync
{
public:
    CFinancedebitSync(IAS2Context * lpContext);
    ~CFinancedebitSync();

protected:
    virtual bool ExpO3View2Temp(); // ��O32�������ݵ���ʱ��
    virtual bool ExpTemp2Dst(); // ����ʱ�������ݵ�Ŀ���
};


#endif /* FINANCEDEBIT_H */
