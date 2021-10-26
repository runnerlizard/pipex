#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

int main (int argc, const char *argv[])
{
	const char	*newargv[argc];
	const char	*newenviron[] = { NULL };
	int			i;

	i = 0;
	while (argv)
		newargv[i++] = argv
	if (_execve(argv[1], newargv, newenviron) == -1)
		perror("Cant execute\n");
	printf("Error\n");
	/*int	id = fork();
	if (id != 0)
		printf("Parent here!\n");
	if (id == 0)
		printf("Child here!\n");*/
	exit(1);
}
