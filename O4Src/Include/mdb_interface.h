/*******************************************************
  Դ��������:mdb_interface.h
  �������Ȩ:�������ӹɷ����޹�˾
  ϵͳ����:  HZHSGS����ҵ�������V1.0
  ģ������:  AS�ڴ����ݿ�ģ��
  ����˵��:  �ڴ����ݿ�����ӿ�
	         �ڴ����ݿ�����ӿڣ�������
				 ר�ò�ѯ�ӿ�(�������ڴ����ݿ�������ѯ����)��
				 ���º�̨���Զ�ͬ���ӿڣ�
				 �ֹ�ͬ���ӿڣ�

  ����ĵ�:  ��Ҫ��ƽӿڲ���  
  
  ��    ��:  xiasj
  ��������:  20040211����
  ��    ע:  
          1  where �����,�������������֮�䲻���пո�.���� where stock_code='600600' ������where stock_code = '600600' 
  �޸���Ա��
  �޸����ڣ� 
  �޸�˵����
*********************************************************/

#ifndef AS_MDB_H
#define AS_MDB_H

#include <Include/plugin_interface.h>
#include <Include/resultset.h>

#define SID_MDB "com.hundsun.fbase.mdb"

/// �Զ��庯��

extern bool contains(char* arg1, char* arg2);

///�ڴ����ݿ����ӿ�
struct IMdbService:IKnown
{
	///��ͨ��ѯ
	/**
	 * ����ñ�û�����ã��򷵻�NULL
	 * ����ñ����ã���������ú����������Ӻ�̨��ȡ���
	 * ����ñ�����Ϊ���ֻ��棬��������ú����������Ӻ�̨��ȡ���
	 * ����ñ�����Ϊ�����棬��������������ӻ����ȡ���
	 * ��� szWhere="" �� szWhere=NULL �����൱���޲�ѯ����
	 * @param int session ��ѯ�Ự������������Ľӿ� getMDBSession �� �ӿں��� getSession ��ȡ
	 * @param const char * szTableName ����
	 * @param const char * szSelect �൱��SQL����е�SELECT�Ӿ䣬����SELECT�ؼ��֣����硰(PriKey, Description)"
     * @param const char * szWhere ��ѯ�������൱��SQL����е�where�Ӿ䣬����where�ؼ��֣�����"id<100"
     * @return IResultSet * �ɹ� ���ؽ����ָ�룬ʧ�� ����NULL
     */
	virtual IF2ResultSet * FUNCTION_CALL_MODE Query(int session, const char * szTableName, const char * szSelect="*", const char * szWhere="")=0; 
	///������ֵ��ѯ
	/**
	 * ����ñ�û�����ã��򷵻�NULL
	 * ����ñ����ã���������ú����������Ӻ�̨��ȡ���
	 * ����ñ�����Ϊ���ֻ��棬���ȴӻ����ȡ��������û�У����ٸ������ú����������Ӻ�̨��ȡ�������������
	 * ����ñ�����Ϊ�����棬��ӻ����ȡ
	 * @param int session ��ѯ�Ự������������Ľӿ� getMDBSession �� �ӿں��� getSession ��ȡ
	 * @param const char * szTableName ����
	 * @param const char * szSelect �൱��SQL����е�SELECT�Ӿ䣬����SELECT�ؼ��֣����硰(PriKey, Description)"
     * @param const char * szPrimeKey ����ֵ���ֶ�ֵ��ϣ�����������"PriKey=100"��"index=1 name='xiasj'")
     * @return IResultSet * �ɹ� ���ؽ����ָ�루һ����¼����ʧ�� ����NULL
     */
	virtual IF2ResultSet * FUNCTION_CALL_MODE QueryByKey(int session, const char * szTableName, const char * szSelect, const char * szPrimeKey)=0; 
	///�������ݿ��еļ�¼������ñ��棬���Զ�ͬ������
	/**
	 * @param const char * szTableName ����
	 * @param const char * szSet �൱��UPDATE����е�SET�Ӿ䣬����SET�ؼ��֣����硰id=100, age=15��
	 * @param const char * szWhere �൱��SQL����е�where�����Ӿ䣬����where�ؼ��֣����硰id<100 AND id>50 OR ...��
	 * @return int �ɹ����� 0��ʧ�ܷ��� -1
	 */
	virtual int FUNCTION_CALL_MODE Update(const char * szTableName, const char * szSet, const char * szWhere)=0;
	///ɾ�����ݿ��еļ�¼������ñ��棬���Զ�ͬ������
	/**
	 * @param const char * szTableName ����
	 * @param const char * szWhere �൱��SQL����е�where�����Ӿ䣬����where�ؼ��֣����硰id<100 AND id>50 OR ...��
	 * @return int �ɹ����� 0��ʧ�ܷ��� -1
	 */
	virtual int FUNCTION_CALL_MODE DeleteFrom(const char * szTableName, const char * szWhere)=0;
	///�����¼�����ݿ��У�����ñ��棬���Զ�ͬ������
	/**
	 * �ֶ������ֶ�ֵ����һһ��Ӧ
	 * szWhere ȱʡֵΪ""������ͬ����ʽΪ������£�Ч�ʵͣ������ szWhere ������ֵ�ַ������򻺴�ͬ����ʽΪ���ָ��£�Ч�ʸ�
	 * @param const char * szTableName ����
	 * @param const char * szColList �ֶ����б���"PriKey, Description"
	 * @param const char * szValueList �ֶ�����Ӧ���ֶ�ֵ�б���"123, 'A description of part 123.'"
	 * @param const char * szWhere ������¼������ֵ�ַ���������where�ؼ��֣����硰id=100����idΪ����
	 * @return int �ɹ����� 0��ʧ�ܷ��� -1
	 */
	virtual int FUNCTION_CALL_MODE Insert(const char * szTableName, const char * szColList, const char * szValueList, const char * szWhere="")=0;
	///ͬ�������ڴ����ݿ��еı�
	/**
	 * ���ڴ洢���̽����ֹ�ͬ������ı�
	 * @param const char * szTableName ����
	 * @param const char * szWhere �൱��SQL����е�where�����Ӿ䣬����where�ؼ��֣����硰id<100 AND id>50 OR ...��
	 * @return int �ɹ����� 0��ʧ�ܷ��� -1
	 */
	virtual int FUNCTION_CALL_MODE Sync(const char * szTableName, const char * szWhere)=0;
	///��ȡ��ѯ�Ự
	/**
	 * @return int �ɹ����� >=0��ʧ�ܷ��� -1
     */
	virtual int FUNCTION_CALL_MODE GetSession()=0; 
	///�ͷŲ�ѯ�Ự
	/**
	 * @param int session ��ѯ�Ự
	 * @return int �ɹ����� 0��ʧ�ܷ��� -1
     */
	virtual int FUNCTION_CALL_MODE FreeSession(int session)=0;
};

///���������׼�������������ܼ�����˵���μ�Include/plugin_interface.h
#ifdef __cplusplus
extern "C" {
#endif
  ///ȡ���ʵ��
  IKnown * FUNCTION_CALL_MODE GetMDBInstance();
  ///�����ʼ��
  int FUNCTION_CALL_MODE MDBInit(void * lpInstance);
  ///ȡ����������������ID��
  char *  FUNCTION_CALL_MODE GetMDBDependSvr(void * lpInstance);
  ///��ѯ������еĲ����Ϣ
  int FUNCTION_CALL_MODE GetMDBInfo(int iIndex, tagBaseServiceInfo * ppv );
#ifdef __cplusplus
}
#endif

#endif

