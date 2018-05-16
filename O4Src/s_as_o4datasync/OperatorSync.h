#ifndef OPERATOR_H
#define OPERATOR_H

#include "DataSync.h"

// һ����ͬ��1W��
#define BATCH_ROWS 10000

// ͬ��������

class COperatorSync : public CDataSync
{
public:
    COperatorSync(IAS2Context * lpContext);
    ~COperatorSync();

protected:
    virtual bool ExpO3View2Temp(); // ��O32�������ݵ���ʱ��
    virtual bool ExpTemp2Dst(); // ����ʱ�������ݵ�Ŀ���
private:
    void ConvertStockTypeList(char (*pStockTypeArr)[1025], char sStockTypeSrc[BATCH_ROWS][1025]);
};


#endif /* OPERATOR_H */
