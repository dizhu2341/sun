#ifndef OPTIONCOMBI_REDO_H
#define OPTIONCOMBI_REDO_H

#include "DataSync.h"

// һ����ͬ��1W��
#define BATCH_ROWS 10000

// ͬ��������

class COptioncombiRedo : public CDataSync
{
public:
    COptioncombiRedo(IAS2Context * lpContext);
    ~COptioncombiRedo();

protected:
    virtual bool ExpO3View2Temp(); // ��O32�������ݵ���ʱ��
    virtual bool ExpTemp2Dst(); // ����ʱ�������ݵ�Ŀ���
};


#endif /* OPTIONCOMBI_REDO_H */
