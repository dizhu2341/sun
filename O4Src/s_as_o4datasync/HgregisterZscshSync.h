#ifndef HGREGISTER_ZSCSH_H
#define HGREGISTER_ZSCSH_H

#include "DataSync.h"

// һ����ͬ��1W��
#define BATCH_ROWS 10000

// ͬ��������

class CHgregisterZscshSync : public CDataSync
{
public:
    CHgregisterZscshSync(IAS2Context * lpContext);
    ~CHgregisterZscshSync();

protected:
    virtual bool ExpO3View2Temp(); // ��O32�������ݵ���ʱ��
    virtual bool ExpTemp2Dst(); // ����ʱ�������ݵ�Ŀ���
};


#endif /* HGREGISTER_ZSCSH_H */
