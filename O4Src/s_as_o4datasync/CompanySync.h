#ifndef COMPANY_H
#define COMPANY_H

#include "DataSync.h"

// һ����ͬ��1W��
#define BATCH_ROWS 10000

// ͬ��������

class CCompanySync : public CDataSync
{
public:
    CCompanySync(IAS2Context * lpContext);
    ~CCompanySync();

protected:
    virtual bool ExpO3View2Temp(); // ��O32���������ݵ���ʱ��
    virtual bool ExpTemp2Dst(); // ����ʱ���������ݵ�Ŀ���
};


#endif /* COMPANY_H */