#include "objsym.h"
#include "bfd.h"
#include <unistd.h>
#include <stdio.h>
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

    long storage_needed;
    asymbol **symbol_table;
    long number_of_symbols;
    long i;
    
    storage_needed = bfd_get_symtab_upper_bound(abfd);

    if (storage_needed == 0){
        bfd_perror("No symbols loaded");
        bfd_close(abfd);
        exit(-1);
    }
    if (storage_needed < 0){
        bfd_perror("Error getting symbol table size");
        bfd_close(abfd);
        exit(-1);
    }
    symbol_table = (asymbol **) malloc(storage_needed);
    //Returns the actual number of pointers , not including nulll
    number_of_symbols = bfd_canonicalize_symtab(abfd,symbol_table);
    //printf("Symbols %ld\n",number_of_symbols);
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
    char hexString[17];
    for (i = 0; i < number_of_symbols; i++){
        long value = symbol_table[i]->value;
        char symbol = (char)bfd_decode_symclass(symbol_table[i]);
        char *name = (char*)symbol_table[i]->name;
        strncpy(ns,name,sizeof(ns)-1);
        ns[sizeof(ns) - 1] = '\0'; 
        // printf("Symbol %c\n",symbol);
        // printf("name %s\n",name);
        // printf("0x%-5lx %c %20s\n",value,symbol,name);
        n = snprintf(buffer,sizeof(buffer),"VMA:0x%-5ld Symbol:%c  Name: %20s\n",value,symbol,name);
        write(1,&buffer,n);

        // numbers_to_ASCII((long)value,hexString);
        // write(1,"0x",sizeof("0x"));
        // write(1,&hexString,sizeof(hexString));
        // write(1," ",sizeof(""));
        // write(1,ns,sizeof(ns));
        // write(1," ",sizeof(""));
        // write(1,&symbol,1);
        // write(STDOUT_FILENO,&newline,sizeof(newline));
        
    }
    free(symbol_table);
    bfd_close(abfd);
    exit(0);
    
}