#ifndef TRADEFEECONFIGHS_H
#define TRADEFEECONFIGHS_H

#include "DataSync.h"

// һ����ͬ��1W��
#define BATCH_ROWS 10000

// ͬ��������

class CTradefeeconfighsSync : public CDataSync
{
public:
    CTradefeeconfighsSync(IAS2Context * lpContext);
    ~CTradefeeconfighsSync();

protected:
    virtual bool ExpO3View2Temp(); // ��O32�������ݵ���ʱ��
    virtual bool ExpTemp2Dst(); // ����ʱ�������ݵ�Ŀ���
};


#endif /* TRADEFEECONFIGHS_H */
