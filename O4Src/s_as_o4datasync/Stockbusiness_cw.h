/* 
 * File:   Stockbusiness_cw.h
 * Author: wangzh19004
 *
 * Created on 2016��11��3��, ����11:26
 */

#ifndef STOCKBUSINESS_CW_H
#define	STOCKBUSINESS_CW_H

#include "DataSync.h"

// һ����ͬ��1W��
#define BATCH_ROWS 10000

class CStockBusinessCw : public CDataSync
{
    public:
        CStockBusinessCw(IAS2Context * lpContext);
        ~CStockBusinessCw();
        
    protected:
        virtual bool ExpO3View2Temp(); // ��O32�������ݵ���ʱ��
        virtual bool ExpTemp2Dst(); // ����ʱ�������ݵ�Ŀ���
};

#endif	/* STOCKBUSINESS_CW_H */

