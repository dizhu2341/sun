#ifndef FUTURECASH_H
#define FUTURECASH_H

#include "DataSync.h"

// һ����ͬ��1W��
#define BATCH_ROWS 10000

// ͬ��������

class CFuturecashSync : public CDataSync
{
public:
    CFuturecashSync(IAS2Context * lpContext);
    ~CFuturecashSync();

protected:
    virtual bool ExpO3View2Temp(); // ��O32�������ݵ���ʱ��
    virtual bool ExpTemp2Dst(); // ����ʱ�������ݵ�Ŀ���
};


#endif /* FUTURECASH_H */
