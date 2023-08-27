#include "../include/include.h"

int	main(int argc, char **argv)
{
	nm	nmFile;

	initNmFile(&nmFile, argc);
	if (argc < 2) {
		if ((nmFile.fd = open("a.out", O_RDONLY)) < 0) {
			ft_putendl_fd("nm: a.out: No Such File", STDERR);
			return(EXIT_FAILURE);
		}
		//Goto function to run
	}
	ft_putendl_fd(argv[0], STDOUT);

	return (0);
}
