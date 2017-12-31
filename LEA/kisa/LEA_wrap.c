#include "LEA.h"

#include <stdio.h>
#include <stdlib.h>
#include <sym-api.h>

void encrypt(unsigned char *plainText, unsigned char *cipherText, unsigned char *masterKey) {
	LEA_KEY key;
	lea_set_key(&key, masterKey, 16);
	lea_encrypt(cipherText, plainText, &key);
}
	
int main() {
	unsigned char *plainText  = lss_fresh_array_uint8(16, 0, NULL);
	unsigned char *key        = lss_fresh_array_uint8(16, 0, NULL);
	unsigned char *cipherText = malloc(16 * sizeof(unsigned char));

	encrypt(plainText, cipherText, key);
	
	lss_write_aiger_array_uint8(cipherText, 16, "LEA_imp.aig");

	return 0;
}
