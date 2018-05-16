#ifndef RZRQCASH_ZSCSH_H
#define RZRQCASH_ZSCSH_H

#include "DataSync.h"

// һ����ͬ��1W��
#define BATCH_ROWS 10000

// ͬ��������

class CRzrqcashZscshSync : public CDataSync
{
public:
    CRzrqcashZscshSync(IAS2Context * lpContext);
    ~CRzrqcashZscshSync();

protected:
    virtual bool ExpO3View2Temp(); // ��O32�������ݵ���ʱ��
    virtual bool ExpTemp2Dst(); // ����ʱ�������ݵ�Ŀ���
};


#endif /* RZRQCASH_ZSCSH_H */
