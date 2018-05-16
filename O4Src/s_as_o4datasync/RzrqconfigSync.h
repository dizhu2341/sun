#ifndef RZRQCONFIG_H
#define RZRQCONFIG_H

#include "DataSync.h"

// һ����ͬ��1W��
#define BATCH_ROWS 10000

// ͬ��������

class CRzrqconfigSync : public CDataSync
{
public:
    CRzrqconfigSync(IAS2Context * lpContext);
    ~CRzrqconfigSync();

protected:
    virtual bool ExpO3View2Temp(); // ��O32�������ݵ���ʱ��
    virtual bool ExpTemp2Dst(); // ����ʱ�������ݵ�Ŀ���
};


#endif /* RZRQCONFIG_H */
