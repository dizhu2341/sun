#ifndef ACCOUNTGROUPTYPE_H
#define ACCOUNTGROUPTYPE_H

#include "DataSync.h"

// һ����ͬ��1W��
#define BATCH_ROWS 10000

// ͬ��������

class CAccountgrouptypeSync : public CDataSync
{
public:
    CAccountgrouptypeSync(IAS2Context * lpContext);
    ~CAccountgrouptypeSync();

protected:
    virtual bool ExpO3View2Temp(); // ��O32�������ݵ���ʱ��
    virtual bool ExpTemp2Dst(); // ����ʱ�������ݵ�Ŀ���
};


#endif /* ACCOUNTGROUPTYPE_H */
