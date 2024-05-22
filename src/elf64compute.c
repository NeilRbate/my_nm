#include "../include/include.h"

#include <stdio.h>

void	printSymtab(nm nmFile)
{

	for (size_t i = 0; i < nmFile.elf64Symtab->st_size; i++) {

		printf("%s \n", "Test");
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

		if (i == 0)
			continue;

		//Find SYMTAB
		if (nmFile.elf64SectionsPtr[i].sh_type == SHT_SYMTAB) {
			printf("SHT_SYMTAB find ! \n");
			nmFile.elf64Symtab = (Elf64_Sym *)((char *)nmFile.mmapPtr \
					+ nmFile.elf64SectionsPtr[i].sh_offset);
		}
		
		//This scope cause an invalid read, need to fix it
		if (nmFile.elf64SectionsPtr[i].sh_type == SHT_STRTAB) {

			nmFile.elf64Ehdr = (Elf64_Ehdr *) elf_header;
			Elf64_Shdr *shdr = (Elf64_Shdr *)(elf_header + nmFile.elf64Ehdr->e_shoff);

			const char *shstrtab = (char *)elf_header + shdr[nmFile.elf64Ehdr->e_shstrndx].sh_offset;
			const char *sh_name = shstrtab + shdr->sh_name;

    		if (ft_strcmp(sh_name, ".strtab") == 0) {

				printf("SHT_STRTAB find ! \n");
				nmFile.elf64StrTab = (Elf64_Shdr *)((char *)nmFile.mmapPtr + nmFile.elf64SectionsPtr[i].sh_offset);

				//This way to get the string table value
				printf("nmFile.elf64StrTab : %s \n", (char *) nmFile.elf64StrTab + 1);
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
