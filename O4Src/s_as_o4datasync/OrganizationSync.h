/* 
 * File:   Organization.h
 * Author: zhouyx11685
 *
 * Created on 2016��10��31��, ����9:43
 */

#ifndef ORGANIZATION_H
#define	ORGANIZATION_H

#include "DataSync.h"

// һ����ͬ��1W��
#define BATCH_ROWS 10000

// ͬ��������

class COrganizationSync : public CDataSync
{
public:
    COrganizationSync(IAS2Context * lpContext);
    ~COrganizationSync();

protected:
    virtual bool ExpO3View2Temp(); // ��O32�������ݵ���ʱ��
    virtual bool ExpTemp2Dst(); // ����ʱ�������ݵ�Ŀ���
};

#endif	/* ORGANIZATION_H */

