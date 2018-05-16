/* 
 * File:   Stockbusiness_qh.h
 * Author: wangzh19004
 *
 * Created on 2016��11��3��, ����10:43
 */

#ifndef STOCKBUSINESS_QH_H
#define	STOCKBUSINESS_QH_H

#include "DataSync.h"

// һ����ͬ��1W��
#define BATCH_ROWS 10000

class CStockBusinessQh : public CDataSync
{
    public:
        CStockBusinessQh(IAS2Context * lpContext);
        ~CStockBusinessQh();
        
    protected:
        virtual bool ExpO3View2Temp(); // ��O32�������ݵ���ʱ��
        virtual bool ExpTemp2Dst(); // ����ʱ�������ݵ�Ŀ���
};

#endif	/* STOCKBUSINESS_QH_H */

