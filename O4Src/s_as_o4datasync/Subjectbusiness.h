/* 
 * File:   Subjectbusiness.h
 * Author: wangzh19004
 *
 * Created on 2016��11��9��, ����9:04
 */

#ifndef SUBJECTBUSINESS_H
#define	SUBJECTBUSINESS_H

#include "DataSync.h"

// һ����ͬ��1W��
#define BATCH_ROWS 10000

// ͬ��������
class CSubjectBusiness : public CDataSync
{
public:
    CSubjectBusiness(IAS2Context * lpContext);
    ~CSubjectBusiness();

protected:
    virtual bool ExpO3View2Temp(); // ��O32�������ݵ���ʱ��
    virtual bool ExpTemp2Dst(); // ����ʱ�������ݵ�Ŀ���
};

#endif	/* SUBJECTBUSINESS_H */

