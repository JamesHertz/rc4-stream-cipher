#include "rc4.h"

// works only for pointers and integers c:
#define swap(fst, snd) do {  \
        *fst = *snd ^ *fst;  \
        *snd = *fst ^ *snd;  \
        *fst = *snd ^ *fst;  \
    }while(0)

void rc4_init(rc4_ctx_t * ctx, secret_key_t key){
    uint8_t tmp[STATE_SIZE];

    uint8_t * state = ctx->state;

    // initialization
    for(size_t i = 0; i < STATE_SIZE; i++){
        state[i] = i;
        tmp[i] = key.key_data[ i % key.key_size ];
    }

    // initial permutation
    for(size_t i = 0; i < STATE_SIZE; i++){
        size_t j = (i + state[i] + tmp[i]) % STATE_SIZE;
        swap(&state[i], &state[j]);
    }

    ctx->i = ctx->j = 0;
}

uint8_t rc4_encrypt(rc4_ctx_t * ctx, uint8_t byte){
    uint8_t * state = ctx->state;
    size_t i = ctx->i + 1;
    size_t j = (ctx->state[i] + ctx->j) % STATE_SIZE;

    swap(&state[i], &state[j]);

    size_t t = (state[i] + state[j]) % STATE_SIZE;
    uint8_t sub_key = state[t];
    return byte ^ sub_key;
}
