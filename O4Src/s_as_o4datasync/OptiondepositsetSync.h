#ifndef OPTIONDEPOSITSET_H
#define OPTIONDEPOSITSET_H

#include "DataSync.h"

// һ����ͬ��1W��
#define BATCH_ROWS 10000

// ͬ��������

class COptiondepositsetSync : public CDataSync
{
public:
    COptiondepositsetSync(IAS2Context * lpContext);
    ~COptiondepositsetSync();

protected:
    virtual bool ExpO3View2Temp(); // ��O32�������ݵ���ʱ��
    virtual bool ExpTemp2Dst(); // ����ʱ�������ݵ�Ŀ���
};


#endif /* OPTIONDEPOSITSET_H */
