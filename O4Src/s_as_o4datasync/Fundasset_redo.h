/* 
 * File:   Fundasset_redo.h
 * Author: wangzh19004
 *
 * Created on 2016��11��8��, ����7:43
 */

#ifndef FUNDASSET_REDO_H
#define	FUNDASSET_REDO_H

#include "DataSync.h"

// һ����ͬ��1W��
#define BATCH_ROWS 10000

// ͬ��������

class CFundassetRedo : public CDataSync
{
public:
    CFundassetRedo(IAS2Context * lpContext);
    ~CFundassetRedo();

protected:
    virtual bool ExpO3View2Temp(); // ��O32�������ݵ���ʱ��
    virtual bool ExpTemp2Dst(); // ����ʱ�������ݵ�Ŀ���
};

#endif	/* FUNDASSET_REDO_H */

