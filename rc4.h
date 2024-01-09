#ifndef __JH_RC4__
#define __JH_RC4__

#include <stdint.h>
#include <stdio.h>

#define STATE_SIZE 256

typedef struct {
    uint8_t * key_data;
    size_t key_size;
} secret_key_t;

typedef struct {
    uint8_t state[STATE_SIZE];
    size_t i, j;
} rc4_ctx_t;

void rc4_init(rc4_ctx_t * ctx, secret_key_t key);
uint8_t rc4_encrypt(rc4_ctx_t * ctx, uint8_t byte);

#endif
