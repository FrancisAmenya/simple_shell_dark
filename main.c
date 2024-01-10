#include "main.h"
/**
 * main - main shell
 * @arg_ac: int of char count, argument 1
 * @argv: char of user string, argument 2
 *
 * Return: exit status, 0 if success, 1 if error, -1 if fail
 */
int main(int arg_ac, char **argv);

int main(int arg_ac, char **argv)
{
	char *char_uprompt = "$: ";
	char *char_lineptr = NULL;
	char *char_lineptr_cp = NULL;
	size_t ss_n = 0;
	ssize_t ss_ncharacters;
	const char *char_delimeter = " \n";
	int int_num_tokens = 0;
	char *char_token;
	int i = 0;
	(void)arg_ac;

	while (1)
	{
		printf("%s", char_uprompt);
		fflush(stdout);
		i = 0;
		ss_ncharacters = getline(&char_lineptr, &ss_n, stdin);
		/** see if getline fail or user exit */
		if (ss_ncharacters == -1 && isatty(STDIN_FILENO))
		{
			printf("Ctrl+D Exiting shell..\n");
			/** if (char_lineptr) */
			/**	free(char_lineptr); */
			free_me(char_lineptr);
			char_uprompt = NULL;
			char_delimeter = NULL;
			(void)&ss_n;
			(void)&int_num_tokens;
			(void)&i;
			return (0);
		}

		if (ss_ncharacters == 0)
		{
			printf("Nothing was typed.\n");
			/** if (char_lineptr) */
			/**	free(char_lineptr); */
			free_me(char_lineptr);
			return (0);
		}

		char_lineptr[strcspn(char_lineptr, "\n")] = '\0';

		if (strcmp(char_lineptr, "exit") == 0)
		{
			printf("User typed exit, exiting Shell..\n");
			/**if (char_lineptr) */
			/**free(char_lineptr); */
			free_me(char_lineptr);
			break;
		}

		if (strcmp(char_lineptr, "env") == 0)
		{
			/** execmd(char_lineptr); */
			printf("Not yet implemented, Exiting Shell..\n");
		}

		char_lineptr_cp = malloc(sizeof(char) * ss_ncharacters);
		if (char_lineptr_cp == NULL)
		{
			perror("tsh: memory allocation error");

			free_me(char_lineptr);
			free_me(char_lineptr_cp);
			return (-1);
		}

		strcpy(char_lineptr_cp, char_lineptr);
		char_token = strtok(char_lineptr, char_delimeter);

		while (char_token != NULL)
		{
			int_num_tokens++;
			char_token = strtok(NULL, char_delimeter);
		}

		int_num_tokens++;

		argv = malloc(sizeof(char *) * int_num_tokens);
		char_token = strtok(char_lineptr_cp, char_delimeter);


		for (i = 0; char_token != NULL; i++)
		{

			argv[i] = malloc(sizeof(char) * (strlen(char_token)) + 1);
			strcpy(argv[i], char_token);
			char_token = strtok(NULL, char_delimeter);
		}
		argv[i] = NULL;

		/**added to test env cmd*/
		if (argv)
		{
			exec_mgr(argv);
		}
		/**end *added to test env cmd*/
		for (i = 0; argv[i] != NULL; i++)
		{
			free_me(argv[i]);
		}

			free_me(char_lineptr);
			free_me(char_token);
			free_me(char_lineptr_cp);
		/** if (char_lineptr_cp != NULL) */
		/** free_me(char_lineptr_cp); */

		/** if (char_lineptr != NULL) */
		/** free_me(char_lineptr); */

		printf("_________________2nd last:@ Main While\n");
	}

	printf("_________________last:@Main\n");
	return (0);
}
