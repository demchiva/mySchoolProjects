#include "stdio.h"
#include "stdlib.h"
#include "unistd.h"
#include "string.h"

#include <openssl/evp.h>
#include <openssl/pem.h>
#include <openssl/rand.h>

/**
  * created by demchiva
  */

int evp_decrypt(FILE *rsa_pkey_file, FILE *in_file, FILE *out_file)
{
    EVP_CIPHER_CTX ctx;
    RSA *rsaPrivateKey = NULL;
    EVP_PKEY *evpPrivateKey = EVP_PKEY_new();

    unsigned char buffer[4096];
    unsigned char buffer_out[4096 + EVP_MAX_IV_LENGTH];
    size_t readBytes;
    int outLength;

    unsigned char *ek;
    unsigned int ekLength;

    unsigned char iv[EVP_MAX_IV_LENGTH];

    if (RAND_load_file("/dev/random", 32) != 32)
        return 1;

    if (!PEM_read_RSAPrivateKey(rsa_pkey_file, &rsaPrivateKey, NULL, NULL))
        return 1;

    if (!EVP_PKEY_assign_RSA(evpPrivateKey, rsaPrivateKey))
        return 1;

    EVP_CIPHER_CTX_init(&ctx);
    ek = (unsigned char *) malloc(EVP_PKEY_size(evpPrivateKey));

    if (fread(&ekLength, sizeof ekLength, 1, in_file) != 1)
    {
        EVP_PKEY_free(evpPrivateKey);
        free(ek);
        return 1;
    }

    if (ekLength > EVP_PKEY_size(evpPrivateKey))
    {
        EVP_PKEY_free(evpPrivateKey);
        free(ek);
        return 1;
    }

    if (fread(ek, ekLength, 1, in_file) != 1)
    {
        EVP_PKEY_free(evpPrivateKey);
        free(ek);
        return 1;
    }

    if (fread(iv, EVP_CIPHER_iv_length(EVP_aes_128_cbc()), 1, in_file) != 1)
    {
        EVP_PKEY_free(evpPrivateKey);
        free(ek);
        return 1;
    }

    if (!EVP_OpenInit(&ctx, EVP_aes_128_cbc(), ek, ekLength, iv, evpPrivateKey))
    {
        EVP_PKEY_free(evpPrivateKey);
        free(ek);
        return 1;
    }

    while ((readBytes = fread(buffer, 1, sizeof buffer, in_file)) > 0)
    {
        if (!EVP_OpenUpdate(&ctx, buffer_out, &outLength, buffer, readBytes))
        {
            EVP_PKEY_free(evpPrivateKey);
            free(ek);
            return 1;
        }

        if (fwrite(buffer_out, outLength, 1, out_file) != 1)
        {
            EVP_PKEY_free(evpPrivateKey);
            free(ek);
            return 1;
        }
    }

    if (ferror(in_file))
    {
        EVP_PKEY_free(evpPrivateKey);
        free(ek);
        return 1;
    }

    if (!EVP_OpenFinal(&ctx, buffer_out, &outLength))
    {
        EVP_PKEY_free(evpPrivateKey);
        free(ek);
        return 1;
    }

    if (fwrite(buffer_out, outLength, 1, out_file) != 1)
    {
        EVP_PKEY_free(evpPrivateKey);
        free(ek);
        return 1;
    }


    EVP_PKEY_free(evpPrivateKey);
    free(ek);

    return 0;
}

int evp_encrypt(FILE *rsaPublicKeyFile, FILE *inFile, FILE *outFile)
{
    EVP_CIPHER_CTX ctx;
    RSA *rsaPublicKey = NULL;
    EVP_PKEY *evpPrivateKey = EVP_PKEY_new();

    unsigned char buffer[4096];
    unsigned char buffer_out[4096 + EVP_MAX_IV_LENGTH];
    size_t readBytes;
    int outLength;

    unsigned char *ek = NULL;
    int ekLength;

    unsigned char iv[EVP_MAX_IV_LENGTH];

    if (RAND_load_file("/dev/random", 32) != 32)
        return 1;

    if (!PEM_read_RSA_PUBKEY(rsaPublicKeyFile, &rsaPublicKey, NULL, NULL))
        return 2;

    if (!EVP_PKEY_assign_RSA(evpPrivateKey, rsaPublicKey))
        return 3;

    EVP_CIPHER_CTX_init(&ctx);
    ek = (unsigned char *) malloc(EVP_PKEY_size(evpPrivateKey));

    if (!EVP_SealInit(&ctx, EVP_aes_128_cbc(), &ek, &ekLength, iv, &evpPrivateKey, 1))
    {
        EVP_PKEY_free(evpPrivateKey);
        free(ek);
        return 4;
    }

    if (fwrite(&ekLength, sizeof ekLength, 1, outFile) != 1)
    {
        EVP_PKEY_free(evpPrivateKey);
        free(ek);
        return 5;
    }

    if (fwrite(ek, ekLength, 1, outFile) != 1)
    {
        EVP_PKEY_free(evpPrivateKey);
        free(ek);
        return 6;
    }

    if (fwrite(iv, EVP_CIPHER_iv_length(EVP_aes_128_cbc()), 1, outFile) != 1)
    {
        EVP_PKEY_free(evpPrivateKey);
        free(ek);
        return 7;
    }

    while ((readBytes = fread(buffer, 1, sizeof buffer, inFile)) > 0)
    {
        if (!EVP_SealUpdate(&ctx, buffer_out, &outLength, buffer, readBytes))
        {
            EVP_PKEY_free(evpPrivateKey);
            free(ek);
            return 8;
        }

        if (fwrite(buffer_out, outLength, 1, outFile) != 1)
        {
            EVP_PKEY_free(evpPrivateKey);
            free(ek);
            return 9;
        }
    }

    if (ferror(inFile))
    {
        EVP_PKEY_free(evpPrivateKey);
        free(ek);
        return 10;
    }

    if (!EVP_SealFinal(&ctx, buffer_out, &outLength))
    {
        EVP_PKEY_free(evpPrivateKey);
        free(ek);
        return 11;
    }

    if (fwrite(buffer_out, outLength, 1, outFile) != 1)
    {
        EVP_PKEY_free(evpPrivateKey);
        free(ek);
        return 12;
    }

    EVP_PKEY_free(evpPrivateKey);
    free(ek);
    return 0;
}

int main(int argc, char *argv[])
{
    FILE *rsa_pkey_file;
    FILE *in_file;
    FILE *out_file;
    int rv;

    if (argc != 5)
    {
        printf("Bad count of argument\n");
        return 1;
    }

    rsa_pkey_file = fopen(argv[2], "rb");
    in_file = fopen(argv[3], "rb");
    out_file = fopen(argv[4], "wb");

    if (!rsa_pkey_file || !in_file || !out_file)
    {
        printf("Error of open file\n");
        return 1;
    }

    if (!strcmp(argv[1], "-e"))
    {
        rv = evp_encrypt(rsa_pkey_file, in_file, out_file);
    } else
           if(!strcmp(argv[1], "-d"))
           {
               rv = evp_decrypt(rsa_pkey_file, in_file, out_file);
           } else {
                      printf("Error of argument\n");
                      rv = 1;
                  }

    fclose(rsa_pkey_file);
    fclose(in_file);
    fclose(out_file);
    return rv;
}
