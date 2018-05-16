/* 
 * File:   FuturesInfoSync.h
 * Author: sunhm15168
 * Description: �ڻ���Ϣͬ��
 * Created on 2016��2��16��, ����9:45
 */

#ifndef FUTURESINFOSYNC_H
#define	FUTURESINFOSYNC_H
#include "DataSync.h"

// һ����ͬ��1W��
#define BATCH_ROWS 10000

// ͬ��������

class CFuturesInfoSync : public CDataSync
{
public:
    CFuturesInfoSync(IAS2Context * lpContext);
    ~CFuturesInfoSync();
protected:
    virtual bool ExpO3View2Temp(); // ��O32�������ݵ���ʱ��
    virtual bool ExpTemp2Dst(); // ����ʱ�������ݵ�Ŀ���
};


#endif	/* FUTURESINFOSYNC_H */

