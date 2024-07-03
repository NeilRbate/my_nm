#include "../include/include.h"

static int
isSymSort(symLst *list, size_t size) 
{
	for (size_t i = 1; i < size - 1; i++) {
		if (ft_strcmp(list[i].symStr, list[i + 1].symStr) > 0)
			return 0;
	}
	return 1;
}

static char*
cleanSymStr(char *str) 
{


	size_t	len = ft_strlen(str);

	if (len < 1)
		return str;

	char	*mmouv = malloc(sizeof(char) * len);
	if (!mmouv)
		return NULL;
	int i = 0, j = 0;
	ft_memset(mmouv, '\0', len);
	while (str[i]) {
		if (str[i] != '_' && str[i] != '.')
			mmouv[j++] = ft_tolower(str[i]);
		i++;
	}
	return mmouv;
}

static void
sortSymList(symLst *list, size_t size) 
{
	size_t i = 1;


	while (i < size - 1) {
		if (isSymSort(list, size) == 1)
			break;
		for (size_t j = 1; j < size - 1; j++ ) {
			if (ft_strcmp(list[j].symTrimStr, list[j + 1].symTrimStr) == 0 
					&& (ft_strlen(list[j].symTrimStr) == ft_strlen(list[j + 1].symTrimStr))) {
				if (ft_strcmp(list[j].symStr, list[j + 1].symStr) > 0) {
					symLst temp = list[j];
					list[j] = list[j + 1];
					list[j + 1] = temp;
				}
			} else if (ft_strcmp(list[j].symTrimStr, list[j + 1].symTrimStr) > 0) {
				symLst temp = list[j];
				list[j] = list[j + 1];
				list[j + 1] = temp;
			}
		}
		i++;
	}
}

static void
reverseSortSymList(symLst *list, size_t size)
{
	size_t i = 1;


	while (i < size - 1) {
		for (size_t j = 1; j < size - 1; j++ ) {

			if (ft_strcmp(list[j].symTrimStr, list[j + 1].symTrimStr) == 0 
					&& (ft_strlen(list[j].symTrimStr) == ft_strlen(list[j + 1].symTrimStr))) {
				if (ft_strcmp(list[j].symStr, list[j + 1].symStr) < 0) {
					symLst temp = list[j];
					list[j] = list[j + 1];
					list[j + 1] = temp;
				}
			} else if (ft_strcmp(list[j].symTrimStr, list[j + 1].symTrimStr) < 0) {
				symLst temp = list[j];
				list[j] = list[j + 1];
				list[j + 1] = temp;
			}
		}
		i++;
	}
}

static void
printSymAddr(unsigned long long addr, uint bitSize, char type) 
{
	
	char	hex[17];
	int	temp = 0, i = 16;

	ft_memset(hex, '0', 17);

	if (type == 'U' || type == 'w' || type == 'v') {
		if (bitSize == 64)
			ft_printf("                ");
		else 
			ft_printf("        ");
		return;
	}

	while (addr != 0) {
		temp = addr % 16;
		if (temp < 10)
			temp = temp + 48;
		else
			temp = temp + 87;
		hex[i--] = temp;
		addr = addr / 16;
	}
	if (bitSize == 32)
		i = 8;
	else
		i = 0;
	while(i++ < 16)
		ft_printf("%c", hex[i]);
}

static void
createSymList(symLst *list, nm nmFile, int bitSize)
{
	size_t	size = 0;

	if (bitSize == 32) size = nmFile.elf32Symtab->sh_size / nmFile.elf32Symtab->sh_entsize;
	else if (bitSize == 64) size = nmFile.elf64Symtab->sh_size / nmFile.elf64Symtab->sh_entsize;

	if (size < 1) return;

	for (size_t i = 0; i < size; i++) {

		list[i].symTrimStr = NULL;
		if (i == 0) continue;
		
		if (bitSize == 32) {
			list[i].symTyp = findType32((Elf32_Sym)nmFile.elf32Sym[i], nmFile.elf32SectionsPtr);
			list[i].symStr = nmFile.symName + nmFile.elf32Sym[i].st_name;
			list[i].symAddr = nmFile.elf32Sym[i].st_value;
			list[i].symTrimStr = cleanSymStr(list[i].symStr);
		} else {
			list[i].symTyp = findType64(nmFile.elf64Sym[i], nmFile.elf64SectionsPtr);
			list[i].symStr = nmFile.symName + nmFile.elf64Sym[i].st_name;
			list[i].symAddr = nmFile.elf64Sym[i].st_value;
			list[i].symTrimStr = cleanSymStr(list[i].symStr);
		}
	}
}

static void
printRawSymList(symLst *list, size_t size, int bitSize)
{
	for (size_t i = 1; i < size; i++) {

		if (bitSize == 64)
			printSymAddr(list[i].symAddr, 64, list[i].symTyp);
		else
			printSymAddr(list[i].symAddr, 32, list[i].symTyp);
		ft_printf(" %c %s\n",
				list[i].symTyp,
				list[i].symStr);
		if (list[i].symTrimStr != NULL && ft_strlen(list[i].symTrimStr) > 0)
			free(list[i].symTrimStr);
	}
}

static void
printFlagSymList(symLst *list, size_t size, int bitSize, int flags)
{
	for (size_t i = 1; i < size; i++) {

		if (!list[i].symStr || ft_strlen(list[i].symStr) < 1)
			continue;
		else if (GET_U_FLAG(flags) == U_OPT) {
			if (list[i].symTyp == 'U' || list[i].symTyp == 'w'){
				if (bitSize == 64)
					printSymAddr(list[i].symAddr, 64, list[i].symTyp);
				else
					printSymAddr(list[i].symAddr, 32, list[i].symTyp);
				ft_printf(" %c %s\n",
					list[i].symTyp,
					list[i].symStr);
			}
		} else if (GET_G_FLAG(flags) == G_OPT) {
			if (list[i].symTyp >= 'A' && list[i].symTyp <= 'Z') {
				if (bitSize == 64)
					printSymAddr(list[i].symAddr, 64, list[i].symTyp);
				else
					printSymAddr(list[i].symAddr, 32, list[i].symTyp);
				ft_printf(" %c %s\n",
					list[i].symTyp,
					list[i].symStr);
			}

		} else if (list[i].symTyp != 'a') {
			if (bitSize == 64)
				printSymAddr(list[i].symAddr, 64, list[i].symTyp);
			else
				printSymAddr(list[i].symAddr, 32, list[i].symTyp);
			ft_printf(" %c %s\n",
					list[i].symTyp,
					list[i].symStr);

		}
		if (list[i].symTrimStr != NULL && ft_strlen(list[i].symTrimStr) > 0)
			free(list[i].symTrimStr);
	}
}


void
printSymtab(nm nmFile, int bitSize)
{
	size_t	size = 0;

	if (bitSize == 32) size = nmFile.elf32Symtab->sh_size / nmFile.elf32Symtab->sh_entsize;
	else if (bitSize == 64) size = nmFile.elf64Symtab->sh_size / nmFile.elf64Symtab->sh_entsize;

	symLst	list[size];
	createSymList(list, nmFile, bitSize);

	if (GET_P_FLAG(nmFile.flags) != P_OPT) {
		if (GET_R_FLAG(nmFile.flags) == R_OPT)
			reverseSortSymList(list, size);
		else
			sortSymList(list, size);
	}
	if (nmFile.displayNb > 1) {
		ft_printf("\n%s:\n", nmFile.fileName);
	}
	if (GET_A_FLAG(nmFile.flags) == A_OPT)
		printRawSymList(list, size, bitSize);
	else
		printFlagSymList(list, size, bitSize, nmFile.flags);

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
		ft_putstr_fd("ft_nm: Warning: '", STDERR);
		ft_putstr_fd(filename, STDERR);
		ft_putendl_fd("' is a directory", STDERR);
		close(fd);
		goto failure;
	}
	if ((fd = open(filename, O_RDONLY)) < 0) {
		ft_putstr_fd("ft_nm: '", STDERR);
		ft_putstr_fd(filename, STDERR);
		ft_putendl_fd("': No such file", STDERR);
		goto failure;
	}
	return (fd);

failure:
	return (-1);
}
