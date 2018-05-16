/* 
 * File:   subject_stock.h
 * Author: wangzh19004
 *
 * Created on 2016��11��9��, ����10:13
 */

#ifndef SUBJECT_STOCK_H
#define	SUBJECT_STOCK_H

#include "DataSync.h"

// һ����ͬ��1W��
#define BATCH_ROWS 10000

// ͬ��������

class CSubjectStock : public CDataSync
{
public:
    CSubjectStock(IAS2Context * lpContext);
    ~CSubjectStock();

protected:
    virtual bool ExpO3View2Temp(); // ��O32�������ݵ���ʱ��
    virtual bool ExpTemp2Dst(); // ����ʱ�������ݵ�Ŀ���
};

#endif	/* SUBJECT_STOCK_H */

