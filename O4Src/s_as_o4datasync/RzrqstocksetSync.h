#ifndef RZRQSTOCKSET_H
#define RZRQSTOCKSET_H

#include "DataSync.h"

// һ����ͬ��1W��
#define BATCH_ROWS 10000

// ͬ��������

class CRzrqstocksetSync : public CDataSync
{
public:
    CRzrqstocksetSync(IAS2Context * lpContext);
    ~CRzrqstocksetSync();

protected:
    virtual bool ExpO3View2Temp(); // ��O32�������ݵ���ʱ��
    virtual bool ExpTemp2Dst(); // ����ʱ�������ݵ�Ŀ���
};


#endif /* RZRQSTOCKSET_H */
