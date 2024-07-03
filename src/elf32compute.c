#include "../include/include.h"

char
findType32(Elf32_Sym sym, Elf32_Shdr *shdr)
{
	char c;

	if (ELF32_ST_TYPE(sym.st_info) == STT_OBJECT && ELF32_ST_BIND(sym.st_info) == STB_WEAK) {
		c = 'v'; if (sym.st_shndx) c = 'V';
	} else if (ELF32_ST_BIND(sym.st_info) == STB_WEAK) {
		c = 'w'; if (sym.st_shndx) c = 'W';
	} else if (ELF32_ST_TYPE(sym.st_info) == STT_GNU_IFUNC) {
		c = 'i';
	} else if (ELF32_ST_TYPE(sym.st_info) == STT_FILE || sym.st_shndx == SHN_ABS) {
		c = (ELF32_ST_BIND(sym.st_info) == STB_GLOBAL) ? 'A' : 'a';
	} else if (shdr[sym.st_shndx].sh_type == SHT_NOBITS) {
		c = (ELF32_ST_BIND(sym.st_info) == STB_GLOBAL) ? 'B' : 'b';
	} else if (shdr[sym.st_shndx].sh_flags == (SHF_MERGE | SHF_STRINGS) || (!shdr[sym.st_shndx].sh_flags && sym.st_shndx)) {
		c = (ELF32_ST_BIND(sym.st_info) == STB_GLOBAL) ? 'N' : 'n';
	} else if (shdr[sym.st_shndx].sh_flags & SHF_EXECINSTR) {
		c = (ELF32_ST_BIND(sym.st_info) == STB_GLOBAL) ? 'T' : 't';
	} else if (shdr[sym.st_shndx].sh_flags == (SHF_WRITE | SHF_ALLOC)) {
		c = (ELF32_ST_BIND(sym.st_info) == STB_GLOBAL) ? 'D' : 'd';
	} else if (shdr[sym.st_shndx].sh_flags == SHF_ALLOC) {
		c = (ELF32_ST_BIND(sym.st_info) == STB_GLOBAL) ? 'R' : 'r';
	} else if (ELF32_ST_TYPE(sym.st_info) == STT_COMMON) {
		c = 'C';
	} else if (!sym.st_shndx) {
		c = (ELF32_ST_BIND(sym.st_info) == STB_GLOBAL) ? 'U' : 'u';
	} else {c = '?';}

	//TODO Add check if symbol is in BSS table

	return c;
}

int
halfCompute(Elf32_Ehdr *elf_header, nm nmFile)
{
	if (elf_header->e_shoff < 1 || elf_header->e_shnum < 1)
		goto failure;

	if (!(nmFile.elf32SectionsPtr = (Elf32_Shdr *)((char *)nmFile.mmapPtr + elf_header->e_shoff)))
		goto failure;

	if (elf_header->e_shnum <= 0 || (long unsigned int)nmFile.fileInfo.st_size < elf_header->e_shoff)
		goto failure;

	for (size_t i = 1; i < elf_header->e_shnum; i++) {
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
