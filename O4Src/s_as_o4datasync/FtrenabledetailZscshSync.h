#ifndef FTRENABLEDETAIL_ZSCSH_H
#define FTRENABLEDETAIL_ZSCSH_H

#include "DataSync.h"

// һ����ͬ��1W��
#define BATCH_ROWS 10000

// ͬ��������

class CFtrenabledetailZscshSync : public CDataSync
{
public:
    CFtrenabledetailZscshSync(IAS2Context * lpContext);
    ~CFtrenabledetailZscshSync();

protected:
    virtual bool ExpO3View2Temp(); // ��O32�������ݵ���ʱ��
    virtual bool ExpTemp2Dst(); // ����ʱ�������ݵ�Ŀ���
};


#endif /* FTRENABLEDETAIL_ZSCSH_H */
