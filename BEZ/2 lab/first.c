#include <stdio.h>
#include <string.h>
#include <openssl/evp.h>

int main(int argc, char *argv[])
{

    int i, res;
    char text[] = "HoJ";
    char hashFunction[] = "sha256";  // zvolena hashovaci funkce ("sha1", "md5" ...)
    char hashString[64];

    EVP_MD_CTX *ctx;  // struktura kontextu
    const EVP_MD *type; // typ pouzite hashovaci funkce
    unsigned char hash[EVP_MAX_MD_SIZE]; // char pole pro hash - 64 bytu (max pro sha 512)
    int length;  // vysledna delka hashe

    /* Inicializace OpenSSL hash funkci */
    OpenSSL_add_all_digests();
    /* Zjisteni, jaka hashovaci funkce ma byt pouzita */
    type = EVP_get_digestbyname(hashFunction);

    /* Pokud predchozi prirazeni vratilo -1, tak nebyla zadana spravne hashovaci funkce */
    if(!type)
    {
        printf("Hash %s neexistuje.\n", hashFunction);
        exit(1);
    }

    ctx = EVP_MD_CTX_create(); // create context for hashing
    if(ctx == NULL)
        exit(2);

    for(int j = 0; j < 255; j++)
    {
        for(int z = 0; z < 255; z++)
        {
            for(int k = 0; k < 255; k++)
            {

                text[0] = (char)j;
                text[1] = (char)z;
                text[2] = (char)k;

                res = EVP_DigestInit_ex(ctx, type, NULL); // context setup for our hash type
                if(res != 1)
                    exit(3);

                res = EVP_DigestUpdate(ctx, text, strlen(text)); // feed the message in
                if(res != 1)
                    exit(4);
                res = EVP_DigestFinal_ex(ctx, hash, (unsigned int *) &length); // get the hash
                if(res != 1)
                    exit(5);

                for(int i = 0; i < length; i++)
                {
                    sprintf(hashString + i, "%02x", hash[i]);
                }

                if(hashString[0] == 'a' && hashString[1] == 'a' && hashString[2] == 'b' && hashString[3] == 'b')
                {
                    /* Vypsani vysledneho hashe */
                    printf("For text: %s hash: %s",text, hashString);
                    printf("\n");
                }
            }
        }
    }

    /* Hash the text */

    EVP_MD_CTX_destroy(ctx); // destroy the context


    exit(0);
}
