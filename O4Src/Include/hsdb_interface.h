/*******************************************************
  Դ��������:hsdb_interface.h
  �������Ȩ:�������ӹɷ����޹�˾
  ϵͳ����:  HZHSGS���ڻ�����V2.0
  ģ������:  ͳһ���ݿ��������ӿ�
  ����˵��: 
             
           
  ����ĵ�:  ��Ҫ��ƽӿڲ���
             
  ��    ��:  zhangly
  ��������:  20080826
  ��    ע:  ƽ̨�޹أ�֧�ֶԶ������ݿ�ķ���

*********************************************************/
#ifndef HSDB_INTERFACE_H
#define HSDB_INTERFACE_H

#include <stdio.h>
#include <stdlib.h>
#include <Include/plugin_interface.h>
#include <Include/resultset.h>

#ifndef PLATFORM_EXPORT
#define PLATFORM_EXPORT
#endif

#define SID_F2HSDBSVR					"com.hundsun.fbase.hsdb"

struct IConnection;              //���ݿ����ӽӿ�
struct IStatement;               //SQL�������ӿ�
struct ICallableStatement;       //�洢���̲����ӿ�

///���ݿ�ͳһ���ʷ���
struct IHSDBService:IKnown
{
    ///��������Դ������ȡ���ݿ�����
    /**��õ�����������֮��,������� IConnection ��toFree()�����黹��������ʹ���߸���;
     *
     *������Դ�����ӳ����������Ӷ���ռ��ʱ���������������趨�ĳ�ʱʱ��������;
     *@param const char *  datasource_name  ����Դ�߼���
     *@return IConnection * ������Դ���ڲ����п�������ʱ�������Ӿ�������򷵻�NULL.
     */   
    virtual IConnection * FUNCTION_CALL_MODE getConnection(const char * datasource_name)=0;

    ///��������Դ����,����Դ���Ӳ����ö�ռʹ��(����),ֱ��ϵͳ�˳�
    /**ʹ�ñ�����ȡ�õ����ӣ��ڵ���toFree()ʱ���������ӹ黹�����ӳأ�
     *
     * ����:AS�����߳��ṩ��ȱʡ���ӣ�����ʹ�ô˷�����ȡ�ģ�ֱ��AS�ر�ʱ���ͷţ�
     *@param const char *  datasource_name  ����Դ�߼���
     *@return ���Ӷ�����
     */
    virtual  IConnection * FUNCTION_CALL_MODE getExclusiveConnection(const char * datasource_name) = 0;

};

const int HSDB_CONNECTION_STATUS_DISCONN                    = 0;//����Ϊ�Ͽ�״̬
const int HSDB_CONNECTION_STATUS_FREE                       = 1;//����Ϊ����״̬
const int HSDB_CONNECTION_STATUS_BUSY                       = 2;//����Ϊæ״̬
const int HSDB_CONNECTION_STATUS_BUSY_AND_DISCONN           = 3;//����Ϊæ���ҶϿ�״̬��

const int IAMSTATEMENTIMPL = 0;     //��ͨ���������
const int IAMCALLABLESTATEMENTIMPL = 1;//�洢�������������



///���ݿ����ӽӿ� 
struct IConnection:IKnown
{

  ///ȡ���ݿ�����״̬
  /*
  *@return HSDB_CONNECTION_STATUS_DISCONN 
  *        HSDB_CONNECTION_STATUS_FREE
  * 	   HSDB_CONNECTION_STATUS_BUSY
  *		   HSDB_CONNECTION_STATUS_BUSY_AND_DISCONN
  */  
  virtual int  FUNCTION_CALL_MODE getConnStatus(void) = 0; 

  ///ִ��һ��update,insert,delete,truncate��sql���
  /**���ִ�н���������������ͷ�
    *@param  sql: һ��update,insert,delete,truncate��sql���
    *@return 0�ɹ���1ʧ��
    */
  virtual int FUNCTION_CALL_MODE executeUpdate(char * sql) = 0;

  ///ִ��һ��select���
  /**���ִ�н����󣬻�򿪲�ռ��һ���α���Դ
   *@param   sql: һ����������ص�sql���
   *@return  :�����ָ��
   */
  virtual IF2ResultSet *  FUNCTION_CALL_MODE executeQuery(char * sql)=0;
 
  ///������ͨ�����
  /**@return ��ͨ���ӿھ�����������þ����destroy()�����ͷ���Դ���黹��ǰ����Ҳ���Զ��ͷ�);
  */ 
  virtual IStatement * FUNCTION_CALL_MODE createStatement(void) = 0;  

  ///����洢���������
  /**@return �洢�������ӿھ�����������þ����destroy()�����ͷ���Դ���黹��ǰ����Ҳ���Զ��ͷ�)
  */  
  virtual ICallableStatement * FUNCTION_CALL_MODE createCallableStatement(void) = 0;
  
  ///�黹ռ�õ�����
  /**�黹������ӻᱻ���������߸��ã��黹ʱ���ͷŴ������ϵ��������
   *@return :����NULLָ��. ����ʹ��FREE_CONNECTION()�����黹��ʹ��ǰ�����ߵ�����ָ�뱻��ΪNULL; 
   */
  virtual void * FUNCTION_CALL_MODE toFree() = 0;

  ///��ô����
  /*@return �����:
  */
  virtual int FUNCTION_CALL_MODE getErrNo() = 0;

  ///��ô�����Ϣ
  /*@return ������Ϣ.
  */
  virtual char * FUNCTION_CALL_MODE getErrInfo() = 0;

  ///��õ�ǰ���Ӷ����Ƕ��SQL�������������� sql_context
  /*@return void * �����ľ��
  */
  virtual void * FUNCTION_CALL_MODE getSQLContext() = 0;  

  ///�������ýӿ�setErrMessage������pro*c��Ƕ��ʽSQL����������SQL����֪ͨhsdb
  /*���ñ��ӿں󣬴�����Ϣ�������뵽AS��־������hsErrNo=HSDB_CONNECT_DISCONN�Ĵ���
   *������hsdb���´�ʹ������ʱ�ؽ�����,��oracle pro*C�е�SQLCODE=-28(session��ֹ)�� -1012 (û�е�¼)
   *@param int hsErrNo            HS����ţ������ǰ������Ҫ��������hsErrNo��Ϊ HSDB_CONNECT_DISCONN ��������Ϊ0
   *@param int errNo              SQL����ţ���pro*C�е�sqlca.sqlcode
   *@param const char * errInfo   SQL������Ϣ����pro*C�е�sqlca.sqlerrm.sqlerrmc
   */
  virtual void FUNCTION_CALL_MODE setErrMessage(int hsErrNo,int errNo,const char * errInfo) = 0;  

  ///��õ�ǰ���Ӷ���ķ�������
  /*@return int ��������
  */
  virtual int FUNCTION_CALL_MODE getServerType() = 0;
  
};

///���ݿ����ӿ�
/**����������У�
 * 1���޽����
 *
 *   (1)׼��             prepare("delete tab"); 
 *
 *   (2)ִ��             exec();
 *
 *   (3)���д���(ִ�з����д�)����ͨ����ǰ����ȡ������Ϣ;
 *
 *   (4)�ͷű��ӿ�       destroy();
 *
 * 2���н����
 *
 *   (1)׼��             prepare("select * from tab");
 *
 *   (2)ִ�в����ؽ���� open();
 *
 *   (3)���������(@see IResultSet),������֮���ͷŽ��������;
 *
 *   (4)���д���(���������NULL)����ͨ����ǰ����ȡ������Ϣ;
 *
 *   (5)�ͷű��ӿ�       destroy();
 */
struct IStatement:IKnown
{
  ///׼��Ҫ���õ�sql����洢�������
  /**@param  char *sql  ��׼SQL����洢�������(�μ���չ��ICallableStatement�ӿ�)
	*@return 0�ɹ���1ʧ��
	*/
  virtual int  FUNCTION_CALL_MODE prepare(char * sql) = 0;
	
  ///ִ��һ��update,insert,delete,truncate��sql���
  /**@param  sql: һ��update,insert,delete,truncate��sql���
    *@return 0�ɹ���1ʧ��
    */
  virtual int FUNCTION_CALL_MODE exec(void) = 0;

   ///ִ��һ��select���
  /**@param   sql: һ����������ص�sql���
   *@return  :�����ָ��
   */
  virtual IF2ResultSet *  FUNCTION_CALL_MODE open(void) = 0;

  ///���Ӱ��ļ�¼����
  /**@return  int ��¼��.
   */
  virtual int  FUNCTION_CALL_MODE getAffectedCount(void) = 0;

  //ȡ������
  /*@return : 0 �ɹ���1ʧ��
  */
  virtual int FUNCTION_CALL_MODE cancel() = 0;

  ///�ݻ�
  /**@return :����NULLָ��. ����ʹ�� ����statObj = statObj->destroy();
  */
  virtual void * FUNCTION_CALL_MODE destroy() = 0;

  ///��λ�ð�SQL����е�ռλ��(��չ��) 
  /**
   *@param int iIndex     Ҫ�󶨵�SQL�����ռλ������(��������0Ϊ����)
   *@param void * pData   �󶨵ı���������
   *@param int iDataLen   �󶨵ı�������������
   *@param char cDataType �󶨵ı�������,�μ�as_hsdb_const.h
   *@return  int �ɹ�Ϊ0 
   */
  //virtual int FUNCTION_CALL_MODE bindByPos(int iIndex,void * pData,int iDataLen,char cDataType) =0;
  
};


///�洢���̷��ʽӿ�
/**˵��
 *1�����෽����parameterIndex����������Ϊ1.
 *
 *2��prepare()�����е�sql��������ʽ�������¹涨 :  
 *             
 *		�����洢����û��returnֵ��Ϊ: "call storeProName(?,?,?.....)"  
 *   
 *		�����洢������returnֵ��Ϊ  : " ? = call storeProName(?,?,?.....)"
 *
 *      ÿ���ʺż�Ϊһ������ռλ��,����oracle�·��ؽ�������α����������ռλ��Լ��Ϊ���һ��������
 *
 *      ��д�洢����ʱ���齫ͬ���͵Ĳ�������һ�𣬲���������˳�����룬�������������������;
 *
 *3����������
 *   (1)׼��             prepare("call storeProName(?,?,?.....)" );
 *
 *   (2)�����������ֵ   setXXXX();
 *
 *   (3)ע���������     registerOutParameter;
 *
 *   (4)ִ��             �н����������open()��������exec();
 *
 *   (5)����н����,����open()ִ�У����ȶ�ȡ�����(@see IResultSet),������֮���ͷŽ��������;
 *
 *   (6)ȡ���������return ����ֵ,(����н�������أ������ڶ�������֮����ȡ�������);
 *
 *   (7)���д���(���������NULL)����ͨ����ǰ����ȡ������Ϣ;
 *
 *   (8)�ͷű��ӿ�       destroy();
 *
 */
struct ICallableStatement:public IStatement
{
  
	/**@name ���·����ڵ���ǰ���ø����������*/
	//@{
	    ///������ݲ���: ����  char * �� c  ���ַ�������
		/**@param int parameterIndex:   �ò�������������б��еĵ�λ��,
		  *@param char * parameterValue:  ����ֵ
		  *@return HSDB_SUCESS or  HSDB_FAILURE
		  */
		virtual int  FUNCTION_CALL_MODE setString(int parameterIndex,char * parameterValue)=0;

		///������ݲ���: ����  char
		/** 
		*@param parameterIndex: �ò�������������б��еĵ�λ��,
		*@param parameterValue: ����ֵ
		*@return HSDB_SUCESS or  HSDB_FAILURE
		*/
  		virtual int  FUNCTION_CALL_MODE setChar(int parameterIndex,char  parameterValue)=0;

		///������ݲ���: ����    Long
		/**
		*@param parameterIndex:   �ò�������������б��еĵ�λ��,
		*@param parameterValue:   ����ֵ
		*@return HSDB_SUCESS or  HSDB_FAILURE
		*/
		virtual int FUNCTION_CALL_MODE setInt(int parameterIndex,int parameterValue) = 0;

		///������ݲ���: ����    double
		/**
		*@param parameterIndex:   �ò�������������б��еĵ�λ��,
		*@param parameterValue:   ����ֵ
		*@return HSDB_SUCESS or  HSDB_FAILURE
		*/
		virtual int FUNCTION_CALL_MODE setDouble(int parameterIndex,double parameterValue) = 0;


		/// ע���������
		/** 
		*@param parameterIndex:int �������λ��
		*@param sqlType :  ���������������HSQL_DATATYPE_STRING or HSQL_DATATYPE_CHAR or HSQL_DATATYPE_LONG or HSQL_DATATYPE_DOUBLE 
		*@param scale   :  ����
		*@return HSDB_SUCESS or  HSDB_FAILURE
		*˵��: �����ķ���ֵ(return)Ҳ��ͨ���˷���ע���
		*      ��ע����return�Ժ�,��ȡ�������ʱ getXXX(1) ȡ���ı���return ֵ
		*/
  		virtual int  FUNCTION_CALL_MODE registerOutParameter(int parameterIndex,
				                          int sqlType,
					                      int scale) = 0;
	//@}


    //@name ���淽��ȡ�������,����н�������أ���Ӧ��ȡ������(�μ�IResultSet)����ȡ�������
	//@{
		///���ݲ���λ�û�ȡ���ز���ֵ ����  char * �� c  ���ַ�������
		/** 
		*@param parameterIndex:int �������λ��
		*@return :��Ӧֵ��ע�⣺ʧ��ʱ���ؿմ�""������NULL
		*/
		virtual  char *  FUNCTION_CALL_MODE getString(int parameterIndex) = 0;

		///���ݲ���λ�û�ȡ���ز���ֵ char.
		/** 
		* @param parameterIndex:int �������λ��
		* @return :��Ӧֵ ��ʧ��ʱ������0
		*/
		virtual char   FUNCTION_CALL_MODE getChar(int parameterIndex) = 0;
  
		///���ݲ���λ�û�ȡ���ز���ֵ long.
		/** 
		*@param parameterIndex:int �������λ��
		*@return :��Ӧֵ
		*/
		virtual int  FUNCTION_CALL_MODE getInt(int parameterIndex) = 0;
  
		///���ݲ���λ�û�ȡ���ز���ֵ double.
        /** 
		*@param parameterIndex:int �������λ��
		*@return : ��Ӧֵ
		*/
		virtual double FUNCTION_CALL_MODE getDouble(int parameterIndex) = 0;
	//@}

		/// ���ò���ΪNULL, Ŀǰֻ֧�ֲ������ݿ⣬���磨sql server��
		/** 
		*@param parameterIndex:int ����λ��
		*@return HSDB_SUCESS or  HSDB_FAILURE
		*/
		virtual int  FUNCTION_CALL_MODE setNULL(int parameterIndex) = 0;
    
};

//----------��Ϊ�ɶ�̬���صĻ���������������붨��������������---------

#ifdef __cplusplus
extern "C" { 
#endif

	///�����ʼ��xxxxInit()
	/**
	 *@return int �汾�� yyyymmdd��ʽ
	 */
	int  FUNCTION_CALL_MODE HSDBSvrInit(void *lpInst, PFOnSetTimeOut lpFunc= NULL);
	
	///ȡ����ӿھ�� getxxxxInstance()
	/**
	 *@return void * ���������� 
	 */
	IKnown * FUNCTION_CALL_MODE GetHSDBSvrInstance(void);

	///ȡ����ӿ���������
	/**
	 *@param iIndex 
	 *@return IKnown * ���������ʶ 
	 */
	char * FUNCTION_CALL_MODE GetHSDBSvrDependService(void *);
	
	///����ͳһ��AS�������������ѯ�ӿ� getxxxInfo()
	/**���������������̬����ʱ��ͨ�����ӿڻ��Ի�ȡ������Ϣ(����xxxxInit(),getxxxxInterface()����ָ��)
	 *@param void ** ppv    �������������Ϣ(�������)��
	 *@return ����0��ʾ�鵽��Ҫ�Ľӿڣ����򷵻ظ���
	 */
	int FUNCTION_CALL_MODE GetHSDBSvrInfo(int iIndex, tagBaseServiceInfo * ppv );

#ifdef __cplusplus
  }
#endif
 
#endif
