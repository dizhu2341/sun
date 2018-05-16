/* 
 * File:   Mortgageinfo_redo.h
 * Author: wangzh19004
 *
 * Created on 2016��11��9��, ����10:02
 */

#ifndef MORTGAGEINFO_REDO_H
#define	MORTGAGEINFO_REDO_H

#include "DataSync.h"

// һ����ͬ��1W��
#define BATCH_ROWS 10000

// ͬ��������

class CMortGageInfoRedo : public CDataSync
{
public:
    CMortGageInfoRedo(IAS2Context * lpContext);
    ~CMortGageInfoRedo();

protected:
    virtual bool ExpO3View2Temp(); // ��O32�������ݵ���ʱ��
    virtual bool ExpTemp2Dst(); // ����ʱ�������ݵ�Ŀ���
};

#endif	/* MORTGAGEINFO_REDO_H */

