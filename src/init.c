#include "../include/include.h"

void	initNmFile(nm *nmFile, int argc)
{
	nmFile->fd = 0;
	nmFile->fileName = NULL;
	nmFile->flags = 0;
	nmFile->nbArgs = argc;
}
