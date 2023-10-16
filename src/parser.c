#include "../include/include.h"


//Control validity of option.
int	optionsControl(nm *nmFile, char *arg)	
{
	if (ft_strncmp(arg, "-a", 3) == 0) {
		nmFile->flags = A_OPT;
		goto ret;
	} else if (ft_strncmp(arg, "-g", 3) == 0) {
		nmFile->flags = G_OPT;
		goto ret;
	} else if (ft_strncmp(arg, "-u", 3) == 0) {
		nmFile->flags = U_OPT;
		goto ret;
	} else if (ft_strncmp(arg, "-r", 3) == 0) {
		nmFile->flags = R_OPT;
		goto ret;
	} else if (ft_strncmp(arg, "-p", 3) == 0) {
		nmFile->flags = P_OPT;
		goto ret;
	}

	nmFile->flags = INVALID_OPT;
	putInvalidOption(arg);
	return (FALSE);

ret:
	return (TRUE);
}

int	argControl(nm *nmFile)
{
	if (nmFile->nbArgs < 2) {
		if ((nmFile->fd = open("a.out", O_RDONLY)) < 0) {
			putError("a.out: No such file");
			return (FALSE);
		}
		//Goto file check
	} else if (nmFile->nbArgs == 2) {
		if (ft_strlen(nmFile->args[1]) >= 2 && ft_strncmp(nmFile->args[1], "-", 1) == 0)
			if (optionsControl(nmFile, nmFile->args[1]) == FALSE)
				return (FALSE);
	}
	return (TRUE);
}
