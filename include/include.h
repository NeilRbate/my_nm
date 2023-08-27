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

#define TRUE	1
#define FALSE	0

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
#define A_OPT	1
#define G_OPT	2
#define U_OPT	3
#define R_OPT	4
#define P_OPT	5


typedef struct {

	int	fd;
	int 	nbArgs;
	char	*fileName;
	char	*flags;
	char	**args;

}		nm;

/*############################FUNCTION ZONE##############################*/


/*
 * This function init the struct nm on launch
 * dir:
 * 	src/init.c
 */

void	initNmFile(nm *nmFile, int argc);

#endif
