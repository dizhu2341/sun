#ifndef SQUENCE_H
#define SQUENCE_H

#include "DataSync.h"

// һ����ͬ��1W��
#define BATCH_ROWS 10000

// ͬ��������

class CSquenceSync : public CDataSync
{
public:
    CSquenceSync(IAS2Context * lpContext);
    ~CSquenceSync();

protected:
    virtual bool ExpO3View2Temp(); // ��O32�������ݵ���ʱ��
    virtual bool ExpTemp2Dst(); // ����ʱ�������ݵ�Ŀ���
};


#endif /* SQUENCE_H */
