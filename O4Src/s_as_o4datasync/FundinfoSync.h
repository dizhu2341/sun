#ifndef FUNDINFO_H
#define FUNDINFO_H

#include "DataSync.h"

// һ����ͬ��1W��
#define BATCH_ROWS 10000

// ͬ��������

class CFundinfoSync : public CDataSync
{
public:
    CFundinfoSync(IAS2Context * lpContext);
    ~CFundinfoSync();

protected:
    virtual bool ExpO3View2Temp(); // ��O32�������ݵ���ʱ��
    virtual bool ExpTemp2Dst(); // ����ʱ�������ݵ�Ŀ���

private:
    void ConvertMarketNoList(char (*pMarketNoArr)[257], char sMarketNoSrc[BATCH_ROWS][257]);
};


#endif /* FUNDINFO_H */
