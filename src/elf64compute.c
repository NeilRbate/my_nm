#include "../include/include.h"

#include <stdio.h>

void	printSymtab(nm nmFile)
{

	for (size_t i = 0; i < nmFile.elf64Symtab->st_size; i++) {
		printf("%d \n", nmFile.elf64Symtab[i].st_name);
	}


	/*
	if (!str) return;

	for (size_t i = 0; i < nmFile.elf64Symtab->st_size / sizeof(Elf64_Sym); i++) {
  		printf("%s\n", str + nmFile.elf64Symtab[i].st_name);
	}	
	*/
}

int	fullCompute(Elf64_Ehdr *elf_header, nm nmFile)
{
	if (elf_header->e_shoff == 0 || elf_header->e_shnum == 0)
		goto failure;

	if (!(nmFile.elf64SectionsPtr = (Elf64_Shdr *)((char *)nmFile.mmapPtr + elf_header->e_shoff)))
		goto failure;

	if (!nmFile.elf64SectionsPtr)
		goto failure;
	//Check number of element in section table
	
	for (size_t i = 0; i < elf_header->e_shnum; i++) {
		if (nmFile.elf64SectionsPtr[i].sh_type == SHT_SYMTAB) {
			printf("SHT_SYMTAB find ! \n");
			nmFile.elf64Symtab = (Elf64_Sym *)((char *)nmFile.mmapPtr \
					+ nmFile.elf64SectionsPtr[i].sh_offset);
		}

		//TODO Refactor and check str, itś not the good way to doing that shit
		if (nmFile.elf64SectionsPtr[i].sh_type == SHT_STRTAB && nmFile.elf64StrTab == NULL) {
			if(ft_strcmp((char *) (nmFile.elf64SectionsPtr[i].sh_name + nmFile.mmapPtr),".strtab")==0) {
				printf("SHT_STRTAB find ! \n");
				nmFile.elf64StrTab = (Elf64_Shdr *)((char *)nmFile.mmapPtr \
						+ nmFile.elf64SectionsPtr[i].sh_offset);
			}
		}
	}

	if (nmFile.elf64Symtab == NULL || nmFile.elf64StrTab == NULL)
		goto failure;

	printSymtab(nmFile);

	return (0);
failure:
	return (1);
}
