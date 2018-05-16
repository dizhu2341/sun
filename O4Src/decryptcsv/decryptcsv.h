#ifndef O4_PUBLIC_H_
#define O4_PUBLIC_H_

/**
 * @brief 对传入的内码加密
 * @param[in] srcInterCode 传入的内码
 * @return 返回加密后的密文
 * @par 示例:
 * @code
   int inter_code_encrypt = hsInterCodeEncrypt(600570001);
 * @endcode
 * @see ::hsInterCodeDectypt ::hsReportCodeEncrypt ::hsReportCodeDecrypt
 */
int hsInterCodeEncrypt(int srcInterCode);

/**
 * @brief 对传入的内码密文解密
 * @param[in] srcInterCode 传入的内码密文
 * @return 返回解密后的内码
 * @par 示例:
 * @code
   int inter_code = hsInterCodeEncrypt("1234567");
 * @endcode
 * @see ::hsInterCodeEncrypt ::hsReportCodeEncrypt ::hsReportCodeDecrypt
 */
int hsInterCodeDecrypt(int srcInterCode);

/**
 * @brief 对传入的证券申报代码加密
 * @param[in] srcReportCode 传入的申报代码
 * @param[out] dstReportCode 返回加密的申报代码密文
 * @return 返回加密后的申报代码
 * @par 示例:
 * @code
   hsReportCodeEncrypt("600570",report_code_encrypt);
 * @endcode
 * @see ::hsInterCodeEncrypt ::hsInterCodeDectypt ::hsReportCodeDecrypt
 */
char* hsReportCodeEncrypt(const char* srcReportCode, char* dstReportCode);

/**
 * @brief 对传入的证券申报代码密文解密
 * @param[in] srcReportCode 传入的申报代码的密文
 * @param[out] dstReportCode 返回解密后的申报代码
 * @return 解密后的申报代码
 * @par 示例:
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