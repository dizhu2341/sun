#ifndef FTRENABLEDETAIL_H
#define FTRENABLEDETAIL_H

#include "DataSync.h"

// һ����ͬ��1W��
#define BATCH_ROWS 10000

// ͬ��������

class CFtrenabledetailSync : public CDataSync
{
public:
    CFtrenabledetailSync(IAS2Context * lpContext);
    ~CFtrenabledetailSync();

protected:
    virtual bool ExpO3View2Temp(); // ��O32�������ݵ���ʱ��
    virtual bool ExpTemp2Dst(); // ����ʱ�������ݵ�Ŀ���
};


#endif /* FTRENABLEDETAIL_H */
