#ifndef FUTUREDEPOSITRATIO_H
#define FUTUREDEPOSITRATIO_H

#include "DataSync.h"

// һ����ͬ��1W��
#define BATCH_ROWS 10000

// ͬ��������

class CFuturedepositratioSync : public CDataSync
{
public:
    CFuturedepositratioSync(IAS2Context * lpContext);
    ~CFuturedepositratioSync();

protected:
    virtual bool ExpO3View2Temp(); // ��O32�������ݵ���ʱ��
    virtual bool ExpTemp2Dst(); // ����ʱ�������ݵ�Ŀ���
};


#endif /* FUTUREDEPOSITRATIO_H */
