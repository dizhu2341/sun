#ifndef BANKHGREGISTER_H
#define BANKHGREGISTER_H

#include "DataSync.h"

// һ����ͬ��1W��
#define BATCH_ROWS 10000

// ͬ��������

class CBankhgregisterSync : public CDataSync
{
public:
    CBankhgregisterSync(IAS2Context * lpContext);
    ~CBankhgregisterSync();

protected:
    virtual bool ExpO3View2Temp(); // ��O32�������ݵ���ʱ��
    virtual bool ExpTemp2Dst(); // ����ʱ�������ݵ�Ŀ���
};


#endif /* BANKHGREGISTER_H */
