#ifndef _SHELL_H_
#define _SHELL_H_

#include <sys/wait.h>
#include <sys/stat.h>
#include <stdio.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>

/* for command chaining */
#define CMD_NORM        0
#define CMD_OR          1
#define CMD_AND         2
#define CMD_CHAIN       3

/* for read/write buffers */
#define READ_BUF_SIZE 1024
#define WRITE_BUF_SIZE 1024
#define BUF_FLUSH -1

/* for convert_number() */
#define CONVERT_LOWERCASE	1
#define CONVERT_UNSIGNED	2

/* 1 if using system getline() */
#define USE_GETLINE 0
#define USE_STRTOK 0

#define HIST_FILE	".simple_shell_history"
#define HIST_MAX	4096

extern char **environ;


/**
 * struct liststr - individual linked list
 * @num: filde the number
 * @str: a string
 * @next: points to the next node
 */
typedef struct liststr
{
	int num;
	char *str;
	struct liststr *next;
} list_t;

/**
 * struct passinfo - provides fictitious arguments,
 * that can be used to call a function,
 * allowing a consistent prototype for function pointer structs.
 * @arg: a string produced by getline that contains arguments
 * @argv:an array of strings generated from arg
 * @path: a string path for the current command
 * @argc: the argument count
 * @line_count: the error count
 * @err_num: the error code for exit()s
 * @linecount_flag: if this line of input counts,
 * @fname: the program filename
 * @env: linked list local copy of environ
 * @environ: custom modified copy of environ from LL env
 * @history: the history node
 * @alias: the alias node
 * @env_changed: on if environ was changed
 * @status: the return status of the last exec'd command
 * @cmd_buf: address of pointer to cmd_buf, on if chaining
 * @cmd_buf_type: CMD_type ||, &&, ;
 * @readfd: the fd from which to read line input
 * @histcount: the history line number count
 */
typedef struct passinfo
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

	char **cmd_buf; /* chain buffer; reference to cmd; for memory management */
	int cmd_buf_type; /* CMD_type ||, &&, ; */
	int readfd;
	int histcount;
} info_t;

#define INFO_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
		0, 0, 0}

/**
 * struct builtin - includes a built-in string,
 * associated functionality, as well as a
 * @type: built-in command flag.
 * @func: the function
 */
typedef struct builtin
{
	char *type;
	int (*func)(info_t *);
} builtin_table;


/* _atoi1.c */
int inter_atoi(info_t *);
int delim(char, char *);
int alpha(int);
int _toi(char *);

/* unix.c */
int _weexit(info_t *);
int _wecd(info_t *);
int _wehelp(info_t *);

/* unix1.c */
int _wealias(info_t *);
int _wemomrey(info_t *);

/* arguments.c */
int _weenv(info_t *);
char *_getsenv(info_t *, const char *);
int _weunsetenv(info_t *);
int _wesetenv(info_t *);
int pulate_env_list(info_t *);

/* exists.c */
int _eputint(char);
void _eput(char *);
int _putstr(char *str, int fd);
int _putc(char c, int fd);

/* exists1.c */
int echo_int(int, int);
void delete_comments(char *);
char *change_number(long int, int, int);
void echo_error(info_t *, char *);
int _err(char *);

/* exit.c */
char *_strct(char *, char *, int);
char *_strcp(char *, char *, int);
char *_strch(char *, char);

/* thebuilt-in.c */
void sigin(int);
int _getsline(info_t *, char **, size_t *);
ssize_t gets_input(info_t *);

/* gettheline.c */
int *setint(info_t *, char *, char *);
char _gets_environ(info_t *);
int _unsetint(info_t *, char *);

/* strings.c */
void clear_fo(info_t *);
void free_fo(info_t *, int);
void set_fo(info_t *, char **);

/* status.c */
int read_momery(info_t *info);
char *gets_momery_file(info_t *info);
int build_momery_list(info_t *info, char *buf, int linecount);
int number_momery(info_t *info);
int write_momery(info_t *info);

/* environment.c */
int delete_node_at_index(list_t **, unsigned int);
list_t *add_node(list_t **, const char *, int);
size_t print_list_str(const list_t *);
list_t *add_node_end(list_t **, const char *, int);
void free_list(list_t **);

/* environment1.c */
char **list_to_strings(list_t *);
size_t list_len(const list_t *);
size_t print_list(const list_t *);
ssize_t get_node_index(list_t *, list_t *);
list_t *node_starts_with(list_t *, char *, char);

/* implementation.c */
int bfree(void **);

/*separator.c */
char *find_path(info_t *, char *, char *);
int is_cmd(info_t *, char *);
char *dup_chars(char *, int, int);

/* operators.c */
void *_realloc(void *, unsigned int, unsigned int);
void ffree(char **);
char *_memset(char *, char, unsigned int);

/* assumptions.c */
void fork_cmd(info_t *);
int hsh(info_t *, char **);
void find_cmd(info_t *);
int find_builtin(info_t *);


/* variables.c */
char *starts_with(const char *, const char *);
int _strlen(char *);
char *_strcat(char *, char *);
int _strcmp(char *, char *);

/* variables1.c */
char *_strcpy(char *, char *);
char *_strdup(const char *);
void _puts(char *);
int _putchar(char);

/* comments.c */
char **strtow2(char *, char);
char **strtow(char *, char *);

/* descriptor.c */
int replace_string(char **, char *);
int is_chain(info_t *, char *, size_t *);
int replace_alias(info_t *);
int replace_vars(info_t *);
void check_chain(info_t *, char *, size_t *, size_t, size_t);

#endif
