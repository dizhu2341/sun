#ifndef TRADEDATE_H
#define TRADEDATE_H

#include "DataSync.h"

// һ����ͬ��1W��
#define BATCH_ROWS 10000

// ͬ��������

class CTradedateSync : public CDataSync
{
public:
    CTradedateSync(IAS2Context * lpContext);
    ~CTradedateSync();

protected:
    virtual bool ExpO3View2Temp(); // ��O32�������ݵ���ʱ��
    virtual bool ExpTemp2Dst(); // ����ʱ�������ݵ�Ŀ���
};


#endif /* TRADEDATE_H */
