#ifndef FUTUREARBITRAGEINFO_H
#define FUTUREARBITRAGEINFO_H

#include "DataSync.h"

// һ����ͬ��1W��
#define BATCH_ROWS 10000

// ͬ��������

class CFuturearbitrageinfoSync : public CDataSync
{
public:
    CFuturearbitrageinfoSync(IAS2Context * lpContext);
    ~CFuturearbitrageinfoSync();

protected:
    virtual bool ExpO3View2Temp(); // ��O32�������ݵ���ʱ��
    virtual bool ExpTemp2Dst(); // ����ʱ�������ݵ�Ŀ���
};


#endif /* FUTUREARBITRAGEINFO_H */
