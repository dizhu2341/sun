/******************************************************************************
  Դ�ļ�����as_ResultSet.h
  �����Ȩ�����ݺ������ӹɷ����޹�˾
  ϵͳ���ƣ����ڻ�������ȫ����
  ����˵����������ӿ�
  ��    �ߣ�κ����
  ����ʱ�䣺20040223
  ��    ע��20071115 ����
  			�����������غ����������������
  �� �� �ߣ�
  �޸�ʱ�䣺
  �޸ļ�飺
********************************************************************************/
#ifndef ResultSetH
#define ResultSetH
#include <Include/plugin_interface.h>


const char HSQL_DATATYPE_STRING                  = 'S';  //��������Ϊstring C��׼���ַ��� 
const char HSQL_DATATYPE_CHAR                    = 'C';  //��������Ϊchar
const char HSQL_DATATYPE_INT                     = 'I';  //��������Ϊint
const char HSQL_DATATYPE_DOUBLE                  = 'D';  //��������ΪDOUBLE
const char HSQL_DATATYPE_BINARY                  = 'R';  //������������� 

///������ӿ�
struct IF2ResultSet : public IKnown
{

	///ȡ�ֶ���
    /**@return �����ֶ���.
      */
    virtual int FUNCTION_CALL_MODE GetColCount()=0;

    ///ȡ�ֶ���
    /** @param column:�ֶ����(��0Ϊ����)
      * @return �����ֶ���  �±�Խ�� ����NULL
      */
    virtual const char * FUNCTION_CALL_MODE GetColName(int column)=0;

    //ȡ�ֶ���������
    /** @param column:�ֶ����(��0Ϊ����)
      * @return:�����泣������;�±�Խ�� ����-1
      */
    virtual char FUNCTION_CALL_MODE GetColType(int column)=0;


   ///ȡ�������ֶ�С��λ��
   /** @param column:�ֶ����(��0Ϊ����)
     * @return int �����ֶ�����С��λ�� �±�Խ�� ����-1
     */
   virtual int FUNCTION_CALL_MODE GetColScale(int column)=0;
  
   //ȡ�ֶ����������ݵ������.
   /** @param column:�ֶ����(��0Ϊ����)
     * @return int �����ֶο�� �±�Խ�� ����-1
     */
   virtual int FUNCTION_CALL_MODE GetColWidth(int column) = 0;

   ///ȡ�ֶ�����Ӧ���ֶ����
   /**@param columnName: �ֶ���
     *@return �����ֶ����. �����ڷ���-1
     */
   virtual int  FUNCTION_CALL_MODE FindColIndex(const char * columnName)=0;

    // (2009-3-9������) ��hsdb�Ľ������ȡʱ������ǰ���ͺ󵼿ո�(��trade2.0Ҫ��)
    //
    //���ֶ����(��0Ϊ����)��ȡ�ֶ�ֵ(�ַ���)
    /**@param column:�ֶ����(��0Ϊ����)
      *@return �ַ������ֶ�ֵ,�±�Խ�緵��NULL
      */
    virtual const char *  FUNCTION_CALL_MODE GetStrByIndex(int column)=0;

    //���ֶ�����ȡ�ֶ�ֵ(�ַ���)
    /**@param columnName: �ֶ���
      *@return �ַ������ֶ�ֵ,�����ڷ���NULL
      */
    virtual const char *  FUNCTION_CALL_MODE GetStr(const char * columnName)=0;

    //���ֶ����(��0Ϊ����)��ȡ�ֶ�ֵ
    /**@param column:�ֶ����(��0Ϊ����)
      *@return �ַ����ֶ�ֵ,�±�Խ�緵��'\0'.
      */
     virtual char  FUNCTION_CALL_MODE  GetCharByIndex(int column)=0;

    //���ֶ�����ȡ�ֶ�ֵ
    /**@param columnName: �ֶ���
     *@return �ַ����ֶ�ֵ,�����ڷ���'\0'
     */
    virtual char   FUNCTION_CALL_MODE GetChar(const char * columnName)=0;

    //���ֶ���ţ�ȡ�ֶ�ֵ
    /**@param column:�ֶ����(��0Ϊ����)
      *@return double���ֶ�ֵ,�±�Խ�緵��0
      */
    virtual double  FUNCTION_CALL_MODE GetDoubleByIndex( int column)=0;
    
	///���ֶ�����ȡ�ֶ�ֵ
    /**@param columnName:�ֶ���
      *@return double���ֶ�ֵ,�����ڷ���0
      */
    virtual double  FUNCTION_CALL_MODE GetDouble(const char * columnName)=0;

    ///���ֶ���ţ�ȡ�ֶ�ֵ
    /**@param column:�ֶ����(��0Ϊ����)
      *@return int���ֶ�ֵ,�±�Խ�緵��0
	  *�����Ӧ����������char�͵ģ����ص����ַ���Ӧ��ascII�룻�����Ӧ����������string�͵ģ��ͻ�������atoi��ת��
      */
    virtual int  FUNCTION_CALL_MODE GetIntByIndex(int column)=0;

    ///���ֶ�����ȡ�ֶ�ֵ
    /**@param columnName:�ֶ���
      *@return int���ֶ�ֵ,�����ڷ���0
	  *�����Ӧ����������char�͵ģ����ص����ַ���Ӧ��ascII�룻�����Ӧ����������string�͵ģ��ͻ�������atoi��ת��
      */
    virtual int FUNCTION_CALL_MODE GetInt(const char * columnName)=0;

	///���ֶ���Ż���ֶ�ֵ,����������
	/**@param column: �ֶ����(��0Ϊ����)
	*@param   lpRawLen: [out]���ݳ���
	*@return : �����׵�ַ
	*/
	virtual void *  FUNCTION_CALL_MODE GetRawByIndex(int column,int * lpRawLen) = 0;

	///���ֶ�����ȡ�ֶ�ֵ
	/**@param columnName:�ֶ���
	*@param   lpRawLen: [out]���ݳ���
	*@return : �����׵�ַ
	*/
	virtual void *  FUNCTION_CALL_MODE GetRaw(const char * columnName,int * lpRawLen) = 0;


	///���һ��ȡ���ֶ�ֵ�Ƿ�ΪNULL
   /**@return 0 �ǣ� 1����
   */
    virtual int  FUNCTION_CALL_MODE WasNull()=0;

    ///ȡ��һ����¼
    virtual void  FUNCTION_CALL_MODE Next()=0;

    ///�ж��Ƿ�Ϊ��β
    /**@return 1 �ǣ�0 ����;
      */
    virtual int  FUNCTION_CALL_MODE IsEOF()=0;
   
	///�ж��Ƿ�Ϊ��
    /**@return 1 �ǣ�0 ����;
      */
    virtual int  FUNCTION_CALL_MODE IsEmpty()=0;
    
    virtual void * FUNCTION_CALL_MODE Destroy() = 0;
};
#endif
