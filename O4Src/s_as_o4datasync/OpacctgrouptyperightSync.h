#ifndef OPACCTGROUPTYPERIGHT_H
#define OPACCTGROUPTYPERIGHT_H

#include "DataSync.h"

// һ����ͬ��1W��
#define BATCH_ROWS 10000

// ͬ��������

class COpacctgrouptyperightSync : public CDataSync
{
public:
    COpacctgrouptyperightSync(IAS2Context * lpContext);
    ~COpacctgrouptyperightSync();

protected:
    virtual bool ExpO3View2Temp(); // ��O32�������ݵ���ʱ��
    virtual bool ExpTemp2Dst(); // ����ʱ�������ݵ�Ŀ���
};


#endif /* OPACCTGROUPTYPERIGHT_H */
