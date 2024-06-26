#include "../include/include.h"

int
printSymAddr(unsigned long long addr, uint bitSize) {
	
	//TODO Create a convert classe to put number in hex
	(void)bitSize;
	return 32;

}

void
printSymtab(nm nmFile, int bitSize)
{
	size_t	size = 0;

	if (bitSize == 32) size = nmFile.elf32Symtab->sh_size / nmFile.elf32Symtab->sh_entsize;
	else if (bitSize == 64) size = nmFile.elf64Symtab->sh_size / nmFile.elf64Symtab->sh_entsize;

	if (size < 1) return;

	symLst	list[size];
	for (size_t i = 0; i < size; i++) {
		if (i == 0) continue;
		
		if (bitSize == 64) {
			list[i].symTyp = findType64(nmFile.elf64Sym[i], nmFile.elf64SectionsPtr);
			list[i].symStr = nmFile.symName + nmFile.elf64Sym[i].st_name;
			list[i].symAddr = nmFile.elf64Sym[i].st_value;
		} else if (bitSize == 32) {
			list[i].symTyp = findType32((Elf32_Sym)nmFile.elf32Sym[i], nmFile.elf32SectionsPtr);
			list[i].symStr = nmFile.symName + nmFile.elf32Sym[i].st_name;
			list[i].symAddr = nmFile.elf32Sym[i].st_value;
		}
		ft_printf("%d %c %s\n", printSymAddr(list[i].symAddr, 32),
			       	list[i].symTyp,
			       	list[i].symStr);


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
