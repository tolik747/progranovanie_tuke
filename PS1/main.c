#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "playfair.h"
#include"bmp.h"

int main() {
    char *encrypted, *decrypted;
    // letter 'X' in message
    encrypted = playfair_encrypt("Password", "Taxi please");
    printf("%s", encrypted);
// "Taxi please" --> "TAXIPLEASE"
// UP YH AK DO OB
    printf("\n");
    decrypted = playfair_decrypt("Password", encrypted);
    printf("%s", decrypted);
// TAXIPLEASE
    free(encrypted);
    free(decrypted);
    printf("\n");
    char* reversed = reverse("Hello world!");
    printf("%s\n", reversed);
// "!DLROW OLLEH"
    free(reversed);
    char* encrypted1;
    char* decrypted1;
// basic test with long text
    encrypted1 = vigenere_encrypt("CoMPuTeR", "Hello world!");
    printf("%s\n", encrypted1);
// "JSXAI PSINR!"
    decrypted1 = vigenere_decrypt("CoMPuTeR", encrypted1);
    printf("%s\n", decrypted1);
    free(encrypted1);
    free(decrypted1);
    unsigned char* encrypted2;

// basic test with long text
    encrypted2 = bit_encrypt("Hello world!");
    for(int i=0; i < 12;i++) {
        printf("%x ", encrypted2[i]);
        //80 9c 95 95 96 11 bc 96 b9 95 9d 10
    }
    printf("\n");
    char* decrypted2;

// basic test with long text
    decrypted2 = bit_decrypt(encrypted2);
    for(int i=0; i < 12;i++) {
        printf("%c ", decrypted2[i]);
        //80 9c 95 95 96 11 bc 96 b9 95 9d 10
    }
    free(encrypted2);
    free(decrypted2);
    printf("\n");
    
    unsigned char* encrypted3;
    encrypted3 = bmp_encrypt("CoMPuTeR", "Hello world!");
    for(int i=0; i < 12;i++) {
        printf("%x ", encrypted3[i]);
    }
    printf("\n");
    char* decrypted3;
    decrypted3 = bmp_decrypt("CoMPuTeR",encrypted3);
    for(int i=0; i < 12;i++) {
        printf("%c ", decrypted3[i]);
        //80 9c 95 95 96 11 bc 96 b9 95 9d 10
    }
    free(encrypted3);
    free(decrypted3);
    return 0;
}