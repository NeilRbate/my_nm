#include "../include/include.h"

#include <stdio.h>

void
printSymtab(nm nmFile)
{
	Elf64_Sym	*sym = (Elf64_Sym *)nmFile.mmapPtr + nmFile.elf64Symtab->sh_offset;
	for (size_t i = 0; i < nmFile.elf64Symtab->sh_size / nmFile.elf64Symtab->sh_entsize; i++) {
		printf("sym_name [%s] sym_type[%d]\n", (char *)nmFile.elf64StrTab + sym[i].st_name, sym[i].st_info);
	}
	printf("Symtab END ---------------\n");
}

int
fullCompute(Elf64_Ehdr *elf_header, nm nmFile)
{
	if (elf_header->e_shoff < 1 || elf_header->e_shnum < 1)
		goto failure;

	if (!(nmFile.elf64SectionsPtr = (Elf64_Shdr *)((char *)nmFile.mmapPtr + elf_header->e_shoff)))
		goto failure;

	for (size_t i = 0; i < elf_header->e_shnum; i++) {

		if (i == 0 || !nmFile.elf64SectionsPtr[i].sh_size) continue;
		switch (nmFile.elf64SectionsPtr[i].sh_type){

			case SHT_SYMTAB:
				nmFile.elf64Symtab = (Elf64_Shdr *)&nmFile.elf64SectionsPtr[i];
				printf("SHT_SYMTAB find !\n");
				continue;

			case SHT_STRTAB:
				nmFile.elf64StrTab = (Elf64_Shdr *)((char *)nmFile.mmapPtr + nmFile.elf64SectionsPtr[i].sh_offset);
				if (ft_strncmp((char *)nmFile.elf64StrTab + nmFile.elf64SectionsPtr[i].sh_name, ".shstrtab", 10) == 0) {
					printf("SHT_SHSTRTAB find !\n");
					nmFile.elf64ShStrTab = (Elf64_Shdr *)&nmFile.elf64SectionsPtr[i];
					continue;
				}
				continue;

			case SHT_DYNSYM:
				nmFile.elf64DynSymtab = (Elf64_Shdr *)&nmFile.elf64SectionsPtr[i];
				printf("SHT_DYNSIM find !\n");
				continue;
		}
	}

	if (nmFile.elf64Symtab == NULL && nmFile.flags != U_OPT) 
		goto nosymb;

	printSymtab(nmFile);

	return (0);
failure:
	return (1);
nosymb:
	return (2);
}
