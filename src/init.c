#include "../include/include.h"

void
initNmFile(nm *nmFile, int argc, char **argv)
{
	if (!nmFile)
		return;

	nmFile->fd =		0;
	nmFile->fileName =	NULL;
	nmFile->nbArgs =	argc;
	nmFile->args =		argv;
	nmFile->mmapPtr =	NULL;

	nmFile->elf64SectionsPtr = 	NULL;
	nmFile->elf32SectionsPtr = 	NULL;
	nmFile->elf64Symtab = 		NULL;
	nmFile->elf64Sym = 		NULL;
	nmFile->elf64DynSymtab =	NULL;
	nmFile->elf64DynSym =		NULL;

	nmFile->elf32Symtab =		NULL;
	nmFile->elf32Sym =		NULL;
	nmFile->elf32DynSymtab = 	NULL;
	nmFile->elf32DynSym =		NULL;

	nmFile->elf64StrTab = 		NULL;
	nmFile->elf64DynStrTab =	NULL;
	nmFile->elf32StrTab =		NULL;
	nmFile->elf32DynStrTab =	NULL;


	nmFile->symList = 		NULL;
}
