
#ifndef INVESTFUNDINFOSYNC_H
#define	INVESTFUNDINFOSYNC_H

#include "DataSync.h"

// һ����ͬ��1W��
#define BATCH_ROWS 10000

// ͬ��������

class CInvestfundinfoSync : public CDataSync
{
public:
    CInvestfundinfoSync(IAS2Context * lpContext);
    ~CInvestfundinfoSync();

protected:
    virtual bool ExpO3View2Temp(); // ��O32�������ݵ���ʱ��
    virtual bool ExpTemp2Dst(); // ����ʱ�������ݵ�Ŀ���
};


#endif /* INVESTFUNDINFOSYNC_H */
