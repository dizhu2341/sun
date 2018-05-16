#ifndef __tempmdb_interface__
#define __tempmdb_interface__
#include <Include/plugin_interface.h>
///����ӿ�ID����
#define SID_TEMPMDB "com.hundsun.fbase.tempmdb"


/**@name �ڴ���ʱ����س��� */
//@{
///�ֶ�����󳤶�
const int FIELD_NAME_LENGTH	 = 256; 
///�ֶ�ֵ��󳤶�
const int FIELD_VALUE_LENGTH     = 256;  
//@}

/**@name �ڴ���ʱ��������ݽṹ */
//@{

///����������ֶε���������
typedef struct tagField
{
	///�ֶ���
    char szName[FIELD_NAME_LENGTH+1];
	///�ֶ�����
    char cType; 
    ///�ֶγ���
    int iLength;  
	///�ֶ�С��λ��
	int iScale;
	
} FIELD, * LPFIELD;

///���ֶ���ŵ��ֶ�ֵ�ṹ
typedef struct tagFieldValueNo
{
	///�ֶκ�(��0��ʼ)
	unsigned int iNo;
	///�ֶ�ֵ
	char szValue[FIELD_VALUE_LENGTH+1];
	
} FVNO, * LPFVNO;

///���ֶ������ֶ�ֵ�ṹ
typedef struct tagFieldValueName
{
	///�ֶ���
	char szName[FIELD_NAME_LENGTH+1];
	///�ֶ�ֵ
	char szValue[FIELD_VALUE_LENGTH+1];
	
} FVNAME, * LPFVNAME;

///��ʱ��ͷβ��ʶ
enum POSITION 
{
	///ͷ��
	HEAD = 0,
		///β��
		TAIL = 1
};

///����ֵ
enum result_code 
{ 
	///ִ�гɹ�
    ok						= 0,
		///������
		table_not_found			= -1,
		///Ԫ���ݸ�ʽ��һ��
		incompatible_metadata	= -2,
		///�����¼ʧ��
		insert_fail				= -3,
		///������Χ
		out_of_range			= -4,
		///����������Ϸ�
		illegal_input_para		= -5,
		///û�ҵ�
		not_found				= -6,
		///������ʧ��
		create_table_fail		= -7,
		///�ڴ����ʧ��
		alloc_memory_fail		= -8,
		///���ܱ�ʧ��
		summarize_fail			= -9
};
//@}

///�ڴ���ʱ���������ӿ�
/**
* ���������Աͨ�����ӿڴ����ڴ���ʱ�������ڴ���ʱ��(������ɨ������)
 */
struct IF2TMdbService: public IKnown
{
	///��ѯ�ڴ���ʱ��
	/**
	* Ϊ��ͳһ������Ĳ�ѯ
	*
	* ��� lRecordNo = 0 �� lRecordNo = 1 ���� *lpRecordNum = 0���򷵻ذ�������ʱ�����м�¼�Ľ����
	*
	* ���򷵻ذ��� lRecordNo ��¼�ſ�ʼ�� lRecordNum ����¼�Ľ����
	*
	* lRecordNo Խ�磬���ѯʧ�ܣ�lRecordNum ����ʵ���������򷵻ذ���ʵ�������Ľ����
	* @param unsigned long lHandle �ڴ���ʱ���� 
	* @param unsigned long lRecordNo ��ʼ��¼�ţ�ȱʡֵΪ1
	* @param unsigned long * lpRecordNum ʵ�ʷ��صļ�¼��������ȱʡֵΪ0, �����������
    * @return IF2ResultSet * �ɹ� �����ָ�룬ʧ�� NULL; �ý��������Ҫ�ͷ�
    */
	virtual IF2ResultSet * FUNCTION_CALL_MODE query(unsigned long lHandle, unsigned long lRecordNo = 1, unsigned long * lpRecordNum = 0) = 0;
	
	///׷�ӽ������ָ����ʱ��ͷ����β��
	/**
	* ׷��ǰ�����ȴ�����
	* @param unsigned long lHandle ��ʱ����
	* @param IF2ResultSet * pSet �ṹ��ָ��
	* @param POSITION pos=TAIL �����׷��λ�ã�ȱʡֵΪβ��
	* @return int �ɹ� ׷�ӵļ�¼���� >=0��ʧ�� -1
	 */
	virtual int FUNCTION_CALL_MODE appendResultSet(unsigned long lHandle, IF2ResultSet * pSet, POSITION pos=TAIL) = 0;
	
	///���ݽ���������ֶ�������Ϣ�������ڴ���ʱ��
	/**
	* ������ɺ󣬽����ݵ�����ʱ��
	* @param IResultSet * pSet �ṹ��ָ��
	* @param const char * szCreater ������������ȱʡֵΪ��
	* @return unsigned long  �ɹ� ��ʱ���� >=0��ʧ�� <0
	 */
	virtual long FUNCTION_CALL_MODE createByResultSet(IF2ResultSet * pSet, const char * szCreater="") = 0;

	///�ۺϻ��ܽ����
	/**
	* �ۺϻ���ǰ�����ȴ�����������ܵ��ֶ����ַ������ַ��������½�����е������滻
	*
	* ɨ����������ָ���ľۺ��ֶΣ��ۼ����л����ֶε�ֵ
	* @param unsigned long lHandle �ڴ���ʱ���� 
	* @param unsigned int iComNum �ۺ��ֶθ���
	* @param char * * pComFieldName �ۺ��ֶ���ָ�������׵�ַ
	* @param unsigned int iSumNum �����ֶθ���
	* @param char * * pSumFieldName �����ֶ���ָ�������׵�ַ
	* @param IF2ResultSet * pSet �ṹ��ָ��
	* @param unsigned int iTag ���ܱ�ǣ�0 �����ܣ�>=1 ����(�ڽ����������һ����������)��ȱʡ����
	* @return int �ɹ� 0��ʧ�� -1
	 */
	virtual int FUNCTION_CALL_MODE comAndSumResultSet(unsigned long	lHandle, 
													unsigned int	iComNum, 
													char **		szComFieldName,
													unsigned int	iSumNum, 
													char **		szSumFieldName, 
													IF2ResultSet *	pSet,
													unsigned int	iTag=1) = 0;

	///ɾ���ڴ���ʱ���ͷ��ڴ�ռ�
	/**
	* @param unsigned long lHandle  ��ʱ����
	* @return int  �ɹ����� 0��ʧ�ܷ��� -1
	 */
	virtual int FUNCTION_CALL_MODE drop(unsigned long lHandle) = 0;

	///ɾ��������ʱ��
	/** 
	* @return void
	 */
	virtual void FUNCTION_CALL_MODE dropAll(void) = 0;
};


///���������׼�������������ܼ�����˵���μ�Include/plugin_interface.h
#ifdef __cplusplus
extern "C" {
#endif
  ///ȡ���ʵ��
  IKnown * FUNCTION_CALL_MODE GetTempMdbInstance();
  ///�����ʼ��
  int FUNCTION_CALL_MODE TempMdbInit(void * lpInstance);
  ///ȡ����������������ID��
  char *  FUNCTION_CALL_MODE GetTempMdbDependSvr(void * lpInstance);
  ///��ѯ������еĲ����Ϣ
  int FUNCTION_CALL_MODE GetTempMdbInfo(int iIndex, tagBaseServiceInfo * ppv );
#ifdef __cplusplus
}
#endif

#endif

