#include "../include/include.h"

#include <stdio.h>

char            print_type(Elf64_Sym sym, Elf64_Shdr *shdr)
{
  char  c;

  if (ELF64_ST_BIND(sym.st_info) == STB_GNU_UNIQUE)
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
  return c;
}

void
printSymtab(nm nmFile)
{
	Elf64_Sym	*sym = (Elf64_Sym *)nmFile.elf64Symtab;
	Elf64_Sym	*dynSym = (Elf64_Sym *)nmFile.elf64DynSymtab;

	//char	*strTab = ((char *)nmFile.mmapPtr + nmFile.elf64StrTab->sh_offset);
	//char	*dynStrTab = ((char *)nmFile.mmapPtr + nmFile.elf64DynStrTab->sh_offset);

	
	for (size_t i = 0; i < nmFile.elf64Symtab->sh_size / nmFile.elf64Symtab->sh_entsize; i++) {
		printf("sym n:[%ld], Type: [%c]\n", i, print_type(sym[i], nmFile.elf64Symtab));
		//printf("name %s\n", (char *)nmFile.elf64StrTab + i);
		//printf("sym_name [%s]\n", strTab + sym[i].st_name);
		//printf("%ld Dynsym_name [%s]\n", i,(char *)nmFile.elf64DynStrTab + dynSym[i].st_name);
		//printf("%s", strTab + i);
	}

	for (size_t i = 0; i < nmFile.elf64DynSymtab->sh_size / nmFile.elf64DynSymtab->sh_entsize; i++) {
		//if (dynSym[i].st_shndx == SHN_UNDEF)
		printf("Dynsym n:[%ld], Type: [%c]\n", i, print_type(dynSym[i], nmFile.elf64DynSymtab));
			//printf("DynSym_name [%s]\n", dynStrTab + dynSym[i].st_name);
	}
	printf("\nSymtab END ---------------\n");
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
		//printf("Section: [%s]\n", sectionsName + nmFile.elf64SectionsPtr[i].sh_name);
		if (i == 0 || !nmFile.elf64SectionsPtr[i].sh_size) continue;
		switch (nmFile.elf64SectionsPtr[i].sh_type){

			case SHT_SYMTAB:
				nmFile.elf64Symtab = nmFile.elf64SectionsPtr + i;
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
