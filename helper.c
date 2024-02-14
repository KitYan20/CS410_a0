#include "helper.h"
#include <string.h>
/*These are helper functions to help convert Hex values into ASCII characters
*numbers_to_ASCII() will be used to convert Hexadecimals for objcopy.c and objsect.c
*reverse_string() will reverse all the numbers back into it's original placements given
*numbers are represented in Little Endian ordering meaning least significant byte is first in memory
*itoa() will convert integers back to ascii for getting the RTSC
*/

void numbers_to_ASCII(long num, char* string){
    //Takes a number and a char pointer of a string array
    //Check if the first hex value is 0,
    //if it is, convert it back into the character value '0' and put it into the ith place of the string
    //increment our counter i by one
    int i = 0;
    if (num == 0){
        string[i] = '0';
        i++;
    }else{
        //Have a while loop to check when number is not zero
        while (num != 0){
            //Hex is represnted in base 16 from 0 to F
            //You want to get the remainder from modding 16
            int remainder = num % 16;
            //If the remainder is a number from 0 to 9, we convert it back into it's ASCII form
            //By adding the ASCII value of '0' to get the ASCII representation of the remainder
            if (remainder < 10){
                string[i] = remainder + '0';
            }else{
            //If the remainder is a non integer value, it needs to subtract the decimal value of remainder by 10 and then
            //Add the ASCII decimal value of 'A' to get back the ASCII value of the remainder
                string[i] = remainder - 10 + 'A';
            }
            //Increment i to move to the next character in the string to convert
            i++;
            //Divide the hex value by 16 to get the next hex number to convert
            num /= 16;
        }
        
    }
    //For better representation of Hex values, fill in the converted string with extra 0s until its a length of 8
    while(i < 8){
        string[i] = '0';
        i++;
    };
    //End the string with a null character
    
    //call the reverse string function for Little Endian ordering
    reverse_string(string,i);
    string[i] = '\0';

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
        //Same process but in base 10 representation
        string[i] = '0' + (time % 10 );
        time /= 10;
        i++;
        
    }
    
    //Reversing the string but with decimals
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
    //end the string with the null character
    string[i] = '\0';
}