#include "shell.h"

/**
 * assumptionsloop - refers to a loop being present,
 * in the main shell
 * @info: refers to Parameter and returned information struct to use
 *
 * @av: from main() you can find the argument vector
 *
 * Return: return with 0 when you succeed,
 * return with 1 on error, or error code
 */
int assumptionsloop(info_t *info, char **av)
{
	ssize_t r = 0;
	int builtin_ret = 0;

	while (r != -1 && builtin_ret != -2)
	{
		clear_fo(info);
		if (inter_atoi(info))
			_adds("$ ");
		_eputstr(BUF_FLUSH);
		r = gets_input(info);
		if (r != -1)
		{
			set_fo(info, av);
			builtin_ret = get_thebuiltin(info);
			if (builtin_ret == -1)
				get_thecmd(info);
		}
		else if (interactive(info))
			_putstr('\n');
		free_fo(info, 0);
	}
	write_momery(info);
	free_fo(info, 1);
	if (!inter_atoi(info) && info->status)
		exit(info->status);
	if (builtin_ret == -2)
	{
		if (info->err_num == -1)
			exit(info->status);
		exit(info->err_num);
	}
	return (builtin_ret);
}

/**
 * find_builtin - a built in command must be found
 * @info: refers to Parameter and returned information struct
 *
 * Return: return with -1 if you didn't find the builtin,
 * return with 0 if builtin functioned with success,
 * return with 1 if builtin was found but didn't succeed,
 * return with 2 if builtin signals with exit()
 */
int get_thebuiltin(info_t *info)
{
	int i, built_in_ret = -1;
	builtin_table builtintbl[] = {
		{"exit", _weexit},
		{"env", _weenv},
		{"help", _wehelp},
		{"history", _wemomery},
		{"setenv", _wesetenv},
		{"unsetenv", _weunsetenv},
		{"cd", _wecd},
		{"alias", _alias},
		{NULL, NULL}
	};

	for (i = 0; builtintbl[i].type; i++)
		if ( _compareandstrcmp(info->argv[0], builtintbl[i].type) == 0)
		{
			info->line_count++;
			built_in_ret = builtintbl[i].func(info);
			break;
		}
	return (built_in_ret);
}

/**
 * get_thecmd - a command in PATH must be found
 * @info: refers to Parameter and returned information struct
 *
 * Return: you must return with void
 */
void get_thecmd(info_t *info)
{
	char *path = NULL;
	int i, k;

	info->path = info->argv[0];
	if (info->linecount_flag == 1)
	{
		info->line_count++;
		info->linecount_flag = 0;
	}
	for (i = 0, k = 0; info->arg[i]; i++)
		if (! delim(info->arg[i], " \t\n"))
			k++;
	if (!k)
		return;

	path = get_thepath(info, _getsenv(info, "PATH="), info->argv[0]);
	if (path)
	{
		info->path = path;
		forks_thecmd(info);
	}
	else
	{
		if ((inter_atoi(info) || _getsenv(info, "PATH=")
					|| info->argv[0][0] == '/') && _cmd(info, info->argv[0]))
			forks_thecmd(info);
		else if (*(info->arg) != '\n')
		{
			info->status = 127;
			print_error(info, "not found\n");
		}
	}
}

/**
 * forks_thecmd - the process of forking an exec thread involves running cmd
 * @info: refers to Parameter and returned information struct
 *
 * * Return: you must return with void
 */
void forks_thecmd(info_t *info)
{
	pid_t child_pid;

	child_pid = fork();
	if (child_pid == -1)
	{
		/* TODO: PUT ERROR FUNCTION */
		perror("Error:");
		return;
	}
	if (child_pid == 0)
	{
		if (execve(info->path, info->argv, get_environ(info)) == -1)
		{
			free_info(info, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
		/* TODO: PUT ERROR FUNCTION */
	}
	else
	{
		wait(&(info->status));
		if (WIFEXITED(info->status))
		{
			info->status = WEXITSTATUS(info->status);
			if (info->status == 126)
				print_error(info, "Permission denied\n");
		}
	}
}
