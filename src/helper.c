#include "helper.h"

void numbers_to_ASCII(long num, char* string){
    int i = 0;
    if (num == 0){
        string[i++] = '0';
    }else{
        while (num != 0){
            int remainder = num % 16;

            if (remainder < 10){
                string[i++] = remainder + '0';
            }else{
                string[i++] = remainder - 10 + 'A';
            }

            num /= 16;
        }
        
    }
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
        ++start;
        --end;

    }
}   