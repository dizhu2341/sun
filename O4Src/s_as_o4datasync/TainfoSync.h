#ifndef TAINFO_H
#define TAINFO_H

#include "DataSync.h"

// һ����ͬ��1W��
#define BATCH_ROWS 10000

// ͬ��������

class CTainfoSync : public CDataSync
{
public:
    CTainfoSync(IAS2Context * lpContext);
    ~CTainfoSync();

protected:
    virtual bool ExpO3View2Temp(); // ��O32�������ݵ���ʱ��
    virtual bool ExpTemp2Dst(); // ����ʱ�������ݵ�Ŀ���
};


#endif /* TAINFO_H */
