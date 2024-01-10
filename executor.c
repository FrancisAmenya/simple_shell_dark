#include "main.h"

/**
 * executor - runs envc command
 * @args: char that holds env arguments
 *
 * Return: exit status 0 for success, 1 has errored, -1 is failure
 **/

/** Function to execute a command **/
int executor(char *args[]);

int executor(char *args[])
{
	pid_t zpid, zwpid;
	int zstatus;

	(void)zwpid;
	zstatus = 0;
	zpid = fork();

	if (zpid == -1)
	{
		perror("shell: fork fatal error");
		printf("executor error: zpi is -1..\n");
		zstatus = -1;
		return (zstatus);
	}

	if (zpid == 0)
	{
		/** Creates a fork if process exists **/

		char *envp[] = { "PATH=/bin", NULL };

	if (execve(args[0], args, envp) == -1)
	{
		perror("shell process doesn't exist");
		printf("executor error: zpid is 0 && execve is -1..\n");
		zstatus = 1;
		/**		exit(EXIT_FAILURE); */
		return (zstatus);
	}

	}

	else if (zpid < 0)
	{
		perror("shell: fork env incorrect process group");
		printf("executor error: zpid is 0..\n");
		zstatus = -1;
	}

	/***********************************************************/
	else
	{

	do {
		printf("executor error: zwpid do..while \n");
		zwpid = waitpid(zpid, &zstatus, WUNTRACED);
	} while (!WIFEXITED(zstatus) && !WIFSIGNALED(zstatus));
	}

	/**	if(args) */
		/**		free(args); */

	return (zstatus);
}
