#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "rc4.h"

secret_key_t parse_key(const char * key_hex) {

    if( strncmp("0x", key_hex, 2) == 0 ) {
        key_hex += 2;
    }

    size_t hex_size  = strlen(key_hex);

    size_t rem = hex_size % 2;
    size_t key_size  = (hex_size / 2) + rem;

    uint8_t * key_data = malloc( key_size );
    assert(key_data != NULL);

    // TODO: find a better solution c:
    if(rem == 1){
        int err = sscanf(key_hex, "%1hhx", key_data);
        if( err == 0 ){
            fprintf(stderr, "ERROR: Invalid keyhex: %s\n", key_hex);
            exit(1);
        }
    }

    for(size_t i = rem; i < key_size; i++){
        // TODO: find a better solution c:
        const char * str = &key_hex[ i*2 - rem ];
        int err = sscanf(str, "%2hhx", &key_data[i]);
        if( err == 0 ){
            fprintf(stderr, "ERROR: Invalid keyhex: %s\n", key_hex);
            exit(1);
        }
    }

    return (secret_key_t) {
        .key_data = key_data,
        .key_size = key_size
    }; 
}


FILE * must_openfile(char * filename, char * mode){
    FILE * file = fopen(filename, mode);
    if( file == NULL ) {
       char * msg;
       asprintf(
           &msg, "Error opening file '%s'", filename
       );

       perror(msg);
       // free(msg); (no need since the program will end anyway)
       exit(1);
    }

    return file;
}

void print_secret_key(secret_key_t key){
   printf("0x");
   for(size_t i = 0; i < key.key_size; i++){
       printf("%02x", key.key_data[i]);
   }
   putchar('\n');
}

void encrypt_file(secret_key_t key, FILE * src, FILE * dst){
    rc4_ctx_t ctx;
    rc4_init(&ctx, key);

    uint8_t curr;
    while(fread(&curr, 1, 1, src)){
        uint8_t enc = rc4_encrypt(&ctx, curr);
        fwrite(&enc, 1, 1, dst);
    }
}

int main(int argc, char *argv[]) {
   if ( argc < 4 ) { 
        fprintf(stderr, 
           "ERROR: missing arguments\n" 
           "usage: %s <secret-key-hex> <src-file> <dst-file>\n", argv[0]
        );
        exit(1);
   }
   
   char * key_hex  = argv[1];
   char * src_filename = argv[2];
   char * dst_filename = argv[3];
   
   secret_key_t key = parse_key(key_hex);
   
   printf("secret key   : "); print_secret_key(key);
   printf("src filename : %s\n", src_filename);
   printf("dst filename : %s\n", dst_filename);
   printf("--------------------\n\n");
   
   FILE * src = must_openfile(src_filename, "r");
   FILE * dst = must_openfile(dst_filename, "w");
   
   printf("Encrypting...\n");
   encrypt_file(key, src, dst);
   
   printf("DONE!!\n");
   
   fclose(src);
   fclose(dst);
   
   
   return 0;
}
