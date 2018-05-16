#ifndef SYSPARAMVALUE_H
#define SYSPARAMVALUE_H

#include "DataSync.h"

// һ����ͬ��1W��
#define BATCH_ROWS 10000

// ͬ��������

class CSysparamvalueSync : public CDataSync
{
public:
    CSysparamvalueSync(IAS2Context * lpContext);
    ~CSysparamvalueSync();

protected:
    virtual bool ExpO3View2Temp(); // ��O32�������ݵ���ʱ��
    virtual bool ExpTemp2Dst(); // ����ʱ�������ݵ�Ŀ���
private:
    void ConvertStockTypeList(char StockTypeArr[4001], char StockTypeSrc[4001]);
    
};


#endif /* SYSPARAMVALUE_H */
