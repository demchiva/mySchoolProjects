#include <stdlib.h>
#include <stdio.h>
#include <openssl/evp.h>
#include <string.h>
#include <iostream>

 // created by demchiva

int des(char * ReadName, char * WriteName, unsigned char * key, unsigned char * iv, const EVP_CIPHER* (*fun)(void), bool encrypt)
{

  unsigned char header[36];
  unsigned char Cipher[8];
  unsigned char OT[8];

  memset(Cipher, 0, 8);
  memset(header, 0, 36);

  EVP_CIPHER_CTX ctx;
  EVP_CIPHER_CTX_init(&ctx);

  const char cipherName[] = "des";
  const EVP_CIPHER * cipher;

  OpenSSL_add_all_ciphers();
  cipher = EVP_get_cipherbyname(cipherName);
  if(!cipher)
  {
      printf("Cipher %s not exist.\n", cipherName);
      return 1;
  }

  FILE * src = fopen(ReadName, "rb");

  if(src == NULL)
  {
    std::cout << "Error of open source file" << std::endl;
    return 1;
  }

  FILE * dst = fopen(WriteName, "wb");

  if(dst == NULL)
  {
    std::cout << "Error of open destination file" << std::endl;
    return 1;
  }

  fread((void *)header, 1, 36, src);
  fwrite((void *)header, 1, 36, dst);

  int tmpLength = 0;
  size_t read = 0;

  EVP_CipherInit_ex(&ctx, fun(), NULL, key, iv, encrypt);

  while ((read = fread(OT, 1, 8, src)) > 0)
  {
      if (! EVP_CipherUpdate(&ctx, Cipher, &tmpLength, OT, read))
      {
        EVP_CIPHER_CTX_cleanup(&ctx);
        fclose(src);
        fclose(dst);
        return 1;
      }

      fwrite(Cipher, 1, tmpLength, dst);
  }

  if (! EVP_CipherFinal_ex(&ctx, Cipher, &tmpLength))
  {
    EVP_CIPHER_CTX_cleanup(&ctx);
    fclose(src);
    fclose(dst);
    return 1;
  }

  fwrite(Cipher, 1, tmpLength, dst);

  EVP_CIPHER_CTX_cleanup(&ctx);
  fclose(src);
  fclose(dst);

  return 0;
}

int ecb(char * in, char * out, unsigned char * key, bool encrypt)
{
    return des(in, out, key, NULL, &EVP_des_ecb, encrypt);
}

int cbc(char * in, char * out, unsigned char * key, unsigned char * iv, bool encrypt)
{
    return des(in, out, key, iv, &EVP_des_cbc, encrypt);
}

void GetFileName(char in[], char out[100], const char* last)
{
   unsigned int i, j;
   for(i = 0; i < strlen(in); i++)
     {
         if(in[i] == '.' && i != 0)
         {
            break;
         }
         out[i] = in[i];
     }

    for(j = 0; j < strlen(last); j++)
      {
         out[i] = last[j];
         i++;
      }

     out[i] = '\0';
}

int main(int argc, char* argv[])
{
    unsigned char key[] = "qwertyuiopghjk";
    unsigned char iv[] = "qwertyuiocvbnjk";

    if(!strcmp(argv[1], "-e"))
    {
       char out_name[100];
       std::cout << "Encrypt" << std::endl;

       if(!strcmp(argv[2], "ecb"))
        {
            GetFileName(argv[3], out_name, "_ecb.bmp");
            std::cout << out_name << std::endl;
            return ecb(argv[3], out_name, key, true);
        } else
             if(!strcmp(argv[2], "cbc"))
              {
                  GetFileName(argv[3], out_name, "_cbc.bmp");
                  std::cout << out_name << std::endl;
                  return cbc(argv[3], out_name, key, iv, true);
              } else
                   {
                       std::cout << "Bad named of shifer" << std::endl;
                       return 1;
                   }
    } else

    if(!strcmp(argv[1], "-d"))
    {
       char out_name[100];
       std::cout << "Decrypt" << std::endl;

      if(!strcmp(argv[2], "ecb"))
        {
            GetFileName(argv[3], out_name, "_dec.bmp");
            std::cout << out_name << std::endl;
            return ecb(argv[3], out_name, key, false);
        } else
             if(!strcmp(argv[2], "cbc"))
              {
                  GetFileName(argv[3], out_name, "_dec.bmp");
                  std::cout << out_name << std::endl;
                  return cbc(argv[3], out_name, key, iv, false);
              } else
                   {
                       std::cout << "Bad name of cipher" << std::endl;
                       return 1;
                   }
    } else
         {
            std::cout << "Bad argument" << std::endl;
            return 1;
         }
}

/**
 *   Rozdil mezi ecb a cbc u zasifrovanych souboru
 *
 *   ecb: pokud pouzijeme tento rezim na soubor nebo neco s pevne danou structurou pak, po zachyceni
 *        urciteho poctu dat, utocnik muze zacit rozlisovat jejich obsah, kdyz rozpozna opakovan
 *        nejakeho klicoveho bloku. Ve souboru bylo videt casti obrazku a slo bych rozpoznat obsah.
 *
 *   cbc: kazdy pristi blok je xorovan zasifrovanym predchozim blokem, pro prvni se vyuziva IV,
 *        je zavisli na predchozich hodnotach a ve pripade chyby nejde rozsirovat pristi bloky,
 *        obrazek vypada jako uplne nahodny obrazek s pixelu ruznych barv.
 *
 *
 */
