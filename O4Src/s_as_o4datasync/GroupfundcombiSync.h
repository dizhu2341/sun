#ifndef GROUPFUNDCOMBI_H
#define GROUPFUNDCOMBI_H

#include "DataSync.h"

// һ����ͬ��1W��
#define BATCH_ROWS 10000

// ͬ��������

class CGroupfundcombiSync : public CDataSync
{
public:
    CGroupfundcombiSync(IAS2Context * lpContext);
    ~CGroupfundcombiSync();

protected:
    virtual bool ExpO3View2Temp(); // ��O32�������ݵ���ʱ��
    virtual bool ExpTemp2Dst(); // ����ʱ�������ݵ�Ŀ���
};


#endif /* GROUPFUNDCOMBI_H */
