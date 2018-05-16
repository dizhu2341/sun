#ifndef FUTURECASH_ZSCSH_H
#define FUTURECASH_ZSCSH_H

#include "DataSync.h"

// һ����ͬ��1W��
#define BATCH_ROWS 10000

// ͬ��������

class CFuturecashZscshSync : public CDataSync
{
public:
    CFuturecashZscshSync(IAS2Context * lpContext);
    ~CFuturecashZscshSync();

protected:
    virtual bool ExpO3View2Temp(); // ��O32�������ݵ���ʱ��
    virtual bool ExpTemp2Dst(); // ����ʱ�������ݵ�Ŀ���
};


#endif /* FUTURECASH_ZSCSH_H */
