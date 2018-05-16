/* 
 * File:   stockbusiness_xh.h
 * Author: wangzh19004
 * 
 * Created on 2016��11��2��, ����4:13
 */

#ifndef STOCKBUSINESS_XH_H
#define	STOCKBUSINESS_XH_H

#include "DataSync.h"

// һ����ͬ��1W��
#define BATCH_ROWS 10000

class CStockBusinessXh : public CDataSync
{
    public:
        CStockBusinessXh(IAS2Context * lpContext);
        ~CStockBusinessXh();
        
    protected:
        virtual bool ExpO3View2Temp(); // ��O32�������ݵ���ʱ��
        virtual bool ExpTemp2Dst(); // ����ʱ�������ݵ�Ŀ���
};

#endif	/* STOCKBUSINESS_XH_H */

