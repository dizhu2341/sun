
#ifndef TRADEFUNDSYNC_ZSCSH_H
#define	TRADEFUNDSYNC_ZSCSH_H

#include "DataSync.h"

// һ����ͬ��1W��
#define BATCH_ROWS 10000

// ͬ��������

class CTradefundZscshSync : public CDataSync
{
public:
    CTradefundZscshSync(IAS2Context * lpContext);
    ~CTradefundZscshSync();

protected:
    virtual bool ExpO3View2Temp(); // ��O32�������ݵ���ʱ��
    virtual bool ExpTemp2Dst(); // ����ʱ�������ݵ�Ŀ���
};


#endif	/* TRADEFUNDSYNC_ZSCSH_H */

