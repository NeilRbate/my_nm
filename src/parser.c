#include "../include/include.h"

static int
optionsControl(nm *nmFile, char *arg)	
{
	size_t	size = ft_strlen(arg);
	short	i = 1;
start:
	if (!arg[i] || size < 2) 
		return (FALSE);
	else if (ft_strncmp(arg + i, "a", 1 ) == 0 ) {
		if (GET_A_FLAG(nmFile->flags) != A_OPT)
			nmFile->flags |= A_OPT;
		goto ret;
	} else if (ft_strncmp(arg + i, "g", 1) == 0) {
		if (GET_G_FLAG(nmFile->flags) != G_OPT)
			nmFile->flags |= G_OPT;
		goto ret;
	} else if (ft_strncmp(arg + i, "u", 1) == 0) {
		if (GET_U_FLAG(nmFile->flags) != U_OPT)
			nmFile->flags |= U_OPT;
		goto ret;
	} else if (ft_strncmp(arg + i, "r", 1) == 0) {
		if (GET_U_FLAG(nmFile->flags) != R_OPT)
			nmFile->flags |= R_OPT;
		goto ret;
	} else if (ft_strncmp(arg + i, "p", 1) == 0) {
		if (GET_P_FLAG(nmFile->flags) != P_OPT)
			nmFile->flags |= P_OPT;
		goto ret;
	}

	nmFile->flags = INVALID_OPT;
	putInvalidOption(arg);
	return (FALSE);

ret:
	i++;
	if (arg[i])
		goto start;
	return (TRUE);
}

static int
loopArgs(nm *nmFile)
{
	for (int i = 1; i < nmFile->nbArgs; i++) {
		if (nmFile->args[i] && nmFile->args[i][0] == '-') {
			if (optionsControl(nmFile, nmFile->args[i]) == FALSE)
				return FALSE;
		}
		else
			nmFile->displayNb++;
	}
	return TRUE;
}

int
argControl(nm *nmFile)
{
	if(!nmFile)
		goto failure;

	if (nmFile->nbArgs < 2) {
		if ((nmFile->fd = open("a.out", O_RDONLY)) < 0) {
			putError("'a.out': No such file");
			goto failure;
		}
	} else if (nmFile->nbArgs == 2) {
		if (ft_strlen(nmFile->args[1]) >= 2 && ft_strncmp(nmFile->args[1], "-", 1) == 0) {
			if (optionsControl(nmFile, nmFile->args[1]) == FALSE)
				goto failure;
			if ((nmFile->fd = open("a.out", O_RDONLY)) < 0) {
				putError("'a.out': No such file");
				goto failure;
			}
		} else
			return TRUE;

	} else if (nmFile->nbArgs > 2) {
		if (loopArgs(nmFile) == FALSE) {
			goto failure;
		}
		return (TRUE);
	}
	return (TRUE);
failure:
	return (FALSE);
}
