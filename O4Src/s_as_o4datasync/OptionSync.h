/* 
 * File:   OptionSync.h
 * Author: zhouyx11685
 * Description: ��Ȩ����ͬ����
 * Created on 2015��12��11��, ����7:44
 */

#ifndef OPTIONSYNC_H
#define	OPTIONSYNC_H

#include "DataSync.h"

// һ����ͬ��1W��
#define BATCH_ROWS 10000

// ͬ��������

class COptionSync : public CDataSync
{
public:
    COptionSync(IAS2Context * lpContext);
    ~COptionSync();
protected:
    virtual bool ExpO3View2Temp(); // ��O32�������ݵ���ʱ��
    virtual bool ExpTemp2Dst(); // ����ʱ�������ݵ�Ŀ���
};

#endif	/* OPTIONSYNC_H */

