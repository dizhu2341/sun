#ifndef BRANCHCAPTACCTINFO_H
#define BRANCHCAPTACCTINFO_H

#include "DataSync.h"

// һ����ͬ��1W��
#define BATCH_ROWS 10000

// ͬ��������

class CBranchcaptacctinfoSync : public CDataSync
{
public:
    CBranchcaptacctinfoSync(IAS2Context * lpContext);
    ~CBranchcaptacctinfoSync();

protected:
    virtual bool ExpO3View2Temp(); // ��O32�������ݵ���ʱ��
    virtual bool ExpTemp2Dst(); // ����ʱ�������ݵ�Ŀ���
};


#endif /* BRANCHCAPTACCTINFO_H */
