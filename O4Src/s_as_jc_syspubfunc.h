

#ifndef _S_AS_JC_SYSPUBFUNC_H
#define _S_AS_JC_SYSPUBFUNC_H

#include "hshead.h" 
//AF_����_�ڴ���ȡ
int FUNCTION_CALL_MODE F3610015(IAS2Context * lpContext,IF2UnPacker * lpInUnPacker,IF2Packer * lpOutPacker,IConnection * lpParentConn=NULL);

//AF_����_�ڴ��ͬ��
int FUNCTION_CALL_MODE F3610016(IAS2Context * lpContext,IF2UnPacker * lpInUnPacker,IF2Packer * lpOutPacker,IConnection * lpParentConn=NULL);

//AF_����_��ȡ�г��Ƿ񿪱���״̬--δ����
int FUNCTION_CALL_MODE F3610025(IAS2Context * lpContext,IF2UnPacker * lpInUnPacker,IF2Packer * lpOutPacker,IConnection * lpParentConn=NULL);

//AF_����_��ȡҵ��������Ϣ--δ����
int FUNCTION_CALL_MODE F3610060(IAS2Context * lpContext,IF2UnPacker * lpInUnPacker,IF2Packer * lpOutPacker,IConnection * lpParentConn=NULL);

//AF_����_��ȡծȯ��Ϣ
int FUNCTION_CALL_MODE F3610106(IAS2Context * lpContext,IF2UnPacker * lpInUnPacker,IF2Packer * lpOutPacker,IConnection * lpParentConn=NULL);

//AF_��������_��ȡ��������
int FUNCTION_CALL_MODE F3610602(IAS2Context * lpContext,IF2UnPacker * lpInUnPacker,IF2Packer * lpOutPacker,IConnection * lpParentConn=NULL);

//AF_��������_��ȡ�������SQL
int FUNCTION_CALL_MODE F3610601(IAS2Context * lpContext,IF2UnPacker * lpInUnPacker,IF2Packer * lpOutPacker,IConnection * lpParentConn=NULL);

//AF_����_��ȡ��˾����
int FUNCTION_CALL_MODE F3610011(IAS2Context * lpContext,IF2UnPacker * lpInUnPacker,IF2Packer * lpOutPacker,IConnection * lpParentConn=NULL);

//AF_����_��ȡ������Ϣ--δ����
int FUNCTION_CALL_MODE F3610057(IAS2Context * lpContext,IF2UnPacker * lpInUnPacker,IF2Packer * lpOutPacker,IConnection * lpParentConn=NULL);

//AF_����_��ȡ������Ϣ--δ����
int FUNCTION_CALL_MODE F3610058(IAS2Context * lpContext,IF2UnPacker * lpInUnPacker,IF2Packer * lpOutPacker,IConnection * lpParentConn=NULL);

//AF_����_��ȡ������_������--δ����
int FUNCTION_CALL_MODE F3610024(IAS2Context * lpContext,IF2UnPacker * lpInUnPacker,IF2Packer * lpOutPacker,IConnection * lpParentConn=NULL);

//AF_����_��ȡ�ֵ���������
int FUNCTION_CALL_MODE F3610105(IAS2Context * lpContext,IF2UnPacker * lpInUnPacker,IF2Packer * lpOutPacker,IConnection * lpParentConn=NULL);

//AF_����_��ȡί�з�����Ϣ
int FUNCTION_CALL_MODE F3610054(IAS2Context * lpContext,IF2UnPacker * lpInUnPacker,IF2Packer * lpOutPacker,IConnection * lpParentConn=NULL);

//AF_��������_��ȡ��ָ�ڻ���Ϣ
int FUNCTION_CALL_MODE F3610804(IAS2Context * lpContext,IF2UnPacker * lpInUnPacker,IF2Packer * lpOutPacker,IConnection * lpParentConn=NULL);

//AF_����_��ȡ�ڻ�Ʒ��--δ����
int FUNCTION_CALL_MODE F3610055(IAS2Context * lpContext,IF2UnPacker * lpInUnPacker,IF2Packer * lpOutPacker,IConnection * lpParentConn=NULL);

//AF_����_��ȡ�ع�����--δ����
int FUNCTION_CALL_MODE F3610107(IAS2Context * lpContext,IF2UnPacker * lpInUnPacker,IF2Packer * lpOutPacker,IConnection * lpParentConn=NULL);

//AF_����_��ȡ�ֲ�ϯλ
int FUNCTION_CALL_MODE F3610067(IAS2Context * lpContext,IF2UnPacker * lpInUnPacker,IF2Packer * lpOutPacker,IConnection * lpParentConn=NULL);

//AF_����_��ȡ��ʼ������
int FUNCTION_CALL_MODE F3610002(IAS2Context * lpContext,IF2UnPacker * lpInUnPacker,IF2Packer * lpOutPacker,IConnection * lpParentConn=NULL);

//AF_����_��ȡ֤ȯ����_ͨ����ع�������--δ����
int FUNCTION_CALL_MODE F3610102(IAS2Context * lpContext,IF2UnPacker * lpInUnPacker,IF2Packer * lpOutPacker,IConnection * lpParentConn=NULL);

//AF_����_��ȡǰ��ʼ������
int FUNCTION_CALL_MODE F3610003(IAS2Context * lpContext,IF2UnPacker * lpInUnPacker,IF2Packer * lpOutPacker,IConnection * lpParentConn=NULL);

//AF_����_��ȡ�����г���Ϣ--δ����
int FUNCTION_CALL_MODE F3610050(IAS2Context * lpContext,IF2UnPacker * lpInUnPacker,IF2Packer * lpOutPacker,IConnection * lpParentConn=NULL);

//AF_����_��ȡ�������
int FUNCTION_CALL_MODE F3610004(IAS2Context * lpContext,IF2UnPacker * lpInUnPacker,IF2Packer * lpOutPacker,IConnection * lpParentConn=NULL);

//AF_��������_��ȡ����Ա��Ϣ
int FUNCTION_CALL_MODE F3610818(IAS2Context * lpContext,IF2UnPacker * lpInUnPacker,IF2Packer * lpOutPacker,IConnection * lpParentConn=NULL);

//AF_����_��ȡ��С�۲���Ϣ--δ����
int FUNCTION_CALL_MODE F3610056(IAS2Context * lpContext,IF2UnPacker * lpInUnPacker,IF2Packer * lpOutPacker,IConnection * lpParentConn=NULL);

//AF_ͨ�ò�ѯ_��ȡͨ�ò�ѯ���˴�
int FUNCTION_CALL_MODE F3610502(IAS2Context * lpContext,IF2UnPacker * lpInUnPacker,IF2Packer * lpOutPacker,IConnection * lpParentConn=NULL);

//AF_ͨ�ò�ѯ_��ȡͨ�ò�ѯSQLģ��
int FUNCTION_CALL_MODE F3610501(IAS2Context * lpContext,IF2UnPacker * lpInUnPacker,IF2Packer * lpOutPacker,IConnection * lpParentConn=NULL);

//AF_��������_��ȡӪҵ����Ϣ
int FUNCTION_CALL_MODE F3610806(IAS2Context * lpContext,IF2UnPacker * lpInUnPacker,IF2Packer * lpOutPacker,IConnection * lpParentConn=NULL);

//AF_����_��ȡ֤ȯ��ҵ������
int FUNCTION_CALL_MODE F3610022(IAS2Context * lpContext,IF2UnPacker * lpInUnPacker,IF2Packer * lpOutPacker,IConnection * lpParentConn=NULL);

//AF_����_��ȡ�ɶ���Ϣ
int FUNCTION_CALL_MODE F3610065(IAS2Context * lpContext,IF2UnPacker * lpInUnPacker,IF2Packer * lpOutPacker,IConnection * lpParentConn=NULL);

//AF_����_��ȡ֤ȯ����_ͨ��֤ȯ����
int FUNCTION_CALL_MODE F3610100(IAS2Context * lpContext,IF2UnPacker * lpInUnPacker,IF2Packer * lpOutPacker,IConnection * lpParentConn=NULL);

//AF_����_��ȡ֤ȯ����_ͨ���걨������г�
int FUNCTION_CALL_MODE F3610101(IAS2Context * lpContext,IF2UnPacker * lpInUnPacker,IF2Packer * lpOutPacker,IConnection * lpParentConn=NULL);

//AF_����_��ȡ֤ȯ���--δ����
int FUNCTION_CALL_MODE F3610053(IAS2Context * lpContext,IF2UnPacker * lpInUnPacker,IF2Packer * lpOutPacker,IConnection * lpParentConn=NULL);

//AF_����_��ȡ��ϵͳ״̬
int FUNCTION_CALL_MODE F3610005(IAS2Context * lpContext,IF2UnPacker * lpInUnPacker,IF2Packer * lpOutPacker,IConnection * lpParentConn=NULL);

//AF_����_��ȡ���Ų���
int FUNCTION_CALL_MODE F3610012(IAS2Context * lpContext,IF2UnPacker * lpInUnPacker,IF2Packer * lpOutPacker,IConnection * lpParentConn=NULL);

//AF_����_��ȡϵͳ����
int FUNCTION_CALL_MODE F3610010(IAS2Context * lpContext,IF2UnPacker * lpInUnPacker,IF2Packer * lpOutPacker,IConnection * lpParentConn=NULL);

//AF_����_��ȡϵͳʱ��
int FUNCTION_CALL_MODE F3610001(IAS2Context * lpContext,IF2UnPacker * lpInUnPacker,IF2Packer * lpOutPacker,IConnection * lpParentConn=NULL);

//AF_����_��ȡ������_��Ȼ��--δ����
int FUNCTION_CALL_MODE F3610023(IAS2Context * lpContext,IF2UnPacker * lpInUnPacker,IF2Packer * lpOutPacker,IConnection * lpParentConn=NULL);

//AF_����_��ȡ�г���ʼ������
int FUNCTION_CALL_MODE F3610020(IAS2Context * lpContext,IF2UnPacker * lpInUnPacker,IF2Packer * lpOutPacker,IConnection * lpParentConn=NULL);

//AF_����_��ȡ���׶���--δ����
int FUNCTION_CALL_MODE F3610070(IAS2Context * lpContext,IF2UnPacker * lpInUnPacker,IF2Packer * lpOutPacker,IConnection * lpParentConn=NULL);

//AF_����_��ȡ����ϯλ--δ����
int FUNCTION_CALL_MODE F3610066(IAS2Context * lpContext,IF2UnPacker * lpInUnPacker,IF2Packer * lpOutPacker,IConnection * lpParentConn=NULL);

//AF_��������_��ȡ����Ա��Ϣ
int FUNCTION_CALL_MODE F3610819(IAS2Context * lpContext,IF2UnPacker * lpInUnPacker,IF2Packer * lpOutPacker,IConnection * lpParentConn=NULL);

//AF_����_�ж��Ƿ�����--δ����
int FUNCTION_CALL_MODE F3610021(IAS2Context * lpContext,IF2UnPacker * lpInUnPacker,IF2Packer * lpOutPacker,IConnection * lpParentConn=NULL);

//AF_ͨ�ò�ѯ_����ͨ�ò�ѯSQL
int FUNCTION_CALL_MODE F3610503(IAS2Context * lpContext,IF2UnPacker * lpInUnPacker,IF2Packer * lpOutPacker,IConnection * lpParentConn=NULL);

//AF_����_��ӡ������
int FUNCTION_CALL_MODE F3610999(IAS2Context * lpContext,IF2UnPacker * lpInUnPacker,IF2Packer * lpOutPacker,IConnection * lpParentConn=NULL);

//AF_����_��ת�����г�
int FUNCTION_CALL_MODE F3610006(IAS2Context * lpContext,IF2UnPacker * lpInUnPacker,IF2Packer * lpOutPacker,IConnection * lpParentConn=NULL);

//AF_����_��ȡ��Ԫ������Ϣ
int FUNCTION_CALL_MODE F3610044(IAS2Context * lpContext,IF2UnPacker * lpInUnPacker,IF2Packer * lpOutPacker,IConnection * lpParentConn=NULL);

//AF_����_��ȡ��ϻ�����Ϣ
int FUNCTION_CALL_MODE F3610045(IAS2Context * lpContext,IF2UnPacker * lpInUnPacker,IF2Packer * lpOutPacker,IConnection * lpParentConn=NULL);

//AF_����_��ȡ��˾������Ϣ--δ����
int FUNCTION_CALL_MODE F3610040(IAS2Context * lpContext,IF2UnPacker * lpInUnPacker,IF2Packer * lpOutPacker,IConnection * lpParentConn=NULL);

//AF_����_��ȡ���Ż�����Ϣ--δ����
int FUNCTION_CALL_MODE F3610041(IAS2Context * lpContext,IF2UnPacker * lpInUnPacker,IF2Packer * lpOutPacker,IConnection * lpParentConn=NULL);

//AF_����_��ȡ�˻�������Ϣ
int FUNCTION_CALL_MODE F3610043(IAS2Context * lpContext,IF2UnPacker * lpInUnPacker,IF2Packer * lpOutPacker,IConnection * lpParentConn=NULL);

#endif /* _S_AS_JC_SYSPUBFUNC_H */
