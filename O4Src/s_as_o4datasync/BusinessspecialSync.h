
#ifndef BUSINESSSPECIALSYNC_H
#define	BUSINESSSPECIALSYNC_H

#include "DataSync.h"

// һ����ͬ��1W��
#define BATCH_ROWS 10000

// ͬ��������

class CBusinessspecialSync : public CDataSync
{
public:
    CBusinessspecialSync(IAS2Context * lpContext);
    ~CBusinessspecialSync();

protected:
    virtual bool ExpO3View2Temp(); // ��O32�������ݵ���ʱ��
    virtual bool ExpTemp2Dst(); // ����ʱ�������ݵ�Ŀ���
};




#endif	/* BUSINESSSPECIALSYNC_H */

