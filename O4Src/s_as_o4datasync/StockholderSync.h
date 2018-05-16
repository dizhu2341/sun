#ifndef STOCKHOLDER_H
#define STOCKHOLDER_H

#include "DataSync.h"

// һ����ͬ��1W��
#define BATCH_ROWS 10000

// ͬ��������

class CStockholderSync : public CDataSync
{
public:
    CStockholderSync(IAS2Context * lpContext);
    ~CStockholderSync();

protected:
    virtual bool ExpO3View2Temp(); // ��O32�������ݵ���ʱ��
    virtual bool ExpTemp2Dst(); // ����ʱ�������ݵ�Ŀ���

private:
    void ConvertStockTypeList(char (*pStockTypeArr)[1025], char sStockTypeSrc[BATCH_ROWS][1025]);
};


#endif /* STOCKHOLDER_H */
