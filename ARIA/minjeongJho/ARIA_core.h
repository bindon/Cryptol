#pragma once
#include<stdio.h>

typedef struct{
        unsigned char ek[13][16];
        unsigned char dk[13][16];
}ariaCipher;

unsigned char Sbox[4][256];
unsigned char c[3][16];

void SubstLayerOdd(unsigned char *y);
void SubstLayerEven(unsigned char *y);

void DiffLayer(unsigned char *y);

void FuncOdd(unsigned char* y, unsigned char* x);
void FuncEven(unsigned char* y, unsigned char* x);

unsigned char* rotXor(unsigned char *tmp, unsigned char *w, unsigned char num);
unsigned char* rotXorleft(unsigned char *tmp, unsigned char *w, unsigned char num);

void KeyScheduling(ariaCipher *test, unsigned char* k);
void decKeyScheduling(ariaCipher* test);

void ariaEncryption(unsigned char* c, ariaCipher* test, unsigned char*p, unsigned char *k);
void ariaDecryption(unsigned char* c, ariaCipher* test, unsigned char*p, unsigned char *k);

void ariaECBKAT();
void ariaECBMMT();
void ariaECBMCT();

void ariaCBCKAT();
void ariaCBCMMT();
void ariaCBCMCT();

void ariaCTRKAT();
void ariaCTRMMT();
void ariaCTRMCT();
