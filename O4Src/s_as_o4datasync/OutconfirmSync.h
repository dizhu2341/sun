#ifndef OUTCONFIRM_H
#define OUTCONFIRM_H

#include "DataSync.h"

// һ����ͬ��1W��
#define BATCH_ROWS 10000

// ͬ��������

class COutconfirmSync : public CDataSync
{
public:
    COutconfirmSync(IAS2Context * lpContext);
    ~COutconfirmSync();

protected:
    virtual bool ExpO3View2Temp(); // ��O32�������ݵ���ʱ��
    virtual bool ExpTemp2Dst(); // ����ʱ�������ݵ�Ŀ���
};


#endif /* OUTCONFIRM_H */
