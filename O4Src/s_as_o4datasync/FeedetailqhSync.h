#ifndef FEEDETAILQH_H
#define FEEDETAILQH_H

#include "DataSync.h"

// һ����ͬ��1W��
#define BATCH_ROWS 10000

// ͬ��������

class CFeedetailqhSync : public CDataSync
{
public:
    CFeedetailqhSync(IAS2Context * lpContext);
    ~CFeedetailqhSync();

protected:
    virtual bool ExpO3View2Temp(); // ��O32�������ݵ���ʱ��
    virtual bool ExpTemp2Dst(); // ����ʱ�������ݵ�Ŀ���
};


#endif /* FEEDETAILQH_H */
