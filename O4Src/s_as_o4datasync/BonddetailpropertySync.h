#ifndef BONDDETAILPROPERTY_H
#define BONDDETAILPROPERTY_H

#include "DataSync.h"

// һ����ͬ��1W��
#define BATCH_ROWS 10000

// ͬ��������

class CBonddetailpropertySync : public CDataSync
{
public:
    CBonddetailpropertySync(IAS2Context * lpContext);
    ~CBonddetailpropertySync();

protected:
    virtual bool ExpO3View2Temp(); // ��O32�������ݵ���ʱ��
    virtual bool ExpTemp2Dst(); // ����ʱ�������ݵ�Ŀ���
};


#endif /* BONDDETAILPROPERTY_H */
