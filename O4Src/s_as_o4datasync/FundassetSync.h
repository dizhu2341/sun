#ifndef FUNDASSET_H
#define FUNDASSET_H

#include "DataSync.h"

// һ����ͬ��1W��
#define BATCH_ROWS 10000

// ͬ��������

class CFundassetSync : public CDataSync
{
public:
    CFundassetSync(IAS2Context * lpContext);
    ~CFundassetSync();

protected:
    virtual bool ExpO3View2Temp(); // ��O32�������ݵ���ʱ��
    virtual bool ExpTemp2Dst(); // ����ʱ�������ݵ�Ŀ���
};


#endif /* FUNDASSET_H */
