#ifndef BANKINFO_H
#define BANKINFO_H

#include "DataSync.h"

// һ����ͬ��1W��
#define BATCH_ROWS 10000

// ͬ��������

class CBankinfoSync : public CDataSync
{
public:
    CBankinfoSync(IAS2Context * lpContext);
    ~CBankinfoSync();

protected:
    virtual bool ExpO3View2Temp(); // ��O32�������ݵ���ʱ��
    virtual bool ExpTemp2Dst(); // ����ʱ�������ݵ�Ŀ���
};


#endif /* BANKINFO_H */
