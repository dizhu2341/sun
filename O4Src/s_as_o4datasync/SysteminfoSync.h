#ifndef SYSTEMINFO_H
#define SYSTEMINFO_H

#include "DataSync.h"

// һ����ͬ��1W��
#define BATCH_ROWS 10000

// ͬ��������

class CSysteminfoSync : public CDataSync
{
public:
    CSysteminfoSync(IAS2Context * lpContext);
    ~CSysteminfoSync();

protected:
    virtual bool ExpO3View2Temp(); // ��O32�������ݵ���ʱ��
    virtual bool ExpTemp2Dst(); // ����ʱ�������ݵ�Ŀ���
};


#endif /* SYSTEMINFO_H */
