/* 
 * File:   CombiSync.h
 * Author: zhouyx11685
 *
 * Created on 2016��4��1��, ����11:49
 */

#ifndef COMBISYNC_H
#define	COMBISYNC_H

#include "DataSync.h"

// һ����ͬ��1W��
#define BATCH_ROWS 10000

// ͬ��������

class CCombiSync : public CDataSync
{
public:
    CCombiSync(IAS2Context * lpContext);
    ~CCombiSync();
protected:
    virtual bool ExpO3View2Temp(); // ��O32�������ݵ���ʱ��
    virtual bool ExpTemp2Dst(); // ����ʱ�������ݵ�Ŀ���

private:
    void ConvertEntrustDirList(char (*pEntrustDirArr)[1025], char sEntrustDirSrc[BATCH_ROWS][1025]);
    void ConvertStockTypeList(char (*pStockTypeArr)[1025], char sStockTypeSrc[BATCH_ROWS][1025]);
    void ConvertMarketNoList(char (*pMarketNoArr)[257], char sMarketNoSrc[BATCH_ROWS][257]);
};

#endif	/* COMBISYNC_H */

