#ifndef _LEA_HEADER_
#define _LEA_HEADER_
#define ROR(W,i) (((W) >> (i)) | ((W) << (32 - (i))))
#define ROL(W,i) (((W) << (i)) | ((W) >> (32 - (i))))
#define loadU32(v) v
typedef struct lea_key_st
{
	unsigned int rk[192];
	unsigned int round;
} LEA_KEY;

void lea_set_key(LEA_KEY *key, const unsigned char *mk, unsigned int mk_len);
void lea_encrypt(unsigned char *ct, const unsigned char *pt, const LEA_KEY *key);
void lea_decrypt(unsigned char *pt, const unsigned char *ct, const LEA_KEY *key);

#endif
