#include "../include/include.h"

#include <stdio.h>
static int	checkFormat(Elf64_Ehdr *elf_header, nm nmFile)
{
	if (!elf_header || !elf_header->e_type)
		goto failure;
	//Check if file type != object files or .so
	if (elf_header->e_type != ET_EXEC && elf_header->e_type != ET_DYN) {
		ft_putstr_fd("nm: ", 2);
		ft_putstr_fd(nmFile.fileName, 2);
		ft_putendl_fd(": file format not recognized", 2);
		goto failure;
	}
	//Check if file is 32 or 64 bits
	if (elf_header->e_ident[EI_CLASS] == ELFCLASS32) {
		printf("32 bit\n");
		//GOTO 32 bit compute
	} else if (elf_header->e_ident[EI_CLASS] == ELFCLASS64) {
		printf("64 bit\n");
		printf("e_flag ->%lu\n", elf_header->e_entry + 2);
		//GOTO 64 bit compute
	}

	return (0);

failure:
	return (1);
}

int	computeElf(nm nmFile)
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
