#include "../include/include.h"

int
fullCompute(Elf64_Ehdr *elf_header, nm nmFile)
{
	if (elf_header->e_shoff < 1 || elf_header->e_shnum < 1)
		goto failure;

	if (!(nmFile.elf64SectionsPtr = (Elf64_Shdr *)((char *)nmFile.mmapPtr + elf_header->e_shoff)))
		goto failure;

	//char	*sectionsName = ((char *)nmFile.mmapPtr + nmFile.elf64SectionsPtr[elf_header->e_shstrndx].sh_offset);

	for (size_t i = 0; i < elf_header->e_shnum; i++) {
		if (i == 0 || !nmFile.elf64SectionsPtr[i].sh_size) continue;
		switch (nmFile.elf64SectionsPtr[i].sh_type){

			case SHT_SYMTAB:
				nmFile.elf64Symtab = &nmFile.elf64SectionsPtr[i];
				nmFile.elf64Sym = (Elf64_Sym *)((char *)nmFile.mmapPtr + nmFile.elf64SectionsPtr[i].sh_offset);
				nmFile.symName = ((char *)nmFile.mmapPtr + nmFile.elf64SectionsPtr[nmFile.elf64SectionsPtr[i].sh_link].sh_offset);
				continue;

			case SHT_DYNSYM:
				nmFile.elf64DynSymtab = nmFile.elf64SectionsPtr + i;
				nmFile.elf64DynSym = (Elf64_Sym *)((char *)nmFile.mmapPtr + nmFile.elf64SectionsPtr[i].sh_offset);
				nmFile.dynSymName = ((char *)nmFile.mmapPtr + nmFile.elf64SectionsPtr[nmFile.elf64SectionsPtr[i].sh_link].sh_offset);
				continue;
		}
	}

	if (nmFile.elf64Symtab == NULL && nmFile.flags != U_OPT) 
		goto nosymb;

	printSymtab(nmFile, 64);

	return (0);
failure:
	return (1);
nosymb:
	return (2);
}
