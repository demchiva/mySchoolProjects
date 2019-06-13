#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>

#include <openssl/crypto.h>
#include <openssl/x509.h>
#include <openssl/pem.h>
#include <openssl/ssl.h>

int main(int argc, char *argv[]){
    int                 sd;
    struct hostent      *host;
    struct sockaddr_in  addr;
    const SSL_METHOD    *method;
    SSL_CTX             *ctx, *ctx_new, *octx;
    SSL                 *ssl, *tmp_ssl, *ssll;
    char                req[] = "GET /student/odkazy HTTP/1.1\r\nHost: fit.cvut.cz\r\n\r\n";;
    size_t              req_len = strlen(req);
    char                hostname[] = "www.fit.cvut.cz";
    int                 port = 443;
    int                 bytes;
    char                buf[128];

    const char          *cipher_name;
    const SSL_CIPHER    *ssl_cipher;
    int                 i;

    char                dest_url[] = "https://www.fit.cvut.cz/";
    X509                *cert = NULL;

    FILE *              page;
    FILE *              certFile;

    OpenSSL_add_all_algorithms();

    if(SSL_library_init() < 0){
        printf("Could not initialize the OpenSSL library !\n");
        return 1;
    }

    method = SSLv23_client_method();
    ctx = SSL_CTX_new(method);
    SSL_CTX_set_options(ctx, SSL_OP_NO_SSLv2 | SSL_OP_NO_SSLv3);

    host = gethostbyname(hostname);
    sd = socket(AF_INET, SOCK_STREAM, 0);
    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    addr.sin_addr.s_addr = *(in_addr_t *)(host->h_addr);

    if ( connect(sd, (struct sockaddr*)&addr, sizeof(addr)) == -1 ) {
        printf("Cannot connect to host %s [%s] on port %d.\n", hostname, inet_ntoa(addr.sin_addr), port);
        return 1;
    }

    ssl = SSL_new(ctx);
    SSL_set_fd(ssl, sd);
    SSL_connect(ssl);

    /* Get the remote certificate into the X509 structure */
    cert = SSL_get_peer_certificate(ssl);
    if (cert == NULL) {
        printf("Error: Could not get a certificate from: %s.\n", dest_url);
        return 1;
    } else
        printf("Retrieved the server's certificate from: %s.\n", dest_url);

     // SSL_connect(ssl);
    ssl_cipher = SSL_get_current_cipher(ssl);
    cipher_name = SSL_CIPHER_get_name(ssl_cipher);
    printf("Current cipher is: %s\n", cipher_name);

    /*
     * DHE - authenticated ephemeral Diffie-Hellman key agreement
     * RSA - is the RSA algorithm
     * AES256 - the AES cipher with a key of length 256 bits
     * SHA - hashing algorithm
     */

    // Blocking it
    printf("Setting ciphers list to \"ALL:!%s\"\n", cipher_name);

    SSL_set_cipher_list(ssl, "ALL:!ECDHE-RSA-AES256-GCM-SHA384");

    // Printing available ciphers out
    i = 0;
    cipher_name = SSL_get_cipher_list(ssl, i);
    i++;
    printf("\nAvailable ciphers:\n");

    while (cipher_name != NULL) {
        printf("%s\n", cipher_name);
        cipher_name = SSL_get_cipher_list(ssl, i);
        i++;
    }

      // Server certificate verification
    ctx_new = SSL_CTX_new(method);
    SSL_CTX_set_default_verify_paths(ctx_new);

    tmp_ssl = SSL_new(ctx_new);
    SSL_set_fd(tmp_ssl, sd);
    SSL_connect(tmp_ssl);

    printf("\nVerifying server certificate...\n");

    if (SSL_get_verify_result(tmp_ssl) == X509_V_OK) {
        printf("[SUCCESS] The certificate looks good.\n");


    /* Writing PEM file */
    certFile = fopen("./cert.pem", "w+b");
    PEM_write_X509(certFile, cert);
    fclose(certFile);

    octx = SSL_CTX_new(method);
    SSL_CTX_set_options(octx, SSL_OP_NO_SSLv2 | SSL_OP_NO_SSLv3);

    host = gethostbyname(hostname);
    sd = socket(AF_INET, SOCK_STREAM, 0);
    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    addr.sin_addr.s_addr = *(in_addr_t *)(host->h_addr);

    if ( connect(sd, (struct sockaddr*)&addr, sizeof(addr)) == -1 ) {
        printf("Cannot connect to host %s [%s] on port %d.\n", hostname, inet_ntoa(addr.sin_addr), port);
        return 1;
    }

    ssll = SSL_new(octx);
    SSL_set_fd(ssll, sd);
    SSL_connect(ssll);

    /* Sending a request */
    SSL_write(ssll, req, (int)req_len);

    /* Writing to file */
    memset(buf, '\0', sizeof(buf));

    page = fopen("./page.html", "w+b");
    if(!page) return 1;
    bytes = SSL_read(ssll, buf, sizeof(buf));
    while(bytes > 0){
        fwrite(buf, 1, (size_t) bytes, page);
        memset(buf, '\0', sizeof(buf));
        bytes = SSL_read(ssll, buf, sizeof(buf));
    }
  } else {
        printf("[FAIL] The certificate does not look good!!!\n");
    }

    /* Freeing resources up */
    fclose(page);
    SSL_shutdown(ssl);
    SSL_free(ssl);
    SSL_shutdown(tmp_ssl);
    SSL_free(tmp_ssl);
    close(sd);
    SSL_CTX_free(ctx);
    SSL_CTX_free(ctx_new);
    return 0;
}
