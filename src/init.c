#include "../include/include.h"

void
initNmFile(nm *nmFile, int argc, char **argv)
{
	if (!nmFile)
		return;

	nmFile->fd =		0;
	nmFile->fileName =	NULL;
	nmFile->flags =		NO_OPT;
	nmFile->nbArgs =	argc;
	nmFile->args =		argv;
	nmFile->mmapPtr =	NULL;

	nmFile->symtabSize = 	0;
	nmFile->strtabSize =	0;
	nmFile->dynsymSize =	0;

	nmFile->elf64SectionsPtr = 	NULL;
	nmFile->elf32SectionsPtr = 	NULL;
	nmFile->elf64Symtab = 		NULL;
	nmFile->elf64DynSymtab =	NULL;
	nmFile->elf32Symtab = 		NULL;
	nmFile->elf32DynSymtab = 	NULL;
	nmFile->elf64StrTab = 		NULL;
	nmFile->elf64DynStrTab = 	NULL;
	nmFile->elf32StrTab = 		NULL;
	nmFile->elf32DynStrTab =	NULL;
	nmFile->elf64Ehdr = 		NULL;
	nmFile->elf32Ehdr = 		NULL;
}
