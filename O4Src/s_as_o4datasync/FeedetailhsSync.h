#ifndef FEEDETAILHS_H
#define FEEDETAILHS_H

#include "DataSync.h"

// һ����ͬ��1W��
#define BATCH_ROWS 10000

// ͬ��������

class CFeedetailhsSync : public CDataSync
{
public:
    CFeedetailhsSync(IAS2Context * lpContext);
    ~CFeedetailhsSync();

protected:
    virtual bool ExpO3View2Temp(); // ��O32�������ݵ���ʱ��
    virtual bool ExpTemp2Dst(); // ����ʱ�������ݵ�Ŀ���
};


#endif /* FEEDETAILHS_H */
