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

	initNmFile(&nmFile, argc, argv);
	if (!argControl(&nmFile))
		goto error;
	if (openFile(argv[1]) == -1)
		goto error;

	return (0);

error:
	return (1);
}
