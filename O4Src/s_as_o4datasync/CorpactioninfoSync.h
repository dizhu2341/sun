#ifndef CORPACTIONINFO_H
#define CORPACTIONINFO_H

#include "DataSync.h"

// һ����ͬ��1W��
#define BATCH_ROWS 10000

// ͬ��������

class CCorpactioninfoSync : public CDataSync
{
public:
    CCorpactioninfoSync(IAS2Context * lpContext);
    ~CCorpactioninfoSync();

protected:
    virtual bool ExpO3View2Temp(); // ��O32�������ݵ���ʱ��
    virtual bool ExpTemp2Dst(); // ����ʱ�������ݵ�Ŀ���
};


#endif /* CORPACTIONINFO_H */
