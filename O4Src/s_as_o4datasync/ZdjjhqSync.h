#ifndef ZDJJHQ_H
#define ZDJJHQ_H

#include "DataSync.h"

// һ����ͬ��1W��
#define BATCH_ROWS 10000

// ͬ��������

class CZdjjhqSync : public CDataSync
{
public:
    CZdjjhqSync(IAS2Context * lpContext);
    ~CZdjjhqSync();

protected:
    virtual bool ExpO3View2Temp(); // ��O32�������ݵ���ʱ��
    virtual bool ExpTemp2Dst(); // ����ʱ�������ݵ�Ŀ���
};


#endif /* ZDJJHQ_H */
