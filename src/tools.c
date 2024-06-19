#include "../include/include.h"

char
printType(Elf64_Sym sym, Elf64_Shdr *shdr, int bitSize)
{
	char  c;

	//TODO Add comversion to 32 bit
	if (bitSize == 32) {
		sym = (Elf32_Sym)sym;
		(Elf32_Shdr *)shdr;
	}

	if (ELF64_ST_TYPE(sym.st_info) == STT_OBJECT && ELF64_ST_BIND(sym.st_info) == STB_WEAK) {
		c = 'v'; if (sym.st_shndx) c = 'V';
	} else if (ELF64_ST_BIND(sym.st_info) == STB_WEAK) {
		c = 'w'; if (sym.st_shndx) c = 'W';
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
	} else {c = '?';}

	return c;
}

void
printSymtab(nm nmFile, int bitSize)
{
	size_t	size = 0;

	if (bitSize == 32) size = nmFile.elf32Symtab->sh_size / nmFile.elf32Symtab->sh_entsize;
	else if (bitSize == 64) size = nmFile.elf64Symtab->sh_size / nmFile.elf64Symtab->sh_entsize;

	if (size < 1) return;

	symLst	list[size];
	//TODO Format all this informations
	for (size_t i = 0; i < size; i++) {
		if (i == 0) continue;
		
		if (bitSize == 64) {
			list[i].symTyp = printType(nmFile.elf64Sym[i], nmFile.elf64SectionsPtr, 64);
			list[i].symStr = nmFile.symName + nmFile.elf64Sym[i].st_name;
			list[i].symAddr = nmFile.elf64Sym[i].st_value;
		} else if (bitSize == 32) {
			list[i].symTyp = printType((Elf64_Sym)nmFile.elf32Sym[i], (Elf64_Shdr *)nmFile.elf32SectionsPtr, 32);
			list[i].symStr = nmFile.symName + nmFile.elf32Sym[i].st_name;
			list[i].symAddr = nmFile.elf32Sym[i].st_value;
		}


		ft_printf("%x %c %s\n", list[i].symAddr,
			       	list[i].symTyp,
			       	list[i].symStr);
		/*
		printf("%lx %c %s\n", 
				nmFile.elf64Sym[i].st_value,
				printType(nmFile.elf64Sym[i], nmFile.elf64SectionsPtr),
			       	nmFile.symName + nmFile.elf64Sym[i].st_name);
				*/
	}
	//TODO Put this scope for option -D (Not in Mandatory/bonus but can be cool)
	/*
	for (size_t i = 0; i < nmFile.elf64DynSymtab->sh_size / nmFile.elf64DynSymtab->sh_entsize; i++) {
		if (i == 0)
			continue;
		printf("%c %s\n",
				printType(nmFile.elf64DynSym[i],
				nmFile.elf64SectionsPtr), nmFile.dynSymName + nmFile.elf64DynSym[i].st_name);
	}
	*/
}

void
*memoryMap(struct stat fileInfo, int fd)
{
	void	*mMap = NULL;

	if ((mMap =  mmap(NULL, fileInfo.st_size, PROT_READ, MAP_PRIVATE, fd, 0)) == MAP_FAILED) {
		putError("mmap failed!");
		close(fd);
		return NULL;
	}
	close(fd);
	return (mMap);
}

int
fileInfo(int fd, struct stat *fileInfo)
{	
	if (fstat(fd, fileInfo) < 0) {
		putError("fstat failure");
		goto failure;
	}
	if (fileInfo->st_size < 1) {
		putError("invalid file size");
		goto failure;
	}

	return (TRUE);

failure:
	close(fd);
	return (FALSE);
}

int
openFile(char *filename)
{
	int	fd;

	if ((fd = open(filename, O_DIRECTORY)) > 0) {
		ft_putstr_fd("nm: Warning: '", STDERR);
		ft_putstr_fd(filename, STDERR);
		ft_putendl_fd("' is a directory", STDERR);
		close(fd);
		goto failure;
	}
	if ((fd = open(filename, O_RDONLY)) < 0) {
		ft_putstr_fd("nm: '", STDERR);
		ft_putstr_fd(filename, STDERR);
		ft_putendl_fd("': No such file", STDERR);
		goto failure;
	}
	return (fd);

failure:
	return (-1);
}
