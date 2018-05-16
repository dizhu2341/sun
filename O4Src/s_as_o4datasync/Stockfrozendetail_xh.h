/* 
 * File:   Stockfrozendetail_xh.h
 * Author: wangzh19004
 *
 * Created on 2016��11��3��, ����3:52
 */

#ifndef STOCKFROZENDETAIL_XH_H
#define	STOCKFROZENDETAIL_XH_H

#include "DataSync.h"

// һ����ͬ��1W��
#define BATCH_ROWS 10000

class CStockFrozenDetailXh : public CDataSync
{
    public:
        CStockFrozenDetailXh(IAS2Context * lpContext);
        ~CStockFrozenDetailXh();
        
    protected:
        virtual bool ExpO3View2Temp(); // ��O32�������ݵ���ʱ��
        virtual bool ExpTemp2Dst(); // ����ʱ�������ݵ�Ŀ���
};

#endif	/* STOCKFROZENDETAIL_XH_H */

