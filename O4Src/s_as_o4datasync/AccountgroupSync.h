#ifndef ACCOUNTGROUP_H
#define ACCOUNTGROUP_H

#include "DataSync.h"

// һ����ͬ��1W��
#define BATCH_ROWS 10000

// ͬ��������

class CAccountgroupSync : public CDataSync
{
public:
    CAccountgroupSync(IAS2Context * lpContext);
    ~CAccountgroupSync();

protected:
    virtual bool ExpO3View2Temp(); // ��O32�������ݵ���ʱ��
    virtual bool ExpTemp2Dst(); // ����ʱ�������ݵ�Ŀ���
};


#endif /* ACCOUNTGROUP_H */
