#ifndef	__FT_NM__
 #define __FT_NM__

/*
 * Welcome to NM 42 project, this .h file contains all documentations of 
 * the code and all dependencies
 *
 * This project going to use the linux kernel coding style,
 * hope you enjoy it
 *
 */

/*############################INCLUDE ZONE##############################*/

/*
 * Libft include from 42 original project.
 * #include:
 * 	stdlib.h
 * 	unistd.h
 * 	stdint.h
 */
#include "../libft/libft.h"

/*
 * Include for:
 * 	mmap
 * 	munmap
 */
#include <sys/mman.h>

/*
 * Include for:
 * 	Open
 * 	Close
 * 	Fstat
 */
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

/*
 * Include for ELF struct like Elf64_Ehdr ..
 */
#include <elf.h>


/*############################DEFINE ZONE##############################*/

#define TRUE	0X0000
#define FALSE	0X1111

#define SUCCESS	0
#define FAILURE	1
#define NOSYM	2


#define STDOUT	1
#define STDERR	2

/*
 * Flag for all option on bonus part
 *  -a
 *  -g
 *  -u
 *  -r
 *  -p
 */
#define NO_OPT		0
#define A_OPT		1 << 1 //-a opt, display or not symbol with a type
#define G_OPT		1 << 2 //-g opt, display only external symbol (SHT_GLOBAL)
#define U_OPT		1 << 3 //-u opt, display only undefined symbol ()
#define R_OPT		1 << 4 //-r opt, reverse sort of output
#define P_OPT		1 << 5 //-p opt, non sort output
#define INVALID_OPT	1 << 6


typedef struct {

	int		fd;
	int 		nbArgs;
	int		argndx;
	int		flags;

	char		*fileName;
	char		**args;
	char		*symName;
	char		*dynSymName;

	struct stat	fileInfo;

	symLst		*symList;

	Elf64_Addr	*mmapPtr;

	Elf64_Shdr	*elf64SectionsPtr;
	Elf32_Shdr	*elf32SectionsPtr;

	Elf64_Shdr	*elf64Symtab;
	Elf64_Sym	*elf64Sym;
	Elf64_Shdr	*elf64DynSymtab;
	Elf64_Sym	*elf64DynSym;

	Elf32_Shdr	*elf32Symtab;
	Elf32_Shdr	*elf32DynSymtab;

	Elf64_Shdr      *elf64StrTab;
	Elf64_Shdr      *elf64ShStrTab;
	Elf64_Shdr      *elf64DynStrTab;
	Elf32_Shdr      *elf32StrTab;
	Elf64_Shdr      *elf32DynStrTab;

} nm;

typedef struct {

	char		symTyp;
	char		*symStr;
	char		*symAddr;
	struct symLst	*next;
	
} symLst;

/*############################FUNCTION ZONE##############################*/

/*
 * This function is use to send a personnal error message
 * dir:
 * 	src/main.c
 */
void
putError(char *errorMessage);

/*
 * This function is use to send an error when an option is invalid
 * dir: 
 * 	src/main.c
 */
void
putInvalidOption(char *option);

/*
 * This function init the struct nm on launch
 * dir:
 * 	src/init.c
 */
void
initNmFile(nm *nmFile, int argc, char **argv);

/*
 * This function control arguments (number, options, valid file..)
 * Own error message is print by itself, no need to catch error nb
 * dir:
 * 	src/parser.c
 * return value:
 * 	FALSE if they ar a problem on args
 * 	True if everything is ok
 */
int
argControl(nm *nmFile);

/*
 * This function control the opening status of file
 * Own error message is print by itself, no need to catch error nb
 * dir:
 * 	src/tools.c
 *
 * return value:
 * 	-1 if some issue with the fd
 * 	fd nb if opening correctly
 */
int
openFile(char *filename);

/*
 * This function is used to use fstat function on open fd
 * Put data on *fileInfo past in arg
 * Own error message is print by itself, no need to cath error bn
 * dir:
 * 	src/tools.c
 *
 * return value:
 *	FALSE in failure
 *	TRUE on success		
 */
int
fileInfo(int fd, struct stat *fileInfo);


/*
 * This function create the memory map from file point in filInfo struct
 * Own error message is print by itself, no need to catch it
 * dir:
 * 	src/tools.c
 * return value:
 * 	??
 * 	
 */
void
*memoryMap(struct stat fileInfo, int fd);

/*
 * This function compute the Elf validity test and execute the nm function
 * dir:
 * 	src/elfcompute.c
 * return value:
 * 	success 1
 * 	failure 0
 */
int
computeElf(nm nmFile);

/*
 * This function is used to find the dyntab on elf 32 bits file
 * dir:
 * 	src/elf32compute.c
 * return value:
 * 	success 0
 * 	failure 1
 */
int
halfCompute(Elf32_Ehdr *elf_header, nm nmFile);

/*
 * This function is used to find the dyntab on elf 64 bites file
 * dir:
 * 	src/elf64compute.c
 * return value:
 * 	success 0
 * 	failure 1
 */
int
fullCompute(Elf64_Ehdr *elf_header, nm nmFile);


#endif
