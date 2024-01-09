# RC4

Simple RC4 implementation on c. The program receives 3 arguments: `<secret-key-hex>` which is the rc4 variable size secret key in hexadecimal (may or may not start with 0x), it also receives `<src-filename>` and `<dst-filename>` which are respectively the name of the file with the contents to be encrypted/decrypted and the file that will contain the encrypted/decrypted data.

For example to encrypt this README with the secret key `0xabcd` we would run:
```sh
$ ./main  0xabcd README.md README-CIPHER-TXT.md
```
and to decrypt:
```sh
$ ./main 0xabcd README-CIPHER-TXT.md README-PLAIN-TXT.md
```

# Building Instruction
To build the project just run the following:
```sh
$ make
```


# TODOs:
- [ ] Validate that the key size is in the range [1, 256]