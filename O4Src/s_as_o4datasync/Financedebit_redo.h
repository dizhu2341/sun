/* 
 * File:   Financedebit_redo.h
 * Author: wangzh19004
 *
 * Created on 2016��11��8��, ����4:32
 */

#ifndef FINANCEDEBIT_REDO_H
#define	FINANCEDEBIT_REDO_H

#include "DataSync.h"

// һ����ͬ��1W��
#define BATCH_ROWS 10000

// ͬ��������

class CFinancedebitRedo : public CDataSync
{
public:
    CFinancedebitRedo(IAS2Context * lpContext);
    ~CFinancedebitRedo();

protected:
    virtual bool ExpO3View2Temp(); // ��O32�������ݵ���ʱ��
    virtual bool ExpTemp2Dst(); // ����ʱ�������ݵ�Ŀ���
};

#endif	/* FINANCEDEBIT_REDO_H */

