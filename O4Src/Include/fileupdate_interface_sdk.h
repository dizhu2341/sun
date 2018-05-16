/** @file fileupdate_interface_sdk.h
 *  @brief �ļ����� SDK�����ӿ��ļ�
 *  @author      majc
 *  @date        20140329
 *  @copyright   �������ӹɷ����޹�˾
 *  @version     1.0.0.0
 *
 *  @par �޸ļ�¼ <����> <�汾> <�޸���Ա> <�޸�����>
 *  
 */
#ifndef _FILEUPDATE_INTERFACE_SDK_H_
#define _FILEUPDATE_INTERFACE_SDK_H_
#if defined(_WIN32)&& _MSC_VER < 1300
#pragma warning(disable: 4786)				//����ڱ�������STLͷ�ļ�ǰ
#pragma warning(disable: 4710)				//����ڱ�������STLͷ�ļ�ǰ
#endif
#include <Include/plugin_interface.h>

#ifdef _WIN32
typedef unsigned int		uint32;
#else
#include <sys/types.h>
#if defined(__linux__)
#include <stdint.h>
#endif
typedef uint32_t			uint32;
#endif

/** �ļ����£����º�ΪAPI�����ļ����¹��������佻���Ĵ�����е��ֶ� */
#define PACKER_INT_FILE_LIST            "file_list"     /**< �ļ��б� */
#define PACKER_INT_FILE_ID              "file_id"       /**< �ļ�id */
#define PACKER_INT_FILE_SIZE            "file_size"     /**< �ļ���С */
#define PACKER_INT_TIME                 "time"          /**< �ļ�ʱ�� */
#define PACKER_STRING_FILE_NAME         "file_name"     /**< �ļ��� */
#define PACKER_STRING_FILE_PATH         "file_path"     /**< �ļ�·�� */
#define PACKER_STRING_LOCAL_PATH        "local_path"    /**< �����ļ�·�� */
#define PACKER_STRING_MD5_CODE          "md5_code"      /**< �ļ�md5ֵ */
#define PACKER_STRING_FILE_FLAG         "file_flag"     /**< �ļ���ʶ */
/**
 * �ļ����»ص��ӿڣ��ϲ�Ӧ��ͨ������ӿڣ����չ�������Ϣ
 */
class CFileUpdateCallbackInterface: public IKnown
{
public:

   /**
    * �յ������ļ��б�Ļص�
    * @param lpData ���ض�����ָ��
    * @param nLength ���������ݵĳ��ȣ����Ϊ������Ϊ������
	* @param lpErrorInfo �����ΪNULL��Ϊ������Ϣ����������Ӧ����ȥ��������Ϣ�����û����ȥ�ô�������Ϣ
    * @return ��
    */
    virtual void FUNCTION_CALL_MODE OnRecvFileList(const void *lpData, int nLength, const char * lpErrorInfo) = 0;

   /**
    * �յ�֪ͨ�ļ����½���
    * @param iOneFileProcessBar ��ǰ�ļ�����
    * @param iTotalProcessBar �ܽ���
	* @param lpErrorInfo �����ΪNULL��Ϊ������Ϣ����������Ӧ����ȥ��������Ϣ�����û����ȥ�ô�������Ϣ
    * @return ��
    */
    virtual void FUNCTION_CALL_MODE OnShowProcessBar(int iOneFileProcessBar, int iTotalProcessBar, const char * lpErrorInfo) = 0;
	
	/**
    * �յ��ɹ�ȡ���ļ�����
    * @return ��
    */
    virtual void FUNCTION_CALL_MODE OnCancel() = 0;


};

class CFileUpdateInterface: public IKnown
{
public:

   /**
    * ����ǰ��ص���ʾ���ļ��б����û�ѡ����·���Ҫ���µ��ļ��б�
    * @param lpPack �����ļ��б�ָ��
    * @return ����0��ʾ�ɹ�������ֵ��ʾʧ��.
    */
    virtual int FUNCTION_CALL_MODE UpdateFile(IF2Packer* lpPack) = 0;

   /**
    * ����ȡ�����ڸ����еĸ��¶���
    * @return ����0��ʾ�ɹ�������ֵ��ʾʧ��
    */
    virtual int FUNCTION_CALL_MODE CancelUpdateFile() = 0;

   /**
    * ��ȡ�����ļ��б�
    * @return �ļ��б��������������ⲿ������ֻ�ܶ��������ͷ�
	* @note �����������ֶμ����ļ�define�ֶ�,ע�⣺��OnRecvFileList�ص��Ժ�÷�����Ч
    */
    virtual IF2UnPacker* FUNCTION_CALL_MODE GetFileUpdateList() = 0;
};

#endif


