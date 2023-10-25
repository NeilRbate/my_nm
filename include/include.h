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


/*############################DEFINE ZONE##############################*/

#define TRUE	0X0000
#define FALSE	0X1111

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
#define A_OPT		1
#define G_OPT		2
#define U_OPT		3
#define R_OPT		4
#define P_OPT		5
#define INVALID_OPT	6


typedef struct {

	int		fd;
	int 		nbArgs;
	int		flags;
	char		*fileName;
	char		**args;
	struct stat	fileInfo;

}		nm;

/*############################FUNCTION ZONE##############################*/

/*
 * This function is use to send a personnal error message
 * dir:
 * 	src/main.c
 */
void	putError(char *errorMessage);

/*
 * This function is use to send an error when an option is invalid
 * dir: 
 * 	src/main.c
 */
void	putInvalidOption(char *option);

/*
 * This function init the struct nm on launch
 * dir:
 * 	src/init.c
 */
void	initNmFile(nm *nmFile, int argc, char **argv);

/*
 * This function control arguments (number, options, valid file..)
 * Own error message is print by itself, no need to catch error nb
 * dir:
 * 	src/parser.c
 * return value:
 * 	FALSE if they ar a problem on args
 * 	True if everything is ok
 */
int	argControl(nm *nmFile);

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
int	openFile(char *filename);

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
 

int	fileInfo(int fd, struct stat *fileInfo);

#endif
