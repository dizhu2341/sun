#ifndef HGRATIO_H
#define HGRATIO_H

#include "DataSync.h"

// һ����ͬ��1W��
#define BATCH_ROWS 10000

// ͬ��������

class CHgratioSync : public CDataSync
{
public:
    CHgratioSync(IAS2Context * lpContext);
    ~CHgratioSync();

protected:
    virtual bool ExpO3View2Temp(); // ��O32�������ݵ���ʱ��
    virtual bool ExpTemp2Dst(); // ����ʱ�������ݵ�Ŀ���
};


#endif /* HGRATIO_H */
