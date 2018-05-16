/* 
 * File:   Stockfrozendetail_qh.h
 * Author: wangzh19004
 *
 * Created on 2016��11��3��, ����5:37
 */

#ifndef STOCKFROZENDETAIL_QH_H
#define	STOCKFROZENDETAIL_QH_H

#include "DataSync.h"

// һ����ͬ��1W��
#define BATCH_ROWS 10000

class CStockFrozenDetailQh : public CDataSync
{
    public:
        CStockFrozenDetailQh(IAS2Context * lpContext);
        ~CStockFrozenDetailQh();
        
    protected:
        virtual bool ExpO3View2Temp(); // ��O32�������ݵ���ʱ��
        virtual bool ExpTemp2Dst(); // ����ʱ�������ݵ�Ŀ���
};

#endif	/* STOCKFROZENDETAIL_QH_H */

