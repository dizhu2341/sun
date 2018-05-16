/*
 * Headfile: s_helper.h
 * Author : ��ΰ��.
 * Date   : 2008/10/20.
 * Notes  : ���ߺ���ʵ��
 * Modify : �汾       �޸�����   �޸���         �޸ĵ�       �޸�˵��
 *				  V8.0.6.0   20100614   ��Ԫ��         �ڲ�         ����ҵ����Ӫƽ̨V2.0��Ŀ2011���߽���
 *          V8.0.5.4   20110415   ������         20110415019  ���Ӻ���SynCallSubServicePack1��SubServiceCallPack1
 *          V8.0.5.2   20100702   ��ΰ��         20100702016  ������CheckDbLinkMethod���޸��޸�iSqlcode <= -25401 && iSqlcode >= -25409�ж�
 *                                                            ������GetLibVersion���޸İ汾ΪV8.0.5.2
 *          V8.0.5.1   20100630   ��ΰ��         20100630020  ������CheckDbLinkMethod���޸�SQLCODE <= -3100 and SQLCODE > -3133�ж�
 *                                                            ������GetLibVersion���޸İ汾ΪV8.0.5.1
 *          V8.0.5.0   20100414   ��ΰ��         �ڲ�         ����
 *          V8.0.4.2   20091212   ��ΰ��         �ڲ�         [SynCallSubService]�޸ĳ�ʱʱ���ԭʼ���л�ȡ,�޸�li_timeout��li_timeout���ʹ�unsigned int�޸�Ϊint
 *          V8.0.4.1   20091027   ��ΰ��         �ڲ�         �����ӷ����쳣ʱ��Proc��������쳣���ݿ��¼
 *          V8.0.4.0   20090926   ��ΰ��         �ڲ�         ����
 *          V8.0.3.2   20090924   ��ΰ��         �ڲ�         ���Ӻ���CheckDbLinkMethod
 *          V8.0.3.1   20090727   ��ΰ��         �ڲ�         AsynPostMessage�������ӽӿ�sPlugInName
 *          V8.0.3.0   20090626   ��ΰ��         �ڲ�         ���
 *          V8.0.2.0   20090420   ��ΰ��         �ڲ�         ���
 *          V8.0.1.0   20090120   ��ΰ��         �ڲ�         ���
 *          V8.0.0.0   20081014   ��ΰ��         �ڲ�         ����
 */

#ifndef s_helper_h
#define s_helper_h

#include "hshead.h"

/*==========================================================
 * Function   : PackResultSet
 * Description: �����������
 * Input      : IF2ResultSet * lpInUnPacker	�����
 * Output     : IF2Packer * lpOutPacker     ���
 * Return     : 0		    �ɹ�
 *				      <>0     ʧ�� 		
 * Author     : zhouwm
 * Date       : 2008/10/20.
 ==========================================================*/
extern int PackResultSet(IF2ResultSet * lpInUnPacker,IF2Packer * lpOutPacker);


/*==========================================================
 * Function   : MutiResultSetPack
 * Description: ���������
 * Input      : IUnPacker  lpResultSet  �����
 * Output     : IPacker    lpOutPacker  ��������
 * Return     : 0   �ɹ�
 *        <>0     ʧ��
 * Author     : zhouwm
 * Date       : 2006/08/15
 ==========================================================*/
extern int MutiResultSetPack(IF2UnPacker * lpResultSet,IF2Packer * lpOutPacker);

/*==========================================================
 * Function   : SynCallSubService
 * Description: �ӷ������
 * Input      : IASContext *pContext              �ӿ�������
 *              IF2Packer * lpReqPacker           ����ӿڰ�
 *              IESBMessage ** lppAnsMessage      ���ݰ�
 *              int iTimeOut                      ��ʱʱ��
 *              unsigned int dwFuncNo             ���ܺ�
 *              unsigned int dwBranchNo           Ӫҵ�����
 *              unsigned int dwSystemNo           ϵͳ���
 *              unsigned int dwSubSystemNo        ��ϵͳ���
 * Output     : 
 * Return     : 0 �ɹ�
 *              -1 ʧ��
 * Author     : zhouwm
 * Date       : 2008/10/20
 ==========================================================*/
extern int SynCallSubService(IAS2Context * lpContext,IF2Packer * lpReqPacker, IESBMessage ** lppAnsMessage,unsigned int iTimeOut,unsigned int dwFuncNo,unsigned int dwBranchNo,unsigned int dwSystemNo,unsigned int dwSubSystemNo,unsigned int dwBusinessNo);

/*==========================================================
 * Function   : SubServiceCall
 * Description: ԭ�ӷ��������չ
 * Input      : IASContext *pContext              �ӿ�������
 *              IF2Packer * lpReqPacker           ����ӿڰ�
 *              IF2Packer * lpOutPacker           ���ݰ�
 *              int iTimeOut                      ��ʱʱ��(Ĭ��5000ms)
 *              int iFuncNo                       ���ܺ�
 *              int iBranchNo                     Ӫҵ�����
 *              int iSystemNo                     ϵͳ���
 *              int iSubSystemNo                  ��ϵͳ���
 * Output     : 
 * Return     : 0 �ɹ�
 *              -1 ʧ��
 * Author     : zhouwm
 * Date       : 2008/10/20
 ==========================================================*/
extern int SubServiceCall(IAS2Context * lpContext,IF2UnPacker * lpInUnPacker, IF2Packer * lpOutPacker,unsigned int iTimeOut,unsigned int iFuncNo,unsigned int iBranchNo,unsigned int iSystemNo,unsigned int iSubSystemNo);

/*==========================================================
 * Function   : SubServiceCallTrans
 * Description: ����ԭ�ӷ��������չ
 * Input      : IASContext *pContext              �ӿ�������
 *              IF2Packer * lpReqPacker           ����ӿڰ�
 *              IF2Packer * lpOutPacker           ���ݰ�
 *              IAS2TM * lpTransMonitor           ����ģ����
 *              int iTimeOut                      ��ʱʱ��(Ĭ��5000ms)
 *              int iFuncNo                       ���ܺ�
 *              int iBranchNo                     Ӫҵ�����
 *              int iSystemNo                     ϵͳ���
 *              int iSubSystemNo                  ��ϵͳ���
 * Output     : 
 * Return     : 0 �ɹ�
 *              -1 ʧ��
 * Author     : zhouwm
 * Date       : 2008/10/20
 ==========================================================*/
extern int SubServiceCallTrans(IAS2Context * lpContext,IF2UnPacker * lpInUnPacker, IF2Packer * lpOutPacker,IAS2TM * lpTransMonitor,unsigned int iTimeOut,unsigned int iFuncNo,unsigned int iBranchNo,unsigned int iSystemNo,unsigned int iSubSystemNo);

/*==========================================================
 * Function   : SystemErrorPacker
 * Description: ������Ϣ������
 * Input      : IF2Packer * lpOutPacker           �����
 *              char *sError_PathInfo             ����·����Ϣ
 *              int iError_no                     �����
 *              char *sError_Info                 ������Ϣ
 * Output     : 
 * Return     : 0 �ɹ�
 *              -1 ʧ��
 * Author     : zhouwm
 * Date       : 2008/10/20
 ==========================================================*/
extern int SystemErrorPacker(IF2Packer * lpOutPacker,const char * sErrorPathInfo,int iErrorNo,const char * sErrorInfo);

/*==========================================================
 * Function   : WriteSystemLog
 * Description: ��¼ϵͳ��־
 * Input      : IASContext *pContext              �ӿ�������
 *              char *sError_PathInfo             ����·����Ϣ
 *              int iError_no                     �����
 *              char *sError_Info                 ������Ϣ
 *              int iError_id                     ϵͳ������
 *              char *sError_SysInfo              ϵͳ������Ϣ
 * Output     : 
 * Return     : 0 �ɹ�
 *              -1 ʧ��
 * Author     : zhouwm
 * Date       : 2008/10/20
 ==========================================================*/
extern int WriteSystemLog(IAS2Context * lpContext,char *sError_PathInfo,int iError_no,char *sError_Info,int iError_id,char *sError_SysInfo);

/*==========================================================
 * Function   : WriteTimeStamp
 * Description: ��¼ʱ���
 * Input      : IASContext *pContext              �ӿ�������
 *              char *sWriteSysInfo               ��¼ʱ�����Ϣ
 * Output     : 
 * Return     : 0 �ɹ�
 *              -1 ʧ��
 * Author     : zhouwm
 * Date       : 2008/10/20
 ==========================================================*/
extern int WriteTimeStamp(IAS2Context * lpContext,char *sWriteSysInfo);

/*==========================================================
 * Function   : AsynPostMessage
 * Description: �첽������Ϣ��2.0�����ͣ�
 * Input      : IASContext *pContext              �ӿ�������
 *              IF2Packer * lpOutPacker           ������Ϣ��
 *              char * sErrorPathInfo             ����·����Ϣ
 *              char * iErrorNo                   �������
 *              char * sErrorInfo                 ������Ϣ
 *              char * sTargetAr                  ·��AR
 *              char * sTransName                 ���Ϳͻ���
 *              int    iFunctionID                ���͹��ܺ�
 *              char * sPlugInName                �����
 * Output     : 
 * Return     : 0 �ɹ�
 *              -1 ʧ��
 * Author     : zhouwm
 * Date       : 2008/10/20
 ==========================================================*/
extern int AsynPostMessage(IAS2Context * lpContext,IF2UnPacker * lpInUnPacker,char * sErrorPathInfo,char * sErrorInfo,char * sTargetAr,char *sTransName,int iFunctionID,int iIssueType=0,char *sPlugInName=NULL);

/*==========================================================
 * Function   : AsynPostMessagePack1
 * Description: �첽������Ϣ��2.0��ת��1.0���ٷ��ͣ�
 * Input      : IASContext *pContext              �ӿ�������
 *              IF2Packer * lpOutPacker           ������Ϣ��
 *              char * sErrorPathInfo             ����·����Ϣ
 *              char * iErrorNo                   �������
 *              char * sErrorInfo                 ������Ϣ
 *              char * sTargetAr                  ·��AR
 *              char * sTransName                 ���Ϳͻ���
 *              int    iFunctionID                ���͹��ܺ�
 * Output     : 
 * Return     : 0 �ɹ�
 *              -1 ʧ��
 * Author     : zhouwm
 * Date       : 2008/10/20
 ==========================================================*/
extern int AsynPostMessagePack1(IAS2Context * lpContext,IF2UnPacker * lpInUnPacker,char * sErrorPathInfo,char * sErrorInfo,char * sTargetAr,char *sTransName,int iFunctionID,int iIssueType=0);


/*==========================================================
 * Function   : GetCancelSerialNo
 * Description: ȡ�м����ˮ��
 * Input      : IASContext *pContext              �ӿ�������
 *              char *sCancelSerialNo             ��ˮ��
 * Output     : 
 * Return     : 0 �ɹ�
 *              -1 ʧ��
 * Author     : zhouwm
 * Date       : 2008/10/20
 ==========================================================*/
extern int GetCancelSerialNo(IAS2Context * lpContext,char *sCancelSerialNo);


//У�����ݿ��������
//  int iDbLinkMethod ���ݿ�����ģʽ
//  int iSqlcode      SQL�������
//  �������sqlcodeΪ-28����sqlcodeΪ-1012���ߣ����ݿ�����ģʽΪselect��sqlcode���ڵ���3100��sqlcodeС��3133���򷵻�-1����Ҫ�������ݿ�����
/*==========================================================
 * Function   : CheckDbLinkMethod
 * Description: У�����ݿ��������
 * Input      : IConnection * lpConn              ���ݿ�����
 *              int iSqlcode                      SQL�������
 * Output     : 
 * Return     : 0 �ɹ�
 *              -1 ʧ��
 * Author     : zhouwm
 * Date       : 2009/09/24
 ==========================================================*/
extern int CheckDbLinkMethod(IConnection * lpConn,int iSqlcode);

/*==========================================================
 * Function   : SynCallSubServicePack1
 * Description: �ӷ���������Ϊpack1
 * Input      : IASContext *pContext              �ӿ�������
 *              IF2Packer * lpReqPacker           ����ӿڰ�
 *              IESBMessage ** lppAnsMessage      ���ݰ�
 *              int iTimeOut                      ��ʱʱ��
 *              unsigned int dwFuncNo             ���ܺ�
 *              unsigned int dwBranchNo           Ӫҵ�����
 *              unsigned int dwSystemNo           ϵͳ���
 *              unsigned int dwSubSystemNo        ��ϵͳ���
 * Output     : 
 * Return     : 0 �ɹ�
 *              -1 ʧ��
 * Author     : wangry
 * Date       : 2011/04/15
 ==========================================================*/
extern int SynCallSubServicePack1(IAS2Context * lpContext,IF2Packer * lpReqPacker, IESBMessage ** lppAnsMessage,unsigned int iTimeOut,unsigned int dwFuncNo,unsigned int dwBranchNo,unsigned int dwSystemNo,unsigned int dwSubSystemNo,unsigned int dwBusinessNo);

/*==========================================================
 * Function   : SubServiceCallPack1
 * Description: ԭ�ӷ��������չ�����ΪPack1
 * Input      : IASContext *pContext              �ӿ�������
 *              IF2Packer * lpReqPacker           ����ӿڰ�
 *              IF2Packer * lpOutPacker           ���ݰ�
 *              int iTimeOut                      ��ʱʱ��(Ĭ��5000ms)
 *              int iFuncNo                       ���ܺ�
 *              int iBranchNo                     Ӫҵ�����
 *              int iSystemNo                     ϵͳ���
 *              int iSubSystemNo                  ��ϵͳ���
 * Output     : 
 * Return     : 0 �ɹ�
 *              -1 ʧ��
 * Author     : wangry
 * Date       : 2011/04/15
 ==========================================================*/
extern int SubServiceCallPack1(IAS2Context * lpContext,IF2UnPacker * lpInUnPacker, IF2Packer * lpOutPacker,unsigned int iTimeOut,unsigned int iFuncNo,unsigned int iBranchNo,unsigned int iSystemNo,unsigned int iSubSystemNo);


#endif

