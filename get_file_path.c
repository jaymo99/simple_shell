#include "main.h"
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

/**
 * get_file_path - looks for a file in the current PATH.
 *
 * @file: the file to look for.
 *
 * Return: on success, the full path of the specified file.
 * on failure, NULL
 */
char *get_file_path(char *file)
{
	int st;
	size_t len = 0;
	char *env_path, *file_path, *str, *token;
	struct stat statbuf;

	env_path = getenv("PATH");
	if (env_path == NULL)
	{
		printf("PATH cannot be NULL\n");
		exit(EXIT_FAILURE);
	}

	/* length of path string */
	len = strlen(env_path);

	/* len+3 for null byte '\0', and path to current directory '.:' */
	str = malloc(sizeof(char) * (len + 3));
	if (str == NULL)
	{
		printf("malloc failed allocating str\n");
		exit(EXIT_FAILURE);
	}
	/* the dot(.) is a token used to indicate path to current directory */
	strcpy(str, ".:");
	strcat(str, env_path);

	/* string tokens */
	token = strtok(str, ":");

	st = stat(file, &statbuf);
	if (st == 0)
	{
		free(str);
		return (file);
	}
	else
	{
		file_path = find_file(token, file);
		free(str);
		return (file_path);
	}
}

/**
 * find_file - looks for a file in the '@token' directory.
 *
 * @token: directory to look in.
 * @file: filename
 *
 * Return: on success, the full path to the file
 * on failure, NULL.
 */
char *find_file(char *token, char *file)
{
	int st;
	char *file_path;
	struct stat statbuf;

	if (token == NULL)
		return (NULL);

	file_path = malloc(strlen(token) + strlen(file) + 2);
	if (file_path == NULL)
	{
		printf("malloc failed allocating file_path\n");
		exit(EXIT_FAILURE);
	}
	strcpy(file_path, token);
	strcat(file_path, "/");
	strcat(file_path, file);

	st = stat(file_path, &statbuf);
	if (st == 0)
		return (file_path);

	token = strtok(NULL, ":");
	free(file_path);
	return (find_file(token, file));
}

/**
 * check_builtins - executes 'built-in' shell commands.
 *
 * @cmd: the command
 *
 * Return: 0 if @cmd is a built-in command
 * 1, otherwise
 */
int check_builtins(char *cmd)
{
	if (strcmp(cmd, "exit") == 0)
	{
		return (0);
	}
	return (1);
}
