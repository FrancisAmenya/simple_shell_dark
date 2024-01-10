#include "main.h"
/**
 * find_cmd - Entry Point
 * @command: the argument passed
 * Return: Null
 */
char *find_cmd(char *command);

char *find_cmd(char *command)
{
	char *cenv_path, *cpath_copy, *cpath_token, *cfile_path;
	int icommand_length, idirectory_length;
	struct stat sbuffer;

	cenv_path = getenv("PATH");

	if (cenv_path)
	{
	cpath_copy = strdup(cenv_path);
	icommand_length = strlen(command);
	cpath_token = strtok(cpath_copy, ":");

	while (cpath_token != NULL)
	{
		idirectory_length = strlen(cpath_token);
		cfile_path = malloc(icommand_length + idirectory_length + 2);

		if (cfile_path == NULL)
		{
			printf("find_cmd: file search error");
			free_me(cpath_copy);
			return (NULL);
		}

		strcpy(cfile_path, cpath_token);
		strcat(cfile_path, "/");
		strcat(cfile_path, command);
		strcat(cfile_path, "\0");

		if (stat(cfile_path, &sbuffer) == 0)
		{
		printf("find_cmd: file search success");
			free_me(cpath_copy);
			return (cfile_path);
		}
		else
		{
		printf("find_cmd: file search halt");
			free_me(cfile_path);
			cpath_token = strtok(NULL, ":");
		}
	}

	if (cpath_copy != NULL)
	{
		printf("find_cmd: cpath_copy is NULL");
		free(cpath_copy);
	}

	}

	if (stat(command, &sbuffer) == 0)
	{
		printf("find_cmd: returning cmd");
		return (strdup(command));
	}

	return (NULL);
}
