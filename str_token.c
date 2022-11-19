#include "main.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

/**
 * split_str - splits a string into words.
 *
 * @str: the string to be split.
 *
 * Return: a struct containing
 *	-> an array containing each word of the string.
 *	-> number of items in the array.
 */
words_n split_str(char *str)
{
	words_n wrds;
	char **array = NULL;
	char *token, *copy;
	int i = 0, num_words = 0, len = 0;

	/* determine the number of words in the string */
	len = strlen(str) + 1;
	copy = malloc(sizeof(char) * len);
	if (copy == NULL)
	{
		perror("malloc failed to create copy");
		exit(EXIT_FAILURE);
	}
	strcpy(copy, str);
	token = strtok(copy, " ");
	while (token != NULL)
	{
		num_words++;
		token = strtok(NULL, " ");
	}
	free(copy);
	/*---------------------------------------------*/

	/* insert tokens to array */
	if (num_words != 0)
	{
		token = strtok(str, " ");
		array = malloc(sizeof(char *) * num_words);
		if (array == NULL)
		{
			perror("malloc failed to create array");
			exit(EXIT_FAILURE);
		}

		while (token != NULL)
		{
			array[i++] = token;
			token = strtok(NULL, " ");
		}
	}
	wrds.array = array;
	wrds.num = num_words;
	return (wrds);
}
