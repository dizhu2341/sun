#ifndef TADEALCONFIG_H
#define TADEALCONFIG_H

#include "DataSync.h"

// һ����ͬ��1W��
#define BATCH_ROWS 10000

// ͬ��������

class CTadealconfigSync : public CDataSync
{
public:
    CTadealconfigSync(IAS2Context * lpContext);
    ~CTadealconfigSync();

protected:
    virtual bool ExpO3View2Temp(); // ��O32�������ݵ���ʱ��
    virtual bool ExpTemp2Dst(); // ����ʱ�������ݵ�Ŀ���
};


#endif /* TADEALCONFIG_H */
