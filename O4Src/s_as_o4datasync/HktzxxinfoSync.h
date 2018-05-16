
#ifndef HKTZXXINFOSYNC_H
#define	HKTZXXINFOSYNC_H

#include "DataSync.h"

// һ����ͬ��1W��
#define BATCH_ROWS 10000

// ͬ��������

class CHktzxxinfoSync : public CDataSync
{
public:
    CHktzxxinfoSync(IAS2Context * lpContext);
    ~CHktzxxinfoSync();

protected:
    virtual bool ExpO3View2Temp(); // ��O32�������ݵ���ʱ��
    virtual bool ExpTemp2Dst(); // ����ʱ�������ݵ�Ŀ���
};



#endif	/* HKTZXXINFOSYNC_H */

