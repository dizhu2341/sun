#ifndef HGREGISTER_H
#define HGREGISTER_H

#include "DataSync.h"

// һ����ͬ��1W��
#define BATCH_ROWS 10000

// ͬ��������

class CHgregisterSync : public CDataSync
{
public:
    CHgregisterSync(IAS2Context * lpContext);
    ~CHgregisterSync();

protected:
    virtual bool ExpO3View2Temp(); // ��O32�������ݵ���ʱ��
    virtual bool ExpTemp2Dst(); // ����ʱ�������ݵ�Ŀ���
};


#endif /* HGREGISTER_H */
