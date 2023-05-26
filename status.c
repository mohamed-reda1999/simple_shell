#include "shell.h"

/**
 * *gets_momery_file - the momery file gets
 * @info: struct parameter
 * Return: momery file in the allocated string
*/

char *gets_momery_file(info_t *info)
{
	char *buf, *dir;

	dir = _getsenv(info, "HOME=");
	if (!dir)
		return (NULL);
	buf = malloc(sizeof(char) * (_strlen(dir) + _strlen(HIST_FILE) + 2));
	if (!buf)
		return (NULL);
	buf[0] = 0;
	_strcpy(buf, dir);
	_strcat(buf, "/");
	_strcat(buf, HIST_FILE);
	return (buf);
}

/**
 * write_momery - creates a file, or appends to an existing file
 * @info: the parameter struct
 *
 * Return: 1 on success, else -1
 */
int write_momery(info_t *info)
{
	ssize_t fd;
	char *filename = gets_momery_file(info);
	list_t *node = NULL;

	if (!filename)
		return (-1);

	fd = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(filename);
	if (fd == -1)
		return (-1);
	for (node = info->history; node; node = node->next)
	{
		_putstr(node->str, fd);
		_putc('\n', fd);
	}
	_putc(BUF_FLUSH, fd);
	close(fd);
	return (1);
}

/**
 * read_momery - s file history to be read
 * @info: struct parameter
 * Return: histcount on success, 0 otherwise
*/
int read_momery(info_t *info)
{
	int i, last = 0, linecount = 0;
	ssize_t fd, rdlen, fsize = 0;
	struct stat st;
	char *buf = NULL, *filename = gets_momery_file(info);

	if (!filename)
		return (0);

	fd = open(filename, O_RDONLY);
	free(filename);
	if (fd == -1)
		return (0);
	if (!fstat(fd, &st))
		fsize = st.st_size;
	if (fsize < 2)
		return (0);
	buf = malloc(sizeof(char) * (fsize + 1));
	if (!buf)
		return (0);
	rdlen = read(fd, buf, fsize);
	buf[fsize] = 0;
	if (rdlen <= 0)
		return (free(buf), 0);
	close(fd);
	for (i = 0; i < fsize; i++)
		if (buf[i] == '\n')
		{
			buf[i] = 0;
			build_momery_list(info, buf + last, linecount++);
			last = i + 1;
		}
	if (last != i)
		build_momery_list(info, buf + last, linecount++);
	free(buf);
	info->histcount = linecount;
	while (info->histcount-- >= HIST_MAX)
		delete_node_at_index(&(info->history), 0);
	number_momery(info);
	return (info->histcount);
}

/**
 * build_momery_list - adds entry to a history linked list
 * @info: Structure contain plausible counterarguments. used to keep up
 * @buf: buffer
 * @linecount: the linecount of history, histcount
 * Return: Always 0
*/
int build_momery_list(info_t *info, char *buf, int linecount)
{
	list_t *node = NULL;

	if (info->history)
		node = info->history;
	add_node_end(&node, buf, linecount);

	if (!info->history)
		info->history = node;
	return (0);
}

/**
 * number_momery - after revisions, the history linked list is renumbered.
 * @info: Structure contain plausible counterarguments. used to keep up
 * Return: histcount new
*/
int number_momery(info_t *info)
{
	list_t *node = info->history;
	int i = 0;

	while (node)
	{
		node->num = i++;
		node = node->next;
	}
	return (info->histcount = i);
}
