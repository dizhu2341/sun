/*
 * DearMoneySecuritySync.h
 *
 * 
 *      Author: wangzh19004
 */

#ifndef S_AS_O4DATASYNC_DEARMONEYSECURITYSYNC_H_
#define S_AS_O4DATASYNC_DEARMONEYSECURITYSYNC_H_

#include "DataSync.h"

#define BATCH_ROWS 10000

class CDearMoneySecuritySync : public CDataSync {
public:
    CDearMoneySecuritySync(IAS2Context * lpContext);
    ~CDearMoneySecuritySync();

protected:
    virtual bool ExpO3View2Temp(); 
    virtual bool ExpTemp2Dst(); 
};

#endif /* S_AS_O4DATASYNC_DEARMONEYSECURITYSYNC_H_ */
