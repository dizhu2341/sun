#ifndef  SZFUNDESTIMATE_H
#define  SZFUNDESTIMATE_H

#include "DataSync.h"

// һ����ͬ��1W��
#define BATCH_ROWS 10000

// ͬ��������

class CSzfundestimateSync : public CDataSync
{
public:
    CSzfundestimateSync(IAS2Context * lpContext);
    ~CSzfundestimateSync();

protected:
    virtual bool ExpO3View2Temp(); // ��O32�������ݵ���ʱ��
    virtual bool ExpTemp2Dst(); // ����ʱ�������ݵ�Ŀ���
};


#endif /* UNITSTOCK_H */
