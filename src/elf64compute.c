#include "../include/include.h"

#include <stdio.h>

void
printSymtab(nm nmFile)
{
	for (size_t i = 0; i < nmFile.symtabSize / sizeof(*nmFile.elf64Symtab); i++) {
  		printf("%s\n", (char *)nmFile.elf64StrTab + nmFile.elf64Symtab[i].st_name);
	}	
	printf("Symtab END ---------------\n");
}

int
fullCompute(Elf64_Ehdr *elf_header, nm nmFile)
{
	if (elf_header->e_shoff == 0 || elf_header->e_shnum == 0)
		goto failure;

	if (!(nmFile.elf64SectionsPtr = (Elf64_Shdr *)((char *)nmFile.mmapPtr + elf_header->e_shoff)))
		goto failure;

	if (!nmFile.elf64SectionsPtr)
		goto failure;

	for (size_t i = 0; i < elf_header->e_shnum; i++) {

		if (i == 0) continue;
		switch (nmFile.elf64SectionsPtr[i].sh_type){

			case SHT_SYMTAB:
				nmFile.elf64Symtab = (Elf64_Sym *)((char *)nmFile.mmapPtr \
					+ nmFile.elf64SectionsPtr[i].sh_offset);
				printf("SHT_SYMTAB find !\n");
				nmFile.symtabSize = nmFile.elf64SectionsPtr[i].sh_size;
				continue;

			case SHT_STRTAB:
				nmFile.elf64StrTab = (Elf64_Shdr *)((char *)nmFile.mmapPtr + nmFile.elf64SectionsPtr[i].sh_offset);
				if (ft_strncmp((char *)nmFile.elf64StrTab + nmFile.elf64SectionsPtr[i].sh_name, ".shstrtab", 10) == 0) {
					printf("SHT_SHSTRAB find !\n");
					nmFile.strtabSize = nmFile.elf64SectionsPtr[i].sh_size;
					continue;
				} 
				printf("dynstr find !\n");
				//TODO Add address to dynstr tab and create a structure to stock it
				continue;

			case SHT_DYNSYM:
				nmFile.elf64DynSymtab = (Elf64_Dyn *)((char *)nmFile.mmapPtr \
					+ nmFile.elf64SectionsPtr[i].sh_offset);
				nmFile.dynsymSize = nmFile.elf64SectionsPtr[i].sh_size;
				printf("SHT_DYNSIM find !\n");
				continue;

			default:
				continue;
		}
	}

	if (nmFile.elf64Symtab == NULL && nmFile.flags != U_OPT) 
		goto nosymb;

	//printSymtab(nmFile);

	return (0);
failure:
	return (1);
nosymb:
	return (2);
}
