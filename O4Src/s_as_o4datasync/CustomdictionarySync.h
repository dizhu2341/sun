
#ifndef CUSTOMDICTIONARYSYNC_H
#define	CUSTOMDICTIONARYSYNC_H

#include "DataSync.h"

// һ����ͬ��1W��
#define BATCH_ROWS 10000

// ͬ��������

class CCustomdictionarySync : public CDataSync
{
public:
    CCustomdictionarySync(IAS2Context * lpContext);
    ~CCustomdictionarySync();

protected:
    virtual bool ExpO3View2Temp(); // ��O32�������ݵ���ʱ��
    virtual bool ExpTemp2Dst(); // ����ʱ�������ݵ�Ŀ���
};



#endif	/* CUSTOMDICTIONARYSYNC_H */

