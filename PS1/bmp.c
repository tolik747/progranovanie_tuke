#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdint.h>
#include "bmp.h"



char* reverse(const char* text)
{
    if(text == NULL)
    {
        return NULL;
    }
    int length = strlen(text);
    char* reversed = (char*)malloc((length+1) * sizeof(char));
    if(reversed == NULL)
    {
        return NULL;
    }

    for (int i = length - 1, j = 0; i >= 0; i--, j++)
    {
        reversed[j] = toupper(text[i]);
    }
    reversed[length] = '\0';
   
    return reversed;
}


char* vigenere_encrypt(const char* key, const char* text)
{
    if(key&&text)
    {

        if(key==NULL)
        {
            return NULL;
        }

        if(text==NULL)
        {
            return NULL;
        }
        for(int i = 0; key[i] != '\0'; i++)
        {
            if(!isalpha(key[i]))
            {
                return NULL;
            }
             if(key[i]==' ')
            {
                return NULL;
            }
        }
            int key_lenth = strlen (key);
            int text_lenth = strlen (text);

            char* code=(char*)calloc((text_lenth+1),sizeof(char));

            if(code==NULL)
            {
                return NULL;
            }
            for(int i=0,j=0;text_lenth>i;i++,j++)
            {
                if(key_lenth==j)
                {
                    j=0;
                }
                char caps = tolower(key[j]) - 'a';
                if(isalpha(text[i]))
                {
                    
                    code[i]=(toupper(text[i])-'A'+ caps)%26+'A';

                }else{
                    code[i]=text[i];
                    j--;
                }
            }
            return code;
    }
    return NULL;
}

char* vigenere_decrypt(const char* key, const char* text)
{
    if(text==NULL)
    {
        return NULL;
    }
    if(key==NULL)
    {
        return NULL;
    }
    for(int i = 0; key[i] != '\0'; i++)
        {
            if(!isalpha(key[i]))
            {
                return NULL;
            }
            if(key[i]==' ')
            {
                return NULL;
            }
        }
    int key_lenth=strlen(key);
    int text_lenth=strlen(text);
    char *decrypted=(char*)calloc((text_lenth+1),sizeof(char));
    if (decrypted==NULL){
        free(decrypted);
        return  NULL;

    }
    
    for(int i=0,j=0;i<text_lenth;i++)
    {
        char let=text[i];
        if(isalpha(let))
        {
            char caps=toupper(key[j%key_lenth])-'A';
           char case_ap;
            if(isupper(let))
            {
                case_ap = 'A';
            }else{
                case_ap = 'a';
            }
           
            decrypted[i]=((let - case_ap - caps + 26)%26) + case_ap;
            j++;
        }else{
             decrypted[i]=let;
             
        }
    }
    decrypted[text_lenth] = '\0';
    return decrypted;
}

unsigned char* bit_encrypt(const char* text)
{
    if(text==NULL)
    {
        return NULL;
    }
    size_t text_length = strlen(text);
    unsigned char* decrypted=(unsigned char*)calloc((text_length+1),sizeof(unsigned char));
    if(decrypted==NULL)
    {
        return NULL;
    }
    uint8_t bits[8]={0};
   // bits[8] = '\0';
    for(int a = 0; a < text_length; a++){
        uint8_t character = text[a];
        uint8_t charac =(uint8_t) character;
        for(int i=7;i>=0;i--)
        {
            bits[i]=charac & 1;
            charac>>=1;
        }
        int g=bits[0];
        int s=bits[1];
        int f=bits[2];
        int o=bits[3];
        bits[0]=s;
        bits[1]=g;
        bits[2]=o;
        bits[3]=f;
        bits[4]= bits[4]^bits[0]; 
        bits[5]= bits[5]^bits[1]; 
        bits[6]= bits[6]^bits[2]; 
        bits[7]= bits[7]^bits[3]; 

        unsigned int index = 0;
        int ko;
        for(ko = 0; ko < 8; ko++) {
            index <<= 1;
            index |= bits[ko];
        }
        
        
        decrypted[a] = index;
    }
    return decrypted;
}



char* bit_decrypt(const unsigned char* text)
{
    if(text == NULL) 
    {
        return NULL;
    }

    size_t length_text=0;

    while(text[length_text]!='\0')
    {
        length_text++;
    }

    char* binary_text = (char*)malloc((length_text * 8) + 1);
    char* encrypted_text = (char*)malloc(length_text + 1);
    if(encrypted_text==NULL||binary_text==NULL)
    {
        free(encrypted_text);
        free(binary_text);
        return NULL;
    }

    for(int i = 0; i < length_text ; i++) 
    {
            unsigned char current_char = text[i];
            for(int j = 7; j >= 0; j--) 
            {
                binary_text[(i * 8) + (7 - j)] = ((current_char >> j) & 1) + '0';   
            }

            char pair1[5];
            char pair2[5];
            pair1[4] = '\0';
            pair2[4]='\0';
            char bits[9];
            
            for(int f = 0; f < 4; f++)
            {
                pair1[f] = binary_text[i * 8 + f];
            }
            for(int g = 4; g < 8; g++)
            {
                pair2[g-4] = binary_text[(i * 8) + g];
                
            }
            //xor
            char xor_result[5];
            xor_result[4] = '\0';
            for(int k = 0; k < 4; k++)
            {
                if(pair1[k] != pair2[k])
                {
                    xor_result[k] = '1';
                }
                else
                {
                    xor_result[k] = '0';
                }
            }
            for(int l = 0; l < 4; l++)
            {
                pair2[l] = xor_result[l];
            }
            //зміна бітів 
        int one=pair1[0];
        int two=pair1[1];
        int three=pair1[2];
        int four=pair1[3];
        pair1[0]=two;
        pair1[1]=one;
        pair1[2]=four;
        pair1[3]=three;
        //копіювання в чар біт
        strcpy(bits,pair1);
        strcat(bits,pair2);
        //перепис в букви
        char decrypted_char = 0;
        for(int let=0;let<8;let++)
        {
            decrypted_char <<= 1;
            if(bits[let]=='1')
            {
                decrypted_char|=1;
            }
        }
        encrypted_text[i]=decrypted_char;
    }
    encrypted_text[length_text]='\0';
    free(binary_text);
    return encrypted_text;
}


unsigned char* bmp_encrypt(const char* key, const char* text)
{
    if(text==NULL)
    {
        return NULL;
    }
    if(key==NULL)
    {
        return NULL;
    }
    for (int i = 0; i < strlen(key); i++)
    {
        if(!isalpha(key[i]))
        {
            return NULL;
        }
         if(key[i]==' ')
            {
                return NULL;
            }
    }
    
    //task 2
    int text_lenth=strlen(text); //дивиться довжину
    int key_length=strlen(key);
    unsigned char* finish = (unsigned char*)calloc((text_lenth + 1), sizeof(unsigned char)); 
    char* reverse=( char*)malloc((text_lenth+1)*sizeof(char));//виділяємо память+1 з запасом
    if(reverse==NULL)//перевірка реверса на нуль
    {
        free(finish);
        return NULL;
    }
    
     const char* end_of_line = text + text_lenth - 1;//кінець рядка та перероблення його до дзеркального виду

     while (end_of_line>=text)//веретворення в верхній реєстр
     {
        *reverse++ = toupper(*end_of_line--);//перетворення
     }
    reverse-=text_lenth;
    
    //task 3
    for(int i=0,j=0;text_lenth>i;i++,j++)
    {
        if(key_length==j)
        {
            j=0;
        }
        char caps = tolower(key[j]) - 'a'; 
        if (isalpha(reverse[i])) 
        { 
            reverse[i] = (toupper(reverse[i]) - 'A' + caps) % 26 + 'A'; 
        } else {
            j--; 
        }
    }
    uint8_t bits[8]={0};
   // bits[8] = '\0';
    for(int a = 0; a < text_lenth; a++){
        uint8_t character = reverse[a];
        uint8_t charac =(uint8_t) character;
        for(int i=7;i>=0;i--)
        {
            bits[i]=charac & 1;
            charac>>=1;
        }
        int g=bits[0];
        int s=bits[1];
        int f=bits[2];
        int o=bits[3];
        bits[0]=s;
        bits[1]=g;
        bits[2]=o;
        bits[3]=f;
        bits[4]= bits[4]^bits[0]; 
        bits[5]= bits[5]^bits[1]; 
        bits[6]= bits[6]^bits[2]; 
        bits[7]= bits[7]^bits[3]; 

        int index = 0;
        int ko;
        for(ko = 0; ko < 8; ko++) {
            index <<= 1;
            index |= bits[ko];
        }
        
        
        finish[a] = index;
    }
    
    free(reverse);
    
    return finish;
    

}
char* bmp_decrypt(const char* key, const unsigned char* text){
    if (text == NULL || key == NULL)
    {
        return NULL;
    }
    char* bititt = bit_decrypt(text);

    char* encrypt_text = vigenere_decrypt(key, bititt);     
    free(bititt);   

    char* reversed_text = reverse(encrypt_text);
    free(encrypt_text);
    
    return reversed_text;    
}
