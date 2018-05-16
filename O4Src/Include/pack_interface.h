/*******************************************************
  Դ��������:pack_interface.h
  �������Ȩ:�������ӹɷ����޹�˾
  ϵͳ����:  FBASE2.0
  ģ������:  ҵ���������
  ����˵��:  ҵ����������ӿ�
             1��IF2PackSvr ��������ӿ�
             2��IF2Packer ����ӿ�
			 3��IResultSet ����ӿ�(resultset.h����)
             
  ����ĵ�:  ��Ҫ��ƽӿڲ���
             
  ��    ��:  zhangly
  ��������:  20040223
  ��    ע:  ƽ̨�޹أ�֧�ֶ��ְ���ʽ
  �޸���Ա�� zhangly
  �޸����ڣ� 20051207
  �޸�˵���� IUnpacker�ӿ�����ȡ��¼�������� getRowCount();
             20130508 05909 ����������м�¼�α�ӿڣ�����First()/Last()/Go()
			 20130809 xuxp  ���ӻ�ȡ��ǰ��������ֵĽӿ�
			 20131115 xuxp  ���ӽ�����ҿ����ڴ�Ľӿ�
			 20140416 majc ���Ӹ������ֻ�ȡ�ֶ����ͣ��ֶξ��ȣ��ֶ���󳤶�
*********************************************************/
#ifndef PACKET_H
#define PACKET_H

#include <stdio.h>
#include <stdlib.h>
#include <Include/plugin_interface.h>
#include <Include/resultset.h>

struct IF2Packer;
struct IF2UnPacker;

#define SID_F2PACKSVR				"com.hundsun.fbase.f2packsvr"
#define SID_F2PACKER				"com.hundsun.fbase.f2packer"
#define SID_F2UNPACKER				"com.hundsun.fbase.f2unpacker"

///����������ӿ� 
struct IF2PackSvr : public IKnown
{
	///����ҵ�����ʽ�汾
	/**����ҵ������ַ��ж�ҵ�����ʽ�汾,ҵ����汾ʶ�����:
	 *
     *  V1���ײ��ŵ����ַ����͵����������Ե�һ���ֽ�>=0x30;
     *
     *  V2���һ���ֽڷŵ��ǰ汾�ţ�ĿǰֵΪ0x21�������Ը���ʱ��ֵ�������0x2F
     *
	 *@param void * lpBuffer		ҵ�������(������ָ��Ϸ�ҵ��������ֽ�)
	 *@return int 					ҵ�����ʽ�汾(1: V1��,0x21~0x2F V2��汾��)
	 */
    virtual int FUNCTION_CALL_MODE GetVersion(const void * lpBuffer) = 0;
	
	/** ��ȡ������ӿ�ָ��
	 *@param int iVersion			ҵ�����ʽ�汾(ȡֵ:1 �ִ���,����ֵ 0x20��)
	 *@return IPacker * 			������ӿ�ָ��
	 */
    virtual IF2Packer * FUNCTION_CALL_MODE GetPacker(int iVersion) = 0;

	/** ����ָ�������ݲ����ؽ���������ӿ�ָ��
	 *@param void * lpBuffer		Ҫ���������ݻ���ָ��
	 *@param unsigned int iLen		���ݳ���
	 *@return IUnPacker *			����������ӿ�ָ��, ������ʧ���򷵻�NULL
	 */
	virtual IF2UnPacker *  FUNCTION_CALL_MODE GetUnPacker(void * lpBuffer, unsigned int iLen ) = 0;
	
	/** ��ȡ������ӿ�ָ��
	 *@param iVersion:				ҵ�����ʽ�汾(1: V1��,0x21~0x2F V2��汾��)
	 *@return IUnPacker *			����������ӿ�ָ��
	 */
	virtual IF2UnPacker *  FUNCTION_CALL_MODE GetEmptyUnPacker(int iVersion) = 0;
};

///����������ӿ�(һ�������ж���칹�����)
/**ִ������:
 *
 * 0��׼��(��ѡ, �������иò���, ����IF2Packer�ڲ������ڴ滺��)�� SetBuffer(),�������������ɵ������ṩ,�������BeginPack()֮ǰ׼��;
 *
 * 1����ʼ:  BeginPack(),�������λ;
 *
 * 2����һ������������
 *
 *(a)����ֶ����б���AddField()
 *
 *(b)���ս������ά��˳�����ֶΣ�������¼���ֶ�����������ݣ�AddStr() {AddInt(), AddDouble(), AddRaw()}
 *
 * 3�����ý�����ķ�����(��ѡ����������, �򷵻���Ϊ0) SetReturnCode()
 *
 * 4������һ�������(��ѡ) NewDataSet()���˴�ͬʱ�����˸ý�����ķ����룻
 * 
 * 5���ο���2��ʵ����һ����������(��ѡ)��
 *
 * 6��������EndPack(),�ظ����ûᵼ�¼���ս����;
 *
 * 7��ȡ������(����������������С�����ݳ���)
 *    ������Ҳ����ֱ�ӽ��UnPack()���ؽ���ӿ�
 *
 *ʹ��ע������:IF2Packer��ʹ�õ��ڴ滺�������ɵ����߸�����գ�
 *             ����������ķ����룬ֻ���ڰ���ʽ�汾0x21������ʱ��Ч��
 */
struct IF2Packer : public IKnown
{
    ///�������ʼ��(ʹ�õ����ߵĻ�����)
	/** ��һ��ʹ�ô����ʱ������ʹ�ñ��������úû�����(���ݳ��ȱ���ΪiDataLen)
	 *@param  char * pBuf  ��������ַ
 	 *@param  int iBufSize  �������ռ�
 	 *@param  int iDataLen  �������ݳ��ȣ��������ݼ�����������֮��ֻ��V1.0��ʽ�İ���Ч�� 	 
 	 */
	virtual void FUNCTION_CALL_MODE SetBuffer(void * pBuf, int iBufSize, int iDataLen = 0) = 0;

	///��λ�����¿�ʼ����һ����(�ֶ������¼����Ϊ0��0��)
	/**
	 * ���ܣ���ʼ������Ѱ���������(�ظ�ʹ�����еĻ������ռ�)
	 *@return ��
	 */
	virtual void FUNCTION_CALL_MODE BeginPack(void) = 0;

	///��ʼ��һ�������
	/**�ڴ򵥽�����İ�ʱ�����Բ����ñ�����,��ȡĬ��ֵ
	 *@param const char *szDatasetName 0x20������Ҫָ�����������
	 *@param int iReturnCode           0x20������ҪΪÿ�������ָ������ֵ
	 */
	virtual int FUNCTION_CALL_MODE NewDataset(const char *szDatasetName, int iReturnCode = 0) = 0;

	/**
	 * ���ܣ��������ֶ�, �������ֶ�ֻ�ڰ���ʽ�汾0x21��������Ч��
	 *
	 *��ִ�д���Ҫ��:�� NewDataset()��Reset(),SetBuffer()֮��,����ֶΰ�˳�����;
	 *
	 *@param szFieldName���ֶ���
	 *@param cFieldType ���ֶ�����:I������D��������C�ַ���S�ַ�����R�������������
	 *@param iFieldWidth ���ֶο�ȣ���ռ����ֽ�����
	 *@param iFieldScale ���ֶξ���,��cFieldType='D'ʱ��С��λ��(ȱʡΪ4λС��)
	 *@return ������ʾʧ�ܣ�����ΪĿǰ���ĳ���
	 */
	virtual int FUNCTION_CALL_MODE AddField(const char *szFieldName,char cFieldType = 'S', int iFieldWidth = 255, int iFieldScale = 4) = 0;

	/**
	 * ���ܣ��������ַ�������
     * ��ִ�д���Ҫ��:�����������ֶ�������֮��,����ֶΰ�˳�����;
	 *@param       szValue���ַ�������
	 *@return ������ʾʧ�ܣ�����ΪĿǰ���ĳ���
	 */
	virtual int FUNCTION_CALL_MODE AddStr(const char *szValue) = 0;

	/**
     * ���ܣ���������������
 	 *@param       iValue����������
	 *@return ������ʾʧ�ܣ�����ΪĿǰ���ĳ���
	 */
	virtual int FUNCTION_CALL_MODE AddInt(int iValue) = 0;
	
    /**
	 * ���ܣ������Ӹ�������
	 *@param       fValue����������
	 *@return ������ʾʧ�ܣ�����ΪĿǰ���ĳ���
	 */
	virtual int FUNCTION_CALL_MODE AddDouble(double fValue) = 0;

	/**
	 * ���ܣ�������һ���ַ�
	 *@param		 cValue���ַ�
	 *@return ������ʾʧ�ܣ�����ΪĿǰ���ĳ���
	 */
	virtual int FUNCTION_CALL_MODE AddChar(char cValue) = 0;

	/**
	 * ���ܣ�������һ���������ֶ�, ����ʽ�汾0x21������ʱ��Ч��
	 *@param	void * lpBuff ������
	 *@param	int iLen  ���ݳ���	 
	 *@return ������ʾʧ�ܣ�����ΪĿǰ���ĳ���
	 */
	virtual int FUNCTION_CALL_MODE AddRaw(void * lpBuff,int iLen) = 0;

    ///�������
	virtual void FUNCTION_CALL_MODE EndPack() = 0;
 
	/**
     * ���ܣ�ȡ������ָ��
	 *@return ������ָ��
     */
	virtual void * FUNCTION_CALL_MODE GetPackBuf(void) = 0;
	
	/**
     * ���ܣ�ȡ����������
     *@return ����������
	 */
	virtual int FUNCTION_CALL_MODE GetPackLen(void) = 0;
	
	/**
	 * ���ܣ�ȡ��������������С
     *@return ��������������С
	 */
	virtual int FUNCTION_CALL_MODE GetPackBufSize(void) = 0;
	
	/**
	 * ���ܣ�ȡ�����ʽ�汾
     *@return �汾
	 */
	virtual int FUNCTION_CALL_MODE GetVersion(void) = 0;
	
	///���ý�����ķ�����(0x20������Ҫ��)������������Ҫ����
	/**������ȡȱʡֵ0�������ã�������ã��������EndPack()֮ǰ����
     *@return �汾
	 */
	virtual void FUNCTION_CALL_MODE SetReturnCode(unsigned long dwRetCode) = 0;

	/**ֱ�ӷ��ص�ǰ�������Ľ���ӿ�,������EndPack()֮����ܵ���,�ڴ�����ͷ�ʱ��Ӧ�Ľ����ʵ��Ҳ�ͷ�
     *@return ������ӿڣ��˽���ӿڲ��ܵ��� destroy()���ͷ�
	 */
	virtual IF2UnPacker * FUNCTION_CALL_MODE UnPack(void) = 0;

	/**
	 *
	 */
	virtual void FUNCTION_CALL_MODE FreeMem(void* lpBuf) = 0;

	/**
	 *
	 */
	virtual void FUNCTION_CALL_MODE ClearValue() = 0;

	//20110302 xuxp ����һ���ӿں������������ݵ�һ�������������
	///��λ�����¿�ʼ����һ����(�ֶ������¼����Ϊ0��0��)
	/**
	 * ���ܣ���ʼ������Ѱ���������(�ظ�ʹ�����еĻ������ռ�)
	 *@return ��
	 */
	virtual void FUNCTION_CALL_MODE BeginPackEx(char* szName = NULL) = 0;

	//20110324 dongpf ����һ���ӿں�����������λ��ǰ�����
	///��λ��ǰ�����(�ֶ������¼����Ϊ0��0��)����Ӱ�����������
	/**
	 * ���ܣ���λ��ǰ�����
	 *@return ��
	 */
	virtual void FUNCTION_CALL_MODE ClearDataSet() = 0;

	//20130920 xuxp ����һ���µĽӿڣ��������double�����ݣ����Ч��
	/**
	 * ���ܣ������Ӹ�������
	 *@param       fValue����������
	 *@return ������ʾʧ�ܣ�����ΪĿǰ���ĳ���
	 */
	virtual int FUNCTION_CALL_MODE AddDoubleEx(double fValue) = 0;
};

///������ӿ�
struct IF2UnPacker : public IF2ResultSet
{
	/** ȡ�����ʽ�汾
     *@return ҵ�����ʽ�汾
	 */
	virtual int FUNCTION_CALL_MODE GetVersion(void) = 0;

	/** ���
	 *@param void * lpBuffer			Ҫ���������
	 *@param unsigned int iLen			���ݳ���
     *@return							0 ��ʾ�ɹ��� ����Ϊʧ��
	 */
	virtual int FUNCTION_CALL_MODE Open(void * lpBuffer,unsigned int iLen) = 0;

    /// ȡ��������� (0x21�����ϰ汾֧��)
    virtual int FUNCTION_CALL_MODE GetDatasetCount()=0;

    /// ���õ�ǰ����� (0x21�����ϰ汾֧��)
    /**
	 *@param  int nIndex				��������
	 *@return int						��0 ��ʾ�ɹ�������Ϊʧ��
	 */
    virtual int FUNCTION_CALL_MODE SetCurrentDatasetByIndex(int nIndex)=0;

    /// ���õ�ǰ����� (0x21�����ϰ汾֧��)
    /**
	 *@param  const char *szDatasetName	���������
	 *@return int						��0 ��ʾ�ɹ�������Ϊʧ��
	 */
    virtual int FUNCTION_CALL_MODE SetCurrentDataset(const char *szDatasetName)=0;

	/** ȡ������ݻ���ָ��
	 *@return ���ݻ���ָ��
     */
	virtual void * FUNCTION_CALL_MODE GetPackBuf(void) = 0;

	/** ȡ������ݳ���
     *@return ������ݳ���
	 */
	virtual unsigned int FUNCTION_CALL_MODE GetPackLen(void) = 0;

	/**ȡ������ݼ�¼����,20051207�Ժ�汾֧��
     *@return ��¼����
	 */
	virtual unsigned int FUNCTION_CALL_MODE GetRowCount(void) = 0;

    /* 20130508 05909 ����������м�¼�α�ӿ� start */
    ///������м�¼�α�ӿڣ�ȡ�������������¼
    virtual void FUNCTION_CALL_MODE First() = 0;

    ///������м�¼�α�ӿڣ�ȡ����������һ����¼
    virtual void FUNCTION_CALL_MODE Last() = 0;

    ///������м�¼�α�ӿڣ�ȡ������ĵ�n����¼��ȡֵ��Χ[1, GetRowCount()]
    virtual void FUNCTION_CALL_MODE Go(int nRow) = 0;
    /* 20130508 05909 ����������м�¼�α�ӿ� end */

	//20130809 xuxp  ���ӻ�ȡ��ǰ��������ֵĽӿ�,û�����ַ���""
	virtual const char* FUNCTION_CALL_MODE GetDatasetName() = 0;


	//20131115 xuxp  ���ӽ�����ҿ����Ľӿ�
	/** ������ҿ������浽�Լ����ڲ��ռ�
	 *@param void * lpBuffer			Ҫ���������
	 *@param unsigned int iLen			���ݳ���
     *@return							0 ��ʾ�ɹ��� ����Ϊʧ��
	 */
	virtual int FUNCTION_CALL_MODE OpenAndCopy(void * lpBuffer,unsigned int iLen) = 0;
	//20140416 majc ���Ӹ������ֻ�ȡ�ֶ����ͣ��ֶξ��ȣ��ֶ���󳤶�
	
	//ȡ�ֶ���������
    /** @param columnName:�ֶ���
      * @return:�����泣������;���������� Ĭ�Ϸ���'S'
      */
    virtual char FUNCTION_CALL_MODE GetColTypeByName(const char * columnName)=0;


   ///ȡ�������ֶ�С��λ��
   /** @param columnName:�ֶ���
     * @return int �����ֶ�����С��λ�� ���������� ����0 
     */
   virtual int FUNCTION_CALL_MODE GetColScaleByName(const char * columnName)=0;
  
   //ȡ�ֶ����������ݵ������.
   /** @param columnName:�ֶ���
     * @return int �����ֶο�� ���������� ����1
     */
   virtual int FUNCTION_CALL_MODE GetColWidthByName(const char * columnName) = 0;
};

//----------��Ϊ�ɶ�̬���صĻ���������������붨��������������---------

#ifdef __cplusplus
extern "C" { 
#endif

	///�����ʼ������
	/**
	 *@return int �汾�� yyyymmdd��ʽ
	 */
	int  FUNCTION_CALL_MODE PackSvrInit(void *lpInst, PFOnSetTimeOut lpFunc= NULL);

	///ȡ����ӿھ��
	/**
	 *@return void * ���������� 
	 */
	IKnown * FUNCTION_CALL_MODE GetPackSvrInstance(void);

	///ȡ����ӿ���������
	/**
	 *@param iIndex 
	 *@return IKnown * ���������ʶ 
	 */
	char * FUNCTION_CALL_MODE GetPackSvrDependService(void *);

	///����ͳһ�Ļ�����������ѯ�ӿ�
	/**���������������̬����ʱ��ͨ�����ӿڻ��Ի�ȡ������Ϣ(����xxxxInit(),getxxxxInterface()����ָ��)
	 *@param int iIndex		
	 *@param void ** ppv    �������������Ϣ(�������)��
	 *@return ����0��ʾ�鵽��Ҫ�Ľӿڣ����򷵻ظ���
	 */
	int FUNCTION_CALL_MODE GetPackSvrInfo(int iIndex, tagBaseServiceInfo * ppv );

#ifdef __cplusplus
  }
#endif
 
#endif
