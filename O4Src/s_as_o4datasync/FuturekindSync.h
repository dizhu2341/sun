#ifndef FUTUREKIND_H
#define FUTUREKIND_H

#include "DataSync.h"

// һ����ͬ��1W��
#define BATCH_ROWS 10000

// ͬ��������

class CFuturekindSync : public CDataSync
{
public:
    CFuturekindSync(IAS2Context * lpContext);
    ~CFuturekindSync();

protected:
    virtual bool ExpO3View2Temp(); // ��O32�������ݵ���ʱ��
    virtual bool ExpTemp2Dst(); // ����ʱ�������ݵ�Ŀ���
};


#endif /* FUTUREKIND_H */
