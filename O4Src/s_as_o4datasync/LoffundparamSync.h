#ifndef LOFFUNDPARAM_H
#define LOFFUNDPARAM_H

#include "DataSync.h"

// һ����ͬ��1W��
#define BATCH_ROWS 10000

// ͬ��������

class CLoffundparamSync : public CDataSync
{
public:
    CLoffundparamSync(IAS2Context * lpContext);
    ~CLoffundparamSync();

protected:
    virtual bool ExpO3View2Temp(); // ��O32�������ݵ���ʱ��
    virtual bool ExpTemp2Dst(); // ����ʱ�������ݵ�Ŀ���
};


#endif /* LOFFUNDPARAM_H */
