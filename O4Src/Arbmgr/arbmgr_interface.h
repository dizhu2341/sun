/* 
 * File:   arbmgr_interface.h
 * Author: wangbh
 *
 * Created on 2016年8月4日, 下午3:23
 */
#ifndef ARBMGR_INTERFACE_H
#define	ARBMGR_INTERFACE_H

#define SID_ARBMGR "arbmanager_plugin_interface" 

struct IArbmgrInterface: public IKnown
{
    ///@todo根据规范定义接口函数，纯虚函数，例如：
    //virtual const char * FUNCTION_CALL_MODE GetName(int iIndex) = 0;
    virtual bool FUNCTION_CALL_MODE SwitchToPrepare() = 0;
    virtual bool FUNCTION_CALL_MODE SwitchToInactive() = 0;
    virtual bool FUNCTION_CALL_MODE SwitchToSingle() = 0;
    virtual bool FUNCTION_CALL_MODE SwitchToActive() = 0;
    virtual bool FUNCTION_CALL_MODE SwitchToSeparate() = 0;
}; 

#endif	/* ARBMGR_INTERFACE_H */

