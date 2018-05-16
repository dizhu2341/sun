/* 
 * File:   Subjectstock_redo.h
 * Author: wangzh19004
 *
 * Created on 2016��11��9��, ����3:30
 */

#ifndef SUBJECTSTOCK_REDO_H
#define	SUBJECTSTOCK_REDO_H

#include "DataSync.h"

// һ����ͬ��1W��
#define BATCH_ROWS 10000

// ͬ��������

class CSubjectStockRedo : public CDataSync
{
public:
    CSubjectStockRedo(IAS2Context * lpContext);
    ~CSubjectStockRedo();

protected:
    virtual bool ExpO3View2Temp(); // ��O32�������ݵ���ʱ��
    virtual bool ExpTemp2Dst(); // ����ʱ�������ݵ�Ŀ���
};

#endif	/* SUBJECTSTOCK_REDO_H */

