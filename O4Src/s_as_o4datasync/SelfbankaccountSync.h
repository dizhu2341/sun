#ifndef SELFBANKACCOUNT_H
#define SELFBANKACCOUNT_H

#include "DataSync.h"

// һ����ͬ��1W��
#define BATCH_ROWS 10000

// ͬ��������

class CSelfbankaccountSync : public CDataSync
{
public:
    CSelfbankaccountSync(IAS2Context * lpContext);
    ~CSelfbankaccountSync();

protected:
    virtual bool ExpO3View2Temp(); // ��O32�������ݵ���ʱ��
    virtual bool ExpTemp2Dst(); // ����ʱ�������ݵ�Ŀ���
};


#endif /* SELFBANKACCOUNT_H */
