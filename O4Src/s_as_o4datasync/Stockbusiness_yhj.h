/* 
 * File:   Stockbusiness_yhj.h
 * Author: wangzh19004
 *
 * Created on 2016��11��3��, ����3:10
 */

#ifndef STOCKBUSINESS_YHJ_H
#define	STOCKBUSINESS_YHJ_H

#include "DataSync.h"

// һ����ͬ��1W��
#define BATCH_ROWS 10000

class CStockBusinessYhj : public CDataSync
{
    public:
        CStockBusinessYhj(IAS2Context * lpContext);
        ~CStockBusinessYhj();
        
    protected:
        virtual bool ExpO3View2Temp(); // ��O32�������ݵ���ʱ��
        virtual bool ExpTemp2Dst(); // ����ʱ�������ݵ�Ŀ���
};

#endif	/* STOCKBUSINESS_YHJ_H */

