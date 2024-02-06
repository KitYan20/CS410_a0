#include <stdio.h>
#include <elf.h>
#include <stdlib.h>
#include <string.h>

void text_section(char* input_file, char* output_file){

    if (!input_file || !output_file){
        perror("Error opening file");
        exit(-1);
    }
    FILE* input = fopen(input_file,'rb');
    FILE* output = fopen(output_file,'wb');
    
    Elf64_Ehdr elf_header;
    fread(&elf_header,sizeof(Elf64_Ehdr),1,input);

    for (int i = 0; i < elf_header.e_shnum; i++){
        
    }

    
}