#ifndef CONTAINFEE_H
#define CONTAINFEE_H

#include "DataSync.h"

// һ����ͬ��1W��
#define BATCH_ROWS 10000

// ͬ��������

class CContainfeeSync : public CDataSync
{
public:
    CContainfeeSync(IAS2Context * lpContext);
    ~CContainfeeSync();

protected:
    virtual bool ExpO3View2Temp(); // ��O32�������ݵ���ʱ��
    virtual bool ExpTemp2Dst(); // ����ʱ�������ݵ�Ŀ���
};


#endif /* CONTAINFEE_H */
