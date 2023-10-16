#include "../include/include.h"

int	openFile(char *filename)
{
	//struct stat	fd_stat;
	int		fd;

	fd = open(filename, O_DIRECTORY);
	if (fd) {
		ft_putstr_fd("nm: Warning: '", STDERR);
		ft_putstr_fd(filename, STDERR);
		ft_putendl_fd("'is a directory", STDERR);
		return (-1);
	}
	fd = open(filename, O_RDONLY);
	if (!fd)
		return (-1);
	return fd;
}
