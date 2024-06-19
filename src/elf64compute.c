#include "../include/include.h"

#include <stdio.h>

static char            printType(Elf64_Sym sym, Elf64_Shdr *shdr)
{
  char  c;

  if (ELF64_ST_TYPE(sym.st_info) == STT_OBJECT && ELF64_ST_BIND(sym.st_info) == STB_WEAK) {
	  c = 'v';
	  if (sym.st_shndx)
		  c = 'V';
  } else if (ELF64_ST_BIND(sym.st_info) == STB_WEAK) {
	  c = 'w';
	  if (sym.st_shndx)
		  c = 'W';
  } else if (ELF64_ST_TYPE(sym.st_info) == STT_GNU_IFUNC) {
	  c = 'i';
  } else if (ELF64_ST_TYPE(sym.st_info) == STT_FILE || sym.st_shndx == SHN_ABS) {
	  c = (ELF64_ST_BIND(sym.st_info) == STB_GLOBAL) ? 'A' : 'a';
  } else if (shdr[sym.st_shndx].sh_type == SHT_NOBITS && shdr[sym.st_shndx].sh_flags == (SHF_ALLOC | SHF_WRITE)) {
	  c = (ELF64_ST_BIND(sym.st_info) == STB_GLOBAL) ? 'B' : 'b';
  } else if (shdr[sym.st_shndx].sh_flags == (SHF_MERGE | SHF_STRINGS) || (!shdr[sym.st_shndx].sh_flags && sym.st_shndx)) {
	  c = (ELF64_ST_BIND(sym.st_info) == STB_GLOBAL) ? 'N' : 'n';
  } else if (shdr[sym.st_shndx].sh_flags & SHF_EXECINSTR) {
	  c = (ELF64_ST_BIND(sym.st_info) == STB_GLOBAL) ? 'T' : 't';
  } else if (shdr[sym.st_shndx].sh_flags == (SHF_WRITE | SHF_ALLOC)) {
	  c = (ELF64_ST_BIND(sym.st_info) == STB_GLOBAL) ? 'D' : 'd';
  } else if (shdr[sym.st_shndx].sh_flags == SHF_ALLOC) {
	  c = (ELF64_ST_BIND(sym.st_info) == STB_GLOBAL) ? 'R' : 'r';
  } else if (ELF64_ST_TYPE(sym.st_info) == STT_COMMON) {
	  c = 'C';
  } else if (!sym.st_shndx) {
	  c = (ELF64_ST_BIND(sym.st_info) == STB_GLOBAL) ? 'U' : 'u';
  } else {
	  c = '?';
  }
  return c;


  /*

  else if (ELF64_ST_BIND(sym.st_info) == STB_GNU_UNIQUE)
    c = 'u';
  else if (ELF64_ST_BIND(sym.st_info) == STB_WEAK)
    {
      c = 'W';
      if (sym.st_shndx == SHN_UNDEF)
        c = 'w';
    }
  else if (ELF64_ST_BIND(sym.st_info) == STB_WEAK && ELF64_ST_TYPE(sym.st_info) == STT_OBJECT)
    {
      c = 'V';
      if (sym.st_shndx == SHN_UNDEF)
        c = 'v';
    }
  else if (sym.st_shndx == SHN_UNDEF)
    c = 'U';
  else if (sym.st_shndx == SHN_ABS)
    c = 'A';
  else if (sym.st_shndx == SHN_COMMON)
    c = 'C';
  else if (shdr[sym.st_shndx].sh_type == SHT_NOBITS
       && shdr[sym.st_shndx].sh_flags == (SHF_ALLOC | SHF_WRITE))
    c = 'B';
  else if (shdr[sym.st_shndx].sh_type == SHT_PROGBITS
       && shdr[sym.st_shndx].sh_flags == SHF_ALLOC)
    c = 'R';
  else if (shdr[sym.st_shndx].sh_type == SHT_PROGBITS
       && shdr[sym.st_shndx].sh_flags == (SHF_ALLOC | SHF_WRITE))
    c = 'D';
  else if (shdr[sym.st_shndx].sh_type == SHT_PROGBITS
       && shdr[sym.st_shndx].sh_flags == (SHF_ALLOC | SHF_EXECINSTR))
    c = 'T';
  else if (shdr[sym.st_shndx].sh_type == SHT_DYNAMIC)
    c = 'D';
  else
    c = '?';
  if (ELF64_ST_BIND(sym.st_info) == STB_LOCAL && c != '?')
    c += 32;
    */
}

void
printSymtab(nm nmFile)
{
	
	for (size_t i = 0; i < nmFile.elf64Symtab->sh_size / nmFile.elf64Symtab->sh_entsize; i++) {
		printf("[%ld] SymType: [%c] SymName: [%s]\n", i, printType(nmFile.elf64Sym[i], nmFile.elf64Symtab), nmFile.symName + nmFile.elf64Sym[i].st_name);
	}

}

int
fullCompute(Elf64_Ehdr *elf_header, nm nmFile)
{
	if (elf_header->e_shoff < 1 || elf_header->e_shnum < 1)
		goto failure;

	if (!(nmFile.elf64SectionsPtr = (Elf64_Shdr *)((char *)nmFile.mmapPtr + elf_header->e_shoff)))
		goto failure;

	char	*sectionsName = ((char *)nmFile.mmapPtr + nmFile.elf64SectionsPtr[elf_header->e_shstrndx].sh_offset);

	for (size_t i = 0; i < elf_header->e_shnum; i++) {
		if (i == 0 || !nmFile.elf64SectionsPtr[i].sh_size) continue;
		switch (nmFile.elf64SectionsPtr[i].sh_type){

			case SHT_SYMTAB:
				nmFile.elf64Symtab = &nmFile.elf64SectionsPtr[i];
				nmFile.elf64Sym = (Elf64_Sym *)((char *)nmFile.mmapPtr + nmFile.elf64SectionsPtr[i].sh_offset);
				nmFile.symName = ((char *)nmFile.mmapPtr + nmFile.elf64SectionsPtr[nmFile.elf64SectionsPtr[i].sh_link].sh_offset);
				printf("SHT_SYMTAB find !\n");
				continue;

			case SHT_STRTAB:
				if (ft_strncmp(sectionsName + nmFile.elf64SectionsPtr[i].sh_name, ".strtab", 8) == 0) {
					printf("SHT_STRTAB find !\n");
					nmFile.elf64StrTab = nmFile.elf64SectionsPtr + i;
					continue;
				} else if (ft_strncmp(sectionsName + nmFile.elf64SectionsPtr[i].sh_name, ".dynstr", 8) == 0) {
					printf("DynStrtab FIND !\n");
					nmFile.elf64DynStrTab = nmFile.elf64SectionsPtr + i;
					continue;
				} else if (ft_strncmp(sectionsName + nmFile.elf64SectionsPtr[i].sh_name, ".shstrtab", 10) == 0) {
					printf("shstrtab find !\n");
					nmFile.elf64ShStrTab = nmFile.elf64SectionsPtr + i;
				}
				continue;

			case SHT_DYNSYM:
				nmFile.elf64DynSymtab = nmFile.elf64SectionsPtr + i;
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
