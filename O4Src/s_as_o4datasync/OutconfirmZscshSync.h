#ifndef OUTCONFIRMZSCSHSYNC_H
#define	OUTCONFIRMZSCSHSYNC_H


#include "DataSync.h"

// һ����ͬ��1W��
#define BATCH_ROWS 10000

// ͬ��������

class COutconfirmZscshSync : public CDataSync
{
public:
    COutconfirmZscshSync(IAS2Context * lpContext);
    ~COutconfirmZscshSync();

protected:
    virtual bool ExpO3View2Temp(); // ��O32�������ݵ���ʱ��
    virtual bool ExpTemp2Dst(); // ����ʱ�������ݵ�Ŀ���
};



#endif	/* OUTCONFIRMZSCSHSYNC_H */

