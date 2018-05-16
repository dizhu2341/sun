#ifndef PENDSETTLE_H
#define PENDSETTLE_H

#include "DataSync.h"

// һ����ͬ��1W��
#define BATCH_ROWS 10000

// ͬ��������

class CPendsettleSync : public CDataSync
{
public:
    CPendsettleSync(IAS2Context * lpContext);
    ~CPendsettleSync();

protected:
    virtual bool ExpO3View2Temp(); // ��O32�������ݵ���ʱ��
    virtual bool ExpTemp2Dst(); // ����ʱ�������ݵ�Ŀ���
};


#endif /* PENDSETTLE_H */
