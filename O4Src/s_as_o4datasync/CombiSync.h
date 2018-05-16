/* 
 * File:   CombiSync.h
 * Author: zhouyx11685
 *
 * Created on 2016年4月1日, 上午11:49
 */

#ifndef COMBISYNC_H
#define	COMBISYNC_H

#include "DataSync.h"

// 一批次同步1W行
#define BATCH_ROWS 10000

// 同步处理类

class CCombiSync : public CDataSync
{
public:
    CCombiSync(IAS2Context * lpContext);
    ~CCombiSync();
protected:
    virtual bool ExpO3View2Temp(); // 从O32表导入数据到临时表
    virtual bool ExpTemp2Dst(); // 从临时表导入数据到目标表

private:
    void ConvertEntrustDirList(char (*pEntrustDirArr)[1025], char sEntrustDirSrc[BATCH_ROWS][1025]);
    void ConvertStockTypeList(char (*pStockTypeArr)[1025], char sStockTypeSrc[BATCH_ROWS][1025]);
    void ConvertMarketNoList(char (*pMarketNoArr)[257], char sMarketNoSrc[BATCH_ROWS][257]);
};

#endif	/* COMBISYNC_H */

