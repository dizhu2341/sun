#ifndef BONDPROPERTY_H
#define BONDPROPERTY_H

#include "DataSync.h"

// һ����ͬ��1W��
#define BATCH_ROWS 10000

// ͬ��������

class CBondpropertySync : public CDataSync
{
public:
    CBondpropertySync(IAS2Context * lpContext);
    ~CBondpropertySync();

protected:
    virtual bool ExpO3View2Temp(); // ��O32�������ݵ���ʱ��
    virtual bool ExpTemp2Dst(); // ����ʱ�������ݵ�Ŀ���
};


#endif /* BONDPROPERTY_H */
