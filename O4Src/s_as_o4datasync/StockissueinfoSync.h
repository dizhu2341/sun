#ifndef STOCKISSUEINFOSYNC_H
#define	STOCKISSUEINFOSYNC_H

#include "DataSync.h"

// һ����ͬ��1W��
#define BATCH_ROWS 10000

// ͬ��������

class CStockissueinfoSync : public CDataSync
{
public:
    CStockissueinfoSync(IAS2Context * lpContext);
    ~CStockissueinfoSync();

protected:
    virtual bool ExpO3View2Temp(); // ��O32�������ݵ���ʱ��
    virtual bool ExpTemp2Dst(); // ����ʱ�������ݵ�Ŀ���
};


#endif	/* STOCKISSUEINFOSYNC_H */

