#ifndef SJSQQZHCL_H
#define SJSQQZHCL_H

#include "DataSync.h"

// һ����ͬ��1W��
#define BATCH_ROWS 10000

// ͬ��������

class CSjsqqzhclSync : public CDataSync
{
public:
    CSjsqqzhclSync(IAS2Context * lpContext);
    ~CSjsqqzhclSync();

protected:
    virtual bool ExpO3View2Temp(); // ��O32�������ݵ���ʱ��
    virtual bool ExpTemp2Dst(); // ����ʱ�������ݵ�Ŀ���
};


#endif /* SJSQQZHCL_H */
