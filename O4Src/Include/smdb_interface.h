#ifndef __smdb_interface__
#define __smdb_interface__
#include <Include/plugin_interface.h>
#include <Include/biz_comp_interface.h>
#include <Include/pack_interface.h>
///����ӿ�ID����
#define SID_SMDB "com.hundsun.fbase.smdb"


///���������׼�������������ܼ�����˵���μ�Include/plugin_interface.h
#ifdef __cplusplus
extern "C" {
#endif
  ///ȡ���ʵ��
  IKnown * FUNCTION_CALL_MODE GetsmdbInstance();
  ///�����ʼ��
  int FUNCTION_CALL_MODE smdbInit(void * lpInstance);
  ///ȡ����������������ID��
  char *  FUNCTION_CALL_MODE GetsmdbDependSvr(void * lpInstance);
  ///��ѯ������еĲ����Ϣ
  int FUNCTION_CALL_MODE GetsmdbInfo(int iIndex, tagBaseServiceInfo * ppv );
#ifdef __cplusplus
}
#endif

///�˽ṹ���ڱ�ʾ���е�key��valueֵ
typedef struct  tagDataNode 
{
	void * lpData;           //����ָ��
	unsigned int  iDataLen;  //���ݳ���
}DATA, * LPDATA;

#define INTDATA(var,data)   DATA var ={&data,sizeof(int)}

#define STRDATA(var,data)   DATA var ={(void *)data, strlen(data)} 

#define INT_KEY  'I'
#define STR_KEY  'S'

///�ڴ��ӿ�
/**ά�������ڴ��¼��key-value�ԣ������м�¼keyֵΨһ.
* д����ʱ����¼����ɾ����keyֵ�����޸�
* 
*/

///����ӿڶ���
struct ISMDBTable: public IKnown
{
	///�ͷ��Լ�
	virtual void FUNCTION_CALL_MODE Destroy(void)=0;

	///������ȡһ����¼(���������������ʱ���������Ѳ�����)
	/**
	*@param  unsigned int  iKeyValue            ����ֵ
	*@return DBt               ��¼ֵ 
	*/   
	virtual LPDATA  FUNCTION_CALL_MODE Get(LPDATA key )=0;

	///����һ����¼
	/**ע����keyΪ�ַ�����ʱ��Ҫ��keyֱ������value�е��ַ�����ַ��
	*@param  DBt key             ����ֵkey
	*@param  DBt value            ����value
	*@return int   
	*/   
	virtual int  FUNCTION_CALL_MODE Put(LPDATA key, LPDATA value )=0;

	///������ȡһ����¼(��д����������������ʱ����������д������updateEnd()�ͷ� )
	/**
	*@param  char *  sKeyValue          ����ֵ
	*@return DBt *                        ��¼ֵ 
	*/   
	virtual LPDATA  FUNCTION_CALL_MODE GetForUpdate(LPDATA key)=0;

	///����һ����¼
	/**
	*@param  char *        sKeyValue            ����ֵkey
	*@param  DBt           lpData               ����value
	*@return int   
	*/   
	virtual int  FUNCTION_CALL_MODE UpdateEnd(LPDATA key )=0;

	///ȡ��¼��
	/**���صļ�¼��Ϊ����RowID-1
	*@return unsigned int   
	*/   
	virtual unsigned int  FUNCTION_CALL_MODE GetCount()=0;

	///����¼��ȡ����
	/**�ڴ���0��ʼΪÿ���ӵ�һ����¼����һ��RowID��ͨ��RowID���Կ��ٻ�ȡ����
	*@param unsigned int dwRowID
	*@return int   
	*/   
	virtual LPDATA  FUNCTION_CALL_MODE GetByID(unsigned int dwRowID)=0;

	///��ָ����¼�Ӷ���
	virtual void  FUNCTION_CALL_MODE ReadLock(LPDATA key )=0;

	///�ͷ�ָ����¼�Ķ���
	virtual void  FUNCTION_CALL_MODE ReadUnLock(LPDATA key )=0;
};

///�߼����ݿ���ʷ���
struct ISMDBService:IKnown
{
	///����һ���ڴ��
	/**����һ���ڴ��ָ������
	*
	*@param const char * sName  �ڴ������
	*@param int   iHashNodeNum    ����hash���������(ÿ�����һ����д��)
	*@param char  cKeyType        ������������ I ���� S�ַ���
	*@param int   iFlag           1 ���ݿռ����û�����
	*@return ISMDB *              ����һ���ڴ��ʵ���ӿ� 
	*/   
	virtual ISMDBTable * FUNCTION_CALL_MODE CreateTable(  const char * sName,
		int   iHashNodeNum,
		char  cKeyType,
		int   iFlag)=0;
	///���ñ���������������������ʵ��
	/**������ϣ������������ SID_LOG ��־���� 
	*
	*@param  iSID               ��������Ψһ��ʶ
	*@param  void * lpService   ��������ӿ�
	*@return int 0�ɹ�������ʧ�� 
	*/   
	virtual int FUNCTION_CALL_MODE SetService(  char * iSID,
		void * lpService)=0;

};
#endif

