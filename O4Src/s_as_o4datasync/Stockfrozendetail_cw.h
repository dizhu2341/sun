/* 
 * File:   Stockfrozendetail_cw.h
 * Author: wangzh19004
 *
 * Created on 2016��11��3��, ����7:26
 */

#ifndef STOCKFROZENDETAIL_CW_H
#define	STOCKFROZENDETAIL_CW_H

#include "DataSync.h"

// һ����ͬ��1W��
#define BATCH_ROWS 10000

class CStockFrozenDetailCw : public CDataSync
{
    public:
        CStockFrozenDetailCw(IAS2Context * lpContext);
        ~CStockFrozenDetailCw();
        
    protected:
        virtual bool ExpO3View2Temp(); // ��O32�������ݵ���ʱ��
        virtual bool ExpTemp2Dst(); // ����ʱ�������ݵ�Ŀ���
};

#endif	/* STOCKFROZENDETAIL_CW_H */

