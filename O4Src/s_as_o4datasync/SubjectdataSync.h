
#ifndef SUBJECTDATASYNC_H
#define	SUBJECTDATASYNC_H

#include "DataSync.h"

// һ����ͬ��1W��
#define BATCH_ROWS 10000

// ͬ��������

class CSubjectdataSync : public CDataSync
{
public:
    CSubjectdataSync(IAS2Context * lpContext);
    ~CSubjectdataSync();

protected:
    virtual bool ExpO3View2Temp(); // ��O32�������ݵ���ʱ��
    virtual bool ExpTemp2Dst(); // ����ʱ�������ݵ�Ŀ���

};



#endif	/* SUBJECTDATASYNC_H */

