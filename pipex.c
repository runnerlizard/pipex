#include "pipex.h"
#include <stdio.h>
#include <io.h>

int	main(int argc, char **argv)
{
	int	i;

	i = 1;
	if (argc != 5)
		printf("Error! Four arguments needed\n", argv[i++]);
	if (access(argv[1], 3) != 0)
		printf("Error! File %s doesn't exist or not readable\n", argv[i++]);
	
	while (i < argc)
		printf("%s\n", argv[i++]);
	return (0);
}
