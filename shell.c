#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>

char **argv;
char *line = NULL, *line2 = NULL;

char *my_strtok_r(char *str, const char *delim, char **save_ptr);
char **my_str_to_array(char *s, const char *delim);
void sig_handler(int signum);

/**
 * main - a simple shell program that takes in commands from the
 * terminal and executes them
 *
 * Return: 0 on success
 */
int main(void)
{
	char *line3, *line4;
	char delim[] = " ";
	size_t nread = 0, len = 0;
	pid_t child_pid;
	int status;

	signal(SIGINT, sig_handler);

	while (1)
	{
		printf("#cisfun$ ");
		nread = getline(&line, &len, stdin);
		if (nread != -1)
		{
			line2 = malloc(sizeof(*line2) * (strlen(line)));
			if (line2 == NULL)
			{
				free(line);
				line = NULL;
				exit(1);
			}

			line3 = line2;
			line4 = line;
			while (*line4)
			{
				if (*line4 == '\n')
				{
					*line3 = '\0';
					break;
				}
				*line3 = *line4;
				++line3;
				++line4;
			}
			argv = my_str_to_array(line2, delim);
			if (argv == NULL)
			{
				free(line);
				free(line2);
				line = NULL;
				line2 = NULL;
				exit(1);
			}
			char **argv2 = argv;

			child_pid = fork();
			if (child_pid == 0)
			{

				printf("Before execve\n");
				printf("%s", argv2[0]);
				if (execve(argv2[0], argv2, NULL) == -1)
				{
					perror("Error:");
					printf("\n");
				}
			}
			else
			{
				wait(&status);
				if (line != NULL)
					free(line);
				free(line2);
				free(argv);
				line = NULL;
				line2 = NULL;
				argv = NULL;
				printf("After execve\n");
			}
		}
	}
	exit(EXIT_SUCCESS);
}

/**
 * sig_handler - handles termination signals by freeing allocated
 * resources first
 * @signum: signal number
 */

void sig_handler(int signum)
{
	if (line != NULL)
		free(line);
	free(line2);
	free(argv);
	line = NULL;
	line2 = NULL;
	argv = NULL;
	signal(signum, SIG_DFL);
	raise(signum);
}

/**
 * my_str_to_array - converts an input string into an array of strings
 * @s: the input string
 * @delim: the delimiter on which the input string is split
 *
 * Return: a pointer to an array of character pointers
 */

char **my_str_to_array(char *s, const char *delim)
{
	char *str, *token, *save_ptr;
	char **arr = NULL;
	unsigned int i;

	for (i = 0, str = s;; ++i, str = NULL)
	{
		token = my_strtok_r(str, delim, &save_ptr);
		/**
		 *token_len = strlen(token) + 1;
		 *arr_size += token_len;
		 */
		arr = (char **)realloc(arr, (sizeof(char **) * (i + 1)));
		if (arr == NULL)
		{
			return (NULL);
		}
		arr[i] = token;
		if (token == NULL)
			break;
	}
	return (arr);
}

/**
 * my_strtok_r -  Parse S into tokens separated by characters in DELIM.
 * If S is NULL, the saved pointer in SAVE_PTR is used as
 * the next starting point
 * @s: the string to be broken into tokens
 * @delim: the token separator
 * @save_ptr: the save pointer where the pointer to
 * the next starting point is stored.
 *
 * Return: pointer to token or Null if none
 */

char *my_strtok_r(char *s, const char *delim, char **save_ptr)
{
	char *end;

	if (s == NULL)
		s = *save_ptr;
	if (*s == '\0')
	{
		*save_ptr = s;
		return (NULL);
	}
	/* Scan leading delimiters.  */
	s += strspn(s, delim);
	if (*s == '\0')
	{
		*save_ptr = s;
		return (NULL);
	}

	/* Find the end of the token */
	end = s + strcspn(s, delim);
	if (*end == '\0')
	{
		*save_ptr = end;
		return (s);
	}
	/* Terminate the token and make *SAVE_PTR point past it. */
	*end = '\0';
	*save_ptr = end + 1;
	return (s);
}
