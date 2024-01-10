#include "main.h"
/**
 * exec_mgr - Entry Point
 * @argv: command arguments typed by user
 *
 * Return: status 0 if success, -1 if failed, 1 if error
 */
int exec_mgr(char **argv);

int exec_mgr(char **argv)
{
	char *ccommand = NULL, *cactual_command = NULL;
	int status = 0;

	if (argv && argv[0])
	{
		ccommand = argv[0];

		cactual_command = find_cmd(ccommand);

		if (cactual_command)
		{
			pid_t child_pid = fork();

			

			if (child_pid == -1)
			{
				perror("fork failed:");
				return (0);
			}

			if (child_pid == 0)
			{

				if (execve(cactual_command, argv, NULL) == -1)
				{
					perror("Hsh: wrong user group, please retry");
					exit(EXIT_FAILURE);
				}
			}
			else
			{
				waitpid(child_pid, &status, 0);
				if (WIFEXITED(status))
				{
					return (WEXITSTATUS(status));
				}
			}
		}
		else
		{
			printf("%s: not found \n", ccommand);
			return (0);
		}
	}

	if (ccommand != NULL)
	{
		printf("exec_mgr: attempting to free ccommand");
		free_me(ccommand);
	}
	return (0);
}
