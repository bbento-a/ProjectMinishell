
#include "../minishell.h"

// Prints an error message to the stderr and takes/returns its error code

int	display_err(char *local, char *arg, char *error_msg, int err_code)
{
	if (local)
		printf("%s: ", local);
	if (arg)
		printf("%s: ", arg);
	printf("%s", error_msg);
	printf("\n");
	data()->exit_code = err_code;
	if (err_code < 0)
		data()->exit_code = 1;
	return (err_code);
}
