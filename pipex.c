#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main (int argc, char *argv[])
{
  /*execv(argv[1], argv);
  perror("execv");*/

	int	id = fork();
	if (id != 0)
		printf("Parent here!\n");
	if (id == 0)
		printf("Child here!\n");

  exit(1);
}
