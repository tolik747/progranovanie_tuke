#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdint.h>
#include "playfair.h"
//tolik

char* strdup(const char* str) {
    size_t len = strlen(str) + 1; 
    char* dup = malloc(len); 
    if (dup) {
        strcpy(dup, str); 
    }
    return dup; 
}


char* playfair_encrypt(const char* key, const char* text)
{
    if(text==NULL)
    {
        return NULL;
    }
    if(key==NULL)
    {
        return NULL;
    }
    for (int i = 0;key[i]!='\0'; i++)
    {
        if(!isalpha(key[i]))
        {
            return NULL;
        }
    }
    
    char matrix[5][5];
    char* result = strdup(key);
    char* result_ptr = result;
    const char* key_ptr = key;
    char using[26] = {0};
    int row = 0;
    int col = 0;
    while (*key_ptr != '\0' && result_ptr - result < 25)
    {
        char let = toupper(*key_ptr++);
        if (let == 'W') {
            let='V';
        }
        int index = let - 'A';
        if (index >= 0 && index < 26 && !using[index]) {
            matrix[row][col++] = let;
            using[index] = 1;
            if (col == 5) {
                col = 0;
                row++;
            }
        }
        
    }

    char ch = 'A';
    while (row < 5 && col < 5)
    {
        if (ch == 'W') {
            ch++;
        }
        int index = ch - 'A';
        if (index >= 0 && index < 26 && !using[index]) {
            matrix[row][col++] = ch;
            using[index] = 1;
            if (col == 5) {
                col = 0;
                row++;
            }
        }
        ch++;
    }
    
    char* text_t=strdup(text);
    char* tmp=text_t;
    for(char* ptr=text_t;*ptr!='\0';ptr++)
    {
        if(*ptr==' ')
        {
            continue;
        }
        if(*ptr=='w')
        {
            *ptr='v';
        }
        *tmp++=toupper(*ptr);
        
    }
    *tmp='\0';
    
    int len = strlen(text_t);
    int len_ak = len;
    char* temp_ptr = tmp = (char*)malloc((2 * len + 1) * sizeof(char));
    if(temp_ptr==NULL)
    {
        return NULL;
    }
    for (int i = 0; i < len_ak; i += 2) 
    {
        *temp_ptr++ = text_t[i];
        if (i < len_ak - 1) {
            if (text_t[i] == text_t[i + 1] && text_t[i] != 'X' && text_t[i] != 'x') {
                *temp_ptr++ = 'X';
            }
            *temp_ptr++ = text_t[i + 1];
        }
    }
    *temp_ptr = '\0';
    len=strlen(tmp);
 if (len % 2 == 1) {
        *temp_ptr++ = 'X';
        len++;
    }
   
    
    for (int i = 0; i < len; i+=2)
    {
        char one=tmp[i];
        char two=tmp[i+1];
        int a_row=0;
        int a_col=0;
        int b_row=0;
        int b_col=0;

        for (int j = 0; j < 5; j++) {
            for (int k = 0; k < 5; k++) {
                if (matrix[j][k] == one) {
                    a_row = j;
                    a_col = k;
                }
                if (matrix[j][k] == two) {
                    b_row = j;
                    b_col = k;
                }
            }
        }
        if (a_row == b_row) {
            tmp[i] = matrix[a_row][(a_col + 1) % 5];
            tmp[i + 1] = matrix[b_row][(b_col + 1) % 5];
        
        }  if (a_col == b_col) {
            tmp[i] = matrix[(a_row + 1) % 5][a_col];
            tmp[i + 1] = matrix[(b_row + 1) % 5][b_col];
        
        }  if(a_col!=b_col&&a_row!=b_row){
            tmp[i] = matrix[a_row][b_col];
            tmp[i + 1] = matrix[b_row][a_col];  
        } if(a_col==b_col&&a_row==b_row){
            tmp[i] = matrix[(a_row + 1) % 5][a_col];
            tmp[i + 1] = matrix[(b_row + 1) % 5][b_col];
        }
    }
    
    char* encrypted_text = (char*)malloc((2 * len + 1) * sizeof(char));
    encrypted_text[0] = '\0'; 
    for (int i = 0; i < len; i+=2) 
    {
        char pair[3] = {tmp[i], tmp[i + 1], '\0'}; 
        strcat(encrypted_text, pair); 
        if (i < len - 2) {
            strcat(encrypted_text, " "); 
        }
    }
    
    free(tmp);
    free(result);
    free(text_t);
    return encrypted_text;
}

char* playfair_decrypt(const char* key, const char* text) {

    if(text == NULL ) {
        return NULL; 
    }
    if(key == NULL ) {
        return NULL; 
    }
    for (int i = 0; key[i] != '\0'; i++) {
        if(!isalpha(key[i])) {
            return NULL;
        }
    }
    
    char matrix[5][5];
    char* result = strdup(key);
    char* result_ptr = result;
    const char* key_ptr = key;
    char using[26] = {0};
    int row = 0;
    int col = 0;
    while (*key_ptr != '\0' && result_ptr - result < 25)
    {
        char let = toupper(*key_ptr++);
        if (let == 'W') {
            let='V';
        }
        int index = let - 'A';
        if (index >= 0 && index < 26 && !using[index]) {
            matrix[row][col++] = let;
            using[index] = 1;
            if (col == 5) {
                col = 0;
                row++;
            }
        }
        
    }
    char ch = 'A';
    while (row < 5 && col < 5)
    {
        if (ch == 'W') {
            ch++;
        }
        int index = ch - 'A';
        if (index >= 0 && index < 26 && !using[index]) {
            matrix[row][col++] = ch;
            using[index] = 1;
            if (col == 5) {
                col = 0;
                row++;
            }
        }
        ch++;
    }

     char* text_t=strdup(text);
    char* tmp=text_t;
    for(char* ptr=text_t;*ptr!='\0';ptr++)
    {
        if(*ptr==' ')
        {
            continue;
        }
        if(*ptr=='w'||*ptr=='W')
        {
            free(text_t);
            return NULL;
        }
        *tmp++=toupper(*ptr); 
    }
    *tmp = '\0';
    int len=strlen(text_t);
    tmp = (char*)malloc((len + 1) * sizeof(char));
    for (int i = 0; i < len; i+=2)
    {
        char one=text_t[i];
        char two=text_t[i+1];
        int a_row=0;
        int b_row=0;
        int a_col=0;
        int b_col=0;
        
        for (int j = 0; j < 5; j++)
        {
            for (int  y = 0; y < 5; y++)
            {
                if(matrix[j][y]==one)
                {
                    a_row=j;
                    a_col=y;
                }
                if(matrix[j][y]==two)
                {
                    b_row=j;
                    b_col=y;
                }
            }
            
        }
        if (a_row == b_row) {
            tmp[i] = matrix[a_row][(a_col - 1 + 5) % 5];
            tmp[i + 1] = matrix[b_row][(b_col - 1 + 5) % 5];
        } if (a_col == b_col) {
            tmp[i] = matrix[(a_row - 1 + 5) % 5][a_col];
            tmp[i + 1] = matrix[(b_row - 1 + 5) % 5][b_col];
        } if(a_col!=b_col&&a_row!=b_row) {
            tmp[i] = matrix[a_row][b_col];
            tmp[i + 1] = matrix[b_row][a_col];
        } if(a_col==b_col&&a_row==b_row)
        {
            tmp[i] = matrix[(a_row - 1 + 5) % 5][a_col];
            tmp[i + 1] = matrix[(b_row - 1 + 5) % 5][b_col];
        }
    }
   
    tmp[len]='\0';
    char* decrypted_text = tmp;
    //free(tmp);
    free(text_t);
    free(result);
    return decrypted_text;
    
}
