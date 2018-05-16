#ifndef BROKER_H
#define BROKER_H

#include "DataSync.h"

// һ����ͬ��1W��
#define BATCH_ROWS 10000

// ͬ��������

class CBrokerSync : public CDataSync
{
public:
    CBrokerSync(IAS2Context * lpContext);
    ~CBrokerSync();

protected:
    virtual bool ExpO3View2Temp(); // ��O32���������ݵ���ʱ��
    virtual bool ExpTemp2Dst(); // ����ʱ���������ݵ�Ŀ���
};


#endif /* BROKER_H */