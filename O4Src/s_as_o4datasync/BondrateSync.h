#ifndef BONDRATE_H
#define BONDRATE_H

#include "DataSync.h"

// һ����ͬ��1W��
#define BATCH_ROWS 10000

// ͬ��������

class CBondrateSync : public CDataSync
{
public:
    CBondrateSync(IAS2Context * lpContext);
    ~CBondrateSync();

protected:
    virtual bool ExpO3View2Temp(); // ��O32�������ݵ���ʱ��
    virtual bool ExpTemp2Dst(); // ����ʱ�������ݵ�Ŀ���
};


#endif /* BONDRATE_H */
