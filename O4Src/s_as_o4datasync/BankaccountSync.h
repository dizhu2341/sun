#ifndef BANKACCOUNT_H
#define BANKACCOUNT_H

#include "DataSync.h"

// һ����ͬ��1W��
#define BATCH_ROWS 10000

// ͬ��������

class CBankaccountSync : public CDataSync
{
public:
    CBankaccountSync(IAS2Context * lpContext);
    ~CBankaccountSync();

protected:
    virtual bool ExpO3View2Temp(); // ��O32�������ݵ���ʱ��
    virtual bool ExpTemp2Dst(); // ����ʱ�������ݵ�Ŀ���
};


#endif /* BANKACCOUNT_H */
