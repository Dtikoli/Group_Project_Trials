#ifndef _MAIN_H_
#define _MAIN_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>

/*  buffer size */
#define BUFF_SIZE 1024
#define BUF_FLUSH -1

/* command chaining */
#define CMD_NORM	0
#define CMD_OR		1
#define CMD_AND		2
#define CMD_CHAIN	3

/* number conversion */
#define CONVERT_LOWER		1
#define CONVERT_UNSIGNED	2

/* system getline */
#define USE_GETLINE 0
#define USE_STRTOK 0

#define INFO_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
	0, 0, 0}

#define HIST_FILE	".simple_shell_history"
#define HIST_MAX	4096

extern char **environ;


/**
 * struct liststr - singly linked list
 * @num: the number fields
 * @str: a string
 * @next: a pointer to the next node
 */
typedef struct liststr
{
	int num;
	char *str;
	struct liststr *next;
} list_t;

/**
 *struct pass_info - contains pseudo-arguements to pass into a function
 *@arg: a string generated from getline containing CL arguements
 *@argv: array of strings from CL arguments
 *@path: a string path for the current command
 *@argc: number of CL arguments
 *@line_count: the error count
 *@err_num: the error code for exit function
 *@linecount_flag: if on, count this line of input
 *@fname: filename of the program
 *@env: linked list local copy of environ
 *@environ: custom modified copy of environ from LL env
 *@history: the history node
 *@alias: the alias node
 *@env_changed: on if, environ was changed
 *@status: return status of the last executed command
 *@cmd_buf: address of pointer to cmd_buf, on if chaining
 *@cmd_buf_type: CMD_type ||, &&, ;
 *@readfd: the fd from which to read line input
 *@histcount: the history line number count
 */
typedef struct pass_info
{
	char *arg;
	char **argv;
	char *path;
	int argc;
	unsigned int line_count;
	int err_num;
	int linecount_flag;
	char *fname;
	list_t *env;
	list_t *history;
	list_t *alias;
	char **environ;
	int env_changed;
	int status;
	char **cmd_buf; /* pointer to cmd ; chain buffer, for memory mangement */
	int cmd_buf_type; /* CMD_type ||, &&, ; */
	int readfd;
	int histcount;
} info_t;

/**
 *struct built_in - contains a builtin string and related functions
 *@type: the builtin command flag
 *@func: the function pointers
 */
typedef struct built_in
{
	char *type;
	int (*func)(info_t *);
} builtin_t;


/* hsh functions */
int hsh(info_t *, char **);
int find_builtin(info_t *);
void find_cmd(info_t *);
void fork_cmd(info_t *);

/* path functions*/
int is_cmd(info_t *, char *);
char *dup_chars(char *, int, int);
char *find_path(info_t *, char *, char *);

/* loophsh function */
int loophsh(char **);

/* error functions */
void _err_puts(char *);
void _print_err(info_t *, char *);
int _err_atoi(char *);
int _err_putc(char);
int _putc_fd(char c, int fd);
int _puts_fd(char *str, int fd);

/* string functions.c */
int _strlen(char *);
int _strcmp(char *, char *);
char *_starts_with(const char *, const char *);
char *_strcat(char *, char *);
char *_strcpy(char *, char *);
char *_strdup(const char *);
char *_strncpy(char *, char *, int);
char *_strncat(char *, char *, int);
char *_strchr(char *, char);
char **strtowk(char *, char *);
char **_strtowk(char *, char);

/* memory functions */
char *_memset(char *, char, unsigned int);
void _ffree(char **);
void *_realloc(void *, unsigned int, unsigned int);
int _bfree(void **);

/* helper functions */
int _interact(info_t *);
void _puts(char *);
int _putchar(char);
int _is_delim(char, char *);
int _isalpha(int);

/* conversion functions */
int _print_decimal(int, int);
int _atoi(char *);
char *convert_num(long int, int, int);
void _remove_comments(char *);

/* builtin emulators */
int _myexit(info_t *);
int _mycd(info_t *);
int _myhelp(info_t *);
int _myhistory(info_t *);
int _myalias(info_t *);

/* module for getline */
ssize_t get_input(info_t *);
int _getline(info_t *, char **, size_t *);
void sigintHandler(int);

/* modue for info */
void clear_info(info_t *);
void set_info(info_t *, char **);
void free_info(info_t *, int);

/*module for env */
char *_getenv(info_t *, const char *);
int _myenv(info_t *);
int _mysetenv(info_t *);
int _myunsetenv(info_t *);
int _push_env_list(info_t *);
char **_get_environ(info_t *);
int _unsetenv(info_t *, char *);
int _setenv(info_t *, char *, char *);

/* module for chain */
int is_chain(info_t *, char *, size_t *);
void check_chain(info_t *, char *, size_t *, size_t, size_t);
int replace_alias(info_t *);
int replace_vars(info_t *);
int replace_string(char **, char *);

/* file input/output_functions */
char *_get_hist_file(info_t *info);
int _write_hist(info_t *info);
int _read_hist(info_t *info);
int _build_hist_list(info_t *info, char *, int);
int _renum_hist(info_t *info);

/* lists_t functions */
list_t *add_node(list_t **, const char *, int);
list_t *add_node_end(list_t **, const char *, int);
size_t print_list_str(const list_t *);
int delete_node_index(list_t **, unsigned int);
void free_list(list_t **);
size_t list_len(const list_t *);
char **list_to_strings(list_t *);
size_t print_list(const list_t *);
list_t *node_starts_with(list_t *, char *, char);
ssize_t get_node_index(list_t *, list_t *);

#endif / #ifndef _MAIN_H_

