#include "../include/include.h"

#include <stdio.h>

static int
checkFormat(Elf64_Ehdr *elf_header, nm nmFile)
{
	if (!elf_header || !elf_header->e_type)
		goto failure;
	//Check if file type != object files or .so
	if (elf_header->e_type != ET_EXEC && elf_header->e_type != ET_DYN && elf_header->e_type != ET_REL) {
		goto failure;
	}	
	//Check if file is 32 or 64 bits
	if (elf_header->e_ident[EI_CLASS] && elf_header->e_ident[EI_CLASS] == ELFCLASS32) {
		switch (halfCompute((Elf32_Ehdr *)elf_header, nmFile)) {
			case FAILURE:
				goto failure;
			case NOSYM:
				goto nosym;
		}
	} else if (elf_header->e_ident[EI_CLASS] == ELFCLASS64) {
		switch (fullCompute(elf_header, nmFile)) {
			case FAILURE:
				goto failure;
			case NOSYM:
				goto nosym;
		}
	} else
		goto failure;

	return (0);

failure:
	ft_printf("ft_nm: %s: file format not recognized\n", nmFile.args[nmFile.argndx]);
	return (1);

nosym:
	ft_printf("ft_nm: %s: no symbols\n", nmFile.args[nmFile.argndx]);
	return (2);
}

int
computeElf(nm nmFile)
{
	Elf64_Ehdr *elf_header = (Elf64_Ehdr *)nmFile.mmapPtr;

	if (!elf_header)
		goto failure;
		
	if (checkFormat(elf_header, nmFile) != 0)
		goto failure;

	return (0);

failure:
	return (1);
}
