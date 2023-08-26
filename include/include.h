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

#define TRUE 1
#define FALSE 0

#define STDOUT 1
#define STDERR 2


#endif
