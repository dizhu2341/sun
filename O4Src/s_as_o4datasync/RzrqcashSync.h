#ifndef RZRQCASH_H
#define RZRQCASH_H

#include "DataSync.h"

// һ����ͬ��1W��
#define BATCH_ROWS 10000

// ͬ��������

class CRzrqcashSync : public CDataSync
{
public:
    CRzrqcashSync(IAS2Context * lpContext);
    ~CRzrqcashSync();

protected:
    virtual bool ExpO3View2Temp(); // ��O32�������ݵ���ʱ��
    virtual bool ExpTemp2Dst(); // ����ʱ�������ݵ�Ŀ���
};


#endif /* RZRQCASH_H */
