#include "ARIA_core.h"
#include <sym-api.h>

void encrypt(unsigned char *plainText, unsigned char *cipherText, unsigned char *key) {
	ARIAEncryption(cipherText, plainText, key);
}

int main() {
	unsigned char *plainText  = lss_fresh_array_uint8(16, 0, NULL);
	unsigned char *key        = lss_fresh_array_uint8(16, 0, NULL);
	unsigned char *cipherText = malloc(16 * sizeof(unsigned char));

	encrypt(plainText, cipherText, key);
	
	lss_write_aiger_array_uint8(cipherText, 16, "ARIA_imp.aig");
	
	return 0;
}
