#ifndef OUTPENDSETTLE_H
#define OUTPENDSETTLE_H

#include "DataSync.h"

// һ����ͬ��1W��
#define BATCH_ROWS 10000

// ͬ��������

class COutpendsettleSync : public CDataSync
{
public:
    COutpendsettleSync(IAS2Context * lpContext);
    ~COutpendsettleSync();

protected:
    virtual bool ExpO3View2Temp(); // ��O32�������ݵ���ʱ��
    virtual bool ExpTemp2Dst(); // ����ʱ�������ݵ�Ŀ���
};


#endif /* OUTPENDSETTLE_H */
