#include "../include/include.h"

int	main(int argc, char **argv)
{
	if (argc < 2) {
		ft_putendl_fd("ft_nm: No such file", STDOUT);
		exit(EXIT_FAILURE);
	}
	ft_putendl_fd(argv[0], STDOUT);

	return (0);
}
