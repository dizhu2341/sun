#ifndef DEPT_H
#define DEPT_H

#include "DataSync.h"

// һ����ͬ��1W��
#define BATCH_ROWS 10000

// ͬ��������

class CDeptSync : public CDataSync
{
public:
    CDeptSync(IAS2Context * lpContext);
    ~CDeptSync();

protected:
    virtual bool ExpO3View2Temp(); // ��O32�������ݵ���ʱ��
    virtual bool ExpTemp2Dst(); // ����ʱ�������ݵ�Ŀ���
};


#endif /* DEPT_H */
