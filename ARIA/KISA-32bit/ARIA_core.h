#include <stdio.h>



void Crypt(const unsigned char *p, int R, const unsigned char *e, unsigned char *c);
int EncKeySetup(const unsigned char *w0, unsigned char *e, int keyBits);
int DecKeySetup(const unsigned char *w0, unsigned char *d, int keyBits);
