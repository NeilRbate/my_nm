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
	Elf64_Shdr *shdr = NULL;
	char *shstrtab = NULL;
		//,*sh_name = NULL;
	int shdroff;


	if (elf_header->e_shoff == 0 || elf_header->e_shnum == 0)
		goto failure;

	if (!(nmFile.elf64SectionsPtr = (Elf64_Shdr *)((char *)nmFile.mmapPtr + elf_header->e_shoff)))
		goto failure;

	if (!nmFile.elf64SectionsPtr)
		goto failure;

	shdroff = elf_header->e_shoff + elf_header->e_shstrndx * elf_header->e_shentsize;
	shdr = (Elf64_Shdr *)(elf_header + shdroff);

	if (!(shstrtab = malloc(shdr->sh_size)))
		goto failure;

	ft_memcpy(shstrtab, (char*)elf_header + shdroff, shdr->sh_size);
	//sh_name = shstrtab + shdr->sh_name;
	
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
		//Find STRTAB
		if (nmFile.elf64SectionsPtr[i].sh_type == SHT_STRTAB) {
			printf("[%s]\n", shstrtab + nmFile.elf64SectionsPtr[i].sh_name);

			if (ft_strcmp(shstrtab + nmFile.elf64SectionsPtr[i].sh_name, ".strtab") == 0) {

				printf("SHT_STRTAB find ! \n");
				nmFile.elf64StrTab = (Elf64_Shdr *)((char *)nmFile.mmapPtr + nmFile.elf64SectionsPtr[i].sh_offset);

				//This way to get the string table value
				printf("nmFile.elf64StrTab : %s \n", (char *) nmFile.elf64StrTab + 1);
			}
		}
	}

	free(shstrtab);
	if (nmFile.elf64Symtab == NULL || nmFile.elf64StrTab == NULL)
		goto failure;

	printSymtab(nmFile);

	return (0);
failure:
	return (1);
}
