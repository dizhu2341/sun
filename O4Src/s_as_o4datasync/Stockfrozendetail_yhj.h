/* 
 * File:   Stockfrozendetail_yhj.h
 * Author: wangzh19004
 *
 * Created on 2016��11��3��, ����7:43
 */

#ifndef STOCKFROZENDETAIL_YHJ_H
#define	STOCKFROZENDETAIL_YHJ_H

#include "DataSync.h"

// һ����ͬ��1W��
#define BATCH_ROWS 10000

class CStockFrozenDetailYhj : public CDataSync
{
    public:
        CStockFrozenDetailYhj(IAS2Context * lpContext);
        ~CStockFrozenDetailYhj();
        
    protected:
        virtual bool ExpO3View2Temp(); // ��O32�������ݵ���ʱ��
        virtual bool ExpTemp2Dst(); // ����ʱ�������ݵ�Ŀ���
};

#endif	/* STOCKFROZENDETAIL_YHJ_H */

