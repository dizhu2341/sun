
#ifndef CUSTOMCLASSSYNC_H
#define	CUSTOMCLASSSYNC_H

#include "DataSync.h"

// һ����ͬ��1W��
#define BATCH_ROWS 10000

// ͬ��������

class CCustomclassSync : public CDataSync
{
public:
    CCustomclassSync(IAS2Context * lpContext);
    ~CCustomclassSync();

protected:
    virtual bool ExpO3View2Temp(); // ��O32�������ݵ���ʱ��
    virtual bool ExpTemp2Dst(); // ����ʱ�������ݵ�Ŀ���
};



#endif	/* CUSTOMCLASSSYNC_H */

