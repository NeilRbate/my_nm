#include "../include/include.h"

void	initNmFile(nm *nmFile, int argc, char **argv)
{
	if (!nmFile)
		return;

	nmFile->fd =		0;
	nmFile->fileName =	NULL;
	nmFile->flags =		NO_OPT;
	nmFile->nbArgs =	argc;
	nmFile->args =		argv;
	nmFile->mmapPtr =	NULL;
}
