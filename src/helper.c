#include "helper.h"
#include <string.h>
void numbers_to_ASCII(long num, char* string){
    int i = 0;
    if (num == 0){
        string[i] = '0';
        i++;
    }else{
        while (num != 0){
            int remainder = num % 16;

            if (remainder < 10){
                string[i] = remainder + '0';
            }else{
                string[i] = remainder - 10 + 'A';
            }
            i++;
            num /= 16;
        }
        
    }
    while(i < 8){
        string[i] = '0';
        i++;
    };
    //null character
    string[i] = '\0';
    reverse_string(string,i);

}
void reverse_string(char* string,long length){
    int start = 0;
    int end = length - 1;

    while(start < end){
        char temp = string[start];
        string[start] = string[end];
        string[end] = temp;
        start++;
        end--;
    }
}   
void itoa(long long time, char *string){
    int i=0;
    while(time > 0){
        string[i] = '0' + (time % 10 );
        time /= 10;
        i++;
        
    }
    //string[i] = '\0';
    int start = 0;
    int end = i - 1 ;
    if (i < 2){
        string;
    }else{
        while(start < end){
            char tmp = string[end];
            string[end] = string[start];
            string[start] = tmp;
            start++;
            end--;
        }
    }
}