#ifndef OPTIONCOMBI_H
#define OPTIONCOMBI_H

#include "DataSync.h"

// һ����ͬ��1W��
#define BATCH_ROWS 10000

// ͬ��������

class COptioncombiSync : public CDataSync
{
public:
    COptioncombiSync(IAS2Context * lpContext);
    ~COptioncombiSync();

protected:
    virtual bool ExpO3View2Temp(); // ��O32�������ݵ���ʱ��
    virtual bool ExpTemp2Dst(); // ����ʱ�������ݵ�Ŀ���
};


#endif /* OPTIONCOMBI_H */
