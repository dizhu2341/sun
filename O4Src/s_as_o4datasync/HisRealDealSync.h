/* 
 * File:   HisRealDealSync.h
 * Author: zhouyx11685
 *
 * Created on 2016��11��3��, ����7:26
 */

#ifndef HISREALDEALSYNC_H
#define	HISREALDEALSYNC_H


#include "DataSync.h"

// һ����ͬ��1W��
#define BATCH_ROWS 10000

// ͬ��������

class CHisRealDealSync : public CDataSync
{
public:
    CHisRealDealSync(IAS2Context * lpContext);
    ~CHisRealDealSync();

protected:
    virtual bool ExpO3View2Temp(); // ��O32�������ݵ���ʱ��
    virtual bool ExpTemp2Dst(); // ����ʱ�������ݵ�Ŀ���
};

#endif	/* HISREALDEALSYNC_H */

