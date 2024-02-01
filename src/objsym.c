#include "objsym.h"
#include "bfd.h"
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

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
    printf("Size: %ld\n",storage_needed);
    if (storage_needed == 0){
        printf("No symbols loaded");
        bfd_close(abfd);
        exit(-1);
    }
    if (storage_needed < 0){
        printf("Error getting symbol table size");
        bfd_close(abfd);
        exit(-1);
    }
    symbol_table = (asymbol **) malloc(storage_needed);
    number_of_symbols = bfd_canonicalize_symtab(abfd,symbol_table);
    printf("Symbols %ld\n",number_of_symbols);
    if (number_of_symbols < 0){
        printf("No symbols available");
        free(symbol_table);
        bfd_close(abfd);
        exit(-1);
    }
    long value;
    for (i = 0; i < number_of_symbols; i++){
        value = bfd_asymbol_value(symbol_table[i]);
        //char name[] = (char)bfd_asymbol_name(symbol_table[i]);
        
        printf("0x%-5lx %20s\n",value,bfd_asymbol_name(symbol_table[i]));
    }
    free(symbol_table);
    bfd_close(abfd);
    exit(0);
    
}