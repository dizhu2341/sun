/* 
 * File:   Futurekindarbitragecombi.h
 * Author: zhouyx11685
 *
 * Created on 2016��5��24��, ����10:56
 */

#ifndef FUTUREKINDARBITRAGECOMBI_H
#define	FUTUREKINDARBITRAGECOMBI_H

#include "DataSync.h"

// һ����ͬ��1W��
#define BATCH_ROWS 10000

// ͬ��������

class CFutureKindArbitrageCombiSync : public CDataSync
{
public:
    CFutureKindArbitrageCombiSync(IAS2Context * lpContext);
    ~CFutureKindArbitrageCombiSync();

protected:
    virtual bool ExpO3View2Temp(); // ��O32�������ݵ���ʱ��
    virtual bool ExpTemp2Dst(); // ����ʱ�������ݵ�Ŀ���
};

#endif	/* FUTUREKINDARBITRAGECOMBI_H */

