#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <sym-api.h>
#include "lea.h"

void encrypt(unsigned char *plainText, unsigned char *cipherText, unsigned char *masterKey) {
	uint32_t subkeys[LEA128_RNDS*4];
	uint8_t buf[16];
	memcpy(buf, plainText, 16);
	lea128_setkey(masterKey, subkeys);
	lea128_encrypt(subkeys, buf);
	memcpy(cipherText, buf, 16);
}
	
int main() {
	unsigned char *plainText  = lss_fresh_array_uint8(16, 0, NULL);
	unsigned char *key        = lss_fresh_array_uint8(16, 0, NULL);
	unsigned char *cipherText = malloc(16 * sizeof(unsigned char));

	encrypt(plainText, cipherText, key);
	
	lss_write_aiger_array_uint8(cipherText, 16, "LEA_imp.aig");

	return 0;
}
