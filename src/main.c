#include "../include/include.h"

void
putInvalidOption(char *option)
{
	ft_putstr_fd("invalid option -- '", STDERR);
	if (option)
		ft_putstr_fd(option, STDERR);
	ft_putendl_fd("'", STDERR);
	ft_putendl_fd("Usage: ft_nm [option(s)] [file(s)]", STDERR);
}

void
putError(char *errorMessage)
{
	if (errorMessage) {
		ft_putstr_fd("ft_nm: ", STDERR);
		ft_putendl_fd(errorMessage, STDERR);
	}
}

int
main(int argc, char **argv)
{
	nm	nmFile;

	//Init nmFile structure
	initNmFile(&nmFile, argc, argv);
	nmFile.flags =		NO_OPT;
	nmFile.displayNb =	0;

	//Control arguments
	if (argControl(&nmFile) == FALSE)
		goto failure;

	for (int i = 1; i < argc; i++) {

		if (ft_strlen(argv[i]) > 0 && argv[i][0] == '-')
			continue;
		//Open file
		if ((nmFile.fd = openFile(argv[i])) < 0)
			goto failure;

		if (nmFile.fileName == NULL)
			nmFile.fileName = argv[i];
		nmFile.argndx = i;

		//Grab fstat info from file
		if ((fileInfo(nmFile.fd, &nmFile.fileInfo)) == FALSE)
			goto failure;
	
		//mmap the file
		if((nmFile.mmapPtr = memoryMap(nmFile.fileInfo, nmFile.fd)) == MAP_FAILED)
			goto failure;
	
		if (computeElf(nmFile) != 0)
			goto clear_exit;

		munmap(nmFile.mmapPtr, nmFile.fileInfo.st_size);

		//Clean struct
		initNmFile(&nmFile, argc, argv);
	}

return (0);

clear_exit:
	munmap(nmFile.mmapPtr, nmFile.fileInfo.st_size);
	return (0);

failure:
	return (1);
}
