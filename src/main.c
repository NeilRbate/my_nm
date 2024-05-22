#include "../include/include.h"

void	putInvalidOption(char *option)
{
	ft_putstr_fd("invalid option -- '", STDERR);
	if (option)
		ft_putstr_fd(option, STDERR);
	ft_putendl_fd("'", STDERR);
	ft_putendl_fd("Usage: ft_nm [option(s)] [file(s)]", STDERR);
}

void	putError(char *errorMessage)
{
	if (errorMessage) {
		ft_putstr_fd("nm: ", STDERR);
		ft_putendl_fd(errorMessage, STDERR);
	}
}

int	main(int argc, char **argv)
{
	nm	nmFile;

	//Init nmFile structure
	initNmFile(&nmFile, argc, argv);

	//Control arguments
	if (argControl(&nmFile) == FALSE)
		goto failure;

	for (int i = 1; i < argc; i++) {

		//Open file
		if ((nmFile.fd = openFile(argv[i])) < 0)
			goto failure;
		//TODO check file name for each
		nmFile.fileName = argv[i];

		//Grab fstat info from file
		if ((fileInfo(nmFile.fd, &nmFile.fileInfo)) == FALSE)
			goto failure;
	
		//mmap the file
		if((nmFile.mmapPtr = memoryMap(nmFile.fileInfo, nmFile.fd)) == MAP_FAILED)
			goto failure;
	
		if (computeElf(nmFile) != 0)
			goto clear_exit;

		munmap(nmFile.mmapPtr, nmFile.fileInfo.st_size);
	}

return (0);

clear_exit:
	munmap(nmFile.mmapPtr, nmFile.fileInfo.st_size);
	return (0);

failure:
	return (1);
}
