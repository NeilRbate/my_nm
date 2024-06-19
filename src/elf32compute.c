#include "../include/include.h"

int
halfCompute(Elf32_Ehdr *elf_header, nm nmFile)
{
	if (elf_header->e_shoff < 1 || elf_header->e_shnum < 1)
		goto failure;

	if (!(nmFile.elf32SectionsPtr = (Elf32_Shdr *)((char *)nmFile.mmapPtr + elf_header->e_shoff)))
		goto failure;

	//char	*sectionsName = ((char *)nmFile.mmapPtr + nmFile.elf32SectionsPtr[elf_header->e_shstrndx].sh_offset);

	for (size_t i = 0; i < elf_header->e_shnum; i++) {
		if (i == 0 || !nmFile.elf32SectionsPtr[i].sh_size) continue;
		switch (nmFile.elf32SectionsPtr[i].sh_type){

			case SHT_SYMTAB:
				nmFile.elf32Symtab = &nmFile.elf32SectionsPtr[i];
				nmFile.elf32Sym = (Elf32_Sym *)((char *)nmFile.mmapPtr + nmFile.elf32SectionsPtr[i].sh_offset);
				nmFile.symName = ((char *)nmFile.mmapPtr + nmFile.elf32SectionsPtr[nmFile.elf32SectionsPtr[i].sh_link].sh_offset);
				continue;

			case SHT_DYNSYM:
				nmFile.elf32DynSymtab = nmFile.elf32SectionsPtr + i;
				nmFile.elf32DynSym = (Elf32_Sym *)((char *)nmFile.mmapPtr + nmFile.elf32SectionsPtr[i].sh_offset);
				nmFile.dynSymName = ((char *)nmFile.mmapPtr + nmFile.elf32SectionsPtr[nmFile.elf32SectionsPtr[i].sh_link].sh_offset);
				continue;
		}
	}

	if (nmFile.elf32Symtab == NULL && nmFile.flags != U_OPT) 
		goto nosymb;

	printSymtab(nmFile, 32);

	return (0);
failure:
	return (1);
nosymb:
	return (2);
}
