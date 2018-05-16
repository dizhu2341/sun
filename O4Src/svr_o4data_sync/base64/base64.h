
#ifndef BASE64_H
#define BASE64_H

#ifdef __cplusplus
extern "C" {
#endif

unsigned char *base64_encode(const unsigned char *str, int length, int *ret_length);
unsigned char *base64_decode(const unsigned char *str, int length, int *ret_length);

#ifdef __cplusplus
}
#endif

#endif /* BASE64_H */

