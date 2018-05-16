#ifndef PENDSETTLE_ZSCSH_H
#define PENDSETTLE_ZSCSH_H

#include "DataSync.h"

// һ����ͬ��1W��
#define BATCH_ROWS 10000

// ͬ��������

class CPendsettleZscshSync : public CDataSync
{
public:
    CPendsettleZscshSync(IAS2Context * lpContext);
    ~CPendsettleZscshSync();

protected:
    virtual bool ExpO3View2Temp(); // ��O32�������ݵ���ʱ��
    virtual bool ExpTemp2Dst(); // ����ʱ�������ݵ�Ŀ���
};


#endif /* PENDSETTLE_ZSCSH_H */
