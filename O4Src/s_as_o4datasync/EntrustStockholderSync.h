/* 
 * File:   EntrustStockholderSync.h
 * Author: zhouyx11685
 *
 * Created on 2016��4��5��, ����1:13
 */

#ifndef ENTRUSTSTOCKHOLDERSYNC_H
#define	ENTRUSTSTOCKHOLDERSYNC_H

#include "DataSync.h"

// һ����ͬ��1W��
#define BATCH_ROWS 10000

// ͬ��������

class CEntrustStockholderSync : public CDataSync
{
public:
    CEntrustStockholderSync(IAS2Context * lpContext);
    ~CEntrustStockholderSync();
protected:
    virtual bool ExpO3View2Temp(); // ��O32�������ݵ���ʱ��
    virtual bool ExpTemp2Dst(); // ����ʱ�������ݵ�Ŀ���
};

#endif	/* ENTRUSTSTOCKHOLDERSYNC_H */

