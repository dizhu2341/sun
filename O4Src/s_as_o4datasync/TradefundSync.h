
#ifndef TRADEFUNDSYNC_H
#define	TRADEFUNDSYNC_H

#include "DataSync.h"

// һ����ͬ��1W��
#define BATCH_ROWS 10000

// ͬ��������

class CTradefundSync : public CDataSync
{
public:
    CTradefundSync(IAS2Context * lpContext);
    ~CTradefundSync();

protected:
    virtual bool ExpO3View2Temp(); // ��O32�������ݵ���ʱ��
    virtual bool ExpTemp2Dst(); // ����ʱ�������ݵ�Ŀ���
};


#endif	/* TRADEFUNDSYNC_H */

