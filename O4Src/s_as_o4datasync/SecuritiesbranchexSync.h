#ifndef SECURITIESBRANCHEX_H
#define SECURITIESBRANCHEX_H

#include "DataSync.h"

// һ����ͬ��1W��
#define BATCH_ROWS 10000

// ͬ��������

class CSecuritiesbranchexSync : public CDataSync
{
public:
    CSecuritiesbranchexSync(IAS2Context * lpContext);
    ~CSecuritiesbranchexSync();

protected:
    virtual bool ExpO3View2Temp(); // ��O32�������ݵ���ʱ��
    virtual bool ExpTemp2Dst(); // ����ʱ�������ݵ�Ŀ���
};


#endif /* SECURITIESBRANCHEX_H */
