/* 
 * File:   arbmgr_interface.h
 * Author: wangbh
 *
 * Created on 2016��8��4��, ����3:23
 */
#ifndef ARBMGR_INTERFACE_H
#define	ARBMGR_INTERFACE_H

#define SID_ARBMGR "arbmanager_plugin_interface" 

struct IArbmgrInterface: public IKnown
{
    ///@todo���ݹ淶����ӿں��������麯�������磺
    //virtual const char * FUNCTION_CALL_MODE GetName(int iIndex) = 0;
    virtual bool FUNCTION_CALL_MODE SwitchToPrepare() = 0;
    virtual bool FUNCTION_CALL_MODE SwitchToInactive() = 0;
    virtual bool FUNCTION_CALL_MODE SwitchToSingle() = 0;
    virtual bool FUNCTION_CALL_MODE SwitchToActive() = 0;
    virtual bool FUNCTION_CALL_MODE SwitchToSeparate() = 0;
}; 

#endif	/* ARBMGR_INTERFACE_H */

