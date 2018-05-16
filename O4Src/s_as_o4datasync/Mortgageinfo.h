/* 
 * File:   Mortgageinfo.h
 * Author: wangzh19004
 *
 * Created on 2016��11��9��, ����9:32
 */

#ifndef MORTGAGEINFO_H
#define	MORTGAGEINFO_H

#include "DataSync.h"

// һ����ͬ��1W��
#define BATCH_ROWS 10000

// ͬ��������

class CMortGageInfo : public CDataSync
{
public:
    CMortGageInfo(IAS2Context * lpContext);
    ~CMortGageInfo();

protected:
    virtual bool ExpO3View2Temp(); // ��O32�������ݵ���ʱ��
    virtual bool ExpTemp2Dst(); // ����ʱ�������ݵ�Ŀ���
};

#endif	/* MORTGAGEINFO_H */

