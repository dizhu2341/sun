#ifndef FEEQH_H
#define FEEQH_H

#include "DataSync.h"

// һ����ͬ��1W��
#define BATCH_ROWS 10000

// ͬ��������

class CFeeqhSync : public CDataSync
{
public:
    CFeeqhSync(IAS2Context * lpContext);
    ~CFeeqhSync();

protected:
    virtual bool ExpO3View2Temp(); // ��O32�������ݵ���ʱ��
    virtual bool ExpTemp2Dst(); // ����ʱ�������ݵ�Ŀ���
};


#endif /* FEEQH_H */
