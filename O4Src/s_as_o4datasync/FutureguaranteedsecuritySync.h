#ifndef FUTUREGUARANTEEDSECURITYSYNC_H
#define	FUTUREGUARANTEEDSECURITYSYNC_H

#include "DataSync.h"

// һ����ͬ��1W��
#define BATCH_ROWS 10000

// ͬ��������

class CFutureguaranteedsecuritySync : public CDataSync
{
public:
    CFutureguaranteedsecuritySync(IAS2Context * lpContext);
    ~CFutureguaranteedsecuritySync();

protected:
    virtual bool ExpO3View2Temp(); // ��O32�������ݵ���ʱ��
    virtual bool ExpTemp2Dst(); // ����ʱ�������ݵ�Ŀ���
};



#endif	/* FUTUREGUARANTESYNC_H */

