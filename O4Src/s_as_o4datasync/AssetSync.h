/* 
 * File:   AssetSync.h
 * Author: sunhm15168
 * Description: �ʲ���Ԫͬ����
 * Created on 2016��3��29��, ����6:28
 */

#ifndef ASSETSYNC_H
#define	ASSETSYNC_H
#include "DataSync.h"

// һ����ͬ��1W��

#define BATCH_ROWS 10000

class CAssetSync : public CDataSync

{
public:
    CAssetSync(IAS2Context * lpContext);
    ~CAssetSync();

protected:
    virtual bool ExpO3View2Temp(); // ��O32�������ݵ���ʱ��
    virtual bool ExpTemp2Dst(); // ����ʱ�������ݵ�Ŀ���
};


#endif	/* ASSETSYNC_H */

