#ifndef ENTRUSTAPPROVESET_H
#define ENTRUSTAPPROVESET_H

#include "DataSync.h"

// һ����ͬ��1W��
#define BATCH_ROWS 10000

// ͬ��������

class CEntrustapprovesetSync : public CDataSync
{
public:
    CEntrustapprovesetSync(IAS2Context * lpContext);
    ~CEntrustapprovesetSync();

protected:
    virtual bool ExpO3View2Temp(); // ��O32�������ݵ���ʱ��
    virtual bool ExpTemp2Dst(); // ����ʱ�������ݵ�Ŀ���
};


#endif /* ENTRUSTAPPROVESET_H */
