#ifndef FEEDETAILSETHS_H
#define FEEDETAILSETHS_H

#include "DataSync.h"

// һ����ͬ��1W��
#define BATCH_ROWS 10000

// ͬ��������

class CFeedetailsethsSync : public CDataSync
{
public:
    CFeedetailsethsSync(IAS2Context * lpContext);
    ~CFeedetailsethsSync();

protected:
    virtual bool ExpO3View2Temp(); // ��O32�������ݵ���ʱ��
    virtual bool ExpTemp2Dst(); // ����ʱ�������ݵ�Ŀ���
};


#endif /* FEEDETAILSETHS_H */
