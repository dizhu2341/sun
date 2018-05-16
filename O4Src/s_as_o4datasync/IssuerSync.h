#ifndef ISSUER_H
#define ISSUER_H

#include "DataSync.h"

// һ����ͬ��1W��
#define BATCH_ROWS 10000

// ͬ��������

class CIssuerSync : public CDataSync
{
public:
    CIssuerSync(IAS2Context * lpContext);
    ~CIssuerSync();

protected:
    virtual bool ExpO3View2Temp(); // ��O32�������ݵ���ʱ��
    virtual bool ExpTemp2Dst(); // ����ʱ�������ݵ�Ŀ���
};


#endif /* ISSUER_H */
