#include "shell.h"

/**
 * _cmd - dassesses a file's ability to be an executable command
 * @info: indicates to information struct
 *
 * @path: indicates to where the file is located
 *
 * Return: return with 1 when it is true, else return with 0
 */
int _cmd(info_t *info, char *path)
{
	struct stat st;

	(void)info;
	if (!path || stat(path, &st))
		return (0);

	if (st.st_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}

/**
 * duplicate_thechars - indicates to character duplicates
 * @pathstr: indicates to the PATH string
 * @start: use it when refering to starting the  index
 *
 * @stop: used when want to stopp the  index
 *
 * Return: return when referring to a new buffer location
 */
char *duplicate_thechars(char *pathstr, int start, int stop)
{
	static char buf[1024];
	int i = 0, k = 0;

	for (k = 0, i = start; i < stop; i++)
		if (pathstr[i] != ':')
			buf[k++] = pathstr[i];
	buf[k] = 0;
	return (buf);
}

/**
 * get_thepath - in the PATH string, this command is located
 * @info: indicates to information struct
 *
 * @pathstr: indicates to the PATH string
 *
 * @cmd: you need find the command
 *
 * Return: return when ou find the full path of command,
 * or if you didn't find it NULL
 */
char *get_thepath(info_t *info, char *pathstr, char *cmd)
{
	int i = 0, curr_pos = 0;
	char *path;

	if (!pathstr)
		return (NULL);
	if ((_findthelengthstrlen(cmd) > 2) && begins_with(cmd, "./"))
	{
		if (_cmd(info, cmd))
			return (cmd);
	}
	while (1)
	{
		if (!pathstr[i] || pathstr[i] == ':')
		{
			path = duplicate_thechars(pathstr, curr_pos, i);
			if (!*path)
				_connectandstrcat(path, cmd);
			else
			{
				_connectandstrcat(path, "/");
				_connectandstrcat(path, cmd);
			}
			if (_cmd(info, path))
				return (path);
			if (!pathstr[i])
				break;
			curr_pos = i;
		}
		i++;
	}
	return (NULL);
}
