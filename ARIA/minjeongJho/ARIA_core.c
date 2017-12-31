#define _CRT_SECURE_NO_WARNINGS
#include"ARIA_core.h"
#define CHAR_TO_HEX(X) X>='A'? (X-55)%0x10:X-48
int passcount, failcount;

unsigned char Sbox[4][256] = {
	{ //sbox1
		0x63, 0x7C, 0x77, 0x7B, 0xF2, 0x6B, 0x6F, 0xC5, 0x30, 0x01, 0x67, 0x2B, 0xFE, 0xD7, 0xAB, 0x76,
		0xCA, 0x82, 0xC9, 0x7D, 0xFA, 0x59, 0x47, 0xF0, 0xAD, 0xD4, 0xA2, 0xAF, 0x9C, 0xA4, 0x72, 0xC0,
		0xB7, 0xFD, 0x93, 0x26, 0x36, 0x3F, 0xF7, 0xCC, 0x34, 0xA5, 0xE5, 0xF1, 0x71, 0xD8, 0x31, 0x15,
		0x04, 0xC7, 0x23, 0xC3, 0x18, 0x96, 0x05, 0x9A, 0x07, 0x12, 0x80, 0xE2, 0xEB, 0x27, 0xB2, 0x75,
		0x09, 0x83, 0x2C, 0x1A, 0x1B, 0x6E, 0x5A, 0xA0, 0x52, 0x3B, 0xD6, 0xB3, 0x29, 0xE3, 0x2F, 0x84,
		0x53, 0xD1, 0x00, 0xED, 0x20, 0xFC, 0xB1, 0x5B, 0x6A, 0xCB, 0xBE, 0x39, 0x4A, 0x4C, 0x58, 0xCF,
		0xD0, 0xEF, 0xAA, 0xFB, 0x43, 0x4D, 0x33, 0x85, 0x45, 0xF9, 0x02, 0x7F, 0x50, 0x3C, 0x9F, 0xA8,
		0x51, 0xA3, 0x40, 0x8F, 0x92, 0x9D, 0x38, 0xF5, 0xBC, 0xB6, 0xDA, 0x21, 0x10, 0xFF, 0xF3, 0xD2,
		0xCD, 0x0C, 0x13, 0xEC, 0x5F, 0x97, 0x44, 0x17, 0xC4, 0xA7, 0x7E, 0x3D, 0x64, 0x5D, 0x19, 0x73,
		0x60, 0x81, 0x4F, 0xDC, 0x22, 0x2A, 0x90, 0x88, 0x46, 0xEE, 0xB8, 0x14, 0xDE, 0x5E, 0x0B, 0xDB,
		0xE0, 0x32, 0x3A, 0x0A, 0x49, 0x06, 0x24, 0x5C, 0xC2, 0xD3, 0xAC, 0x62, 0x91, 0x95, 0xE4, 0x79,
		0xE7, 0xC8, 0x37, 0x6D, 0x8D, 0xD5, 0x4E, 0xA9, 0x6C, 0x56, 0xF4, 0xEA, 0x65, 0x7A, 0xAE, 0x08,
		0xBA, 0x78, 0x25, 0x2E, 0x1C, 0xA6, 0xB4, 0xC6, 0xE8, 0xDD, 0x74, 0x1F, 0x4B, 0xBD, 0x8B, 0x8A,
		0x70, 0x3E, 0xB5, 0x66, 0x48, 0x03, 0xF6, 0x0E, 0x61, 0x35, 0x57, 0xB9, 0x86, 0xC1, 0x1D, 0x9E,
		0xE1, 0xF8, 0x98, 0x11, 0x69, 0xD9, 0x8E, 0x94, 0x9B, 0x1E, 0x87, 0xE9, 0xCE, 0x55, 0x28, 0xDF,
		0x8C, 0xA1, 0x89, 0x0D, 0xBF, 0xE6, 0x42, 0x68, 0x41, 0x99, 0x2D, 0x0F, 0xB0, 0x54, 0xBB, 0x16
	},
	{ //sbox2
		0xe2, 0x4e, 0x54, 0xfc, 0x94, 0xc2, 0x4a, 0xcc, 0x62, 0x0d, 0x6a, 0x46, 0x3c, 0x4d, 0x8b, 0xd1,
		0x5e, 0xfa, 0x64, 0xcb, 0xb4, 0x97, 0xbe, 0x2b, 0xbc, 0x77, 0x2e, 0x03, 0xd3, 0x19, 0x59, 0xc1,
		0x1d, 0x06, 0x41, 0x6b, 0x55, 0xf0, 0x99, 0x69, 0xea, 0x9c, 0x18, 0xae, 0x63, 0xdf, 0xe7, 0xbb,
		0x00, 0x73, 0x66, 0xfb, 0x96, 0x4c, 0x85, 0xe4, 0x3a, 0x09, 0x45, 0xaa, 0x0f, 0xee, 0x10, 0xeb,
		0x2d, 0x7f, 0xf4, 0x29, 0xac, 0xcf, 0xad, 0x91, 0x8d, 0x78, 0xc8, 0x95, 0xf9, 0x2f, 0xce, 0xcd,
		0x08, 0x7a, 0x88, 0x38, 0x5c, 0x83, 0x2a, 0x28, 0x47, 0xdb, 0xb8, 0xc7, 0x93, 0xa4, 0x12, 0x53,
		0xff, 0x87, 0x0e, 0x31, 0x36, 0x21, 0x58, 0x48, 0x01, 0x8e, 0x37, 0x74, 0x32, 0xca, 0xe9, 0xb1,
		0xb7, 0xab, 0x0c, 0xd7, 0xc4, 0x56, 0x42, 0x26, 0x07, 0x98, 0x60, 0xd9, 0xb6, 0xb9, 0x11, 0x40,
		0xec, 0x20, 0x8c, 0xbd, 0xa0, 0xc9, 0x84, 0x04, 0x49, 0x23, 0xf1, 0x4f, 0x50, 0x1f, 0x13, 0xdc,
		0xd8, 0xc0, 0x9e, 0x57, 0xe3, 0xc3, 0x7b, 0x65, 0x3b, 0x02, 0x8f, 0x3e, 0xe8, 0x25, 0x92, 0xe5,
		0x15, 0xdd, 0xfd, 0x17, 0xa9, 0xbf, 0xd4, 0x9a, 0x7e, 0xc5, 0x39, 0x67, 0xfe, 0x76, 0x9d, 0x43,
		0xa7, 0xe1, 0xd0, 0xf5, 0x68, 0xf2, 0x1b, 0x34, 0x70, 0x05, 0xa3, 0x8a, 0xd5, 0x79, 0x86, 0xa8,
		0x30, 0xc6, 0x51, 0x4b, 0x1e, 0xa6, 0x27, 0xf6, 0x35, 0xd2, 0x6e, 0x24, 0x16, 0x82, 0x5f, 0xda,
		0xe6, 0x75, 0xa2, 0xef, 0x2c, 0xb2, 0x1c, 0x9f, 0x5d, 0x6f, 0x80, 0x0a, 0x72, 0x44, 0x9b, 0x6c,
		0x90, 0x0b, 0x5b, 0x33, 0x7d, 0x5a, 0x52, 0xf3, 0x61, 0xa1, 0xf7, 0xb0, 0xd6, 0x3f, 0x7c, 0x6d,
		0xed, 0x14, 0xe0, 0xa5, 0x3d, 0x22, 0xb3, 0xf8, 0x89, 0xde, 0x71, 0x1a, 0xaf, 0xba, 0xb5, 0x81
	},
	{ //sbox1inverse
		0x52, 0x09, 0x6a, 0xd5, 0x30, 0x36, 0xa5, 0x38, 0xbf, 0x40, 0xa3, 0x9e, 0x81, 0xf3, 0xd7, 0xfb,
		0x7c, 0xe3, 0x39, 0x82, 0x9b, 0x2f, 0xff, 0x87, 0x34, 0x8e, 0x43, 0x44, 0xc4, 0xde, 0xe9, 0xcb,
		0x54, 0x7b, 0x94, 0x32, 0xa6, 0xc2, 0x23, 0x3d, 0xee, 0x4c, 0x95, 0x0b, 0x42, 0xfa, 0xc3, 0x4e,
		0x08, 0x2e, 0xa1, 0x66, 0x28, 0xd9, 0x24, 0xb2, 0x76, 0x5b, 0xa2, 0x49, 0x6d, 0x8b, 0xd1, 0x25,
		0x72, 0xf8, 0xf6, 0x64, 0x86, 0x68, 0x98, 0x16, 0xd4, 0xa4, 0x5c, 0xcc, 0x5d, 0x65, 0xb6, 0x92,
		0x6c, 0x70, 0x48, 0x50, 0xfd, 0xed, 0xb9, 0xda, 0x5e, 0x15, 0x46, 0x57, 0xa7, 0x8d, 0x9d, 0x84,
		0x90, 0xd8, 0xab, 0x00, 0x8c, 0xbc, 0xd3, 0x0a, 0xf7, 0xe4, 0x58, 0x05, 0xb8, 0xb3, 0x45, 0x06,
		0xd0, 0x2c, 0x1e, 0x8f, 0xca, 0x3f, 0x0f, 0x02, 0xc1, 0xaf, 0xbd, 0x03, 0x01, 0x13, 0x8a, 0x6b,
		0x3a, 0x91, 0x11, 0x41, 0x4f, 0x67, 0xdc, 0xea, 0x97, 0xf2, 0xcf, 0xce, 0xf0, 0xb4, 0xe6, 0x73,
		0x96, 0xac, 0x74, 0x22, 0xe7, 0xad, 0x35, 0x85, 0xe2, 0xf9, 0x37, 0xe8, 0x1c, 0x75, 0xdf, 0x6e,
		0x47, 0xf1, 0x1a, 0x71, 0x1d, 0x29, 0xc5, 0x89, 0x6f, 0xb7, 0x62, 0x0e, 0xaa, 0x18, 0xbe, 0x1b,
		0xfc, 0x56, 0x3e, 0x4b, 0xc6, 0xd2, 0x79, 0x20, 0x9a, 0xdb, 0xc0, 0xfe, 0x78, 0xcd, 0x5a, 0xf4,
		0x1f, 0xdd, 0xa8, 0x33, 0x88, 0x07, 0xc7, 0x31, 0xb1, 0x12, 0x10, 0x59, 0x27, 0x80, 0xec, 0x5f,
		0x60, 0x51, 0x7f, 0xa9, 0x19, 0xb5, 0x4a, 0x0d, 0x2d, 0xe5, 0x7a, 0x9f, 0x93, 0xc9, 0x9c, 0xef,
		0xa0, 0xe0, 0x3b, 0x4d, 0xae, 0x2a, 0xf5, 0xb0, 0xc8, 0xeb, 0xbb, 0x3c, 0x83, 0x53, 0x99, 0x61,
		0x17, 0x2b, 0x04, 0x7e, 0xba, 0x77, 0xd6, 0x26, 0xe1, 0x69, 0x14, 0x63, 0x55, 0x21, 0x0c, 0x7d
	},
	{ //sbox2inverse
		0x30, 0x68, 0x99, 0x1b, 0x87, 0xb9, 0x21, 0x78, 0x50, 0x39, 0xdb, 0xe1, 0x72, 0x09, 0x62, 0x3c,
		0x3e, 0x7e, 0x5e, 0x8e, 0xf1, 0xa0, 0xcc, 0xa3, 0x2a, 0x1d, 0xfb, 0xb6, 0xd6, 0x20, 0xc4, 0x8d,
		0x81, 0x65, 0xf5, 0x89, 0xcb, 0x9d, 0x77, 0xc6, 0x57, 0x43, 0x56, 0x17, 0xd4, 0x40, 0x1a, 0x4d,
		0xc0, 0x63, 0x6c, 0xe3, 0xb7, 0xc8, 0x64, 0x6a, 0x53, 0xaa, 0x38, 0x98, 0x0c, 0xf4, 0x9b, 0xed,
		0x7f, 0x22, 0x76, 0xaf, 0xdd, 0x3a, 0x0b, 0x58, 0x67, 0x88, 0x06, 0xc3, 0x35, 0x0d, 0x01, 0x8b,
		0x8c, 0xc2, 0xe6, 0x5f, 0x02, 0x24, 0x75, 0x93, 0x66, 0x1e, 0xe5, 0xe2, 0x54, 0xd8, 0x10, 0xce,
		0x7a, 0xe8, 0x08, 0x2c, 0x12, 0x97, 0x32, 0xab, 0xb4, 0x27, 0x0a, 0x23, 0xdf, 0xef, 0xca, 0xd9,
		0xb8, 0xfa, 0xdc, 0x31, 0x6b, 0xd1, 0xad, 0x19, 0x49, 0xbd, 0x51, 0x96, 0xee, 0xe4, 0xa8, 0x41,
		0xda, 0xff, 0xcd, 0x55, 0x86, 0x36, 0xbe, 0x61, 0x52, 0xf8, 0xbb, 0x0e, 0x82, 0x48, 0x69, 0x9a,
		0xe0, 0x47, 0x9e, 0x5c, 0x04, 0x4b, 0x34, 0x15, 0x79, 0x26, 0xa7, 0xde, 0x29, 0xae, 0x92, 0xd7,
		0x84, 0xe9, 0xd2, 0xba, 0x5d, 0xf3, 0xc5, 0xb0, 0xbf, 0xa4, 0x3b, 0x71, 0x44, 0x46, 0x2b, 0xfc,
		0xeb, 0x6f, 0xd5, 0xf6, 0x14, 0xfe, 0x7c, 0x70, 0x5a, 0x7d, 0xfd, 0x2f, 0x18, 0x83, 0x16, 0xa5,
		0x91, 0x1f, 0x05, 0x95, 0x74, 0xa9, 0xc1, 0x5b, 0x4a, 0x85, 0x6d, 0x13, 0x07, 0x4f, 0x4e, 0x45,
		0xb2, 0x0f, 0xc9, 0x1c, 0xa6, 0xbc, 0xec, 0x73, 0x90, 0x7b, 0xcf, 0x59, 0x8f, 0xa1, 0xf9, 0x2d,
		0xf2, 0xb1, 0x00, 0x94, 0x37, 0x9f, 0xd0, 0x2e, 0x9c, 0x6e, 0x28, 0x3f, 0x80, 0xf0, 0x3d, 0xd3,
		0x25, 0x8a, 0xb5, 0xe7, 0x42, 0xb3, 0xc7, 0xea, 0xf7, 0x4c, 0x11, 0x33, 0x03, 0xa2, 0xac, 0x60
	}
};

unsigned char c[3][16] = { { 0x51, 0x7c, 0xc1, 0xb7, 0x27, 0x22, 0x0a, 0x94, 0xfe, 0x13, 0xab, 0xe8, 0xfa, 0x9a, 0x6e, 0xe0 }, //c1
{ 0x6d, 0xb1, 0x4a, 0xcc, 0x9e, 0x21, 0xc8, 0x20, 0xff, 0x28, 0xb1, 0xd5, 0xef, 0x5d, 0xe2, 0xb0 }, //c2
{ 0xdb, 0x92, 0x37, 0x1d, 0x21, 0x26, 0xe9, 0x70, 0x03, 0x24, 0x97, 0x75, 0x04, 0xe8, 0xc9, 0x0e } }; //c3
	
void SubstLayerOdd(unsigned char *y){
	unsigned char i, x[16];
	for (i = 0; i < 16; i++) x[i] = y[i];
	//for (i = 0; i < 16; i++) y[i] ^= x[i];
	for (i = 1; i < 16; i += 4){
		y[i - 1] = Sbox[0][x[i - 1]];
		y[i] = Sbox[1][x[i]]; 
		y[i + 1] = Sbox[2][x[i + 1]];
		y[i + 2] = Sbox[3][x[i + 2]];
	}
	
}
                                                                                                                                                                                              
void SubstLayerEven(unsigned char *y){
	unsigned char i, x[16];
	for (i = 0; i < 16; i++)	x[i] = y[i];
	for (i = 1; i < 16; i +=4){
		y[i - 1] = Sbox[2][x[i - 1]];  
		y[i] = Sbox[3][x[i]];
		y[i + 1] = Sbox[0][x[i + 1]];
		y[i + 2] = Sbox[1][x[i + 2]];
	}
}

void DiffLayer(unsigned char *y){ 
	unsigned char i, x[16];
	for (i = 0; i < 16; i++)	x[i] = y[i];
	y[0] = x[3] ^ x[4] ^ x[6] ^ x[8] ^ x[9] ^ x[13] ^ x[14];
	y[1] = x[2] ^ x[5] ^ x[7] ^ x[8] ^ x[9] ^ x[12] ^ x[15];
	y[2] = x[1] ^ x[4] ^ x[6] ^ x[10] ^ x[11] ^ x[12] ^ x[15];
	y[3] = x[0] ^ x[5] ^ x[7] ^ x[10] ^ x[11] ^ x[13] ^ x[14];
	y[4] = x[0] ^ x[2] ^ x[5] ^ x[8] ^ x[11] ^ x[14] ^ x[15];
	y[5] = x[1] ^ x[3] ^ x[4] ^ x[9] ^ x[10] ^ x[14] ^ x[15];
	y[6] = x[0] ^ x[2] ^ x[7] ^ x[9] ^ x[10] ^ x[12] ^ x[13];
	y[7] = x[1] ^ x[3] ^ x[6] ^ x[8] ^ x[11] ^ x[12] ^ x[13];
	y[8] = x[0] ^ x[1] ^ x[4] ^ x[7] ^ x[10] ^ x[13] ^ x[15];
	y[9] = x[0] ^ x[1] ^ x[5] ^ x[6] ^ x[11] ^ x[12] ^ x[14];
	y[10] = x[2] ^ x[3] ^ x[5] ^ x[6] ^ x[8] ^ x[13] ^ x[15];
	y[11] = x[2] ^ x[3] ^ x[4] ^ x[7] ^ x[9] ^ x[12] ^ x[14];
	y[12] = x[1] ^ x[2] ^ x[6] ^ x[7] ^ x[9] ^ x[11] ^ x[12];
	y[13] = x[0] ^ x[3] ^ x[6] ^ x[7] ^ x[8] ^ x[10] ^ x[13];
	y[14] = x[0] ^ x[3] ^ x[4] ^ x[5] ^ x[9] ^ x[11] ^ x[14];
	y[15] = x[1] ^ x[2] ^ x[4] ^ x[5] ^ x[8] ^ x[10] ^ x[15];
}

void FuncOdd(unsigned char* y, unsigned char *x){
	int i;
	for (i = 0; i < 16; i++) y[i] ^= x[i];  
	
	SubstLayerOdd(y);
	DiffLayer(y);
		
};


void FuncEven(unsigned char* y, unsigned char* x){
	int i;
	for (i = 0; i < 16; i++) y[i] ^= x[i];
	SubstLayerEven(y);
	DiffLayer(y);
};

unsigned char* rotXor(unsigned char *tmp, unsigned char *w, unsigned char num){
	unsigned char i, j, m, n, tmp1, tmp2;
	m = num / 8; n = num % 8;
	for (i = 0; i < 16; i++) tmp[i] = w[i];
	for (j = 0; j < m; j++){
		tmp1 = tmp[15];
		for (i = 15; i > 0; i--){
			tmp[i] = tmp[i - 1];
		}
		tmp[0] = tmp1;
	}

	tmp1 = tmp[15];
	for (j = 15; j >0; j--){
		tmp2 = tmp[j - 1];
		tmp[j] = ((tmp[j] >> n) | (tmp2 << (8 - n))) % 0x100;
	}
	tmp[0] = ((tmp[0] >> n) | (tmp1 << (8 - n))) % 0x100;
	return tmp;
}
 
unsigned char* rotXorleft(unsigned char *tmp, unsigned char *w, unsigned char num){
	unsigned char i, j, m, n, tmp1,tmp2;
	m = num / 8; n = num % 8;
	for (i = 0; i < 16; i++) tmp[i] = w[i];
	for (j = 0; j < m; j++){
		tmp1 = tmp[0];
		for (i = 0; i < 15; i++){
			tmp[i] = tmp[i+1];
		}
		tmp[15] = tmp1;
	}

	tmp1 = tmp[0];
	for (j = 0; j <15; j++){
		tmp2 = tmp[j + 1];
		tmp[j] = ((tmp[j] << n) | (tmp2 >> (8 - n))) % 0x100;
	}
	tmp[15] = ((tmp[15] << n) | (tmp1 >> (8 - n))) % 0x100;
	return tmp;
}

void KeyScheduling(ariaCipher *test,unsigned char *k){
	unsigned char w[4][16];
	int i,j;
	unsigned char tmp[16];
	unsigned char shiftnum[10];	shiftnum[0] = 19;	shiftnum[4] = 31;	shiftnum[8] = 61;
	//키 초기화//   
	
	for (i = 0; i < 16; i++) w[0][i] = k[i]; 
	for (i = 0; i < 16; i++) tmp[i] = w[0][i];
	FuncOdd(tmp, c[0]);	for (i = 0; i < 16; i++) w[1][i] = tmp[i] ^ 0x00;
	for (i = 0; i < 16; i++) tmp[i] = w[1][i];
	FuncEven(tmp, c[1]);	for (i = 0; i < 16; i++)  w[2][i] = tmp[i] ^ w[0][i]; 
	for (i = 0; i < 16; i++) tmp[i] = w[2][i];
	FuncOdd(tmp, c[2]);	for (i = 0; i < 16; i++)  w[3][i] = tmp[i] ^ w[1][i];
	// 초기화 ok

	//키 생성//
	for (i = 0; i < 9; i+=4){
			rotXor(tmp, w[1], shiftnum[i]);		for (j = 0; j < 16; j++) test->ek[i][j] = w[0][j] ^ tmp[j];
			rotXor(tmp, w[2], shiftnum[i]);		for (j = 0; j < 16; j++) test->ek[i + 1][j] = w[1][j] ^ tmp[j];
			rotXor(tmp, w[3], shiftnum[i]);		for (j = 0; j < 16; j++) test->ek[i + 2][j] = w[2][j] ^ tmp[j];
			rotXor(tmp, w[0], shiftnum[i]);		for (j = 0; j < 16; j++) test->ek[i + 3][j] = tmp[j] ^ w[3][j];
	}
		rotXorleft(tmp, w[1], 61);	for (j = 0; j < 16; j++) test->ek[8][j] = w[0][j] ^ tmp[j];
		rotXorleft(tmp, w[2], 61);	for (j = 0; j < 16; j++) test->ek[9][j] = w[1][j] ^ tmp[j];
		rotXorleft(tmp, w[3], 61);	for (j = 0; j < 16; j++) test->ek[10][j] = w[2][j] ^ tmp[j];
		rotXorleft(tmp, w[0], 61);	for (j = 0; j < 16; j++) test->ek[11][j] = tmp[j] ^ w[3][j];
		rotXorleft(tmp, w[1], 31);	for (j = 0; j < 16; j++) test->ek[12][j] = w[0][j] ^ tmp[j];
	
}

void decKeyScheduling(ariaCipher *test){
	int i,j;
	for (i = 0; i < 16; i++) test->dk[0][i] = test->ek[12][i];
	for (i = 1; i < 12; i++){
		for (j = 0; j < 16; j++) test->dk[i][j] = test->ek[12-i][j];
		DiffLayer(test->dk[i]);
	}
	for (i = 0; i < 16; i++) test->dk[12][i] = test->ek[0][i];
}

void ariaEncryption(unsigned char* c,ariaCipher* test,unsigned char*p, unsigned char *k){
	int i;

	KeyScheduling(test,k); 
	
	for (i = 0; i < 16; i++) c[i] = p[i];

	for (i = 0; i < 10; i += 2){
		FuncOdd(c, test->ek[i]); 
		FuncEven(c,test->ek[i+1]);
	}
	FuncOdd(c, test->ek[10]);
	//
	for (i = 0; i < 16; i++) c[i] ^= test->ek[11][i];
	SubstLayerEven(c);
	for (i = 0; i < 16; i++)	c[i] ^= test->ek[12][i];
	
}

void ariaDecryption(unsigned char* c, ariaCipher* test, unsigned char*p, unsigned char *k){
	int i;
	decKeyScheduling(test);

	for (i = 0; i < 16; i++) p[i] = c[i];

	for (i = 0; i < 10; i += 2){
		FuncOdd(p, test->dk[i]);
		FuncEven(p, test->dk[i + 1]);
	}
	FuncOdd(p, test->dk[10]);
	//
	for (i = 0; i < 16; i++) p[i] ^= test->dk[11][i];
	SubstLayerEven(p);
	for (i = 0; i < 16; i++)	p[i] ^= test->dk[12][i];
	
}

void ariaECBKAT(){
	unsigned char k[16];
	unsigned char p[16];
	unsigned char c[16];
	ariaCipher test;

	FILE *f, *out; 
	unsigned char i, suc;

	unsigned char tmp1, tmp2;
	unsigned char type[100], eq[100], content[100];
	out = fopen("ARIA128(ECB)KAT.txt", "w+");
	f = fopen("ARIA128(ECB)KATreq.txt", "r+");

	for (int j = 0; j < 100; j++){

		suc = 1;

		// 키
		fscanf(f, " %s %s %s", type, eq, content);
		fprintf(out, "%s %s %s \n", type, eq, content);
		for (i = 0; i < 16; i++){
			tmp1 = CHAR_TO_HEX(content[i * 2]); tmp2 = CHAR_TO_HEX(content[i * 2 + 1]);
			k[i] = tmp1 * 16 + tmp2;
		}

		// 평문
		fscanf(f, " %s %s %s", type, eq, content);
		fprintf(out, "%s %s %s \n", type, eq, content);
		for (i = 0; i < 16; i++){
			tmp1 = CHAR_TO_HEX(content[i * 2]); tmp2 = CHAR_TO_HEX(content[i * 2 + 1]);
			p[i] = tmp1 * 16 + tmp2;
		}

		// 암호문
		fscanf(f, " %s %s %s", type, eq, content);

		ariaEncryption(c,&test,p,k);

		fprintf(out, "%s %s ", type, eq);
		for (i = 0; i < 16; i++){
			fprintf(out, "%x", c[i]);
		}
		for (i = 0; i < 16; i++){
			content[i * 2] = CHAR_TO_HEX(content[i * 2]); content[i * 2 + 1] = CHAR_TO_HEX(content[i * 2 + 1]);
			if ((content[i * 2] != c[i] / 16) || (content[i * 2 + 1] != c[i] % 16)) {
				suc = 0;
			}
		}
		if (suc) {
			fprintf(out, "\nresult : pass\n\n"); passcount++;
		}
		else {
			fprintf(out, "\nresult: fail\n\n"); failcount++;
		}
		
	}
	fprintf(out, " passcount : %d, failcount : %d \n", passcount, failcount);
	fclose(f);
	fclose(out);
}
void ariaECBMMT(){
	unsigned char k[16];
	unsigned char p[10][16];
	unsigned char c[16];

	ariaCipher test;

	FILE *f, *out; 
	unsigned char i, j, m, suc, count;

	unsigned char tmp1, tmp2;
	unsigned char type[101], eq[101], content[340];
	out = fopen("ARIA128(ECB)MMT.txt", "w+");
	f = fopen("ARIA128(ECB)MMTreq.txt", "r+");
	count = 1;

	for (j = 0; j < 10; j++){
		suc = 1;
		// 키
		fscanf(f, " %s %s %s", type, eq, content);
		fprintf(out, "%s %s %s \n", type, eq, content);
		for (i = 0; i < 16; i++){
			tmp1 = CHAR_TO_HEX(content[i * 2]); tmp2 = CHAR_TO_HEX(content[i * 2 + 1]);
			k[i] = tmp1 * 16 + tmp2;
		}

		// 평문
		fscanf(f, " %s %s %s", type, eq, content);
		fprintf(out, "%s %s %s\n", type, eq, content);

		for (m = 0; m< count; m++){
			for (i = 0; i < 16; i++){
				tmp1 = CHAR_TO_HEX(content[i * 2 + 16 * m * 2]); tmp2 = CHAR_TO_HEX(content[i * 2 + 1 + 16 * m * 2]);
				p[m][i] = tmp1 * 16 + tmp2;
			}
		}


		// 암호문
		fscanf(f, " %s %s %s", type, eq, content);
		fprintf(out, "%s %s ", type, eq);

		for (m = 0; m < count; m++){
			
			ariaEncryption(c, &test, p[m], k);

			for (i = 0; i < 16; i++){ fprintf(out, "%x", c[i]); }

			for (i = 0; i < 16; i++){
				content[i * 2 + 16 * m * 2] = CHAR_TO_HEX(content[i * 2 + 16 * m * 2]); content[i * 2 + 1 + 16 * m * 2] = CHAR_TO_HEX(content[i * 2 + 1 + 16 * m * 2]);
				if ((content[i * 2 + 16 * m * 2] != c[i] / 16) || (content[i * 2 + 1 + 16 * m * 2] != c[i] % 16)) {
					suc = 0;
				}
			}

		}
		if (suc) {
			fprintf(out, "\nresult : pass\n\n"); passcount++;
		}
		else {
			fprintf(out, "\nresult: fail\n\n"); failcount++;
		}

	}
	fprintf(out, " passcount : %d, failcount : %d \n", passcount, failcount);
	fclose(f);
	fclose(out);
}
void ariaECBMCT(){
	unsigned char k[16];
	unsigned char p[16];
	unsigned char c[16];
	
	ariaCipher test;

	FILE *f, *out; 
	unsigned char i, suc;
	int m;

	unsigned char tmp1, tmp2 ;
	unsigned char type[100], eq[100], content[100];
	out = fopen("ARIA128(ECB)MCT.txt", "w+");
	f = fopen("ARIA128(ECB)MCTreq.txt", "r+");

	for (int j = 0; j < 100; j++){

		suc = 1;
		//카운트
		fscanf(f, " %s %s %s", type, eq, content);
		fprintf(out, "%s %s %s \n", type, eq, content);
		// 키
		fscanf(f, " %s %s %s", type, eq, content);
		fprintf(out, "%s %s %s \n", type, eq, content);
		for (i = 0; i < 16; i++){
			tmp1 = CHAR_TO_HEX(content[i * 2]); tmp2 = CHAR_TO_HEX(content[i * 2 + 1]);
			k[i] = tmp1 * 16 + tmp2;
		}

		// 평문
		fscanf(f, " %s %s %s", type, eq, content);
		fprintf(out, "%s %s %s \n", type, eq, content);
		for (i = 0; i < 16; i++){
			tmp1 = CHAR_TO_HEX(content[i * 2]); tmp2 = CHAR_TO_HEX(content[i * 2 + 1]);
			p[i] = tmp1 * 16 + tmp2;
		}

		// 암호문
		fscanf(f, " %s %s %s", type, eq, content);
		fprintf(out, "%s %s ", type, eq);

		for (m = 0; m < 1000; m++){	
			ariaEncryption(c, &test, p, k);
			for (i = 0; i < 16; i++) p[i] = c[i];
		}

		for (i = 0; i < 16; i++){
			fprintf(out, "%x", c[i]);
		}
		for (i = 0; i < 16; i++){
			content[i * 2] = CHAR_TO_HEX(content[i * 2]); content[i * 2 + 1] = CHAR_TO_HEX(content[i * 2 + 1]);
			if ((content[i * 2] != c[i] / 16) || (content[i * 2 + 1] != c[i] % 16)) {
				suc = 0;
			}
		}
		if (suc) {
			fprintf(out, "\nresult : pass\n\n"); passcount++;
		}
		else {
			fprintf(out, "\nresult: fail\n\n"); failcount++;
		}

	}
	fprintf(out, " passcount : %d, failcount : %d \n", passcount, failcount);
	fclose(f);
	fclose(out);
}

void ariaCBCKAT(){
	unsigned char k[16];
	unsigned char p[16];
	unsigned char c[16];
	unsigned char iv[16];
	ariaCipher test;

	FILE *f, *out; 
	unsigned char i, suc;

	unsigned char tmp1, tmp2;
	unsigned char type[100], eq[100], content[100];
	out = fopen("ARIA128(CBC)KAT.txt", "w+");
	f = fopen("ARIA128(CBC)KATreq.txt", "r+");


	for (int j = 0; j < 100; j++){

		suc = 1;

		// 키
		fscanf(f, " %s %s %s", type, eq, content);
		fprintf(out, "%s %s %s \n", type, eq, content);
		for (i = 0; i < 16; i++){
			tmp1 = CHAR_TO_HEX(content[i * 2]); tmp2 = CHAR_TO_HEX(content[i * 2 + 1]);
			k[i] = tmp1 * 16 + tmp2;
		}

		// 초기화 벡터
		fscanf(f, " %s %s %s", type, eq, content);
		fprintf(out, "%s %s %s \n", type, eq, content);
		for (i = 0; i < 16; i++){
			tmp1 = CHAR_TO_HEX(content[i * 2]); tmp2 = CHAR_TO_HEX(content[i * 2 + 1]);
			iv[i] = tmp1 * 16 + tmp2;
		}

		// 평문
		fscanf(f, " %s %s %s", type, eq, content);
		fprintf(out, "%s %s %s \n", type, eq, content);
		for (i = 0; i < 16; i++){
			tmp1 = CHAR_TO_HEX(content[i * 2]); tmp2 = CHAR_TO_HEX(content[i * 2 + 1]);
			p[i] = tmp1 * 16 + tmp2;
		}

		// 암호문
		fscanf(f, " %s %s %s", type, eq, content);

		// p^iv
		for (i = 0; i < 16; i++) p[i] ^= iv[i];

		ariaEncryption(c, &test, p, k);

		fprintf(out, "%s %s ", type, eq);
		for (i = 0; i < 16; i++){
			fprintf(out, "%x", c[i]);
		}
		for (i = 0; i < 16; i++){
			content[i * 2] = CHAR_TO_HEX(content[i * 2]); content[i * 2+1] = CHAR_TO_HEX(content[i * 2+1]);
			if ( (content[i * 2] != c[i] / 16) || (content[i * 2 + 1] != c[i] % 16)) {
				suc = 0;
			}
		}
		if (suc) {
			fprintf(out, "\nresult : pass\n\n"); passcount++;
		}
		else {
			fprintf(out, "\nresult: fail\n\n"); failcount++;
		}
	}
	fprintf(out, " passcount : %d, failcount : %d \n", passcount, failcount);
	fclose(f);
	fclose(out);
}
void ariaCBCMMT(){
	unsigned char k[16];
	unsigned char p[10][16];
	unsigned char c[16];
	unsigned char iv[16];
	ariaCipher test;

	FILE *f, *out; 
	unsigned char i, j,m,suc, count;

	unsigned char tmp1, tmp2;
	unsigned char type[101], eq[101], content[320];
	out = fopen("ARIA128(CBC)MMT.txt", "w+");
	f = fopen("ARIA128(CBC)MMTreq.txt", "r+");
	count = 1;

	for (j = 0; j < 10; j++){
		suc = 1;
		// 키
		fscanf(f, " %s %s %s", type, eq, content);
		fprintf(out, "%s %s %s \n", type, eq, content);
		for (i = 0; i < 16; i++){
			tmp1 = CHAR_TO_HEX(content[i * 2]); tmp2 = CHAR_TO_HEX(content[i * 2 + 1]);
			k[i] = tmp1 * 16 + tmp2;
		}

		// 초기화 벡터
		fscanf(f, " %s %s %s", type, eq, content);
		fprintf(out, "%s %s %s \n", type, eq, content);
		for (i = 0; i < 16; i++){
			tmp1 = CHAR_TO_HEX(content[i * 2]); tmp2 = CHAR_TO_HEX(content[i * 2 + 1]);
			iv[i] = tmp1 * 16 + tmp2;
		}

		// 평문
		fscanf(f, " %s %s %s", type, eq, content);
		fprintf(out, "%s %s %s\n", type, eq, content);
		
		for (m = 0; m< count; m++){
			for (i = 0; i < 16; i++){	
				tmp1 = CHAR_TO_HEX(content[i * 2+16*m*2]); tmp2 = CHAR_TO_HEX(content[i * 2 + 1+16*m*2]);
				p[m][i] = tmp1 * 16 + tmp2;
			}
		}
		

		// 암호문
		fscanf(f, " %s %s %s", type, eq, content); 
		fprintf(out, "%s %s ", type, eq);
	
		for (m = 0; m < count; m++){
			// p^iv

			for (i = 0; i < 16; i++) p[m][i] ^= iv[i];
			
			ariaEncryption(c, &test, p[m], k);
			for (i = 0; i < 16; i++) iv[i] = c[i];
			
			for (i = 0; i < 16; i++){ fprintf(out, "%x", c[i]);}
			
			for (i = 0; i < 16; i++){
				content[i * 2 + 16 * m * 2] = CHAR_TO_HEX(content[i * 2 + 16 * m * 2]); content[i * 2 + 1 + 16 * m * 2] = CHAR_TO_HEX(content[i * 2 + 1 + 16 * m * 2]);
				if ((content[i * 2 + 16 * m * 2] != c[i] / 16) || (content[i * 2 + 1 + 16 * m * 2] != c[i] % 16)) {
					suc = 0;
				}
			}
			
		} 
		if (suc) {
			fprintf(out, "\nresult : pass\n\n"); passcount++;
		}
		else {
			fprintf(out, "\nresult: fail\n\n"); failcount++;
		}
	}
	fprintf(out, " passcount : %d, failcount : %d \n", passcount, failcount);
	fclose(f);
	fclose(out);
}
void ariaCBCMCT(){
	unsigned char k[16];
	unsigned char p[16];
	unsigned char c[16];
	unsigned char iv[16];
	ariaCipher test;

	FILE *f, *out;
	unsigned char i,suc;
	int m;

	unsigned char tmp1, tmp2;
	unsigned char type[100], eq[100], content[100];
	out = fopen("ARIA128(CBC)MCT.txt", "w+");
	f = fopen("ARIA128(CBC)MCTreq.txt", "r+");

	for (int j = 0; j < 100; j++){

		suc = 1;
		//카운트
		fscanf(f, " %s %s %s", type, eq, content);
		fprintf(out, "%s %s %s \n", type, eq, content);
		// 키
		fscanf(f, " %s %s %s", type, eq, content);
		fprintf(out, "%s %s %s \n", type, eq, content);
		for (i = 0; i < 16; i++){
			tmp1 = CHAR_TO_HEX(content[i * 2]); tmp2 = CHAR_TO_HEX(content[i * 2 + 1]);
			k[i] = tmp1 * 16 + tmp2;
		}

		// 초기화 벡터
		fscanf(f, " %s %s %s", type, eq, content);
		fprintf(out, "%s %s %s \n", type, eq, content);
		for (i = 0; i < 16; i++){
			tmp1 = CHAR_TO_HEX(content[i * 2]); tmp2 = CHAR_TO_HEX(content[i * 2 + 1]);
			iv[i] = tmp1 * 16 + tmp2;
		}

		// 평문
		fscanf(f, " %s %s %s", type, eq, content);
		fprintf(out, "%s %s %s \n", type, eq, content);
		for (i = 0; i < 16; i++){
			tmp1 = CHAR_TO_HEX(content[i * 2]); tmp2 = CHAR_TO_HEX(content[i * 2 + 1]);
			p[i] = tmp1 * 16 + tmp2;
		}

		// 암호문
		fscanf(f, " %s %s %s", type, eq, content);
		fprintf(out, "%s %s ", type, eq);
		// p^iv
		for (m = 0; m < 1000; m++){
			for (i = 0; i < 16; i++) p[i] ^= iv[i];
			ariaEncryption(c, &test, p, k);
			for (i = 0; i < 16; i++) p[i] = iv[i];
			for (i = 0; i<16; i++) iv[i] = c[i];

		}
		
		for (i = 0; i < 16; i++){
			fprintf(out, "%x", c[i]);
		}
		for (i = 0; i < 16; i++){
			content[i * 2] = CHAR_TO_HEX(content[i * 2]); content[i * 2 + 1] = CHAR_TO_HEX(content[i * 2 + 1]);
			if ((content[i * 2] != c[i] / 16) || (content[i * 2 + 1] != c[i] % 16)) {
				suc = 0;
			}
		}
		if (suc) {
			fprintf(out, "\nresult : pass\n\n"); passcount++;
		}
		else {
			fprintf(out, "\nresult: fail\n\n"); failcount++;
		}

	}
	fprintf(out, " passcount : %d, failcount : %d \n", passcount, failcount);
	fclose(f);
	fclose(out);
}

void ariaCTRKAT(){
	unsigned char k[16];
	unsigned char p[16];
	unsigned char c[16];
	unsigned char iv[16];
	ariaCipher test;

	FILE *f, *out; 
	unsigned char i, suc;

	unsigned char tmp1, tmp2;
	unsigned char type[100], eq[100], content[100];
	out = fopen("ARIA128(CTR)KAT.txt", "w+");
	f = fopen("ARIA128(CTR)KATreq.txt", "r+");

	for (int j = 0; j < 100; j++){

		suc = 1;

		// 키
		fscanf(f, " %s %s %s", type, eq, content);
		fprintf(out, "%s %s %s \n", type, eq, content);
		for (i = 0; i < 16; i++){
			tmp1 = CHAR_TO_HEX(content[i * 2]); tmp2 = CHAR_TO_HEX(content[i * 2 + 1]);
			k[i] = tmp1 * 16 + tmp2;
		}

		// 초기화 벡터
		fscanf(f, " %s %s %s", type, eq, content);
		fprintf(out, "%s %s %s \n", type, eq, content);
		for (i = 0; i < 16; i++){
			tmp1 = CHAR_TO_HEX(content[i * 2]); tmp2 = CHAR_TO_HEX(content[i * 2 + 1]);
			iv[i] = tmp1 * 16 + tmp2;
		}

		// 평문
		fscanf(f, " %s %s %s", type, eq, content);
		fprintf(out, "%s %s %s \n", type, eq, content);
		for (i = 0; i < 16; i++){
			tmp1 = CHAR_TO_HEX(content[i * 2]); tmp2 = CHAR_TO_HEX(content[i * 2 + 1]);
			p[i] = tmp1 * 16 + tmp2;
		}

		// 암호문
		fscanf(f, " %s %s %s", type, eq, content);

		ariaEncryption(c, &test, iv, k);

		// p^c
		for (i = 0; i < 16; i++) c[i] ^= p[i];

		fprintf(out, "%s %s ", type, eq);
		for (i = 0; i < 16; i++){
			fprintf(out, "%x", c[i]);
		}
		for (i = 0; i < 16; i++){
			content[i * 2] = CHAR_TO_HEX(content[i * 2]); content[i * 2 + 1] = CHAR_TO_HEX(content[i * 2 + 1]);
			if ((content[i * 2] != c[i] / 16) || (content[i * 2 + 1] != c[i] % 16)) {
				suc = 0;
			}
		}
		if (suc) {
			fprintf(out, "\nresult : pass\n\n"); passcount++;
		}
		else {
			fprintf(out, "\nresult: fail\n\n"); failcount++;
		}
	}
	fprintf(out, " passcount : %d, failcount : %d \n", passcount, failcount);
	fclose(f);
	fclose(out);
}
void ariaCTRMMT(){
	unsigned char k[16];
	unsigned char p[10][16];
	unsigned char c[16];
	unsigned char iv[16];
	ariaCipher test;

	FILE *f, *out; 
	unsigned char i, j, m, suc, count;

	unsigned char tmp1, tmp2;
	unsigned char type[101], eq[101], content[340];
	out = fopen("ARIA128(CTR)MMT.txt", "w+");
	f = fopen("ARIA128(CTR)MMTreq.txt", "r+");
	count = 1;

	for (j = 0; j < 10; j++){
		suc = 1;
		// 키
		fscanf(f, " %s %s %s", type, eq, content);
		fprintf(out, "%s %s %s \n", type, eq, content);
		for (i = 0; i < 16; i++){
			tmp1 = CHAR_TO_HEX(content[i * 2]); tmp2 = CHAR_TO_HEX(content[i * 2 + 1]);
			k[i] = tmp1 * 16 + tmp2;
		}

		// 초기화 벡터
		fscanf(f, " %s %s %s", type, eq, content);
		fprintf(out, "%s %s %s \n", type, eq, content);
		for (i = 0; i < 16; i++){
			tmp1 = CHAR_TO_HEX(content[i * 2]); tmp2 = CHAR_TO_HEX(content[i * 2 + 1]);
			iv[i] = tmp1 * 16 + tmp2;
		}

		// 평문
		fscanf(f, " %s %s %s", type, eq, content);
		fprintf(out, "%s %s %s\n", type, eq, content);

		for (m = 0; m< count; m++){
			for (i = 0; i < 16; i++){
				tmp1 = CHAR_TO_HEX(content[i * 2 + 16 * m * 2]); tmp2 = CHAR_TO_HEX(content[i * 2 + 1 + 16 * m * 2]);
				p[m][i] = tmp1 * 16 + tmp2;
			}
		}


		// 암호문
		fscanf(f, " %s %s %s", type, eq, content);
		fprintf(out, "%s %s ", type, eq);

		for (m = 0; m < count; m++){
		

			ariaEncryption(c, &test, iv, k);

			// p^iv
			for (i = 0; i < 16; i++) c[i] ^= p[m][i];

			//카운터값 증가 
			for(i = 15; i >= 0; i--) {
				if (iv[i] < 0xff) { iv[i]++; break; }
				else iv[i] = 0;
			}

			for (i = 0; i < 16; i++){ fprintf(out, "%x", c[i]); }

			for (i = 0; i < 16; i++){
				content[i * 2 + 16 * m * 2] = CHAR_TO_HEX(content[i * 2 + 16 * m * 2]); content[i * 2 + 1 + 16 * m * 2] = CHAR_TO_HEX(content[i * 2 + 1 + 16 * m * 2]);
				if ((content[i * 2 + 16 * m * 2] != c[i] / 16) || (content[i * 2 + 1 + 16 * m * 2] != c[i] % 16)) {
					suc = 0;
				}
			}

		}
		if (suc) {
			fprintf(out, "\nresult : pass\n\n"); passcount++;
		}
		else {
			fprintf(out, "\nresult: fail\n\n"); failcount++;
		}
		count++;
	}
	fprintf(out, " passcount : %d, failcount : %d \n", passcount, failcount);
	fclose(f);
	fclose(out);
}
void ariaCTRMCT(){
	unsigned char k[16];
	unsigned char p[16];
	unsigned char c[16];
	unsigned char iv[16];
	ariaCipher test;

	FILE *f, *out;
	unsigned char i, suc;
	int m;

	unsigned char tmp1, tmp2;
	unsigned char type[100], eq[100], content[100];
	out = fopen("ARIA128(CTR)MCT.txt", "w+");
	f = fopen("ARIA128(CTR)MCTreq.txt", "r+");

	for (int j = 0; j < 100; j++){

		suc = 1;
		//카운트
		fscanf(f, " %s %s %s", type, eq, content);
		fprintf(out, "%s %s %s \n", type, eq, content);

		// 키
		fscanf(f, " %s %s %s", type, eq, content);
		fprintf(out, "%s %s %s \n", type, eq, content);
		for (i = 0; i < 16; i++){
			tmp1 = CHAR_TO_HEX(content[i * 2]); tmp2 = CHAR_TO_HEX(content[i * 2 + 1]);
			k[i] = tmp1 * 16 + tmp2;
		}

		// 초기화 벡터
		fscanf(f, " %s %s %s", type, eq, content);
		fprintf(out, "%s %s %s \n", type, eq, content);
		for (i = 0; i < 16; i++){
			tmp1 = CHAR_TO_HEX(content[i * 2]); tmp2 = CHAR_TO_HEX(content[i * 2 + 1]);
			iv[i] = tmp1 * 16 + tmp2;
		}

		// 평문
		fscanf(f, " %s %s %s", type, eq, content);
		fprintf(out, "%s %s %s \n", type, eq, content);
		for (i = 0; i < 16; i++){
			tmp1 = CHAR_TO_HEX(content[i * 2]); tmp2 = CHAR_TO_HEX(content[i * 2 + 1]);
			p[i] = tmp1 * 16 + tmp2;
		}

		// 암호문
		fscanf(f, " %s %s %s", type, eq, content);
		fprintf(out, "%s %s ", type, eq);

		for (m = 0; m < 1000; m++){
			
			ariaEncryption(c, &test, iv, k);
			// p^c
			for (i = 0; i < 16; i++) c[i] ^= p[i];

			//카운터값 증가 
			for (i = 15; i >= 0; i--) {
				if (iv[i] < 0xff) { iv[i]++; break; }
				else iv[i] = 0;
			}
	
			//p[m+1]=c[m]
			for (i = 0; i < 16; i++) p[i] = c[i];
		}

		for (i = 0; i < 16; i++){
			fprintf(out, "%x", c[i]);
		}
		for (i = 0; i < 16; i++){
			content[i * 2] = CHAR_TO_HEX(content[i * 2]); content[i * 2 + 1] = CHAR_TO_HEX(content[i * 2 + 1]);
			if ((content[i * 2] != c[i] / 16) || (content[i * 2 + 1] != c[i] % 16)) {
				suc = 0;
			}
		}
		if (suc) {
			fprintf(out, "\nresult : pass\n\n"); passcount++;
		}
		else {
			fprintf(out, "\nresult: fail\n\n"); failcount++;
		}

	}
	fprintf(out, " passcount : %d, failcount : %d \n", passcount, failcount);
	fclose(f);
	fclose(out);
}
