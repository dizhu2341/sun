/* 
 * File:   Bankuncomplete.h
 * Author: wangzh19004
 *
 * Created on 2016��11��8��, ����8:27
 */

#ifndef BANKUNCOMPLETE_H
#define	BANKUNCOMPLETE_H

#include "DataSync.h"

// һ����ͬ��1W��
#define BATCH_ROWS 10000

// ͬ��������

class CBankUncomplete : public CDataSync
{
public:
    CBankUncomplete(IAS2Context * lpContext);
    ~CBankUncomplete();

protected:
    virtual bool ExpO3View2Temp(); // ��O32�������ݵ���ʱ��
    virtual bool ExpTemp2Dst(); // ����ʱ�������ݵ�Ŀ���
};

#endif	/* BANKUNCOMPLETE_H */

