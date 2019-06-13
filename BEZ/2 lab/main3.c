#include <stdlib.h>
#include <openssl/evp.h>
#include <string.h>

int hexchr2bin(const char hex, unsigned char *out)
{
	if (out == NULL)
		return 0;

	if (hex >= '0' && hex <= '9') {
		*out = hex - '0';
	} else if (hex >= 'A' && hex <= 'F') {
		*out = hex - 'A' + 10;
	} else if (hex >= 'a' && hex <= 'f') {
		*out = hex - 'a' + 10;
	} else {
		return 0;
	}

	return 1;
}

int main(int argc, char* argv[]) 
{

  int i, res;
  unsigned char SecretText[1024] = "this is my text without shtaco"; 
  unsigned char KnownText[1024] = "abcdefghijklmnopqrstuvwxyz0123"; 
  unsigned char SecretSt[1024];
  unsigned char KnownSt[1024];
   char HexaKnownText[1024];  
   char HexaSecretText[1024];
  unsigned char key[EVP_MAX_KEY_LENGTH] = "Best key in the "; 
  unsigned char iv[EVP_MAX_IV_LENGTH] = "inicial. vektor";
  const char cipherName[] = "RC4";
  const EVP_CIPHER * cipher;

  OpenSSL_add_all_ciphers();
  cipher = EVP_get_cipherbyname(cipherName);

  if(!cipher) 
  {
    printf("Sifra %s neexistuje.\n", cipherName);
    exit(1);
  }

  int SecretTextLength = strlen((const char*) SecretText);
  int SecretStLength = 0;
  int tmpLength = 0;

  EVP_CIPHER_CTX *ctx; 
  ctx = EVP_CIPHER_CTX_new();
  if (ctx == NULL) exit(2);

  if(!strcmp(argv[1], "-e"))
  {
      res = EVP_EncryptInit_ex(ctx, cipher, NULL, key, iv); 
      if(res != 1) exit(3);
      res = EVP_EncryptUpdate(ctx, SecretSt, &tmpLength, SecretText, SecretTextLength);  
      if(res != 1) exit(4);
      SecretStLength += tmpLength;
      res = EVP_EncryptFinal_ex(ctx, SecretSt + SecretStLength, &tmpLength);  
      if(res != 1) exit(5);
      SecretStLength += tmpLength;
 
      tmpLength = 0;
      int KnownTextLength = strlen((const char*) KnownText);
      int KnownStLength = 0;

      res = EVP_EncryptInit_ex(ctx, cipher, NULL, key, iv); 
      if(res != 1) exit(3);
      res = EVP_EncryptUpdate(ctx, KnownSt, &tmpLength, KnownText, KnownTextLength);  
      if(res != 1) exit(4);
      KnownStLength += tmpLength;
      res = EVP_EncryptFinal_ex(ctx, KnownSt + KnownStLength, &tmpLength);  
      if(res != 1) exit(5);
      KnownStLength += tmpLength;

      for(i = 0; i < KnownStLength; i++)
        {
           sprintf(HexaKnownText + 2*i, "%02x", KnownSt[i]);
        }

      for(i = 0; i < SecretStLength; i++)
        {
           sprintf(HexaSecretText + 2*i, "%02x", SecretSt[i]);
        }

      printf("KnownText: %s\nCipher of KnownText: %s\nSecretCipherText: %s\n", 
                                     KnownText, HexaKnownText, HexaSecretText);
  } else
       if(!strcmp(argv[1], "-d"))
         {
             if(argc != 5)
              {
                 printf("Bad count of arguments");
                 return 1;
              }
               unsigned int length = 0;
               unsigned char tmp_buf[100];
              
               if(strlen(argv[3]) < strlen(argv[4]))
                  length = strlen(argv[3]);
               else
                  length = strlen(argv[4]);

               if(strlen(argv[2]) < length)
                  length = strlen(argv[2]);  
 		
		unsigned char sifr1[100];
		unsigned char sifr2[100];

              if(strlen(argv[3]) % 2 == 1)
               {
                   sifr1[0] = 0;
                   i = 1;
               } else i = 0;
 
     
              unsigned int j = 0;
              for(; i < strlen(argv[3]); i+=2)
                {
                   unsigned char tmp1;
		   unsigned char tmp2;
		   hexchr2bin(argv[3][i],&tmp1);
		   hexchr2bin(argv[3][i+1],&tmp2);
		   sifr1[j++]=(tmp1<<4)|(tmp2);
                }

               if(strlen(argv[4]) % 2 == 1)
               {
                   sifr2[0] = 0;
                   i = 1;
               } else i = 0;
 
     
              j = 0;
              for(; i < strlen(argv[4]); i+=2)
                {
                   unsigned char tmp1;
		   unsigned char tmp2;
		   hexchr2bin(argv[4][i],&tmp1);
		   hexchr2bin(argv[4][i+1],&tmp2);
		   sifr2[j++]=(tmp1<<4)|(tmp2);
                }


               for(i = 0; i < length; i++)
                 {
                     tmp_buf[i] = ((sifr1[i] ^ sifr2[i]) ^ argv[2][i]);
                 }

		tmp_buf[length] = '\0';

		printf("%s\n",tmp_buf);

         } else {
                   printf("Bad argument\n");
                }

  EVP_CIPHER_CTX_free(ctx);

  exit(0);
}
