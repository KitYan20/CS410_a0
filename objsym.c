#include "objsym.h"
#include "bfd.h"
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include "helper.h"
void find_symbols(char* filename){

    bfd_init();
    bfd *abfd = bfd_openr(filename,"elf64-x86-64" /*elf32-i386*/);

    if (!bfd_check_format(abfd,bfd_object)){
        bfd_perror("Error opening the file");
        bfd_close(abfd);
        exit(-1);
    }
    //Initialize a variable to allocate the size of the table
    long storage_needed;

    //To output the symbols, BFD will structure this table as pointers to pointers to symbols
    asymbol **symbol_table;
    //Initialize a variable to get the number of symbols
    long number_of_symbols;
    //Initialize a variable i to iterate through the table of symbols
    long i;
    
    //the function returns the number of bytes required to store a vector of pointers to asymbols for all the symbols in the BFD abfd, 
    //including a terminal NULL pointer.
    storage_needed = bfd_get_symtab_upper_bound(abfd);

    //Error checking for if there are no symbols available, exit with 0
    if (storage_needed == 0){
        bfd_perror("No symbols available");
        bfd_close(abfd);
        exit(0);
    }
    //Else, exit with error indicating failure
    if (storage_needed < 0){
        bfd_perror("Error getting symbol table size");
        bfd_close(abfd);
        exit(-1);
    }
    //Use malloc() to allocate enough memory to for the symbol_table from the heap
    symbol_table = (asymbol **) malloc(storage_needed);
    //Returns the actual number of pointers , not including null
    number_of_symbols = bfd_canonicalize_symtab(abfd,symbol_table);
    //If theres no symbols available, exist with error
    //Free the memory from the heap and close the bfd
    if (number_of_symbols < 0){
        bfd_perror("No symbols available");
        free(symbol_table);
        bfd_close(abfd);
        exit(-1);
    }
    //Get the character symbol of the symbol class
    // char symbol;
    
    int n;
    //Allocate enough bytes to write to standard out
    char buffer[1024];
    char ns[256];
    char newline = '\n';
    char hexString[9];
    
    for (i = 0; i < number_of_symbols; i++){
        //This will get the vma of the symbol
        long value = symbol_table[i]->value;
        //Gets the Virtual Memory Address of the section 
        bfd_vma vma = symbol_table[i]->section->vma;
        //Adding the vma and the symbol table value will give back the VMA
        value = vma + value;
    
        //Gets the unicode of the symbol
        char symbol = (char)bfd_decode_symclass(symbol_table[i]);
        //Gets the name of the symbol
        char *name = (char*)symbol_table[i]->name;
        //make a copy of the string
        strncpy(ns,name,sizeof(ns)-1);
        //end the string with a null character
        ns[sizeof(ns) - 1] = '\0'; 
        //convert the vma value to hex
        numbers_to_ASCII((long)value,hexString);
        //write it back to standard out
        write(1,"0x",sizeof("0x"));
        write(1,&hexString,sizeof(hexString));
        write(1," ",sizeof(""));
        //Write the symbol name back to stanard out
        write(1,&symbol,1);
        write(1," ",sizeof(""));
        write(1,ns,sizeof(ns));
        write(1,&newline,sizeof(newline));
        
    }
    //Free the memory of the symbol_table and close the bfd and exit with 0 indicating exit with no error
    free(symbol_table);
    bfd_close(abfd);
    exit(0);
    
}