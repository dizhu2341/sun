/* 
 * File:   Otcdealsettuncomp.h
 * Author: wangzh19004
 *
 * Created on 2016��11��10��, ����3:09
 */

#ifndef OTCDEALSETTUNCOMP_H
#define	OTCDEALSETTUNCOMP_H

#include "DataSync.h"

// һ����ͬ��1W��
#define BATCH_ROWS 10000

// ͬ��������

class COtcdealsettuncomp : public CDataSync
{
public:
    COtcdealsettuncomp(IAS2Context * lpContext);
    ~COtcdealsettuncomp();

protected:
    virtual bool ExpO3View2Temp(); // ��O32�������ݵ���ʱ��
    virtual bool ExpTemp2Dst(); // ����ʱ�������ݵ�Ŀ���
};

#endif	/* OTCDEALSETTUNCOMP_H */

