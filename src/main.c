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

#include <stdio.h>

int	main(int argc, char **argv)
{
	nm	nmFile;


	initNmFile(&nmFile, argc, argv);
	if (argControl(&nmFile) == FALSE)
		goto failure;
	if ((nmFile.fd = openFile(argv[1])) == -1)
		goto failure;
	if ((fileInfo(nmFile.fd, &nmFile.fileInfo)) == FALSE)
		goto failure;
	//OK 
		

	return (0);

failure:
	return (1);
}
