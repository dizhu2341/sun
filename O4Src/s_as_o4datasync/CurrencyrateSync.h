#ifndef CURRENCYRATE_H
#define CURRENCYRATE_H

#include "DataSync.h"

// һ����ͬ��1W��
#define BATCH_ROWS 10000

// ͬ��������

class CCurrencyrateSync : public CDataSync
{
public:
    CCurrencyrateSync(IAS2Context * lpContext);
    ~CCurrencyrateSync();

protected:
    virtual bool ExpO3View2Temp(); // ��O32�������ݵ���ʱ��
    virtual bool ExpTemp2Dst(); // ����ʱ�������ݵ�Ŀ���
};


#endif /* CURRENCYRATE_H */
