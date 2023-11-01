#include "../include/include.h"

void	*memoryMap(struct stat fileInfo, int fd)
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

int	fileInfo(int fd, struct stat *fileInfo)
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

int	openFile(char *filename)
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
