#ifndef FEESETPROPERTY_H
#define FEESETPROPERTY_H

#include "DataSync.h"

// һ����ͬ��1W��
#define BATCH_ROWS 10000

// ͬ��������

class CFeesetpropertySync : public CDataSync
{
public:
    CFeesetpropertySync(IAS2Context * lpContext);
    ~CFeesetpropertySync();

protected:
    virtual bool ExpO3View2Temp(); // ��O32�������ݵ���ʱ��
    virtual bool ExpTemp2Dst(); // ����ʱ�������ݵ�Ŀ���
};


#endif /* FEESETPROPERTY_H */
