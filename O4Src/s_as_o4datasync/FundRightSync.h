/* 
 * File:   FundRightSync.h
 * Author: zhouyx11685
 * Description: �˻�Ȩ��ͬ����
 * Created on 2015��12��16��, ����3:10
 */

#ifndef FUNDRIGHTSYNC_H
#define	FUNDRIGHTSYNC_H

#include "DataSync.h"

// һ����ͬ��1W��
#define BATCH_ROWS 50000

// ͬ��������

class CFundRightSync : public CDataSync
{
public:
    CFundRightSync(IAS2Context * lpContext);
    ~CFundRightSync();
protected:
    virtual bool ExpO3View2Temp(); // ��O32�������ݵ���ʱ��
    virtual bool ExpTemp2Dst(); // ����ʱ�������ݵ�Ŀ���
};

#endif	/* FUNDRIGHTSYNC_H */

