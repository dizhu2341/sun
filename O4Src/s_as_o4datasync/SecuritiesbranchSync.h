#ifndef SECURITIESBRANCH_H
#define SECURITIESBRANCH_H

#include "DataSync.h"

// һ����ͬ��1W��
#define BATCH_ROWS 10000

// ͬ��������

class CSecuritiesbranchSync : public CDataSync
{
public:
    CSecuritiesbranchSync(IAS2Context * lpContext);
    ~CSecuritiesbranchSync();

protected:
    virtual bool ExpO3View2Temp(); // ��O32�������ݵ���ʱ��
    virtual bool ExpTemp2Dst(); // ����ʱ�������ݵ�Ŀ���
private:
    void ConvertEntrustDirList(char (*pEntrustDirArr)[1025], char sEntrustDirSrc[BATCH_ROWS][1025]);
};


#endif /* SECURITIESBRANCH_H */
