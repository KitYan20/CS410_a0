#include <stdio.h>
#include <elf.h>
#include <stdlib.h>
#include <string.h>

void text_section(const char* input_file){

    if (!input_file){
        perror("Error opening file");
        exit(-1);
    }
    const char* output_file = "text-output";
    FILE* input = fopen(input_file,"rb");
    FILE* output = fopen(output_file,"wb");
    
    Elf64_Ehdr elf_header;
    fread(&elf_header,sizeof(Elf64_Ehdr),1,input);

    for (int i = 0; i < elf_header.e_shnum; i++){
        fseek(input, elf_header.e_shoff + i * sizeof(Elf64_Shdr),SEEK_SET);
        Elf64_Shdr section_header;
        fread(&section_header,sizeof(Elf64_Shdr),1,input);

        if (section_header.sh_type == SHT_PROGBITS && strcmp(".text", (char *)(elf_header.e_shstrndx + section_header.sh_name) + elf_header.e_shoff) == 0) {
            // Found the .text section
            fseek(input, section_header.sh_offset, SEEK_SET);
            char buffer[section_header.sh_size];
            fread(buffer, section_header.sh_size, 1, input);

            // Dump the .text section to the output file
            fwrite(buffer, section_header.sh_size, 1, output);
            break;
        }
    }
    fclose(input);
    fclose(output);
    exit(0);
    
}