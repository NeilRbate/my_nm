#include "../include/include.h"

#include <stdio.h>

static int
checkFormat(Elf64_Ehdr *elf_header, nm nmFile)
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
	if (elf_header->e_ident[EI_CLASS] && elf_header->e_ident[EI_CLASS] == ELFCLASS32) {
		printf("32 Bits ELF detected\n");
		if (halfCompute((Elf32_Ehdr *)elf_header, nmFile) == 1)
			goto failure;
	} else if (elf_header->e_ident[EI_CLASS] == ELFCLASS64) {
		switch (fullCompute(elf_header, nmFile)) {
			case FAILURE:
				goto failure;
			case NOSYM:
				goto nosym;
		}
	}

	return (0);

failure:
	return (1);

nosym:
	ft_putstr_fd("ft_nm: ", STDOUT);
	ft_putstr_fd(nmFile.args[nmFile.argndx], STDOUT);
	ft_putendl_fd(": no symbols", STDOUT);
	return (0);
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
