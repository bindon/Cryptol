/**
  Copyright © 2017 Odzhan. All Rights Reserved.

  Redistribution and use in source and binary forms, with or without
  modification, are permitted provided that the following conditions are
  met:

  1. Redistributions of source code must retain the above copyright
  notice, this list of conditions and the following disclaimer.

  2. Redistributions in binary form must reproduce the above copyright
  notice, this list of conditions and the following disclaimer in the
  documentation and/or other materials provided with the distribution.

  3. The name of the author may not be used to endorse or promote products
  derived from this software without specific prior written permission.

  THIS SOFTWARE IS PROVIDED BY AUTHORS "AS IS" AND ANY EXPRESS OR
  IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
  WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  DISCLAIMED. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT,
  INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
  (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
  HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
  STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
  ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
  POSSIBILITY OF SUCH DAMAGE. */

#ifndef LEA_H
#define LEA_H

#include "macros.h"
  
#define LEA128_RNDS 24
#define LEA192_RNDS 28
#define LEA256_RNDS 32

typedef struct _lea_ctx_t {
    uint64_t key[LEA256_RNDS];
} lea_ctx;

typedef union _w32_t {
    uint8_t  b[4];
    uint32_t w;
} w32_t;
 
typedef union _w64_t {
    uint8_t  b[8];
    uint32_t w[2];
    uint64_t q;
} w64_t;

#ifdef __cplusplus
extern "C" {
#endif

  void lea128_setkey(void*, void*);
  void lea128_encrypt(void*, void*);
  void lea128_encrypt_single(void*, void*);
  void lea128_encryptx(void*, void*);

  void lea256_setkey(void*, void*);
  void lea256_encrypt(void*, void*);
    
#ifdef __cplusplus
}
#endif

#endif

