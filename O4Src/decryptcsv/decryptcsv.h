#ifndef O4_PUBLIC_H_
#define O4_PUBLIC_H_

/**
 * @brief �Դ�����������
 * @param[in] srcInterCode ���������
 * @return ���ؼ��ܺ������
 * @par ʾ��:
 * @code
   int inter_code_encrypt = hsInterCodeEncrypt(600570001);
 * @endcode
 * @see ::hsInterCodeDectypt ::hsReportCodeEncrypt ::hsReportCodeDecrypt
 */
int hsInterCodeEncrypt(int srcInterCode);

/**
 * @brief �Դ�����������Ľ���
 * @param[in] srcInterCode �������������
 * @return ���ؽ��ܺ������
 * @par ʾ��:
 * @code
   int inter_code = hsInterCodeEncrypt("1234567");
 * @endcode
 * @see ::hsInterCodeEncrypt ::hsReportCodeEncrypt ::hsReportCodeDecrypt
 */
int hsInterCodeDecrypt(int srcInterCode);

/**
 * @brief �Դ����֤ȯ�걨�������
 * @param[in] srcReportCode ������걨����
 * @param[out] dstReportCode ���ؼ��ܵ��걨��������
 * @return ���ؼ��ܺ���걨����
 * @par ʾ��:
 * @code
   hsReportCodeEncrypt("600570",report_code_encrypt);
 * @endcode
 * @see ::hsInterCodeEncrypt ::hsInterCodeDectypt ::hsReportCodeDecrypt
 */
char* hsReportCodeEncrypt(const char* srcReportCode, char* dstReportCode);

/**
 * @brief �Դ����֤ȯ�걨�������Ľ���
 * @param[in] srcReportCode ������걨���������
 * @param[out] dstReportCode ���ؽ��ܺ���걨����
 * @return ���ܺ���걨����
 * @par ʾ��:
 * @code
   hsReportCodeDecrypt("abcde",report_code_encrypt);
 * @endcode
 * @see ::hsInterCodeEncrypt ::hsInterCodeDectypt ::hsReportCodeEncrypt
 */
char* hsReportCodeDecrypt(const char* srcReportCode, char* dstReportCode);

int check_param(int argc,char* argv[]);
void print_help();

int encrypt();
int encrypt_file(char* src_file,char* dst_file);

int decrypt();
int decrypt_file(char* src_file,char* dst_file);

int dosplit(char *linebuf,char buf[][1024]);
#endif