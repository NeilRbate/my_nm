#include "../include/include.h"

#include <stdio.h>

/*
struct Elf32_Shdr {
  Elf32_Word sh_name;      // Section name (index into string table)
  Elf32_Word sh_type;      // Section type (SHT_*)
  Elf32_Word sh_flags;     // Section flags (SHF_*)
  Elf32_Addr sh_addr;      // Address where section is to be loaded
  Elf32_Off sh_offset;     // File offset of section data, in bytes
  Elf32_Word sh_size;      // Size of section, in bytes
  Elf32_Word sh_link;      // Section type-specific header table index link
  Elf32_Word sh_info;      // Section type-specific extra information
  Elf32_Word sh_addralign; // Section address alignment
  Elf32_Word sh_entsize;   // Size of records contained within the section
};
*/

int	halfCompute(Elf32_Ehdr *elf_header, nm nmFile)
{
	if (elf_header->e_shoff == 0 || elf_header->e_shnum == 0)
		goto failure;

	if (!(nmFile.elf32SectionsPtr = (Elf32_Shdr *)((char *)nmFile.mmapPtr + elf_header->e_shoff)))
		goto failure;

	if (!nmFile.elf32SectionsPtr)
		goto failure;
	//Check number of element in section table
	
	//TODO Try it wth 32 bits files
	for (int i = 0; i < elf_header->e_shnum; i++) {
		printf("Hello\n");
	}


	return (0);
failure:
	return (1);
}
