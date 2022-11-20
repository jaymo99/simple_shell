#ifndef MAIN_H
#define MAIN_H


/**
 * struct words_n - an array of words
 *
 * @array: array containing word tokens
 * @num: number of words/items in the array.
 */
typedef struct words_n
{
	char **array;
	int num;
} words_n;


/* get_file_path.c */
char *get_file_path(char *file);
char *find_file(char *token, char *file);
int check_builtins(char *cmd);

/* str_token.c */
words_n split_str(char *str);

/* main.c */
char *init_shell(void);


#endif /* MAIN_H */
