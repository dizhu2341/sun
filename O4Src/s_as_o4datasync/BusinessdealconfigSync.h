#ifndef BUSINESSDEALCONFIG_H
#define BUSINESSDEALCONFIG_H

#include "DataSync.h"

// һ����ͬ��1W��
#define BATCH_ROWS 10000

// ͬ��������

class CBusinessdealconfigSync : public CDataSync
{
public:
    CBusinessdealconfigSync(IAS2Context * lpContext);
    ~CBusinessdealconfigSync();

protected:
    virtual bool ExpO3View2Temp(); // ��O32�������ݵ���ʱ��
    virtual bool ExpTemp2Dst(); // ����ʱ�������ݵ�Ŀ���
};


#endif /* BUSINESSDEALCONFIG_H */
