/* 
 * File:   Otcdealsettuncomp_redo.h
 * Author: wangzh19004
 *
 * Created on 2016��11��10��, ����4:28
 */

#ifndef OTCDEALSETTUNCOMP_REDO_H
#define	OTCDEALSETTUNCOMP_REDO_H

#include "DataSync.h"

// һ����ͬ��1W��
#define BATCH_ROWS 10000

// ͬ��������

class COtcdealsettuncompRedo : public CDataSync
{
public:
    COtcdealsettuncompRedo(IAS2Context * lpContext);
    ~COtcdealsettuncompRedo();

protected:
    virtual bool ExpO3View2Temp(); // ��O32�������ݵ���ʱ��
    virtual bool ExpTemp2Dst(); // ����ʱ�������ݵ�Ŀ���
};

#endif	/* OTCDEALSETTUNCOMP_REDO_H */

